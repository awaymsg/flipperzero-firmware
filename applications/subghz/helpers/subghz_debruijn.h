#pragma once

#include <m-string.h>

typedef struct
{
    string_t debruijnstr;
    uint8_t a[100];
    uint8_t n;
    uint8_t bitcount;
    uint8_t byte;
} DeBruijnData;

void DeBruijn(uint8_t codelength, string_t outputstr);