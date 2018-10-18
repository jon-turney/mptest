#include <semaphore.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  pid_t f = fork();
  if (f == 0) { /* child */
    sem_t sem;
    *(void **)sem = &sem; /* prime sem with a valid pointer */
    sem_init(&sem, 0, 0);
  } else if (f == -1) { /* failed */
    printf("fork failed\n");
  } else { /* parent */
    int stat;
    waitpid(f, &stat, 0);
    printf("child exited %x\n", stat);
  }
}
