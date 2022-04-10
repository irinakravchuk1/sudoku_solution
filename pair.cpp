#include "MethodPair.h"
#include <math.h>

void pair::variations_fill(int i, int j, char ch)
{
	for (int in = 0; in < this->num_variations.size(); ++in)
	{
		if (this->num_variations[in].i == i && this->num_variations[in].j == j) // if cell[i][j] already exxists - add new char 
		{
			this->num_variations[in].ch.push_back(ch);
			return;
		}
	}

	cell c;
	c.i = i;
	c.j = j;
	c.ch.push_back(ch);
	this->num_variations.push_back(c);
}


bool pair::sq3(int in, int jn)
{
	int i1, i2, j1, j2;
	i1 = std::max(this->pairs[jn][1].i, this->num_variations[in].i);
	i2 = std::min(this->pairs[jn][1].i, this->num_variations[in].i);
	j1 = std::max(this->pairs[jn][1].j, this->num_variations[in].j);
	j2 = std::min(this->pairs[jn][1].j, this->num_variations[in].j);

	if ((i1-i2)<3 && (j1-j2)<3 && ((i1%3-i2%3)>=0 || (j1 % 3 - j2 % 3) >= 0))
		return 1;

	return 0;
}

bool pair::hor(int in, int jn)
{
	return (this->pairs[jn][1].i == this->num_variations[in].i);
}

bool pair::ver(int in, int jn)
{
	return (this->pairs[jn][1].j == this->num_variations[in].j);
}


bool pair::same_cell(int in, int jn)
{
	if (this->pairs[jn][0].ch[0] != this->num_variations[in].ch[0] || this->pairs[jn][0].ch[1] != this->num_variations[in].ch[1])
		return 0;

	bool hor, ver;
	hor = (this->pairs[jn][1].i == this->num_variations[in].i);
	ver = (this->pairs[jn][1].j == this->num_variations[in].j);

	if (hor || ver || sq3(in, jn))
		return 1;

	return 0;
}


void pair::trivial_pair()
{
	for (int in = 0; in < this->num_variations.size(); ++in)
	{
		if (this->num_variations[in].ch.size() != 2) // if cell conteins more then 2 vars - next cell
			continue;
		
		for (int jn = 0; jn < this->pairs.size(); ++jn)
		{
			if (same_cell(in, jn))
			{
				this->pairs[jn].push_back(this->num_variations[in]); // if there is the same cell - push back the second val
				continue;
			}
		
			this->pairs[this->pairs.size()].push_back(this->num_variations[in]); // if there is no same cell - create new 
		}
	}

}


void pair::del_num()
{

}
