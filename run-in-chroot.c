#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

	// check for arguments
	if(argc < 2){
		printf("Usage: %s <program name>\n", argv[0]);
		exit(0);
	}
	// create directory
	mkdir("./myroot", 0777);
	// create filesystem
	system("debootstrap sid ./myroot");
	// touch
	open("./myroot/run/in-chroot", O_CREAT, 007);
	// chroot
	chroot("myroot");
	execve(argv[1], &argv[1], NULL);


	return 0;
}
