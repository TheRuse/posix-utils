#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int error_msg(const char *str)
{
    write(STDERR_FILENO, str, strlen(str));

    return 1;
}

int main(int argc, char **argv)
{
    // Set default mode
    mode_t mode = 0777;

    if (argc < 2)
    {
        const char* err_msg = "Not enough arguments\n";
        write(STDERR_FILENO, err_msg, strlen(err_msg));

        exit(EXIT_FAILURE);
    }

    // Check if user provided mode
    if (argc >= 3)
    {
        mode = (mode_t)strtol(argv[2], NULL, 8);
        if ((mode < 0) && (mode > 0100000))
        {
            const char* err_msg = "Invalid mode\n";
            write(STDERR_FILENO, err_msg, strlen(err_msg));
        }
    }

    if (mkdir(argv[1], mode) != 0)
    {
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}