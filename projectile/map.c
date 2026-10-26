#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"


size_t hashString(char *key){

    size_t hash =  14695981039346656037ULL; //FNV Offset 64bit

    for(char *p = key; *p != '\0'; p++){

        hash ^= (uint8_t)*p;
        hash *=  1099511628211ULL; //FNV Prime 64bit
    }

    return hash;
}

Entry* createEntry(char *key, double value){

    Entry *e =  malloc(sizeof(Entry));
    e->key = key;
    e->value = value;
    return e;
}

void freeMap(HashMap *map){

    


}

void mapInsert(Entry *e, HashMap *map){

    size_t hash = hashString(e->key);
    int index  = hash % map->capacity;

    if(map->buckets[index] == NULL){

        map->buckets[index] = e;
        map->count++;
    }
    else{

        e->next = map->buckets[index];
        map->buckets[index] = e;
        map->count++;
    }

    return;
}

double mapSearch(HashMap *map, char *key){

    int index = hashString(key) % map->capacity;

    struct Entry* current = map->buckets[index];

    while(current != NULL){

        if(strcmp(current->key, key) == 0){

            return current->value;
        }
        current = current->next;
    }
}




// int main(){

//     Entry *e1 = malloc(sizeof(Entry));
//     Entry *e2 = malloc(sizeof(Entry));
//     Entry *e3 = malloc(sizeof(Entry));
//     Entry *e4 = malloc(sizeof(Entry));
//     Entry *e5 = malloc(sizeof(Entry));

//     e1->key = "mach0"; e1->value = 0.25;
//     e2->key = "mach1"; e2->value = 1.0;
//     e3->key = "mach2"; e3->value = 0.45;
//     e4->key = "mach3"; e3->value = 0.55;
//     e5->key = "mach5"; e5->value = 1.2;

    
//     HashMap *map = malloc(sizeof(HashMap));
//     map->capacity = 5;
//     map->buckets = calloc(map->capacity, sizeof(Entry *));

//     mapInsert(e1, map);
//     mapInsert(e2, map);
//     mapInsert(e4, map);
//     mapInsert(e3, map);
//     mapInsert(e5, map);

//     printf("key: %s value: %f\n", e5->key, mapSearch(map, e5->key));
//     printf("key: %s value: %f\n", e3->key, mapSearch(map, e3->key));

//     free(e1);
//     free(e2);
//     free(e3);
//     free(e4);
//     free(e5);
//     free(map);
//     return 0;
// }
