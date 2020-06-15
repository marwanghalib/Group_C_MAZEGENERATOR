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

#include <main.h>
#include <coll_input.h>

#endif /* MAIN_H */



void (*gen_alg(maze_t* maze)) collect_arguments(int argc, char **argv, File** output_file, maze_t* maze, tile_set_t** tile_set){

/* Display help information and exit succesfully
 */

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
/* Display version information and exit succesfully
 */
void version(void)
{
	printf("\
%s %s\n\
\n\
The Program name and the version number is.\n",
	       PRG_NAME, VERSION);

	exit(EXIT_SUCCESS);
}

void coll_args(int argc, char *argv[])
{
	int i;

	for (i = 1; i < argc; ++i) {
		if (strncmp(argv[i], "-h", 3) == 0
		 || strncmp(argv[i], "--help", 7) == 0)
			help();
		else if (strncmp(argv[i], "-v", 7) == 0
		        || strncmp(argv[i], "--version", 10) == 0)
			version();

        else{
        break;
        }
 }
}



