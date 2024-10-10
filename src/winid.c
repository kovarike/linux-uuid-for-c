#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <fcntl.h>
#include <errno.h>
#include <wincrypt.h>

#include "../include/winid.h"

// Função de logging
void log_message(const char *message) {
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file) {
        fprintf(log_file, "%s\n", message);
        fclose(log_file);
    } else {
        perror("Erro ao abrir o arquivo de log");
    }
}

// Função para liberar memória da lista encadeada
void free_uuid_nodes(UuidNode *node) {
    while (node) {
        UuidNode *temp = node;
        node = node->next;
        free(temp);
    }
}

// Função para destruir a tabela de hash
void destroy_uuid_table(UuidHashTable *table) {
    if (table) {
        for (int i = 0; i < table->size; i++) {
            free_uuid_nodes(table->buckets[i]);
        }
        free(table->buckets);
        free(table);
    }
}

// Inicializa a tabela de hash
UuidHashTable *init_uuid_table(int size) {
    UuidHashTable *table = malloc(sizeof(UuidHashTable));
    if (!table) {
        perror("Erro ao alocar memória para a tabela de hash");
        exit(EXIT_FAILURE);
    }
    table->buckets = calloc(size, sizeof(UuidNode *));  // Inicializa os buckets com NULL
    if (!table->buckets) {
        perror("Erro ao alocar memória para os buckets");
        free(table);
        exit(EXIT_FAILURE);
    }
    table->size = size;
    table->count = 0;
    return table;
}

// Função para adicionar UUID à tabela de hash
void add_uuid(UuidHashTable *table, const char *uuid) {
    if ((double)table->count / table->size > LOAD_FACTOR) {
        resize_table(table);
    }

    unsigned int index = hash(uuid, table->size);
    UuidNode *new_node = malloc(sizeof(UuidNode));
    if (!new_node) {
        perror("Erro ao alocar memória para novo nó");
        exit(EXIT_FAILURE);
    }
    strncpy(new_node->uuid, uuid, SIZE_ID);
    new_node->uuid[SIZE_ID - 1] = '\0';  // Certificar que o UUID está corretamente terminando em nulo
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->count++;
}

// Função para redimensionar a tabela de hash
void resize_table(UuidHashTable *table) {
    int new_size = table->size * 2;
    UuidNode **new_buckets = calloc(new_size, sizeof(UuidNode *));
    if (!new_buckets) {
        perror("Erro ao alocar memória para nova tabela de hash");
        exit(EXIT_FAILURE);
    }

    // Rehash todos os elementos da tabela antiga para a nova tabela
    for (int i = 0; i < table->size; i++) {
        UuidNode *node = table->buckets[i];
        while (node) {
            UuidNode *next_node = node->next;
            unsigned int new_index = hash(node->uuid, new_size);
            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;
            node = next_node;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->size = new_size;
    log_message("Tabela de hash redimensionada."); // Log de redimensionamento
}

// Função de hash simples baseada na soma dos caracteres
unsigned int hash(const char *uuid, int table_size) {
    unsigned int hash_value = 0;
    while (*uuid) {
        hash_value = (hash_value * 31) + *uuid++;
    }
    return hash_value % table_size;
}

// Verifica se o UUID é único
int is_unique_uuid(UuidHashTable *table, const char *uuid) {
    unsigned int index = hash(uuid, table->size);
    UuidNode *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->uuid, uuid) == 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

// Função para copiar UUID para a estrutura User
void parse(char *out, Uuid *uuid, UuidHashTable *uuid_table) {
    if (out != NULL) {
        strncpy(out, uuid->uuid, SIZE_ID);
        out[SIZE_ID - 1] = '\0';

        while (!is_unique_uuid(uuid_table, uuid->uuid)) {
            fprintf(stderr, "UUID duplicado detectado, gerando outro...\n");
            log_message("UUID duplicado detectado, gerando outro...");
            guuid(uuid);
        }
        add_uuid(uuid_table, out);
    } else {
        fprintf(stderr, "Erro: User não pode ser nulo.\n");
        log_message("Erro: User não pode ser nulo.");
        exit(EXIT_FAILURE);
    }
}

void generate_random_bytes(unsigned char *buffer, size_t size) {
    HCRYPTPROV hProvider = 0;
    if (!CryptAcquireContext(&hProvider, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        fprintf(stderr, "Erro ao adquirir contexto de criptografia.\n");
        log_message("Erro ao adquirir contexto de criptografia.");
        exit(EXIT_FAILURE);
    }
    
    if (!CryptGenRandom(hProvider, size, buffer)) {
        fprintf(stderr, "Erro ao gerar números aleatórios no Windows.\n");
        log_message("Erro ao gerar números aleatórios no Windows.");
        CryptReleaseContext(hProvider, 0);
        exit(EXIT_FAILURE);
    }

    CryptReleaseContext(hProvider, 0);
}

// Função para gerar o UUID v4
void guuid(Uuid *uuid) {
    unsigned char random_bytes[16];
    generate_random_bytes(random_bytes, sizeof(random_bytes));

    // Ajusta os bits para a versão 4 e variante RFC 4122
    random_bytes[6] = (random_bytes[6] & 0x0F) | 0x40;
    random_bytes[8] = (random_bytes[8] & 0x3F) | 0x80;

    snprintf(uuid->uuid, SIZE_ID, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
             random_bytes[0], random_bytes[1], random_bytes[2], random_bytes[3],
             random_bytes[4], random_bytes[5],
             random_bytes[6], random_bytes[7],
             random_bytes[8], random_bytes[9],
             random_bytes[10], random_bytes[11],
             random_bytes[12], random_bytes[13], random_bytes[14], random_bytes[15]);
}

// Função para criar e inicializar um UUID
Uuid* create_uuid() {
    Uuid *uuid = malloc(sizeof(Uuid));
    if (!uuid) {
        perror("Erro ao alocar memória para UUID");
        return NULL; // Ou trate o erro de outra forma
    }
    guuid(uuid); // Gera um UUID
    return uuid;
}