
#ifndef __KFIFO__
#define __KFIFO__

#include <assert.h>
#include <time.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <errno.h>
#include <signal.h>



struct __kfifo {
    unsigned int    in;
    unsigned int    out;
    unsigned int    mask;
    unsigned int    esize;
    void        *data;
};


static inline unsigned int
__kfifo_uint_must_check_helper(unsigned int val)
{
    return val;
}

static inline int __kfifo_int_must_check_helper(int val)
{
    return val;
}

/*kfifo module port from kernel*/

#define ARRAY_SIZE(ary) (sizeof((ary))/sizeof(*(ary)))
#ifdef __GNUC__
    #define typeof __typeof__
    #define smp_wmb __sync_synchronize
#endif



#define __STRUCT_KFIFO_COMMON(datatype, recsize, ptrtype) \
    union { \
        struct __kfifo  myfifo; \
        datatype    *type; \
        const datatype  *const_type; \
        char        (*rectype)[recsize]; \
        ptrtype     *ptr; \
        ptrtype const   *ptr_const; \
    }

#define __STRUCT_KFIFO_PTR(type, recsize, ptrtype) \
{ \
    __STRUCT_KFIFO_COMMON(type, recsize, ptrtype); \
    type        buf[0]; \
}

struct kfifo __STRUCT_KFIFO_PTR(unsigned char, 0, void);

#define __is_kfifo_ptr(fifo)    (sizeof(*fifo) == sizeof(struct __kfifo))

#define kfifo_len(fifo) \
({ \
    typeof((fifo) + 1) __tmpl = (fifo); \
    __tmpl->myfifo.in - __tmpl->myfifo.out; \
})

#define kfifo_size(fifo)	((fifo)->myfifo.mask + 1)

#define kfifo_alloc(fifo, size, gfp_mask) \
__kfifo_int_must_check_helper( \
({ \
    typeof((fifo) + 1) __tmp = (fifo); \
    struct __kfifo *__kfifo = &__tmp->myfifo; \
    __is_kfifo_ptr(__tmp) ? \
    __kfifo_alloc(__kfifo, size, sizeof(*__tmp->type), gfp_mask) : \
    -EINVAL; \
}) \
)

#define kfifo_free(fifo) \
({ \
    typeof((fifo) + 1) __tmp = (fifo); \
    struct __kfifo *__kfifo = &__tmp->myfifo; \
    if (__is_kfifo_ptr(__tmp)) \
        __kfifo_free(__kfifo); \
})

#define kfifo_in(fifo, buf, n) \
({ \
    typeof((fifo) + 1) __tmp = (fifo); \
    typeof(__tmp->ptr_const) __buf = (buf); \
    unsigned long __n = (n); \
    const size_t __recsize = sizeof(*__tmp->rectype); \
    struct __kfifo *__kfifo = &__tmp->myfifo; \
    (__recsize) ?\
    __kfifo_in_r(__kfifo, __buf, __n, __recsize) : \
    __kfifo_in(__kfifo, __buf, __n); \
})

#define kfifo_out(fifo, buf, n) \
__kfifo_uint_must_check_helper( \
({ \
    typeof((fifo) + 1) __tmp = (fifo); \
    typeof(__tmp->ptr) __buf = (buf); \
    unsigned long __n = (n); \
    const size_t __recsize = sizeof(*__tmp->rectype); \
    struct __kfifo *__kfifo = &__tmp->myfifo; \
    (__recsize) ?\
    __kfifo_out_r(__kfifo, __buf, __n, __recsize) : \
    __kfifo_out(__kfifo, __buf, __n); \
}) \
)

#define kfifo_avail(fifo) \
__kfifo_uint_must_check_helper( \
({ \
    typeof((fifo) + 1) __tmpq = (fifo); \
    const size_t __recsize = sizeof(*__tmpq->rectype); \
    unsigned int __avail = kfifo_size(__tmpq) - kfifo_len(__tmpq); \
    (__recsize) ? ((__avail <= __recsize) ? 0 : \
    __kfifo_max_r(__avail - __recsize, __recsize)) : \
    __avail; \
}) \
)
extern int __kfifo_alloc(struct __kfifo *fifo, unsigned int size,
    size_t esize, int gfp_mask);

extern void __kfifo_free(struct __kfifo *fifo);

extern unsigned int __kfifo_in(struct __kfifo *fifo,
    const void *buf, unsigned int len);

extern unsigned int __kfifo_out(struct __kfifo *fifo,
    void *buf, unsigned int len);

extern unsigned int __kfifo_in_r(struct __kfifo *fifo,
    const void *buf, unsigned int len, size_t recsize);

extern unsigned int __kfifo_out_r(struct __kfifo *fifo,
    void *buf, unsigned int len, size_t recsize);

extern unsigned int __kfifo_out_peek_r(struct __kfifo *fifo,
    void *buf, unsigned int len, size_t recsize);

extern unsigned int __kfifo_max_r(unsigned int len, size_t recsize);

#endif

