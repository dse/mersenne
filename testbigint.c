#include "bigint.h"

#include <stdio.h>

int main(int argc, char **argv) {
     bigint_t s = { uints: NULL, uint_count: 0 };
     bigint_embiggen(&s, 1);
     bigint_print(&s, "s");
     bigint_set(&s, 20);
     bigint_print(&s, "s");
     bigint_set_M(&s, 3);
     bigint_print(&s, "s");
     bigint_set_M(&s, 33);
     bigint_print(&s, "s");
     bigint_set_M(&s, 63);
     bigint_print(&s, "s");
     bigint_set_M(&s, 64);
     bigint_print(&s, "64");
     bigint_set_M(&s, 65);
     bigint_print(&s, "65");
     bigint_set_M(&s, 64);
     bigint_print(&s, "64");
     bigint_incr(&s, 1);
     bigint_print(&s, "64");
     bigint_set_M(&s, 69);
     bigint_incr(&s, 1);
     bigint_print(&s, "69");
     bigint_set_M(&s, 128);
     bigint_incr(&s, 155);
     bigint_print(&s, "128");
     bigint_incr(&s, 155);
     bigint_print(&s, "128");
     /* for (int i = 0; i < 40; i += 1) { */
     /*      printf("%lld => %lld\n", (unsigned long long) i, */
     /*             (unsigned long long)bigint_next_pow2(i)); */
     /* } */
     /* for (int i = 0; i < 420; i += 1) { */
     /*      printf("bigint_uint_count %lld => %lld\n", (unsigned long long) i, */
     /*             (unsigned long long)bigint_uint_count(i)); */
     /* } */
}
