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
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strncmp(entry->d_name, ".", ft_strlen(entry->d_name)) \
		!= 0 && ft_strncmp(entry->d_name, "..", ft_strlen(entry->d_name)) \
		!= 0)
		{
			printf("entry name:%s:\n", entry->d_name);
			num_entries++;
			names[num_entries - 1] = strdup(entry->d_name);
			if (!names[num_entries - 1])
				return (NULL);
				//(NULL && closedir(dir) || ft_free(names, 1));
			readdir(dir);
		}
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
	while ((entry = readdir(dir)) != NULL)
	{
		num_entries++;
		readdir(dir);
	}
	return (num_entries);
}
