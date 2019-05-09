/*
管道是一种两个进程间进行单向通信的机制。
管道又被称为半双工管道。
数据只能由一个进程流向另一个进程（一个读管道，一个写管道）；如果要进行双工通信，
则需要建立两个管道。只能用于父子进程或兄弟进程间的通信。
管道由pipe()函数创建，需要依赖的头文件是#include <unistd.h>,函数原型pipe(int fd[2])
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define INPUT 0
#define OUTPUT 1

int main(){
    int fd[2];
    pid_t pid;
    char buf[256];
    int returned_count;
    pipe(fd);
    pid = fork();
    if(pid < 0){
        printf("Error in fork\n");
        exit(1);
    }else if(pid == 0){
        printf("in the child process....\n");
        close(fd[INPUT]);
        write(fd[OUTPUT], "hello world", sizeof("hello world"));
        exit(0);
    }else{
        printf("in the parent process...\n");
        close(fd[OUTPUT]);
        returned_count = read(fd[INPUT], buf, sizeof(buf));
        printf("%dbytes of data received from child process : %s\n", returned_count , buf);
    }
return 0;
}