#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

int handlerequest_cache(char request[], int dataOut, int dataIn);
int handlerequest_dram(char request[], int dataOut, int dataIn);
int toDecimal(char characters[], int hexOrBin);
void toBinary(int decimalCharacters, char binaryArray[]);
void printDram(int dram[8][8]);
void printCache(int cache[16]);


int main() {
    int requests = 0;
    char answer[20] = "";

    while (requests <= 16) {

        // READ USER INPUT AND PASS IT TO THE CACHE

        printf("\nGive hexadecimal number (for address + read/write) and Data_out and Data_in\nExample: 9B 100 0\n(Max 20 characters total, max hex value FF)\n");
        fflush(stdout);
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = '\0';

        char cpurequest[3] = "";
        cpurequest[0] = answer[0];
        cpurequest[1] = answer[1];

        int Data_out;
        int Data_in;
        bool dataOutProcessed = false;
        char tempArray[9] = "";
        int j = 0;

        for (int i = 3; answer[i] != '\0'; i++) {
            if (answer[i] != ' ') {
                if (dataOutProcessed == false) {
                tempArray[i-3] = answer[i];
                } else {
                    tempArray[j++] = answer[i];
                }
            } else {
                Data_out = atoi(tempArray);
                memset(tempArray, 0, sizeof(tempArray));
                dataOutProcessed = true;
            }
        }

        Data_in = atoi(tempArray);

        printf("\ncpurequest: %s, Data_out: %d, Data_in: %d\n", cpurequest, Data_out, Data_in);

        int result = handlerequest_cache(cpurequest, Data_out, Data_in);

        printf("\nresult: %d\n", result);
    }


    return 0;
}


int handlerequest_cache(char request[], int dataOut, int dataIn) {

    int cache[16] = {0};
    int tagStore[16] = {0};

    // CONVERT HEX TO DECIMAL

    int requestDecimal = toDecimal(request, 0);

    // DECIMAL TO BINARY

    char binaryArray[9] = {0};

    toBinary(requestDecimal, binaryArray);

    // READ BINARY DATA

    char readwrite = binaryArray[0];

/*     printf("\nreadwrite: %c", readwrite); */

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
            printCache(cache);
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
            printCache(cache);
            return dramData;
        // WRITE AND MISS
        } else {
            printf("\n%d CACHE WRITE MISS\n", indexDecimal);
            handlerequest_dram(binaryArray, dataOut, dataIn);
        }
    }
    printCache(cache);
    return -1;
}

int handlerequest_dram(char request[], int dataOut, int dataIn) {

    int dram[8][8] = {0};

    // READ BINARY DATA

    char readwrite = request[0];

    char indexChars[7] = {0};

    for (int i = 1; i < 8; i++) {
        indexChars[i-1] = request[i];
    }

/*     printf("\nindexChars: %s\n", indexChars); */

    int indexDecimal = toDecimal(indexChars, 1);

    int row = (int)(indexDecimal/8);
    int col = indexDecimal % 8;

    int data = dram[row][col];
    // READ
    if (readwrite == '0') {
        printf("\n%d DRAM READ\n", indexDecimal);
        printDram(dram);
        return data;
    // WRITE
    } else {
        printf("\n%d DRAM WRITE\n", indexDecimal);
        dram[row][col] = dataOut;
    }


    printDram(dram);
    return -1;
}

void printDram(int dram[8][8]) {

    printf("\nDRAM STATUS:\n\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("[%d][%d]: %d\n", i, j, dram[i][j]);
        }
    }
}

void printCache(int cache[16]) {

    printf("\nCACHE STATUS: \n\n");
    for (int i = 0; i < 16; i++) {
        printf("[%d]: %d\n", i, cache[i]);
    }
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