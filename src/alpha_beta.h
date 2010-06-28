// =====================================================================================
//
//       Filename:  alpha_beta.h
//
//    Description:
//
//        Version:  1.0
//        Created:  05/26/2010 04:22:51 PM
//       Revision:  none
//       Compiler:  g++
//
//         AUTHOR:  Gasparina Damien (http://lamada.eu, gaspar_d@epita.fr)
//        Company:  Epita
//
// =====================================================================================

#ifndef ALPHA_BETA_H
#define ALPHA_BETA_H

#include        "data.h"
#include        "get_successors.h"
#include        "heuristic.h"
#include        "heuristic2.h"

#include        <algorithm>
#include        <list>
#include        <climits>
#include	<iostream>


/* --------------------------------------------------------------------------*/
/**
 * @brief Main algorithm
 *
 * @param depth Max depth of the three
 * @param main_board Initial board's game
 * @param player Actual player
 *
 * @returns   Heuristic of the best move
 */
/* ----------------------------------------------------------------------------*/
tree_node alpha_beta(int depth,
               board main_board,
               chess_case player,
               int alpha=INT_MIN,
               int beta=INT_MAX);


namespace {
    int get_heuristic_value(chess_case player, board x, board test_board);

    int max_value(int depth,
                  tree_node grid,
                  chess_case player,
                  board main_board,
                  board test_board,
                  int alpha,
                  int beta);

    int min_value(int depth,
                  tree_node grid,
                  chess_case player,
                  board main_board,
                  board test_board,
                  int alpha,
                  int beta);
}
#endif
