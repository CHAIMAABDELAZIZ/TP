#include <stdio.h>
#include "MachineAbstraite.h"
#include "fonctions.h"
#include <time.h>
int main() {
    L7OF *F;
    Tbloc buf;
    int i, j , cptBloc = 0 ;
    char continu[10] ="oui";
    Tenreg E;
    printf("%d\n",cptBloc);
    chargementInitial(  F, "aok.txt", 2);
    printf("%d\n",cptBloc);

        for (i = 1; i <= entete(F, 2); i++)
        {
            if((continu[0] == 'o')||(continu[0] == 'O')){
                cptBloc++ ;
                lireDir(&F, i, &buf);
                printf("\n");
                for (j = 0; j < buf.NB; j++)
                {

                    printf("%s\n",E.Matricule);
                    printf("%s\n",E.Nom);
                    printf("%s\n",E.Prenom);
                    printf("%s\n",E.Sexe);
                    printf("%s/%s/%s\n",E.Date_Naissance.jour,E.Date_Naissance.mois,E.Date_Naissance.annee);
                    printf("%s\n",E.Wilaya);
                    printf("%s\n",E.Groupe_Sanguin);
                    printf("%s\n",E.Grade);
                    printf("%s\n",E.Dernier_Diplome);
                    printf("%s/%s/%s\n",E.Date_Recrutement.jour,E.Date_Recrutement.mois,E.Date_Recrutement.annee);
                }
                if((cptBloc == 8 )&&(i != entete(&F , 2))){
                    cptBloc= 0;
                    printf("\n\t>Voulez vouz continuer l'affichage(o/n) :");
                    scanf("%s",continu);
                }
            }
        }
        fermer(&F);
    }
