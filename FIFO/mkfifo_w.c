/*
有名管道提供一个路径名与之关联，以FIFO的文件形式存在与文件系统中，
这样即使与FIFO的创建进程不存在亲缘关系的进程，只要可以访问路径，就
能彼此通过FIFO相互通信。
有名管道由函数mkfifo()创建，需依赖头文件
#include <sys/types.h>
#include <sys/stat.h>
函数原形：int mkfifo(const char *pathname, mode_t mode)
*/
/***************mkfifo_w.c*****************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define P_FIFO "fifo"

int main(int argc ,char **argv){
    int fd;
    if(argc < 2){
        printf("please input the write data\n");
        fd = open(P_FIFO, O_WRONLY | O_NONBLOCK);
        write(fd, argv[1], 100);
        close(fd);
        return 0;
    }
}