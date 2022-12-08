# TP
1/Faut fermer le fichier apres chaque modification sinon on ne pourra rien reccuperer
2/Le fichier est supposé etre .BIN, de plus faut verifier la creation du fichier dans le dossier ou se trouve le projet
3/je comprends pas la modifiction dans les deux fonctions de lecture et ecriture (i-1)
4/allocbloc a ete modifier (instructions inutiles lors de l'utilisation d'un seul buffer)
5/Petit conseil: limite b à 5 ça te permettra de cibler le scas particuliers 
tu peux tester avec ça le bon fonctionnement des deux fonctions (j'ai prefere afficher tout le fichier)
int main() {
    srand(time(NULL));
    Tenreg E;
    BUFFER buf;
    L7OF F;
    printf("Chargement Initial (9enreg) avec nbr d'enreg par bloc = 4");
     chargementInitial(&F,"Fichier.bin",9);
    printf("\n");
     Affichage(&F,"Fichier.bin");
    insertion_Ens(&F,"Fichier.bin");
    printf("Apres insertion d'un enregistrement avec mat=0000000 (inserion à la fin du fichier)");

    Affichage(&F,"Fichier.bin");

}
