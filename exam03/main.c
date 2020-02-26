#include "minipaint.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

int	ft_error(char *str)
{
	ft_putstr(str);
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*s3;

	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	free(s1);
	return (s3);
}

int	main(int argc, char **argv)
{
	FILE	*fd;
	int	ret;
	char	*str;
	char	buf[33];

	if (argc == 2)
	{
		str = calloc(1, sizeof(char));
		if (!(fd = fopen(argv[1], "r")))
			return (ft_error("Error file\n"));
		while ((ret = fread(buf, 1, 32, fd)) > 0)
		{
			buf[ret] = '\0';
			str = ft_strjoin(str, buf);
		}
		if (ret != 0)
			return (ft_error("Read error\n"));
		return (pars(str));
	}
	else
		return (ft_error("Arguments error\n"));
	return (0);
}
