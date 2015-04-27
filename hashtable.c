/*
This file is part of Word Fall.

Word Fall is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Word Fall is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Word Fall.  If not, see <http://www.gnu.org/licenses/>.
*/

// Hash table implementation based off of code found here. Used with permission.
// http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#hashTables

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hashtable.h"

struct elt {
	struct elt *next;
	char *key;
	char *value;
};

struct dict {
	int size; // size of the pointer table
	int n; // number of elements stored
	struct elt **table;
};

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)
#define MULTIPLIER (97)

Dict internal_dict_create(int size)
{
	Dict d;
	d = malloc(sizeof(*d));
	assert(d != 0);

	d->size = size;
	d->n = 0;
	d->table = malloc(sizeof(struct elt *) * d->size);

	assert(d->table != 0);

	for(int i = 0; i < d->size; i++) {
		d->table[i] = 0;
	}

	return d;
}

Dict dict_create(void)
{
	return internal_dict_create(INITIAL_SIZE);
}

void dict_destroy(Dict d)
{
	struct elt *e;
	struct elt *next;

	for(int i = 0; i < d->size; i++) {
		for(e = d->table[i]; e != 0; e = next) {
			next = e->next;
			free(e->key);
			free(e->value);
			free(e);
		}
	}

	free(d->table);
	free(d);
}

static unsigned long hash_function(const char *s)
{
	unsigned const char *us;
	unsigned long h;

	h = 0;

	for(us = (unsigned const char *) s; *us; us++) {
		h = h * MULTIPLIER + *us;
	}

	return h;
}

static void grow(Dict d)
{
	Dict d2; // new dictionary created
	struct dict swap; // temp structure for transplant
	struct elt *e;

	d2 = internal_dict_create(d->size * GROWTH_FACTOR);

	for(int i = 0; i < d->size; i++) {
		for(e = d->table[i]; e != 0; e = e->next) {
			// note: this recopies everything
			// a more efficient implementation would patch out the strdups
			// inside dict_insert to avoid this problem.
			dict_insert(d2, e->key, e->value);
		}
	}

	// hideous
	// swap guts of d and d2
	// call dict_destroy on d2
	swap = *d;
	*d = *d2;
	*d2 = swap;

	dict_destroy(d2);
}

// insert a new key-value pair into an existing dictionary
void dict_insert(Dict d, const char *key, const char *value)
{
	struct elt *e;
	unsigned long h;

	assert(key);
	assert(value);

	e = malloc(sizeof(*e));

	assert(e);

	e->key = strdup(key);
	e->value = strdup(value);

	h = hash_function(key) % d->size;

	e->next = d->table[h];
	d->table[h] = e;

	d->n++;

	// grow table if there is not enough room
	if(d->n >= d->size * MAX_LOAD_FACTOR) {
		grow(d);
	}
}

// return the most recently inserted value associated with a key 
// or 0 if not matching key is present
const char * dict_search(Dict d, const char *key)
{
	struct elt *e;

	for(e = d->table[hash_function(key) % d->size]; e != 0; e = e->next) {
		if(!strcmp(e->key, key)) {
			// got it
			return e->value;
		}
	}

	return 0;
}

// delete the most recently inserted record with the given key
// if there is no such record, this has no effect
void dict_delete(Dict d, const char *key) {
	// what to change when elt is destroyed
	struct elt **prev;
	// what to delete
	struct elt *e;

	for(prev = &(d->table[hash_function(key) % d->size]); *prev != 0; prev = &((*prev)->next)) {
		if(!strcmp((*prev)->key, key)) {
			// got em
			e = *prev;
			*prev = e->next;

			free(e->key);
			free(e->value);
			free(e);

			return;
		}
	}
}
