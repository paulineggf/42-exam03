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

void    algo(char **buf, int width, int height, char r, int longueur, int hauteur, int x, int y, char c)
{
    int     xb;
    int     yb;

    yb = y;
    while (yb - y <= hauteur && yb < height)
    {
        xb = x;
        while (xb - x <= longueur && xb < width)
        {
            if (xb >= 0 && yb >= 0)
            {
                if (xb == x || yb == y)
                    buf[yb][xb] = c;
                if (xb - x == longueur || yb - y == hauteur)
                    buf[yb][xb] = c;
                if ((xb - x < longueur || yb - y < hauteur) && r == 'R')
                    buf[yb][xb] = c;
            }
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
        return (ft_error("Error: argument\n", 0));
    if (!(fd = fopen(argv[1], "r")))
        return (ft_error("Error: Operation file corrupted\n", 1));
    ret = fscanf(fd, "%f %f %c\n", &width, &height, &back);
    printf("%f %f %c\n", width, height, back);
    if (ret != 3 || !(width > 0 && width <= 300) || !(height > 0 && height <= 300))
        return (ft_error("2/ Error file\n", 1));
    buf = malloc(sizeof(char*) * height);
    i = 0;
    while (i < height)
    {
        buf[i] = malloc(sizeof(char) * width);
        buf[i] = memset(buf[i], back, width);
        i++;
    }
    while ((ret = fscanf(fd, "%c %f %f %f %f %c\n", &r, &longueur, &hauteur, &x, &y, &c)) != EOF)
    {
        printf("%c %f %f %f %f %c\n", r, longueur, hauteur, x, y, c);
        if ((r != 'r' && r != 'R') || (c == 'r' || c == 'R') || ret != 6)
            return (ft_error("3/ Error file\n", 1));
        algo(buf, width, height, r, longueur - 1, hauteur - 1, x - 1, y - 1, c);
    }
    i = 0;
    while (i < height)
    {
        write(1, buf[i], width);
        write(1, "\n", 1);
        i++;
    }
    return (0);
}