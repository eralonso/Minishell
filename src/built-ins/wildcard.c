/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:22:48 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/29 15:27:44 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

char	**get_wildcard(char *directory)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**names;
	int				num_entries;

	num_entries = ft_count_dir(directory);
	if (num_entries == -1)
		return (NULL);
	names = ft_calloc(sizeof(char *), num_entries + 1);
	if (!names)
		return (NULL);
	(1 && (dir = opendir(directory)) && (num_entries = 0));
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			names[num_entries] = ft_strdup(entry->d_name);
			if (!names[num_entries++])
				return (ft_free(names, (closedir(dir) || 1)));
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (names);
}

int	ft_count_dir(char *directory)
{
	int				num_entries;
	struct dirent	*entry;
	DIR				*dir;

	num_entries = 0;
	dir = opendir(directory);
	if (dir == NULL)
	{
		perror("opendir");
		return (-1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			num_entries++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (num_entries);
}
