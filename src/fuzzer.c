/* Marc Blanchou (2012) */

#include "fuzzer.h"
#include "permutations.h"
#include "utils.h"

static void (*ptrFct_NO_ZERO[])(char*, const size_t, const uint16_t) = {PERMUTATIONS_NO_ZERO};
static void (*ptrFct[])(char*, const size_t, const uint16_t) = {PERMUTATIONS};

static void (**_ptrFct)(char*, const size_t, const uint16_t);
static size_t _ptrFctSize;

// will remove as it will
// be reduced to only one fct ptr later
static void _setFctPtr(const uint16_t flag) {
  if (flag & FUZZ_NO_ZERO) {
	_ptrFct = ptrFct_NO_ZERO;
	_ptrFctSize = sizeof(ptrFct_NO_ZERO) / sizeof(*ptrFct_NO_ZERO);
  } else {
	_ptrFct = ptrFct;
	_ptrFctSize = sizeof(ptrFct) / sizeof(*ptrFct);
  }
}

/*
  Perform mutations on a few bytes in the memory buffer
 */
void mutate(char *buff, const size_t size, const uint16_t flag) {
  _setFctPtr(flag);

  if (flag & FUZZ_FULL_PERMUTE) {
	_permuteFull(buff, size, flag);
  }
  else if (flag & FUZZ_ONE_BYTE) {
	_permuteSingleByte(buff, size, flag);
  }
  else {
	/*
	  Determines how many bytes to fuzz.
	  Note: A lower number than what we get here
	  could be better depending on the size of 
	  the buffer a division could be added here.
	*/
	size_t changes = (size_t)ksqrt(size);
   	size_t permuteType = getRand(_ptrFctSize);
	size_t pos;

	/* added division for files, need to scale it */
	if (flag & FUZZ_FILE)
	  changes /= 4;
	
	while (changes--) {
	  if (!(flag & FUZZ_KEEP_SAME_PERMUTE))
		permuteType = getRand(_ptrFctSize);
	  
	  if (flag & FUZZ_UTF16)
		permuteGroupBytes(buff, size, 2, flag);
	  else if (flag & FUZZ_UTF32)
		permuteGroupBytes(buff, size, 4, flag);
	  else {
		pos = getRand(size);
		(*_ptrFct[permuteType])(buff, pos, flag);
	  }
	}
  }
}

/*
   Permute per groupe of (power of 2) bytes
   Can be usefull for fuzzing a structure
   groupSize should be a power of 2
*/
static void permuteGroupBytes(char *buff, const size_t len, size_t groupSize, const uint16_t flag) {
  // get multiple by removing corresponding lsb
  const size_t pos = getRand(len) & (0xFF - (groupSize >> 1) - 1);

  const size_t permutation = getRand(_ptrFctSize);
  while (groupSize--)
    (*ptrFct[permutation])(buff + pos, groupSize, flag);
}

/*
  Perform random permutations on every byte of the bufer
 */
static void	_permuteFull(char* buff, size_t size, const uint16_t flag) {
  const size_t	permutation = getRand(_ptrFctSize);
  size_t		pos = 0;

  while (size--)
    (*_ptrFct[permutation])(buff, pos++, flag);
}

/*
  Perform a random permutation of a single byte
 */
static void _permuteSingleByte(char* buff, const size_t size, const uint16_t flag) {
  (*_ptrFct[getRand(_ptrFctSize)])(buff, getRand(size), flag);
}
