#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

static char *filename = "/dev/fb0";

int main(int argc, char *argv[])
{
	int pos;
	int pixels;
	int fd;
	uint8_t *byte;

	if (argc > 1)
		pos = atoi(argv[1]);	

	if (argc > 2)
		pixels = atoi(argv[2]);

	fd = open(filename, O_RDWR);
	if (fd < 0) {
		perror("Cannot open framebuffer!\n");
		return -1;
	}

	byte = mmap(0, (128/8)*64, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(byte == MAP_FAILED) {
		perror("Failed to mmap framebuffer!");
	}	

	byte[pos] = pixels;	

	munmap(byte, (128/8)*64);
	close(fd);
	
	return 0;
}
