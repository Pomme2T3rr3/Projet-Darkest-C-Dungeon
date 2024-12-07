#include "proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




void ajoutSanitarium(ListeSanitarium* liste, ListePerso* dispo, Personnage perso) {
    celluleSanitarium* tmp = (celluleSanitarium*)malloc(sizeof(celluleSanitarium));
    if (tmp != NULL) {
        tmp->perso = perso;
        tmp->suivant = *liste;
        *liste = tmp;

        // Retirer perso
        retirerPerso(dispo, perso);
    }
    return;
}


void recupererationHP(ListeSanitarium* liste) {
    celluleSanitarium* courant = *liste;
    while (courant != NULL) {
        courant->perso.HP += 7;
        if (courant->perso.HP > courant->perso.HPmax) {
            courant->perso.HP = courant->perso.HPmax;
        }
        courant = courant->suivant;
    }
}


void afficherSanitarium(ListeSanitarium liste) {
    int index = 1;
    celluleSanitarium* courant = liste;

    printf("Sanitarium\n");
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


void retirerDuSanitarium(ListeSanitarium* sanitarium, ListePerso* dispoPerso) {
    celluleSanitarium* courant = *sanitarium;
    celluleSanitarium* precedent = NULL;

    while (courant != NULL) {
        printf("Voulez-vous faire sortir %s du sanitarium ? (Y/N): ", courant->perso.nom);
        char choix;
        scanf(" %c", &choix);

        if (choix == 'Y' || choix == 'y') {
            if (precedent == NULL) {
                *sanitarium = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }

            ajoutPerso(dispoPerso, courant->perso);

            free(courant);
            courant = (precedent == NULL) ? *sanitarium : precedent->suivant;
        } else {
            precedent = courant;
            courant = courant->suivant;
        }
    }
}