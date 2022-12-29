#include "MachineAbstraite.h"
#include <stdio.h>
#include <stdlib.h>

extern int nbLireDir,
        nbEcrireDir; //FAUT VOIR LE MAIN AUSSI

//lecture directe du contenu de fichier à la position i dans le buf
void lireDir(L7OF *fichier,int i,BUFFER *buf)  {

    rewind(fichier->f);
    fseek(fichier->f,sizeof(Entete)+i*sizeof(Tbloc),SEEK_SET); //se positionner à la place exacte
    fread(buf,sizeof(Tbloc),1,fichier->f); //lecture
    nbLireDir++;
}

//ecriture directe du contenu de buf dans le fichier à la position i

void ecrireDir(L7OF *fichier,int i,Tbloc *buf) {
    rewind(fichier->f);
    fseek(fichier->f,sizeof(Entete)+i*sizeof(Tbloc),SEEK_SET); //se positionner à la place exacte
    fwrite(buf,sizeof(Tbloc),1,fichier->f); //ecriture
    nbEcrireDir++;
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

        affEntete(fichier, 2, entete(fichier, 2) + 1);
        ecrireDir(fichier, entete(fichier, 2), &buf);

        return entete(fichier, 2);
    }
    else
        return -1;
}

//fermer un fichier

void fermer (L7OF *fichier) {
    rewind(fichier->f);  //on se positionne au debut de fichier
    fwrite(fichier->entete,sizeof(Entete),1,fichier->f);  //on enregistre les modifications effectuées sur l'entete
    fclose(fichier->f);  //on ferme le fichier
    free(fichier->entete);  //liberer la zone entete reservée
}

//ouvrir un fichier de type L7OF en mode voulu

void ouvrir (L7OF *fichier,char nom_fich[30],const char mode) {

    fichier->entete = malloc(sizeof(Entete)); //allouer dynamiquement une zone en mémo centrale pour l'entete

    if ((mode=='n')||(mode=='N')) //si le mode est nouveau ie:le fichier n'existe pas déjà
    {   fichier->f = fopen(nom_fich,"wb+"); //ouvrir un fichier en mode ecriture binaire
        fichier->entete->tete=-1; //initialiser les champs 1 ET 3 de l'entete à -1
        fichier->entete->NBEnreg=0; //initialiser le nombre d'enregistrements à 0
        fichier->entete->queue=-1;
        fwrite(fichier->entete,sizeof(Entete),1,fichier->f);//ecrire l'en_tete ds le fichier binaire
    }
    else
    {
        if ((mode=='a')||(mode=='A')) //si le mode est ancien ie:le fichier existe
        {
            fichier->f=fopen(nom_fich,"rb+"); //ouvrir le fichier en mode lecture binaire
            if (fichier->f==NULL) printf("\n\t\t<<Le fichier n'existe pas...>>"); //si erreur d'ouverture


            else {
                fread(fichier->entete,sizeof(Entete),1,fichier->f);  //recuperer le contenu de l'entete ds la variable en_tete

            }
        }
        else printf("le mode est erroné.");
    }
}