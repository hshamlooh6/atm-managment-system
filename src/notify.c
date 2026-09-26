#include "header.h"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t listenerPid = -1;

static void fifoPathForUser(const char *userName, char outPath[256])
{
    snprintf(outPath, 256, "/tmp/atm_notify_%s", userName);
}

static void listenerLoop(const char *path)
{
    while (1)
    {
        int fd = open(path, O_RDONLY);
        if (fd < 0)
        {
            _exit(1);
        }

        char message[256];
        ssize_t bytesRead = read(fd, message, sizeof(message) - 1);
        close(fd);

        if (bytesRead > 0)
        {
            message[bytesRead] = '\0';
            printf("\n\a\n*** Notification: %s ***\n", message);
            fflush(stdout);
        }
    }
}

void notifyStart(const struct User *u)
{
    char path[256];
    fifoPathForUser(u->name, path);

    if (mkfifo(path, 0600) != 0 && errno != EEXIST)
    {
        printf("(Note: real-time notifications could not be enabled.)\n");
        return;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        printf("(Note: real-time notifications could not be enabled.)\n");
        return;
    }

    if (pid == 0)
    {
        listenerLoop(path);
        _exit(0);
    }

    listenerPid = pid;
}

void notifyStop(void)
{
    if (listenerPid > 0)
    {
        kill(listenerPid, SIGTERM);
        waitpid(listenerPid, NULL, 0);
        listenerPid = -1;
    }
}

void notifySend(const char *toUserName, const char *message)
{
    char path[256];
    fifoPathForUser(toUserName, path);

    mkfifo(path, 0600);

    int fd = open(path, O_WRONLY | O_NONBLOCK);
    if (fd < 0)
    {
        printf("(%s is not currently online - they'll see the change next time they log in.)\n",
               toUserName);
        return;
    }

    write(fd, message, strlen(message));
    close(fd);
}
