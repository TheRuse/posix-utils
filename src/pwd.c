
#include <linux/limits.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
    char buf[PATH_MAX+1];
    if (getcwd(buf, sizeof(buf)) == NULL)
    {
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        exit(EXIT_FAILURE);
    }
    
    strcat(buf, "\n");
    
    int bytes_written = write(STDOUT_FILENO, buf, strlen(buf));
    if (bytes_written == -1)
    {
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}