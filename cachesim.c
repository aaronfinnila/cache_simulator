#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int handlerequest_cache(char request[], int dataOut, int dataIn);
int handlerequest_dram(char request[], int dataOut, int dataIn);
int toDecimal(char characters[], int hexOrBin);
void toBinary(int decimalCharacters, char binaryArray[]);


int main() {

    char cpurequest[] = "BF";

    int result = handlerequest_cache(cpurequest, 159, 0);

    printf("\nresult: %d\n", result);
    return 0;
}


int handlerequest_cache(char request[], int dataOut, int dataIn) {

    int cache[16] = {0};
    int tagStore[16] = {0};
    bool inCache;

    // CONVERT HEX TO DECIMAL

    int requestDecimal = toDecimal(request, 0);

    // DECIMAL TO BINARY

    char binaryArray[9] = {0};

    toBinary(requestDecimal, binaryArray);

    // READ BINARY DATA

    char readwrite = binaryArray[0];

    printf("\nreadwrite: %c", readwrite);

    char indexChars[7] = {0};

    for (int i = 1; i < 8; i++) {
        indexChars[i-1] = binaryArray[i];
    }

    int indexDecimal = toDecimal(indexChars, 1);

    int cacheIndex = indexDecimal % 16;

    if (cache[cacheIndex] != 0) {
        // READ AND HIT
        if (readwrite == '0') {
            printf("\n%d CACHE READ HIT\n", indexDecimal);
            return cache[cacheIndex];
        // WRITE AND HIT
        } else {
            printf("\n%d CACHE WRITE HIT\n", indexDecimal);
            handlerequest_dram(binaryArray, dataOut, dataIn);
        }
    } else {
        // READ AND MISS
        if (readwrite == '0') {
            printf("\n%d CACHE READ MISS\n", indexDecimal);
            int dramData = handlerequest_dram(binaryArray, dataOut, dataIn);
            return dramData;
        // WRITE AND MISS
        } else {
            printf("\n%d CACHE WRITE MISS\n", indexDecimal);
            handlerequest_dram(binaryArray, dataOut, dataIn);
        }
    }
    return -1;
}

int handlerequest_dram(char request[], int dataOut, int dataIn) {

    int dram[8][8] = {0};
    dram[7][7] = 210;

    // READ BINARY DATA

    char readwrite = request[0];

    char indexChars[7] = {0};

    for (int i = 1; i < 8; i++) {
        indexChars[i-1] = request[i];
    }

    printf("\nindexChars: %s\n", indexChars);

    int indexDecimal = toDecimal(indexChars, 1);

    int row = (int)(indexDecimal/8);
    int col = indexDecimal % 8;

    int data = dram[row][col];
    // READ
    if (readwrite == '0') {
        printf("\n%d DRAM READ\n", indexDecimal);
        return data;
    // WRITE
    } else {
        printf("\n%d DRAM WRITE\n", indexDecimal);
        dram[row][col] = dataOut;
    }

    return -1;
}

void toBinary(int decimalCharacters, char binaryArray[]) {

    binaryArray[8] = '\0';

    for (int i = 7; i >= 0; i--) {
        binaryArray[i] = (decimalCharacters & 1) ? '1' : '0';
        decimalCharacters >>= 1;
    }
}

int toDecimal(char characters[], int hexOrBin) {

    if (hexOrBin == 0) {
    int counter = 0;
    for (int i = 0; i < strlen(characters); i++) {
        int len = strlen(characters);
        char c = characters[i];
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

    } else {
        int count = 0;
        int decimal = 0;
        for (int i = 6; i >= 0; i--) {
            if (characters[i] == '1') {
                decimal += (int)pow(2, count);
            }
            count++;
        }
        return decimal;
    }

    return -1;
}