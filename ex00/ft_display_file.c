#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
int	main(int argc, char **argv)
{
	char	buffer[1024];
	size_t	bytes_read;
	int	fd;

	if (argc < 2)
	{
		write(2, "File name missing.\n", 19);
		return (1);
	}
	else if (argc > 2)
	{
		write(2, "Too many arguments.\n", 20);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		if (write(1, buffer, bytes_read) == -1)
		{
			close(fd);
			return (1);
		}
	}
	if (bytes_read == -1)
	{
		write(2, "Cannot read file.\n", 18);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
