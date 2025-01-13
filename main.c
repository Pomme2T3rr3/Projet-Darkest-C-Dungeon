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
    /**
     * @brief Ajoute un accessoire à une liste chaînée d'accessoires.
     *
     * Cette fonction crée une nouvelle cellule pour un accessoire donné 
     * et l'ajoute au début de la liste chaînée des accessoires.
     *
     * @param liste Pointeur vers la liste chaînée d'accessoires.
     * 
     * @param acc   L'accessoire à ajouter (de type Accessoire).
     */
    celluleAcc* tmp = (celluleAcc*)malloc(sizeof(celluleAcc));
    if (tmp != NULL) {
        tmp->acc = acc;
        tmp->suivant = *liste;
        *liste = tmp;
    }
}

void afficherAccessoire(Accessoire acc) {
    /**
     * @brief Affiche les détails d'un accessoire.
     *
     * Cette fonction affiche les informatios d'un accessoire
     *
     * @param acc L'accessoire à afficher (de type Accessoire).
     */
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
    /**
     * @brief Affiche tous les accessoires disponibles dans une liste.
     *
     * Cette fonction affice les accessoires disponibles.
     *
     * @param liste La liste chaînée des accessoires (de type ListeAcc).
     */
    celluleAcc* courant = liste;
    while (courant != NULL) {
        afficherAccessoire(courant->acc);
        courant = courant->suivant;
    }
}


Accessoire* retirerAcc(ListeAcc* liste, int id) {
    /**
     * @brief Retire un accessoire d'une liste chaînée d'accessoires en fonction de son identifiant.
     *
     * @param liste Un pointeur vers la liste chaînée des accessoires (de type ListeAcc*).
     * @param id L'identifiant de l'accessoire à retirer.
     * @return Un pointeur vers l'accessoire retiré (de type Accessoire*) si trouvé, ou NULL si aucun accessoire avec 
     *         l'identifiant donné n'est trouvé.
     *
     */
    ListeAcc courant = *liste;
    ListeAcc precedent = NULL;

    while (courant != NULL) {
        if (courant->acc.num == id) {
            if (precedent == NULL) {
                *liste = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }
            return &courant->acc;
        }
        precedent = courant;
        courant = courant->suivant;
    }
    return NULL;
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
    /**
     * @brief Ajoute un personnage à la liste chaînée de personnages.
     *
     * @param liste Un pointeur vers la liste chaînée des personnages (de type ListePerso*).
     * @param perso Le personnage à ajouter (de type Personnage).
     */
    cellulePerso* tmp = (cellulePerso*)malloc(sizeof(cellulePerso));
    if (tmp != NULL) {
        tmp->perso = perso;
        tmp->suivant = *liste;
        *liste = tmp;
    }
}

void ajoutCombattant(ListeCombattant* listeC, Personnage perso) {
    /**
     * @brief Ajoute un personnage à la liste chaînée de personnages combattants.
     *
     * @param listeC Pointeur vers la tête de la liste chaînée des combattants.
     *               La liste sera mise à jour pour inclure le nouveau combattant.
     * @param perso Le personnage à ajouter à la liste des combattants.
     */
    celluleCombattant* nouveau = (celluleCombattant*)malloc(sizeof(celluleCombattant));
    nouveau->perso = perso;
    nouveau->suivant = *listeC;
    *listeC = nouveau;
}

void retirerPerso(ListePerso *liste, Personnage perso) {
    /**
     * @brief Retire un personnage de la liste chaînée des personnages.
     *
     * @param liste Pointeur vers la tête de la liste chaînée des personnages.
     *              La liste sera mise à jour après la suppression du personnage.
     * @param perso Le personnage à retirer de la liste. La comparaison se fait
     *              sur le nom du personnage.
     */
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
    /**
     * @brief Affiche les informations d'un personnage.
     *
     * @param perso Les infos du personnage à afficher.
     */
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
    /**
     * @brief Affiche les personnages disponible.
     *
     * @param liste La liste des personnages à afficher. Chaque personnage sera affiché individuellement 
     *              avec ses informations détaillées.
     */
    cellulePerso* courant = liste;
    while (courant != NULL) {
        afficherPersonnage(courant->perso);
        courant = courant->suivant;
    }
}


void afficherCombattants(ListeCombattant listeC) {
     /**
     * @brief Affiche les personnages combattants
     *
     * @param listeC La liste des personnages combattants à afficher.
     */
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
    /**
     * @brief Vérifie si un indice a déjà été sélectionné dans un tableau.
     *
     * @param indices Le tableau d'indices à vérifier.
     * @param taille La taille du tableau `indices`, indique le nombre d'éléments dans le tableau.
     * @param indice L'indice à vérifier dans le tableau.
     * 
     * @return Retourne 1 si l'indice est déjà présent dans le tableau, sinon retourne 0.
     */
    for (int i = 0; i < taille; i++) {
        if (indices[i] == indice) {
            return 1;
        }
    }
    return 0;
}


void actionsPerso(ListeCombattant listeC, Ennemi* enn) {
    /**
     * @brief Permet aux personnages de la liste d'effectuer une action (sélectionnée dans le terminal par une lettre) 
     *        durant leur tour.
     *
     * @param listeC La liste des combattants qui vont exécuter leurs actions.
     * @param enn L'ennemi contre lequel les personnages vont interagir.
     */

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
    /**
     * @brief Permet à un ennemi d'attaquer un combattant au hasard dans la liste des personnages combattants.
     *
     * @param listeC La liste des combattants présents dans le combat.
     * @param enn L'ennemi qui va attaquer un combattant.
     */
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

void incrementerNbCombats(ListeCombattant listeC) {
    /**
     * @brief Incrémente le nombre de combats de chaque combattant de la liste des personnages combattants.
     *
     * @param listeC La liste des combattants à parcourir.
     */
    celluleCombattant* courant = listeC;
    while (courant != NULL) {
        courant->perso.nbcomb++;
        courant = courant->suivant;
    }
}

int combat(ListeCombattant* listeC, Ennemi* enn) {
    /**
     * @brief Gère le déroulement du combat entre les personnages et un ennemi.
     *
     * @param listeC La liste des combattants (personnages) participant au combat.
     * @param enn Pointeur vers l'ennemi qui participe au combat.
     * 
     * @return 1 si l'ennemi est vaincu, 0 si tous les personnages sont éliminés.
     */

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
            incrementerNbCombats(*listeC);
            return 1;
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
        return 0;
    }
}


void attribuerAccessoires(ListeAcc dispoAcc, ListeCombattant listeCombattants) {
    /**
     * @brief Permet d'attribuer des accessoires aux combattants pendant la phase de préparation.
     * 
     * @param dispoAcc La liste des accessoires disponibles à attribuer.
     * @param listeCombattants La liste des combattants à qui les accessoires peuvent être attribués.
     */
    printf("\nPhase de préparation :\n");
    printf("Vous pouvez attribuer des accessoires aux personnages suivants :\n");

    // Afficher les combattants disponibles
    int nbCombattants = 0;
    ListeCombattant temp = listeCombattants;
    while (temp != NULL) {
        printf("%d. %s\n", nbCombattants + 1, temp->perso.nom);
        temp = temp->suivant;
        nbCombattants++;
    }

    printf("\nVoici les accessoires disponibles :\n");
    afficherDispoAcc(dispoAcc);

    // Répartition des accessoires (jusqu'à nbCombattants * 2)
    for (int i = 0; i < nbCombattants * 2; i++) {
        int choixAccessoire, choixPersonnage;

        printf("\nChoisissez un accessoire (entrez le numéro de l'accessoire) : ");
        scanf("%d", &choixAccessoire);

        printf("A quel personnage souhaitez-vous l'attribuer ? (entrez le numéro correspondant) : ");
        scanf("%d", &choixPersonnage);

        // Retirer l'accessoire sélectionné de la liste des accessoires
        Accessoire* accessoireSelectionne = retirerAcc(&dispoAcc, choixAccessoire);

        if (accessoireSelectionne != NULL) {
            // Trouver le personnage sélectionné dans la liste des combattants
            ListeCombattant cible = listeCombattants;
            for (int j = 1; j < choixPersonnage && cible != NULL; j++) {
                cible = cible->suivant;
            }

            if (cible != NULL) {
                Personnage* persoCible = &(cible->perso);

                if (persoCible->acc_1 == NULL) {
                    persoCible->acc_1 = accessoireSelectionne;
                    persoCible->HP += atoi(accessoireSelectionne->HPbonus);
                    persoCible->HPmax += atoi(accessoireSelectionne->HPbonus);
                } else if (persoCible->acc_2 == NULL) {
                    persoCible->acc_2 = accessoireSelectionne;
                    persoCible->HP += atoi(accessoireSelectionne->HPbonus);
                    persoCible->HPmax += atoi(accessoireSelectionne->HPbonus);
                } else {
                    printf("Le personnage %s a déjà 2 accessoires attribués.\n", persoCible->nom);
                }
            } else {
                printf("Personnage invalide. Réessayez.\n");
            }
        } else {
            printf("Accessoire non trouvé. Réessayez.\n");
        }
    }
}


int MiseEnPlaceCombat(ListePerso listeP, ListeCombattant* listeC, int nbCombats, Ennemi* enn, ListeAcc* dispoAcc) {
    /**
 * @brief Prépare le prochain combat en sélectionnant les combattants et en leur attribuant des accessoires.
 * 
 * @param listeP La liste des personnages disponibles.
 * @param listeC Pointeur vers la liste des combattants qui sera mise à jour avec les personnages sélectionnés.
 * @param nbCombats Le nombre de combats qui détermine le nombre de combattants à sélectionner (2 ou 3).
 * @param enn L'ennemi contre lequel les combattants vont se battre.
 * @param dispoAcc Liste des accessoires disponibles pour être attribués aux combattants.
 * 
 * @return 1 Si les combattants ont gagné le combat, 0 en cas de défaite.
 */
    printf("\n");
    printf("Personnages disponibles:\n");
    printf("\n");
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

    attribuerAccessoires(*dispoAcc, *listeC);

    printf("Combat préparé avec les combattants suivants :\n");
    printf("\n");
    afficherCombattants(*listeC);
    printf("\n");
    return combat(listeC, enn);
}


void ajoutSanitarium(ListeSanitarium* liste, ListePerso* dispo, Personnage perso) {
    /**
     * @brief Ajoute un personnage au Sanitarium et le retire de la liste des personnages disponibles.
     *
     * @param liste Pointeur vers la liste des personnages au Sanitarium qui sera mise à jour.
     * @param dispo Pointeur vers la liste des personnages disponibles, de laquelle le personnage sera retiré.
     * @param perso Le personnage à ajouter au Sanitarium.
     */
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
    /**
     * @brief Restaure les points de vie (HP) des personnages grâce au Sanitarium.
     * 
     * @param liste Pointeur vers la liste des personnages au Sanitarium dont les HP seront restaurés.
     */
    celluleSanitarium* courant = *liste;
    while (courant != NULL) {
        courant->perso.HP += 7;
        if (courant->perso.HP > courant->perso.HPmax) {
            courant->perso.HP = courant->perso.HPmax;
        }
        courant = courant->suivant;
    }
}


void afficherSanitarium(Personnage perso) {
    /**
     * @brief Affiche les informations d'un personnage au Sanitarium.
     * 
     * @param perso Le personnage dont les informations seront affichées.
     */
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


void sanitarium_affichage(ListeSanitarium liste) {
    /**
     * @brief Affiche les informations de tous les personnages présents dans le Sanitarium (fonction principale d'affichage).
     * 
     * @param liste La liste des personnages présents dans le Sanitarium.
     */
    celluleSanitarium* courant = liste;
    while (courant != NULL) {
        afficherSanitarium(courant->perso);
        courant = courant->suivant;
    }
}


void retirerDuSanitarium(ListeSanitarium* sanitarium, ListePerso* dispoPerso) {
    /**
     * @brief Retire un personnage du Sanitarium et le réintègre dans la liste des personnages disponibles.
     * 
     * @param sanitarium La liste des personnages présents dans le Sanitarium.
     * @param dispoPerso La liste des personnages disponibles, dans laquelle le personnage sera réintégré.
     */
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

void afficherTaverne(Personnage perso) {
    /**
     * @brief Affiche les informations d'un personnage dans la Taverne.
     * 
     * @param perso Le personnage dont les informations doivent être affichées.
     */
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

void taverne_affichage(ListeTaverne liste) {
    /**
     * @brief Affiche la liste des personnages présents dans la Taverne (fonction d'affichage principale).
     * 
     * @param liste La liste des personnages présents dans la Taverne.
     */
    celluleTaverne* courant = liste;
    while (courant != NULL) {
        afficherTaverne(courant->perso);
        courant = courant->suivant;
    }
}

void ajoutTaverne(ListeTaverne* liste, ListePerso* dispo, Personnage perso) {
    /**
     * @brief Ajoute un personnage à la Taverne et le retire de la liste des personnages disponibles.
     * 
     * @param liste La liste de la Taverne dans laquelle le personnage sera ajouté.
     * @param dispo La liste des personnages disponibles, à partir de laquelle le personnage sera retiré.
     * @param perso Le personnage à ajouter à la Taverne.
     */
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
    /**
     * @brief Réduit le stress des personnages à chaque tour, dans la Taverne.
     * 
     * @param liste La liste de la Taverne contenant les personnages dont le stress sera réduit.
     */
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
    /**
     * @brief Permet de retirer des personnages de la Taverne et de les réintégrer dans la liste des personnages disponibles.
     * 
     * @param taverne La liste des personnages actuellement dans la Taverne.
     * @param dispoPerso La liste des personnages disponibles, où seront ajoutés ceux retirés de la Taverne.
     */
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
    /**
     * @brief Ajoute un l'accessoire en paramètre à la roulotte.
     * 
     * @param roulotte La liste des accessoires actuellement dans la roulotte.
     * @param acc L'accessoire à ajouter à la roulotte.
     */
    celluleRoulotte* nouveau = (celluleRoulotte*)malloc(sizeof(celluleRoulotte));
    if (nouveau != NULL) {
        nouveau->acc = acc;
        nouveau->suivant = *roulotte;
        *roulotte = nouveau;
    }
}

void afficherLot(Accessoire acc) {
    /**
     * @brief Affiche les détails d'un accessoire dans la roulotte.
     * 
     * @param acc L'accessoire dont les détails doivent être affichés.
     */
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
    /**
     * @brief Affiche les détails de tous les accessoires dans la roulotte.
     * 
     * @param roulotte La liste des accessoires présents dans la roulotte.
     */
    celluleRoulotte* courant = roulotte;
    while (courant != NULL) {
        afficherLot(courant->acc);
        courant = courant->suivant;
    }
}


void retirerLot(ListeRoulotte* roulotte, ListeAcc* dispoAcc) {
    /**
     * @brief Retire un accessoire de la roulotte et l'ajoute à la liste des accessoires disponibles.
     * 
     * @param roulotte La liste des accessoires dans la roulotte.
     * @param dispoAcc La liste des accessoires disponibles où l'accessoire retiré sera ajouté.
     */
    if (*roulotte == NULL) return;

    celluleRoulotte* courant = *roulotte;
    *roulotte = courant->suivant;

    celluleAcc* nouvelleCellule = (celluleAcc*)malloc(sizeof(celluleAcc));
    if (nouvelleCellule != NULL) {
        nouvelleCellule->acc = courant->acc;  // Copie de l'accessoire
        nouvelleCellule->suivant = *dispoAcc;
        *dispoAcc = nouvelleCellule;
    }

    free(courant);
}

void achat(ListeRoulotte* roulotte, ListeAcc* dispoAcc, int or_joueur) {
    /**
     * @brief Permet d'acheter un accessoire disponible dans la roulotte si le joueur a assez d'or.
     *
     * @param roulotte La liste des accessoires dans la roulotte.
     * @param dispoAcc La liste des accessoires disponibles où l'accessoire acheté sera ajouté.
     * @param or_joueur Le montant actuel d'or du joueur, mis à jour après l'achat.
     */
    if (*roulotte == NULL) {
        printf("La roulotte est vide. Aucun achat possible.\n");
        return;
    }

    char entree[10];
    printf("Votre or actuel : %d\n", or_joueur);
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
            if (or_joueur >= courant->acc.prix) {
                or_joueur -= courant->acc.prix;
                printf("Vous avez acheté : %s pour %d or.\n", courant->acc.nom, courant->acc.prix);

                if (precedent == NULL) {
                    *roulotte = courant->suivant;
                } else {
                    precedent->suivant = courant->suivant;
                }

                // Crée une nouvelle celluleAcc pour dispoAcc
                celluleAcc* nouvelleCellule = (celluleAcc*)malloc(sizeof(celluleAcc));
                if (nouvelleCellule != NULL) {
                    nouvelleCellule->acc = courant->acc;
                    nouvelleCellule->suivant = *dispoAcc;
                    *dispoAcc = nouvelleCellule;
                }

                free(courant);  // Libère l'ancienne cellule de roulotte
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


int phaseAvantCombat(ListeSanitarium* sanitarium, ListeTaverne* taverne,
                      ListePerso* dispo, ListeRoulotte* roulotte,
                      ListeAcc* dispoAcc, int or_joueur, int quitter) {
    
    /**
     * @brief phase de préparation avant le combat, gestion sanitarium/taverne/roulotte.
     *
     * @param sanitarium La liste des personnages dans le sanitarium.
     * @param taverne La liste des personnages dans la taverne.
     * @param dispo La liste des personnages disponibles pour le combat.
     * @param roulotte La liste des accessoires dans la roulotte.
     * @param dispoAcc La liste des accessoires disponibles.
     * @param or_joueur Le montant actuel d'or du joueur.
     * @param quitter La variable qui indique si le joueur souhaite quitter la partie (1 pour quitter, 0 pour continuer).
     *
     * @return 1 si le joueur quitte la partie, sinon 0.
     */

    char choix;

    printf("\nvoulez vous quitter la partie maintenant ? (o/n) : ");
    scanf(" %c", &choix);
    if (choix == 'o') {
        return quitter = 1;
    }

    printf("\n--- Préparation avant le combat suivant ---\n");


    if (*sanitarium != NULL) {
        printf("\n--- Gestion du sanitarium ---\n");
        sanitarium_affichage(*sanitarium);
        retirerDuSanitarium(sanitarium, dispo);
    }

    if (*taverne != NULL) {
        printf("\n--- Gestion de la taverne ---\n");
        taverne_affichage(*taverne);
        retirerTaverne(taverne, dispo);
    }

    if (*roulotte != NULL) {
        printf("\n--- Passage à la roulotte ---\n");
        achat(roulotte, dispoAcc, or_joueur);
    }
    return quitter = 0;

}


void sauvegarderJeu(const char* nomFichier, int* victoire, int* niveau, int* or_joueur,
                    ListePerso dispoPerso, ListeSanitarium sanitarium, ListeTaverne taverne,
                    ListeAcc dispoAcc, ListeRoulotte roulotte) {

    /**
     * @brief Sauvegarde l'état actuel du jeu dans un fichier.
     *
     * @param nomFichier Le nom du fichier dans lequel les données du jeu seront sauvegardées.
     * @param victoire Un pointeur vers la variable qui indique si le joueur a gagné.
     * @param niveau Un pointeur vers la variable qui représente le niveau actuel du joueur.
     * @param or_joueur Un pointeur vers la variable qui contient le nombre d'or du joueur.
     * @param dispoPerso La liste des personnages disponibles pour le combat.
     * @param sanitarium La liste des personnages actuellement dans le sanitarium.
     * @param taverne La liste des personnages actuellement à la taverne.
     * @param dispoAcc La liste des accessoires disponibles pour le joueur.
     * @param roulotte La liste des accessoires actuellement dans la roulotte.
     *
     * @return void
     */

    FILE* fichier = fopen(nomFichier, "w");
    if (!fichier) {
        printf("Erreur : Impossible d'ouvrir le fichier %s pour l'écriture.\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    // Sauvegarde des variables simples
    fprintf(fichier, "Victoire: %d\n", *victoire);
    fprintf(fichier, "Niveau: %d\n", *niveau);
    fprintf(fichier, "Or: %d\n", *or_joueur);

    // Sauvegarde des personnages disponibles
    fprintf(fichier, "PersonnagesDisponibles:\n");
    cellulePerso* perso = dispoPerso;
    while (perso != NULL) {
        fprintf(fichier, "- ID: %d, Nom: %s, Classe: %s, Att: %d, Def: %d, HP: %d, HPmax: %d, Rest: %d, Str: %d, Comb: %d, Acc1: %p, Acc2: %p\n",
                perso->perso.num, perso->perso.nom, perso->perso.classe, perso->perso.att, perso->perso.def,
                perso->perso.HP, perso->perso.HPmax, perso->perso.rest, perso->perso.str, perso->perso.nbcomb,
                (void*)perso->perso.acc_1, (void*)perso->perso.acc_2);
        perso = perso->suivant;
    }

    // Sauvegarde des personnages au sanitarium
    fprintf(fichier, "Sanitarium:\n");
    celluleSanitarium* persoSanit = sanitarium;
    while (persoSanit != NULL) {
        fprintf(fichier, "- ID: %d, Nom: %s, Classe: %s, Att: %d, Def: %d, HP: %d, HPmax: %d, Rest: %d, Str: %d\n",
                persoSanit->perso.num, persoSanit->perso.nom, persoSanit->perso.classe, persoSanit->perso.att,
                persoSanit->perso.def, persoSanit->perso.HP, persoSanit->perso.HPmax, persoSanit->perso.rest,
                persoSanit->perso.str);
        persoSanit = persoSanit->suivant;
    }

    // Sauvegarde des personnages à la taverne
    fprintf(fichier, "Taverne:\n");
    celluleTaverne* persoTav = taverne;
    while (persoTav != NULL) {
        fprintf(fichier, "- ID: %d, Nom: %s, Classe: %s, Att: %d, Def: %d, HP: %d, HPmax: %d, Rest: %d, Str: %d\n",
                persoTav->perso.num, persoTav->perso.nom, persoTav->perso.classe, persoTav->perso.att,
                persoTav->perso.def, persoTav->perso.HP, persoTav->perso.HPmax, persoTav->perso.rest,
                persoTav->perso.str);
        persoTav = persoTav->suivant;
    }

    // Sauvegarde des accessoires disponibles
    fprintf(fichier, "AccessoiresDisponibles:\n");
    celluleAcc* acc = dispoAcc;
    while (acc != NULL) {
        fprintf(fichier, "- ID: %d, Nom: %s, AttBonus: %s, DefBonus: %s, HPBonus: %s, RestBonus: %s, StrRed: %d, Prix: %d\n",
                acc->acc.num, acc->acc.nom, acc->acc.attbonus, acc->acc.defbonus, acc->acc.HPbonus,
                acc->acc.restbonus, acc->acc.strred, acc->acc.prix);
        acc = acc->suivant;
    }

    // Sauvegarde des accessoires de la roulotte
    fprintf(fichier, "Roulotte:\n");
    celluleRoulotte* roul = roulotte;
    while (roul != NULL) {
        fprintf(fichier, "- ID: %d, Nom: %s, AttBonus: %s, DefBonus: %s, HPBonus: %s, RestBonus: %s, StrRed: %d, Prix: %d\n",
                roul->acc.num, roul->acc.nom, roul->acc.attbonus, roul->acc.defbonus, roul->acc.HPbonus,
                roul->acc.restbonus, roul->acc.strred, roul->acc.prix);
        roul = roul->suivant;
    }

    fclose(fichier);
    printf("Partie sauvegardée avec succès dans le fichier %s.\n", nomFichier);
}



void chargerJeu(const char* nomFichier, int* victoire, int* niveau, int* or_joueur,
                ListePerso* dispoPerso, ListeSanitarium* sanitarium, ListeTaverne* taverne,
                ListeAcc* dispoAcc, ListeRoulotte* roulotte) {

    /**
     * @brief Charge l'état du jeu depuis un fichier de sauvegarde.
     *
     * @param nomFichier Le nom du fichier de sauvegarde à charger.
     * @param victoire Un pointeur vers la variable qui sera mise à jour avec la valeur de la victoire chargée depuis le fichier.
     * @param niveau Un pointeur vers la variable qui sera mise à jour avec le niveau du joueur chargé depuis le fichier.
     * @param or_joueur Un pointeur vers la variable qui sera mise à jour avec le nombre d'or du joueur chargé depuis le fichier.
     * @param dispoPerso Pointeur vers la liste des personnages disponibles, qui sera mise à jour avec les personnages chargés depuis le fichier.
     * @param sanitarium Pointeur vers la liste des personnages dans le sanitarium, qui sera mise à jour avec les personnages chargés depuis le fichier.
     * @param taverne Pointeur vers la liste des personnages à la taverne, qui sera mise à jour avec les personnages chargés depuis le fichier.
     * @param dispoAcc Pointeur vers la liste des accessoires disponibles, qui sera mise à jour avec les accessoires chargés depuis le fichier.
     * @param roulotte Pointeur vers la liste des accessoires dans la roulotte, qui sera mise à jour avec les accessoires chargés depuis le fichier.
     *
     * @return void
     */

    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier)) {

        // Chargement de la victoire
        if (sscanf(ligne, "Victoire: %d", victoire) != 1)
            printf("Erreur lors de la lecture de la victoire (ligne: %s).\n", ligne);

        // Chargement du niveau
        if (sscanf(ligne, "Niveau: %d", niveau) != 1)
            printf("Erreur lors de la lecture du niveau (ligne: %s).\n", ligne);

        // Chargement de l'or du joueur
        if (sscanf(ligne, "Or: %d", or_joueur) != 1)
            printf("Erreur lors de la lecture de l'or du joueur (ligne: %s).\n", ligne);

        // Lecture de la liste des personnages disponibles
        if (strncmp(ligne, "PersonnagesDisponibles:", 23) == 0) {
            while (fgets(ligne, sizeof(ligne), fichier) && ligne[0] == '-') {
                Personnage perso;
                if (sscanf(ligne, "- ID: %d, Nom: %[^,], Classe: %[^,], Att: %d, Def: %d, HP: %d, HPmax: %d, Rest: %d, Str: %d, Comb: %d, Acc1: %d, Acc2: %d",
                    &perso.num, perso.nom, perso.classe, &perso.att, &perso.def, &perso.HP, &perso.HPmax, &perso.rest, &perso.str, &perso.nbcomb, &perso.acc_1, &perso.acc_2) == 12) {
                    ajoutPerso(dispoPerso, perso);
                } else {
                    printf("Erreur de format dans la ligne des personnages disponibles : %s\n", ligne);
                }
            }
            continue;
        }

        // Lecture de la liste des personnages au sanitarium
        if (strncmp(ligne, "Sanitarium:", 11) == 0) {
            while (fgets(ligne, sizeof(ligne), fichier) && ligne[0] == '-') {
                Personnage perso;
                if (sscanf(ligne, "- ID: %d, Nom: %[^,], Classe: %[^,], Att: %d, Def: %d, HP: %d, HPmax: %d, Rest: %d, Str: %d",
                           &perso.num, perso.nom, perso.classe, &perso.att, &perso.def, &perso.HP, &perso.HPmax, &perso.rest, &perso.str) == 9) {
                    ajoutSanitarium(sanitarium, dispoPerso, perso);
                } else {
                    printf("Erreur de format dans la ligne des personnages du sanitarium : %s\n", ligne);
                }
            }
            continue;
        }

        // Lecture de la liste des personnages à la taverne
        if (strncmp(ligne, "Taverne:", 8) == 0) {
            while (fgets(ligne, sizeof(ligne), fichier) && ligne[0] == '-') {
                Personnage perso;
                if (sscanf(ligne, "- ID: %d, Nom: %[^,], Classe: %[^,], Att: %d, Def: %d, HP: %d, HPmax: %d, Rest: %d, Str: %d",
                           &perso.num, perso.nom, perso.classe, &perso.att, &perso.def, &perso.HP, &perso.HPmax, &perso.rest, &perso.str) == 9) {
                    ajoutTaverne(taverne, dispoPerso, perso);
                } else {
                    printf("Erreur de format dans la ligne des personnages de la taverne : %s\n", ligne);
                }
            }
            continue;
        }

        // Lecture des accessoires disponibles
        if (strncmp(ligne, "AccessoiresDisponibles:", 23) == 0) {
            while (fgets(ligne, sizeof(ligne), fichier) && ligne[0] == '-') {
                Accessoire acc;
                if (sscanf(ligne, "- ID: %d, Nom: %[^,], AttBonus: %[^,], DefBonus: %[^,], HPBonus: %[^,], RestBonus: %[^,], StrRed: %d, Prix: %d",
                           &acc.num, acc.nom, acc.attbonus, acc.defbonus, acc.HPbonus, acc.restbonus, &acc.strred, &acc.prix) == 8) {
                    ajoutAcc(dispoAcc, acc);
                } else {
                    printf("Erreur de format dans la ligne des accessoires disponibles : %s\n", ligne);
                }
            }
            continue;
        }

        // Lecture des accessoires en vente à la roulotte
        if (strncmp(ligne, "Roulotte:", 9) == 0) {
            while (fgets(ligne, sizeof(ligne), fichier) && ligne[0] == '-') {
                Accessoire acc;
                if (sscanf(ligne, "- ID: %d, Nom: %[^,], AttBonus: %[^,], DefBonus: %[^,], HPBonus: %[^,], RestBonus: %[^,], StrRed: %d, Prix: %d",
                           &acc.num, acc.nom, acc.attbonus, acc.defbonus, acc.HPbonus, acc.restbonus, &acc.strred, &acc.prix) == 8) {
                    ajouterlot(roulotte, acc);
                } else {
                    printf("Erreur de format dans la ligne des accessoires de la roulotte : %s\n", ligne);
                }
            }
            continue;
        }
    }

    fclose(fichier);
    printf("Chargement de la sauvegarde terminé.\n");
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
    char choix;
    int niveau = 0;
    int nombreEnnemis;
    int or_joueur = 0;
    int victoire = 0;
    int quitter = 0;

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

    // création des accessoires
    Accessoire pendentif_tranchant = creerAccessoire(1, "pendentif tranchant", "+5", "+1", "+0", "+0", 0, 7);
    Accessoire calice_de_jeunesse = creerAccessoire(2, "calice de jeunesse", "+0", "+3", "+5", "+0", 5, 16);
    Accessoire anneau_magique = creerAccessoire(3, "Anneau Magique", "+3", "+2", "+0", "+5", 10, 7);
    Accessoire amulette_divine = creerAccessoire(4, "Amulette Divine", "+0", "+5", "+10", "+0", 15, 32);
    Accessoire lame_du_roi_dechu = creerAccessoire(5, "Lame du Roi Déchu", "+8", "+2", "+0", "+3", 5, 20);
    Accessoire egide_de_la_legion = creerAccessoire(6, "Égide de la Légion", "+0", "+6", "+10", "+0", 8, 15);
    Accessoire danse_de_la_mort = creerAccessoire(7, "Danse de la Mort", "+12", "+0", "+0", "+5", 10, 25);
    Accessoire cape_de_la_nuit = creerAccessoire(8, "Cape de la Nuit", "+0", "+4", "+0", "+7", 7, 18);
    Accessoire cotte_epineuse = creerAccessoire(9, "Cotte Épineuse", "+0", "+10", "+20", "+0", 12, 30);
    Accessoire gage_de_sterak = creerAccessoire(10, "Gage de Sterak", "+5", "+0", "+15", "+0", 6, 22);
    Accessoire cimeterre_mercantile = creerAccessoire(11, "Cimeterre Mercuriel", "+10", "+2", "+0", "+0", 7, 26);
    Accessoire heraut_de_zaun = creerAccessoire(12, "Héraut de Zaun", "+0", "+5", "+5", "+10", 8, 24);
    Accessoire sablier_de_zhonya = creerAccessoire(13, "Sablier de Zhonya", "+0", "+7", "+0", "+15", 10, 28);
    Accessoire arc_axiomatique = creerAccessoire(14, "Arc Axiomatique", "+15", "+0", "+0", "+0", 5, 19);

    // création des personnages
    Personnage Boudicca = creerPersonnage(1, "Boudicca", classes[indicesSelectionnes[0]], NULL, NULL);
    Personnage Junia = creerPersonnage(2, "Junia", classes[indicesSelectionnes[1]], NULL, NULL);
    Personnage Flash = creerPersonnage(3, "Flash", classes[indicesSelectionnes[2]], NULL, NULL);
    Personnage Gordi = creerPersonnage(4, "Gordi", classes[indicesSelectionnes[3]], NULL, NULL);
    Personnage Ragnard = creerPersonnage(5, "Ragnard", classes[indicesSelectionnes[0]], NULL, NULL);
    Personnage Tritus = creerPersonnage(6, "Tritus", classes[indicesSelectionnes[1]], NULL, NULL);

    // Création des ennemis
        Ennemi ennemis[] = {
            creerEnnemi("Brigand", 1, 2, 10, 10, 2),
            creerEnnemi("Squelette", 2, 3, 11, 15, 3),
            creerEnnemi("Goule", 3, 5, 13, 20, 5),
            creerEnnemi("Zombi", 4, 6, 14, 25, 6),
            creerEnnemi("Ogre", 5, 8, 16, 30, 8),
            creerEnnemi("Loup_garou", 6, 9, 18, 35, 9),
            creerEnnemi("Hydre", 7, 11, 19, 40, 11),
            creerEnnemi("Spectre", 8, 12, 20, 45, 12),
            creerEnnemi("Golem", 9, 14, 22, 50, 14),
            creerEnnemi("Chevalier noir", 10, 15, 23, 60, 15)
        };

    nombreEnnemis = sizeof(ennemis) / sizeof(ennemis[0]);

    printf("Voulez-vous charger une sauvegarde ? (o/n) : ");
    scanf(" %c", &choix);
    if (choix == 'o') {

        char nomFichier[100];
        printf("Entrez le nom du fichier de sauvegarde : ");
        scanf("%s", nomFichier);
        chargerJeu(nomFichier, &victoire, &niveau, &or_joueur, &dispoPerso, &sanitarium, &taverne, &dispoAcc, &roulotte);
    }

    else {

        ajoutPerso(&dispoPerso, Boudicca);
        ajoutPerso(&dispoPerso, Junia);

        ajoutAcc(&dispoAcc, pendentif_tranchant);
        ajoutAcc(&dispoAcc, calice_de_jeunesse);

        ajouterlot(&roulotte, anneau_magique);
        ajouterlot(&roulotte, amulette_divine);
        ajouterlot(&roulotte, lame_du_roi_dechu);
        ajouterlot(&roulotte, egide_de_la_legion);
        ajouterlot(&roulotte, danse_de_la_mort);
        ajouterlot(&roulotte, cape_de_la_nuit);
        ajouterlot(&roulotte, cotte_epineuse);
        ajouterlot(&roulotte, gage_de_sterak);
        ajouterlot(&roulotte, cimeterre_mercantile);
        ajouterlot(&roulotte, heraut_de_zaun);
        ajouterlot(&roulotte, sablier_de_zhonya);
        ajouterlot(&roulotte, arc_axiomatique);

        };

    printf("\n");
    printf("Accessoires disponibles:\n");
    printf("\n");
    afficherDispoAcc(dispoAcc);


    while (victoire == 0 && niveau < nombreEnnemis && quitter != 1) {
        printf("\nNiveau %d - Mise en place du combat contre %s :\n\n", niveau + 1, ennemis[niveau].nom);

        int resultatCombat = MiseEnPlaceCombat(dispoPerso, &listeC, nbcombat, &ennemis[niveau], &dispoAcc);

        if (resultatCombat == 0) {
            printf("Vous avez perdu le combat contre %s. Le jeu est terminé.\n", ennemis[niveau].nom);
            victoire = -1;
            break;
        }

        printf("Félicitations ! Vous avez vaincu %s.\n", ennemis[niveau].nom);
        niveau++;

        if (niveau >= nombreEnnemis) {
            printf("Félicitations ! Vous avez vaincu tous les ennemis et gagné le jeu !\n");
            victoire = 1;
            break;
        }

        or_joueur += 10;
        quitter = phaseAvantCombat(&sanitarium, &taverne, &dispoPerso, &roulotte, &dispoAcc, or_joueur, quitter);

        if (niveau == 2) ajoutPerso(&dispoPerso,Flash);
        if (niveau == 4) ajoutPerso(&dispoPerso, Gordi);
        if (niveau == 7) ajoutPerso(&dispoPerso,Ragnard);
        if (niveau == 8) ajoutPerso(&dispoPerso, Tritus);
    }

    if (quitter == 1) {
    char nomFichier[100];

    while (1) {
        printf("Entrez un nom de fichier pour sauvegarder la partie : ");
        scanf("%c", nomFichier);
        if (nomFichier[0] != '\0') {

            FILE* fichierTest = fopen(nomFichier, "w");
            if (fichierTest != NULL) {
                fclose(fichierTest);
                break;
            } else {
                printf("Erreur : Impossible d'ouvrir le fichier %s pour l'écriture. Essayez encore.\n", nomFichier);
            }
        } else {
            printf("Nom de fichier invalide. Essayez encore.\n");
        }
    }

    sauvegarderJeu(nomFichier, &victoire, &niveau, &or_joueur, dispoPerso, sanitarium, taverne, dispoAcc, roulotte);
}

}
