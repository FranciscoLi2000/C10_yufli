#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
void	print_error(char *prog_name, char *filename);
void	process_file(char *prog_name, char *filename, long n);
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
int	ft_strcmp(char const *s1, char const *s2)
{
	int	i;

	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
void	print_error(char *prog_name, char *filename)
{
	char	*base_prog;
	char	*error_msg;

	base_prog = basename(prog_name);
	error_msg = strerror(errno);
	write(2, base_prog, ft_strlen(base_prog));
	write(2, ": ", 2);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
}
/* 模拟 lseek 的行为 */
off_t	ft_lseek(int fd, off_t offset)
{
	char	buffer[1];
	off_t	pos;

	pos = 0;
	while (pos < offset)
	{
		if (read(fd, buffer, 1) != 1)
			return (-1);
		pos++;
	}
	return (pos);
}
void	process_file(char *prog_name, char *filename, long n)
{
	char	buffer[1];
	int	fd;
	off_t	file_size;
	off_t	start_pos;
	/* 1. 打开文件并检查错误 */
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(prog_name, filename);
		return ;
	}
	/* 2. 获取文件总大小 */
	file_size = 0;
	while (read(fd, buffer, 1) == 1)
		file_size++;
	/* 3. 计算起始位置 */
	if (file_size > n)
		start_pos = file_size - n;
	else
		start_pos = 0;
	/* 4. 重新打开文件并定位到起始位置 */
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(prog_name, filename);
		return ;
	}
	if (ft_lseek(fd, start_pos) == -1)
	{
		print_error(prog_name, filename);
		close(fd);
		return ;
	}
	/* 5. 读取从 start_pos 到文件末尾的数据 */
	while (read(fd, buffer, 1) == 1)
		write(STDOUT_FILENO, buffer, 1);
	close(fd);
}
int	main(int argc, char **argv)
{
	long	n;
	int	i;

	if (argc < 4 || ft_strcmp(argv[1], "-c") != 0)
	{
		write(2, "Usage: ft_tail -c <bytes> <file1> <file2> ...\n", 45);
		return (1);
	}
	n = atol(argv[2]);
	if (n <= 0)
	{
		write(2, "Error: Invalid byte count\n", 26);
		return (1);
	}
	i = 3;
	while (i < argc)
	{
		process_file(argv[0], argv[i], n);
		i++;
	}
	return (0);
}
