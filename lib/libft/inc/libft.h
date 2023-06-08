/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:50:15 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/08 17:15:27 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<limits.h>

# define B10 (char *)"0123456789"
# define BL16 (char *)"0123456789abcdef"
# define BU16 (char *)"0123456789ABCDEF"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_gnl {
	char	*buffer;
	char	*line;
	int		fd;
	int		err;
}			t_gnl;

//MEM
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);

//NUM
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
long long	ft_atoll(char *str);
size_t		ft_nbrlen_base(long long nbr, long long len);

//IS: NUM
int			ft_isnum(char *input);
int			ft_isnumdup(char **input, int num, int index);
int			ft_isint(char *num);

//IS: CHAR
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);

//CHAR: CONVERSOR
int			ft_tolower(int c);
int			ft_toupper(int c);

//STR: EDIT
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtrim(char *s1, char *set);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_strcat(char *dst, const char *src);

//STR: UTILS
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strrncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strchri(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle,
				size_t len);

//MATRIX: UTILS
void		*ft_free(char **str, int option);
int			ft_matrixlen(char **matrix);

//PRINT
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

//LIST
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void*));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));

//GET_NEXT_LINE
void		ft_read_file(t_gnl *gnl);
void		ft_get_line(t_gnl *gnl);
void		ft_clean_buffer(t_gnl *gnl);
char		*get_next_line(int fd);
char		*ft_malloc_strjoin(char *s1, char *s2);

//STDLIB
int			ft_close(int *fd);

#endif
