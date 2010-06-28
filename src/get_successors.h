// =====================================================================================
//
//       Filename:  get_successors.h
//
//    Description:
//
//        Version:  1.0
//        Created:  05/26/2010 04:37:22 PM
//       Revision:  none
//       Compiler:  g++
//
//         AUTHOR:  Gasparina Damien (http://lamada.eu, gaspar_d@epita.fr)
//        Company:  Epita
//
// =====================================================================================

#ifndef GET_SUCCESSORS_H
#define GET_SUCCESSORS_H

#include        "data.h"
#include        "utils.h"
#include        "heuristic.h"


/* --------------------------------------------------------------------------*/
/**
 * @brief Return a list containing each children
 *
 * @param tmp The parent board
 * @param next_player The actual player
 *
 * @returns Returns the list of possible moves with corresponding heuristic Successors are sort according to this heuristic
 */
/* ----------------------------------------------------------------------------*/
successors get_successors(chess_case next_player, board tmp);

/* --------------------------------------------------------------------------*/
/**
 * @brief  Actualize the main father board
 *
 * @param nw New father board
 */
/* ----------------------------------------------------------------------------*/
void main_board_change(board nw);


/* --------------------------------------------------------------------------*/
/**
 * @brief  Get the main board
 *
 * @returns   main board
 */
/* ----------------------------------------------------------------------------*/
board main_board_get(void);

/* --------------------------------------------------------------------------*/
/**
 * @brief  Check if we can play in a position
 *
 * @param grid Board to test
 * @param x position of the chess
 *
 * @returns   True if we can play, false else
 */
/* ----------------------------------------------------------------------------*/
bool special_rules(board grid, pos x);

#endif
