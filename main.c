#include <stdio.h>
#include "MachineAbstraite.h"
#include "fonctions.h"
#include <time.h>
#include <string.h>

char  **nomWilaya,**nomSpecialite, **nomEU, **region_centre, **region_est, **region_ouest ; // tableau pour recuperer les differents noms

int nbLireDir=0,
        nbEcrireDir=0;

int main() {
    int c,v1,v2;
    nomWilaya = fichVersTab("..\\Fichiers_System\\Wilaya.txt", 22, 58, &c);
    nomSpecialite = fichVersTab("..\\Fichiers_System\\Specialite.txt", 33, 111, &c);
    nomEU = fichVersTab("..\\Fichiers_System\\Etablissement_univ.txt", 97, 114, &c);

    srand(time(NULL));
    L7OF ENS,codee, decodee ;
    indexPrimaire indexPrim ;
    ENS.indexPr = &indexPrim;
    tBlocIndex buff ;
    fichierIndex Ifichier;
    chargementInitial(&ENS, "Fichier.bin", 10);
    Affichage(&ENS,"Fichier.bin");

}