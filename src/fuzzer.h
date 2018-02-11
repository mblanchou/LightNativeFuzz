/* Marc Blanchou (2012) */

#include <stddef.h>
#include <stdint.h>

/* flags for the permute functions */
#define FUZZ_NORMAL			0
#define FUZZ_FILE			0x01
#define FUZZ_NO_ZERO			0x02
#define FUZZ_FULL_PERMUTE		0x04
#define FUZZ_ONE_BYTE			0x08
#define FUZZ_KEEP_SAME_PERMUTE		0x10
#define FUZZ_UTF16			0x20
#define FUZZ_UTF32			0x40

/*
  Perform mutations on a few bytes of the memory buffer using different flags and techniques
 */
void mutate(char *buff, const size_t size, const uint16_t flag);

/*
   Permute per groupe of (power of 2) bytes (for protocols, memory segments, structs/objects)
*/
static void permuteGroupBytes(char *buff, const size_t len, size_t groupSize, const uint16_t flag);

/*
  Perform random permutations on every byte of the buffer
 */
static void _permuteFull(char* buff, const size_t size, const uint16_t flag);

/*
  Perform a random permutation of a single byte
 */
static void _permuteSingleByte(char* buff, const size_t size, const uint16_t flag);
