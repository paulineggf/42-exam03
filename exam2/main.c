#include "minipaint.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	return (s3);
}

int	main(int argc, char **argv)
{
	FILE	*fd;
	int	ret;
	char	buf[33];
	char	*str;

	if (argc == 2)
	{
		fd = fopen(argv[1], "r");
		if (fd == NULL)
			return (ft_error("Error\n"));
		str = calloc(1, sizeof(char));
		while ((ret = fread(buf, 1, 32, fd)) > 0)
		{
			buf[ret] = '\0';
			str = ft_strjoin(str, buf);
		}
		if (ret != 0)
			return (ft_error("Error\n"));
		return (pars(str));
	}
	else
		return (ft_error("Error\n"));
	return (0);
}
