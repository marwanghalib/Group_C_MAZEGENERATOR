#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif /* STDIO_H */

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif /* STRING_H */

#ifndef MAIN_H
#define MAIN_H
#include "main.h"
#endif /* MAIN_H */

#ifndef COLL_INPUT_H
#define COLL_INPUT_H
#include "coll_input.h"
#endif /* COLL_INPUT_H */

#ifndef MAZE_H
#define MAZE_H
#include "maze.h"
#endif

#define PRG_NAME "maze" /* program name */
#define VERSION  "0.3"  /* version number */


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

void coll_args(int argc, char *argv[],maze_t* maze){
  //assigning default values to the variables which will reset if user input something
    int width = 10;
    int height = 5;
    double bias = 1.0;
    char* output_file_path = NULL;
    char* alg_name = "backtrack";
    char* tile_set_name = "hedge";

    int i = 0;

    while(i<argc) {
      char *temp_argv=strtok(argv[i],"?");
      printf("%s",temp_argv);
        if (strcmp(temp_argv, "-h") == 0 || strcmp(temp_argv, "--help") == 0){
            help();
            // return NULL;
        }
        else if(strcmp(temp_argv, "--width") == 0){
          //temp_argv will contain value for width
           temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                // if input value is null we will proceed to the next index of loop without changing anything
                i++;
                continue;
            }
           //if user input a wrong value for width then width will remain set to its default value
            int temp_width = atoi(temp_argv);
            i++;
            if (temp_width > 0){
              width=temp_width;
            }
         }else if(strcmp(temp_argv, "--height") == 0){
              temp_argv = strtok(NULL, "?");
              if(temp_argv == NULL){
                // if input value is null we will proceed to the next index of loop without changing anything
                i++;
                continue;
            }

             int temp_height = atoi(temp_argv);
              i++;
              if (temp_height > 0){
                  height=temp_height;
               }
         }else if(strcmp(temp_argv, "--bias") == 0 || strcmp(temp_argv, "-b")){
              temp_argv = strtok(NULL, "?");
               if(temp_argv == NULL){
                // if input value is null we will proceed to the next index of loop without changing anything
                i++;
                continue;
            }
              double temp_bias = atof(temp_argv);
              i++;
              if (temp_bias > 0){
                  bias=temp_bias;
             }
       else if(strcmp(temp_argv, "-a") == 0||strcmp(temp_argv, "--alg") == 0||strcmp(temp_argv, "--algorithm") == 0){
            temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                // if input value is null we will proceed to the next index of loop without changing anything
                i++;
                continue;
            }
            alg_name=temp_argv;
            i++;
        }
      else if(strcmp(temp_argv, "-s") == 0||strcmp(temp_argv, "--size") == 0){
        // here temp_argv will first contain width value then next token will contain height value
            temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                // if input value is null we will proceed to the next index of loop without changing anything
                i++;
                continue;
            }
            int temp_width=atoi(temp_argv);
            temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                i++;
                continue;
            }
            int temp_height=atoi(temp_argv);
            i++;
            if(temp_width<0||temp_height<0)
            {
              continue;
            }
            width=temp_width;
            height=temp_height;
        }
      else if(strcmp(temp_argv, "-o") == 0||strcmp(temp_argv, "--output") == 0){
            temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                // if input value is null we will proceed to the next index of loop without changing anything
                i++;
                continue;
            }

            output_file_path=temp_argv;
            i++;
        }
        init_maze(width,height,&maze);
        set_bias(bias,&maze);
        //generate_backtrack(&maze);
 }
}
}





