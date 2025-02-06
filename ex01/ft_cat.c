#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>
#include <libgen.h>
#include <string.h>
void	print_error(char *prog_name, char *filename);
void	process_file(char *prog_name, char *filename);
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
	ft_putendl_fd(strerror(errno), STDERR_FILENO);/* 自动添加换行 */
}
/*
void	process_file(char *prog_name, char *filename)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(prog_name, filename);
		return ;
	}
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, bytes_read); 仍用 write 处理二进制数据 
	if (bytes_read == -1)
		print_error(prog_name, filename);
	close(fd);
}*/
void	process_file(char *prog_name, char *filename)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(prog_name, filename);
		return ;
	}
	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		ft_putstr_fd(buffer, STDOUT_FILENO);
	}
	if (bytes_read == -1)
		print_error(prog_name, filename);
	close(fd);
}
int	main(int argc, char **argv)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	int	i;

	/* 无参数：读取标准输入 */
	if (argc == 1)
	{
		while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
			write(STDOUT_FILENO, buffer, bytes_read);
		/* 确保在文件读取失败时，程序不会进入死循环。
		 * 如果是从标准输入读取数据，确保在读取失败时退出循环 */
		if (bytes_read == -1)
			print_error(argv[0], "stdin");
		return (0);
	}
	/* 处理每个文件参数
	for (i = 1; i < argc; i++)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd == -1)
		{
			print_error(argv[0], argv[i], strerror(errno));
			continue ;  跳过当前文件，继续处理下一个 
		}
		while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
		{
			if (write(STDOUT_FILENO, buffer, bytes_read) == -1)
			{
				close(fd);
				return (1);
			}
		}
		if (bytes_read == -1)
			print_error(argv[0], argv[i], strerror(errno));
		close(fd);
	}*/
	for (i = 1; i < argc; i++)
		process_file(argv[0], argv[i]);
	return (0);
}
