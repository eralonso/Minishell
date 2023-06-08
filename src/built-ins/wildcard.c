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

char	**get_wildcard(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**names;
	int				num_entries;

	dir = opendir(".");
	names = malloc(sizeof(char *) * ft_count_dir(dir));
	entry = readdir(dir);
	num_entries = 0;
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			num_entries++;
			names[num_entries - 1] = ft_strdup(entry->d_name);
			if (!names[num_entries - 1])
				return (ft_free(names, (closedir(dir) || 1)));
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (names);
}

int	ft_count_dir(DIR *dir)
{
	int				num_entries;
	struct dirent	*entry;

	num_entries = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (0);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		num_entries++;
		readdir(dir);
		entry = readdir(dir);
	}
	return (num_entries);
}
