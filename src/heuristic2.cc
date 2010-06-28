#include        <iostream>
#include        <climits>
#include        "heuristic2.h"

int heuristic2(chess_case cs, board grid)
{
    int h = 0;
    int i;


    // Testing each row
    //std::cout << "col :" << std::endl;
    for (i = 0; i < BOARD_SIZE; i++)
        find_bulbs_row(h, i, cs, grid);

    //std::cout << "line :" << std::endl;
    // Testing each column
    for (i = 0; i < BOARD_SIZE; i++)
        find_bulbs_col(h, i, cs, grid);

    //std::cout << "Diagonal :" << std::endl;
    // Testing diagonal
    for (i = 0; i < BOARD_SIZE - 4; i++)
        find_bulbs_diag(h, i, 0, cs, grid);
    for (i = 1; i < BOARD_SIZE - 4; i++)
        find_bulbs_diag(h, 0, i, cs, grid);

    //std::cout << "Counter diagonal :" << std::endl;
    // Testing counter diagonal
    for (i = 4; i < BOARD_SIZE; i++)
        find_bulbs_cdiag(h, i, 0, i - 3, cs, grid);
    for (i = 1; i < BOARD_SIZE - 4; i++)
        find_bulbs_cdiag(h, BOARD_SIZE - 1, i, BOARD_SIZE - i - 4, cs, grid);

    return h;
}

// Returns the value of a bulb
// The m||e pieces there are, the greater the value is
// Inverse the result acc||ding of which pieces construct the bulb
int bulb_value(int nb_pieces, chess_case cs, chess_case piece)
{
    int sub_h = 0;
/*
     if (piece == ENNEMY)
        std::cout << "-";
    std::cout << nb_pieces << std::endl;
*/
    switch(nb_pieces)
    {
        case 1: sub_h = 1; break;
        case 2: sub_h = 10; break;
        case 3: sub_h = 250 ; break;
        case 4: sub_h = 5000; break;
        case 5: sub_h = 50000; break;
        default: break;
    }
    if (cs != piece)
        sub_h *= 2;
    return cs * piece * sub_h;
}


// Find 5 length bulbs
// in given row
void find_bulbs_row(int &h, int row, chess_case cs, board grid)
{
    int result = 0;

    // Index from which it is not possible to find another bulb
    int stop_search_x = BOARD_SIZE - 4;
    // Last piece found in the bulb
    chess_case last = BLANK;

    int bulb_BOARD_SIZE;
    int nb_pieces;
    for (int i = 0; i < stop_search_x; i++) {
        // Look for a bulb starting from position i
        bulb_BOARD_SIZE = 0;
        nb_pieces = 0;
        while (bulb_BOARD_SIZE < 5)
        {
            chess_case p = grid[i + bulb_BOARD_SIZE][row];
            if (p == COMPUTER || p == ENNEMY)
            {
                // Test if the piece breaks the bulb
                if (p == (chess_case)(-1 * last))
                    break;
                last = p;
                nb_pieces++;
            }
            bulb_BOARD_SIZE++;
        }
        // If we succeeded to build an non-empty 5 length bulb
        if ((bulb_BOARD_SIZE == 5) && (nb_pieces > 0))
            result += bulb_value(nb_pieces, cs, last);
    }
    h += result;
}


// Find 5 length bulbs
// in given column
void find_bulbs_col(int &h, int col, chess_case cs, board grid)
{
    int result = 0;

    // Index from which it is not possible to find another bulb
    int stop_search_y = BOARD_SIZE - 4;
    // Last piece found in the bulb
    chess_case last = BLANK;

    int bulb_BOARD_SIZE;
    int nb_pieces;
    for (int i = 0; i < stop_search_y; i++) {
        // Look for a bulb starting from position i
        bulb_BOARD_SIZE = 0;
        nb_pieces = 0;
        while (bulb_BOARD_SIZE < 5)
        {
            chess_case p = grid[col][i + bulb_BOARD_SIZE];
            if (p == COMPUTER || p == ENNEMY)
            {
                // Test if the piece breaks the bulb
                if (p == (chess_case)(-1 * last))
                    break;
                last = p;
                nb_pieces++;
            }
            bulb_BOARD_SIZE++;
        }
        // If we succeeded to build an non-empty 5 length bulb
        if ((bulb_BOARD_SIZE == 5) && (nb_pieces > 0))
            result += bulb_value(nb_pieces, cs, last);
    }
    h += result;
}

// Find 5 length bulbs
// in diagonal
void find_bulbs_diag(int &h, int row, int col, chess_case cs, board grid)
{
    int result = 0;

    // Last piece found in the bulb
    chess_case last = BLANK;

    // Last index for search = length of the diagonal "15 - (row + col)"
    // minus length of the bulb
    int stop_search = BOARD_SIZE - (row + col) - 4;

    int bulb_BOARD_SIZE;
    int nb_pieces;
    for (int i = 0; i < stop_search; i++) {
        // Look for a bulb starting from position i
        bulb_BOARD_SIZE = 0;
        nb_pieces = 0;
        while (bulb_BOARD_SIZE < 5)
        {
            chess_case p = grid[col + i + bulb_BOARD_SIZE][row + i + bulb_BOARD_SIZE];
            if (p == COMPUTER || p == ENNEMY)
            {
                // Test if the piece breaks the bulb
                if (p == (chess_case)(-1 * last))
                    break;
                last = p;
                nb_pieces++;
            }
            bulb_BOARD_SIZE++;
        }
        // If we succeeded to build an non-empty 5 length bulb
        if ((bulb_BOARD_SIZE == 5) && (nb_pieces > 0))
            result += bulb_value(nb_pieces, cs, last);
    }
    h += result;
}

// Find 5 length bulbs
// in counter diagonal
void find_bulbs_cdiag(int &h, int row, int col, int stop_search, chess_case cs, board grid)
{
    int result = 0;

    // Last piece found in the bulb
    chess_case last = BLANK;

    // Last index for search = length of the diagonal "(row + col + 1)"
    // minus length of the bulb
    //int stop_search = row + col + 1 - 4;

    //std::cout << "stop_search: " << stop_search << std::endl;

    int bulb_BOARD_SIZE;
    int nb_pieces;
    //std::cout << "new diag" << std::endl;
    for (int i = 0; i < stop_search; i++) {
        // Look for a bulb starting from position i
        bulb_BOARD_SIZE = 0;
        nb_pieces = 0;
        //std::cout << "***** new bulb" << std::endl;
        while (bulb_BOARD_SIZE < 5)
        {
            //std::cout << col + i + bulb_BOARD_SIZE << ", "
            //    << row - i - bulb_BOARD_SIZE << std::endl;
            chess_case p = grid[col + i + bulb_BOARD_SIZE][row - i - bulb_BOARD_SIZE];
            if (p == COMPUTER || p == ENNEMY)
            {
                // Test if the piece breaks the bulb
                if (p == (chess_case)(-1 * last))
                    break;
                last = p;
                nb_pieces++;
            }
            bulb_BOARD_SIZE++;
        }
        // If we succeeded to build an non-empty 5 length bulb
        if ((bulb_BOARD_SIZE == 5) && (nb_pieces > 0))
            result += bulb_value(nb_pieces, cs, last);
    }
    h += result;
}

