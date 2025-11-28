// Simple hash table implemented in C.

#ifndef _HT_H
#define _HT_H

#include <stdbool.h>
#include <stddef.h>

// Hash table structure: create with ht_create, free with ht_destroy.
typedef struct hashTable hashTable;

// Create hash table and return pointer to it, or NULL if out of memory.
hashTable* hT_criar(void);

// Free memory allocated for hash table, including allocated keys.
void hT_destruir(hashTable* tabela);

// Get item with given key (NUL-terminated) from hash table. Return
// value (which was set with ht_set), or NULL if key not found.
void* hT_get(hashTable* tabela, const char* nome);

// Set item with given key (NUL-terminated) to value (which must not
// be NULL). If not already present in table, key is copied to newly
// allocated memory (keys are freed automatically when ht_destroy is
// called). Return address of copied key, or NULL if out of memory.
const char* hT_set(hashTable* tabela, const char* nome, void* ID);

// Return number of items in hash table.
size_t hT_tamanho(hashTable* tabela);

// Hash table iterator: create with ht_iterator, iterate with ht_next.
typedef struct {
    const char* nome;  // current key
    void* ID;      // current value

    // Don't use these fields directly.
    hashTable* _tabela;       // reference to hash table being iterated
    size_t _index;    // current index into ht._entries
} hTiterator;

// Return new hash table iterator (for use with ht_next).
hTiterator hT_iterator(hashTable* tabela);

// Move iterator to next item in hash table, update iterator's key
// and value to current item, and return true. If there are no more
// items, return false. Don't call ht_set during iteration.
bool hT_proximo(hTi* iterator);

#endif // _HT_H
