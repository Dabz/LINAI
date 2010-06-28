#include "get_successors.h"

namespace {
    board main_board = NULL;
}


void main_board_change(board nw) {
    // No need to copy && destroy
    main_board = nw;
}

board main_board_get() {
    return main_board;
}

// Comparison function for s||ting the list of successors acc||ding to
// the heuristic of each state
bool compare (tree_node first, tree_node second)
{
    return (first.h > second.h);
}

// Add a successor for which a piece has been added in given position
void add_successor(
                   int x,
                   int y,
                   board tmp,
                   chess_case next_player,
                   successors &list
                  )
{
    tree_node node_succ;
    tmp[x][y] = next_player;
    node_succ.move.x = x;
    node_succ.move.y = y;
    // Add successor to the list
    list.push_back(node_succ);
    tmp[x][y] = NEIGHBOOR;
}

// Add successors for every blank case around given position with radius
// SUCC_RADIUS
void add_successors_radius(
                           int x,
                           int y,
                           board tmp,
                           chess_case next_player,
                           successors &list
                          )
{
    pos p;
    for (int i = x - SUCC_RADIUS; i <= x + SUCC_RADIUS; i++) {
        if ((i >= 0) && (i < BOARD_SIZE))
        {
            p.x = i;
            for (int j = y - SUCC_RADIUS; j <= y + SUCC_RADIUS ; j++) {
                if ((j >= 0) && (j < BOARD_SIZE)) {
                    p.y = j;
                    if (tmp[i][j] == BLANK && (next_player == ENNEMY || special_rules(tmp, p)) )
                        add_successor(i, j, tmp, next_player, list);
                }
            }
        }
    }
}

void clean_board(board grid) {
    int i,j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (grid[i][j] == NEIGHBOOR)
                grid[i][j] = BLANK;
        }
    }
}

successors get_successors(chess_case next_player, board tmp)
{
    successors list;
    int i,j;
    // successors are blank cases around pieces within radius
    // SUCC_RADIUS
    for (i = 0; i < BOARD_SIZE; i++) {
        j = 0;
        while (j < BOARD_SIZE) {
            // for each piece in the grid
            if ( ((tmp[i][j] == COMPUTER) || (tmp[i][j] == ENNEMY)))
                // Add every successor around it
                add_successors_radius(i, j, tmp, next_player, list);
            j++;
        }
    }

    clean_board(tmp);
    return list;
}

bool increment_counter(int nb, int& count_3, int& count_4) {
    if (nb == 3)
        count_3++;
    else if (nb == 4)
        count_4++;
    else if (nb > 5)
        return true;
    return false;
}

bool special_rules(board grid, pos x) {
    int i, nb;
    int count_3 = 0, count_4 = 0;
    const chess_case cs = COMPUTER;

    // Check vertical lined
    i = 1;
    nb = 1;
    while(x.y-i >= 0 && grid[x.x][x.y-i] == cs)
        i++;
    nb += i-1;
    i = 1;
    while(x.y+i < BOARD_SIZE && grid[x.x][x.y+i] == cs)
        i++;
    nb += i-1;

    if (increment_counter(nb, count_3, count_4))
        return false;

    // Check horizontal lines
    i = 1;
    nb = 1;
    while(x.x-i >= 0 && grid[x.x-i][x.y] == cs)
        i++;
    nb += i-1;
    i = 1;
    while(x.x+i < BOARD_SIZE && grid[x.x+i][x.y] == cs)
        i++;
    nb += i-1;

    if (increment_counter(nb, count_3, count_4))
      return false;


    // Check diagonal lines
    i = 1;
    nb = 1;
    while(x.y-i >= 0 && x.x-i >= 0 && grid[x.x-i][x.y-i] == cs)
        i++;
    nb += i-1;
    i = 1;
    while(x.y+i < BOARD_SIZE && x.x+i < BOARD_SIZE && grid[x.x+i][x.y+i] == cs)
        i++;
    nb += i-1;
    if (increment_counter(nb, count_3, count_4))
        return false;

    // Check counter diagonal lines
    nb = 1;
    i = 1;
    while(x.y-i >= 0 && x.x+i < BOARD_SIZE && grid[x.x+i][x.y-i] == cs)
        i++;
    nb += i-1;
    i = 1;
    while(x.y+i < BOARD_SIZE && x.x-i >= 0 && grid[x.x-i][x.y+i] == cs)
        i++;
    nb += i-1;
    if (increment_counter(nb, count_3, count_4))
        return false;

    if (count_3 > 1 || count_4 > 1)
        return false;
    else
        return true;

}
