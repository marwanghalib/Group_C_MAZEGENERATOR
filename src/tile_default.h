#ifndef TILE_H
#define TILE_H
#include "tile.h"
#endif

static const tile_set_t hedge_set = (tile_set_t){
    .empty      = " ",
    .full       = ".",
    .before     = "",
    .after      = "",
    .start      = "<",
    .end        = ">",
    .h_wall     = "#",
    .v_wall     = "#",
    .corner[0]  = " ",
    .corner[1]  = "#",
    .corner[2]  = "#",
    .corner[3]  = "#",
    .corner[4]  = "#",
    .corner[5]  = "#",
    .corner[6]  = "#",
    .corner[7]  = "#",
    .corner[8]  = "#",
    .corner[9]  = "#",
    .corner[10] = "#",
    .corner[11] = "#",
    .corner[12] = "#",
    .corner[13] = "#",
    .corner[14] = "#",
    .corner[15] = "#"
};

static const tile_set_t dungen_set = (tile_set_t){
    .empty      = " ",
    .full       = ".",
    .before     = "",
    .after      = "",
    .start      = "<",
    .end        = ">",
    .h_wall     = "-",
    .v_wall     = "|",
    .corner[0]  = " ",
    .corner[1]  = "-",
    .corner[2]  = "-",
    .corner[3]  = "-",
    .corner[4]  = "-",
    .corner[5]  = "-",
    .corner[6]  = "-",
    .corner[7]  = "-",
    .corner[8]  = "-",
    .corner[9]  = "-",
    .corner[10] = "-",
    .corner[11] = "-",
    .corner[12] = "-",
    .corner[13] = "-",
    .corner[14] = "-",
    .corner[15] = "-"
};

static const tile_set_t vt100_set = (tile_set_t){
    .empty      = "_",
    .full       = "a",
    .before     = "\x1b(0",
    .after      = "\x1b(B",
    .start      = "<",
    .end        = ">",
    .h_wall     = "q",
    .v_wall     = "x",
    .corner[0]  = "_",
    .corner[1]  = "x",
    .corner[2]  = "q",
    .corner[3]  = "j",
    .corner[4]  = "x",
    .corner[5]  = "x",
    .corner[6]  = "k",
    .corner[7]  = "u",
    .corner[8]  = "q",
    .corner[9]  = "m",
    .corner[10] = "q",
    .corner[11] = "v",
    .corner[12] = "l",
    .corner[13] = "t",
    .corner[14] = "w",
    .corner[15] = "n"
};

//const tile_set_t* TILE_SET_HEDGE  = &hedge_set;
//const tile_set_t* TILE_SET_DUNGEN = &dungen_set;
/*see https://en.wikipedia.org/wiki/Box-drawing_character#Unix,_CP/M,_BBS */
//const tile_set_t* TILE_SET_VT100    = &vt100_set;
