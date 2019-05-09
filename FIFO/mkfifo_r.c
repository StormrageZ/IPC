/*
有名管道提供一个路径名与之关联，以FIFO的文件形式存在与文件系统中，
这样即使与FIFO的创建进程不存在亲缘关系的进程，只要可以访问路径，就
能彼此通过FIFO相互通信。
有名管道由函数mkfifo()创建，需依赖头文件
#include <sys/types.h>
#include <sys/stat.h>
函数原形：int mkfifo(const char *pathname, mode_t mode)
*/
/***************mkfifo_r.c*****************/
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define P_FIFO "fifo"

int main(int argc, char **argv){
    char cache[100];
    int fd;
    memset(cache, 0, sizeof(cache));
    if(access(P_FIFO,F_OK) == 0){
        execlp("rm", "-f", P_FIFO, NULL);
        printf("access.\n");
    }
    if(mkfifo(P_FIFO, 0777) < 0){
        printf("create named pipe failed\n");
    }
    fd = open(P_FIFO, O_RDONLY | O_NONBLOCK);
    while(1){
        memset(cache, 0, sizeof(cache));
        if(read(fd, cache,100) == 0){
            printf("no data\n");
        }else
        {
            printf("get data:%s", cache);
        }
        sleep(1);
    }
    close(fd);
    return 0;
}