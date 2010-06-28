// =====================================================================================
//
//       Filename:  load.cc
//
//    Description:
//
//        Version:  1.0
//        Created:  05/27/2010 11:24:41 PM
//       Revision:  none
//       Compiler:  g++
//
//         Auth||:  GASPARINA Damien (http://lamada.eu), gaspar_d@epita.fr
//        Company:  Epita
//
// =====================================================================================

#include        "load.h"

using namespace std;

board load_from_file(char* filename) {
    ifstream file(filename);
    if (file) {
        string line;
        board grid = new chess_case*[BOARD_SIZE];
        int x=0;
        unsigned int y;
        while(file >> line && x < BOARD_SIZE) {
            grid[x] = new chess_case[BOARD_SIZE];
            for (y = 0; y < line.length(); y++) {
                switch (line[y]) {
                    case '0':
                        grid[x][y] = BLANK;
                        break;
                    case '1':
                        grid[x][y] = COMPUTER;
                        break;
                    case '2':
                        grid[x][y] = ENNEMY;
                        break;
                }
            }
            x++;
        }
        if (x != BOARD_SIZE)
            cerr << "Load_from_file: Bad BOARD_SIZE of the file, hope it's ok\n";
        return grid;
    }
    else
        throw int(127);
}
