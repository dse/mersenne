#ifndef BIGINT_H
#define BIGINT_H

#define BIGINT_NBITS_INIT 1024

#include <stdlib.h>
#include <stdint.h>

typedef struct bigint {
     size_t uint_count;
     uint64_t *uints;
} bigint_t;

void bigint_embiggen(bigint_t *, size_t);
void bigint_set(bigint_t *, uint64_t);
size_t bigint_next_pow2(size_t);
size_t bigint_uint_count(size_t);
void bigint_print(bigint_t *, char *);
void bigint_set_M(bigint_t *, size_t);
void bigint_incr(bigint_t *, uint64_t);

#endif
