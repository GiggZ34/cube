/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:24:29 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/17 14:55:50 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define PI 3.14159265359

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*previous;
}				t_list;

typedef struct	s_fd
{
	int			fd;
	char		*buff;
	int			start;
	int			end;
	struct s_fd	*next;
}				t_fd;

typedef struct	s_dot
{
	double		x;
	double		y;
	double		z;
}				t_dot;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_plane
{
	double		a;
	double		b;
	double		c;
	double		d;
	void		*add;
}				t_plane;


/*
** Function Math
*/

double			ft_abs(double n);
double			ft_min(double a, double b);
double			ft_max(double a, double b);
void			ft_sort_numbers(int *tab, int n);
t_vector		ft_create_vector(t_dot dot1, t_dot dot2);
t_vector		ft_normalize_vector(t_vector vec);
t_vector		ft_vec_norm_define(t_vector vec, double size);
t_vector		ft_rotate_vector(t_vector vec, double angle, char axis);
double			ft_dot_product(t_vector vec1, t_vector vec2);
double			ft_size_vec_plane(t_plane *plane, t_vector vec, t_dot orign);
t_dot			ft_intersect_plane_dot(t_dot origin, t_vector vec, double t);
double			ft_norm_vector_calculate(t_vector v);
double			ft_deg_to_rad(double degree);

/*
** Function Number
*/

int				ft_atoi(const char *str);
char			*ft_itoa(long n);
char			*ft_itoa_base(unsigned long nbr, char *base);
char			*ft_dechex(unsigned long dec);

/*
** Function List
*/

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclearone(t_list **lst, t_list *element, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*), int del_content);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *));
void			ft_lst_swap(t_list *a, t_list *b);

/*
** Function memory
*/

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_calloc(size_t count, size_t size);
char			*ft_realloc(char *str, int size);

void			ft_free_array(char **array);

/*
** Function char
*/

int				ft_toupper(int c);
int				ft_tolower(int c);

/*
** Function str
*/

size_t			ft_strlen(const char *s);
int				ft_strpos(const char *s, char c);
char			*ft_char_to_str(char c);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcpy(char *dst, char *src);
char			*ft_strcpypos(char *dst, char *src, int position);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strstr(char *s, char *needle);
char			*ft_strnstr(const char *s, const char *needle, size_t len);
char			*ft_str_pad(char *src, int size, char c, char direction);
char			*ft_str_repeat(const char *str, int nb);
char			*ft_str_to_lower(char *s);
char			*ft_str_to_upper(char *s);
char			*ft_substr(char const *s, int start, int len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			**ft_split(char const *s, char *c);

/*
** Function parsing
*/

int				ft_count_words(const char *s, const char *charset);

/*
** Function array
*/

int				ft_in_array(const char c, const char *charset);
int				**ft_nsplit(int *tab, int tab_size, int n);
int				ft_count_array(char **array);

/*
** Function ctype
*/

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_iswhtespace(char c);
int				ft_isupper(char c);
int				ft_islower(char c);

/*
** Function display
*/

size_t			ft_putchar_fd(char c, int fd);
size_t			ft_putstr_fd(char *s, int fd);
size_t			ft_putendl_fd(char *s, int fd);
size_t			ft_putnbr_fd(int n, int fd);
size_t			ft_putstr_repeat(char *str, size_t len, int fd);

/*
** Functions files
*/

int				get_next_line(int fd, char **line);

#endif
