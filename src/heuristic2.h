#ifndef HEURISTIC_H_2
#define HEURISTIC_H_2

#include "data.h"
#include <climits>

int heuristic2(chess_case cs, board grid);
int bulb_value(int nb_pieces, chess_case cs, chess_case piece);
void find_bulbs_row(int &h, int row, chess_case cs, board grid);
void find_bulbs_col(int &h, int col, chess_case cs, board grid);
void find_bulbs_diag(int &h, int row, int col, chess_case cs, board grid);
void find_bulbs_cdiag(int &h, int row, int col, int stop_search, chess_case cs, board grid);


#endif
