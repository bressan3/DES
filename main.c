#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_splitKeys{
    char *c;
    char *d;
    unsigned char *cd;
}splitKeys;

typedef struct s_subkeys{
    char *k;
}subkeys;

const int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62,  54, 46,  38,  30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

const int numLeftShifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

const int PC_2[] = {14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};

const int IP_1[] = {58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

const int BIT_SELECTION [] = {32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

const int S1[] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};

void printCharAsBinary(char input) {
    
    for (int i = 0; i < 8; i++) {
        if ((0x01 << (7-i)) & input) // 0x01 = 00000001
            printf("1");
        else
            printf("0");
    }
}

char* applyTable(char *key, int tableSize, const int *table){
    
    // Initializes k+ with all 0's
    char *kPlus = malloc((tableSize / 8)*sizeof(char));
    for (int i = 0; i < 8; i++)
        kPlus[i] = 0x00;
    
    for(int i=0; i<tableSize; i++) {
        // Checks if bit at the position (7 - (PC_1[i] - 1) % 8)) of key is 1
        if(((key[(table[i] - 1) / 8] >> (7 - (table[i] - 1) % 8)) & 0b1) == 0b1){
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
char* leftShift(char *splitKey) {
    
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
    
    // Makes sure that the rotation exclude the
    // last 4 bits
    if((d[3] & 0b00000001) == 1)
        d[3] |= (1 << 4);
    if ((d[3] & 0b00000001) == 0)
        d[3] &= ~(1 << 4);
    
    d[3] &= ~(1 << 0);
    
    return d;
}

// Puts c and d back toghether forming cd
unsigned char* concatenateBits(char *c, char *d){
    
    unsigned char *concatenatedString = malloc(8*sizeof(char));
    int table[] = {0b00010000, 0b00100000, 0b01000000, 0b10000000};
    
    strncpy((char*)concatenatedString, c, 4);
    
    for (int i = 0; i < 4; i++) {
        if(d[0] & table[i])
            concatenatedString[3] |= 1 << i;
    }
    
    for (int i = 0; i < 4; i++) {
        unsigned char temp1 = d[i] & 0b00001111;
        unsigned char temp2 = d[i+1] & 0b11110000;
        temp1 <<= 4;
        temp2 >>= 4;
        concatenatedString[i + 4] = temp1 | temp2;
    }
    
    /*unsigned char temp1 = d[2] & 0b00001111; // 00001000
    unsigned char temp2 = d[3] & 0b11110000; // 11110000
    temp1 <<= 4;
    temp2 >>= 4;
    concatenatedString[6] = temp1 | temp2;*/
    
    return concatenatedString;
}

void getBit(char *array, int pos, int outPos, char *out){
    int correctChar = pos/8;
    unsigned char ch = array[correctChar];
    char result = (ch<<(pos%8)) & (0x80);
    result = result >> outPos;
    *out = (*out & ~result) | result;
}

void applySBlock(const int *sBlock, unsigned char block, unsigned char *out){
    /*unsigned char index = 0x00;
    unsigned char blocks[]={block};

    getBit(blocks, 0, 0, &index);
    getBit(blocks, 7, 1, &index);
    getBit(blocks, 1, 2, &index);
    getBit(blocks, 2, 3, &index);
    getBit(blocks, 3, 4, &index);
    getBit(blocks, 4, 5, &index);
    getBit(blocks, 5, 6, &index);
    getBit(blocks, 6, 7, &index);
    
    unsigned char num = sBlock[index];
    *out = num;*/
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
    
    char *kPlus = applyTable(key, 56, PC_1);
    
    printf("K+ = ");
    for (int i = 0; i < 7; i++) {
        printCharAsBinary(kPlus[i]);
    }
    printf("\n");
    
    // (Subkeys Part) -------------------------------------------------------------------------
    
    // Original plus 16 other shifted versions
    //splitKeys *splitKeys = malloc(17*sizeof(splitKeys));
    splitKeys splitKeys[17];
    splitKeys[0].c = malloc(4*sizeof(char));
    splitKeys[0].d = malloc(4*sizeof(char));
    
    strncpy(splitKeys[0].c, kPlus, 4);
    // Masking
    splitKeys[0].c[3] &= 0b11110000;
    printf("C: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(splitKeys[0].c[i]);
    }
    printf("\n");
    
    strncpy(splitKeys[0].d, kPlus + 3, 7);
    
    // Masking for d
    for (int i = 0; i < 4; i ++) {
        for (int i = 0;  i < 3;  ++i)
        {
            splitKeys[0].d[i] = (splitKeys[0].d[i] << 1) | ((splitKeys[0].d[i+1] >> 31) & 1);
        }
        splitKeys[0].d[3] = splitKeys[0].d[3] << 1;
    }

    printf("D: ");
    for (int i = 0; i < 4; i++)
        printCharAsBinary(splitKeys[0].d[i]);
    
    printf("\n");
    
    // Do the left shifts according to the table
    for (int i = 1; i < 17; i ++) {
        splitKeys[i].c = malloc(4*sizeof(char));
        splitKeys[i].d = malloc(4*sizeof(char));
        strncpy(splitKeys[i].c, splitKeys[i - 1].c, 4);
        strncpy(splitKeys[i].d, splitKeys[i - 1].d, 4);
        for (int j = 1; j <= numLeftShifts[i - 1]; j++){
            splitKeys[i].c = leftShift(splitKeys[i].c);
            splitKeys[i].d = leftShift(splitKeys[i].d);
        }
    }
    
    //unsigned char *concatenated = concatenateBits(splitKeys[0].c, splitKeys[0].d);
    splitKeys[0].cd = concatenateBits(splitKeys[0].c, splitKeys[0].d);
    
    // Concatenates the rest of the keys back
    for (int i = 1; i < 17; i++) {
        splitKeys[i].cd = concatenateBits(splitKeys[i].c, splitKeys[i].d);
    }
    
    // Apply PC_2
    subkeys *subkeys = malloc(16*sizeof(subkeys));
    
    // k[0] holds the subkey made by C0D0 and so on
    for (int i = 0; i < 17; i++) {
        subkeys[i].k = malloc(6*sizeof(char));
        subkeys[i].k = applyTable((char*)splitKeys[i].cd, 48, PC_2);
    }
    
    printf("K16: ");
    for (int i = 0; i < 6; i++) {
        printCharAsBinary(subkeys[16].k[i]);
    }
    printf("\n");
    
    // (Subkeys Part) -------------------------------------------------------------------------
    // (Message Part) -------------------------------------------------------------------------
    
    // M = 0123456789ABCDEF
    char message[8];
    message[0] = 0x01;
    message[1] = 0x23;
    message[2] = 0x45;
    message[3] = 0x67;
    message[4] = 0x89;
    message[5] = 0xAB;
    message[6] = 0xCD;
    message[7] = 0xEF;
    
    char *IP = applyTable(message, 64, IP_1);
    
    printf("IP: ");
    for (int i = 0; i < 8; i++) {
        printCharAsBinary(IP[i]);
    }
    printf("\n");
    
    
    
    printf("\n");
    
    printf("\n");
    
    return 0;
}
