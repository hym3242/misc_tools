#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tty_device> [str]\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("Failed to open TTY device");
        return 1;
    }

 if(argc==3){
        int arglen = strlen(argv[2]);
        for(int i=0;i<arglen;i++){ioctl(fd,TIOCSTI,argv[2]+i);}
        return 0;
 }

    char ch;
    while (read(STDIN_FILENO, &ch, 1) == 1) {
        ioctl(fd, TIOCSTI, &ch);
    }

    close(fd);
    return 0;
}
