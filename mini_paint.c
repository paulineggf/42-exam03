#include <libc.h>
#include <math.h>

int     ft_strlen(char *str)
{
    int     i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}

int     ft_error(char *str)
{
    write(1, str, ft_strlen(str));
    return (1);
}

void    algo(char **buf, int width, int height, char v, float x, float y, float rayon, char c)
{
    float xb;
    float yb;
    float res;

    yb = 0;
    while (yb < height)
    {
        xb = 0;
        while (xb < width)
        {
            if (xb >= 0 && yb >= 0)
            {
                res = sqrtf(((x - xb) * (x - xb)) + ((y - yb) * (y - yb)));
                if (res <= rayon && v == 'C')
                    buf[(int)yb][(int)xb] = c;
                if (rayon - res < 1 && res <= rayon && v == 'c')
                    buf[(int)yb][(int)xb] = c;
            }
            xb++;
        }
        yb++;
    }
}

int     main(int argc, char **argv)
{
    FILE    *fd;
    float   width;
    float   height;
    char    back;
    char    v;
    float   x;
    float   y;
    float   rayon;
    char    c;
    char    **buf;
    int     ret;

    if (argc != 2)
        return (ft_error("Error: argument\n"));
    if (!(fd = fopen(argv[1], "r")))
        return (ft_error("Error: Operation file corrupted\n"));
    ret = fscanf(fd, "%f %f %c\n", &width, &height, &back);
    if (ret != 3 || !(width > 0 && width <= 300) || !(height > 0 && height <= 300))
        return (ft_error("Error: Operation file corrupted\n"));
    buf = malloc(sizeof(char*) * height);
    int i;
    i = 0;
    while (i < height)
    {
        buf[i] = malloc(sizeof(char) * width);
        buf[i] = memset(buf[i], back, width);
        i++;
    }
    while ((ret = fscanf(fd, "%c %f %f %f %c\n", &v, &x, &y, &rayon, &c)) != EOF)
    {
        if (ret != 5 || !(v == 'C' || v == 'c') || rayon <= 0)
            return (ft_error("Error: Operation file corrupted\n"));
        algo(buf, width, height, v, x, y, rayon, c);
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