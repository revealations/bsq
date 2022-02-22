#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	ft_filesize(char *argv)
{
	int	size;
	char	buf;
	int	fd;

	size = 0;
	fd = open(argv, O_RDONLY);
	while (read(fd, &buf, 1))
		size++;
	close(fd);
	return (size);
}

int	ft_filecol(char *argv)
{
	int	col;
	char	*buf;
	int	fd;
	int	i;
	int	size;

	size = ft_filesize(argv);
	buf = (char *)malloc(sizeof(char) * size + 1);
	if (buf == NULL)
		return (0);
	i = 0;
	col = 0;
	if ((fd = open(argv, O_RDONLY) == -1))
		return (0);
	read(fd, buf, size);
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			break;
		col++;
		i++;
	}
	free(buf);
	close(fd);
	return (col + 1);
}

int	ft_filerow(char *argv)
{
	int	row;
	char	*buf;
	int	fd;
	int	i;
	int	size;
	
	size = ft_filesize(argv);
	buf = (char *)malloc(sizeof(char) * size + 1);
	if (buf == NULL)
		return (0);
	row = 0;
	i = 0;
	if ((fd = open(argv, O_RDONLY) == -1))
		return (0);
	read(fd, buf, size);
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			row++;
		i++;
	}
	free(buf);
	close(fd);
	return (row + 1);
}

void	ft_filetobuf(char **buf, int row, int col, char *argv)
{
	char	*c;
	int	i;
	int	j;
	int	fd;
	int	count;

	count = 0;
	j = 0;
	if ((fd = open(argv, O_RDONLY) == -1))
		return ;
	read (fd, c, ft_filesize(argv));
	while (i < ft_filesize(argv))
	{
		i = 0;
		while (c[count] != '\n')
		{
			buf[j][i] = c[count];
			count++;
			i++;
		}
		count++;
		j++;
	}
	close (fd);
}

char	**ft_read_file(char *argv)
{
	int	fd;
	char	**buf;
	int	row;
	int	col;
	int	i;
	
	col = ft_filecol(argv);
	row = ft_filerow(argv);
	if ((fd = open(argv, O_RDONLY) == -1))
		return (0);
	buf = (char**)malloc(sizeof(char*) * row);
	if (buf == NULL)
		return NULL;
	while (row > i)
	{
		buf[i] = (char*)malloc(sizeof(char) * col + 1);
		if (buf[i] == NULL)
			return NULL;
		i++;
	}
	ft_filetobuf(buf, row, col, argv);
	close (fd);
	return (buf);
}
