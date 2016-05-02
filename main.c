#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"

typedef struct s_splitKeys{
    char c[4];
    char d[4];
}splitKeys;

const int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62,  54, 46,  38,  30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

const int numLeftShifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void printCharAsBinary(char input) {
    
    for (int i = 0; i < 8; i++) {
        if ((0x01 << (7-i)) & input) // 0x01 = 00000001
            printf("1");
        else
            printf("0");
    }
}

char* buildKPlus(char *key){
    
    // Initializes k+ with all 0's
    char *kPlus = malloc(7*sizeof(char));
    for (int i = 0; i < 8; i++)
        kPlus[i] = 0x00;
    
    for(int i=0; i<56; i++) {
        // Checks if bit at the position (7 - (PC_1[i] - 1) % 8)) of key is 1
        if(((key[(PC_1[i] - 1) / 8] >> (7 - (PC_1[i] - 1) % 8)) & 0b1) == 0b1){
            // Swaps the binary value at position (7 - i%8) to 1
            kPlus[i/8] |= (1u << (7 - i%8));
        } else{
            // Swaps the binary value at position (7 - i%8) to 0
            kPlus[i/8] |= (0u << (7 - i%8));
        }
    }
    
    return kPlus;
}

// Makes a left rotating bitshif on d. bits = num bits in d or s + num rotations
char* leftShift(char *splitKey)
{
    const uint8_t octetshifts = 1 / 8;
    const uint8_t bitshift = 1 % 8;
    const uint8_t bitsleft = (8 - bitshift);
    const uint8_t lm = (1 << bitshift) - 1;
    const uint8_t um = ~lm;
    
    char* d = malloc(4*sizeof(char));
    
    for (int i = 0; i < 4; i++)
    {
        d[(i + 4 - octetshifts) % 4] =
        ((splitKey[i] << bitshift) & um) |
        ((splitKey[(i + 1) % 4] >> bitsleft) & lm);
    }
    
    if(((d[3] >> 7) & 1))
        d[3] |= (1 << 4);
    if ((d[3] & 0b00000001) == 0)
        d[3] &= ~(1 << 4);
    
    d[3] &= ~(1 << 0);
    
    return d;
}


int main(){
	
    // Key from the example
    char key[8];
	key[0] = 0x13;
	key[1] = 0x34;
	key[2] = 0x57;
	key[3] = 0x79;
	key[4] = 0x9B;
	key[5] = 0xBC;
	key[6] = 0xDF;
	key[7] = 0xF1;
    
    printf("K = ");
    
    for (int i = 0; i < 8; i++)
        printCharAsBinary(key[i]);
    
    printf("\n");
    
    char *kPlus = buildKPlus(key);
    
    printf("K+ = ");
    for (int i = 0; i < 7; i++) {
        printCharAsBinary(kPlus[i]);
    }
    printf("\n");
    
    splitKeys splitKeys[16];
    
    // Used to be unsigned
    //char *c = malloc(4*sizeof(char));
    strncpy(splitKeys[0].c, kPlus, 4);
    // Masking
    splitKeys[0].c[3] &= 0b11110000;
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(splitKeys[0].c[i]);
    }
    printf("\n");
    /*
    //char *d = malloc(4*sizeof(char));
    //strncpy(c, (char*)c, 4);
    c = leftShift(c);
    c = leftShift(c);
    c = leftShift(c);
    c = leftShift(c);
    for(int i = 0; i < 4; i++)
        printCharAsBinary(c[i]);
    printf("\n");
    c = leftShift(c);
    //c = rotateLeft(c);
    
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(c[i]);
    }
    printf("\n");
    
    char *d = malloc(4*sizeof(char));
    strncpy(d, kPlus + 3, 7);
    
    // Masking for d
    for (int i = 0; i < 4; i ++) {
        for (int i = 0;  i < 3;  ++i)
        {
            d[i] = (d[i] << 1) | ((d[i+1] >> 31) & 1);
        }
        d[3] = d[3] << 1;
    }

    printf("D: ");
    for (int i = 0; i < 4; i++)
        printCharAsBinary(d[i]);

    free(c);*/
    
    
    printf("\n");
    
	
    return 0;
}





/*
 Binary stuff for tests
 char a = 0b00000100;
 print_char_as_binary(a);
 printf("\n");
 a |= (1u << (7 - 1));
 print_char_as_binary(a);
 */



