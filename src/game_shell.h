#ifndef GAME_SHELL_H
#define GAME_SHELL_H

#include        "data.h"
#include        "alpha_beta.h"
#include        "display.h"
#include        <iostream>
#include        <ctime>

chess_case has_won(const board grid);
void start_game(player_type p1, player_type p2);

#endif
