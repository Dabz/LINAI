#include "game_shell.h"

namespace
{
    chess_case sub_has_won(int i, int j, int& align, const board grid, chess_case& player) {
        if (align >= 5 ) {
            return player;
        }
        if ( i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE ) {
            if (grid[i][j] != COMPUTER && grid[i][j] != ENNEMY) {
                align = 0;
            }
            else if (align == 0 || grid[i][j] != player) {
                player = grid[i][j];
                align = 1;
            }
            else {
                align += 1;
            }
        }
        return BLANK;
    }
}


chess_case has_won(const board grid)
{
    int i,j,z;
    int align_horizontal = 0;
    int align_vertical = 0;
    int align_diag1 = 0;
    int align_diag2 = 0;
    chess_case player_horizontal = grid[0][0];
    chess_case player_vertical = grid[0][0];
    chess_case player_diag1 = grid[0][0];
    chess_case player_diag2 = grid[0][0];

    chess_case tmp;

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {

            // Check for horizontal line
            tmp = sub_has_won(i,j,align_horizontal,grid,player_horizontal);
            if (tmp != BLANK)
                return tmp;

            // Check for vertical line
            tmp = sub_has_won(j,i,align_vertical,grid,player_vertical);
            if (tmp != BLANK)
                return tmp;

            // Check for diagonal
            for (z = 0; z < BOARD_SIZE; z++) {
                tmp = sub_has_won(i+z, j+z,align_diag1,grid,player_diag1);
                if (tmp != BLANK)
                    return tmp;
                tmp = sub_has_won(i+z,j-z,align_diag2,grid,player_diag2);
                if (tmp != BLANK)
                    return tmp;
            }
        }
    }
    return BLANK;
}

void start_game(player_type p1, player_type p2)
{
  std::cout << "\nGAME START:\n";

  board grid = board_create_empty();
  tree_node tmp, tree_grid;
  tree_grid.father = NULL;
  main_board_change(grid);

  player_type pt = p1;
  chess_case color = COMPUTER;
  clock_t before, after;
  int player = 1;
  int x,y;
  pos p;

  do {
    print_board(grid);
    before = clock();

    if (pt == HUM) {
      std::cout << "Player "
                << player
                << " (human) turn:\n";
      do {
	std::cout << "X: ";
	std::cin >> x;
	std::cout << "Y: ";
	std::cin >> y;
	p.x = x;
	p.y = y;
      } while ((grid[x][y] != BLANK) || !special_rules(grid, p));
    }
    else {
      std::cout << "Player "
                << player
                 << " (computer) turn:\n";
      tmp = alpha_beta(DEPTH, grid, color);
      x = tmp.move.x;
      y = tmp.move.y;
      std::cout << "X: " << x << std::endl
                << "Y: " << y << std::endl;
    }

    //Move parameters
    std::cout << "-------------------------\n"
              << "Heuristic before: " << heuristic(color, grid) << std::endl;
    grid[x][y] = color;
    after = clock();
    std::cout << "Heuristic after: " << heuristic(color, grid) << std::endl
              << "Time Elapsed: " << (double)(after - before) / CLOCKS_PER_SEC
              << "\n-------------------------\n";

    //Switch the player
    if (player == 1) {
      player = 2;
      pt = p2;
    }
    else {
      player = 1;
      pt = p1;
    }
    color = (chess_case) (color * -1);
  } while (has_won(grid) == BLANK);

  print_board(grid);
  std::cout << "Game over" << std::endl;
}
