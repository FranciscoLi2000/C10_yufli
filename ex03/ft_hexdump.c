#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
void	print_error(char *prog_name, char *filename);
void	process_file(char *prog_name, char *filename);
void	ft_hexdump(int fd);
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
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
void	process_file(char *prog_name, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(prog_name, filename);
		return ;
	}
	ft_hexdump(fd);
	close(fd);
}
/* 格式化输出十六进制和 ASCII */
void	ft_hexdump(int fd)
{
	unsigned char	buffer[16];
	char		addr_str[9];
	char		hex[3];
	ssize_t		bytes_read;
	unsigned long	address;
	int		i;

	address = 0;
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		/* 输出地址 */
		snprintf(addr_str, sizeof(addr_str), "%08lx", address);
		write(1, addr_str, 8);
		write(1, "  ", 2);
		/* 输出十六进制部分 */
		i = 0;
		while (i < 16)
		{
			if (i < bytes_read)
			{
				snprintf(hex, sizeof(hex), "%02x", buffer[i]);
				write(1, hex, 2);
			}
			else
				write(1, "  ", 2);  /* 不足16字节用空格填充 */
			if (i == 7)
				write(1, " ", 1);  /* 每8字节加空格 */
			write(1, " ", 1);
			i++;
		}
		/* 输出ASCII部分 */
		write(1, " |", 2);
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] >= 32 && buffer[i] <= 126)
				write(1, &buffer[i], 1);
			else
				write(1, ".", 1);
			i++;
		}
		write(1, "|\n", 2);
		address += 16;
	}
}
int	main(int argc, char **argv)
{
	char	*prog_name;
	int	i;

	if (argc < 2)
	{
		prog_name = basename(argv[0]);
		write(2, prog_name, ft_strlen(prog_name));
		write(2, ": No file specified\n", 20);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		process_file(argv[0], argv[i]);
		i++;
	}
	return (0);
}
