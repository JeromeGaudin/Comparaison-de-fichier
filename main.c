#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "algorithmeDeComparaison.h"
#include "lectureDeFichier.h"
#include "option.h"

#define ERRNO 1 /* si = 1 debug */

int main(int argc, char ** argv) {
  long nbLigneA, nbLigneB;
  optionC* option =  ajouter_option(argc, argv);
  char** fichierA = charger_fichier_en_memoire(argv[argc-2], &nbLigneA);
  puts("fichier 1 chargé");
  char** fichierB = charger_fichier_en_memoire(argv[argc-1], &nbLigneB);
  if(ERRNO) {
    int nbLigne = (nbLigneA >= nbLigneB)? nbLigneA: nbLigneB;
    int i;
    for(i=0; i<nbLigne; i++) {
      if(i < nbLigneA) {
        printf("%s\t\t", fichierA[i]);
      } else {
        printf("\t\t\t");
      }
      if(i < nbLigneB) {
        printf("%s\n", fichierB[i]);
      } else {
        putchar('\n');
      }
    }
    putchar('\n');
  }
  algo_comparaison_de_fichier(&fichierA, nbLigneA, &fichierB, nbLigneB);
}
