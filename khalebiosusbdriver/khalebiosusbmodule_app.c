#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define DEVICE "/dev/khalebiosusbdevice"
#define DEVICEGAME "/dev/input/js0"

int main(){
	int i,fd;
	char ch, write_buf[100],read_buf[100];
	unsigned int ch_hex, write_buf_hex[100],read_buf_hex[100];

	
	fd=open(DEVICEGAME, O_RDWR);	//open for reading and writing
	
	if(fd==-1){
		printf("file %s either does not exist or has been lock by another process\n",DEVICEGAME);
		printf("use commande : sudo mknod %s c MajorNumber MinorNumber \n",DEVICEGAME);
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
			read(fd,read_buf_hex,sizeof(read_buf_hex));
			printf("Data in Device is: %x\n ",read_buf_hex);			
			break;
		default:
			printf("Wrong command\n");
			break;
	
	}

	return 0;
}
