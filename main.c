#include <stdio.h>
#include "MachineAbstraite.h"
#include "fonctions.h"
#include <time.h>



int main() {
    srand(time(aNULL));
    Tenreg E;
    BUFFER buf;
    tBlocIndex buff;
    L7OF ENS ;
    indexPrimaire indexPrim ;
    ENS.indexPr = &indexPrim;
    chargementInitial(&ENS, "Fichier.bin", 10);
    Affichage(&ENS, "Fichier.bin");
    sauvIndexPr("index.bin", &ENS);
    fichierIndex fich;
    fich.f = fopen("index.bin","rb");
    fgets(&buff,10,fich.f);
    printf("%s",&buff);

}
