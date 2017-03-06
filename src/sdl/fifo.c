#include <stdlib.h>
#include <string.h>

#include "fifo.h"

fifo_t *fifo_init(int l) {

    fifo_t *f = (fifo_t *) malloc(sizeof (fifo_t));

    f->len = l + sizeof (int);

    f->buf = calloc(f->len, 1);

    f->wp = f->buf + (f->len >> 1);
    f->rp = f->buf;

    f->end = f->buf + f->len;

    return f;
}

void fifo_free(fifo_t *f) {

    free(f->buf);
    free(f);
}

static int fifo_filled(fifo_t *f) {

    int l = f->wp - f->rp;

    if (l < 0)
        l += f->len;

    return l;
}

static int fifo_avail(fifo_t *f) {

    return f->len - fifo_filled(f) - sizeof (int);
}

int fifo_put(fifo_t *f, void *b, int l) {

    int m = fifo_avail(f);

    if (l > m)
        l = m;

    int s = f->end - f->wp;

    if (s < l) {

        memcpy(f->wp, b, s);
        memcpy(f->buf, b + s, l - s);

    } else {

        memcpy(f->wp, b, l);
    }

    f->wp += l;

    if (f->wp >= f->end)
        f->wp -= f->len;

    return l;
}

int fifo_get(fifo_t *f, void *b, int l) {

    int m = fifo_filled(f);

    if (l > m)
        l = m;

    int s = f->end - f->rp;

    if (s < l) {

        memcpy(b, f->rp, s);
        memcpy(b + s, f->buf, l - s);

    } else {

        memcpy(b, f->rp, l);
    }

    f->rp += l;

    if (f->rp >= f->end)
        f->rp -= f->len;

    return l;
}

int fifo_error(fifo_t *f) {

    return fifo_filled(f) - (f->len >> 1);
}
