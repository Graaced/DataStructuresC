#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define HASHMAP_SIZE 3
#define HASHMAP_SIZE_LIST 2

typedef struct ex_dict_item
{
    const char *key;
    size_t key_len;
    const char *value;
    size_t value_len;

}ex_dict_item;

typedef struct ex_dict
{
    ex_dict_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST]; 
    
}ex_dict;


size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}


void dict_insert(ex_dict *dict, const char *key, const char *value)
{

    const size_t key_len = strlen(key);
    const size_t value_len = strlen(value);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for(size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (dict->hashmap[index][i].key_len > 0 && dict->hashmap[index][i].key_len == key_len && !memcmp(dict->hashmap[index][i].key, key, key_len))
        {
            // THE KEY IS DUPLICATE 
            printf("DUPLICATE KEY %s (index: %llu, slot: %llu)\n", key, index, i);
            return;
        }
    }

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {     
        // ADD KEY
        if (dict->hashmap[index][i].key_len == 0)
        {
            dict->hashmap[index][i].key = key;
            dict->hashmap[index][i].key_len = key_len;
            dict->hashmap[index][i].value = value;
            dict->hashmap[index][i].value_len = value_len;

            printf("ADDED %s -> %s (index : %llu, slot: %llu)\n", key, value, index, i);
            return;
        }
    }

    printf("Collision! for %s (index%llu)\n",key, index);
}

const char *dict_find(ex_dict *dict, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (dict->hashmap[index][i].key_len > 0)
        {
            if (dict->hashmap[index][i].key_len == key_len &&
                !memcmp(dict->hashmap[index][i].key, key, key_len))
            {
                printf("FOUND %s -> %s at index: %llu slot: %llu\n", key, dict->hashmap[index][i].value, index, i);
                return dict->hashmap[index][i].value;
            }
        }
    }

    printf("%s Not Founded On Dictionary\n", key);
    return NULL;
}

void dict_remove(ex_dict *dict, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (dict->hashmap[index][i].key_len > 0)
        {
            if (dict->hashmap[index][i].key_len == key_len &&
                !memcmp(dict->hashmap[index][i].key, key, key_len))
            {
                printf("REMOVED %s at index: %llu slot: %llu\n", key, index, i);
                dict->hashmap[index][i].key = NULL;
                dict->hashmap[index][i].key_len = 0;
                dict->hashmap[index][i].value = NULL;
                dict->hashmap[index][i].value_len = 0;
                return;
            }
        }
    }
}


int main(int argc, char **argv)
{
    ex_dict mydict;

    memset(&mydict, 0, sizeof(ex_dict)); // to quickly clear the memory
    
    // INSERT KEY
    dict_insert(&mydict, "hello", "mondo");
    dict_insert(&mydict, "Bye", "arrivederci");
    dict_insert(&mydict, "test", "prova");
    dict_insert(&mydict, "NO", "non puoi");
    dict_insert(&mydict, "SI", "puoi");


    // FIND KEY  
    const char *result = dict_find(&mydict, "test");
    if (result)
    {
        printf("Value for 'test': %s\n", result);
    }


    //  FIND NON EXISTENT KEY
    result = dict_find(&mydict, "NotkeyFound");
    if (result)
    {
        printf("Value for 'NotkeyFound': %s\n", result);
    }


   // REMOVE KEY
    dict_find(&mydict, "Bye");
    dict_remove(&mydict, "Bye");
    result = dict_find(&mydict, "Bye");
    if (result)
    {
        printf("Value for 'Bye': %s\n", result);
    }
    else
    {
        printf("'Bye' Not Founded On Dictionary\n");
    }

    // UNIQUE KEYS
    dict_insert(&mydict, "hello", "dog");
    dict_insert(&mydict, "dog", "bark");
   
   return 0;
}