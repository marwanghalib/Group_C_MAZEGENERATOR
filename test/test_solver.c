#ifndef SOLVE_H
#define SOLVE_H
#include <solve.h>
#endif

#ifndef MAZE_H
#define MAZE_H
#include <maze.h>
#endif

#ifndef SDTBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif

#ifndef TILE_H
#define TILE_H
#include <tile.h>
#endif


#ifndef TILE_DEFAULT_H
#define TILE_DEFAULT_H
#include <tile_default.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif /* STDIO_H */

#ifndef PRINTER_H
#define PRINTER_H
#include <printer.h>
#endif

#ifndef GEN_ALGS_H
#define GEN_ALGS_H
#include <gen_algs.h>
#endif

int main(){

    maze_t maze;

    init_maze(10, 15, &maze);

    gen_sidewinder(&maze);

    print_maze(&maze, TILE_SET_HEDGE, stdout);
    solve_maze(&maze);
    print_maze(&maze, TILE_SET_HEDGE, stdout);

    return 0;
}
