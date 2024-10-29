#include "bigint.h"

#include <strings.h>
#include <string.h>
#include <stdio.h>

/**
 * arbitrarily sized non-negative integers.
 *
 * routines specially designed for working with numbers mod (2^p - 1)
 */

/* increase size of bigint if needed */
void bigint_embiggen(bigint_t *bi, size_t nbits) {
     if (bi->uint_count > nbits)
          return;
     size_t old_uint_count = bi->uint_count;
     bi->uint_count = nbits;
     bi->uints = realloc(bi->uints, sizeof(uint64_t) * bi->uint_count);
     bzero(bi->uints + old_uint_count,
           (bi->uint_count - old_uint_count) * sizeof(uint64_t));
}

/* set bigint's value to what is specified */
void bigint_set(bigint_t *bi, uint64_t value) {
     bzero(bi->uints + 1, bi->uint_count - 1);
     bi->uints[0] = value;
}

/* set bigint's value to 2^nbits - 1 */
void bigint_set_M(bigint_t *bi, size_t nbits) {
     bigint_embiggen(bi, bigint_uint_count(bigint_next_pow2(nbits)));
     size_t uint_index = nbits / 64; /* 63 => 0; 64 => 1; 65 => 1; ... */
     memset(bi->uints, 0xff, uint_index * 8);
     bzero(bi->uints + uint_index, bi->uint_count - uint_index);
     if (nbits % 64) {
          bi->uints[uint_index] = 0xffffffffffffffff >> (64 - (nbits % 64));
     }
}

/**
 * Number of uints required to store <nbits> bits.
 *
 * e.g., bigint_uint_count(69) => 2
 * e.g., bigint_uint_count(420) => 7
 */
size_t bigint_uint_count(size_t nbits) {
     return ((nbits + 7) / 8 + sizeof(uint64_t) - 1) / sizeof(uint64_t);
}

/**
 * Next power of 2 equal to or greater than <value>.
 *
 * e.g., bigint_next_pow2(69) => 128
 * e.g., bigint_next_pow2(420) => 512
 */
size_t bigint_next_pow2(size_t value) {
     if (value == 0)
          return 1;
     for (int i = 0; i < 63; i += 1) {
          if (value == (1 << i))
               return 1 << i;
     }
     value |= (value >> 1); /* fill msb and all bits to the right with 1's */
     value |= (value >> 2);
     value |= (value >> 4);
     value |= (value >> 8);
     value |= (value >> 16);
     value |= (value >> 32);
     return value + 1;
}

void bigint_print(bigint_t *bi, char *name) {
     if (name) {
          printf("<bigint name=\"%s\">\n", name);
     } else {
          printf("<bigint>\n");
     }
     for (size_t i = 0; i < bi->uint_count; i += 1) {
         printf("%12llu: %016llx\n", (unsigned long long)i, (unsigned long long)(bi->uints[i]));
     }
     printf("</bigint>\n");
}

void bigint_incr(bigint_t *bi, uint64_t incr) {
     size_t i;
     for (i = 0; i < bi->uint_count; i += 1) {
          int carry = (incr > 0 && bi->uints[i] > (UINT64_MAX - incr));
          bi->uints[i] += incr;
          incr = carry;
     }
     if (incr) {
          bigint_embiggen(bi, bi->uint_count + 1);
          bi->uints[i] = incr;
     }
}
