
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/uuid.h"


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


// Função para destruir a tabela de hash
void destroy_uuid_table(UuidHashTable *table) {
    for (int i = 0; i < table->size; i++) {
        free_uuid_nodes(table->buckets[i]);
    }
    free(table->buckets);
    free(table);
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
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->count++;
}
