// =====================================================================================
//
//       Filename:  alpha_beta.cc
//
//    Description:
//
//        Version:  1.0
//        Created:  05/26/2010 07:26:48 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gasparina Damien (http://lamada.eu), gaspar_d@epita.fr
//        Company:  Epita
//
// =====================================================================================

#include        "alpha_beta.h"

tree_node alpha_beta(int depth,
                     board main_board,
                     chess_case player,
                     int alpha,
                     int beta) {

    // Make a copy of itself
    main_board = board_create(main_board);

    // This board is use to opimize the heuristic algorithm
    board test_board = get_heuristic_board(main_board);

    // Get every successor possible
    successors my_successors = get_successors(player, main_board);
    successors::iterator child;
    tree_node res;

    // For the first move
    res.move.x = BOARD_SIZE / 2;
    res.move.y = BOARD_SIZE / 2;
    int tmp;

    for (child=my_successors.begin(); child != my_successors.end(); child++) {
        main_board[child->move.x][child->move.y] = get_opponent(player);
        test_board[child->move.x][child->move.y] = get_opponent(player);
        tmp = min_value(depth-1, (*child), get_opponent(player),
                         main_board, test_board, alpha, beta);
        if (tmp > alpha) {
            alpha = tmp;
            res = (*child);
        }
        main_board[child->move.x][child->move.y] = BLANK;
        test_board[child->move.x][child->move.y] = BLANK;
    }
    return res;
}

namespace {

    int get_heuristic_value(chess_case player, board x, board test_board) {
        int tmp = heuristic(player, x, test_board);
        return tmp;
    }

    // Can be simplified with negamax
    int max_value(int depth,
                  tree_node grid,
                  chess_case player,
                  board main_board,
                  board test_board,
                  int alpha,
                  int beta) {
        if (depth <= 0) {
            return get_heuristic_value(player, main_board, test_board);
        }
        else {
            successors my_successors = get_successors(player, main_board);
            successors::iterator child;

            for (child=my_successors.begin(); child != my_successors.end(); child++) {
                main_board[child->move.x][child->move.y] = player;
                test_board[child->move.x][child->move.y] = player;
                alpha = std::max(alpha, min_value(depth-1, (*child), get_opponent(player),
                                                  main_board, test_board, alpha, beta));
                if (alpha < beta) {
                    main_board[child->move.x][child->move.y] = BLANK;
                    test_board[child->move.x][child->move.y] = BLANK;
                    return alpha;
                }
                main_board[child->move.x][child->move.y] = BLANK;
                test_board[child->move.x][child->move.y] = BLANK;
            }
            return alpha;
        }
    }

    int min_value(int depth,
                  tree_node grid,
                  chess_case player,
                  board main_board,
                  board test_board,
                  int alpha,
                  int beta) {
        if (depth == 0) {
            return get_heuristic_value(player, main_board, test_board);
        }
        else {
            successors my_successors = get_successors(player, main_board);
            successors::iterator child;
            for (child=my_successors.begin(); child != my_successors.end(); child++) {
                main_board[child->move.x][child->move.y] = player;
                test_board[child->move.x][child->move.y] = player;
                beta = std::min(beta, max_value(depth-1, (*child), get_opponent(player),
                                                 main_board, test_board, alpha, beta));
                if (alpha < beta) {
                    main_board[child->move.x][child->move.y] = BLANK;
                    test_board[child->move.x][child->move.y] = BLANK;
                    return beta;
                }
                main_board[child->move.x][child->move.y] = BLANK;
                test_board[child->move.x][child->move.y] = BLANK;
            }
            return beta;
        }
    }
}

