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


#endif /* MAIN_H */



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

/* This function collects all the arguments
 */
void coll_args(int argc, char *argv[],maze_t* maze, tile_set_t** tile_set){
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
            return NULL;
        }else if (strcmp(temp_argv, "-v") == 0 || strcmp(temp_argv, "--version") == 0){
            version();
            return NULL;
        }else if(strcmp(temp_argv, "--width") == 0){
           temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                help();
                return NULL;
            }

             width = atoi(temp_argv);
             i++;
             if (width > 0){
                width;
              }

             else{
               help();
             return NULL;
             }
         }else if(strcmp(temp_argv, "--height") == 0){
              temp_argv = strtok(NULL, "?");
              if(temp_argv == NULL){
                help();
                return NULL;
            }

              height = atoi(temp_argv);
              i++;
              if (height > 0){
                  height;
               }
              else{
                help();
              return NULL;
              }

         }else if(strcmp(temp_argv, "--bias") == 0 || strcmp(temp_argv, "-b")){
              temp_argv = strtok(NULL, "?");
               if(temp_argv == NULL){
                help();
                return NULL;
            }

              bias = atof(temp_argv);
              i++;
              if (bias > 0){
                  bias;
               }
              else{
                help();
                return NULL;
            }
         }else if(strcmp(temp_argv, "--tileset") == 0 || strcmp(temp_argv, "-t")==0){
              temp_argv = strtok(NULL, "?");
              if(temp_argv == NULL){
                help();
                return NULL;
            }

              tile_set_name = temp_argv;
              i++;
              if (tile_set){
                 tile_set_name;
               }
              else{
                help();
                return NULL;
       }
     }else if(strcmp(temp_argv, "-a") == 0||strcmp(temp_argv, "--alg") == 0||strcmp(temp_argv, "--algorithm") == 0){
            temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                help();
                return NULL;
            }
            alg_name=temp_argv;
            i++;
        }
      else if(strcmp(temp_argv, "-s") == 0||strcmp(temp_argv, "--size") == 0){
            temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                help();
                return NULL;
            }
            width=atoi(temp_argv);
            temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                help();
                return NULL;
            }
            height=atoi(temp_argv);
            i++;
            if(width<0||height<0)
            {
              help();
              return NULL;
            }
        }
      else if(strcmp(temp_argv, "-o") == 0||strcmp(temp_argv, "--output") == 0){
            temp_argv = strtok(NULL, "?");
            if(temp_argv == NULL){
                help();
                return NULL;
            }

            output_file_path=temp_argv;
            i++;
        }
   }
 }





