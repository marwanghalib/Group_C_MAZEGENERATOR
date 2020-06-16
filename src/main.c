#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef SDTBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif /* STDIO_H */
#define PRG_NAME "maze" /* program name */
#define VERSION  "0.3"  /* version number */

#ifndef MAIN_H
#define MAIN_H
#include <coll_input.h>

#endif /* MAIN_H */



int main(int argc, char* argv[]){

   coll_args(argc, argv);

    return 0;
}
