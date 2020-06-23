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

struct solver_data{
    long step_count;
    bool on_the_path;

};

/* starting at the end, flood fill to the start of the maze */
static void paint_steps(maze_t* maze){
    struct solver_data* data = get_extra(maze, maze->end_x, maze->end_y);
    data->step_count = 1;
    long count = 1;
    cell_t cell;
    bool keep_going = true;
    while(keep_going){
        keep_going = false;
        for(int x = 0; x<maze->width; x++){
            for(int y = 0; y<maze->height; y++){
                if(data = get_extra(maze, x, y) && data->step_count == count){
                    if(x == maze->start_x && y == maze->start_y){
                        return;/*I am at the start, and it has the correct step count, so I am done*/
                    }
                    cell = get_cell(maze, x, y);
                    if(!cell.north){
                        data = get_extra(maze, x, y-1);
                        if(!data->step_count){
                            data->step_count = count+1;
                            keep_going = true;
                        }
                    }
                    if(!cell.south){
                        data = get_extra(maze, x, y+1);
                        if(!data->step_count){
                            data->step_count = count+1;
                            keep_going = true;
                        }
                    }
                    if(!cell.east){
                        data = get_extra(maze, x+1, y);
                        if(!data->step_count){
                            data->step_count = count+1;
                            keep_going = true;
                        }
                    }
                    if(!cell.west){
                        data = get_extra(maze, x-1, y);
                        if(!data->step_count){
                            data->step_count = count+1;
                            keep_going = true;
                        }
                    }
                }
            }
        }
        count++;
    }
}

static void trace_path(maze_t* maze){
    int x = maze->start_x;
    int y = maze->start_y;
    struct solver_data* data = get_extra(maze, x, y);
    data->on_the_path = true;

    while(true){
        long count = data->step_count;
        cell_t cell = get_cell(maze, x, y);
        if(cell.end){
            return;
        }
        if(!cell.north){
            data = get_extra(maze, x, y-1);
            if(data->step_count < count){
                data->on_the_path = true;
                y -= 1;
                continue;
            }
        }
        if(!cell.south){
            data = get_extra(maze, x, y+1);
            if(data->step_count < count){
                data->on_the_path = true;
                y += 1;
                continue;
            }
        }
        if(!cell.east){
            data = get_extra(maze, x+1, y);
            if(data->step_count < count){
                data->on_the_path = true;
                x += 1;
                continue;
            }
        }
        if(!cell.west){
            data = get_extra(maze, x-1, y);
            if(data->step_count < count){
                data->on_the_path = true;
                x -= 1;
                continue;
            }
        }
    }

}

static void clear_step_count(maze_t* maze){
    for(int x = 0; x<maze->width; x++){
        for(int y = 0; y<maze->height; y++){
            struct solver_data* data = get_extra(maze, x, y);
            if(data){
                data->step_count = 0;
            }
        }
    }
}

void solve_maze(maze_t* maze){
    set_size_of_extra(sizeof(struct solver_data), maze);

    paint_steps(maze);

    struct solver_data* data = get_extra(maze, maze->start_x, maze->start_y);

    if(!data.step_count){/*There is no solusion*/
        set_size_of_extra(0, maze);
        return;
    }

    trace_path(maze);
}



















