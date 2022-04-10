#include "Solution.h"



sudoku_sol::sudoku_sol()
{}

sudoku_sol::sudoku_sol(const char* str)
{
	sudoku_sol::board_fill(str);
}


void sudoku_sol::board_fill(const char* str)
{
	this->name = str;
	std::ifstream fin;
	fin.open(this->name);
	char ch;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			fin.get(ch);
			if (ch != '\n')
			{
				this->board[i][j] = ch;
				if (ch == '_')
					++this->empty;
			}
			else
				--j;
		}
	}
	fin.close();
}
	
void sudoku_sol::board_print()
{
	std::string s(37, '-');
	for (int i = 0; i < 9; ++i)
	{
		std::cout << " "<<s<<std::endl;
		for (int j = 0; j < 9; ++j)
			std::cout << " | " << this->board[i][j];
		std::cout << " |" << std::endl;
	}
	std::cout << " " << s<<std::endl;
}


bool sudoku_sol::hor(int k, char ch)
{
	for (int j = 0; j < 9; ++j)
	{
		if (ch == this->board[k][j])
			return 0;
	}
	return 1;
}

bool sudoku_sol::ver(int p, char ch)
{
	for (int i = 0; i < 9; ++i)
	{
		if (ch == this->board[i][p])
			return 0;
	}
	return 1;
}

bool sudoku_sol :: sq3(int k, int p, char ch)
{
	for (int i = k - k % 3; i < k - k % 3 + 3; i++)
	{
		for (int j = p - p % 3; j < p - p % 3 + 3; j++)
		{
			if (i != k && j != p)
			{
				if (ch == this->board[i][j])
					return 0;
			}
		}
	}
	return 1;
}


void sudoku_sol::hor_fill()
{
	for (int i = 0; i < 9; ++i)
	{
		for (char ch = '1'; ch <= '9'; ++ch)
		{
			if (hor(i, ch) == 0)
				continue;

			int s = 0, k = -1, p = -1;
			
			for (int j = 0; j < 9; ++j)
			{
				if (this->board[i][j] != '_' || ver(j, ch) == 0 || sq3(i, j, ch) == 0)
					continue;

				++s;
				k = i;
				p = j;

				if (s > 1)
					break;
			}
			if (s == 1)
			{
				this->board[k][p] = ch;
				--this->empty;
			}
		}
	}
}

void sudoku_sol::ver_fill()
{
	for (int j = 0; j < 9; ++j)
	{
		for (char ch = '1'; ch <= '9'; ++ch)
		{
			if (ver(j, ch) == 0)
				continue;

			int s = 0, k = -1, p = -1;

			for (int i = 0; i < 9; ++i)
			{
				if (this->board[i][j] != '_' || hor(i, ch) == 0 || sq3(i, j, ch) == 0)
					continue;
				
				++s;
				k = i;
				p = j;

				if (s > 1)
					break;
			}
			if (s == 1)
			{
				this->board[k][p] = ch;
				--this->empty;
			}
		}
	}
}

void sudoku_sol::sq3_fill()
{
	for (int i = 0, j=0, i_max = 3; i < 9; i+=3, i_max+=3)
	{
		for (char ch = '1'; ch <= '9'; ++ch)
		{
			/*if (hor(i, ch) == 0)
			{
				continue;
			}*/

			int j_max = 3;
			for (j = 0; j < 9; j+=3, j_max+=3)
			{
				int s = 0, k = -1, p = -1;
				if (sq3(i, j, ch) == 0 )
					continue;
				do
				{
					do
					{
						if (this->board[i][j] != '_' || ver(j, ch) == 0 || hor(i, ch) == 0)
						{
							++j;
							continue;
						}

						s++;
						k = i;
						p = j;

						if (s > 1)
						{
							j = j - j % 3 + 3;
							i = i - i % 3 + 2;
							continue;
						}
						++j;

					} while (j % 3 > 0 && j < j_max);
					j -= 3;
					++i;

				} while (i % 3 > 0 && i < i_max);
				i -= 3;
				
				if (s == 1)
				{
					this->board[k][p] = ch;
					--this->empty;
				}
			}
			
		}
	}
}

void sudoku_sol::cell_fill()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (this->board[i][j] != '_')
				continue;

			int s = 0;
			char cur_ch='_';

			for (char ch = '1'; ch <= '9'; ++ch)
			{
				if (hor(i, ch) == 0 || ver(j, ch) == 0 || sq3(i, j, ch) == 0)
					continue;
			
				s++;
				cur_ch = ch;

				if (this->method_pair)
				{
					this->p.variations_fill(i, j, ch);
					continue;
				}

				if (s > 1)
					break;
				
			}
			if (s == 1)
			{
				this->board[i][j] = cur_ch;
				--this->empty;
			}
		}
	}
	method_pair = 0;
}


void sudoku_sol::last_num()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (this->board[i][j] != '_')
				continue;

			int s = 0;
			char cur_ch;

			for (char ch = '1'; ch <= '9'; ++ch)
			{
				if (hor(i, ch)==0 || ver(j, ch)==0 || sq3(i, j, ch)==0)
					continue;

				s++;
				cur_ch = ch;

				if (s > 1)
					break;
				
			}
			if (s == 1)
			{
				this->board[i][j] = cur_ch;
				--this->empty;
			}
		}
	}
}


void sudoku_sol::solution()
{
	do
	{
		int check_empty=this->empty;
		hor_fill();
		ver_fill();
		sq3_fill(); // doesn't work
		cell_fill(); // fill vector for method of pair
		last_num();
		if (check_empty == this->empty)
		{
			if (p.pair_num == 0) // if vector of pairs is empty - fill it
			{
				// using method of pair
				this->method_pair = 1;
			}
			board_print();
			//std::cout << "no solution";
			//break;
		}
	}while (this->empty != 0);
}

bool sudoku_sol::check()
{
	this->name_sol = this->name;
	this->name_sol.insert(this->name_sol.size() - 4, "_sol");

	std::ifstream fin;
	fin.open(this->name_sol);
	char ch_sol;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			fin.get(ch_sol);
			if (ch_sol == '\n')
			{
				--j;
				continue;
			}
			if (this->board[i][j] != ch_sol)
			{
				fin.close();
				return 0;
			}
		}
	}
	
	fin.close();
	return 1;
}
