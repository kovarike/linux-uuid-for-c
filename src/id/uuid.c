#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "../../include/uuid.h"


// Função de hash simples baseada na soma dos caracteres
unsigned int hash(const char *uuid, int table_size) {
    unsigned int hash_value = 0;
    while (*uuid) {
        hash_value = (hash_value * 31) + *uuid++;
    }
    return hash_value % table_size;
}


// Função para liberar memória da lista encadeada
void free_uuid_nodes(UuidNode *node) {
    while (node) {
        UuidNode *temp = node;
        node = node->next;
        free(temp);
    }
}

// Função para gerar números aleatórios de forma segura (Linux/Windows)
void generate_random_bytes(unsigned char *buffer, size_t size) {
#if defined(__linux__) || defined(__APPLE__)
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        perror("Erro ao abrir /dev/urandom");
        log_message("Erro ao abrir /dev/urandom");
        exit(EXIT_FAILURE);
    }
    ssize_t bytes_read = read(fd, buffer, size);
    if (bytes_read != size) {
        perror("Erro ao ler bytes aleatórios");
        log_message("Erro ao ler bytes aleatórios");
        exit(EXIT_FAILURE);
    }
    close(fd);
#elif defined(_WIN32) || defined(_WIN64)
    if (BCryptGenRandom(NULL, buffer, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
        fprintf(stderr, "Erro ao gerar números aleatórios no Windows.\n");
        log_message("Erro ao gerar números aleatórios no Windows.");
        exit(EXIT_FAILURE);
    }
#else
    fprintf(stderr, "Erro: Sistema não suportado.\n");
    log_message("Erro: Sistema não suportado.");
    exit(EXIT_FAILURE);
#endif
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

// Função para copiar UUID para a estrutura User
void unparse(char *out, Uuid *uuid) { 
    UuidHashTable *uuid_table = init_uuid_table(INITIAL_SIZE);
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
        destroy_uuid_table(uuid_table);
        fprintf(stderr, "Erro: User não pode ser nulo.\n");
        log_message("Erro: User não pode ser nulo.");
        exit(EXIT_FAILURE);
    }

    destroy_uuid_table(uuid_table);
}


// int main() {
  
//     Uuid *uud;
    
//     guuid(uud);
//     // unparse(uuid, id);
//     printf("uud:%s\n", uud);
        
//     guuid(uud);
//     // unparse(uuid, id);
//     printf("uud:%s\n", uud);
       
    
//     guuid(uud);
//     // unparse(uuid, id);
//     printf("uud:%s\n", uud);
      
    
//     guuid(uud);
//     // unparse(uuid, id);
//     printf("uud:%s\n", uud);
  

//     return 0;
// }
    