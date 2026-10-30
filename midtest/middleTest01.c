/*
*비전대학교 컴퓨터 학과
*1학년 A반 202618028 최규보
*시스템 프로그래밍 중간고사 1번
*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

	
	int rfd, wfd, n;
	char buf[10];

	rfd = open("linux.txt", O_RDONLY);
	if(rfd==-1){
		perror("Open linux.txt");
		exit(1);
	}

	if(mkdir("cgb",0777)==-1){
		perror("cgb");
		exit(1);
	}
	char *cwd;
	
	cwd = getcwd(NULL,BUFSIZ);

	chdir("cgb");

	wfd = open("linux.txt", O_CREAT | O_WRONLY| O_TRUNC, 0644);
	if(wfd==-1){
		perror("Open linux.txt");
		exit(1);
	}
	while ((n=read(rfd,buf,6))>0){
		if(write(wfd,buf,n)!=n)perror("write");
	}

	if (n==-1) perror("Read");

	close(rfd);
	close(wfd);
	

	char cd[BUFSIZ];

	getcwd(cd, BUFSIZ);
	printf("현재 작업 디렉터리: %s\n",cd);
	printf("[디렉터리 생성 및 linux.txt 파일 복사 완료]\n");
	printf("--- linux.txt 파일 상세 정보 (fstat 결과) ---\n");
	int fd;	
	struct stat statbuf;

	fd = open("linux.txt",O_RDONLY);
	if (fd == -1){
		perror("open: linux.txt");
		exit(1);
	}

	
	fstat(fd, &statbuf);
	printf("파일 크기: %d\n", (int)statbuf.st_size);
	printf("inode 번호: %d\n", (int)statbuf.st_ino);
	close(fd);
}
