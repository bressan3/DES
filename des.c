#include <stdio.h>
#include<stdlib.h>
#include "des.h"

char* generateKey(){
	char key[8];
	for(int i = 0; i < 8; i++)
			key[i] = rand()%255;

	return key;
}
