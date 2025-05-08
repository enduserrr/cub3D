#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

int	ft_print_char(int c);
int	ft_print_str(char *s);
int	ft_print_dg(long long int n, char *base);
int	ft_print_uint(unsigned long n, char *base);
int	ft_print_ptr(size_t ptr);
int	ft_find_format(char type, va_list ap, int temp);
int	ft_printf(const char *format, ...);

#endif