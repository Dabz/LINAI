#include "display.h"
using namespace std;

void print_board(board grid)
{
  std::cout << "\t    ";
  for (int i=0; i<BOARD_SIZE; i++)
    std::cout << (i%10) << "  ";
  
  string header(BOARD_SIZE * 3 + 2,'-');
  cout << "\n\t  " << header << '\n';
  for (int i=0; i<BOARD_SIZE; i++) {
    cout << "\t" << (i%10) <<" |";
    for (int j=0; j<BOARD_SIZE; j++) {
      if (grid[i][j] == COMPUTER)
	cout << " X ";
      else if (grid[i][j] == ENNEMY)
	cout << " O ";
      else
	cout << " - ";
    }
    cout << "|\n";
  }
  cout << "\t  " << header << '\n';
}
