#ifndef QUICKJS_X68K_STUB_H
#define QUICKJS_X68K_STUB_H

/* 先に必要な標準ヘッダをすべて読み込み、プロトタイプ宣言を確定させる */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

/* 以降、newlibに存在しない、または競合するシンボルをインライン関数でオーバーライド */
#define STUB_FUNC static inline __attribute__((always_inline))

/* 1. 基本マクロハック */
#define malloc_usable_size(ptr) (0)
#define tm_gmtoff tm_sec; res = 0

/* 2. 動的リンク (dlfcn) スタブ */
#define RTLD_LAZY 1
#define RTLD_NOW 2
#define RTLD_GLOBAL 8
#define RTLD_LOCAL 0
STUB_FUNC void *dlopen(const char *f, int g) { return NULL; }
STUB_FUNC const char *dlerror(void) { return "Not supported"; }
STUB_FUNC void *dlsym(void *h, const char *s) { return NULL; }
STUB_FUNC int dlclose(void *h) { return 0; }

/* 3. 端末制御 (termios/ioctl) スタブ */
// c_cc を正しく配列に変更
struct termios { int c_iflag; int c_oflag; int c_cflag; int c_lflag; unsigned char c_cc[32]; };
#define TCSANOW 0
#define ICANON 0
#define ECHO 0
#define ISIG 0
#define VMIN 0
#define VTIME 1
#define IGNBRK 0
#define BRKINT 0
#define PARMRK 0
#define ISTRIP 0
#define INLCR 0
#define IGNCR 0
#define ICRNL 0
#define IXON 0
#define OPOST 0
#define ECHONL 0
#define IEXTEN 0
#define CSIZE 0
#define PARENB 0
#define CS8 0
STUB_FUNC int tcgetattr(int fd, struct termios *t) { return 0; }
STUB_FUNC int tcsetattr(int fd, int opt, const struct termios *t) { return 0; }
struct winsize { unsigned short ws_row; unsigned short ws_col; };
#define TIOCGWINSZ 0
STUB_FUNC int ioctl(int fd, unsigned long req, ...) { return -1; }

/* 4. OS/プロセス系システムコールスタブ */
#define lstat(path, sb) stat(path, sb)
STUB_FUNC int waitpid(int pid, int *status, int options) { return -1; }

STUB_FUNC int pclose_stub(FILE *stream) { return -1; }
#define pclose pclose_stub

STUB_FUNC int pipe_stub(int *pipedes) { return -1; }
#define pipe pipe_stub

STUB_FUNC int nanosleep(const struct timespec *req, struct timespec *rem) { return 0; }
// struct timespec に修正
STUB_FUNC int clock_gettime(clockid_t id, struct timespec *tp) { return 0; }

STUB_FUNC char *realpath_stub(const char *path, char *resolved) { return NULL; }
#define realpath realpath_stub

STUB_FUNC int utimes_stub(const char *path, const struct timeval *times) { return -1; }
#define utimes utimes_stub

STUB_FUNC FILE *popen_stub(const char *command, const char *type) { return NULL; }
#define popen popen_stub

STUB_FUNC long sysconf_stub(int name) { return -1; }
#define sysconf sysconf_stub

STUB_FUNC int setgid_stub(gid_t gid) { return -1; }
#define setgid setgid_stub

STUB_FUNC int setuid_stub(uid_t uid) { return -1; }
#define setuid setuid_stub

/* 5. pthread 関連マクロ */
#define pthread_mutex_init(m, a)    (0)
#define pthread_mutex_lock(m)      (0)
#define pthread_mutex_unlock(m)    (0)
#define pthread_mutex_destroy(m)   (0)
#define pthread_cond_init(c, a)     (0)
#define pthread_cond_signal(c)      (0)
#define pthread_cond_wait(c, m)     (0)
#define pthread_cond_timedwait(c, m, t) (0)
#define pthread_cond_destroy(c)     (0)

#endif
