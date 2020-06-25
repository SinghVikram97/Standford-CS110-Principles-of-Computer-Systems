#include <fcntl.h>  // for open
#include <unistd.h> // for read, write and close
#include <stdio.h>
#include <stdbool.h> // for bool
static const int kWrongArgumentCount = 1;

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "%s <source-file><destination-file>.\n", argv[0]);
    return kWrongArgumentCount;
  }

  int fdin = open(argv[1], O_RDONLY);
  int fdout = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0644);

  char buffer[1024];

  while (true)
  {
    // ssize_t same as size_t but with ability to take negative numbers
    ssize_t bytesRead = read(fdin, buffer, sizeof(buffer)); // pointer and how much to read

    if (bytesRead == 0)
    {
      // No more bytes to read
      break;
    }

    size_t bytesWritten = 0;

    while (bytesWritten < bytesRead)
    {
      bytesWritten += write(fdout, buffer + bytesWritten, bytesRead - bytesWritten);
    }
  }
  close(fdout);
  close(fdin);
  return 0;
}