#include "Solution.h"

int main()
{
	sudoku_sol board1("board5.txt");
	board1.board_print();
	board1.solution();
	board1.board_print();
	std::cout<<std::boolalpha<<board1.check();

}
