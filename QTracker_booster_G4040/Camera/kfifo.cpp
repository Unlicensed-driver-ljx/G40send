#include "kfifo.h"

/*kfifo from kernel*/

#define min(x,y) ((x)<(y)?(x):(y))

// https://stackoverflow.com/questions/4398711/round-to-the-nearest-power-of-two
static inline uint32_t roundup_pow_of_two(uint32_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}
#if 0
// https://blog.csdn.net/dreamispossible/article/details/91162847
static uint32_t rounddown_pow_of_two(uint32_t n) {
    n|=n>>1; n|=n>>2; n|=n>>4; n|=n>>8; n|=n>>16;
    return (n+1) >> 1;
}
#endif

/*
 * internal helper to calculate the unused elements in a fifo
 */
static inline uint32_t kfifo_unused(struct __kfifo *fifo)
{
    return (fifo->mask + 1) - (fifo->in - fifo->out);
}

int __kfifo_alloc(struct __kfifo *fifo, uint32_t size,
        size_t esize, int gfp_mask)
{
    /*
     * round down to the next power of 2, since our 'let the indices
     * wrap' technique works only in this case.
     */
    size = roundup_pow_of_two(size);

    fifo->in = 0;
    fifo->out = 0;
    fifo->esize = esize;

    if (size < 2) {
        fifo->data = NULL;
        fifo->mask = 0;
        return -EINVAL;
    }

    fifo->data = malloc(size * esize);

    if (!fifo->data) {
        fifo->mask = 0;
        return -ENOMEM;
    }
    fifo->mask = size - 1;

    return 0;
}

void __kfifo_free(struct __kfifo *fifo)
{
    free(fifo->data);
    fifo->in = 0;
    fifo->out = 0;
    fifo->esize = 0;
    fifo->data = NULL;
    fifo->mask = 0;
}

static void kfifo_copy_in(struct __kfifo *fifo, const void *src,
        uint32_t len, uint32_t off)
{
    uint32_t size = fifo->mask + 1;
    uint32_t esize = fifo->esize;
    uint32_t l;

    off &= fifo->mask;
    if (esize != 1) {
        off *= esize;
        size *= esize;
        len *= esize;
    }
    l = min(len, size - off);

    memcpy((uint8_t*)fifo->data + off, src, l);
    memcpy(fifo->data, (uint8_t*)src + l, len - l);
    /*
     * make sure that the data in the fifo is up to date before
     * incrementing the fifo->in index counter
     */
    smp_wmb();
}

uint32_t __kfifo_in(struct __kfifo *fifo,
        const void *buf, uint32_t len)
{
    uint32_t l;

    l = kfifo_unused(fifo);
    if (len > l)
        len = l;

    kfifo_copy_in(fifo, buf, len, fifo->in);
    fifo->in += len;
    return len;
}

static void kfifo_copy_out(struct __kfifo *fifo, void *dst,
        uint32_t len, uint32_t off)
{
    uint32_t size = fifo->mask + 1;
    uint32_t esize = fifo->esize;
    uint32_t l;

    off &= fifo->mask;
    if (esize != 1) {
        off *= esize;
        size *= esize;
        len *= esize;
    }
    l = min(len, size - off);

    memcpy(dst, (uint8_t*)fifo->data + off, l);
    memcpy((uint8_t*)dst + l, fifo->data, len - l);
    /*
     * make sure that the data is copied before
     * incrementing the fifo->out index counter
     */
    smp_wmb();
}

uint32_t __kfifo_out_peek(struct __kfifo *fifo,
        void *buf, uint32_t len)
{
    uint32_t l;

    l = fifo->in - fifo->out;
    if (len > l)
        len = l;

    kfifo_copy_out(fifo, buf, len, fifo->out);
    return len;
}

uint32_t __kfifo_out(struct __kfifo *fifo,
        void *buf, uint32_t len)
{
    len = __kfifo_out_peek(fifo, buf, len);
    fifo->out += len;
    return len;
}

uint32_t __kfifo_max_r(uint32_t len, size_t recsize)
{
    uint32_t max = (1 << (recsize << 3)) - 1;

    if (len > max)
        return max;
    return len;
}

#define __KFIFO_POKE(data, in, mask, val) \
    ( \
    (data)[(in) & (mask)] = (unsigned char)(val) \
    )

/*
 * __kfifo_poke_n internal helper function for storeing the length of
 * the record into the fifo
 */
static void __kfifo_poke_n(struct __kfifo *fifo, unsigned int n, size_t recsize)
{
    unsigned int mask = fifo->mask;
    unsigned char *data = (unsigned char*)fifo->data;

    __KFIFO_POKE(data, fifo->in, mask, n);

    if (recsize > 1)
        __KFIFO_POKE(data, fifo->in + 1, mask, n >> 8);
}

#define __KFIFO_PEEK(data, out, mask) \
    ((data)[(out) & (mask)])
/*
 * __kfifo_peek_n internal helper function for determinate the length of
 * the next record in the fifo
 */
static unsigned int __kfifo_peek_n(struct __kfifo *fifo, size_t recsize)
{
    unsigned int l;
    unsigned int mask = fifo->mask;
    unsigned char *data = (unsigned char*)fifo->data;

    l = __KFIFO_PEEK(data, fifo->out, mask);

    if (--recsize)
        l |= __KFIFO_PEEK(data, fifo->out + 1, mask) << 8;

    return l;
}

static unsigned int kfifo_out_copy_r(struct __kfifo *fifo,
    void *buf, unsigned int len, size_t recsize, unsigned int *n)
{
    *n = __kfifo_peek_n(fifo, recsize);

    if (len > *n)
        len = *n;

    kfifo_copy_out(fifo, buf, len, fifo->out + recsize);
    return len;
}

uint32_t __kfifo_out_r(struct __kfifo *fifo, void *buf,
        uint32_t len, size_t recsize)
{
    uint32_t n;

    if (fifo->in == fifo->out)
        return 0;

    len = kfifo_out_copy_r(fifo, buf, len, recsize, &n);
    fifo->out += n + recsize;
    return len;
}

uint32_t __kfifo_in_r(struct __kfifo *fifo, const void *buf,
        uint32_t len, size_t recsize)
{
    if (len + recsize > kfifo_unused(fifo))
        return 0;

    __kfifo_poke_n(fifo, len, recsize);

    kfifo_copy_in(fifo, buf, len, fifo->in + recsize);
    fifo->in += len + recsize;
    return len;
}


