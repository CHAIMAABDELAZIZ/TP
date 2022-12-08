#ifndef TPSFSD_FONCTIONS_H
#define TPSFSD_FONCTIONS_H

#include "MachineAbstraite.h"

//Déclarations des prototypes

void gen_Matricule (char matricule[7]); //Generation du matricule
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
void RechDicho (char matricule[7], caseIndexPrimaire *Case, int taille, int *trouv, int *k);
Tenreg Demander_Info();
char **fichVersTab(char nomf[], int taiMot, int nbMot, int *cpt);
void chargementInitial(L7OF *fich, char *nomf, int N) ;
void insererIndex(caseIndexPrimaire valeur, caseIndexPrimaire *tab, int taille);



#endif //TPSFSD_FONCTIONS_H