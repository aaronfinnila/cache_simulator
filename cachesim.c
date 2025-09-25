#include <stdio.h>

#define BLOCKSIZE = 1
#define DRAM_ADDRESS_WIDTH = 6

int handlerequest_cache(char request[]);
int handlerequest_dram(char request[]);
int toDecimal(char hexaCharacters[]);
char toBinary(int decimalCharacters);


int main() {

    int cpuregisters[8] = {0};
    char cpurequest[] = "3F";

    int result = handlerequest_cache(cpurequest);

/*     printf("\n\nCurrent status\n\n");
    printf("\nRegisters:\n\n");
    for (int i = 0; i < 8; i++) {
        printf("[%d] = %d\n", i, cpuregisters[i]);
    }
    printf("\n\nCache:\n\n");
    for (int i = 0; i < 16; i++) {
        printf("[%d] = %d\n", i, cache[i]);
    }
    printf("\n\nDRAM:\n\n");
    for (int i = 0; i < 8; i++) {
        for (int j =0; j < 8; j++) {
            printf("[%d][%d] = %d\n", i, j, dram[i][j]);
        }
    } */

    return 0;
}

int handlerequest_cache(char request[]) {

    int requestDecimal = toDecimal(request);

    char requestBinary[] = toBinary(requestDecimal);

    int cache[16] = {0};

    int readwrite = requestBinary[0];

    if (readwrite == 0) {

        char indexChars[] = {0};

        for (int i = 1; i < 7; i++) {
            indexChars[i-1] = request[i];
        }

        if (cache[])

    } else {

    }

}

int handlerequest_dram(char request[]) {

    int dram[8][8] = {0};

}

char toBinary(int decimalCharacters) {

    char binaryCharacters[9] = {0};

    binaryCharacters[8] = '\0';

    for (int i = 7; i >= 0; i--) {
        binaryCharacters[i] = (decimalCharacters & 1) ? 1 : 0;
        decimalCharacters >>= 1;
    }
    
    return binaryCharacters;
}

int toDecimal(char hexaCharacters[]) {
    int counter = 0;
    for (int i = 0; i < strlen(hexaCharacters); i++) {
        int len = strlen(hexaCharacters);
        char c = hexaCharacters[i];
        int num = 0;
        if (c > 47 && c < 58) {
            num = c - 48;
        } else if (c > 64 && c < 71) {
            num = c - 55;
        } else {
            num = c - 87;
        }
        num = num * (int)pow(16, len-i-1);
        counter += num;
    }
    return counter;
}