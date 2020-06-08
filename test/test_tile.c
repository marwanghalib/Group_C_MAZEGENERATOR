#ifndef TILE_H
#define TILE_H
#include <tile.h>
#endif

#ifndef MAZE_H
#define MAZE_H
#include <maze.h>
#endif

#ifndef SDTBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

/*
  
typedef struct tile_set{
    char *empty;
    char *before;
    char *after;
    char *start;
    char *end;
    char *h_wall;
    char *v_wall;
    char *corner[16];
} tile_set_t;

 */
void print_tile_set(const tile_set_t* set){
     printf("empty    \"%s\"\n"
            "before   \"%s\"\n"
            "after    \"%s\"\n"
            "start    \"%s\"\n"
            "end      \"%s\"\n"
            "h_wall   \"%s\"\n"
            "v_wall   \"%s\"\n"
            "corner_0 \"%s\"\n"
            "corner_1 \"%s\"\n"
            "corner_2 \"%s\"\n"
            "corner_3 \"%s\"\n"
            "corner_4 \"%s\"\n"
            "corner_5 \"%s\"\n"
            "corner_6 \"%s\"\n"
            "corner_7 \"%s\"\n"
            "corner_8 \"%s\"\n"
            "corner_9 \"%s\"\n"
            "corner_A \"%s\"\n"
            "corner_B \"%s\"\n"
            "corner_C \"%s\"\n"
            "corner_D \"%s\"\n"
            "corner_E \"%s\"\n"
            "corner_F \"%s\"\n", 
        set->empty,     
        set->before,    
        set->after,     
        set->start,     
        set->end,       
        set->h_wall,    
        set->v_wall,    
        set->corner[0], 
        set->corner[1], 
        set->corner[2], 
        set->corner[3], 
        set->corner[4], 
        set->corner[5], 
        set->corner[6], 
        set->corner[7], 
        set->corner[8], 
        set->corner[9], 
        set->corner[10],
        set->corner[11],
        set->corner[12],
        set->corner[13],
        set->corner[14],
        set->corner[15]);
}

void crash_print(tile_set_t* set){
    char* s = set->empty;
    for(int i = 0; i < 40; i++){
        printf("%d, %c \n", s[i], s[i]);
    }
}

bool new_tile_set_creates_a_tile_set_with_the_correct_defaults(void){
    tile_set_t* set = new_tile_set("#");
    
    /*strcmp returns 0 if they are equal, 
      if any of these ar unequal it fails*/
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
        delete_tile_set(set);
        return false;
    }
    delete_tile_set(set);
    return true;
}

bool new_tile_set_plus_creates_a_tile_set_with_the_correct_defaults_and_respects_the_3_arguments(void){
    tile_set_t* set = new_tile_set_plus("-", "|", "+");
    
    /*strcmp returns 0 if they are equal, 
      if any of these ar unequal it fails*/
    if( strcmp(set->empty,      " ") ||
        strcmp(set->before,     "" ) ||
        strcmp(set->after,      "" ) ||
        strcmp(set->start,      "<") ||
        strcmp(set->end,        ">") ||
        strcmp(set->h_wall,     "-") ||
        strcmp(set->v_wall,     "|") ||
        
        strcmp(set->corner[0],  "+") ||
        strcmp(set->corner[1],  "+") ||
        strcmp(set->corner[2],  "+") ||
        strcmp(set->corner[3],  "+") ||
        strcmp(set->corner[4],  "+") ||
        strcmp(set->corner[5],  "+") ||
        strcmp(set->corner[6],  "+") ||
        strcmp(set->corner[7],  "+") ||
        strcmp(set->corner[8],  "+") ||
        strcmp(set->corner[9],  "+") ||
        strcmp(set->corner[10], "+") ||
        strcmp(set->corner[11], "+") ||
        strcmp(set->corner[12], "+") ||
        strcmp(set->corner[13], "+") ||
        strcmp(set->corner[14], "+") ||
        strcmp(set->corner[15], "+")
        ){
        delete_tile_set(set);
        return false;
    }
    delete_tile_set(set);
    return true;
}


bool new_tile_set_full_corners_creates_a_tile_set_with_the_correct_defaults_and_respects_the_arguments(void){
    char *corners[16];
    corners[0] = "0";
    corners[1] = "1";
    corners[2] = "2";
    corners[3] = "3";
    corners[4] = "4";
    corners[5] = "5";
    corners[6] = "6";
    corners[7] = "7";
    corners[8] = "8";
    corners[9] = "9";
    corners[10]= "A";
    corners[11]= "B";
    corners[12]= "C";
    corners[13]= "D";
    corners[14]= "E";
    corners[15]= "F";
    tile_set_t* set = new_tile_set_full_corners("-", "|", corners);
        
    /*strcmp returns 0 if they are equal, 
      if any of these ar unequal it fails*/
    if( strcmp(set->empty,      " ") ||
        strcmp(set->before,     "" ) ||
        strcmp(set->after,      "" ) ||
        strcmp(set->start,      "<") ||
        strcmp(set->end,        ">") ||
        strcmp(set->h_wall,     "-") ||
        strcmp(set->v_wall,     "|") ||
        
        strcmp(set->corner[0],  "0") ||
        strcmp(set->corner[1],  "1") ||
        strcmp(set->corner[2],  "2") ||
        strcmp(set->corner[3],  "3") ||
        strcmp(set->corner[4],  "4") ||
        strcmp(set->corner[5],  "5") ||
        strcmp(set->corner[6],  "6") ||
        strcmp(set->corner[7],  "7") ||
        strcmp(set->corner[8],  "8") ||
        strcmp(set->corner[9],  "9") ||
        strcmp(set->corner[10], "A") ||
        strcmp(set->corner[11], "B") ||
        strcmp(set->corner[12], "C") ||
        strcmp(set->corner[13], "D") ||
        strcmp(set->corner[14], "E") ||
        strcmp(set->corner[15], "F")
        ){
        delete_tile_set(set);
        return false;
    }
    delete_tile_set(set);
    return true;
}



bool new_tile_set_no_defaults_creates_a_tile_set_that_respects_the_arguments(void){
    char *corners[16];
    corners[0] = "0";
    corners[1] = "1";
    corners[2] = "2";
    corners[3] = "3";
    corners[4] = "4";
    corners[5] = "5";
    corners[6] = "6";
    corners[7] = "7";
    corners[8] = "8";
    corners[9] = "9";
    corners[10]= "A";
    corners[11]= "B";
    corners[12]= "C";
    corners[13]= "D";
    corners[14]= "E";
    corners[15]= "F";
    tile_set_t* set = new_tile_set_no_defaults("_", "s", "e", "h", "v", "b", "a", corners);
    
    //crash_print(set);
    //puts("now a clean one");
    //print_tile_set(set);
    
    /*strcmp returns 0 if they are equal, 
      if any of these ar unequal it fails*/
    if( strcmp(set->empty,      "_") ||
        strcmp(set->before,     "b") ||
        strcmp(set->after,      "a") ||
        strcmp(set->start,      "s") ||
        strcmp(set->end,        "e") ||
        strcmp(set->h_wall,     "h") ||
        strcmp(set->v_wall,     "v") ||
        
        strcmp(set->corner[0],  "0") ||
        strcmp(set->corner[1],  "1") ||
        strcmp(set->corner[2],  "2") ||
        strcmp(set->corner[3],  "3") ||
        strcmp(set->corner[4],  "4") ||
        strcmp(set->corner[5],  "5") ||
        strcmp(set->corner[6],  "6") ||
        strcmp(set->corner[7],  "7") ||
        strcmp(set->corner[8],  "8") ||
        strcmp(set->corner[9],  "9") ||
        strcmp(set->corner[10], "A") ||
        strcmp(set->corner[11], "B") ||
        strcmp(set->corner[12], "C") ||
        strcmp(set->corner[13], "D") ||
        strcmp(set->corner[14], "E") ||
        strcmp(set->corner[15], "F")
        ){
        delete_tile_set(set);
        return false;
    }
    delete_tile_set(set);
    return true;
}


bool new_tile_set_supports_a_multy_byte_string(void){
    tile_set_t* set = new_tile_set("#+");
    
    /*strcmp returns 0 if they are equal, 
      if any of these ar unequal it fails*/
    if( strcmp(set->empty,      " ") ||
        strcmp(set->before,     "" ) ||
        strcmp(set->after,      "" ) ||
        strcmp(set->start,      "<") ||
        strcmp(set->end,        ">") ||
        strcmp(set->h_wall,     "#+") ||
        strcmp(set->v_wall,     "#+") ||
        
        strcmp(set->corner[0],  "#+") ||
        strcmp(set->corner[1],  "#+") ||
        strcmp(set->corner[2],  "#+") ||
        strcmp(set->corner[3],  "#+") ||
        strcmp(set->corner[4],  "#+") ||
        strcmp(set->corner[5],  "#+") ||
        strcmp(set->corner[6],  "#+") ||
        strcmp(set->corner[7],  "#+") ||
        strcmp(set->corner[8],  "#+") ||
        strcmp(set->corner[9],  "#+") ||
        strcmp(set->corner[10], "#+") ||
        strcmp(set->corner[11], "#+") ||
        strcmp(set->corner[12], "#+") ||
        strcmp(set->corner[13], "#+") ||
        strcmp(set->corner[14], "#+") ||
        strcmp(set->corner[15], "#+")
        ){
        delete_tile_set(set);
        return false;
    }
    delete_tile_set(set);
    return true;
}

bool new_tile_set_plus_supports_multy_byte_characters(void){
    tile_set_t* set = new_tile_set_plus("---", "[]", "{++}");
    
    /*strcmp returns 0 if they are equal, 
      if any of these ar unequal it fails*/
    if( strcmp(set->empty,      " ") ||
        strcmp(set->before,     "" ) ||
        strcmp(set->after,      "" ) ||
        strcmp(set->start,      "<") ||
        strcmp(set->end,        ">") ||
        strcmp(set->h_wall,     "---") ||
        strcmp(set->v_wall,     "[]") ||
        
        strcmp(set->corner[0],  "{++}") ||
        strcmp(set->corner[1],  "{++}") ||
        strcmp(set->corner[2],  "{++}") ||
        strcmp(set->corner[3],  "{++}") ||
        strcmp(set->corner[4],  "{++}") ||
        strcmp(set->corner[5],  "{++}") ||
        strcmp(set->corner[6],  "{++}") ||
        strcmp(set->corner[7],  "{++}") ||
        strcmp(set->corner[8],  "{++}") ||
        strcmp(set->corner[9],  "{++}") ||
        strcmp(set->corner[10], "{++}") ||
        strcmp(set->corner[11], "{++}") ||
        strcmp(set->corner[12], "{++}") ||
        strcmp(set->corner[13], "{++}") ||
        strcmp(set->corner[14], "{++}") ||
        strcmp(set->corner[15], "{++}")
        ){
        delete_tile_set(set);
        return false;
    }
    delete_tile_set(set);
    return true;
}


bool new_tile_set_full_corners_supports_multy_byte_characters(void){
    char *corners[16];
    corners[0] = "x0";
    corners[1] = "x1";
    corners[2] = "x2";
    corners[3] = "x3";
    corners[4] = "x4";
    corners[5] = "x5";
    corners[6] = "x6";
    corners[7] = "x7";
    corners[8] = "x8";
    corners[9] = "x9";
    corners[10]= "xA";
    corners[11]= "xB";
    corners[12]= "xC";
    corners[13]= "xD";
    corners[14]= "xE";
    corners[15]= "xF";
    tile_set_t* set = new_tile_set_full_corners("--", "||", corners);
        
    /*strcmp returns 0 if they are equal, 
      if any of these ar unequal it fails*/
    if( strcmp(set->empty,      " ") ||
        strcmp(set->before,     "" ) ||
        strcmp(set->after,      "" ) ||
        strcmp(set->start,      "<") ||
        strcmp(set->end,        ">") ||
        strcmp(set->h_wall,     "--") ||
        strcmp(set->v_wall,     "||") ||
        
        strcmp(set->corner[0],  "x0") ||
        strcmp(set->corner[1],  "x1") ||
        strcmp(set->corner[2],  "x2") ||
        strcmp(set->corner[3],  "x3") ||
        strcmp(set->corner[4],  "x4") ||
        strcmp(set->corner[5],  "x5") ||
        strcmp(set->corner[6],  "x6") ||
        strcmp(set->corner[7],  "x7") ||
        strcmp(set->corner[8],  "x8") ||
        strcmp(set->corner[9],  "x9") ||
        strcmp(set->corner[10], "xA") ||
        strcmp(set->corner[11], "xB") ||
        strcmp(set->corner[12], "xC") ||
        strcmp(set->corner[13], "xD") ||
        strcmp(set->corner[14], "xE") ||
        strcmp(set->corner[15], "xF")
        ){
        delete_tile_set(set);
        return false;
    }
    delete_tile_set(set);
    return true;
}



bool new_tile_set_no_defaults_supports_multy_byte_characters(){
    char *corners[16];
    corners[0] = "x0x";
    corners[1] = "x1x";
    corners[2] = "x2x";
    corners[3] = "x3x";
    corners[4] = "x4x";
    corners[5] = "x5x";
    corners[6] = "x6x";
    corners[7] = "x7x";
    corners[8] = "x8x";
    corners[9] = "x9x";
    corners[10]= "xAx";
    corners[11]= "xBx";
    corners[12]= "xCx";
    corners[13]= "xDx";
    corners[14]= "xEx";
    corners[15]= "xFx";
    tile_set_t* set = new_tile_set_no_defaults("___", "[s]", "[e]", "[-]", "{|}", "maze below:\n", "maze above\n", corners);
    
    //crash_print(set);
    //puts("now a clean one");
    //print_tile_set(set);
    
    /*strcmp returns 0 if they are equal, 
      if any of these ar unequal it fails*/
    if( strcmp(set->empty,      "___") ||
        strcmp(set->before,     "maze below:\n") ||
        strcmp(set->after,      "maze above\n") ||
        strcmp(set->start,      "[s]") ||
        strcmp(set->end,        "[e]") ||
        strcmp(set->h_wall,     "[-]") ||
        strcmp(set->v_wall,     "{|}") ||
        
        strcmp(set->corner[0],  "x0x") ||
        strcmp(set->corner[1],  "x1x") ||
        strcmp(set->corner[2],  "x2x") ||
        strcmp(set->corner[3],  "x3x") ||
        strcmp(set->corner[4],  "x4x") ||
        strcmp(set->corner[5],  "x5x") ||
        strcmp(set->corner[6],  "x6x") ||
        strcmp(set->corner[7],  "x7x") ||
        strcmp(set->corner[8],  "x8x") ||
        strcmp(set->corner[9],  "x9x") ||
        strcmp(set->corner[10], "xAx") ||
        strcmp(set->corner[11], "xBx") ||
        strcmp(set->corner[12], "xCx") ||
        strcmp(set->corner[13], "xDx") ||
        strcmp(set->corner[14], "xEx") ||
        strcmp(set->corner[15], "xFx")
        ){
        delete_tile_set(set);
        return false;
    }
    delete_tile_set(set);
    return true;
}

/* Takes the name of a function that is passed no arguments, and prints if that function returns true and it's name*/
#define test(f) printf("[%s] " #f "\n", (f())?("\033[0;32mPassed\033[0m"):("\033[0;31mFailed\033[0m"))

int main(){
    
    test(new_tile_set_creates_a_tile_set_with_the_correct_defaults);
    test(new_tile_set_plus_creates_a_tile_set_with_the_correct_defaults_and_respects_the_3_arguments);
    test(new_tile_set_full_corners_creates_a_tile_set_with_the_correct_defaults_and_respects_the_arguments);
    test(new_tile_set_no_defaults_creates_a_tile_set_that_respects_the_arguments);
    test(new_tile_set_supports_a_multy_byte_string);
    test(new_tile_set_plus_supports_multy_byte_characters);
    test(new_tile_set_full_corners_supports_multy_byte_characters);
    test(new_tile_set_no_defaults_supports_multy_byte_characters);
    return 0;
}

#undef test
