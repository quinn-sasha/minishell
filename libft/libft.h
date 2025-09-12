/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:54:19 by squinn            #+#    #+#             */
/*   Updated: 2025/09/12 17:42:23 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# define TRUE 1
# define FALSE 0
# define NOT_FOUND -1

# define STDOUT 1
# define MAX_ADDRESS_LENGTH 16
# define SINGLE_PERCENT_ERROR 1
# define LETTER 2
# define STRING 3
# define POINTER 4
# define INTEGER 5
# define UNSIGNED_INTEGER 6
# define LOWER_HEX 7
# define UPPER_HEX 8
# define PERCENT 9
# define UNKNOWN_CONVERSION_TYPE 10

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *str, const char *find, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_atoi_base(char *str, const char *base_numbers);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

void	*ft_calloc(size_t nmeb, size_t size);
char	*ft_strdup(const char *s);

char	*ft_substr(char const *s, int start, int last);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	*free_words(char **words);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(const char *str, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int num, int fd);

// get_next_line
char	*get_next_line(int fd);

// ft_printf
int		ft_printf(const char *format, ...);
int		ft_vprintf(const char *format, va_list args);
int		print_by_conversion_type(int type, va_list args, char specifier);
int		determine_conversion_type(char letter);
int		ft_putchar(char c);
int		print_specifier(char specifier);
int		ft_putstr(const char *str);
int		print_address(const void *address);
char	*unsigned_itoa(unsigned long long num, unsigned int base);
int		ft_putnbr(int num);
int		print_unsigned_decimal(unsigned int n);
int		print_hexadecimal(unsigned int n, int is_upper);
// ft_dprintf_utils.c
int		print_address_fd(int fd, const void *address);
int		print_unsigned_decimal_fd(int fd, unsigned int n);
int		print_hexadecimal_fd(int fd, unsigned int n, int is_upper);
// ft_dprintf.c
int		print_specifier_fd(int fd, char specifier);
int		print_by_conversion_type_fd(int fd, int type, va_list args,
			char specifier);
int		ft_vdprintf(int fd, const char *format, va_list args);
int		ft_dprintf(int fd, const char *format, ...);

#endif
