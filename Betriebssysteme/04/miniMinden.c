#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/limits.h>

void printInfo()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
    }
    char *name;
    name = getlogin();
    printf("\n %s:~%s$ ", name, cwd);
}

char *readInput()
{
    char *buf;
    buf = (char *)malloc(PATH_MAX * sizeof(char));
    scanf("%s", buf);
    return buf;
}

void makeABaby()
{
    pid_t p = fork();
    /* Child */
    if (p == (pid_t)0)
    {

    }
    /* Parent */
    else if (p > (pid_t)0)
    {

    }
    else
    {
        printf("Fehler!");
    }
}

int main()
{
    printInfo();
    char *input = readInput();

    makeABaby();

    return 0;
}
