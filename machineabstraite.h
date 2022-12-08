#ifndef TP_SFSD_MACHINEABSTRAITE_H
#define TP_SFSD_MACHINEABSTRAITE_H


#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000
#define b 1024





typedef struct Date
{
    char jour[3];
    char mois[3];
    char annee[5];
}Date;

typedef struct Tenreg
{
    char Matricule[7];
    char Nom[31];
    char Prenom[31];
    Date Date_Naissance;
    char Wilaya[20];
    char Sexe[10];
    char Groupe_Sanguin[4];
    Date Date_Recrutement;
    char Grade[30];
    char Specialite[30];
    char Dernier_Diplome[30];
    char Etablissement_Universitaire[30];
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
    char matricule;
    int Nbloc;
    int Deplacement;
} caseIndexPrimaire ;

typedef struct Index {
    caseIndexPrimaire tab[MAX];
    int Nenreg;
} Index;

typedef struct indexEntete
{
    int nbBloc; //nombre de blocs du fichier de sauvegarde de l'index
} indexEntete;

typedef struct fichierIndex
{
    FILE *f;
    indexEntete entete;
} fichierIndex;


typedef struct TbolcIndex
{
    caseIndexPrimaire tab[b];
    int NB;

} tBlocIndex;

// index Secondaire pour la spécialitée , la region ..
typedef struct mallion
{
    int matricule;
    struct mallion *suivant;

} mallion;

typedef struct mallionRech
{
    int bloc;
    int dep;
    struct mallionRech *suivant;

} mallionRech;

typedef struct iBlocForce
{
    int tab[b];
    int NB;
} iBlocForce;

typedef struct L7OF
{
    FILE *f;
    Entete entete;
    Index *indexPrimaire;//index primaire


} L7OF;

//Declarations des prototypes des fonctions de la machine abstraite
void lireDir(L7OF *fichier, int i, Tbloc *buf) ;//lecture directe du contenu de fichier à la position i dans le buf
void ecrireDir(L7OF *fichier, int i, Tbloc *buf); //ecriture directe du contenu de buf dans le fichier à la position i
int entete(L7OF *fichier,int num); //retourner la cracterstique num dans val
void affEntete(L7OF *fichier, int i, int val);
int allocBloc(L7OF *fichier); //allocations d'un nouveau bloc
void fermer (L7OF *fichier); //fermer un fichier
void ouvrir(L7OF *fichier, char *nomF, char mode);

#endif //TP_SFSD_MACHINEABSTRAITE_H
