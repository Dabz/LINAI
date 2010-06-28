#include        "heuristic.h"

/* --------------------------------------------------------------------------*/
/**
 * @brief Computes the heuristic value for the given grid && player
 *
 * @param cs Player for whom the heuristic value is computed
 * @param grid Grid
 *
 * @returns Returns the heuristic value
 */
/* --------------------------------------------------------------------------*/
int heuristic(chess_case cs, board grid, board test_grid)
{

    int h = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((grid[i][j] == COMPUTER || grid[i][j] == ENNEMY) &&
                (test_grid == NULL || (test_grid[i][j] != BLANK)))
            {
                // Inverse the value depending on the player for whom
                // the heuristic is computed
                int h_tmp = value_zone(i, j, grid);
                if (h_tmp == INT_MAX) {
                    return ((cs * grid[i][j] == -1) ? INT_MIN : INT_MAX);
                }
                else
                {
                    int sub_h = cs * grid[i][j] * h_tmp;
                    if (((DEPTH % 2 == 1) && (cs != grid[i][j])) ||
                        ((DEPTH % 2 == 0) && (cs == grid[i][j])))
                        sub_h *= 100;
                    h += sub_h;
                }
            }
        }
    }

    return h;
}

board get_heuristic_board(board grid) {
    int i,j;
    board res = board_create();
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (grid[i][j] == ENNEMY || grid[i][j] == COMPUTER)
                res[i][j] = check_cell(grid, i, j);
            else
                res[i][j] = BLANK;
        }
    }
    return res;
}


/* --------------------------------------------------------------------------*/
/**
 * @brief Computes the heuristic value for the given player in the row,
 * column && both diagonals affected by the given position
 *
 * @param x
 * @param y
 * @param grid
 *
 * @returns
 */
/* --------------------------------------------------------------------------*/
int value_zone(int x, int y, board grid)
{
    int value = 0;
    int nb_stone = 1;
    int nb_case = 1;
    int i;
    int h = 0;
    chess_case player = grid[x][y];
    chess_case ennemy = (chess_case)(-1 * player);

    //Calculate stones on the column
    for (i=1; ((x+i<BOARD_SIZE)&&is_valid(i, x+i, y, ennemy, grid)); i++)
        check_case(i, value, nb_stone, nb_case, x+i, y, player, grid);
    for (i=1; ((x-i>0)&&is_valid(i, x-i ,y , ennemy ,grid)); i++)
        check_case(i, value, nb_stone, nb_case, x-i, y, player, grid);
    if (update_heuristic(value, nb_stone, nb_case, h))
        return h;

    //Calculate stones on the row
    for (i=1; ((y+i<BOARD_SIZE)&&is_valid(i, x, y+i, ennemy, grid)); i++)
        check_case(i, value, nb_stone, nb_case, x, y+i, player, grid);
    for (i=1; ((y-i>0)&&is_valid(i, x, y-i, ennemy, grid)); i++)
        check_case(i, value, nb_stone, nb_case, x, y-i, player, grid);
    if (update_heuristic(value, nb_stone, nb_case, h))
        return h;

    //Calculate stones on the diagonals
    for (i=1; ((x+i<BOARD_SIZE)&&(y+i<BOARD_SIZE)&&is_valid(i, x+i, y+i, ennemy, grid)); i++)
        check_case(i, value, nb_stone, nb_case, x+i, y+i, player, grid);
    for (i=1; ((x-i>0)&&(y-i>0)&&is_valid(i, x-i, y-i, ennemy, grid)); i++)
        check_case(i, value, nb_stone, nb_case, x-i, y-i, player, grid);
    if (update_heuristic(value, nb_stone, nb_case, h))
        return h;

    for (i=1; ((x+i<BOARD_SIZE)&&(y-i>0)&&is_valid(i, x+i, y-i, ennemy, grid)); i++)
        check_case(i, value, nb_stone, nb_case, x+i, y-i, player, grid);
    for (i=1; ((x-i>0)&&(y+i<BOARD_SIZE)&&is_valid(i, x-i, y+i, ennemy, grid)); i++)
        check_case(i, value, nb_stone, nb_case, x-i, y+i, player, grid);
    update_heuristic(value, nb_stone, nb_case, h);

    return h;
}

// Continue to move forward while we have not reached the 5th case,
// while we are not out of bounds && while there is no ennemy
inline bool is_valid(int i, int x, int y, chess_case ennemy, board grid)
{
    return ((i<4)&&(grid[x][y] != ennemy));
}

void check_case(int i, int &value, int &nb_stone, int &nb_case,
                int x, int y, chess_case player, board grid)
{
    //Value are like this : (123x321)
    if (grid[x][y] == player) {
        nb_stone++;
        value += 4-i;
    }
    nb_case++;
}

void init_value(int &value, int &nb_stone, int &nb_case)
{
    value = 0;
    nb_stone = 1;
    nb_case = 1;
}

bool update_heuristic(int &value, int &nb_stone, int &nb_case, int &h)
{
    if (nb_case < 5) {
        init_value(value, nb_stone, nb_case);
        return false;
    }
    else if ((value == 10) && (nb_stone == 5)) {
        h = INT_MAX;  // Win (23x32)
        //std::cout << "1 ";
    }
    else if ((value == 8) && (nb_case == 7)) {
        h += 50000; // Always Win in 1 move (1.3x3.1) (.23x3..)
        //std::cout << "2 ";
    }
    else if ((value == 8) || ((value == 7) && (nb_stone == 4))) {
        h += 5000;  // Win in 1 move [.23x3.] (23x3.) (23x.2)
        //std::cout << "3 ";
    }
    else if ((value == 6) && (nb_stone == 3) && (nb_case >= 5)) {
        h += 500;    // Win in 2 moves (..3x3..) (.3x3..)
        //std::cout << "4 ";
    }
    else
        h += ((nb_stone - 1) * 10) + value;

    init_value(value, nb_stone, nb_case);
    return (h == INT_MAX);
}

namespace {
    chess_case check_cell(board grid, short int i, short int j) {

        // Counter for every direction
        short int hor = 1, vert = 1, diag = 1, counter_diag = 1;

        // To know if we must continue to search in a direction
        bool hor_l = true, vert_l = true, diag_l = true, counter_diag_l = true,
             hor_r = true, vert_r = true, diag_r = true, counter_diag_r = true;

        short int x;

        chess_case opponent = get_opponent(grid[i][j]);

        for (x = 1; x < 5; x++) {
            // Check horizontals line
            if (hor_l && j-x >= 0 && grid[i][j-x] != opponent)
                hor++;
            else
                hor_l = false;
            if (hor_r && j+x < BOARD_SIZE && grid[i][j+x] != opponent)
                hor++;
            else
                hor_r = false;

            // Check verticals line
            if (vert_l && i-x >= 0 && grid[i-x][j] != opponent)
                vert++;
            else
                vert_l = false;
            if (vert_r && i+x < BOARD_SIZE && grid[i+x][j] != opponent)
                vert++;
            else
                vert_r = false;

            // Check diagonals
            if (diag_l && j-x >= 0 && i-x >= 0 &&  grid[i-x][j-x] != opponent)
                diag++;
            else
                diag_l = false;
            if (diag_r && j+x < BOARD_SIZE && i+x < BOARD_SIZE && grid[i+x][j+x] != opponent)
                diag++;
            else
                diag_r = false;

            // Check counter diagonals
            if (counter_diag_l && j-x >= 0 && i+x < BOARD_SIZE && grid[i+x][j-x] != opponent)
                counter_diag++;
            else
                counter_diag_l = false;
            if (counter_diag_r && j+x < BOARD_SIZE && i-x >= 0 && grid[i-x][j+x] != opponent)
                counter_diag++;
            else
                counter_diag_r = false;

            if (diag >= 5 || counter_diag >= 5 || hor >= 5 || vert >= 5)
                return grid[i][j];
            else if ( ! (diag_l || diag_r || counter_diag_r || counter_diag_l || hor_r || hor_l || vert_l || vert_r) )
                return BLANK;
        }

        return BLANK;
    }
}
