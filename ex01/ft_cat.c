#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>
#include <libgen.h>
#include <string.h>

#define BUFFER_SIZE 1024  /* 固定缓冲区大小，小于30KB */
static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
void	print_error(char *prog_name, char *file, char *error_msg)
{
	char	*base_prog;

	base_prog = basename(prog_name);
	write(2, base_prog, ft_strlen(base_prog));
	write(2, ": ", 2);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, error_msg, strlen(error_msg));
	write(2, "\n", 1);
}
int	main(int argc, char **argv)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int	i;
	int	fd;
	/* 无参数：读取标准输入 */
	if (argc == 1)
	{
		while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
		{
			if (write(STDOUT_FILENO, buffer, bytes_read) == -1)
				return (1);  /* 写入失败时退出程序 */
		}
		/* 确保在文件读取失败时，程序不会进入死循环。
		 * 如果是从标准输入读取数据，确保在读取失败时退出循环 */
		if (bytes_read == -1)
			print_error(argv[0], "stdin", strerror(errno));
		return (0);
	}
	/* 处理每个文件参数 */
	for (i = 1; i < argc; i++)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd == -1)
		{
			print_error(argv[0], argv[i], strerror(errno));
			continue ; /* 跳过当前文件，继续处理下一个 */
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
	}
	return (0);
}
