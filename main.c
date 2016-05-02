#include <stdio.h>
#include <stdlib.h>
#include "des.h"

const int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62,  54, 46,  38,  30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

void print_char_as_binary(char input) {
    int i;
    for (i=0; i<8; i++) {
        char shift_byte = 0x01 << (7-i);
        if (shift_byte & input) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

char* buildKPlus(char *key){
    
    // Initializes k+ with all 0's
    char *kPlus = malloc(8*sizeof(char));
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


int main(){
	
    char key[8];
	key[0] = 0x13;
	key[1] = 0x34;
	key[2] = 0x57;
	key[3] = 0x79;
	key[4] = 0x9B;
	key[5] = 0xBC;
	key[6] = 0xDF;
	key[7] = 0xF1;
    
	//printf("K = %s", key); // Should print _4Wy____
    printf("K = ");
    
    for (int i = 0; i < 8; i++)
        print_char_as_binary(key[i]);
    
    printf("\n");
    
    char *kPlus = buildKPlus(key);
    
    printf("K+ = ");
    for (int i = 0; i < 7; i++) {
        print_char_as_binary(kPlus[i]);
    }
    printf("\n");
    
    /*
    Binary stuff for tests
    char a = 0b00000100;
    print_char_as_binary(a);
    printf("\n");
    a |= (1u << (7 - 1));
    print_char_as_binary(a);
    */
    
	
    return 0;
}
