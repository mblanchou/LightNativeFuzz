/* Marc Blanchou (2012) */

#include <stdlib.h>
#include "permutations.h"
#include "utils.h"
#include "fuzzer.h"

static const char* meta = "./\\$-%$;,'\"*";

inline static void flipBits(char* buff, int pos, int bitpos, int bitlen, const uint16_t flag) {
  while (bitlen--) {
	//	buff[pos] ^= (1 << (7 - (bitpos++ % 8)));
	*(unsigned char*)(buff + pos) ^= (1 << (7 - (bitpos++ % 8)));
  }
}

inline void setRandByte(char* buff, const size_t pos, const uint16_t flag) {
  buff[pos] = getRand(256);
}

/* Flip all bits */
inline void flipAllBits(char* buff, const size_t pos, const uint16_t flag) {
  if (!(flag & FUZZ_NO_ZERO) || *(unsigned char*)(buff + pos) != 0xFF)
	//	buff[pos] ^= 0xFF;
	*(unsigned char*)(buff + pos) ^= 0xFF;
}

/* Flip a random bit */
inline void flipRandBit(char* buff, const size_t pos, const uint16_t flag) {
  const size_t bitPos = getRand(8);
  
  flipBits(buff, pos, bitPos, 1, flag);
  if ((flag & FUZZ_NO_ZERO) && !buff[pos])
    // revert if we flipped the only bit set
    flipBits(buff, pos, bitPos, 1, flag);
}

/* Flip a random group of bits */
inline void flipRandGroupBits(char* buff, const size_t pos, const uint16_t flag) {
  const size_t bitPos = getRand(8);
  const size_t bitlen = getRand(8 - bitPos);
  
  flipBits(buff, pos, bitPos, bitlen, flag);
  if ((flag & FUZZ_NO_ZERO) && !buff[pos])
    // revert if 0
    flipBits(buff, pos, bitPos, bitlen, flag);
}

/* Flip 1 random bit on 4 random bytes */
inline void flipRandBits(char* buff, const size_t pos, const uint16_t flag) {
  size_t i;

  for (i = 0; i < 4; i++)
    flipRandBit(buff, pos, flag);
}

inline void setMeta(char* buff, const size_t pos, const uint16_t flag) {
  static size_t size = 0;
  
  if (!size)
    size = strlen(meta);
  buff[pos] = meta[getRand(size)];
}

inline void setZero(char* buff, const size_t pos, const uint16_t flag) {
  buff[pos] = 0;
}

