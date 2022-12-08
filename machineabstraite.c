
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


int entete(L7OF *fichier, int i)
{

    if (i == 1)
    {
        return fichier->entete.tete;
    }

    else if (i == 2)
    {
        return fichier->entete.queue;
    }

    else
        return -1;
}

//affecter à la caracteristique num la val

void affEntete(L7OF *fichier, int i, int val)
{

    if (i == 1)
        fichier->entete.tete = val;
    else if (i == 2)
        fichier->entete.queue = val;

}


//Allocation d'un nouveau bloc en MS

int allocBloc(L7OF *fichier)
{

    BUFFER buf;
    if (fichier->f != NULL) //existe deja
    {

        buf.NB = 0;
        buf.suivant = -1;

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

