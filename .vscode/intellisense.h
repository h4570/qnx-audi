#define NULL 0
#define _NULL 0
#define nullptr 0
#define __INT_BITS__ 32
#define CLOCK_MONOTONIC 2
#define bool char

#define pid_t int
#define pthread_t int
#define __WCHAR_T int
#define __MBSTATE_T int
#define __FPOS_T int
#define __OFF_T int
#define __SYNC_T int
#define __SYNC_ATTR_T int
#define __PTHREAD_MUTEX_T int
#define __PTHREAD_KEY_T int
#define __PTHREAD_MUTEXATTR_T int
#define __PTHREAD_CONDATTR_T int
#define __PTHREAD_COND_T int
#define __PTHREAD_ONCE_T int
#define __PTHREAD_ATTR_T int

// typedef char _int8;
typedef unsigned char _uint8;
// typedef short _int16;
typedef unsigned short _uint16;
// typedef int _int32;
typedef unsigned int _uint32;
// typedef long _int64;
typedef unsigned long _uint64;
typedef int *_intptr;
typedef unsigned int *_uintptr;

typedef char _int8t;
typedef unsigned char _uint8t;
typedef short _int16t;
typedef unsigned short _uint16t;
typedef int _int32t;
typedef unsigned int _uint32t;
typedef long _int64t;
typedef unsigned long _uint64t;
typedef int *_intptrt;
typedef unsigned int *_uintptrt;

typedef char _Int8t;
typedef unsigned char _Uint8t;
typedef short _Int16t;
typedef unsigned short _Uint16t;
typedef int _Int32t;
typedef unsigned int _Uint32t;
typedef long _Int64t;
typedef unsigned long _Uint64t;
typedef int *_Intptrt;
typedef unsigned int *_Uintptrt;

typedef unsigned long long _ULonglong;
typedef long long _Longlong;

extern void exit(int __status);
extern long int strtol(const char *__nptr, char **__endptr, int __base);
extern int rand(void);
extern int abs(int _Left);
extern int open(const char *a, int b);
extern int close(int a);
extern int getpid();
extern int read(int fd, void *buf, size_t count);

#define RAND_MAX 32767u
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#undef _WIN32
#undef _STDLIB_H_INCLUDED
#undef _STDDEF_H_INCLUDED
#undef _LIMITS_H_INCLUDED
#undef _MSC_VER