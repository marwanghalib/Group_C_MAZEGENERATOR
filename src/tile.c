
/*
typedef struct tile_set{
    char *empty;
    char *start;
    char *end;
    char *h_wall;
    char *v_wall;
    char *corner[16];
} tile_set_t;
*/

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef TILE_H
#define TILE_H
#include <tile.h>
#endif

#ifndef MAZE_H
#define MAZE_H
#include <maze.h>
#endif

int delete_tile_set(tile_set_t* set){
    if(set){
        if(set->empty){
            free(set->empty);
        }
        free(set);
    }
    return 0;
}

tile_set_t* new_tile_set(char* wall){
    char default_string[] = {' ', '\0', '<', '\0', '>', '\0'};
    tile_set_t* set = calloc(1, sizeof(tile_set_t));
    if(!set){
        return NULL;
    }
    set->empty = calloc(sizeof(default_string)+strlen(wall)+1, sizeof(char));
    if(!set->empty){
        free(set);
        return NULL;
    }
    memcpy(set->empty, default_string, sizeof(default_string));
    strcpy(set->empty+sizeof(default_string), wall);
    set->before = set->empty+1;
    set->after  = set->empty+1;
    set->start  = set->empty+2;
    set->end    = set->empty+4;
    set->h_wall = set->empty+6;
    set->v_wall = set->empty+6;
    
    set->corner[0] = set->empty;
    for(int i = 1; i < 16; i++){
        set->corner[i] = set->empty+6;
    }
    return set;
}


tile_set_t* new_tile_set_plus(char* h_wall, char* v_wall, char* corner){
    char default_string[] = {' ', '\0', '<', '\0', '>', '\0'};
    tile_set_t* set = calloc(1, sizeof(tile_set_t));
    if(!set){
        return NULL;
    }
    size_t arr_len = sizeof(default_string);
    arr_len += strlen(h_wall)+1;
    arr_len += strlen(v_wall)+1;
    arr_len += strlen(corner)+1;

    set->empty = calloc(arr_len, sizeof(char));
    if(!set->empty){
        free(set);
        return NULL;
    }
    memcpy(set->empty, default_string, sizeof(default_string));
    set->before = set->empty+1;
    set->after  = set->empty+1;
    set->start  = set->empty+2;
    set->end    = set->empty+4;

    size_t i = 6;

    strcpy(set->empty+i, h_wall);
    set->h_wall = set->empty+i;
    i += strlen(h_wall)+1;

    strcpy(set->empty+i, v_wall);
    set->v_wall = set->empty+i;
    i += strlen(v_wall)+1;

    set->corner[0] = set->empty;
    strcpy(set->empty+i, corner);
    for(int n = 1; n < 16; n++){
        set->corner[n] = set->empty+i;
    }
    return set;
}

tile_set_t* new_tile_set_full_corners(char* h_wall, char* v_wall, char *corners[16]){
    char default_string[] = {' ', '\0', '<', '\0', '>', '\0'};
    tile_set_t* set = calloc(1, sizeof(tile_set_t));
    if(!set){
        return NULL;
    }
    size_t arr_len = sizeof(default_string);
    arr_len += strlen(h_wall)+1;
    arr_len += strlen(v_wall)+1;
    for(int c = 0; c<16; c++){
        arr_len += strlen(corners[c])+1;
    }

    set->empty = calloc(arr_len, sizeof(char));
    if(!set->empty){
        free(set);
        return NULL;
    }
    memcpy(set->empty, default_string, sizeof(default_string));
    set->before = set->empty+1;
    set->after  = set->empty+1;
    set->start  = set->empty+2;
    set->end    = set->empty+4;

    size_t i = 6;

    strcpy(set->empty+i, h_wall);
    set->h_wall = set->empty+i;
    i += strlen(h_wall)+1;

    strcpy(set->empty+i, v_wall);
    set->v_wall = set->empty+i;
    i += strlen(v_wall)+1;

    for(int c = 0; c < 16; c++){
        strcpy(set->empty+i, corners[c]);
        set->corner[c] = set->empty+i;
        i += strlen(corners[c])+1;
    }
    return set;
}

tile_set_t* new_tile_set_no_defaults(
        char* empty,
        char* start,
        char* end,
        char* h_wall,
        char* v_wall,
        char* before,
        char* after,
        char *corners[16]){
    tile_set_t* set = calloc(1, sizeof(tile_set_t));
    if(!set){
        return NULL;
    }
    size_t arr_len = 0;
    arr_len += strlen(empty)+1;
    arr_len += strlen(before)+1;
    arr_len += strlen(after)+1;
    arr_len += strlen(start)+1;
    arr_len += strlen(end)+1;
    arr_len += strlen(h_wall)+1;
    arr_len += strlen(v_wall)+1;
    for(int c = 0; c<16; c++){
        arr_len += strlen(corners[c])+1;
    }

    size_t i = 0;
    set->empty = calloc(arr_len, sizeof(char));
    if(!set->empty){
        free(set);
        return NULL;
    }

    strcpy(set->empty, empty);
    i += strlen(empty)+1;

    set->before = set->empty+i;
    strcpy(set->before, before);
    i += strlen(before)+1;

    set->after = set->empty+i;
    strcpy(set->after, after);
    i += strlen(after)+1;

    set->start = set->empty+i;
    strcpy(set->start, start);
    i += strlen(start)+1;

    set->end = set->empty+i;
    strcpy(set->end, end);
    i += strlen(end)+1;

    set->h_wall = set->empty+i;
    strcpy(set->h_wall, h_wall);
    i += strlen(h_wall)+1;

    set->v_wall = set->empty+i;
    strcpy(set->v_wall, v_wall);
    i += strlen(v_wall)+1;

    for(int c = 0; c < 16; c++){
        set->corner[c] = set->empty+i;
        strcpy(set->corner[c], corners[c]);
        i += strlen(corners[c])+1;
    }
    return set;
}

char* get_corner(const tile_set_t* set, cell_t cell){
    uint8_t c = cell.cross_north     |
                cell.cross_west  <<1 |
                cell.west        <<2 |
                cell.north       <<3;
    return set->corner[c];
}




