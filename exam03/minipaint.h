#ifndef MINIPAINT_H
# define MINIPAINT_H

# include <libc.h>

int	main(int argc, char **argv);
void	ft_putstr(char *str);
int 	ft_error(char *str);
float	ft_atoi(char *str, int *i);
int	ft_isdigit(char c);
int	pars(char *str);
void	algo(char **buf, char r, float width, float height, int x, int y, int largeur, int hauteur, char c);

#endif
