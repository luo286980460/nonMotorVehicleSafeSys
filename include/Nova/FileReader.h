//
// Created by Lightning on 2017/5/1.
//

#ifndef DES2_0_FILEREADER_H
#define DES2_0_FILEREADER_H

extern "C" {
#include "require.h"

    void ascToBinary(int character, int *ones, int index);

    char BinaryToasc(int *ones, int index);

    void readBinary(unsigned char *temp, int *s, int max);

    void writeBinary(int *temp, char *s);

    int readFile64(FILE *fd, int *s);

    int readChar64(char* butf, int offset, int max, int* s);

    void writeFile64(FILE *fd, int *s);

    void closeFile(FILE *fd);
}

#endif //DES2_0_FILEREADER_H
