#include "proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



Accessoire creerAccessoire(const char* nom, const char* attbonus, const char* defbonus, const char* HPbonus, const char* restbonus, int strred) {
    Accessoire acc;
    strcpy(acc.nom, nom);
    strcpy(acc.attbonus, attbonus);
    strcpy(acc.defbonus, defbonus);
    strcpy(acc.HPbonus, HPbonus);
    strcpy(acc.restbonus, restbonus);
    acc.strred = strred;
    return acc;
}

void ajoutAcc(ListeAcc* liste, Accessoire acc) {
    celluleAcc* tmp = (celluleAcc*)malloc(sizeof(celluleAcc));
    if (tmp != NULL) {
        tmp->acc = acc;
        tmp->suivant = *liste;
        *liste = tmp;
    }
}

void afficherAccessoire(Accessoire acc) {
    printf("   <-%s->\n", acc.nom);
    printf("______________________________\n");
    printf(" attbonus: %s\n", acc.attbonus);
    printf("------------------------------\n");
    printf(" defbonus: %s\n", acc.defbonus);
    printf("------------------------------\n");
    printf(" HPbonus: %s\n", acc.HPbonus);
    printf("------------------------------\n");
    printf(" restbonus: %s\n", acc.restbonus);
    printf("------------------------------\n");
    printf(" strred: %d\n", acc.strred);
    printf("______________________________\n");
    printf("\n");
    printf("\n");
}

void afficherDispoAcc(ListeAcc liste) {
    celluleAcc* courant = liste;
    while (courant != NULL) {
        afficherAccessoire(courant->acc);
        courant = courant->suivant;
    }
}