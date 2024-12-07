#include "proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



Classe creerClasse(const char* nom, int att, int def, int HPmax, int rest) {
    Classe c;
    strcpy(c.nom, nom);
    c.att = att;
    c.def = def;
    c.HPmax = HPmax;
    c.rest = rest;
    return c;
}



Personnage creerPersonnage(const char* nom, Classe classe, Accessoire* acc1, Accessoire* acc2) {
    Personnage perso;
    strcpy(perso.nom, nom);
    strcpy(perso.classe, classe.nom);
    perso.att = classe.att;
    perso.def = classe.def;
    perso.HP = classe.HPmax;
    perso.HPmax = classe.HPmax;
    perso.rest = classe.rest;
    perso.str = 0;
    perso.nbcomb = 0;
    strcpy(perso.acc_1, acc1 ? acc1->nom : "");
    strcpy(perso.acc_2, acc2 ? acc2->nom : "");
    return perso;
}


void ajoutPerso(ListePerso* liste, Personnage perso) {
    cellulePerso* tmp = (cellulePerso*)malloc(sizeof(cellulePerso));
    if (tmp != NULL) {
        tmp->perso = perso;
        tmp->suivant = *liste;
        *liste = tmp;
    }
}

void ajoutCombattant(ListeCombattant* listeC, Personnage perso) {
    celluleCombattant* nouveau = (celluleCombattant*)malloc(sizeof(celluleCombattant));
    nouveau->perso = perso;
    nouveau->suivant = *listeC;
    *listeC = nouveau;
}

void retirerPerso(ListePerso *liste, Personnage perso) {
    cellulePerso *courant = *liste;
    cellulePerso *precedent = NULL;

    while (courant != NULL) {
        if (strcmp(courant->perso.nom, perso.nom) == 0) {
            if (precedent == NULL) {
                *liste = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }

            free(courant);
            return;
        }
        precedent = courant;
        courant = courant->suivant;
    }
    printf("Personnage pas dans la liste : %s\n", perso.nom);
}


void afficherPersonnage(Personnage perso) {
    printf("          <-%s->\n", perso.nom);
    printf("______________________________\n");
    printf(" Classe: %s\n", perso.classe);
    printf("------------------------------\n");
    printf(" att: %d\n", perso.att);
    printf("------------------------------\n");
    printf(" def: %d\n", perso.def);
    printf("------------------------------\n");
    printf(" HP/HPmax: %d/%d\n", perso.HP, perso.HPmax);
    printf("------------------------------\n");
    printf(" rest: %d\n", perso.rest);
    printf("------------------------------\n");
    printf(" str: %d\n", perso.str);
    printf("------------------------------\n");
    printf(" nbcomb: %d\n", perso.nbcomb);
    printf("------------------------------\n");
    printf(" acc 1: %s\n", strcmp(perso.acc_1, "") == 0 ? "Aucun" : perso.acc_1);
    printf("------------------------------\n");
    printf(" acc 2: %s\n", strcmp(perso.acc_2, "") == 0 ? "Aucun" : perso.acc_2);
    printf("______________________________\n");
    printf("\n");
    printf("\n");
}

void afficherDispoPerso(ListePerso liste) {
    cellulePerso* courant = liste;
    while (courant != NULL) {
        afficherPersonnage(courant->perso);
        courant = courant->suivant;
    }
}


void afficherCombattants(ListeCombattant listeC) {
    celluleCombattant* courant = listeC;
    while (courant != NULL) {
        afficherPersonnage(courant->perso);
        courant = courant->suivant;
    }
}


Ennemi creerEnnemi(const char* nom, int niveau, int attenn, int defenn, int HPenn, int attstrenn) {
    Ennemi enn;
    strcpy(enn.nom, nom);
    enn.niveau = niveau;
    enn.attenn = attenn;
    enn.defenn = defenn;
    enn.HPenn = HPenn;
    enn.attstrenn = attstrenn;
    return enn;
}



void MiseEnPlaceCombat(ListePerso listeP, ListeCombattant* listeC, int nbCombats) {

    afficherDispoPerso(listeP);

    int maxCombattants = (nbCombats <= 5) ? 2 : 3;
    int nbSelectionnes = 0;
    int indicesSelectionnes[maxCombattants];
    memset(indicesSelectionnes, -1, sizeof(indicesSelectionnes));

    while (nbSelectionnes < maxCombattants) {
        printf("Choix du combattant %d (entrez un numéro ou N pour terminer) : ", nbSelectionnes + 1);
        char choix[10];
        scanf("%s", choix);

        if (strcmp(choix, "N") == 0 || strcmp(choix, "n") == 0) {
            if (nbSelectionnes == 0) {
                printf("Vous devez sélectionner au moins un combattant\n");
                continue;
            }
            break;
        }

        int indice = atoi(choix);
        if (indice <= 0) {
            printf("Choix invalide. Veuillez réessayer.\n");
            continue;
        }

        cellulePerso* courant = listeP;
        int position = 1;
        while (courant != NULL && position < indice) {
            courant = courant->suivant;
            position++;
        }

        if (courant == NULL || indiceDejaSelectionne(indicesSelectionnes, nbSelectionnes, indice)) {
            printf("Personnage non disponible ou déjà sélectionné. Veuillez réessayer.\n");
            continue;
        }

        // Ajouter le personnage à la liste des combattants
        ajoutCombattant(listeC, courant->perso);
        indicesSelectionnes[nbSelectionnes] = indice;
        nbSelectionnes++;
    }

    printf("Combat préparé avec les combattants suivants :\n");
    afficherCombattants(*listeC);
}