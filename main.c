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

const int E_BIT_SELECTION [] = {32, 1, 2, 3, 4, 5,
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

const int S2[] = {15,  1,   8, 14,   6, 11,   3,  4,   9,  7,   2, 13,  12,  0,   5, 10,
    3, 13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5,
    0, 14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9,  3,   2, 15,
    13,  8,  10,  1,   3, 15,   4,  2, 11,  6,   7, 12,   0,  5,  14,  9};

const int S3[] = {10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8,
    13,  7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1,
    13,  6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7,
    1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12};

const int S4[] = {7, 13,  14,  3,   0,  6, 9, 10,   1,  2,   8,  5,  11, 12,   4, 15,
    13,  8,  11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9,
    10,  6,   9,  0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4,
    3, 15,   0,  6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14};

const int S5[] = {2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9,
    14, 11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6,
    4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14,
    11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3};

const int S6[] = {12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11,
    10, 15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8,
    9, 14,  15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6,
    4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13};

const int S7[] = {4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1,
    13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6,
    1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2,
    6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12};

const int S8[] = {13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7,
    1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2,
    7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8,
    2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11};


const int P[] = {16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25};

const int FINAL_PERMUTATION[] =  {40, 8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25};


void printCharAsBinary(char input) {
    
    for (int i = 0; i < 8; i++) {
        if ((0x01 << (7-i)) & input) // 0x01 = 00000001
            printf("1");
        else
            printf("0");
    }
}

// "from" and "to" = indices - Created because strncpy wouldnt work sometimes
void copyString(char* target, char *original, int from, int to){
    for (int i = from; i <= to; i++) {
        target[i - from] = original[i];
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
    
    copyString((char*)concatenatedString, c, 0, 3);
    
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
    
    return concatenatedString;
}

// Xors two strings of same size
char* xorString(char *str1, char *str2, int strSize){
    char* xorStr = malloc(strSize*sizeof(char));
    
    for (int i = 0; i < strSize; i++)
        xorStr[i] = str1[i] ^ str2[i];
    
    return xorStr;
}

char applySTable(char block, const int *sTable){
    char row, column, actualMatrixPosition;
    
    row = block & 0b00100001;
    
    if(row & 0b00100000){
        row |= (1 << 1);
        row &= ~(1 << 5);
    }
    
    column = (block & 0b00011110) >> 1;
    
    /*printf("Row:");
    printCharAsBinary(row);
    printf(" | %d", (int)row);
    printf("\n");
    
    printf("Column:");
    printCharAsBinary(column);
    printf(" | %d", (int)column);
    printf("\n");*/
    
    actualMatrixPosition = (15*(int)row + (int)row) + (int)column;
    /*printf("Actual Position: %d", (int)actualMatrixPosition);
    printf("\n");*/
    
    return (char)sTable[actualMatrixPosition];
}

char* f(char *previousRight, char *currentSubkey){
    
    // E(R(n-1))
    char *expandedPreviousRight = applyTable(previousRight, 48, E_BIT_SELECTION);
    
    printf("E(0): ");
    for (int i = 0; i < 6; i++) {
        printCharAsBinary(expandedPreviousRight[i]);
    }
    printf("\n");
    
    // K(n)+E(R(n-1)) = B1B2B3B4B5B6B7B8 (6 by 6)
    char *xorOutputAndKey = xorString(currentSubkey, expandedPreviousRight, 6);
    
    printf("K(1)+E(R(0)): ");
    for (int i = 0; i < 6; i++) {
        printCharAsBinary(xorOutputAndKey[i]);
    }
    printf("\n");
    
    char *b = malloc(8*sizeof(char));
    
    // B1
    b[0] = (xorOutputAndKey[0] & 0b11111100) >> 2;
    
    printf("B1: ");
    printCharAsBinary(b[0]);
    printf("\n");
    
    // B2
    b[1] = (xorOutputAndKey[0] & 0b00000011) << 4;
    b[1] |= (xorOutputAndKey[1] & 0b11110000) >> 4;
    
    printf("B2: ");
    printCharAsBinary(b[1]);
    printf("\n");
    
    // B3
    b[2] = (xorOutputAndKey[1] & 0b00001111) << 2;
    b[2] |= (xorOutputAndKey[2] & 0b11000000) >> 6;
    
    printf("B3: ");
    printCharAsBinary(b[2]);
    printf("\n");
    
    // B4
    b[3] = xorOutputAndKey[2] & 0b00111111;
    
    printf("B4: ");
    printCharAsBinary(b[3]);
    printf("\n");
    
    // B5
    b[4] = (xorOutputAndKey[3] & 0b11111100) >> 2;
    
    printf("B5: ");
    printCharAsBinary(b[4]);
    printf("\n");
    
    // B6
    b[5] = (xorOutputAndKey[3] & 0b00000011) << 4;
    b[5] |= (xorOutputAndKey[4] & 0b11110000) >> 4;
    
    printf("B6: ");
    printCharAsBinary(b[5]);
    printf("\n");
    
    // B7 Error HERE
    b[6] = (xorOutputAndKey[4] & 0b00001111) << 2;
    b[6] |= (xorOutputAndKey[5] & 0b11000000) >> 6;
    
    printf("B7: ");
    printCharAsBinary(b[6]);
    printf("\n");
    
    // B8
    b[7] = xorOutputAndKey[5] & 0b00111111;
    
    printf("B7: ");
    printCharAsBinary(b[7]);
    printf("\n");
    
    char *sb = malloc(4*sizeof(char));
    
    sb[0] = applySTable(b[0], S1) << 4;
    sb[0] |= applySTable(b[1], S2);
    
    sb[1] = applySTable(b[2], S3) << 4;
    sb[1] |= applySTable(b[3], S4);
    
    sb[2] = applySTable(b[4], S5) << 4;
    sb[2] |= applySTable(b[5], S6);
    
    sb[3] = applySTable(b[6], S7) << 4;
    sb[3] |= applySTable(b[7], S8);
    
    printf("SB = ");
    for (int i = 0; i < 4; i++)
        printCharAsBinary(sb[i]);
    printf("\n");
    
    
    return applyTable(sb, 32, P);
}

int main(){
    
    // Key from the example
    /*char key[8];
    key[0] = 0x13;
    key[1] = 0x34;
    key[2] = 0x57;
    key[3] = 0x79;
    key[4] = 0x9B;
    key[5] = 0xBC;
    key[6] = 0xDF;
    key[7] = 0xF1;*/
    
    char key[8];
    key[0] = 0x4B;
    key[1] = 0x41;
    key[2] = 0x53;
    key[3] = 0x48;
    key[4] = 0x49;
    key[5] = 0x53;
    key[6] = 0x41;
    key[7] = 0x42;
    
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
    splitKeys splitKeys[17];
    splitKeys[0].c = malloc(4*sizeof(char));
    splitKeys[0].d = malloc(4*sizeof(char));
    
    copyString(splitKeys[0].c, kPlus, 0, 3);
    // Masking
    splitKeys[0].c[3] &= 0b11110000;
    printf("C: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(splitKeys[0].c[i]);
    }
    printf("\n");
    
    copyString(splitKeys[0].d, kPlus, 3, 7);
    
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
        copyString(splitKeys[i].c, splitKeys[i - 1].c, 0, 3);
        copyString(splitKeys[i].d, splitKeys[i - 1].d, 0, 3);
        for (int j = 1; j <= numLeftShifts[i - 1]; j++){
            splitKeys[i].c = leftShift(splitKeys[i].c);
            splitKeys[i].d = leftShift(splitKeys[i].d);
        }
    }
    
    printf("C16: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(splitKeys[16].c[i]);
    }
    printf("\n");
    
    printf("D16: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(splitKeys[16].d[i]);
    }
    printf("\n");
    
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
    
    printf("K2: ");
    for (int i = 0; i < 6; i++) {
        printCharAsBinary(subkeys[2].k[i]);
    }
    printf("\n");
    
    // Works fine!
    
    // (Subkeys Part) -------------------------------------------------------------------------
    // (Message Part) -------------------------------------------------------------------------
   
    // M = 0123456789ABCDEF
    /*char message[8];
    message[0] = 0x01;
    message[1] = 0x23;
    message[2] = 0x45;
    message[3] = 0x67;
    message[4] = 0x89;
    message[5] = 0xAB;
    message[6] = 0xCD;
    message[7] = 0xEF;*/
    
    // 4e45565251554954
    char message[8];
    message[0] = 0x4E;
    message[1] = 0x45;
    message[2] = 0x56;
    message[3] = 0x52;
    message[4] = 0x51;
    message[5] = 0x55;
    message[6] = 0x49;
    message[7] = 0x54;
    
    // 763549d38b570c0e
    /*char message[8];
    message[0] = 0x76;
    message[1] = 0x35;
    message[2] = 0x49;
    message[3] = 0xD3;
    message[4] = 0x8B;
    message[5] = 0x57;
    message[6] = 0x0C;
    message[7] = 0x0E;*/
    
    char *IP = applyTable(message, 64, IP_1);
    
    printf("IP: ");
    for (int i = 0; i < 8; i++) {
        printCharAsBinary(IP[i]);
    }
    printf("\n");
    
    typedef struct s_messageSplit{
        char *l;
        char *r;
    }t_messageSplit;
    
    t_messageSplit messageSplit[17];
    messageSplit[0].l = malloc(4*sizeof(char));
    messageSplit[0].r = malloc(4*sizeof(char));
    
    copyString(messageSplit[0].l, IP, 0, 3);
    copyString(messageSplit[0].r, IP, 4, 7);
    
    printf("L0: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(messageSplit[0].l[i]);
    }
    printf("\n");
    
    printf("R0: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(messageSplit[0].r[i]);
    }
    printf("\n");
    
    char *test = f(messageSplit[0].r, subkeys[1].k);
    printf("f: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(test[i]);
    }
    printf("\n");
    
    char *r1 = xorString(messageSplit[0].l, test, 4);
    char *l1 = malloc(4*sizeof(char));
    copyString(l1, messageSplit[0].r, 0, 3);
    
    printf("R1: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(r1[i]);
    }
    printf("\n");
    
    printf("L1: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(l1[i]);
    }
    printf("\n");
    
    // Everything works fine untill here ...
    
    // 16 x L(n) = R(n-1) | R(n) = L(n-1) + f(R(n-1), K(n))
    for (int i = 1; i < 17; i++) {
        messageSplit[i].r = xorString(messageSplit[i-1].l, f(messageSplit[i-1].r, subkeys[i].k), 4);
        messageSplit[i].l = malloc(4*sizeof(char));
        copyString(messageSplit[i].l, messageSplit[i-1].r, 0, 3);
    }
    
    char *test2 = test2 = f(r1, subkeys[2].k);
    
    printf("f2: ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(test2[i]);
    }
    printf("\n");
    
    char *r2 = xorString(l1, test2, 4);
    char *l2 = malloc(4*sizeof(char));
    copyString(l2, r1, 0, 3);
    
    printf("R2 = ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(r2[i]);
    }
    printf("\n");
    
    printf("L2 = ");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(l2[i]);
    }
    printf("\n");
    
    //char *L16R16 = malloc(8*sizeof(char));
    
    printf("R2: \n");
    for (int i = 0; i < 4; i++) {
        printCharAsBinary(messageSplit[2].r[i]);
    }
    printf("\n");
    
    
    char *R16L16 = malloc(8*sizeof(char));
    strcat(R16L16, messageSplit[16].r);
    strcat(R16L16, messageSplit[16].l);
    char *finalPermutation = applyTable(R16L16, 64, FINAL_PERMUTATION);
    
    printf("Final Permutation: \n");
    for (int i = 0; i < 8; i++) {
        printCharAsBinary(finalPermutation[i]);
    }
    printf("\n");
    
    printf("Message: ");
    for (int i = 0; i < 8; i++)
        printf("%x", (unsigned char)message[i]);
    printf("\n");
    
    printf("Encrypted Message: ");
     for (int i = 0; i < 8; i++)
         printf("%x", (unsigned char)finalPermutation[i]);
    
    // (Memory Freeing) ------------------------------------------------------------------------
    
    /*free(kPlus);
    for (int i = 16; i >= 0; i--) {
        free(splitKeys[i].c);
        free(splitKeys[i].d);
        free(splitKeys[i].cd);
    }
    for (int i = 15; i >= 0; i--)
        free(subkeys[i].k);
    
    free(subkeys);
    free(IP);*/
    
    printf("\n");
    
    printf("\n");
    
    return 0;
}