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
#define PRG_NAME "Maze Generator" /* program name */
#define VERSION  "1.0"  /* version number */

#include <main.h>
#include <coll_input.h>
#endif /* MAIN_H */

//void (*collect_arguments(int argc, char** argv, FILE** output_file, maze_t* maze,tile_set_t** tile_set))(maze_t*);

void help(void)
{
    printf(" %s - a maze generator and solver\n\
Usage: %s [options]\n\
\n\
  --height              How tall is the maze\n\
  --width               How tall is the maze\n\
  --size or -s          How wide and tall is the maze\n\
  --bias or -b          How biased is the maze: >1 more horizontal hallways <1 more vertical hallways\n\
  -a or -algorithm      Which algorithm to use \n\
  -v or --version       Display program name and version number\n\
  -t or --tileset	    What characters to use to represent the walls of the maze in the output\n\
  -o or	--output	    Where to send the output\n\
  --solve	            Solve the maze\n\
  -i or	--input	        Read stdin as FILE\n",
            PRG_NAME, PRG_NAME);

	exit(EXIT_SUCCESS);
}

/*
 void openfile(File *argv){
    char *out_file = argv;
    FILE *output_file=fopen(out_file,"w");

 } */
 //Display version information and exit succesfully
void version(void)
{
	printf("\
The Program name is %s and the version number is %s .\n",PRG_NAME, VERSION);

	exit(EXIT_SUCCESS);
}

void coll_args(int argc, char **argv, FILE** output_file)
{
	int i, height=5, width=10, bias = 1.0;

	for (i = 1; i < argc; i++) {
		if (strncmp(argv[i], "-h", 3) == 0
		 || strncmp(argv[i], "--help", 7) == 0)
			help();
		else if (strncmp(argv[i], "-v", 7) == 0
		        || strncmp(argv[i], "--version", 10) == 0)
			version();
        else if(strncmp(argv[i], "-o", 3) == 0
		        || strncmp(argv[i], "--output", 9) == 0))
		        openfile();

        break;
        }
 }
}

int main(int argc, char* argv[]){

   coll_args(argc, argv);

    return 0;
}
