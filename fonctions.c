#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MachineAbstraite.h"
#include "fonctions.h"


void gen_Matricule (int *matricule) {
    *matricule=0;
    *matricule=(rand()*100)%888888+111111;

}
void gen_Nom (char nom[31]) {
    strncpy(nom, "",30);
    int taille=(rand()%27) + 4;
    for (int i = 0; i < taille; ++i) {
        int caractere=(rand()%26)+1;
        nom[i]= caractere + (96);
    }
    nom[0]= toupper(nom[0]);

}

void gen_Date (Date *date) {
    int n;
    strncpy((*date).jour, "",2);
    strncpy((*date).annee, "",2);
    strncpy((*date).mois, "",4);
    sprintf((*date).annee,"%d",(rand()%46)+1953);

    sprintf((*date).mois,"%d",(rand()%13)+1);

    if (strcmp((*date).mois,"2") == 0) {
        if ((atoi((*date).annee)%4) == 0) { //année bissextile

            n=28;
        } else {
            n=27;
        }
    } else {
        if (((atoi((*date).mois)%2)== 1) || ( strcmp((*date).mois,"8") == 0)) { //les mois impairs et le mois d'aout ont 31jours au max
            n=30;
        } else {
            n=29;
        }
    }
    sprintf((*date).jour,"%d",(rand()%(n+1))+1);

}

void gen_Wilaya (char Wilaya[3]) {

    sprintf(Wilaya,"%d",rand()%58+1);


}

void gen_Sexe (char Sexe[10]) {
    if (rand()%2+1 == 1) {
        strcpy(Sexe,"Masculain");
    } else {
        strcpy(Sexe,"Feminain");
    }

}

void gen_Grade (char Grade[30]) {
    char tabGS[6][30] = {"Professeur","Maitre de conferences Rang A","Maitre de conferences Rang B","Maitre assistant Rang A","Maitre assistant Rang B","Assistant"};
    strcpy(Grade,tabGS[rand()%6]);
}

void gen_Dernier_Diplome (char Dernier_Diplome[30]) {
    char tabDD[6][30] = {"Doctorat d'Etat","Doctorat en sciences","Doctorat D_LMD","PhD","Habiliation Universitaire","Magistere"};
    strcpy(Dernier_Diplome,tabDD[rand()%6]);
}
void gen_Specialite (char Specialite[4]) {
    sprintf(Specialite,"%d",rand()%122+1);
}

void gen_EU (char Etab_Univ[4]) {
    sprintf(Etab_Univ,"%d",rand()%111+1);
}

void gen_GS (char groupeSanguin[4]) {
    char tabGS[8][4] = {"O+","A+","B+","O-","A-","AB+","B-","AB-"};
    strcpy(groupeSanguin,tabGS[rand()%8]);
}

Tenreg enseignant() {
    Tenreg e;
    gen_Matricule(&e.Matricule);
    gen_Nom(e.Nom);
    gen_Nom(e.Prenom);
    gen_Date(&e.Date_Naissance);
    gen_Wilaya(e.Wilaya);
    gen_Sexe(e.Sexe);
    gen_GS(e.Groupe_Sanguin);
    gen_Date(&e.Date_Recrutement);
    gen_Grade(e.Grade);
    gen_Specialite(e.Specialite);
    gen_Dernier_Diplome(e.Dernier_Diplome);
    gen_EU(e.Etablissement_Universitaire);
    return e;
}

void chargementInitial(L7OF *fich, char *nomf, int N) {
    Tenreg Ens;
    BUFFER buf;
    caseIndexPrimaire valIndex;

    int i=0,
    j=0,
    i1=0,

    pos;

    ouvrir(fich, nomf, 'N');
    fich->indexPr->Nenreg=0;
    i=allocBloc(fich);
    for (int k = 0; k < N; ++k) {
        int trouv=1;
        while (trouv)
        {
            Ens = enseignant();
            RechDicho(Ens.Matricule, fich->indexPr->tableau, k, &trouv, &pos);
        }
        if (j < b) {
            buf.tab[j]=Ens;
           valIndex = (caseIndexPrimaire){.matricule = Ens.Matricule, .Nbloc = i, .Deplacement = j};
            insertion_Index(valIndex, fich->indexPr->tableau, fich->indexPr->Nenreg);
            fich->indexPr->Nenreg++;
            j++;
        } else {
            buf.NB=b;

            i1=allocBloc(fich);
            buf.suivant=i1;
            ecrireDir(fich, i, &buf);
            i=i1;
            buf.tab[0]=Ens;
            valIndex = (caseIndexPrimaire){.matricule = Ens.Matricule, .Nbloc = i, .Deplacement = 0};
            insertion_Index(valIndex, fich->indexPr->tableau, fich->indexPr->Nenreg);
            fich->indexPr->Nenreg++;
            j=1;
        }
    }
    buf.NB=j;
    buf.suivant=-1;
    ecrireDir(fich,i,&buf);
    affEntete(fich,1,1);
    affEntete(fich,2,i);
    affEntete(fich,3,N);
    fermer(fich); //sans la fermeture du fichier rien ne sera enregistré dans la MS
}


void RechDicho (int matricule, caseIndexPrimaire *Case, int taille, int *trouv, int *k ) {
    int bi=0,
            bs=taille-1;
    *trouv=0;
    while ((bi <= bs) && (!(*trouv))) {
        (*k)=(bi+bs)/2;
        if (matricule == Case[*k].matricule) {
            *trouv=1;
        }
        else if (matricule < Case[*k].matricule) {
            bs=(*k)-1;
        }else{
            bi=(*k)+1;
        }
    }
    if(!(*trouv)) {
        (*k)=bi;
    }

}


Tenreg Demander_Info() {
    Tenreg Ens;
    caseIndexPrimaire Case;
    int trouv,k,taille;

    printf("\n");
    printf("Donnez le matricule de l'enseignant?\n");
    scanf("%d",&Ens.Matricule);
/*
    RechDicho (Ens.Matricule, &Case, taille, &trouv, &k);
    if (trouv) {
        printf("L'enregistrement de l'enseignant existe déja!");
    } else {
        printf("Donnez le nom de l'enseignant?\n");
        scanf("%s",Ens.Nom);
        printf("Donnez le prenom de l'enseignant?\n");
        scanf("%s",Ens.Prenom);
        printf("Donnez l'annee, le mois, et le jour de naissance de l'enseignant?\n");
        scanf("%s %s %s",Ens.Date_Naissance.annee,Ens.Date_Naissance.mois,Ens.Date_Naissance.jour );
        printf("Donnez la wilaya de l'enseignant?\n");
        scanf("%s",Ens.Wilaya);
        printf("Donnez le sexe de l'enseignant?\n");
        scanf("%s",Ens.Sexe);
        printf("Donnez le groupe sanguin de l'enseignant?\n");
        scanf("%s",Ens.Groupe_Sanguin);
        printf("Donnez l'annee, le mois, et le jour de recrutement de l'enseignant?\n");
        scanf("%s %s %s",Ens.Date_Recrutement.annee,Ens.Date_Recrutement.mois,Ens.Date_Recrutement.jour );
        printf("Donnez le grade de l'enseignant?\n");
        scanf("%s",Ens.Grade);
        printf("Donnez la specialite de l'enseignant?\n");
        scanf("%s",Ens.Specialite);
        printf("Donnez le dernier diplome de l'enseignant?\n");
        scanf("%s",Ens.Dernier_Diplome);
        printf("Donnez l'etablisssement universitaire de l'enseignant?\n");
        scanf("%s",Ens.Etablissement_Universitaire);
    }*/
    return Ens;
}

void insertion_Ens(L7OF *fich, char *nomf) { //Insertion sans table d'index
    ouvrir(fich,nomf,'A');
    int i = entete(fich, 2),
    i1=0, trouv=1, pos=0;
    caseIndexPrimaire valIndex;
    BUFFER buf;
    lireDir(fich, i, &buf);
    Tenreg E = Demander_Info();

    RechDicho(E.Matricule, fich->indexPr->tableau, fich->indexPr->Nenreg, &trouv, &pos);
    if (!trouv)
    {
    if (buf.NB < b) {
        buf.tab[buf.NB]=E;

    } else {
        i1 = allocBloc(fich);
        buf.suivant=i1;
        ecrireDir(fich,i,&buf);
        i=i1;
        lireDir(fich,i,&buf);
        buf.tab[0]=E;
        buf.NB=0;
    }
    valIndex = (caseIndexPrimaire){.matricule = E.Matricule, .Nbloc = i, .Deplacement = buf.NB};
    insertion_Index(valIndex, fich->indexPr->tableau,fich->indexPr->Nenreg );
    fich->indexPr->Nenreg++;

    buf.NB++;
    buf.suivant=-1;
    ecrireDir(fich,i,&buf);
    affEntete(fich,2,i);
    affEntete(fich,3, entete(fich,3)+1);
    }
    else {
        printf("\n Insertion impossible. Si vous souhaitez effectuer une modification de \nl'etablissement universiaire, veuillez revenir au menu principal");
    }
    fermer(fich);
}

void suppression_Ens(L7OF *f, char *nomf) {
    BUFFER buf;
    int i=2,
            j=1;
    Tenreg X;
    ouvrir(f,nomf,'A');
    lireDir(f, entete(f,2),&buf);
    if ((entete(f,2) == entete(f,1)) && buf.NB==1) {
        affEntete(f,1,-1);
        affEntete(f,2,-1);
        affEntete(f,3,0);
        buf.NB=0;
    } else {

        X=buf.tab[buf.NB-1];
        buf.NB--;
        if (buf.NB==0) {

            affEntete(f,2, entete(f,2)-1);
            lireDir(f, entete(f,2),&buf);
            buf.suivant=-1;
        }
        ecrireDir(f, entete(f,2),&buf);
        lireDir(f,i,&buf);
        buf.tab[j]=X;
        affEntete(f,3, entete(f,3)-1);

    }
    ecrireDir(f, i,&buf);
    fermer(f);
}

void Affichage(L7OF *fichier, char *nomf) {
    BUFFER buf;
    ouvrir(fichier, nomf,'A');
    int i = 1;
    while (i!=-1) {
        lireDir(fichier, i,&buf);
        for (int k = 0; k < buf.NB; ++k) {
            printf(" -%d:%d %d\n",i,k, buf.tab[k].Matricule); //si tu veux tester les autres champs enleve juste les (/**/)
            /*
            printf("%s\n",buf.tab[k].Nom);
            printf("%s\n",buf.tab[k].Prenom);
            printf("%s\n",buf.tab[k].Sexe);
            printf("%s/%s/%s\n",buf.tab[k].Date_Naissance.jour,buf.tab[k].Date_Naissance.mois,buf.tab[k].Date_Naissance.annee);
            printf("%s\n",buf.tab[k].Wilaya);
            printf("%s\n",buf.tab[k].Groupe_Sanguin);
            printf("%s\n",buf.tab[k].Grade);
            printf("%s\n",buf.tab[k].Dernier_Diplome);
            printf("%s/%s/%s\n",buf.tab[k].Date_Recrutement.jour,buf.tab[k].Date_Recrutement.mois,buf.tab[k].Date_Recrutement.annee);
        */
        }
        i=buf.suivant;
    }
    fermer(fichier);
}

void insertion_Index(caseIndexPrimaire valeur, caseIndexPrimaire *tab, int taille)
{

    char continu = 1;
    int k = taille - 1;

    while (k >= 0 && continu)
    {
        if (valeur.matricule < tab[k].matricule)
        {
            tab[k + 1] = (caseIndexPrimaire){.matricule = tab[k].matricule, .Nbloc = tab[k].Nbloc, .Deplacement = tab[k].Deplacement};

            k = k - 1;
        }
        else
        {
            tab[k + 1] = (caseIndexPrimaire){.matricule = valeur.matricule, .Nbloc = valeur.Nbloc, .Deplacement = valeur.Deplacement};
            continu = 0;
        }
    }
    if (continu)
    {
        tab[0] = (caseIndexPrimaire){.matricule = valeur.matricule, .Nbloc = valeur.Nbloc, .Deplacement = valeur.Deplacement};
    }
}
void suppTabOrd(caseIndexPrimaire *tab, int taille, int pos)
{

    while (pos < taille - 1)
    {
        tab[pos] = tab[pos + 1];
        pos++;
    }
}

void Modification_Ens(char *nomf, L7OF *fich, int matricule) {
    int trouv,pos,i,j;
    Tenreg E;
    BUFFER buf;
    RechDicho(matricule, fich->indexPr->tableau, fich->indexPr->Nenreg, &trouv, &pos);
    if (trouv){
        i=fich->indexPr->tableau[pos].Nbloc;
        j=fich->indexPr->tableau[pos].Deplacement;
        lireDir(fich,i,&buf);

        strcpy( buf.tab[j].Etablissement_Universitaire,"merde");
    }
}

void sauvIndexPr(char nomIndex[], L7OF *fichier)
{

    fichierIndex ifichier;
    tBlocIndex buf;
    int j = 0, i = 1;

    ifichier.f = fopen(nomIndex, "wb"); //ouverture en mode nouveau

    if (ifichier.f != NULL)
    {
        fseek(ifichier.f, sizeof(indexEntete), SEEK_SET); // fseek vers le premier bloc

        for ( int k = 0  ; k < fichier->indexPr->Nenreg - 1; k++) //parcourir tout l'index
        {

            if (j < MAX) //bloc non plein
            {
                buf.tab[j] = fichier->indexPr->tableau[k];
                j++;
            }
            else //bloc plein
            {
                buf.NB = j;
                fwrite(&buf, sizeof(tBlocIndex), 1, ifichier.f); //ecriture du bloc dans le fichier
                i++;
                buf.tab[0] = fichier->indexPr->tableau[k]; ;
                j = 1;
            }
        }
        // ecriture du dernier bloc
        buf.NB = j;
        fwrite(&buf, sizeof(tBlocIndex), 1, ifichier.f);
        // modification de l'entete
        ifichier.entete.nbBloc = i;
        rewind(ifichier.f);
        // ecriture du l'entete dans le fichier
        fwrite(&(ifichier.entete), sizeof(indexEntete), 1, ifichier.f);
        fclose(ifichier.f);
    }
}

