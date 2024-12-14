#include "proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



void ajoutTaverne(ListeTaverne* liste, ListePerso* dispo, Personnage perso) {
    celluleTaverne* tmp = (celluleTaverne*)malloc(sizeof(celluleTaverne));
    if (tmp != NULL) {
        tmp->perso = perso;
        tmp->suivant = *liste;
        *liste = tmp;

        // Retirer perso
        retirerPerso(dispo, perso);
    }
    return;
}


void recupererationStress(ListeTaverne* liste) {
    celluleTaverne* courant = *liste;
    while (courant != NULL) {
        courant->perso.str -= 25;
        if (courant->perso.str < 0) {
            courant->perso.str = 0;
        }
        courant = courant->suivant;
    }
}


void afficherTaverne(ListeTaverne liste) {
    int index = 1;
    celluleTaverne* courant = liste;

    printf("Taverne\n");
    printf("-------------------------------------------------\n");
    printf(" N° | Nom      | Classe          | att | def | HP/HPmax | rest | str \n");
    printf("-------------------------------------------------\n");
    while (courant != NULL) {
        printf(" %2d | %-8s | %-15s | %-3d | %-3d | %-8d/%-8d | %-4d | %-3d\n",
               index, courant->perso.nom, courant->perso.classe, courant->perso.att,
               courant->perso.def, courant->perso.HP, courant->perso.HPmax,
               courant->perso.rest, courant->perso.str);
        courant = courant->suivant;
        index++;
    }
    printf("-------------------------------------------------\n");
}

void retirerTaverne(ListeTaverne* taverne, ListePerso* dispoPerso) {
    celluleTaverne* courant = *taverne;
    celluleTaverne* precedent = NULL;

    while (courant != NULL) {
        printf("Voulez-vous faire sortir %s de la Taverne ? ? (Y/N): ", courant->perso.nom);
        char choix;
        scanf(" %c", &choix);

        if (choix == 'Y' || choix == 'y') {
            if (precedent == NULL) {
                *taverne = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }

            ajoutPerso(dispoPerso, courant->perso);

            free(courant);
            courant = (precedent == NULL) ? *taverne : precedent->suivant;
        } else {
            precedent = courant;
            courant = courant->suivant;
        }
    }
}