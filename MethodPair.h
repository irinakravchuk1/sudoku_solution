#pragma once
#include<vector>


struct cell
{
	int i, j;
	std::vector<char> ch;
};

class pair
{
private: 
	std::vector<cell> num_variations;
	std::vector<std::vector<cell>> pairs;
	

	

	bool sq3(int in, int jn);
	bool hor(int in, int jn);
	bool ver(int in, int jn);

	bool same_cell(int in, int jn);

	void trivial_pair();

	void del_num(); // if there is pair in hor/ver/sq3 - delete vars of pair from another cells

	// if some num was deleted from the cell - it num has't check in ..._fill

	// if in vector ch only 1 var = board[][]=ch

	// if (board[][]=ch) - delete from num_variations this cell

public:
	pair() {};
	int pair_num = pairs.size(); // number of pairs

	void variations_fill(int i, int j, char ch);
};
