#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MachineAbstraite.h"
#include "fonctions.h"


void gen_Matricule (char matricule[7]) {
    strncpy(matricule,"",6);
    sprintf(matricule,"%d",(rand()*100)%888888 + 111111); //car RAND_MAX=32767.
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
    gen_Matricule(e.Matricule);
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

void RechDicho (char matricule[7], caseIndexPrimaire *Case, int taille, int *trouv, int *k ) {
    int bi=0,
            bs=taille-1;
    *trouv=0;
    while ((bi <= bs) && (!(*trouv))) {
        (*k)=(bi+bs)/2;
        if (strcmp(matricule, Case[*k].matricule) == 0) {
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

void chargementInitial(char *nomf, int N, L7OF *fich) //Chargement initial (table d'index non verifiee
{
    Tenreg Ens;
    BUFFER buf;
    caseIndexPrimaire val;
    int i=1,
        j=0;
    ouvrir(fich, nomf, 'N');
    for (int k = 0; k < N; ++k) {
        Ens = enseignant();
        if (j < b) {
            buf.tab[j]=Ens;
            val = (caseIndexPrimaire){.matricule = Ens.Matricule, .Nbloc = i, .Deplacement = j};
            insererIndex(val, fich->indexPrimaire->tab, k);
            j++;
        } else {
            buf.NB=b;
            
            i1 = allocBloc(fich);
            buf.suivant=i1;
            ecrireDir(fich, i, &buf);
            i=i1;
            lireDir(fich, i,&buf);
            buf.tab[0]=Ens;
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


Tenreg Demander_Info() {
    Tenreg Ens;
    caseIndexPrimaire Case;
    int trouv,k,taille;

    printf("\n");
    printf("Donnez le matricule de l'enseignant?\n");
    scanf(" %s",Ens.Matricule);
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

    }
    */
    return Ens;
}





//  une insertion par decalage dans la table d'index
void insererIndex(caseIndexPrimaire valeur, caseIndexPrimaire *tab, int taille)
{

    char stop = 0;
    int k = taille - 1;

    while (k >= 0 && !stop)
    {
        if (valeur.matricule < tab[k].matricule)
        {
            tab[k + 1] = (caseIndexPrimaire){.matricule = tab[k].matricule, .Nbloc = tab[k].Nbloc, .Deplacement = tab[k].Deplacement};
            k = k - 1;
        }
        else
        {
            tab[k + 1] = (caseIndexPrimaire){.matricule = valeur.matricule, .Nbloc = valeur.Nbloc, .Deplacement = valeur.Deplacement};
            stop = 1;
        }
    }
    if (!stop)
    {
        tab[0] = (caseIndexPrimaire){.matricule = valeur.matricule, .Nbloc = valeur.Nbloc, .Deplacement = valeur.Deplacement};

    }
}

void insertion_Ens(L7OF *fich, char *nomf) { //Insertion sans table d'index
    ouvrir(fich,nomf,'A');
    int i = entete(fich, 2),
    i1;
    BUFFER buf;
    lireDir(fich, i, &buf);


    Tenreg E = Demander_Info();
    if (buf.NB < b) {
        buf.tab[buf.NB]=E;

    } else {
        i1 = allocBloc(fich);
        buf.suivant=i1;
        ecrireDir(fich,i,&buf);
        i=i1;
        lireDir(fich,i,&buf);
        buf.tab[0]=E;
        affEntete(fich,2,i1);
    }
    buf.NB++;
    ecrireDir(fich,i,&buf);
    affEntete(fich,3, entete(fich,3)+1);
    fermer(fich);
}




void Affichage(L7OF *fichier, char *nomf) {
    BUFFER buf;
    ouvrir(fichier, nomf,'A');
    int i = 1;
    while (i!=-1) {
        lireDir(fichier, i,&buf);
        for (int k = 0; k < buf.NB; ++k) {
            printf(" -%d: %s\n",k, buf.tab[k].Matricule); //si tu veux tester les autres champs enleve juste les (/**/)
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

}
