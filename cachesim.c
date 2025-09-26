#include <stdio.h>
#include <string.h>
#include <math.h>

int handlerequest_cache(char request[]);
int handlerequest_dram(char request[]);
int toDecimal(char characters[], int hexOrBin);
void toBinary(int decimalCharacters, char binaryArray[]);


int main() {

    char cpurequest[] = "3F";

    int result = handlerequest_cache(cpurequest);

    printf("\nresult: %d\n", result);
    return 0;
}


int handlerequest_cache(char request[]) {

    // CONVERT HEX TO DECIMAL

    int requestDecimal = toDecimal(request, 0);

    // DECIMAL TO BINARY

    char binaryArray[9] = {0};

    toBinary(requestDecimal, binaryArray);

    int cache[16] = {0};

    int tagStore[16] = {0};

    // READ BINARY DATA

    char readwrite = binaryArray[0];

    if (readwrite == '0') {

        char indexChars[7] = {0};

        for (int i = 1; i < 8; i++) {
            indexChars[i-1] = binaryArray[i];
        }

        printf("\nindexChars: %s\n", indexChars);

        int indexDecimal = toDecimal(indexChars, 1);

        printf("\nindexDecimal: %d\n", indexDecimal);

        int cacheIndex = indexDecimal % 16;

        // IF IN CACHE, RETURN DATA. IF NOT, SEND REQUEST TO DRAM 

        if (cache[cacheIndex] != 0) {
            printf("\nCACHE READ HIT\n");
            return cache[cacheIndex];
        } else {
            printf("\nCACHE READ MISS\n");

            int dramData = handlerequest_dram(binaryArray);
            return dramData;
        }

    } else {

    }

    printf("\n\nCache:\n\n");
    for (int i = 0; i < 16; i++) {
        printf("[%d] = %d\n", i, cache[i]);
    }
}

int handlerequest_dram(char request[]) {

    // READ BINARY DATA

    int dram[8][8] = {0};
    dram[7][7] = 210;

    char readwrite = request[0];

    char indexChars[7] = {0};

    for (int i = 1; i < 8; i++) {
        indexChars[i-1] = request[i];
    }

    int indexDecimal = toDecimal(indexChars, 1);

    int row = (int)(indexDecimal/8);
    int col = indexDecimal % 8;

    if (readwrite == '0') {
        int data = dram[row][col];
        return data;
    } else {

    }
    
    printf("\n\nDRAM:\n\n");
    for (int i = 0; i < 8; i++) {
        for (int j =0; j < 8; j++) {
            printf("[%d][%d] = %d\n", i, j, dram[i][j]);
        }
    }

    return -1;
}

void toBinary(int decimalCharacters, char binaryArray[]) {

    binaryArray[8] = '\0';

    for (int i = 7; i >= 0; i--) {
        binaryArray[i] = (decimalCharacters & 1) ? '1' : '0';
        decimalCharacters >>= 1;
    }
    
    printf("\nbinaryChars: %s\n", binaryArray);
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
                printf("\ndecimal: %d", decimal);
            }
            count++;
        }
        return decimal;
    }

    return -1;
}