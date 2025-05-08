#include "../../incs/ft_printf.h"

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (s[count])
		count++;
	if (write(1, s, count) == -1)
		return (-1);
	return (count);
}

int	ft_print_dg(long long int n, char *base)
{
	int	count;
	int	count2;
	int	base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	if (n < 0)
	{
		if (ft_print_char('-') == -1)
			return (-1);
		return (ft_print_dg(-n, base) + 1);
	}
	else if (n < base_len)
		return (ft_print_char(base[n]));
	else
	{
		count = ft_print_dg(n / base_len, base);
		if (count == -1)
			return (-1);
		count2 = ft_print_dg(n % base_len, base);
		if (count2 == -1)
			return (-1);
		return (count + count2);
	}
}

int	ft_print_uint(unsigned long n, char *base)
{
	int	count;
	int	base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	if (n < (unsigned long)base_len)
		return (ft_print_char(base[n]));
	else
	{
		count = ft_print_dg(n / base_len, base);
		return (count + ft_print_dg(n % base_len, base));
	}
}

int	ft_print_ptr(size_t ptr)
{
	size_t	value;
	int		count;
	int		tmp;
	char	*base;

	base = "0123456789abcdef";
	tmp = 0;
	value = (size_t)ptr;
	tmp = write (1, "0x", 2);
	if (tmp == -1)
		return (-1);
	count = ft_print_uint(value, base);
	return (count + 2);
}
