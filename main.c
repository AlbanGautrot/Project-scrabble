#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>


void color (int t, int f){
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, f*16+t);
}


char CARDS_AVAILABLE[102] = {
        "AAAAAAAAABBCCDDDEEEEEEEEEEEEEEEFFGGHHIIIIIIIIJKLLLLLMMMNNNNNNOOOOOOPPQRRRRRRSSSSSSTTTTTTUUUUUUVVWXYZ**"};
char pioche[102];
typedef struct {
    char pseudo[1001];
    int score;
} Joueur;

int verifiermot(char mot[13], char dico[][10]) {

    do {
        printf("quel est votre mot : \n");
        scanf(" %s", mot);
        for (int i = 0; i < 5; i++) {
            if (strcmp(mot, dico[i]) == 0) {
                return 1;
            }
        }
    } while (strcmp(mot, dico) != 0);
    return 0;

}

Joueur infojoueur() {
    Joueur j;
    printf("quel est votre pseudo ? : \n");
    scanf(" %s", j.pseudo);
    return j;
}

afficherInfojoueur (Joueur j){
color(8, 0);

printf("Bienvenue %s. \n", j.pseudo);
color(15, 0);

}

typedef struct {
    int adresse;
    char caractere;
} Case;

Case plateau[15][15] = {};

void afficherLigneDuHaut() {
    char croix = 197;
    char ligne = 196;
    char tversdroite = 195;
    char tversbas = 194;
    char tversgauche = 180;
    char barreverticale = 179;
    char angleHautGauche = 218;
    char angleHautDroit = 191;

    for (int i = 0; i < 46; ++i) {
        if (i == 0) {
            printf("   %c", angleHautGauche);
        } else if (i == 45) {
            printf("%c", angleHautDroit);
        } else if (i % 3 == 0) {
            printf("%c", tversbas);
        } else {
            printf("%c%c", ligne, ligne);
        }

    }
}


void afficherLigneDuBas() {
    char croix = 197;
    char ligne = 196;
    char tversdroite = 195;
    char tversbas = 194;
    char tvershaut = 193;
    char tversgauche = 180;
    char barreverticale = 179;
    char angleHautGauche = 218;
    char angleHautDroit = 191;
    char angleBasGauche = 192;
    char angleBasDroite = 217;


    for (int i = 0; i < 46; ++i) {
        if (i == 0) {
            printf("   %c", angleBasGauche);
        } else if (i == 45) {
            printf("%c", angleBasDroite);
        } else if (i % 3 == 0) {
            printf("%c", tvershaut);
        } else {
            printf("%c%c", ligne, ligne);
        }

    }
}

void afficherIndicesColone() {
    color(12, 0);
    printf("     A    B    C    D    E    F    G    H    I    J    K    L    M    N    O\n");
    color(15,0);
}

void afficherLigne() {
    char croix = 197;
    char ligne = 196;
    char tversdroite = 195;
    char tversbas = 194;
    char tversgauche = 180;
    char barreverticale = 179;
    for (int i = 0; i < 46; ++i) {
        if (i == 0) {
            printf("   %c", tversdroite);
        } else if (i == 45) {
            printf("%c", tversgauche);
        } else if (i % 3 == 0) {
            printf("%c", croix);
        } else {
            printf("%c%c", ligne, ligne);
        }

    }
}


char affecteMultiple(int x, int y) {
    char multiple = ' ';
    //mot triple
    if ((x == 0 && (y == 0 || y == 7 || y == 14)) || (x == 7 && (y == 0 || y == 14)) ||
        (x == 14 && (y == 0 || y == 7 || y == 14))) {
        multiple = 245;
    }
    //mot double
    if ((x == 1 && (y == 1 || y == 13) || (x == 2 && (y == 2 || y == 12)) || (x == 3 && (y == 3 || y == 11)) ||
         (x == 4 && (y == 4 || y == 10))) ||
        (x == 13 && (y == 1 || y == 13) || (x == 12 && (y == 2 || y == 12)) || (x == 11 && (y == 3 || y == 11)) ||
         (x == 10 && (y == 4 || y == 10)))) {
        multiple = '@';
    }
    if ((x == 1 && (y == 5 || y == 9)) || (x == 5 && (y == 1 || y == 13 || y == 5 || y == 9)) ||
        (x == 13 && (y == 5 || y == 9)) || (x == 9 && (y == 1 || y == 13 || y == 5 || y == 9))) {
        multiple = '%';
    }
    if ((x == 0 && (y == 3 || y == 11)) || (x == 2 && (y == 6 || y == 8)) ||
        (x == 3 && (y == 0 || y == 7 || y == 14)) || (x == 6 && (y == 2 || y == 6 || y == 8 || y == 12)) ||
        (x == 7 && (y == 3 || y == 11)) || (x == 14 && (y == 3 || y == 11)) || (x == 12 && (y == 6 || y == 8)) ||
        (x == 11 && (y == 0 || y == 7 || y == 14)) || (x == 8 && (y == 2 || y == 6 || y == 8 || y == 12))) {
        multiple = '&';
    }
    if (x == 7 && y == 7) {
        multiple='#';
    }
    return multiple;
}

void affichagePlateau() {
    char croix = 197;
    char ligne = 196;
    char tversdroite = 195;
    char tversbas = 194;
    char tversgauche = 180;
    char barreverticale = 179;
    int numeroLigne = 0;
    char motTriple = 15;
    char multiple = ' ';


    afficherIndicesColone();
    afficherLigneDuHaut();
    color(12, 0);
    printf("\n %2.d", ++numeroLigne);
    color(15,0);
    printf("%c", barreverticale);


    for (int ligne = 0; ligne < 15; ++ligne) {

        for (int colone = 0; colone < 15; ++colone) {

            multiple = affecteMultiple(ligne, colone);


            if (colone == 0 && ligne != 0) {
                printf("\n");
                if (ligne < 14) {

                    afficherLigne();
                    color(12, 0);
                    printf("\n %2.d", ++numeroLigne);
                    color(15,0);
                    printf("%c", barreverticale);
                    printf(" %c%c %c", multiple, plateau[ligne][colone].caractere, barreverticale);
                }
                if (ligne == 14) {
                    afficherLigne();
                    color(12, 0);
                    printf("\n %2.d", ++numeroLigne);
                    color(15,0);
                    printf("%c", barreverticale);
                    printf(" %c%c %c", multiple, plateau[ligne][colone].caractere, barreverticale);
                }


            } else {
                printf(" %c%c %c", multiple, plateau[ligne][colone].caractere, barreverticale);
            }
            if (colone == 14 && ligne == 14) {
                printf("\n");

                afficherLigneDuBas();
            }

        }
    }
}

int scoreDeLaLettre(int pointDuJeton, int x, int y) {
    int scoreaditionel = 0;
    int pointLettre = 0;
    int multiple = 1;

    if ((x == 1 && (y == 5 || y == 9)) || (x == 5 && (y == 1 || y == 13 || y == 5 || y == 9)) ||
        (x == 13 && (y == 5 || y == 9)) || (x == 9 && (y == 1 || y == 13 || y == 5 || y == 9))) {
        multiple = 3;
    }
    if ((x == 0 && (y == 3 || y == 11)) || (x == 2 && (y == 6 || y == 8)) ||
        (x == 3 && (y == 0 || y == 7 || y == 14)) || (x == 6 && (y == 2 || y == 6 || y == 8 || y == 12)) ||
        (x == 7 && (y == 3 || y == 11)) || (x == 14 && (y == 3 || y == 11)) || (x == 12 && (y == 6 || y == 8)) ||
        (x == 11 && (y == 0 || y == 7 || y == 14)) || (x == 8 && (y == 2 || y == 6 || y == 8 || y == 12))) {
        multiple = 2;
    }


    if (pointDuJeton ==1){
        pointLettre = 1 * multiple;
        scoreaditionel = scoreaditionel + pointLettre;
    }
    if (pointDuJeton == 2) {
        pointLettre = 2 * multiple;
        scoreaditionel = scoreaditionel + pointLettre;
    }
    if (pointDuJeton == 3) {
        pointLettre = 3 * multiple;
        scoreaditionel = scoreaditionel + pointLettre;
    }
    if (pointDuJeton == 4) {
        pointLettre = 4 * multiple;
        scoreaditionel = scoreaditionel + pointLettre;
    }
    if (pointDuJeton == 8) {
        pointLettre = 8 * multiple;
        scoreaditionel = scoreaditionel + pointLettre;
    }
    if (pointDuJeton == 10) {
        pointLettre = 10 * multiple;
        scoreaditionel = scoreaditionel + pointLettre;
    }

    return scoreaditionel;
}

int multiplicateur(int y, char coor, char sens, int nbLettres) {
    int multiplicateur = 1;
    int x=coor- 'A';
    y=y-1;

    if (sens=='h') {
        do {
            if ((x == 0 && (y == 0 || y == 7 || y == 14)) || (x == 7 && (y == 0 || y == 14)) ||
                (x == 14 && (y == 0 || y == 7 || y == 14))) {
                multiplicateur += 3;
            }

            if ((x == 1 && (y == 1 || y == 13) || (x == 2 && (y == 2 || y == 12)) || (x == 3 && (y == 3 || y == 11)) ||
                 (x == 4 && (y == 4 || y == 10))) ||
                (x == 13 && (y == 1 || y == 13) || (x == 12 && (y == 2 || y == 12)) ||
                 (x == 11 && (y == 3 || y == 11)) ||
                 (x == 10 && (y == 4 || y == 10)))) {
                multiplicateur += 2;
            }
            --nbLettres;
            ++x;
        }while (nbLettres != 0);
    }
    if (sens=='v') {
        do {
            if ((x == 0 && (y == 0 || y == 7 || y == 14)) || (x == 7 && (y == 0 || y == 14)) ||
                (x == 14 && (y == 0 || y == 7 || y == 14))) {
                multiplicateur += 3;
            }

            if ((x == 1 && (y == 1 || y == 13) || (x == 2 && (y == 2 || y == 12)) || (x == 3 && (y == 3 || y == 11)) ||
                 (x == 4 && (y == 4 || y == 10))) ||
                (x == 13 && (y == 1 || y == 13) || (x == 12 && (y == 2 || y == 12)) ||
                 (x == 11 && (y == 3 || y == 11)) ||
                 (x == 10 && (y == 4 || y == 10)))) {
                multiplicateur += 2;
            }
            --nbLettres;
            ++y;
        }while (nbLettres != 0);
    }

    return multiplicateur;

}



int scoreLettre(char mot[8], char coor, int y, char sens) {
    int x=coor- 65;
    // y = y - 1;
    int somme = 0;
    int numlettre = 0;
    int i = 0;
    int points=0;
    int lettrespoint[27] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 10, 1, 2, 1, 1, 3, 8, 1, 1, 1, 1, 4, 10, 10, 10, 10, 0};

    do {

        numlettre = (mot[i] - 97);
        points=scoreDeLaLettre(lettrespoint[numlettre], x, y);

        somme = (points + somme);
        i++;



    } while (mot[i] != '\0');

    printf("\nsomme des jetons=  %d points\n", somme);
    sleep(2);

    return somme;
}




void fonctionPlacementMot(int nbLettres, char lettre1, char lettre2, char lettre3, char lettre4, char lettre5, char lettre6,
                          char lettre7, char coor, int chiffre, char sens, char mot[]) {
    int limite = 0;
    char lettre = 'A';
    int multiplicateur=0;
    chiffre = chiffre - 1;
    coor = coor - 'A';
    nbLettres = nbLettres - 1;
    limite = nbLettres;
    nbLettres = 1;
    if (sens == 'h') {
        plateau[chiffre][coor].caractere = lettre1;
        do {
            coor++;

            switch (nbLettres) {
                case 1:
                    lettre = lettre2;
                    break;
                case 2:
                    lettre = lettre3;
                    break;

                case 3:
                    lettre = lettre4;
                    break;
                case 4:
                    lettre = lettre5;
                    break;

                case 5:
                    lettre = lettre6;
                    break;

                case 6:
                    lettre = lettre7;
                    break;

                default:;


            }

            plateau[chiffre][coor].caractere = lettre;
            ++nbLettres;
            //scoreLettre( mot[8], chiffre, coor, sens);


        } while (nbLettres != limite);

    } else if (sens == 'v') {
        plateau[chiffre][coor].caractere = lettre1;
        do {
            chiffre++;


            switch (nbLettres) {
                case 1:
                    lettre = lettre2;
                    break;
                case 2:
                    lettre = lettre3;
                    break;

                case 3:
                    lettre = lettre4;
                    break;
                case 4:
                    lettre = lettre5;
                    break;

                case 5:
                    lettre = lettre6;
                    break;

                case 6:
                    lettre = lettre7;
                    break;

                default:;


            }

            plateau[chiffre][coor].caractere = lettre;
            ++nbLettres;
            //scoreLettre( mot[8], chiffre, coor, sens);



        } while (nbLettres != limite);
    }

}

void retirerlettre(int lettrearetirer) {
    strcpy(&pioche[lettrearetirer], &pioche[lettrearetirer + 1]);

}

void hand(int *taillepioche, char pioche[102], int nbjoueur, char derniermain[nbjoueur][102]) {

    int a = 0;
    printf("\n");
    printf("dernieres lettres du joueur %d :\n",nbjoueur);
    color(8,15);
    printf("|");
    for (int i = 0; i < 7; i++) {
        printf(" %c |", derniermain[nbjoueur][i]);
    }
    color(15,0);

    do{
        printf("\nCombien de lettre voulez vous tirer (entre 0 et 7) ? \n");
        scanf("%d", &a);
    } while (a<0 || a>7);

    printf("vous avez pioche les lettres suivantes : \n");
    color(8, 15);
    printf("| ");
    for (int i = 0; i < a; i++) {
        printf("%c | ", pioche[i]);

    }
    for (int i = 0; i < 7; i++) {
        derniermain[nbjoueur][i] = pioche[i];

    }
    for (int j = 0; j < a; j++) {
        retirerlettre(0);
    }
    color(15,0);
    printf("\n");
    *taillepioche = *taillepioche - a;
    printf("Lettres resantes dans la pioche : %d \n", *taillepioche);
}

int main() {
    char derniermain[5][102]={0};
    char dico [10][10] = {"salut", "bonjour"};
    int nbjoueur = 0;
    clock_t temps = 0;
    int i = 0;
    int compteTours=1;
    Joueur tableauDeJoueur[1001];
    srand(time(NULL));
    int taillepioche = 102;
    int piochetemporaire = 0;
    int max = 102;
    int lettreretire = 0;
    for (int i = 0; i < 102; i++) {
        lettreretire = rand() % 102;
        piochetemporaire = CARDS_AVAILABLE[lettreretire];
        CARDS_AVAILABLE[lettreretire] = CARDS_AVAILABLE[max - 1];
        CARDS_AVAILABLE[max - 1] = piochetemporaire;
        max--;
        pioche[i] = piochetemporaire;
    }
    int choixjoueurs = 0;
    char saisie[21];
    char motDePasse[21] = "ecelyon";
    do {
        printf("veuillez saisir le mot de passe : \n");
        scanf("%s", &saisie);
    } while (strcmp(motDePasse, saisie) != 0);

    do {
        system("clear");
        color(13, 8);
        printf("MENU DU JEU : \n");
        printf("Commencer une partie, tapez 1\nReprendre une partie sauvegardée, tapez 2\nAfficher l'aide, tapez 3\nAffichez le score des joueurs, tapez 4 \nQuiiter le jeu, tapez 0\n");
        color(13, 8);
        scanf("%d", &choixjoueurs);
        if (choixjoueurs == 1) {
            do{
                printf("combien y a t il de joueurs?:\n");
                scanf("%d", &nbjoueur);
            } while (nbjoueur!= 4 || nbjoueur!= 2 || nbjoueur!=3);

            for (i = 0; i < nbjoueur; i++) {
                tableauDeJoueur[i] = infojoueur();
            }
            for (i = 0; i < nbjoueur; i++) {
                afficherInfojoueur(tableauDeJoueur[i]);
            }
            int numerojoueur=0;
            for (int numeroDuJoueur = 0; numeroDuJoueur < nbjoueur; numeroDuJoueur++) {
                tableauDeJoueur[numeroDuJoueur].score=0;
            }
            do {
                for (int numeroDuJoueur = 0; numeroDuJoueur < nbjoueur; numeroDuJoueur++) {


                    printf(" %s, a vous de jouer !, pour l'instant votre score est de %d points \n", tableauDeJoueur[numeroDuJoueur].pseudo, tableauDeJoueur[numeroDuJoueur].score);
                    printf("\n");
                    sleep(3);

                    affichagePlateau();
                    printf("\nTour numero : %d", compteTours);
                    hand(&taillepioche, pioche, numerojoueur, derniermain);

                    char saisie[4];
                    char mot[101];
                    char coor = 0;
                    int chiffre = 0;
                    char lettre1 = ' ';
                    char lettre2 = ' ';
                    char lettre3 = ' ';
                    char lettre4 = ' ';
                    char lettre5 = ' ';
                    char lettre6 = ' ';
                    char lettre7 = ' ';
                    int nbLettres = 0;
                    char sens = ' ';


                    printf("\nvotre mot est-il horizontal? OUI ou NON\n");
                    scanf("%s", saisie);

                    if ((strcmp(saisie, "OUI") == 0) || (strcmp(saisie, "oui") == 0)) {

                        sens = 'h';


                    } else if ((strcmp(saisie, "NON") == 0) || (strcmp(saisie, "non") == 0)) {
                        sens = 'v';
                    }
                    printf("Entrer un mot\n");

                    int l=0;



                    char lettre;
                    lettre = getchar();


                    do {
                        switch (nbLettres) {
                            case 1:
                                lettre1 = lettre;
                                break;

                            case 2:
                                lettre2 = lettre;
                                break;
                            case 3:
                                lettre3 = lettre;
                                break;
                            case 4:
                                lettre4 = lettre;
                                break;
                            case 5:
                                lettre5 = lettre;
                                break;
                            case 6:
                                lettre6 = lettre;
                                break;
                            case 7:
                                lettre7 = lettre;
                                break;
                            default:;

                        }
                        if (sens=='v') {
                            printf("%c\n", lettre);
                        }
                        lettre = getchar();

                        mot[l]=lettre;
                        ++l;
                        ++nbLettres;
                    } while (lettre != '\n');


                    printf("quel est la colone de votre premiere lettre (en majuscule svp) ?\n");
                    scanf(" %c", &coor);
                    printf("quel est la ligne de votre premiere lettre ?\n");
                    scanf(" %d", &chiffre);
                    printf("votre premiere lettre est dans la case %c%d\n", coor, chiffre);

                    fonctionPlacementMot(nbLettres, lettre1, lettre2, lettre3, lettre4, lettre5, lettre6, lettre7, coor, chiffre, sens, mot);



                    int scoreDuMot=0;

                    scoreDuMot=(scoreLettre(mot, coor, chiffre, sens) * multiplicateur(chiffre, coor, sens, nbLettres));
                    color(14,0);
                    printf("\nLe mot vaut: %d points\n", scoreDuMot);
                    sleep(3);
                    tableauDeJoueur[numeroDuJoueur].score= tableauDeJoueur[numeroDuJoueur].score + scoreDuMot;


                    printf("\n %s votre score est de %d points\n", tableauDeJoueur[numeroDuJoueur].pseudo, tableauDeJoueur[i].score);
                    color(15, 0);



                    affichagePlateau();

                    printf("\n");
                    numerojoueur++;
                    temps = clock();
                    printf("Le temps de la partie est de %2.f secondes. \n", (double) temps/CLOCKS_PER_SEC);
                    sleep(3);
                    numeroDuJoueur=(numeroDuJoueur)%nbjoueur;

                }

                numerojoueur=numerojoueur%1;
                compteTours++;
                i=(i+1)%nbjoueur;
            } while (taillepioche > 1);
            if(tableauDeJoueur[0].score>tableauDeJoueur[1].score && tableauDeJoueur[2].score && tableauDeJoueur[3].score ||tableauDeJoueur[0].score>tableauDeJoueur[1].score && tableauDeJoueur[2].score ||tableauDeJoueur[0].score>tableauDeJoueur[1].score ){
                printf("Bravo %s, vous avez gagne avec %d points.", tableauDeJoueur[0].pseudo, tableauDeJoueur[0].score);
            }else if (tableauDeJoueur[1].score>tableauDeJoueur[0].score && tableauDeJoueur[2].score && tableauDeJoueur[3].score ||tableauDeJoueur[1].score>tableauDeJoueur[0].score && tableauDeJoueur[2].score ||tableauDeJoueur[1].score>tableauDeJoueur[0].score){
                printf("Bravo %s, vous avez gagne avec %d points.", tableauDeJoueur[1].pseudo, tableauDeJoueur[1].score);

            }else if(tableauDeJoueur[2].score>tableauDeJoueur[0].score && tableauDeJoueur[1].score && tableauDeJoueur[3].score ||tableauDeJoueur[2].score>tableauDeJoueur[0].score && tableauDeJoueur[1].score ||tableauDeJoueur[2].score>tableauDeJoueur[0].score){
                printf("Bravo %s, vous avez gagne avec %d points.", tableauDeJoueur[2].pseudo, tableauDeJoueur[2].score);

            }else if(tableauDeJoueur[3].score>tableauDeJoueur[0].score && tableauDeJoueur[1].score && tableauDeJoueur[2].score ||tableauDeJoueur[3].score>tableauDeJoueur[0].score && tableauDeJoueur[1].score ||tableauDeJoueur[0].score>tableauDeJoueur[0].score){
                printf("Bravo %s, vous avez gagne avec %d points.", tableauDeJoueur[3].pseudo, tableauDeJoueur[3].score);
            }

        } else if (choixjoueurs == 1) {

        } else if (choixjoueurs == 3) {
            printf("Le scrabble se joue a 2, 3, ou 4 joueurs.\nChaque joueur pioche 7 lettres aléatoirement en début de chaque partie et les place sur son chevalet.\n"
                   "Son but est ensuite de placer les lettres sur le plateau de jeu en essayant de cumuler le plus de points possibles.\n"
                   "Si le joueur pose toutes ses lettres,il fait un scrabble et il remporte 50 points. \n"
                   "La partie est finie une fois la pioche et le chevalet d'un joueur vide.\n");
            system("pause");
            choixjoueurs = -1;
        } else if (choixjoueurs == 0) {
            return 0;
        } else if (choixjoueurs == 4) {
        }
    } while (choixjoueurs != 0 && choixjoueurs != 1 && choixjoueurs != 2 && choixjoueurs != 3 && choixjoueurs != 4);
    return 0;
}