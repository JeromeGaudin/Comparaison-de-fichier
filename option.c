#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "algorithmeDeComparaison.h"
#include "lectureDeFichier.h"
#include "option.h"

/* différentes options */
const int optionLettreTaille = 2;
const char optionLettre[2] = {'e','t'};
const int optionMotTaille = 1;
const char* optionMot[1] = {"no-symbol"/*"help","recent"*/};

option_t* option; /* permet d'optenir la variable golbal du main*/

void ajouter_option(int argc, char ** argv) {
  if(argc < 3) {
    fprintf(stderr, "Il faut au moins 2 arguments : deux fichiers\n");
    option = NULL;
  } else {
    if(argc > 3) { /* options */
      creer_struct_option();
      int nbOption = argc-2; /* -2 car il on doit mettre deux ficheir sur la ligne de commande */
      int i;
      for(i=1; i<nbOption; i++) {
        if(argv[i][0] == '-' && argv[i][1] == '-') { /* option en mot */
          if( !ajouter_option_mot(&argv[i][2])) {
            fprintf(stderr, "Erreur l'option %s n'est pas valide\n", argv[i]);
            exit(1);
          }
        } else if(argv[i][0] == '-') { /* option à une lettre */
          int j;
          for(j=1; j<strlen(argv[i]);j++) {
            if( !ajouter_option_lettre(argv[i][j])) {
              fprintf(stderr, "Erreur l'option -%c n'est pas valide\n", argv[i][j]);
              exit(1);
            }
          }
        }
      }
    }
  }
}

void creer_struct_option() {
  option_t* r = NULL;
  r = (option_t*) malloc(sizeof(option_t));
  if(r == NULL) {
    fprintf(stderr,"L'allocation de mémoire dans la fonction creer_struct_option a échoué");
    exit(1);
  }
  r->optionLettre = 0;
  r->optionMot = 0;
  option = r;
}

void supprimer_struct_option() {
  free(option);
}

bool ajouter_option_lettre(char lettreOption) {
  int i;
  bool trouve = false;
  for(i=0; i<optionLettreTaille && !trouve; i++) {
    if(optionLettre[i] == lettreOption)
      trouve = true;
  }
  i--; /* car for incrémente i avant de tester la condition */
  if( !trouve) {
    return false; /* la lettre nes't pas dans les options*/
  } else {
    int flag = 0x1;
    flag = flag << i;
    option->optionLettre = option->optionLettre | flag;
    return true; /* bien passé*/
  }
}

bool ajouter_option_mot(char* motOption) {
  int i;
  bool trouve = false;
  for(i=0; i<optionMotTaille && !trouve; i++) {
    if(strcmp(optionMot[i], motOption)==0) {
      trouve = true;
    }
  }
  i--; /* car for incrémente i avant de tester la condition*/
  if( !trouve) {
    return false;  /*la lettre n'est pas dans les options*/
  } else {
    int flag = 0x1;
    flag = flag << i;
    option->optionMot = option->optionMot | flag;
    return true;
  }
}

int option_lettre_active(char lettreOption) {
  if(option != NULL) {
    int i;
    for(i=0; i<optionLettreTaille; i++)  {
      if(lettreOption == optionLettre[i]) {
        int optionMot = option->optionLettre;
        return (optionMot & (1 << i)) >> i;
      }
    }
    return -1; /* l'option n'est pas dans la liste d'option (problème de programmation) */
  }
  return 0; /* erreur option_t n'exixste pas*/
}

int option_mot_actif(char* motOption) {
  if(option != NULL) {
    int i;
    for(i=0; i<optionMotTaille; i++)  {
      if(strcmp(motOption, optionMot[i])==0) {
        int optionMot = option->optionMot;
        return (optionMot & (1 << i)) >> i;
      }
    }
    return -1; /* l'option n'est pas dans la liste d'option (problème de programmation) */
  }
  return 0; /* erreur option_t n'exixste pas*/
}
