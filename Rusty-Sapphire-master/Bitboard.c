#include <stdlib.h>
#include <stdio.h>
#include "Tetris.h"

/** 
 *	Retrieves the value of the bit positionned at indexToRetrieve in bitboard, starting from the right 
 * */
unsigned short getBitboardValue(unsigned short bitboard, unsigned short indexToRetrieve) {
	return (bitboard & (short)1 << indexToRetrieve) > 0;
}

/** 
 *	Sets the value of the bit positionned at indexToRetrieve in bitboard, starting from the right, to value
 * */
unsigned short setBitboardValue(unsigned short bitboard, unsigned short indexToRetrieve, unsigned short value) {
	unsigned short bitValue = getBitboardValue(bitboard, indexToRetrieve);
	if(bitValue != value) 
		bitboard ^= ((short)1 << indexToRetrieve);
	return bitboard;
}




