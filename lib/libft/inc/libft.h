/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:50:15 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/21 12:10:23 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//Includes
# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<limits.h>

//Defines
///Define: Bases for a numbers
# define B10 (char *)"0123456789"
# define BL16 (char *)"0123456789abcdef"
# define BU16 (char *)"0123456789ABCDEF"

///Define: ft_strchrjoin: Type of mode
# define PREFIX	(int)0
# define SUFFIX	(int)1

//Typedefs
typedef struct s_list	t_list;
typedef struct s_gnl	t_gnl;

//Structs
///Struct: list
struct s_list
{
	void			*content;
	struct s_list	*next;
};

///Struct: gnl: struct for management of get_next_line
struct s_gnl {
	char	*buffer;
	char	*line;
	int		fd;
	int		err;
};

//Functions
///Functions: MEM
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);

///Functions: NUM
int			ft_atoi(char *str);
char		*ft_itoa(int n);
long long	ft_atoll(char *str);
size_t		ft_nbrlen_base(long long nbr, long long len);

///Functions: NUM: IS
int			ft_isnum(char *input);
int			ft_isnumdup(char **input, int num, int index);
int			ft_isint(char *num);

///Functions: CHAR: IS
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_isblank(int c);

///Functions: STR: IS
int			ft_isempty(char *str);

///Functions: CHAR: CONVERSOR
int			ft_tolower(int c);
int			ft_toupper(int c);

///Functions: STR: CONVERSOR
void		ft_strtolower(char *str);
void		ft_strtoupper(char *str);

///Functions: STR: EDIT
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
char		*ft_strchrjoin(char *str, char c, int mode);
char		*ft_strwnchr(char c, int size);

///Functions: STR: UTILS
size_t		ft_strlen(const char *s);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_strrncmp(char *s1, char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strchri(const char *s, int c);
char		*ft_strnstr(char *haystack, char *needle, size_t len);
int			ft_strnstri(char *haystack, char *needle, size_t len);

///Functions: MATRIX: UTILS
void		*ft_free(char **str, int option);
void		*ft_free_size(char **matrix, int size);
int			ft_matrixlen(char **matrix);
char		*ft_matrixjoin(char **matrix, char c);
char		*ft_matrixjoin_size(char **matrix, char c, int size);
int			ft_matrix_remainder(char **matrix, int size);
char		**ft_matrixdup(char **matrix);

///Functions: PRINT
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

///Functions: LIST
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void*));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));

///Functions: GET_NEXT_LINE
void		ft_read_file(t_gnl *gnl);
void		ft_get_line(t_gnl *gnl);
void		ft_clean_buffer(t_gnl *gnl);
char		*get_next_line(int fd);
char		*ft_malloc_strjoin(char *s1, char *s2);

///Functions: STDLIB
int			ft_close(int *fd);

#endif
