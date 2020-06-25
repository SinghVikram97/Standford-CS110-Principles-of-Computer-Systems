#include <fcntl.h>  // for open
#include <unistd.h> // for read, write and close
#include <stdio.h>
#include <sys/types.h> // for umask
#include <sys/stat.h>  // for umask
#include <errno.h>     // for errno

const char *kFilename = "my_file1.txt"; // k is a convention to indicate it is a constant
const int kFileExistsError = 17;        // file exists error code

int main()
{
  umask(0); // Set to 0 to enable all permissions to be set

  int file_descriptor = open(kFilename, O_WRONLY | O_CREAT | O_EXCL, 0644);
  // 644 -> (110)(100)(100) -> rw-r--r--
  // ls -l my_file1.txt to check permissions

  // -1 if fails to open
  if (file_descriptor == -1)
  {
    printf("There was a problem in creating '%s'! \n", kFilename);

    if (errno == kFileExistsError)
    {
      printf("The file already exists \n");
    }
    else
    {
      printf("Unknown errorno: %d\n", errno);
    }
    return -1;
  }
  close(file_descriptor);
  return 0;
}
