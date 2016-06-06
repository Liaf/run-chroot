#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

	// check for arguments
	if(argc < 2){
		printf("Usage: %s <program name>\n", argv[0]);
		exit(0);
	}
	
	int binary;
	int binaryInChroot;
	char c[1];

	// create directory
	mkdir("./myroot", 0777);

	// create filesystem
	system("debootstrap sid ./myroot");

	// move program you want to execute
	if((binary = open(argv[1], O_RDONLY)) < 0) printf("Cannot open binary.\n");
	if((binaryInChroot = open("./myroot/testThis", O_CREAT | O_WRONLY, 0700)) < 0) printf("Cannot open to write.\n");
	while((read(binary, &c, 1)) > 0){
		write(binaryInChroot, &c, 1);
	}
	close(binary);
	close(binaryInChroot);

	// chroot
	chroot("myroot");
	chdir("/");

	// execute program
	system("/testThis");

	return 0;
}
