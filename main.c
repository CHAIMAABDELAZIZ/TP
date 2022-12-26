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
    nomSpecialite = fichVersTab("..\\Fichiers_System\\oklm.txt", 33, 111, &c);
    nomEU = fichVersTab("..\\Fichiers_System\\Eablissement_univ.txt", 97, 114, &c);

    srand(time(NULL));
        L7OF ENS ;
        indexPrimaire indexPrim ;
        ENS.indexPr = &indexPrim;
        tBlocIndex buff ;
        chargementInitial(&ENS, "Fichier.bin", 5);
        Affichage(&ENS,"Fichier.bin" )   ;
        consultation_region(&ENS, "Fichier.bin");
    /* fich.f = fopen("index.bin","rb");
     fread(&buff,100,1,fich.f);
     for (int i = 0; i <10 ; ++i) {
         printf("\n%d",&buff.tab[i].matricule);
       printf("\n%d",&buff.tab[i].Nbloc);
          printf("\n%d",&buff.tab[i].Deplacement);*/

    }
