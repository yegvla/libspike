#include <sys/errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/errno.h>

register char *stack_ptr asm("sp");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#pragma GCC diagnostic ignored "-Wunused-parameter"

caddr_t __attribute__((weak, used)) _sbrk(int incr)
{
    extern char __bss_end__;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == NULL)
        heap_end = &__bss_end__;

    prev_heap_end = heap_end;

    if (heap_end + incr > stack_ptr) {
        errno = ENOMEM;
        return (caddr_t) -1;
    }

    heap_end += incr;

    return (caddr_t) prev_heap_end;
}

int __attribute__((weak, used)) _write (int fd, char *buf, int count)
{
    return 0;
}

int __attribute__((weak, used)) _read (int fd, char *buf, int count)
{
    return 0;
}

int __attribute__((weak, used)) _close(int file)
{
    return -1;
}

int __attribute__((weak, used)) _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int __attribute__((weak, used)) _isatty(int file)
{
    return 1;
}

int __attribute__((weak, used)) _lseek(int file, int ptr, int dir)
{
    return 0;
}

void __attribute__((weak, used)) _exit(int status)
{
    asm("BKPT #0");
    __builtin_unreachable();
}

int __attribute__((weak, used)) _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}

int __attribute__((weak, used)) _getpid(void)
{
    return 1;
}

int __attribute__((weak, used)) _open(char *path, int flags, ...)
{
    return -1;
}

int __attribute__((weak, used)) _wait(int *status)
{
    errno = ECHILD;
    return -1;
}

int __attribute__((weak, used)) _unlink(char *name)
{
    errno = ENOENT;
    return -1;
}

int __attribute__((weak, used)) _times(struct tms *buf)
{
    return -1;
}

int __attribute__((weak, used)) _link(char *old, char *new)
{
    errno = EMLINK;
    return -1;
}

int __attribute__((weak, used)) _fork(void)
{
    errno = EAGAIN;
    return -1;
}

int __attribute__((weak, used)) _execve(char *name, char **argv, char **env)
{
    errno = ENOMEM;
    return -1;
}

#pragma GCC diagnostic pop
