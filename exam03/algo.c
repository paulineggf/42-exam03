#include "minipaint.h"

void	algo(char **buf, char r, float width, float height, int x, int y, int largeur, int hauteur, char c)
{
	int	xb;
	int	yb;

	yb = y;
	while (yb - y <= hauteur && yb < height)
	{
		xb = x;
		while (xb - x <= largeur && xb < width)
		{
			if (xb >= 0 && yb >= 0)
			{
				if (xb == x || yb == y)
					buf[yb][xb] = c;
				if (xb - x == largeur || yb - y == hauteur)
					buf[yb][xb] = c;
				if (r == 'R' && xb - x < largeur && yb - y  < hauteur)
					buf[yb][xb] = c;
			}
			xb++;
		}
		yb++;
	}
}
