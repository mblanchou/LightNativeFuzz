/* Marc Blanchou (2012) */

#include <stdint.h>

void setRandByte(char* buff, const size_t pos, const uint16_t flag);
void flipAllBits(char* buff, const size_t pos, const uint16_t flag);
void setMeta(char* buff, const size_t pos, const uint16_t flag);
void setZero(char* buff, const size_t pos, const uint16_t flag);
void flipRandBit(char* buff, const size_t pos, const uint16_t flag);
void flipRandGroupBits(char* buff, const size_t pos, const uint16_t flag);
void flipRandBits(char* buff, const size_t pos, const uint16_t flag);


#define PERMUTATIONS_NO_ZERO setMeta,flipAllBits,setRandByte,setRandByte,flipRandBit,flipRandGroupBits,flipRandBits

#define PERMUTATIONS_ZERO ,setZero

#define PERMUTATIONS PERMUTATIONS_NO_ZERO PERMUTATIONS_ZERO

