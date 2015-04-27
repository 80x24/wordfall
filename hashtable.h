#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct dict *Dict;

// new empty dictionary
Dict dict_create(void);

// destroy a dictionary
void dict_destroy(Dict);

// insert new key-value pair into existing dictionary
void dict_insert(Dict, const char *key, const char *value);

// return the most recently inserted value associated with a key
// or 0 if not matching key is present
const char *dict_search(Dict, const char *key);

// delete the most recently inserted record with the given key
// if there is not record, has no effect
void dict_delete(Dict, const char *key);

#endif
