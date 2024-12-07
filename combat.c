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


int indiceDejaSelectionne(int* indices, int taille, int indice) {
    for (int i = 0; i < taille; i++) {
        if (indices[i] == indice) {
            return 1;
        }
    }
    return 0;
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