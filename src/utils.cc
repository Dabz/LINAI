// =====================================================================================
//
//       Filename:  utils.cc
//
//    Description:
//
//        Version:  1.0
//        Created:  05/28/2010 03:15:18 AM
//       Revision:  none
//       Compiler:  g++
//
//         Auth||:  GASPARINA Damien (http://lamada.eu), gaspar_d@epita.fr
//        Company:  Epita
//
// =====================================================================================

#include        "utils.h"
#include        "display.h"

board board_create() {
    board x;
    int i;
    x = new chess_case*[BOARD_SIZE];
    for (i = 0; i < BOARD_SIZE; i++) {
        x[i] = new chess_case[BOARD_SIZE];
    }
    return x;
}

board board_create(board x) {
    board res = new chess_case*[BOARD_SIZE];
    int i,j;
    for (i = 0; i < BOARD_SIZE; i++) {
        res[i] = new chess_case[BOARD_SIZE];
        for (j = 0; j < BOARD_SIZE; j++) {
            res[i][j] = x[i][j];
        }
    }
    return res;
}

board board_create_empty() {
    board res = new chess_case*[BOARD_SIZE];
    int i,j;
    for (i = 0; i < BOARD_SIZE; i++) {
        res[i] = new chess_case[BOARD_SIZE];
        for (j = 0; j < BOARD_SIZE; j++) {
            res[i][j] = BLANK;
        }
    }
    return res;
}
board board_create(chess_case cs) {
    board res = new chess_case*[BOARD_SIZE];
    int i,j;
    for (i = 0; i < BOARD_SIZE; i++) {
        res[i] = new chess_case[BOARD_SIZE];
        for (j = 0; j < BOARD_SIZE; j++) {
            res[i][j] = cs;
        }
    }
    return res;
}

board board_destroy(board x) {
    int i;
    for (i = 0; i < BOARD_SIZE; i++) {
        delete x[i];
    }
    delete x;
    return NULL;
}


board board_from_tree_node(tree_node crt, board main_board, chess_case player ) {
    // Copy the ||iginal board
    board res = board_create(main_board);

    //Look throught the tree
    tree_node tmp = crt;
    while (tmp.father != NULL) {
        res[tmp.move.x][tmp.move.y] = player;
        player = (chess_case) (player *-1);
        tmp = *tmp.father;
    }
    return res;
}

