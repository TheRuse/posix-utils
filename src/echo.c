#include <errno.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{

    char buf[ARG_MAX + 1];
    if (argc < 2)
    {
        const char *err_msg = "Not enough arguments\n";
        write(STDERR_FILENO, err_msg, strlen(err_msg));

        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; ++i)
    {
        strcpy(buf, argv[1]);
        strcat(buf, " ");

        int bytes_written = write(STDOUT_FILENO, buf, strlen(buf));
        if (bytes_written == -1)
        {
            write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
            write(STDERR_FILENO, "\n", 1);

            exit(EXIT_FAILURE);
        }
    }

    int bytes_written = write(STDOUT_FILENO, "\n", 1);
    if (bytes_written == -1)
    {
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);

        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}