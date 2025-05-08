#include "../../incs/libft.h"

static char	*ft_char(char *s, int number, long int len)
{
	while (number > 0)
	{
		s[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (s);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*res;
	long int	len;

	len = ft_len(n);
	res = ft_calloc(len + 1, sizeof(char));
	if (!(res))
		return (0);
	res[len--] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		n = -n;
		res[0] = '-';
	}
	res = ft_char(res, n, len);
	return (res);
}
