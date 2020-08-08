#include <libc.h>

int     ft_strlen(char *str)
{
    int     i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

int     ft_error(char *str, int nb)
{
    write(1, str, ft_strlen(str));
    return (nb);
}

int     in_rectangle(float xb, float x, float yb, float y, float longueur, float hauteur)
{
	if (xb < x || x + longueur < xb
		|| yb < y || y + hauteur < yb)
		return (0);
	if ((xb - x < 1 || (x + longueur) - xb < 1 ||
	yb - y < 1 || (y + hauteur) - yb < 1))
		return (2);
	return (1);
}

void    algo(char **buf, int width, int height, char r, float x, float y, float longueur, float hauteur, char c)
{
    int     xb;
    int     yb;
    int     ret;

    yb = 0;
    while (yb < height)
    {
        xb = 0;
        while (xb < width)
        {
            ret = in_rectangle(xb, x, yb, y, longueur, hauteur);
            if ((ret == 2 && r == 'r') || (ret && r == 'R'))
                buf[yb][xb] = c;
            xb++;
        }
        yb++;
    }
}

int     main(int argc, char ** argv)
{
    FILE    *fd;
    float   width;
    float   height;
    char    back;
    char    r;
    float   longueur;  
    float   hauteur;
    float   x;
    float   y;
    char    c;
    int     ret;
    char    **buf;
    int     i;

    if (argc != 2)
        return (ft_error("Error: argument\n", 1));
    if (!(fd = fopen(argv[1], "r")))
        return (ft_error("Error: Operation file corrupted\n", 1));
    ret = fscanf(fd, "%f %f %c\n", &width, &height, &back);
    if (ret != 3 || !(width > 0 && width <= 300) || !(height > 0 && height <= 300))
        return (ft_error("Error: Operation file corrupted\n", 1));
    buf = malloc(sizeof(char*) * height);
    i = 0;
    while (i < height)
    {
        buf[i] = malloc(sizeof(char) * width);
        buf[i] = memset(buf[i], back, width);
        i++;
    }
    while ((ret = fscanf(fd, "%c %f %f %f %f %c\n", &r, &x, &y, &longueur, &hauteur, &c)) != EOF)
    {
        if ((r != 'r' && r != 'R') || longueur <= 0 || hauteur <= 0 || ret != 6)
            return (ft_error("Error: Operation file corrupted\n", 1));
        algo(buf, width, height, r, x, y, longueur, hauteur, c);
    }
    i = 0;
    while (i < height)
    {
        write(1, buf[i], width);
        free(buf[i]);
        write(1, "\n", 1);
        i++;
    }
    free(buf);
    fclose(fd);
    return (0);
}