#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lectureDeFichier.h"
#include "option.h"

#define ERRNO 1 /* si = 1 debug */

char** charger_fichier_en_memoire(char* nomFichier, long* nbLignes) {
  FILE* f = fopen(nomFichier, "r");
  int i, premierTour=1;
  char** fichierMemoire;

  if(f == NULL) {
    fprintf(stderr, "Erreur le fichier n'éxiste pas ou les droits de lecture ne sont pas sur ce fichier\n");
    exit(1);
  }
  *nbLignes = occurence_fichier(f, '\n');
  if(ERRNO) printf("calacule du nombre de lignes : %d\n", *nbLignes);
  fichierMemoire = (char**) malloc((*nbLignes)*sizeof(char*));
  if(fichierMemoire == NULL) {
    fprintf(stderr, "Erreur l'allocation de mémoire n'a pas pus être effectuée\n");
    exit(1);
  }
  fseek(f, 0L, SEEK_SET); /* car la fonction occurence_fichier ne revient pas au début*/

  for(i=0; i<*nbLignes; i++) {
    int tailleChaine = 0;
    printf("T_1_%d\n", ftell(f));
    if(premierTour != 1) fseek(f, 1L, SEEK_CUR); /* pour pas que la fonction chercher_lettre_dans_fichier ne retourne le \n sur lequel il est*/
    printf("T_2\n");
    tailleChaine = (int) chercher_lettre_dans_fichier(f, '\n');
    if(ERRNO) printf("tailleLigne = %d\n", tailleChaine);
    tailleChaine =tailleChaine+1;/* +1 car on va mettre \0 */
    printf("%d\n", tailleChaine);
    char* ligneBrut = malloc(1+tailleChaine*sizeof(char));
    printf("décaration variables\n");
    fgets(ligneBrut, tailleChaine, f);
    printf("bon\n");
    ligneBrut[tailleChaine-1] = '\0';
    if(ERRNO) printf("Ligne %d brut (taille=%d): %s\n", i, tailleChaine, ligneBrut);
    tailleChaine = strlen(ligneBrut);
    if(ERRNO) printf("Ligne après les options (taille=%d): %s \n", tailleChaine, ligneBrut);
    /*tailleChaine = tailleChaine +1;  +1 car il faut la place pour le \0*/
    fichierMemoire[i] = (char*) malloc(tailleChaine*sizeof(char));
    if(fichierMemoire[i] == NULL) {
      fprintf(stderr, "Erreur l'allocation de mémoire n'a pas pus être effectuée\n");
      exit(1);
    }

    memmove(fichierMemoire[i], ligneBrut, tailleChaine);
    free(ligneBrut);
    printf("%s \n", fichierMemoire[i]);
    premierTour=0;
    printf("i=%d < %d\n", i, *nbLignes);
  }
  puts("fin boucle");
  fclose(f);
  return fichierMemoire;
}

/* nb d'occurence dans un fichier */
long occurence_fichier(FILE* f, char occurence) {
  long compteur=0;
  fseek(f, 0L, SEEK_SET);
  while(feof(f) == 0) {
    if(getc(f) == occurence) compteur++;
    if(ferror(f) == 1) {
      fprintf(stderr,"Erreur lors de la lecture du fichier dans la fonction \"occurence_fichier\"\n");
      exit(1);
    }
  }
  return compteur;
}

/* retourne un long qui correspond a la positon de la lettre relative par rapport a la position du curseur avant la fonction( ne bouge pas le curseur)*/
long chercher_lettre_dans_fichier(FILE* f, char lettre) {
  long savePosition = ftell(f);
  long ret = -1;
  int flagTrouver = 0;
  char c;
  puts("b.1");
  while( feof(f) == 0 && ferror(f) == 0 && flagTrouver == 0) {
    c = getc(f);
    puts("b.2");
    if(c == lettre) {
      puts("b.3");
      flagTrouver = 1;
      ret = ftell(f) - savePosition -1; /*-1 car on a dépacé la lettre d'un cran*/
      fseek(f, savePosition, SEEK_SET);
    }
  }
  if(ferror(f) != 0) {
    fprintf(stderr, "Erreur de lecture dans un fichier");
  }
  return ret;
}

/* me semble faux */
/*char* option_e(char ligneLu[], int* tailleRetourne) {
  int i, j, tailleChaine=strlen(ligneLu);
  bool espace = true;
  for(i=0; i<tailleChaine && espace; i++) {
    if(ligneLu[i] == ' ')
      espace = false;
  }
  espace = true;
  if(i < tailleChaine) {
    char* ligneFinal = NULL;
    for(j=tailleChaine-2; j>0 && espace; j++) {*/ /* -2 pour pas prendre le \0 */
      /*if(ligneLu[j] == ' ')
        espace = false;
    }
    *tailleRetourne = strlen(ligneLu);
    ligneLu = &ligneLu[i];
    strncpy(ligneLu, ligneFinal, j+1);*/ /* car avant on a fais -2 */
    /**tailleRetourne = *tailleRetourne - (i+j);
    return ligneFinal;
  } else {
    return NULL;
  }
}*/
