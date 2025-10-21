#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

int main()
{
    char buf[LOGIN_NAME_MAX+1];
    if (getlogin_r(buf, sizeof(buf)) != 0)
    {
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        exit(EXIT_FAILURE);
    }

    strcat(buf, "\n");

    int num_bytes = write(STDOUT_FILENO, buf, strlen(buf));
    if (num_bytes == -1)
    {
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}