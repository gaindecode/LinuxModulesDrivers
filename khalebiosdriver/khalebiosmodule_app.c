#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define DEVICE "/dev/khalebiosdevice"

int main(){
	int i,fd;
	char ch, write_buf[100],read_buf[100];
	
	fd=open(DEVICE, O_RDWR);	//open for reading and writing
	
	if(fd==-1){
		printf("file %s either does not exist or has been lock by another process\n",DEVICE);
		exit(-1);
	}
	printf("r=Read from device\nw=Write to device\nenter command: ");
	scanf("%c",&ch);
	
	switch(ch){
		case 'w':
			printf("enter data: ");
			scanf(" %[^\n]",write_buf);
			write(fd,write_buf,sizeof(write_buf));
			break;
		case 'r':
			read(fd,read_buf,sizeof(read_buf));
			printf("Data in Device is: %s\n ",read_buf);			
			break;
		default:
			printf("Wrong command\n");
			break;
	
	}

	return 0;
}