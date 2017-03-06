#ifndef FIFO_H
#define FIFO_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        volatile int len;
        void *buf, *end;
        void *wp, *rp;
    } fifo_t;

    fifo_t *fifo_init(int);
    void fifo_free(fifo_t *);

    int fifo_put(fifo_t *, void *, int);
    int fifo_get(fifo_t *, void *, int);

    int fifo_error(fifo_t *);

#ifdef __cplusplus
}
#endif

#endif
