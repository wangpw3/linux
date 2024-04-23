#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

char r_buf[110];

int main(int argc, char * argv[]) {
    int fp = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(fp == 1) {
        perror("fp");
    }
    write(fp, argv[2], strlen(argv[2]));
    lseek(fp, 0, SEEK_SET);
    ssize_t n = read(fp, r_buf, 100);
    printf("n = %ld\n", n);
    printf("%s\n", r_buf);
    close(fp);
    return 0;
}   