#ifndef UUID_H
#define UUID_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <fcntl.h>
#include <errno.h>
#include <wincrypt.h>




#define SIZE_ID 37
#define INITIAL_SIZE 17  // Tamanho inicial da tabela de hash
#define LOAD_FACTOR 0.75  // Fator de carga
#define LOG_FILE "uuid_log.txt"

// Estrutura para armazenar UUIDs em nós da lista encadeada
typedef struct UuidNode {
    char uuid[SIZE_ID];
    struct UuidNode *next;
} UuidNode;

// Estrutura para a tabela de hash
typedef struct {
    UuidNode **buckets;  // Vetor de ponteiros para os buckets
    int size;            // Tamanho atual da tabela
    int count;           // Número de elementos na tabela
} UuidHashTable;

extern UuidHashTable *uuid_table; 


typedef struct {
    char uuid[SIZE_ID];
} Uuid;


extern Uuid* id;  


// Função de logging
void log_message(const char *message);

// Função de hash simples baseada na soma dos caracteres
unsigned int hash(const char *uuid, int table_size);

// Inicializa a tabela de hash
UuidHashTable *init_uuid_table(int size);

// Função para liberar memória da lista encadeada
void free_uuid_nodes(UuidNode *node);

// Função para destruir a tabela de hash
void destroy_uuid_table(UuidHashTable *table);

// Função para redimensionar a tabela de hash
void resize_table(UuidHashTable *table);

// Função para adicionar UUID à tabela de hash
void add_uuid(UuidHashTable *table, const char *uuid);
// Função para verificar se um UUID é único
int is_unique_uuid(UuidHashTable *table, const char *uuid);

void parse(char *out, Uuid *id);

void generate_random_bytes(unsigned char *buffer, size_t size);

void guuid(Uuid *uuid);

Uuid* create_uuid(); 




#endif // UUID_H