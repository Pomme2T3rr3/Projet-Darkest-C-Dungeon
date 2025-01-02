#include "proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ajouterlot(ListeRoulotte* roulotte, Accessoire acc) {
    celluleRoulotte* nouveau = (celluleRoulotte*)malloc(sizeof(celluleRoulotte));
    if (nouveau != NULL) {
        nouveau->acc = acc;
        nouveau->suivant = *roulotte;
        *roulotte = nouveau;
    }
}

void afficherLot(Accessoire acc) {
    printf("   <-%s->\n", acc.nom);
    printf("______________________________\n");
    printf(" num: %d\n", acc.num);
    printf("------------------------------\n");
    printf(" attbonus: %s\n", acc.attbonus);
    printf("------------------------------\n");
    printf(" defbonus: %s\n", acc.defbonus);
    printf("------------------------------\n");
    printf(" HPbonus: %s\n", acc.HPbonus);
    printf("------------------------------\n");
    printf(" restbonus: %s\n", acc.restbonus);
    printf("------------------------------\n");
    printf(" strred: %d\n", acc.strred);
    printf("------------------------------\n");
    printf(" prix: %d\n", acc.prix);
    printf("______________________________\n");
    printf("\n");
}


void afficherRoulotte(ListeRoulotte roulotte) {
    celluleRoulotte* courant = roulotte;
    while (courant != NULL) {
        afficherLot(courant->acc);
        courant = courant->suivant;
    }
}

void retirerLot(ListeRoulotte* roulotte, ListeAcc* dispoAcc) {
    if (*roulotte == NULL) return;

    celluleRoulotte* courant = *roulotte;
    *roulotte = courant->suivant;

    courant->suivant = *dispoAcc;
    *dispoAcc = courant;
}

void achat(ListeRoulotte* roulotte, ListeAcc* dispoAcc, int* or_joueur) {
    if (*roulotte == NULL) {
        printf("La roulotte est vide. Aucun achat possible.\n");
        return;
    }

    char entree[10];
    printf("Votre or actuel : %d\n", *or_joueur);
    afficherRoulotte(*roulotte); 

    printf("Entrez le numéro de l'accessoire à acheter ou 'Q' pour quitter : ");
    scanf("%s", entree);

    if (strcmp(entree, "Q") == 0 || strcmp(entree, "q") == 0) {
        printf("Vous quittez la roulotte.\n");
        return;
    }

    int choix = atoi(entree);
    if (choix == 0 && strcmp(entree, "0") != 0) {
        printf("Entrée invalide. Veuillez entrer un numéro d'accessoire ou 'Q'.\n");
        return;
    }

    celluleRoulotte* courant = *roulotte;
    celluleRoulotte* precedent = NULL;

    while (courant != NULL) {
        if (courant->acc.num == choix) {
            if (*or_joueur >= courant->acc.prix) {
                *or_joueur -= courant->acc.prix; 
                printf("Vous avez acheté : %s pour %d or.\n", courant->acc.nom, courant->acc.prix);

                if (precedent == NULL) {
                    *roulotte = courant->suivant;
                } else {
                    precedent->suivant = courant->suivant;
                }

                courant->suivant = *dispoAcc;
                *dispoAcc = courant;
                return;

            } else {
                printf("Vous n'avez pas assez d'or !\n");
                return;
            }
        }
        precedent = courant;
        courant = courant->suivant;
    }

    printf("Accessoire non trouvé.\n");
}