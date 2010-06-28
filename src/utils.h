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
//         Author:  GASPARINA Damien (http://lamada.eu), gaspar_d@epita.fr
//        Company:  Epita
//
// =====================================================================================

#ifndef UTILS_H
#define UTILS_H

#include        "data.h"
#include        "alpha_beta.h"

/* --------------------------------------------------------------------------*/
/**
 * @brief  Create an empty board
 *
 * @returns  The empty board
 */
/* ----------------------------------------------------------------------------*/
board board_create(void);

/* --------------------------------------------------------------------------*/
/**
 * @brief  Copy a board
 *
 * @param x Board to copy
 *
 * @returns   New board equal to x
 */
/* ----------------------------------------------------------------------------*/
board board_create(board x);


/* --------------------------------------------------------------------------*/
/**
 * @brief  Create a board fill with cd
 *
 * @param cs Element present in every cell of the board
 *
 * @returns   New board
 */
/* ----------------------------------------------------------------------------*/
board board_create(chess_case cs);

/* --------------------------------------------------------------------------*/
/**
 * @brief  Create an empty board
 *
 * @returns   An empty board
 */
/* ----------------------------------------------------------------------------*/
board board_create_empty();


/* --------------------------------------------------------------------------*/
/**
 * @brief  Destroy a board
 *
 * @param x the board to detroy
 *
 * @returns   a null board
 */
/* ----------------------------------------------------------------------------*/
board board_destroy(board x);

/* --------------------------------------------------------------------------*/
/**
 * @brief  Create a board from a tree and a original board
 *
 * @param crt The tree
 * @param main_board The original board
 * @param player The actual player
 *
 * @returns   The generated board
 */
/* ----------------------------------------------------------------------------*/
board board_from_tree_node(tree_node crt, board main_board, chess_case player );


/* --------------------------------------------------------------------------*/
/**
 * @brief  Return the ennemy of cs
 *
 * @param cs
 *
 * @returns   Ennemy of cs
 */
/* ----------------------------------------------------------------------------*/
chess_case get_opponent(chess_case cs);

inline chess_case get_opponent(chess_case cs) {
    return (chess_case) (-1 * cs);
}

#endif
