/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:01:19 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 11:35:40 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*ft_create_word(char const *s, char c)
{
	size_t	size;
	char	*word;

	size = 0;
	while (s[size] != c && s[size])
		size++;
	word = ft_substr(s, 0, size);
	if (!word)
		return (NULL);
	return (word);
}

static size_t	ft_word_counter(char const *s, char c)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	split = (char **)ft_calloc((ft_word_counter(s, c) + 1), sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = -1;
	while (s[++j])
	{
		while (s[j] == c && s[j + 1])
			j++;
		if (s[j] == c)
			break ;
		split[i++] = ft_create_word(&s[j], c);
		if (!split[i - 1])
			return (ft_free(split, 1));
		while (s[j] != c && s[j + 1])
			j++;
	}
	return (split);
}
