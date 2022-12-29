#include <stdio.h>
#include "MachineAbstraite.h"
#include "fonctions.h"
#include <time.h>
#include <string.h>
#include <windows.h>
#include "conio2.h"


char  **nomWilaya,**nomSpecialite, **nomEU, **region_centre, **region_est, **region_ouest ; // tableau pour recuperer les differents noms
 int couleurPrincipale = 12;



int main(int argc, char *argv[]) {

    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);

    home();
    int c, nbEnreg, repeter, m , n ,ageMin , ageMax ,y ,x,Nspecialite;
    int menu1,menuChamp, menuSupression;
    char *nomFichier, * extension, validation[8], pathFichier[50] = ".\\Fichiers_Binaire\\";
    long long nb ;

acceuil:
    clrscr();
    accueil();
    textcolor(couleurPrincipale);
    printf("\n\n\n\tVeuillez saisir votre choix");
    textcolor(YELLOW);
    printf(" [Utilisez les fleches de clavier] :\n\n\n");
    menu1 = menu(2, " \t\t\t[1]- Creer un nouveau fichier.","\t\t\t[2]- Quitter.");

    nomWilaya = fichVersTab(".\\Fichiers_System\\Wilaya.txt", 22, 58, &c);
    nomSpecialite = fichVersTab(".\\Fichiers_System\\oklm.txt", 33, 12, &c);
    nomEU = fichVersTab(".\\Fichiers_System\\Eablissement_univ.txt", 97, 114, &c);
    srand(time(NULL));
    ENS.indexPr = &indexPr;



    clrscr();

    switch (menu1)
    {
    case 1:
        creationFichier();
    textcolor(couleurPrincipale);
    printf("\n\n\tVeuillez saisir le nom du  fichier :\n");
    textcolor(WHITE);
    repeter = 1;
    while (repeter)
    {
        textcolor(couleurPrincipale);
        printf("\t\t> ");
        textcolor(WHITE);
        scanf("%s", &nomFichier);
        if ((extension = strrchr(&nomFichier, '.')))
        {
            if (strcmp(extension, ".bin") == 0)
            {
                textcolor(couleurPrincipale);
                printf("\n\tVeuillez saisir le nombre d'enregistrements dans le fichier:\n\t\t> ");
                textcolor(WHITE);
                scanf2(&nb);
                nbEnreg = (int) nb ;

                while ((nbEnreg <= 0) || (nbEnreg > 888888))
                {
                    textcolor(RED);
                    printf("/!\\  Nombre d'enregistrement invalide");
                    if (nbEnreg > 888888)
                    {
                        printf("(TROP GRAND!)\n");
                    }
                    else
                    {
                        printf(" (NOMBRE NEGATIF!)\n");
                    }
                    textcolor(couleurPrincipale);
                    printf("\t\t> ");
                    textcolor(WHITE);
                    scanf2(&nb);
                    nbEnreg = (int) nb ;

                }

                strcat(pathFichier, &nomFichier);
                textcolor(YELLOW);
                printf("\n\t\t Creation en cour  ");
                textcolor(15);

                for(int l=0;l<2;l++)
                {
                    int x=wherex();
                    y=wherey();
                    textcolor(15);
                    delay(150);
                    printf("%c ",254);
                    gotoxy(65,y);
                    printf("%d %c",(100/14)*l,37);
                    gotoxy(x+2,y);
                }
                chargementInitial(&ENS, pathFichier, nbEnreg);

                for(int l=2;l<14;l++)
                {
                    int x=wherex();
                    y=wherey();
                    textcolor(15);
                    delay(150);
                    printf("%c ",254);
                    gotoxy(65,y);
                    printf("%d %c",(100/14)*l,37);
                    gotoxy(x+2,y);
                }
                gotoxy(65,y);
                textcolor(YELLOW);
                printf("100 %c\n\n",37);
                textcolor(15);
                strcpy(e.nomf, &nomFichier);
                e.frg = 0;
                textcolor(YELLOW);
                //fInserer(e, &fBuf);

                printf("\n>> Fichier cree avec succes\n");

                textcolor(WHITE);
                retour();
                repeter = 0;
                getch();
            }
            else
            {
                textcolor(RED);
                printf("/!\\  Nom de fichier non valid!\n");
                textcolor(WHITE);
            }
        }
        else
        {
            textcolor(RED);
            printf("/!\\ Nom de fichier non valid!\n");
            textcolor(WHITE);
        }
    }

    break;

            goto acceuil ;
            break;
    case 2:
            goto end;
    }
    menuPrin:
    system("cls");
    menuPrincipale();
    textcolor(couleurPrincipale);
    ouvrir(&ENS , pathFichier , 'A');

    detailsFichier(ENS);
    fermer(&ENS);
    textcolor(couleurPrincipale);
    gotoxy(1,14);printf("\tVeuillez saisir votre choix :\n\n");

    textcolor(WHITE);
    menuChamp = menu(7, "\t\t\t[1]- Affichage.", "\t\t\t[2]- Insertion.", "\t\t\t[3]- Suppression.",  "\t\t\t[4]- Modification.", "\t\t\t[5]- Codage et decodage.", "\t\t\t[6]- Modification de l'interface.","\t\t\t[7]- Quitter.");

    system("cls");
    switch (menuChamp)
    {
        case 1:
            textcolor(couleurPrincipale);
            printf("\n\n\n\tVeuillez saisir votre choix :\n\n\n");
            textcolor(WHITE);
            menuChamp = menu(4, "\t\t\t[1]- Affichage par bloc", "\t\t\t[2]- Affichage par champs", "\t\t\t[3]- Affichage de fichier", "\t\t\t[4]- Retour");
            system("cls");
            switch (menuChamp)
            {
                case 1:
                    textcolor(couleurPrincipale);
                    printf("\n\n\tVeuillez saisir le numero de bloc a afficher:\n\t\t>  ");
                    textcolor(WHITE);
                    scanf2(&nb);
                    c = (int) nb ;
                    if ((c > entete(&ENS, 2)) || (c <= 0))
                    {
                        textcolor(RED);
                        printf("/!\\  Bloc [ %d ] : n'existe pas dans le fichier\n", c);
                        textcolor(WHITE);
                    }
                    else
                    {
                        printf("\tAffichage de bloc numero %d\n", c);
                        afficherBloc(&ENS, pathFichier, c);
                    }
                    retour();
                    gotoxy(1, 1);
                    getch();
                    goto menuPrin;
                    break;
                case 2:
                    textcolor(couleurPrincipale);
                    printf("\n\n\n\tAfficher tous les enregistremenet relatifs a :\n\n");
                    textcolor(WHITE);
                    menuChamp = menu(2, "\t\t\t[1]- un etablissement.", "\t\t\t[2]-une region.");
                    clrscr();

                    textcolor(couleurPrincipale);
                    switch (menuChamp)
                    {
                        case 1:
                            c = menuTab(NB_EU, nomEU);
                            clrscr();
                            textcolor(couleurPrincipale);
                            printf("\n _________ ____________________ ____________________ __________ ____________ ____________________ ____________________ ______________________ ___ ____________ ________ ____\n");
                            printf("|         |                    |                    |          |            |                    |                    |                      |   |            |        | \n");
                            printf("|Matricule|        Nom         |       Prenom       |   Date   |  Wilaya.N  |        Grade       |     Specialite     |       Ddiplome       |ABO|   Date.R   |  Sexe  | EU |\n");
                            printf("|_________|____________________|____________________|__________|____________|____________________|____________________|______________________|___|____________|________|____\n");
                            printf("|         |                    |                    |          |            |                    |                    |                      |   |            |        |    |\n");
                            textcolor(WHITE);
                            Affichage_EU(pathFichier, &ENS);
                            printf(" _________ ____________________ ____________________ __________ ____________ ____________________ ____________________ ______________________ ___ ____________ ________ ____ ");
                            textcolor(WHITE);
                            retour();
                            gotoxy(1, 1);
                            getch();
                            goto menuPrin;
                            break;

                        case 2:
                            textcolor(couleurPrincipale);
                            printf("\n\n\n\tChoisir la region  :\n\n");
                            textcolor(WHITE);
                            menuChamp = menu(3, "\t\t\t[1]-  Centre.", "\t\t\t[2]-  Est.", "\t\t\t[3]-  Ouest.");
                            printf("menuchamps est %d",menuChamp);
                            clrscr();
                            textcolor(couleurPrincipale);
                            printf("\n _________ ____________________ ____________________ __________ ____________ ____________________ ____________________ ______________________ ___ ____________ ________ ____\n");
                            printf("|         |                    |                    |          |            |                    |                    |                      |   |            |          \n");
                            printf("|Matricule|        Nom         |       Prenom       |   Date   |  Wilaya.N  |        Grade       |     Specialite     |       Ddiplome       |ABO|   Date.R   |  Sexe  | EU |\n");
                            printf("|_________|____________________|____________________|__________|____________|____________________|____________________|______________________|___|____________|_____________\n");
                            printf("|         |                    |                    |          |            |                    |                    |                      |   |            |        |    |\n");
                            textcolor(WHITE);
                            consultation_region(&ENS, pathFichier,menuChamp);
                            printf(" _________ ____________________ ____________________ __________ ____________ ____________________ ____________________ ______________________ ___ ____________ ________ ____ ");
                            textcolor(WHITE);
                            retour();
                            gotoxy(1, 1);
                            getch();
                            break;
                    }
                    goto menuPrin;
                    break;

                case 3:
                    printf("\n\t>Affichage complet de fichier:\n");
                    int g=((ENS.entete->NBEnreg)/1024)+1;
                    printf("g est %d",g);
                    for (int c = 1; c <= g; ++c) {
                            afficherBloc(&ENS, pathFichier, c);}
                    retour();
                    getch();
                    goto menuPrin;
                    break;

                case 4:
                    goto menuPrin;
                    break;
            }

            break;
        case 2:
            textcolor(couleurPrincipale);
            printf("\n\n\n\tVoulez-vous inserer un enregistrement d'enseignant :\n\n\n");
            textcolor(WHITE);
            menuChamp = menu(3, "\t\t\t[1]- Oui", "\t\t\t[2]- Non (Retour)");
            clrscr();
            switch (menuChamp)
            {
                case 1:
                textcolor(YELLOW);
                if (insertion_Ens(&ENS,pathFichier) == 0)
                {
                    printf(">>Insertion avec succes .\n");
                }
                else
                {
                    textcolor(RED);
        printf("\n Insertion impossible. Si vous souhaitez effectuer une modification de \nl'etablissement universiaire, veuillez revenir au menu principal");
                }

            retour();
            getch();
            goto menuPrin;
            break;

                case 2:
                    textcolor(RED);
                printf("/!\\  Insertion annule .\n");
                    goto menuPrin;
                    break;
            }

            break;
        case 3:
            textcolor(couleurPrincipale);
            printf("\n\n\tVeuillez saisir le mode de suppression :\n\n\n");
            menuSupression = menu(3, "\t\t[1]-  Par matricule", "\t\t[2]-  Par specialite", "\t\t[3]-  Retour");
            clrscr();
            switch (menuSupression)
            {
                case 1:
                    textcolor(couleurPrincipale);
                    printf("\n\n\t>Saisir le matricule d'enregistrement a supprimer :\n\t\t> ");
                    textcolor(WHITE);
                    scanf2(&nb);
                    c = (int ) nb ;
                        textcolor(YELLOW);
                        printf("\t-veuillez confirmer la suppression de ce enregistrement (o/n) :  > ");
                        textcolor(WHITE);
                        scanf("%s", validation);

                        if (validation[0] == 'o' || validation[0] == 'O')
                        {
                            textcolor(couleurPrincipale);
                            textcolor(YELLOW);
                            suppression_Ens(&ENS,pathFichier,nb);
                            }
                    textcolor(WHITE);
                    retour();
                    getch();
                    clrscr();
                    goto menuPrin;
                    break;
                case 2:

                    c = menuTab(NB_Specialite, nomSpecialite);
                    printf("\nVeuillez choisir le numero de la specialite que vous souhaitez supprimer");
                    scanf("%d",&Nspecialite);

                    textcolor(YELLOW);
                    printf("\n\t-veuillez confirmer la suppression  de toutes les enregistrement relatif a votre specialite (o/n) :  ");
                    textcolor(WHITE);
                    scanf("%s", validation);
                    if (validation[0] == 'o' || validation[0] == 'O')
                    {
                        textcolor(couleurPrincipale);
                        textcolor(YELLOW);
                        printf("\n\tSuppression en cour  ");
                        textcolor(15);

                        for(int l=0;l<2;l++)
                        {
                            int x=wherex();
                            y=wherey();
                            textcolor(15);
                            delay(150);
                            printf("%c ",254);
                            gotoxy(65,y);
                            printf("%d %c",(100/14)*l,37);
                            gotoxy(x+2,y);
                        }
                        for(int l=2;l<14;l++)
                        {
                            int x=wherex();
                            y=wherey();
                            textcolor(15);
                            delay(150);
                            printf("%c ",254);
                            gotoxy(65,y);
                            printf("%d %c",(100/14)*l,37);
                            gotoxy(x+2,y);
                        }
                        gotoxy(65,y);
                        textcolor(YELLOW);
                        printf("100 %c",37);
                        Suppression_Specialite(pathFichier, &ENS,Nspecialite);


                    }
                    else
                    {
                        textcolor(RED);
                        printf(">>\tSupression annule");
                    }

                    textcolor(WHITE);
                    retour();
                    getch();
                    clrscr();
                    goto menuPrin;

                    break;
                case 3:
                    goto menuPrin;
                    break;
            }

            break;
        case 4:

            system("cls");
            textcolor(couleurPrincipale);
            printf("\n\n\tVeuillez saisir le matricule de l'enseignant : \n\t\t\t>  ");
            textcolor(WHITE);
            scanf2(&nb);
            c = (int ) nb ;

            Modification_Ens(pathFichier, &ENS, nb);

            textcolor(WHITE);
            retour();
            getch();
            clrscr();
            goto menuPrin;

            break;
        case 6:
            menuChamp = 1;
            while( menuChamp != 4){
                clrscr();
                textcolor(YELLOW);
                printf("\n\n\t\tVeuillez saisir la nouvelle couleur :\n\n\n");
                textcolor(WHITE);
                menuChamp=menu(4,"\t\t\t[1]-  Vert","\t\t\t[2]-  Marron","\t\t\t[3]-  Bleu"  , "\t\t\t[4]-  Retour");
                switch(menuChamp){
                    case 1:
                        couleurPrincipale = 10;

                        break;
                    case 2:
                        couleurPrincipale = 6 ;

                        break;
                    case 3:
                        couleurPrincipale = 9;

                        break;
                    case 4:
                        break;

                }
            }

            goto menuPrin    ;
            break;
        case 7:
            goto fin;
            break;
    }

    fin:

    /*strcat(nomfIndex, nomFichier);
    sauvIndexPr(nomfIndex, &ENS);

    strcat(nomfIndexForce, nomFichier);
    sauvIndexSec(1, nomfIndexForce, &ENS);

    strcat(nomfIndexRegion, nomFichier);
    sauvIndexSec(2, nomfIndexRegion, &ENS);

    strcat(nomfIndexGrade, nomFichier);
    sauvIndexSec(3, nomfIndexGrade, &ENS);
    libererIndexSec(1, &ENS);
    libererIndexSec(2, &ENS);
    libererIndexSec(3, &ENS);
    fInserer(e, &fBuf);*/
    end:

    //fSauvgarder(".\\Fichiers_System\\fichiersExistants.bin", &fBuf);
    fin();
}
    
