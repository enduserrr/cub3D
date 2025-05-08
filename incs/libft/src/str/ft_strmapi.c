#include "../../incs/libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*newstr;

	i = 0;
	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	newstr = ft_calloc(len + 1, sizeof(char));
	if (!newstr)
		return (0);
	while (i < len)
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}
