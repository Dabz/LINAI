// =====================================================================================
//
//       Filename:  data.h
//
//    Description:
//
//        Version:  1.0
//        Created:  05/26/2010 04:07:25 PM
//       Revision:  none
//       Compiler:  gcc
//
//         AUTHOR:  Gasparina Damien (http://lamada.eu, gaspar_d@epita.fr)
//        Company:  Epita
//
// =====================================================================================

#ifndef DATA_H
#define DATA_H

#include        <list>

const int BOARD_SIZE = 15;
const int DEPTH = 3;
const int SUCC_RADIUS = 2;


struct pos {
  int x;
  int y;
};

enum chess_case {
    BLANK = 0,
    COMPUTER = 1,
    ENNEMY = -1,
    NEIGHBOOR = 2
};

enum player_type {
  CPU = 0,
  HUM = 1
};

typedef chess_case** board;

struct tree_node {
    int h;
    pos move;
    tree_node* father;
};

typedef std::list<tree_node> successors;

struct tree {
    tree_node node;
    successors children;
};

#endif
