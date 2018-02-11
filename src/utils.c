/* Marc Blanchou (2012) */

#include <time.h>
#include <stdlib.h>

/* Sqrt function to not have -lm dependencies. (Carmack's sqrt) */
inline float ksqrt(float const number) {
    long i;
    float x, y;
    const float f = 1.5F;

    x = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = * ( float * ) &i;
    y  = y * ( f - ( x * y * y ) );
    y  = y * ( f - ( x * y * y ) );
    return number * y;
}

inline size_t getRand(const size_t max) {
  static size_t seed = 0;
  if (!seed) {
    seed = (size_t)time(0) ^ getpid();
    srand(seed);
  }
  return rand() % max;
}
