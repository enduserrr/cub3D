#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "libft.h"

void	strlcpy_mod(char *dst, const char *src, size_t dstsize);
char	*strjoin_mod(char *s1, char *s2, int *eol);

char	*initialize(char *stash, int *eol);
size_t	find_eol(char *line);
char	*extract(char *line, char *stash, int *eol, int fd);
char	*get_next_line(int fd);

#endif