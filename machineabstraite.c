
#include "MachineAbstraite.h"
#include <stdio.h>
#include <stdlib.h>


//lecture directe du contenu de fichier à la position i dans le buf

void lireDir(L7OF *fichier, int i, Tbloc *buf)
{

    fseek(fichier->f, (i - 1) * sizeof(Tbloc) + sizeof(entete), SEEK_SET);
    fread(buf, sizeof(Tbloc), 1, fichier->f);
    rewind(fichier->f);
}


//ecriture directe du contenu de buf dans le fichier à la position i

void ecrireDir(L7OF *fichier, int i, Tbloc *buf)
{

    fseek(fichier->f, (i - 1) * sizeof(Tbloc) + sizeof(entete), SEEK_SET);
    fwrite(buf, sizeof(Tbloc), 1, fichier->f);
    rewind(fichier->f);
}

//retourner la cracterstique num dans val


int entete(L7OF *fichier,int num) {
    int val;
    switch(num)
    {
        case 1 : //Numero du premier bloc
            val=fichier->entete->tete;
            break;
        case 2 : //Nombre d'enregistrement dans le bloc
            val=fichier->entete->NBEnreg;
            break;
        case 3 : //Numero du dernier bloc
            val=fichier->entete->queue;
            break;
        default :
            return -1;
    }
    return val;
}

//affecter à la caracteristique num la val

void affEntete(L7OF *fichier,int num,int val) {

    switch(num)
    {
        case 1 : //Affectation du numero du premier bloc
            fichier->entete->tete=val;
            break;
        case 2 : //Affectation du nombre d'enregistrement courants
            fichier->entete->NBEnreg=val;
            break;
        case 3 : //Affectation du numero du dernier bloc
            fichier->entete->queue=val;
            break;
    }
}


//Allocation d'un nouveau bloc en MS

int allocBloc(L7OF *fichier)
{

    BUFFER buf;
    if (fichier->f != NULL) //existe deja
    {

       //pour les buffers ça sert à rien d'affecter buf.suiv à -1 et buf.nb à 0 il change pas faut le faire en dehors de la fonction 

        affEntete(fichier, 2, entete(fichier, 2) + 1);
        ecrireDir(fichier, entete(fichier, 2), &buf);

        return entete(fichier, 2);
    }
    else
        return -1;
}

//fermer un fichier

void fermer(L7OF *fichier)
{

    if (fichier != NULL)
    {
        rewind(fichier->f);
        fwrite(&(fichier->entete), sizeof(Entete), 1, fichier->f);
        rewind(fichier->f);
        fclose(fichier->f);
    }
}


//ouvrir un fichier de type L7OF en mode voulu

void ouvrir(L7OF *fichier, char *nomF, char mode)
{

    if ((mode == 'N') || (mode == 'n'))
    {

        fichier->f = fopen(nomF, "wb+");

        affEntete(fichier, 1, 1);
        affEntete(fichier, 2, 1);
    }
    else if ((mode == 'A') || (mode == 'a'))
    {
        fichier->f = fopen(nomF, "rb+");
        if (fichier->f != NULL)
            fread(&(fichier->entete), sizeof(entete), 1, fichier->f);
    }
    else
        fichier->f = NULL;
}

