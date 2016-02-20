#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int file = open("/dev/khalebiosdriver", O_RDWR);
	
	if(file < 0)
	{
		perror("open");
		exit(errno);
	}
	char *s = "une commande";
	write (file, s, strlen(s));
	
	
	close(file);
	
	return 0;
}
