// =====================================================================================
//
//       Filename:  heuristic.h
//
//    Description:
//
//        Version:  1.0
//        Created:  05/26/2010 04:42:43 PM
//       Revision:  none
//       Compiler:  g++
//
//         AUTHOR:  GASPARINA DAMIEN (HTTP://LAMADA.EU__ GASPAR_D@EPITA.FR
//        Company:  Epita
//
// =====================================================================================

#ifndef HEURISTIC_H
#define HEURISTIC_H

#include        "data.h"
#include        "utils.h"
#include        <climits>
#include        <iostream>

int heuristic(chess_case cs, board grid, board test_grid = NULL);
int value_zone(int x, int y, board grid);
inline bool is_valid(int i, int x, int y, chess_case cs, board grid);
void check_case(int i, int &value, int &nb_stone, int &nb_case,
                int x, int y, chess_case player, board grid);
void init_value(int &value, int &nb_stone, int &nb_case);
bool update_heuristic(int &nb_value, int &nb_stone, int &nb_case, int &h);


/* --------------------------------------------------------------------------*/
/**
 * @brief  Usefull to know which chess has an non-null heuristic value
 *
 * @param grid the grid to test
 *
 * @returns   An board fill with BLANK and chess without a null
 * heuristic value
 */
/* ----------------------------------------------------------------------------*/
board get_heuristic_board(board grid);

namespace {
    chess_case check_cell(board grid, short int i, short int j);
}

#endif
