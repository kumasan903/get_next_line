#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char	*get_next_line(int fd);

int main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("gnl_return -> %s%%\n", get_next_line(fd));
	printf("gnl_return -> %s%%\n", get_next_line(fd));
	printf("gnl_return -> %s%%\n", get_next_line(fd));
	close(fd);
}
