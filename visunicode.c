#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main(){
	char* line=NULL;
	size_t linecap=0;
	ssize_t linelen;
	uint8_t buf[3];

	while( (linelen=getline(&line,&linecap,stdin)) >0 ){
		for(int i=0;i<linelen;i++){
//			write(1,line+i,1);
			if((uint8_t)line[i]<=0x7F){
				write(1,line+i,1);
			}else{
				buf[0]=((line[i]&0x0F)<<4)|((line[i+1]&0x3C)>>2);
				buf[1]=((line[i+1]&0x03)<<6)|((line[i+2]&0x3F)>>0);
				printf("\e[7mU+%02X%02X\e[0m",buf[0],buf[1]); fflush(stdout);
				i+=2;
			}
		}
	}
}
