#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* anterior;
    struct No* proximo;
} No;

void remover_final(No** cabeca) {
    if (*cabeca == NULL) {
        return;  
    }

    No* ultimo = *cabeca;
    
    while (ultimo->proximo != NULL) {
        ultimo = ultimo->proximo;
    }

    if (ultimo->anterior == NULL) {
        free(ultimo);
        *cabeca = NULL; 
    } else {
        ultimo->anterior->proximo = NULL; 
        free(ultimo); 
    }
}

int main() {
    No* CABECA = NULL;

    remover_final(&CABECA); 

    return 0; 
}

