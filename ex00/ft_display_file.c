#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}
void	print_error(char *prog_name, char *filename)
{
	char	*base_prog;

	base_prog = basename(prog_name);
	ft_putstr_fd(base_prog, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO); /* 自动添加换行 */
}
int	main(int argc, char **argv)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	int	fd;

	if (argc < 2)
	{
		ft_putendl_fd("File name missing:", STDERR_FILENO);/* 自动换行 */
		return (1);
	}
	else if (argc > 2)
	{
		ft_putendl_fd("Too many arguments:", STDERR_FILENO);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		print_error(argv[0], argv[1]);
		return (1);
	}
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, bytes_read);/* 仍用 write 处理二进制数据 */
	if (bytes_read == -1)
		print_error(argv[0], argv[1]);
	close(fd);
	return (0);
}
