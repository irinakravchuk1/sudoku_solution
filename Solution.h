#pragma once
#include<iostream>
#include <string>
#include <fstream>
#include "MethodPair.h"

class sudoku_sol 
{
private:
	char board[9][9];
	int empty = 0; 
	std::string name;
	std::string name_sol;

	pair p;
	bool method_pair = 0; // if board is too hard for method ..._fill - use method of pair

	bool hor(int k, char ch);
	bool ver(int p, char ch);
	bool sq3(int k, int p, char ch);

	void hor_fill();
	void ver_fill();
	void sq3_fill();
	void cell_fill();

	void last_num();

public:
	
	sudoku_sol();
	sudoku_sol(const char* str);

	void board_fill(const char* str);
	void board_print();
	
	void solution();
	bool check();
};
