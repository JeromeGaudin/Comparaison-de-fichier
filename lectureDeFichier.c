#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lectureDeFichier.h"
#include "option.h"

#define ERRNO 0  /* si = 1 debug */

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
    if(premierTour != 1) fseek(f, 1L, SEEK_CUR); /* pour pas que la fonction chercher_lettre_dans_fichier ne retourne le \n sur lequel il est*/
    tailleChaine = (int) chercher_lettre_dans_fichier(f, '\n');
    if(ERRNO) printf("tailleLigne = %d\n", tailleChaine);
    tailleChaine =tailleChaine+1;/* +1 car on va mettre \0 */
    char* ligneBrut = malloc(tailleChaine*sizeof(char));
    fgets(ligneBrut, tailleChaine, f);
    gere_option_e_et_t(&ligneBrut);
    if(option_lettre_active('e') || option_lettre_active('t')) {
      tailleChaine =strlen(ligneBrut)+1;/* +1 car on va mettre \0 */
    }
    ligneBrut[tailleChaine-1] = '\0';
    if(ERRNO) printf("Ligne %d brut (taille=%d): %s\n", i, tailleChaine, ligneBrut);
    tailleChaine = strlen(ligneBrut);
    if(ERRNO) printf("Ligne après les options (taille=%d): %s \n", tailleChaine, ligneBrut);
    fichierMemoire[i] = (char*) malloc(tailleChaine*sizeof(char));
    if(fichierMemoire[i] == NULL) {
      fprintf(stderr, "Erreur l'allocation de mémoire n'a pas pus être effectuée\n");
      exit(1);
    }

    memmove(fichierMemoire[i], ligneBrut, tailleChaine);
    free(ligneBrut);
    premierTour=0;
  }
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
  while( feof(f) == 0 && ferror(f) == 0 && flagTrouver == 0) {
    c = getc(f);
    if(c == lettre) {
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

void gere_option_e_et_t(char ** string) {
  char* aExclure;
  bool eActif=0, tActif=0;
  if(option_lettre_active('e')) {
    eActif=1;
  }
  if(option_lettre_active('t')) {
    tActif=1;
  }
  if(eActif && tActif) {
    aExclure = (char*) malloc(2*sizeof(char));
    aExclure[0] = ' ';
    aExclure[1] = '\t';
    super_trim(string, aExclure, 2);
    free(aExclure);
  } else if(eActif || tActif) {
    aExclure = (char*) malloc(sizeof(char));
    if(eActif) {
      aExclure[0] = ' ';
    } else {
      aExclure[0] = '\t';
    }
    super_trim(string, aExclure, 1);
    free(aExclure);
  }
}

void super_trim(char ** string, char* exclure, int tailleExclure) {
  int i, j, i2, j2;
  char * s = *string;
  int taille=strlen(s);
  int enlever=0;
  for(i=0; i != taille; i++) {
    for(i2=0; i2<tailleExclure && !enlever; i2++) { /* on verifie pour tous les caractères exclue*/
      if(s[i] == exclure[i2]) { 
        enlever = 1;
      }
    }
    if( !enlever) {
      break;  /* aucun caractère enlever donc on s'arrête*/
    }
    enlever=0;
  }
  if(taille == i){ /*string contient que des caractères a enlever*/
    string=NULL;
    return;
  }
  for(j=taille-1; j > 0; j--) {
    for(j2=0; j2<tailleExclure && !enlever; j2++) { /* on verifie pour tous les caractères exclue*/
      if(s[j] == exclure[j2]) {
        enlever = 1;
      }
    }
    if( !enlever) {
      break;  /* aucun caractère enlever donc on s'arrête*/
    }
    enlever=0;
  }
  int tailleAGarder = j-i+1; /* car j est décrémenté avant d'être testé, pose pas de problème pour i car il commence a 0*/
  char* n = (char*) malloc(tailleAGarder*sizeof(char));
  strncpy(n, &s[i], tailleAGarder);
  *string = n;
}