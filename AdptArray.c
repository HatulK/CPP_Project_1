#include <malloc.h>
#include <memory.h>
#include "AdptArray.h"

typedef struct AdptArray_ {
    PElement* pElementArray;
    int size;
    DEL_FUNC del;
    COPY_FUNC copy;
    PRINT_FUNC print;
} *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
    if(copyFunc==NULL||delFunc==NULL||printFunc==NULL) return NULL;
    PAdptArray arr = malloc(sizeof(struct AdptArray_));
    if (!arr) {
        return NULL;
    }
    arr->size = 0;
    arr->pElementArray = malloc(sizeof(PElement)*arr->size);
    arr->del = delFunc;
    arr->copy = copyFunc;
    arr->print = printFunc;
    return arr;
}

void DeleteAdptArray(PAdptArray pAdptArray) {
    if (pAdptArray == NULL) return;
    if (pAdptArray->pElementArray == NULL) return;
    for (int i = 0; i < pAdptArray->size; ++i) {
        if (pAdptArray->pElementArray[i]!=NULL) pAdptArray->del(pAdptArray->pElementArray[i]);
    }
    free(pAdptArray->pElementArray);
    free(pAdptArray);
}

Result SetAdptArrayAt(PAdptArray pAdptArray, int num, PElement pElement) {
    if (!pAdptArray) return FAIL;
    PElement* newpElementArray=NULL;
    if (num >= pAdptArray->size) {
        newpElementArray = calloc((num + 1), sizeof(PElement));
        if (!newpElementArray) return FAIL;
        memcpy(newpElementArray, pAdptArray->pElementArray, (pAdptArray->size) * sizeof(PElement));
        free(pAdptArray->pElementArray);
        pAdptArray->pElementArray = newpElementArray;
        pAdptArray->size = num + 1;
    }
    if (pAdptArray->pElementArray[num] != NULL) pAdptArray->del((pAdptArray->pElementArray[num]));
    pAdptArray->pElementArray[num] = pAdptArray->copy(pElement);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pAdptArray, int num) {
    if (!pAdptArray||((pAdptArray->size) - 1) <= num) {
        return NULL;
    }
    PElement copy = NULL;
    if(pAdptArray->pElementArray[num]!=NULL)  copy = pAdptArray->copy(pAdptArray->pElementArray[num]);
    return copy;
}

int GetAdptArraySize(PAdptArray pAdptArray) {
    if (!pAdptArray) return -1;
    else return pAdptArray->size;
}

void PrintDB(PAdptArray pAdptArray) {
    if (!pAdptArray) {
        return;
    }
    if (pAdptArray->size == 0) {
        return;
    }
    for (int i = 0; i < pAdptArray->size; ++i) {
        if ((pAdptArray->pElementArray[i]) != NULL) {
            pAdptArray->print((pAdptArray->pElementArray)[i]);
        }
    }
}