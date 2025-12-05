// Simple hash table implemented in C.

#include "HashTable.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Hash table entry (slot may be filled or empty).
typedef struct {
    const char* chave;  // key is NULL if this slot is empty
    void* ID;
} hT_entrada;

// Hash table structure: create with ht_create, free with ht_destroy.
struct hashTable {
    hT_entrada* entradas;  // hash slots
    size_t capacidade;    // size of _entries array
    size_t tamanho;      // number of items in hash table
};

#define INITIAL_CAPACITY 16  // must not be zero

hashTable* hT_criar(void) {
    // Allocate space for hash table struct.
    hashTable* tabela = malloc(sizeof(hashTable));
    if (tabela == NULL) {
        return NULL;
    }
    tabela->tamanho = 0;
    tabela->capacidade = INITIAL_CAPACITY;

    // Allocate (zero'd) space for entry buckets.
    tabela->entradas = calloc(tabela->capacidade, sizeof(hT_entrada));
    if (tabela->entradas == NULL) {
        free(tabela); // error, free table before we return!
        return NULL;
    }
    return tabela;
}

void hT_destruir(hashTable* tabela) {
    // First free allocated keys.
    for (size_t i = 0; i < tabela->capacidade; i++) {
        free((void*)tabela->entradas[i].chave);
    }

    // Then free entries array and table itself.
    free(tabela->entradas);
    free(tabela);
}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function   
static uint64_t hash_chave(const char* chave) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = chave; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

void* hT_get(hashTable* tabela, const char* chave) {
    // AND hash with capacity-1 to ensure it's within entries array.
    uint64_t hash = hash_chave(chave);
    size_t index = (size_t)(hash & (uint64_t)(tabela->capacidade - 1));

    // Loop till we find an empty entry.
    while (tabela->entradas[index].chave != NULL) {
        if (strcmp(chave, tabela->entradas[index].chave) == 0) {
            // Found key, return value.
            return tabela->entradas[index].ID;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
        if (index >= tabela->capacidade) {
            // At end of entries array, wrap around.
            index = 0;
        }
    }
    return NULL;
}

// Internal function to set an entry (without expanding table).
static const char* hT_set_entrada(hT_entrada* entradas, size_t capacidade,
        const char* chave, void* ID, size_t* ptamanho) {
    // AND hash with capacity-1 to ensure it's within entries array.
    uint64_t hash = hash_chave(chave);
    size_t index = (size_t)(hash & (uint64_t)(capacidade - 1));

    // Loop till we find an empty entry.
    while (entradas[index].chave != NULL) {
        if (strcmp(chave, entradas[index].chave) == 0) {
            // Found key (it already exists), update value.
            entradas[index].ID = ID;
            return entradas[index].chave;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
        if (index >= capacidade) {
            // At end of entries array, wrap around.
            index = 0;
        }
    }

    // Didn't find key, allocate+copy if needed, then insert it.
    if (ptamanho != NULL) {
        chave = strdup(chave);
        if (chave == NULL) {
            return NULL;
        }
        (*ptamanho)++;
    }
    entradas[index].chave = (char*)chave;
    entradas[index].ID = ID;
    return chave;
}

// Expand hash table to twice its current size. Return true on success,
// false if out of memory.
static bool hT_expandir(hashTable* tabela) {
    // Allocate new entries array.
    size_t nova_capacidade = tabela->capacidade * 2;
    if (nova_capacidade < tabela->capacidade) {
        return false;  // overflow (capacity would be too big)
    }
    hT_entrada* novas_entradas = calloc(nova_capacidade, sizeof(hT_entrada));
    if (novas_entradas == NULL) {
        return false;
    }

    // Iterate entries, move all non-empty ones to new table's entries.
    for (size_t i = 0; i < tabela->capacidade; i++) {
        hT_entrada entrada = tabela->entradas[i];
        if (entrada.chave != NULL) {
            hT_set_entrada(novas_entradas, nova_capacidade, entrada.chave,
                         entrada.ID, NULL);
        }
    }

    // Free old entries array and update this table's details.
    free(tabela->entradas);
    tabela->entradas = novas_entradas;
    tabela->capacidade = nova_capacidade;
    return true;
}

const char* hT_set(hashTable* tabela, const char* chave, void* ID) {
    assert(ID != NULL);
    if (ID == NULL) {
        return NULL;
    }

    // If length will exceed half of current capacity, expand it.
    if (tabela->tamanho >= tabela->capacidade / 2) {
        if (!hT_expandir(tabela)) {
            return NULL;
        }
    }

    // Set entry and update length.
    return hT_set_entrada(tabela->entradas, tabela->capacidade, chave, ID,
                        &tabela->tamanho);
}

size_t hT_tamanho(hashTable* tabela) {
    return tabela->tamanho;
}

hTiterator hT_iterator(hashTable* tabela) {
    hTiterator iterator;
    iterator._tabela = tabela;
    iterator._index = 0;
    return iterator;
}

bool hT_proximo(hTiterator* iterator) {
    // Loop till we've hit end of entries array.
    hashTable* tabela = iterator->_tabela;
    while (iterator->_index < tabela->capacidade) {
        size_t i = iterator->_index;
        iterator->_index++;
        if (tabela->entradas[i].chave != NULL) {
            // Found next non-empty item, update iterator key and value.
            hT_entrada entrada = tabela->entradas[i];
            iterator->nome = entrada.chave;
            iterator->ID = entrada.ID;
            return true;
        }
    }
    return false;
}
