#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Classe {
    char nom[50];
    int att;
    int def;
    int HPmax;
    int rest;
} Classe;

typedef struct Accessoire {
    int num;
    char nom[50];
    char attbonus[10];
    char defbonus[10];
    char HPbonus[10];
    char restbonus[10];
    int strred;
    int prix;
} Accessoire;

typedef struct Personnage {
    int num;
    char nom[50];
    char classe[50];
    int att;
    int def;
    int HP;
    int HPmax;
    int rest;
    int str;
    int nbcomb;
    Accessoire *acc_1;
    Accessoire *acc_2;
} Personnage;

typedef struct Ennemi {
    char nom[50];
    int niveau;
    int attenn;
    int defenn;
    int HPenn;
    int attstrenn;
} Ennemi;

typedef struct celluleAcc {
    Accessoire acc;
    struct celluleAcc* suivant;
} celluleAcc, *ListeAcc;


typedef struct cellulePerso {
    Personnage perso;
    struct cellulePerso* suivant;
} cellulePerso, *ListePerso;

typedef struct celluleCombattant {
    Personnage perso;
    struct celluleCombattant* suivant;
} celluleCombattant, *ListeCombattant;

typedef struct celluleSanitarium {
    Personnage perso;
    struct celluleSanitarium* suivant;
} celluleSanitarium, *ListeSanitarium;

typedef struct celluleTaverne {
    Personnage perso;
    struct celluleTaverne* suivant;
} celluleTaverne, *ListeTaverne;

typedef struct celluleRoulotte {
    Accessoire acc;
    struct celluleRoulotte* suivant;
} celluleRoulotte, *ListeRoulotte;

Classe creerClasse(const char* nom, int att, int def, int HPmax, int rest) {
    Classe c;
    strcpy(c.nom, nom);
    c.att = att;
    c.def = def;
    c.HPmax = HPmax;
    c.rest = rest;
    return c;
}

Accessoire creerAccessoire(int num, const char* nom, const char* attbonus, const char* defbonus, const char* HPbonus, const char* restbonus, int strred, int prix) {
    Accessoire acc;
    acc.num = num;
    strcpy(acc.nom, nom);
    strcpy(acc.attbonus, attbonus);
    strcpy(acc.defbonus, defbonus);
    strcpy(acc.HPbonus, HPbonus);
    strcpy(acc.restbonus, restbonus);
    acc.strred = strred;
    acc.prix = prix;
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

Personnage creerPersonnage(int num, const char* nom, Classe classe, Accessoire* acc1, Accessoire* acc2) {
    Personnage perso;
    perso.num = num;
    strcpy(perso.nom, nom);
    strcpy(perso.classe, classe.nom);
    perso.att = classe.att;
    perso.def = classe.def;
    perso.HP = classe.HPmax;
    perso.HPmax = classe.HPmax;
    perso.rest = classe.rest;
    perso.str = 0;
    perso.nbcomb = 0;
    perso.acc_1 = acc1; 
    perso.acc_2 = acc2;
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
    printf(" num: %d\n", perso.num);
    printf("------------------------------\n");
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
    printf(" acc 1: %s\n", perso.acc_1 == NULL ? "Aucun" : perso.acc_1->nom);
    printf("------------------------------\n");
    printf(" acc 2: %s\n", perso.acc_2 == NULL ? "Aucun" : perso.acc_2->nom);
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


void actionsPerso(ListeCombattant listeC, Ennemi* enn) {

    celluleCombattant* courant = listeC;
    while (courant != NULL) {
        printf("Action de %s, A : Attaque, D : Defendre, R : Restaurer. ", courant->perso.nom);
        char action;
        scanf(" %c", &action); 

        int bonusAttaque = 0, bonusDefense = 0, bonusRestauration = 0;

        if (courant->perso.acc_1 != NULL) {
            bonusAttaque += atoi(courant->perso.acc_1->attbonus);
            bonusDefense += atoi(courant->perso.acc_1->defbonus);
            bonusRestauration += atoi(courant->perso.acc_1->restbonus);
        }

        if (courant->perso.acc_2 != NULL) {
            bonusAttaque += atoi(courant->perso.acc_2->attbonus);
            bonusDefense += atoi(courant->perso.acc_2->defbonus);
            bonusRestauration += atoi(courant->perso.acc_2->restbonus);
        }

        if (action == 'A') {

            int attTotal = courant->perso.att + bonusAttaque;
            float roll = 0.8 + ((float)rand() / (float)RAND_MAX) * (1.2 - 0.8); 
            int dommages = attTotal > enn->defenn ? (attTotal - enn->defenn) * roll : 1;

            enn->HPenn -= dommages;
            printf("%s attaque et inflige %d dégâts. %s a %d HP restants.\n", courant->perso.nom, dommages, enn->nom, enn->HPenn);

        } else if (action == 'D') {
            courant->perso.def += courant->perso.def * 0.1; 
            printf("%s défend. Défense augmentée pour ce tour.\n", courant->perso.nom);

        } else if (action == 'R') {
            printf("Quel personnage voulez-vous restaurer (1, 2, 3...) ? ");
            int cible;
            scanf("%d", &cible);

            celluleCombattant* ciblePerso = listeC;
            for (int i = 1; ciblePerso != NULL && i < cible; i++) {
                ciblePerso = ciblePerso->suivant;
            }
            if (ciblePerso != NULL) {
                int restauration = courant->perso.rest + bonusRestauration;
                ciblePerso->perso.HP = (ciblePerso->perso.HP + restauration > ciblePerso->perso.HPmax)
                                           ? ciblePerso->perso.HPmax
                                           : ciblePerso->perso.HP + restauration;
                printf("%s restaure %d HP pour %s. HP actuel : %d/%d.\n",
                       courant->perso.nom, restauration, ciblePerso->perso.nom,
                       ciblePerso->perso.HP, ciblePerso->perso.HPmax);
            } else {
                printf("Personnage invalide.\n");
            }
        } else {
            printf("Action invalide, %s passe son tour.\n", courant->perso.nom);
        }
        courant = courant->suivant;
    }
}


void actionEnn(ListeCombattant listeC, Ennemi* enn) {
    if (listeC == NULL) {
        printf("Pas de combattants disponibles pour l'ennemi à attaquer.\n");
        return;
    }

    int nbCombattants = 0;
    celluleCombattant* courant = listeC;
    while (courant != NULL) {
        nbCombattants++;
        courant = courant->suivant;
    }

    int cibleIndex = rand() % nbCombattants;
    courant = listeC;
    for (int i = 0; i < cibleIndex; i++) {
        courant = courant->suivant;
    }

    int dommage = (enn->attenn - courant->perso.def);
    if (dommage > 0) {
        courant->perso.HP -= dommage;
        printf("L'ennemi %s attaque %s et inflige %d dégâts. %s a maintenant %d/%d HP.\n", enn->nom, courant->perso.nom, dommage, courant->perso.nom, courant->perso.HP, courant->perso.HPmax);

        if (courant->perso.HP <= 0) {
            printf("%s est tombé au combat !\n", courant->perso.nom);
        }
    } else {
        printf("L'attaque de %s n'a pas pu passer la défense de %s.\n", enn->nom, courant->perso.nom);
    }
}

void combat(ListeCombattant* listeC, Ennemi* enn) {

    srand(time(NULL)); 
    int tour = rand() % 2; 

    while (enn->HPenn > 0 && *listeC != NULL) {
        if (tour == 0) {
            printf("\n--- Tour des Personnages ---\n");
            actionsPerso(*listeC, enn);
            tour = 1; 
        } else {
            printf("\n--- Tour de l'Ennemi ---\n");
            actionEnn(*listeC, enn);
            tour = 0; 
        }

        if (enn->HPenn <= 0) {
            printf("L'ennemi %s a été vaincu !\n", enn->nom);
            return;
        }

        celluleCombattant* courant = *listeC;
        celluleCombattant* precedent = NULL;
        while (courant != NULL) {
            if (courant->perso.HP <= 0) {
                if (precedent == NULL) {
                    *listeC = courant->suivant;
                } else {
                    precedent->suivant = courant->suivant;
                }
                free(courant);
                courant = (precedent == NULL) ? *listeC : precedent->suivant;
            } else {
                precedent = courant;
                courant = courant->suivant;
            }
        }
    }

    if (*listeC == NULL) {
        printf("Tous vos personnages ont été vaincus. Défaite...\n");
    }
}


void MiseEnPlaceCombat(ListePerso listeP, ListeCombattant* listeC, int nbCombats, Ennemi* enn) {
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

        int numero = atoi(choix);
        if (numero <= 0) {
            printf("Choix invalide. Veuillez entrer un numéro valide.\n");
            continue;
        }

        cellulePerso* courant = listeP;
        while (courant != NULL) {
            if (courant->perso.num == numero) {
                if (indiceDejaSelectionne(indicesSelectionnes, nbSelectionnes, numero)) {
                    printf("Ce personnage est déjà sélectionné. Veuillez en choisir un autre.\n");
                    courant = NULL; 
                }
                break;
            }
            courant = courant->suivant;
        }

        if (courant == NULL) {
            printf("Numéro non trouvé. Veuillez réessayer.\n");
            continue;
        }

        ajoutCombattant(listeC, courant->perso);
        indicesSelectionnes[nbSelectionnes] = numero;
        nbSelectionnes++;
    }

    printf("Combat préparé avec les combattants suivants :\n");
    printf("\n");
    afficherCombattants(*listeC);
    printf("\n");
    combat(listeC, enn);
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


int main() {

    srand(time(NULL));

    int nbcombat = 0;

    // innitialisation des listes chaines
    ListePerso dispoPerso = NULL;
    ListeCombattant listeC = NULL;
    ListeAcc dispoAcc = NULL;
    ListeSanitarium sanitarium = NULL;
    ListeTaverne taverne = NULL;
    ListeRoulotte roulotte = NULL;

    int or_joueur = 0;

    // création des classes
    Classe classes[] = {
        creerClasse("Furie", 13, 0, 20, 0),
        creerClasse("Vestale", 3, 0, 20, 10),
        creerClasse("Chasseur_de_primes", 7, 3, 25, 3),
        creerClasse("Maître_chien", 10, 6, 17, 5)
    };

    int nombreClasses = sizeof(classes) / sizeof(classes[0]);
    int indicesSelectionnes[4]; // Tableau pour enregistrer les indices
    int compteur = 0;

    while (compteur < 4) {
        int nouvelIndice = rand() % nombreClasses;
        if (!indiceDejaSelectionne(indicesSelectionnes, compteur, nouvelIndice)) {
            indicesSelectionnes[compteur] = nouvelIndice;
            compteur++;
        }
    }

    // création des accesoires
    Accessoire pendentif_tranchant = creerAccessoire(1, "pendentif_tranchant", "+5", "+1", "+0", "+0", 0, 7);
    Accessoire calice_de_jeunesse = creerAccessoire(2, "calice_de_jeunesse", "+0", "+3", "+5", "+0", 5, 16);
    Accessoire anneau_magique = creerAccessoire(3, "Anneau Magique", "+3", "+2", "+0", "+5", 10, 7);
    Accessoire amulette_divine = creerAccessoire(4, "Amulette Divine", "+0", "+5", "+10", "+0", 15, 32);

    // création des personnages
    Personnage Boudicca = creerPersonnage(6, "Boudicca", classes[indicesSelectionnes[0]], NULL, NULL);
    Personnage Junia = creerPersonnage(5, "Junia", classes[indicesSelectionnes[1]], NULL, NULL);
    Personnage Flash = creerPersonnage(4, "Flash", classes[indicesSelectionnes[2]], NULL, NULL);
    Personnage Gordi = creerPersonnage(3, "Gordi", classes[indicesSelectionnes[3]], NULL, NULL);
    Personnage Tritus = creerPersonnage(2, "Tritus", classes[indicesSelectionnes[2]], NULL, NULL);
    Personnage Ragnard = creerPersonnage(1, "Ragnard", classes[indicesSelectionnes[0]], NULL, NULL);

    // création des énnemi
    Ennemi Brigand = creerEnnemi("Brigand", 1, 3, 3, 9, 0);
    Ennemi Squelette = creerEnnemi("Squelette", 2, 6, 4, 13, 10);
    Ennemi Goule = creerEnnemi("Goule", 3, 8, 8, 16, 20);

    ajoutPerso(&dispoPerso, Boudicca);
    ajoutPerso(&dispoPerso, Junia);
    ajoutPerso(&dispoPerso, Flash);
    ajoutPerso(&dispoPerso, Gordi);
    ajoutPerso(&dispoPerso, Tritus);
    ajoutPerso(&dispoPerso, Ragnard);

    ajoutAcc(&dispoAcc, pendentif_tranchant);
    ajoutAcc(&dispoAcc, calice_de_jeunesse);

    ajouterlot(&roulotte, anneau_magique);
    ajouterlot(&roulotte, amulette_divine);

    printf("\n");
    printf("Personnages disponibles:\n");
    printf("\n");
    afficherDispoPerso(dispoPerso);

    printf("\n");
    printf("Accessoires disponibles:\n");
    printf("\n");
    afficherDispoAcc(dispoAcc);

    afficherTaverne(taverne);

    //test sanitarium
    /*
    ajoutSanitarium(&sanitarium, &dispoPerso, Flash);
    afficherDispoPerso(dispoPerso);
    afficherSanitarium(sanitarium);
    retirerDuSanitarium(&sanitarium, &dispoPerso);
    afficherDispoPerso(dispoPerso); */

    // test mise en place combat
    printf("Mise en place du combat :\n");
    MiseEnPlaceCombat(dispoPerso, &listeC, nbcombat, &Brigand);

    printf("\n");
    printf("Roulotte :\n");
    afficherLot(anneau_magique);
    achat(&roulotte, &dispoAcc, &or_joueur);
}
