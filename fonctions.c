#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "MachineAbstraite.h"
#include "fonctions.h"


extern char **nomWilaya, **nomSpecialite, **nomEU, **region_centre, **region_est, **region_ouest;

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

void gen_Wilaya (char Wilaya[22]) {

    strcpy(Wilaya,nomWilaya[(rand()%58)]);

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
void gen_Specialite (char Specialite[30]) {
    strcpy(Specialite,nomSpecialite[(rand()%12)]);
}


void gen_EU (char Etab_Univ[97]) {
    strcpy(Etab_Univ,nomEU[rand()%111]);
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

    for (int v = 0; v < 111; ++v) {
        fich->iEU[v].nbmat = 0;
    }
    for (int v = 0; v < 11; ++v) {
        fich->iSpecialite[v].nbmat = 0;
    }

    for (int k = 0; k < N; ++k) {

        int trouv=1;
        while (trouv)
        {

            Ens = enseignant();
            RechDicho(Ens.Matricule, fich->indexPr->tableau, k, &trouv, &pos);
        }
        int a=RechSeq(nomSpecialite, Ens.Specialite);
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
        insererLLC(&(fich->iEU[RechSeq(nomEU, Ens.Etablissement_Universitaire)].info), Ens.Matricule);
        fich->iEU[RechSeq(nomEU, Ens.Etablissement_Universitaire)].nbmat++;
        insererLLC(&(fich->iSpecialite[RechSeq(nomSpecialite,Ens.Specialite)].info),Ens.Matricule);
        fich->iSpecialite[RechSeq(nomSpecialite, Ens.Specialite)].nbmat++;

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
    int a;
    printf("\n");
    printf("Donnez le matricule de l'enseignant?\n");
    scanf("%d",&Ens.Matricule);
    for (int l = 0; l <= 113; l++)
    {
        printf ("\n %s",nomEU[l]);
    }
    printf("Donnez l'etablisssement universitaire de l'enseignant?\n");
    scanf("%d",&a);
    strcpy(Ens.Etablissement_Universitaire,nomEU[a]);

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
    }
    return Ens;
}

void afficher_enreg(L7OF *fichier, char *nomf, int mat)
{
    int i,j,k,trouv;
    BUFFER buf;
    Tenreg E;
    RechDicho (mat, fichier->indexPr->tableau, fichier->indexPr->Nenreg, &trouv, &k);
    i=fichier->indexPr->tableau[k].Nbloc,
            j=fichier->indexPr->tableau[k].Deplacement;
    lireDir(fichier, i,&buf);
    E = buf.tab[j];
    printf(" -%d:%d %d\n",i,k, E.Matricule);
    printf("%s\n",E.Wilaya);
    printf("%s\n",E.Nom);
    printf("%s\n",E.Sexe);
    printf("%s/%s/%s\n",E.Date_Naissance.jour,E.Date_Naissance.mois,E.Date_Naissance.annee);
    printf("%s\n",E.Groupe_Sanguin);
    printf("%s\n",E.Grade);
    printf("%s\n",E.Specialite);
    printf("%s\n",E.Dernier_Diplome);
    printf("%s\n",E.Etablissement_Universitaire);
    printf("%s/%s/%s\n",E.Date_Recrutement.jour,E.Date_Recrutement.mois,E.Date_Recrutement.annee);
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

void suppression_Ens(L7OF *f, char *nomf, int mat) {
    BUFFER buf;
    Tenreg X;
    int trouv=0, k=0;
    ouvrir(f,nomf,'A');
    lireDir(f, entete(f,2),&buf);
    RechDicho (mat, f->indexPr->tableau, f->indexPr->Nenreg, &trouv, &k);
    printf("%d",k);
    int i=f->indexPr->tableau[k].Nbloc,
            j=f->indexPr->tableau[k].Deplacement;
    printf("%d,%d",i,j);
    if (trouv) {
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
    }
    fermer(f);
}


void Affichage(L7OF *fichier, char *nomf) {
    BUFFER buf;
    ouvrir(fichier, nomf,'A');
    int i = 1;
    while (i!=-1) {
        lireDir(fichier, i,&buf);

        for (int k = 0; k < buf.NB; ++k) {
            printf(" -%d:%d %d\n",i,k, buf.tab[k].Matricule);
            printf("%s\n",buf.tab[k].Wilaya);
            printf("%s\n",buf.tab[k].Nom);
            printf("%s\n",buf.tab[k].Prenom);
            printf("%s\n",buf.tab[k].Sexe);
            printf("%s/%s/%s\n",buf.tab[k].Date_Naissance.jour,buf.tab[k].Date_Naissance.mois,buf.tab[k].Date_Naissance.annee);
            printf("%s\n",buf.tab[k].Groupe_Sanguin);
            printf("%s\n",buf.tab[k].Grade);
            printf("%s\n",buf.tab[k].Specialite);
            printf("%s\n",buf.tab[k].Dernier_Diplome);
            printf("%s\n",buf.tab[k].Etablissement_Universitaire);
            printf("%s/%s/%s\n",buf.tab[k].Date_Recrutement.jour,buf.tab[k].Date_Recrutement.mois,buf.tab[k].Date_Recrutement.annee);
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
    int trouv=0,pos=0,i,j,N,k;
    Tenreg E;
    BUFFER buf;

    RechDicho(matricule, fich->indexPr->tableau, fich->indexPr->Nenreg, &trouv, &pos);
    ouvrir(fich,nomf,'A');
    if (trouv){
        i=fich->indexPr->tableau[pos].Nbloc;
        j=fich->indexPr->tableau[pos].Deplacement;
        lireDir(fich,i,&buf);
        for ( int l = 0; l <= 113; l++)
        {
            printf ("\n %s",nomEU[l]);
        }
        printf("Veuillez choisir le numero du nouveau etablissement de l'enseignant");
        scanf("%d",&N);
        printf("N");
        strcpy( buf.tab[j].Etablissement_Universitaire,nomEU[N]);

    }
    ecrireDir(fich,i,&buf);
    fermer(fich);
}

void sauvIndexPr(char *nomIndex, L7OF *fichier)
{
    fichierIndex ifichier;
    tBlocIndex buf;
    indexEntete entete;
    int j = 0, i = 1;
    buf.NB=0;
    ifichier.f = fopen(nomIndex, "wb"); //ouverture en mode nouveau

    if (ifichier.f != NULL)
    {
        fseek(ifichier.f, sizeof(indexEntete), SEEK_SET); // fseek vers le premier bloc

        for ( int k = 0  ; k < fichier->indexPr->Nenreg - 1; k++) //parcourir tout l'index
        {

            if (j < MAX) //bloc non plein
            {
                buf.tab[j].Nbloc = fichier->indexPr->tableau[k].Nbloc;
                buf.tab[j].matricule = fichier->indexPr->tableau[k].matricule;
                buf.tab[j].Deplacement = fichier->indexPr->tableau[k].Deplacement;

                j++;
            }
            else //bloc plein
            {
                buf.NB = j;
                fwrite(&buf, sizeof(tBlocIndex), 1, ifichier.f); //ecriture du bloc dans le fichier
                i++;
                buf.tab[0].Nbloc = fichier->indexPr->tableau[k].Nbloc;
                buf.tab[0].matricule = fichier->indexPr->tableau[k].matricule;
                buf.tab[0].Deplacement = fichier->indexPr->tableau[k].Deplacement;

                j = 1;
            }
        }
        // ecriture du dernier bloc
        buf.NB = j;
        fwrite(&buf, sizeof(tBlocIndex), 1, ifichier.f);
        rewind(ifichier.f);
        // modification de l'entete
        ifichier.entete.nbBloc = i;
        // ecriture du l'entete dans le fichier
        fwrite(&(ifichier.entete), sizeof(indexEntete), 1, ifichier.f);
        fclose(ifichier.f);
    }
}

void chargerIndexPr(char *nomIndex, L7OF *fichier)
{

    fichierIndex ifichier;
    tBlocIndex buf;
    int k = 0 ; //position dans la table d'index
    ifichier.f = fopen(nomIndex, "rb"); //ouverture en mode lecture


    if (ifichier.f != NULL)
    {
        fread(&ifichier.entete, sizeof(indexEntete), 1, ifichier.f); //lecture d'entete
        fichier->indexPr->Nenreg = 0;
        for (int i = 1; i <= ifichier.entete.nbBloc; i++) // boucle intraBloc
        {
            fread(&buf, sizeof(tBlocIndex), 1, ifichier.f); //lecture du bloc iB dans buf
            for (int j = 0; j < buf.NB; j++)             //boucle interBloc
            {
                //chargement d'index
                fichier->indexPr->tableau[k] = buf.tab[j] ;
                k++;
                fichier->indexPr->Nenreg = fichier->indexPr->Nenreg + 1;
            }
        }
    }

    fclose(ifichier.f);
}

//  retourne un mot avec seulement des caractere alphabetique
char *motPure(char *mot)
{

    char delimiteurs[] = "/\\\t\n;:.=*\"(){}<>!?&$"; //caratere non alphabetique
    return strtok(mot, delimiteurs);
}


//  transform un fichier texte utilse comme une base de donnes vers un tableau de nbMot case chaque est une chaine de taille taiMot , cpt est le nombre des cases remplis dans le tableau
char **fichVersTab(char nomf[], int taiMot, int nbMot, int *cpt)
{

    FILE *f = fopen(nomf, "r");
    char mot[taiMot];
    char **tabMot = (char **)malloc(sizeof(char *) * nbMot); //alocation dynamique du tableau
    *cpt = 0;

    if (f != NULL)
        while (!feof(f))
        {    {

                fgets(mot, 100, f); //recuperer la ligne
                if (motPure(mot) != NULL) //s'il existe un mot dans la ligne
                {
                    strcpy(mot, motPure(mot)); // recuperer le motPure

                    tabMot[*cpt] = (char *)malloc(sizeof(char) * taiMot);
                    strcpy(tabMot[*cpt], mot); //copier le mot dans une case dans tabMot
                    *cpt = *cpt + 1;
                }
            }
        }
    fclose(f);
    return tabMot;

}

void insererLLC(maillon **tete, int matricule)
{

    maillon *p = malloc(sizeof(maillon));
    p->matricule = matricule;
    p->suivant = (struct mallion *) *tete;
    *tete = p;

}

void supprimerLLC(maillon **tete, int matricule)
{
    maillon *p = *tete, *q = NULL;
    if ((*tete) != NULL)
    {
        while ((p != NULL) && (p->matricule != matricule))
        {
            q = p;
            p = (maillon *) p->suivant;
        }
        if (p != NULL)
        {
            if (p->matricule == matricule)
            {
                if (q == NULL)
                {
                    *tete = (maillon *) (*tete)->suivant;
                    free(p);
                }
                else
                {
                    q->suivant = p->suivant;
                    free(p);
                }
            }
        }
    }
}

void libererLLC(maillon *liste)
{
    maillon *p;
    while (liste != NULL)
    {
        p = liste;
        liste = (maillon *) liste->suivant;
        free(p);
    }
}

int RechSeq(char **tabmot, char *nom) {
    int i = 0;
    int trouv = 0;
    while ((!trouv) ) {
        if (strcmp(tabmot[i], nom) == 0) {
            trouv = 1;
        }else{
            i++;
        }
    }
    return i ;
}

void Suppression_Specialite(char *nomf, L7OF *fichier){
    int Nspecialite=0, mat=0 ;
    maillon *P,*Q;
    for (int i = 0; i < 12; ++i) {
        printf("\n%s",nomSpecialite[i]);
    }
    printf("\nVeuillez choisir le numero de la specialite que vous souhaitez supprimer");
    scanf("%d",&Nspecialite);
    P=fichier->iSpecialite[Nspecialite].info;
    for (int i = 0; i < fichier->iSpecialite[Nspecialite].nbmat; ++i)
    {
        mat = P->matricule;
        suppression_Ens(fichier, nomf, mat);
        P = (maillon *) P->suivant;
    }
    P->suivant=NULL;
    libererLLC(Q);
}

void Affichage_EU(char *nomf, L7OF *fichier,int v1,int v2){
    int NEU,mat, trouv, k, i, j,v,an,d;
    maillon *P,*Q;
    BUFFER buf;
    Tenreg E ;

    SYSTEMTIME Time;
    GetLocalTime(&Time);
    an=Time.wYear;

    ouvrir(fichier,nomf,'A');
    for (int i = 0; i < 114; ++i) {
        printf("\n%s",nomEU[i]);
    }
    printf("\nVeuillez choisir le numero de l'etablissement que vous souhaitez afficher");
    scanf("%d",&NEU);
    printf("enrez la premiere valeure");
    scanf("%d",&v1);
    printf("enrez la 2eme valeure");
    scanf("%d",&v2);
    P=fichier->iEU[NEU].info;

    for (int l = 0; l <fichier->iEU[NEU].nbmat ; ++l)
    {
        mat = P->matricule;
        RechDicho (mat, fichier->indexPr->tableau, fichier->indexPr->Nenreg, &trouv, &k);
        i=fichier->indexPr->tableau[k].Nbloc,
                j=fichier->indexPr->tableau[k].Deplacement;
        lireDir(fichier, i,&buf);
        E = buf.tab[j];
        d = atoi(E.Date_Recrutement.annee);
        v = (an-d);
        if ((v>=v1) && (v<=v2)){
            afficher_enreg(fichier, nomf, E.Matricule)  ;      }
        else printf("Il n'exise aucun enseignant ayant uen anciennée entre ces deuc valeurs");
        P = (maillon *) P->suivant;
    }
    if (fichier->iEU[NEU].nbmat == 0){
        printf("Il n'existe aucun enseignant enregistré dans cet etabliseement");
    }
}
void consultation_region(L7OF *fich, char *nomf) {
    int i, mat, trouv, k,cpt;
    maillon *P;
    Tenreg E;
    BUFFER buf;
    printf("donner la region: 01-Centre \n 02-Est \n 03-Ouest");
    scanf(" %d", &i);
    ouvrir(fich, nomf, 'A');
    if (i == 1) {
        int c = 0;
        region_centre = fichVersTab("..\\Fichiers_System\\region-centre.txt", 97, 45, &c);
        for (int j = 0; j < 45; ++j) {
            int u = RechSeq(nomEU, region_centre[j]);
            if (fich->iEU[u].nbmat != 0) {
                P = fich->iEU[u].info;
                for (int l = 0; l < fich->iEU[u].nbmat; ++l) {
                    mat = P->matricule;
                    printf("le mat est %d ",mat);
                    afficher_enreg(fich, nomf, mat)  ;
                    P = (maillon *) P->suivant;
                }
            }

        }
    } else if (i == 2) {
            int c = 0;
            region_est = fichVersTab("..\\Fichiers_System\\region-est.txt", 97, 37, &c);
            for (int j = 0; j < 37; ++j) {
                int u = RechSeq(nomEU, region_est[j]);
                if (fich->iEU[u].nbmat != 0) {
                    P = fich->iEU[u].info;
                    for (int l = 0; l < fich->iEU[u].nbmat; ++l) {
                        mat = P->matricule;
                        printf("le mat est %d ",mat);
                        afficher_enreg(fich, nomf, mat)  ;
                        P = (maillon *) P->suivant;
                    }
                }

            }
        }
    else if (i==3) {
        int c = 0;
        region_ouest = fichVersTab("..\\Fichiers_System\\region-ouest.txt", 97, 30, &c);
        for (int j = 0; j < 29; ++j) {
                int u = RechSeq(nomEU, region_ouest[j]);
                if (fich->iEU[u].nbmat != 0) {
                    P = fich->iEU[u].info;
                    for (int l = 0; l < fich->iEU[u].nbmat; ++l) {
                        mat = P->matricule;
                        afficher_enreg(fich, nomf, mat)  ;
                        P = (maillon *) P->suivant;
                    }
                }
            }
        }
    }


void sauvIndexSec(int codeIndex, char *nomIndexSec, L7OF *fichier)
{
    indexEntete buff;
    fichierIndex ifichier;
     tBlocIndexSec buf;

    int max;
    caseSec *tabIndex;
    maillon *liste;

    switch (codeIndex) // choisir l'index a sauvgarde selon le condeIndex
    {
        case 1:
            max = NB_EU;
            tabIndex = fichier->iEU;
            break;
        case 2:
            max = NB_SPECIALITE;
            tabIndex = fichier->iSpecialite;
            break;
        default:
            return;
            break;
    }

    int matricule, j = 0, i = 1;

    ifichier.f = fopen(nomIndexSec, "wb"); //ouverture en mode nouveau
    if (ifichier.f != NULL)
    {
        fseek(ifichier.f, sizeof(indexEntete), SEEK_SET);
        for (int k = 0; k < max; k++) // parcours des case du table d'index  [les differentes listes]
        {
            liste = tabIndex[k].info;
            int cpt=tabIndex[k].nbmat;
            while (cpt!=0) //parcours d'une liste
            {
                if (j < MAX) //bloc non plein
                {
                    buf.tab[j] = liste->matricule;
                    j++;
                }
                else //bloc plein
                {
                    //ecriture du bloc en MS
                    buf.NB = j;
                    fwrite(&buf, sizeof(tBlocIndex), 1, ifichier.f);
                    i++;
                    buf.tab[0] = liste->matricule;
                    j = 1;

                }
                liste = (maillon *) liste->suivant;
                cpt--;
            }
            if (j < MAX)
            {
                buf.tab[j] = -1;
                j++;
            }
            else
            {
                i++;
                buf.NB = j;
                fwrite(&buf, sizeof(tBlocIndexSec), 1, ifichier.f);
                buf.tab[0] = -1;
                j = 1;
            }

        }

        //ecriture du dernier buffer en MS
        buf.NB = j;
        fwrite(&buf, sizeof(tBlocIndex), 1, ifichier.f);
        ifichier.entete.nbBloc = i; //M-a-j d'entete
        rewind(ifichier.f);
        fwrite(&(ifichier.entete), sizeof(indexEntete), 1, ifichier.f); //ecriture d'entete
        fclose(ifichier.f);


    }
}

void chargerIndexSec(int codeIndex, char *nomIndexSec, L7OF *fichier)
{

    fichierIndex ifichier;

    tBlocIndexSec *buf;
    buf = malloc(sizeof(tBlocIndexSec)); //alloue un buffer dynamiquement

    int indice = 0;
    ifichier.f = fopen(nomIndexSec, "rb"); //ouverture en mode ancien

    for (int v = 0; v < 111; ++v) {
        fichier->iEU[v].nbmat = 0;
    }
    for (int v = 0; v < 11; ++v) {
        fichier->iSpecialite[v].nbmat = 0;
    }

    if (ifichier.f != NULL)
    {

        rewind(ifichier.f);
        fread(&(ifichier.entete), sizeof(indexEntete), 1, ifichier.f); //lecture d'entete

        for (int i = 1; i <= ifichier.entete.nbBloc; i++) //parcourir les blocs de fichier de sauvgarde
        {

            fread(buf, sizeof(tBlocIndexSec), 1, ifichier.f);

            for (int j = 0; j < buf->NB; j++) //parcour des matricules dans le buf
            {
                if (buf->tab[j] == -1) //changement de liste
                {
                    indice++;
                }
                else // insertion dans la liste
                {

                    switch (codeIndex) //choisir l'index selon le code index
                    {
                        //insertion dans la liste du table d'index
                        case 1:
                            insererLLC(&(fichier->iEU[indice].info), buf->tab[j]);
                            fichier->iEU[indice].nbmat;
                            break;
                        case 2:
                            insererLLC(&(fichier->iSpecialite[indice].info), buf->tab[j]);
                            fichier->iSpecialite[indice].nbmat;
                            break;
                        default:
                            return;
                          break;
                    }
                }
            }
        }
    }
    free(buf);
    fclose(ifichier.f);
}



void Affichage_Entete(L7OF *fichier, char *nomf) {
    ouvrir(fichier, nomf, 'A');
    printf("\n%d", entete(fichier,1));
    printf("\n%d", entete(fichier,2));
    printf("\n%d", entete(fichier,3));
}

char *gen_cle( char *code,const char *cle) {
    char *newCle = malloc(strlen(code)+1);
    strcpy(newCle,cle);
    int x = strlen(code),
            y = strlen(newCle);
    int i=0;
    while (y != x) {
        if (i==x){
            i=0;
        }
        strncat(newCle, &newCle[i],1);
        i++;
        y = strlen(newCle);
    }
    stringToUpper(newCle);
    return newCle;
}

void Encrypted(char *code, const char *cle, char codee[]) {
    stringToUpper(code);
    char *key = gen_cle(code,cle);
    strncpy(codee,"",30);
    for (int i=0; i < strlen(code); i++) {
        int x=0;
        x = (code[i] + key[i]) % 26;
        x = x + 'A';
        codee[i] = (char) x;
    }
}

void Decrypted(char *coded, char *cle,char decodee[]) {
    stringToUpper(coded);
    char *deckey= gen_cle(coded,cle);
    strncpy(decodee,"",31);
    int i=0;
    while ((i < strlen(coded) && (i < strlen(deckey)))){
        int x = (coded[i] - deckey[i] + 26)%26;
        x = x+'A';
        decodee[i]=(char) x;
        i++;
    }
}


void coderMat(int n, int *matricule) {
    char tab_char[7];
    int tab_int[7];
    itoa(n,tab_char,10);

    for (int i = 0; i < 6; ++i) {
        if (tab_char[i]=='0') {
            tab_char[i]='9';
        }
        tab_int[i]=tab_char[i]- '0';
    }
    *matricule = bubbleSort(tab_int,*matricule,1);
    for (int i = 0; i < 6; ++i) {
        tab_char[i]=tab_int[i]+'0';

    }
    n = atoi(tab_char);


}
void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// A function to implement bubble sort
int bubbleSort(int arr[], int mat,int sort)
{
    int i, j;
    char tab_char[7];
    int tab_int[7];
    itoa(mat,tab_char,10);

    for (int k= 0; k < 6; ++k) {
        tab_int[k]=tab_char[k]- '0';
    }

    for (i = 0; i < 5 ; i++)

        // Last i elements are already in place
        for (j = 0; j < 5 - i ; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                if(sort) swap(&tab_int[j],&tab_int[j+1]);

            }

        }
    if (sort) {
        for (int k = 0; k < 6; ++k) {
            tab_char[k]=tab_int[k]+'0';
            mat = atoi(tab_char);
        }
    }

    return mat;
}

int decoderMat(int key, int *mat) {

    char ord_key[7],mat_char[7];
    int tab[7], tab1[7],tab_mat[7];
    itoa(key,ord_key,10);
    for (int i = 0; i < 6; ++i) {
        tab[i]=ord_key[i]-'0';
        tab1[i]=tab[i];//tab1 key init
    }
    itoa(*mat,mat_char,10);
    for (int i = 0; i < 6; ++i) {
        tab_mat[i]=mat_char[i]-'0';
    }
    bubbleSort(tab,*mat,0); //tab key ordored
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (tab[j]!=tab1[j]) {
                int pos = lookFor(tab,tab1[j]);
                swap(&tab[pos], &tab[j]);
                swap(&tab_mat[pos],&tab_mat[j]);
            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        mat_char[i]=tab_mat[i]+'0';
    }
    *mat=atoi(mat_char);
    return *mat;
}


int lookFor(int tab_int[7], int a) {
    int i;
    for (int j = 0; j < 6; ++j) {
        if (tab_int[j] == a)  {
            i=j;
        }
    }
    return i;
}




void Decodage(L7OF *fichdecode, char *nomfDecode, char *nomfCode) {
    BUFFER buf_init, buf_code;
    L7OF fichDecode;
    int j=0, mat,i1,i2;
    ouvrir(&fichDecode,nomfDecode,'N');
    ouvrir(fichdecode,nomfCode,'A');
    int key= 965214;
    char *key2="spr";
    i1= allocBloc(&fichDecode);
    int i = entete(fichdecode, 1);
    lireDir(fichdecode, i,&buf_init);
    for (int k = 0; k < entete(fichdecode,3); ++k) {
        if (j < b) {
            mat = buf_init.tab[j].Matricule;
            buf_code.tab[j].Matricule= decoderMat(key,&mat);
            Decrypted(buf_init.tab[j].Nom,key2,buf_code.tab[j].Nom);
            stringToLower(buf_code.tab[j].Nom);
            buf_code.tab[j].Nom[0]= toupper(buf_code.tab[j].Nom[0]);
            Decrypted(buf_init.tab[j].Prenom,key2,buf_code.tab[j].Prenom);
            buf_code.tab[j].Prenom[0]= toupper(buf_code.tab[j].Prenom[0]);
            stringToLower(buf_code.tab[j].Prenom);
            strcpy(buf_code.tab[j].Sexe,buf_init.tab[j].Sexe);
            strcpy(buf_code.tab[j].Dernier_Diplome,buf_init.tab[j].Dernier_Diplome);
            strcpy(buf_code.tab[j].Grade,buf_init.tab[j].Grade);
            buf_code.tab[j].Date_Naissance=buf_init.tab[j].Date_Naissance;
            buf_code.tab[j].Date_Recrutement=buf_init.tab[j].Date_Recrutement;
            strcpy(buf_code.tab[j].Groupe_Sanguin,buf_init.tab[j].Groupe_Sanguin);
            strcpy(buf_code.tab[j].Specialite,buf_init.tab[j].Specialite);
            strcpy(buf_code.tab[j].Etablissement_Universitaire,buf_init.tab[j].Etablissement_Universitaire);
            strcpy(buf_code.tab[j].Wilaya,buf_init.tab[j].Wilaya);


            j++;
        } else {
            i++;
            lireDir(fichdecode,i,&buf_init);
            i2 = allocBloc(&fichDecode);
            buf_code.suivant=i2;
            buf_code.NB=b;
            ecrireDir(&fichDecode, i1,&buf_code);
            i1=i2;
            mat = buf_init.tab[0].Matricule;
            buf_code.tab[0].Matricule= decoderMat(key,&mat);
            Decrypted(buf_init.tab[0].Nom,key2,buf_code.tab[0].Nom);
            stringToLower(buf_code.tab[0].Nom);
            buf_code.tab[0].Nom[0]= toupper(buf_code.tab[0].Nom[0]);
            Decrypted(buf_init.tab[0].Prenom,key2,buf_code.tab[0].Prenom);
            stringToLower(buf_code.tab[0].Prenom);
            buf_code.tab[0].Prenom[0]= toupper(buf_code.tab[0].Prenom[0]);
            strcpy(buf_code.tab[0].Sexe,buf_init.tab[0].Sexe);
            strcpy(buf_code.tab[0].Dernier_Diplome,buf_init.tab[0].Dernier_Diplome);
            strcpy(buf_code.tab[0].Grade,buf_init.tab[0].Grade);
            buf_code.tab[0].Date_Naissance=buf_init.tab[0].Date_Naissance;
            buf_code.tab[0].Date_Recrutement=buf_init.tab[0].Date_Recrutement;
            strcpy(buf_code.tab[0].Groupe_Sanguin,buf_init.tab[0].Groupe_Sanguin);
            strcpy(buf_code.tab[0].Specialite,buf_init.tab[0].Specialite);
            strcpy(buf_code.tab[0].Etablissement_Universitaire,buf_init.tab[0].Etablissement_Universitaire);
            strcpy(buf_code.tab[0].Wilaya,buf_init.tab[0].Wilaya);

            buf_code.NB=0;
            j=1;

        }
    }
    buf_code.NB=j;
    buf_code.suivant=-1;
    ecrireDir(&fichDecode,i1,&buf_code);
    affEntete(&fichDecode,1,1);
    affEntete(&fichDecode,2,i1);
    affEntete(&fichDecode,3, entete(fichdecode,3));
    fermer(fichdecode);
    fermer(&fichDecode);
}

void Codage(L7OF *fichier, char *nomfCode, char *nomf) {
    BUFFER buf_init, buf_code;
    L7OF fichCode;
    int j=0, mat,i1,i2;
    ouvrir(&fichCode,nomfCode,'N');
    ouvrir(fichier,nomf,'A');
    int key= 965214;
    char key2[]="spr", *string;
    Tenreg e;
    strcpy(key2,key2);
    i1=allocBloc(&fichCode);
    int i = entete(fichier, 1);
    lireDir(fichier, i,&buf_init);
    for (int k = 0; k < entete(fichier,3); ++k) {
        if (j < b) {
            mat = buf_init.tab[j].Matricule;
            coderMat(key,&mat);
            buf_code.tab[j].Matricule=mat;
            Encrypted(buf_init.tab[j].Nom,key2,buf_code.tab[j].Nom);
            Encrypted(buf_init.tab[j].Prenom,key2,buf_code.tab[j].Prenom);
            strcpy(buf_code.tab[j].Sexe,buf_init.tab[j].Sexe);
            strcpy(buf_code.tab[j].Dernier_Diplome,buf_init.tab[j].Dernier_Diplome);
            strcpy(buf_code.tab[j].Grade,buf_init.tab[j].Grade);
            buf_code.tab[j].Date_Naissance=buf_init.tab[j].Date_Naissance;
            buf_code.tab[j].Date_Recrutement=buf_init.tab[j].Date_Recrutement;
            strcpy(buf_code.tab[j].Groupe_Sanguin,buf_init.tab[j].Groupe_Sanguin);
            strcpy(buf_code.tab[j].Specialite,buf_init.tab[j].Specialite);
            strcpy(buf_code.tab[j].Etablissement_Universitaire,buf_init.tab[j].Etablissement_Universitaire);
            strcpy(buf_code.tab[j].Wilaya,buf_init.tab[j].Wilaya);
            j++;
        } else {
            i++;
            lireDir(fichier,i,&buf_init);
            i2 = allocBloc(&fichCode);
            buf_code.suivant=i2;
            buf_code.NB=b;
            ecrireDir(&fichCode, i1,&buf_code);
            i1=i2;
            mat = buf_init.tab[0].Matricule;
            coderMat(key,&mat);
            buf_code.tab[0].Matricule=mat;
            Encrypted(buf_init.tab[0].Nom,key2,buf_code.tab[0].Nom);
            Encrypted(buf_init.tab[0].Prenom,key2,buf_code.tab[0].Prenom);
            strcpy(buf_code.tab[0].Sexe,buf_init.tab[0].Sexe);
            strcpy(buf_code.tab[0].Dernier_Diplome,buf_init.tab[0].Dernier_Diplome);
            strcpy(buf_code.tab[0].Grade,buf_init.tab[0].Grade);
            buf_code.tab[0].Date_Naissance=buf_init.tab[0].Date_Naissance;
            buf_code.tab[0].Date_Recrutement=buf_init.tab[0].Date_Recrutement;
            strcpy(buf_code.tab[0].Groupe_Sanguin,buf_init.tab[0].Groupe_Sanguin);
            strcpy(buf_code.tab[0].Specialite,buf_init.tab[0].Specialite);
            strcpy(buf_code.tab[0].Etablissement_Universitaire,buf_init.tab[0].Etablissement_Universitaire);
            strcpy(buf_code.tab[0].Wilaya,buf_init.tab[0].Wilaya);
            buf_code.NB=0;
            j=1;

        }
    }
    buf_code.NB=j;
    buf_code.suivant=-1;
    ecrireDir(&fichCode,i1,&buf_code);
    affEntete(&fichCode,1,1);
    affEntete(&fichCode,2,i1);
    affEntete(&fichCode,3, entete(fichier,3));
    fermer(fichier);
    fermer(&fichCode);
}



void stringToUpper(char *Str) {
    for (int i=0; i< strlen(Str)+1; i++) {
        Str[i]= toupper(Str[i]);
    }
}

void stringToLower(char *Str) {
    for (int i=0; i< strlen(Str); i++) {
        Str[i]= tolower(Str[i]);
    }

}
