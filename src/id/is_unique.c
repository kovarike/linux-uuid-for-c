#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/uuid.h"

// Função para verificar se um UUID é único
int is_unique_uuid(UuidHashTable *table, const char *uuid) {
    unsigned int index = hash(uuid, table->size);
    UuidNode *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->uuid, uuid) == 0) {
            return 0;  // UUID duplicado
        }
        current = current->next;
    }
    return 1;  // UUID é único
}