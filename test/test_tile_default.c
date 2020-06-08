#ifndef TILE_H
#define TILE_H
#include <tile.h>
#endif

#ifndef TILE_DEFAULTH
#define TILE_DEFAULT_H
#include <tile_default.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

bool hedge_set_reflects_requirements(void){
    const tile_set_t* set = TILE_SET_HEDGE;
    if( strcmp(set->empty,      " ") ||
        strcmp(set->before,     "" ) ||
        strcmp(set->after,      "" ) ||
        strcmp(set->start,      "<") ||
        strcmp(set->end,        ">") ||
        strcmp(set->h_wall,     "#") ||
        strcmp(set->v_wall,     "#") ||
        
        strcmp(set->corner[0],  "#") ||
        strcmp(set->corner[1],  "#") ||
        strcmp(set->corner[2],  "#") ||
        strcmp(set->corner[3],  "#") ||
        strcmp(set->corner[4],  "#") ||
        strcmp(set->corner[5],  "#") ||
        strcmp(set->corner[6],  "#") ||
        strcmp(set->corner[7],  "#") ||
        strcmp(set->corner[8],  "#") ||
        strcmp(set->corner[9],  "#") ||
        strcmp(set->corner[10], "#") ||
        strcmp(set->corner[11], "#") ||
        strcmp(set->corner[12], "#") ||
        strcmp(set->corner[13], "#") ||
        strcmp(set->corner[14], "#") ||
        strcmp(set->corner[15], "#")
        ){
        return false;
    }
    return true;
}


bool dungen_set_reflects_requirements(void){
    const tile_set_t* set = TILE_SET_DUNGEN;
    if( strcmp(set->empty,      " ") ||
        strcmp(set->before,     "" ) ||
        strcmp(set->after,      "" ) ||
        strcmp(set->start,      "<") ||
        strcmp(set->end,        ">") ||
        strcmp(set->h_wall,     "-") ||
        strcmp(set->v_wall,     "|") ||
        
        strcmp(set->corner[0],  "-") ||
        strcmp(set->corner[1],  "-") ||
        strcmp(set->corner[2],  "-") ||
        strcmp(set->corner[3],  "-") ||
        strcmp(set->corner[4],  "-") ||
        strcmp(set->corner[5],  "-") ||
        strcmp(set->corner[6],  "-") ||
        strcmp(set->corner[7],  "-") ||
        strcmp(set->corner[8],  "-") ||
        strcmp(set->corner[9],  "-") ||
        strcmp(set->corner[10], "-") ||
        strcmp(set->corner[11], "-") ||
        strcmp(set->corner[12], "-") ||
        strcmp(set->corner[13], "-") ||
        strcmp(set->corner[14], "-") ||
        strcmp(set->corner[15], "-")
        ){
        return false;
    }
    return true;
}

bool vt100_set_reflects_requirements(void){
    const tile_set_t* set = TILE_SET_VT100;
    if( strcmp(set->empty,      "_") ||
        strcmp(set->before,     "\x1b(0" ) ||
        strcmp(set->after,      "\x1b(B" ) ||
        strcmp(set->start,      "<") ||
        strcmp(set->end,        ">") ||
        strcmp(set->h_wall,     "x") ||
        strcmp(set->v_wall,     "q") ||
        
        strcmp(set->corner[0],  "_") ||
        strcmp(set->corner[1],  "x") ||
        strcmp(set->corner[2],  "q") ||
        strcmp(set->corner[3],  "j") ||
        strcmp(set->corner[4],  "x") ||
        strcmp(set->corner[5],  "x") ||
        strcmp(set->corner[6],  "k") ||
        strcmp(set->corner[7],  "u") ||
        strcmp(set->corner[8],  "q") ||
        strcmp(set->corner[9],  "m") ||
        strcmp(set->corner[10], "q") ||
        strcmp(set->corner[11], "v") ||
        strcmp(set->corner[12], "l") ||
        strcmp(set->corner[13], "t") ||
        strcmp(set->corner[14], "w") ||
        strcmp(set->corner[15], "n")
        ){
        return false;
    }
    return true;
}

/* Takes the name of a function that is passed no arguments, and prints if that function returns true and it's name*/
#define test(f) printf("[%s] " #f "\n", (f())?("\033[0;32mPassed\033[0m"):("\033[0;31mFailed\033[0m"))

int main(){
    
    test(hedge_set_reflects_requirements);
    test(dungen_set_reflects_requirements);
    test(vt100_set_reflects_requirements);
    return 0;
}

#undef test
