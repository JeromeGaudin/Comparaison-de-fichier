#include <stdio.h>
#include <string.h>

#include "algorithmeDeComparaison.h"
#include "option.h"

#define ERRNO 0 /* si = 1 debug */

option_t* option; /* permet d'optenir la variable golbal du main*/

void ligne_inchange(char** tableau, int ligneDebut/*, int ligneFin*/) {
	char symbole = '.';
	if(option_mot_actif("no-symbol")) {
		symbole = 0;
	}
  printf("%c%s\n", symbole, tableau[ligneDebut]);
}

void ligne_suppression(char** tableau,int ligneDebut, int ligneFin) {
	char symbole = '-';
	if(option_mot_actif("no-symbol")) {
		symbole = 0;
	}
	do {
	  printf("\33[38;5;196m%c%s\33[39m\n", symbole, tableau[ligneDebut]);
	  ligneDebut++;
	}while(ligneDebut < ligneFin);
}

void ligne_ajout(char** tableau,int ligneDebut, int ligneFin) {
	char symbole = '+';
	if(option_mot_actif("no-symbol")) {
		symbole = 0;
	}
  do {
    printf("\33[38;5;82m%c%s\33[39m\n", symbole, tableau[ligneDebut]);
    ligneDebut++;
  }while(ligneDebut < ligneFin);
}

void algo_comparaison_de_fichier(char ** fichierA[], int tailleA, char ** fichierB[], int tailleB) {
  int CA = 0; /*ligneCouranteA*/
  int CB = 0; /*ligneCouranteB*/
  int SA = 0; /*SauvegardeLigneA*/
  int fin=0; /*boolean pour indiquer la fin*/

  while(CA < tailleA && CB < tailleB) {
    SA=CA;
    if(ERRNO) fprintf(stderr,"0) %d %d\n", CA, CB);
    if(CA == tailleA) {
      if(ERRNO) fprintf(stderr,"fichierA vide\n");
      ligne_suppression(*fichierB, CB, tailleB);
      CB=tailleB;
    } else if(CB == tailleB) {
      if(ERRNO) fprintf(stderr,"fichierB vide\n");
      ligne_ajout(*fichierA, CA, tailleA);
      CA=tailleA;
    } else {
      if(ERRNO) fprintf(stderr,"1) %d %d  %d\n",CA,CB,strcmp((*fichierA)[CA],(*fichierB)[CB]));
      if(strcmp((*fichierA)[CA], (*fichierB)[CB]) == 0) {
        ligne_inchange(*fichierA, CA);
        CA++;
        CB++;
      } else {
        fin=0;
        while(fin==0 && CA < tailleA) {
          if(ERRNO) fprintf(stderr,"2) %d %d  %d\n",CA,CB,strcmp((*fichierA)[CA],(*fichierB)[CB]));
          if(strcmp((*fichierA)[CA], (*fichierB)[CB]) == 0) {
            ligne_ajout(*fichierA, SA, CA);
            ligne_inchange(*fichierA, CA);
            CA++;
            CB++;
            fin=1;
          } else {
            CA++;
          }
        }

        if(fin == 0) {
          if(ERRNO) fprintf(stderr,"3) %d %d 3ème if\n", CA, CB);
          ligne_suppression(*fichierB, CB, CB);
          CB++;
          CA=SA;
        }
      }
    }
  }
}
