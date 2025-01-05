#include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>

int main(int argc, char *argv[]) {

  open("/dev/null", O_RDONLY);
  open("/dev/null", O_WRONLY | O_CREAT | O_EXCL);
  fopen("/dev/random", "r");
  fopen("/does/not/exist", "w");

  return 0;
}