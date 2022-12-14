#ifndef TPSFSD_FONCTIONS_H
#define TPSFSD_FONCTIONS_H

#include "MachineAbstraite.h"

//Déclarations des prototypes


void gen_Matricule (int *matricule); //Generation du matricule
void gen_Nom (char nom[31]); //Generation du Nom/Prenom
void gen_Date (Date *date); //Generation d'une date
void gen_Wilaya (char Wilaya[3]); //Generation du numero de wilaya
void gen_Sexe (char Sexe[2]); //generation du sexe
void gen_Grade (char Grade[7]); //Generation du grade
void gen_Dernier_Diplome (char Dernier_Diplome[7]); //Generation du dernier diplome
void gen_Specialite (char Specialite[4]); //Generation de la specialite
void gen_EU (char Etab_Univ[4]); //Generation de l'etablissement universitaire
void gen_GS (char groupeSanguin[2]); //Generation du groupe sanguin
Tenreg enseignant();
void RechDicho (int matricule, caseIndexPrimaire *Case, int taille, int *trouv, int *k);
Tenreg Demander_Info();
void afficher_enreg(L7OF *f, char *nomf, int mat);
void chargementInitial(L7OF *fich, char *nomf, int N);
void Affichage(L7OF *fichier, char *nomf);
void insertion_Ens(L7OF *fich, char *nomf);
void suppression_Ens(L7OF *f, char *nomf, int mat);
void insertion_Index(caseIndexPrimaire valeur, caseIndexPrimaire *tab, int taille);
void suppTabOrd(caseIndexPrimaire *tab, int taille, int pos);
void Modification_Ens(char *nomf, L7OF *fich, int matricule);
void sauvIndexPr(char *nomIndex, L7OF *fichier);
void chargerIndexPr(char *nomIndex, L7OF *fichier);
char **fichVersTab(char nomf[], int taiMot, int nbMot, int *cpt);
char *motPure(char *mot);
void insererLLC(maillon  **tete, int matricule);
void supprimerLLC(maillon **tete, int matricule);
void libererLLC(maillon *liste);
void Suppression_Specialite(char *nomf, L7OF *fichier);
int RechSeq(char **tabmot, char *nom);
void Affichage_EU(char *nomf, L7OF *fichier,int v1,int v2);
void consultation_region(L7OF *fich, char *nomf);
void Affichage_Entete(L7OF *fichier, char *nomf);
//FROM HERE
void Codage(L7OF *fichier, char *nomfCode, char *nomf);
void coderMat(int n,int *mat);
int bubbleSort(int *arr,int mat,int sort);
void swap(int* x, int* y);
int decoderMat(int key, int *mat);
int lookFor(int tab_int[7], int a);
void Decodage(L7OF *fichdecode, char *nomfDecode, char *nomfCode);
void VignereEncrypt(char *Message, char *key, char *coded);
char *gen_cle( char *code,const char *cle);
void Encrypted(char *code,const char *cle, char codee[]);
void Decrypted(char *coded, char *cle, char decodee[]);
void stringToUpper(char *Str);
void stringToLower(char *Str);
void sauvIndexSec(int codeIndex, char *nomIndexSec, L7OF *fichier);
void chargerIndexSec(int codeIndex, char *nomIndexSec, L7OF *fichier);
#endif //TPSFSD_FONCTIONS_H
