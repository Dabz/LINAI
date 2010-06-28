// =====================================================================================
//
//       Filename:  main.cc
//
//    Description:
//
//        Version:  1.0
//        Created:  05/26/2010 04:52:08 PM
//       Revision:  none
//       Compiler:  g++
//
//         Auth||:  GASPARINA Damien (http://lamada.eu), gaspar_d@epita.fr
//        Company:  Epita
//
// =====================================================================================

#include	<cstdlib>
#include        <cstring>
#include        <iostream>
#include        "data.h"
#include        "load.h"
#include        "heuristic.h"
#include        "alpha_beta.h"
#include        "display.h"
#include        "game_shell.h"
#include		"interface.h"

void test(int x, int y, board grid)
{
    char case_ = '-';
    if (grid[x][y] == ENNEMY)
        case_ = 'O';
    else if (grid[x][y] == COMPUTER)
        case_ = 'X';

    std::cout << "heuristic in " << x << ", " << y << "\n";
    std::cout << "Case is " << case_ << "\n";
    std::cout << "Result: " << value_zone(x, y, grid) << '\n';
}

int main ( int argc, char *argv[] )
{
    if (argc == 4 && !strcmp(argv[1], "client")) {
        std::cout << "Client started\n";
        launch_client(argv[2], atoi(argv[3]));
    }
    else if (argc == 3 && !strcmp(argv[1], "heuristic")) {
        // Print the heuristic of a board in a file (giving as argument)
        board grid = load_from_file(argv[2]);
        std::cout << "Board\n";
        print_board(grid);
        std::cout  << "Heuristic: "
                    << heuristic(COMPUTER, grid)
                    << std::endl;
    }
    else if (argc == 2 && !strcmp(argv[1], "play")) {
      int type;
      std::cout << "Which kind of game do you want ?:\n"
                << "1: Computer vs Computer\n"
                << "2: Human vs Computer\n"
                << "3: Human vs Human\n"
                << "Game type : ";
      std::cin >> type;
      switch (type) {
      case 1:
        start_game(CPU, CPU);
        break;
      case 2:
        start_game(CPU, HUM);
        break;
      case 3:
        start_game(HUM, HUM);
        break;
      default:
        std::cout << "Invalid number.\n";
        break;
      }
    }
    else if (argc == 3 && !strcmp(argv[1], "alpha_beta")) {
        board grid = load_from_file(argv[2]);
        main_board_change(grid);
        tree_node foo;
        foo.father = NULL;

        foo.h = heuristic(COMPUTER,grid);
        std::cout << "||iginal board\n";
        print_board(grid);
        std::cout << "Next board\n";
        tree_node tmp = alpha_beta(DEPTH, grid, COMPUTER);
        grid[tmp.move.x][tmp.move.y] = COMPUTER;
        print_board(grid);
    }
    else if (argc == 3 && !strcmp(argv[1], "successors")) {
        board grid = load_from_file(argv[2]);
        tree_node foo;
        foo.father = NULL;
        main_board_change(grid);
        foo.h = heuristic(COMPUTER,grid);
        successors x = get_successors(ENNEMY, grid);
        successors::iterator it;
        int i = 0;
        for(it = x.begin(); it != x.end(); it++) {
            std::cout << "X :" << it->move.x << std::endl
                      << "Y :" << it->move.y << std::endl
                      << "Heuristic: " << it->h << std::endl;
            i++;
        }
        std::cout << i << " successors found.\n";
    }
    else if (argc == 3 && !strcmp(argv[1], "result")) {
        std::cout << "Board" << std::endl;
        board grid = load_from_file(argv[2]);
        print_board(grid);
        chess_case tmp = has_won(grid);
        if (tmp) {
            if (tmp == COMPUTER)
                std::cout << "Computer has won" << std::endl;
            else
                std::cout << "Ennemy has won" << std::endl;
        }
        else
            std::cout << "No one has won" << std::endl;
    }
    else {
        std::cout << "Usage:\n------------\n"
                  << "gobang client <server> <port> : launch the server\n"
                  << "gobang play : start a game in the shell\n"
                  << "gobang heuristic <file> : print the heuristic of the file\n"
                  << "gobang alpha_beta <file> : print alpha beta of the file\n"
                  << "gobang successors <file> : print successors board\n";
    }
    return EXIT_SUCCESS;
}
