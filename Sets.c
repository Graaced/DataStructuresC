#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define HASHMAP_SIZE 3
#define HASHMAP_SIZE_LIST 2

typedef struct ex_set_item
{
    const char *key;
    size_t key_len;
    
}ex_set_item;

typedef struct ex_set
{
    ex_set_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST]; // how many nodes do I pre-allocate // 3 = the hashmap is made by 3 of ex_set_node
    
}ex_set;


size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}


void set_insert(ex_set *set, const char *key)
{

    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for(size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0 && set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
        {
            // THE KEY IS DUPLICATE 
            printf("DUPLICATE KEY %s (index: %llu, slot: %llu)\n", key, index, i);
            return;
        }
    }

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {     
        // ADD KEY
        if (set->hashmap[index][i].key_len == 0)
        {
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;

            printf("ADDED %s (index: %llu, slot: %llu)\n", key, index, i);
            return;
        }
    }

    printf("Collision! for %s (index%llu)\n",key, index);
}

void set_find(ex_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for(size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            
            if(set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                printf("FOUND %s at index %llu slot %llu\n", key, index, i);
                return;
            }
            
        }
    }
}

void set_search(ex_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                printf("FOUND %s at index %llu slot %llu\n", key, index, i);
                return;
            }
        }
    }

    printf("%s not found in the set\n", key);
}

void set_remove(ex_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                printf("REMOVING %s from index %llu slot %llu\n", key, index, i);
                set->hashmap[index][i].key = NULL;
                set->hashmap[index][i].key_len = 0;
                return;
            }
        }
    }
}


int main(int argc, char **argv)
{
    //INIT
    ex_set myset;

    memset(&myset, 0, sizeof(ex_set)); // to quickly clear the memory
    
    // INSERT KEY
    set_insert(&myset, "hello");
    set_insert(&myset, "Bye");
    set_insert(&myset, "test");
    set_insert(&myset, "NO");
    set_insert(&myset, "SI");

    // FIND KEY
    set_find(&myset, "test");

    // SEARCH KEY
    set_search(&myset, "NO");
    set_search(&myset, "NotFoundKey");

    // REMOVE KEY
    set_find(&myset,"Bye");
    set_remove(&myset, "Bye");
    set_search(&myset, "Bye");

    // UNIQUE KEYS
    set_insert(&myset, "hello");
    set_insert(&myset, "dog");
    return 0;
}
