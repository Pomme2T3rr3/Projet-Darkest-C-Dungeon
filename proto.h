#ifndef __main__
#define __main__

typedef struct Classe {
    char nom[50];
    int att;
    int def;
    int HPmax;
    int rest;
} Classe;

typedef struct Accessoire {
    char nom[50];
    char attbonus[10];
    char defbonus[10];
    char HPbonus[10];
    char restbonus[10];
    int strred;
} Accessoire;

typedef struct Personnage {
    char nom[50];
    char classe[50];
    int att;
    int def;
    int HP;
    int HPmax;
    int rest;
    int str;
    int nbcomb;
    char acc_1[50];
    char acc_2[50];
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



Classe creerClasse(const char* nom, int att, int def, int HPmax, int rest);

Accessoire creerAccessoire(const char* nom, const char* attbonus, const char* defbonus, const char* HPbonus, const char* restbonus, int strred);
void ajoutAcc(ListeAcc* liste, Accessoire acc);
void afficherAccessoire(Accessoire acc);
void afficherDispoAcc(ListeAcc liste);

Personnage creerPersonnage(const char* nom, Classe classe, Accessoire* acc1, Accessoire* acc2);
void ajoutPerso(ListePerso* liste, Personnage perso);
void ajoutCombattant(ListeCombattant* listeC, Personnage perso);
void retirerPerso(ListePerso *liste, Personnage perso);
void afficherPersonnage(Personnage perso);
void afficherDispoPerso(ListePerso liste);
void afficherCombattants(ListeCombattant listeC);

Ennemi creerEnnemi(const char* nom, int niveau, int attenn, int defenn, int HPenn, int attstrenn);

int indiceDejaSelectionne(int* indices, int taille, int indice);
void MiseEnPlaceCombat(ListePerso listeP, ListeCombattant* listeC, int nbCombats);

void ajoutSanitarium(ListeSanitarium* liste, ListePerso* dispo, Personnage perso);
void recupererationHP(ListeSanitarium* liste);
void afficherSanitarium(ListeSanitarium liste);
void retirerDuSanitarium(ListeSanitarium* sanitarium, ListePerso* dispoPerso);

void ajoutTaverne(ListeTaverne* liste, ListePerso* dispo, Personnage perso);
void recupererationStress(ListeTaverne* liste);
void afficherTaverne(ListeTaverne liste);
void retirerTaverne(ListeTaverne* taverne, ListePerso* dispoPerso);

#endif