#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include"make_log.h"

#define FDFS_LOG_MODULE	"test"
#define FDFS_LOG_PROC	"fdfs_test"

int main(int argc, char *argv[])
{
	LOG("111","111", "111");
	int fd[2] = {0};
	char buf[1024] = {0};
	ssize_t buf_len = 0;
	
	if (2 != argc)
	{
		printf("usage: ./a.out <filename path>\n");
		return 0;
	}
	
	if (-1 == pipe(fd))
	{
		LOG(FDFS_LOG_MODULE, FDFS_LOG_PROC, "pip error");
		return 1;
	}
	
	pid_t pid = fork();
	if (0 == pid)
	{
		//×Ó½ø³Ì
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execl
		(
			"/usr/bin/fdfs_upload_file",\
			"fdfs_upload_file",\
			"/home/test/fastdfs/etc/client.conf",\
			"/home/test/dis_storage/file.c",\
			 NULL\
		);
		LOG(FDFS_LOG_MODULE, FDFS_LOG_PROC, "exec error");
	}
	else if (0 < pid)
	{
		//¸¸½ø³Ì
		close(fd[1]);
		wait(NULL);
		buf_len = read(fd[0], buf, sizeof(buf));
		if (-1 == buf_len)
		{
			LOG(FDFS_LOG_MODULE, FDFS_LOG_PROC, "read error");
			return 2;	
		}
		int i = 0;
		while (buf[i] != '\n') ++i;
		buf[i] = '\0';
		LOG(FDFS_LOG_MODULE, FDFS_LOG_PROC, "upload file_id[%s] success!", buf);
	}
	else
	{
		LOG(FDFS_LOG_MODULE, FDFS_LOG_PROC, "fork error");
		return 3;
	}
	return 0;
}
