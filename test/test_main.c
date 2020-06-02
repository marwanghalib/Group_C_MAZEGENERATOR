#ifndef STDIO_H
#define STDIO_H

#include <stdio.h>

#endif /* STDIO_H */

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif /* STDLIB_H */

#ifndef STRING_H
#define STRING_H

#include <string.h>

#endif /* STRING_H */


#ifndef TEST_MAIN_H
#define TEST_MAIN_H

#include <test_main.h>

#endif /* TEST_MAIN_H */


char* call_program(char* cmd, int buffer_size){
    FILE* fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return NULL;
    }

    char* buffer = malloc(buffer_size);
    int index = 0;
    char c = '\0';
    /*the = is intentional, we need to use c later*/
    while(((c = fgetc(fp)) != EOF) && (index < buffer_size-1)){
        buffer[index++] = c;
    }
    pclose(fp);
    buffer[index] = '\0';

    return buffer;
}

#ifndef _WIN32
/* Linux command */
#define DIR_SEPORATOR "/"
#else
/* Windows command */
#define DIR_SEPORATOR "\\"
#endif

static int test_length(void){
    #define BUF_SIZE 1024
    char cmd[BUF_SIZE];
    const char* cmd_start = "bin" DIR_SEPORATOR "cmaze";

    strcpy(cmd, cmd_start);

    char* buf = call_program(cmd, 1024);
    if(
       buf[9]  == ' ' &&
       buf[10] == '1' &&
       buf[11] == ' '){
        printf("Pass: with no arguments, prints that argc is 1\n");
    }else{
        printf("FAIL: with no arguments, prints the wrong number of arguments. \n\t It prints: %.3s\n", buf+9);
    }
    free(buf);
    return 0;
    #undef BUF_SIZE
}

#undef DIR_SEPORATOR

int main(void){
    test_length();
    return 0;
}


