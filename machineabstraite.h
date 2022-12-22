#ifndef TP_SFSD_MACHINEABSTRAITE_H
#define TP_SFSD_MACHINEABSTRAITE_H


#include <stdio.h>
#include <stdlib.h>
#define MAX 9999
#define b 100
#define NB_Specialite 12
#define NB_EU 113





typedef struct Date
{
    char jour[3];
    char mois[3];
    char annee[5];
}Date;

typedef struct Tenreg
{
    int Matricule;
    char Nom[31];
    char Prenom[31];
    Date Date_Naissance;
    char Wilaya[22];
    char Sexe[10];
    char Groupe_Sanguin[4];
    Date Date_Recrutement;
    char Grade[30];
    char Specialite[35];
    char Dernier_Diplome[30];
    char Etablissement_Universitaire[97];
}Tenreg;

typedef struct Tbloc
{
    Tenreg tab[b];
    int suivant;
    int NB;
}Tbloc;

typedef struct Entete {
    int tete;
    int queue;
    int NBEnreg;
} Entete;


typedef Tbloc BUFFER;

typedef struct caseIndexPrimaire {
    int matricule;
    int Nbloc;
    int Deplacement;
} caseIndexPrimaire;

typedef struct indexPrimaire {
    caseIndexPrimaire tableau[MAX];
    int Nenreg;
} indexPrimaire;

typedef struct indexEntete
{
    int nbBloc; //nombre de blocs du fichier de sauvegarde de l'index
} indexEntete;

typedef struct fichierIndex
{
    FILE *f;
    indexEntete entete;
} fichierIndex;

typedef struct tBlocIndex
{
    caseIndexPrimaire tab[b];
    int NB;

} tBlocIndex;

typedef struct maillon
{
    int matricule;
    struct mallion *suivant;

} maillon;

typedef struct caseSec {
    maillon *info;
    int nbmat;
}caseSec;

typedef struct L7OF
{
    FILE *f;
    Entete *entete;
    indexPrimaire *indexPr;
    caseSec iSpecialite[NB_Specialite]; //indexSec pour la spécialité
    caseSec iEU[NB_EU];


} L7OF;



//Declarations des prototypes des fonctions de la machine abstraite
void lireDir(L7OF *fichier,int i,BUFFER *buf); //lecture directe du contenu de fichier à la position i dans le buf
void ecrireDir(L7OF *fichier,int i,Tbloc *buf); //ecriture directe du contenu de buf dans le fichier à la position i
int entete(L7OF *fichier,int num); //retourner la cracterstique num dans val
void affEntete(L7OF *fichier,int num,int val); //affecter à la caracteristique num la val
int allocBloc(L7OF *fichier); //allocations d'un nouveau bloc
void fermer (L7OF *fichier); //fermer un fichier
void ouvrir (L7OF *fichier,char *nom_fich,const char mode); //ouvrir un fichier de type L7OF en mode voulu


#endif //TP_SFSD_MACHINEABSTRAITE_H
