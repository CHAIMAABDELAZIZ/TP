#include <stdio.h>
#include "MachineAbstraite.h"
#include "fonctions.h"
#include <time.h>
#include <string.h>

char  **nomWilaya,**nomSpecialite, **nomEU ; // tableau pour recuperer les differents noms

int main() {
    int c;
    nomWilaya = fichVersTab("..\\Fichiers_System\\Wilaya.txt", 30, 57, &c);
    nomSpecialite = fichVersTab("..\\Fichiers_System\\oklm.txt", 30, 11, &c);
    for (int p = 0; p < 12; ++p) {
        printf("%s",nomSpecialite[p]);
    }
    for (int p = 0; p < 12; ++p) {
        printf("%s",nomWilaya[p]);
    }
    //nomEU = fichVersTab("..\\Fichiers_System\\Eablissement_univ.txt", 70, 111, &c);

    srand(time(NULL));
        L7OF ENS ;
        indexPrimaire indexPrim ;
        ENS.indexPr = &indexPrim;
        BUFFER buff ;

        chargementInitial(&ENS, "Fichier.bin", 10);
        Affichage(&ENS, "Fichier.bin");
        /*sauvIndexPr("index.bin", &ENS);
        fichierIndex fich;
        fich.f = fopen("index.bin","rb");
        fgets(&buff,10,fich.f);
        printf("%s",&buff);*/

}
