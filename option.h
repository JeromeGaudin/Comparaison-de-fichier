#ifndef OPTION_H
#define OPTION_H


#include <stdbool.h>

/*structure ou tout les option de la ligne de commande snt enregistrer*/
typedef struct{
  unsigned int optionLettre;
  unsigned int optionMot;
} option_t; /* option de la commande */

/*verifie les options et construit la structure option*/
void ajouter_option(int argc, char ** argv);

/* crée une structure option où sont enregistrer les options saisi dans la ligne de commande*/
void creer_struct_option();

/*supprime une structure option*/
void supprimer_struct_option();

/*ajoute une optionLettre dans la structure*/
bool ajouter_option_lettre(char lettreOption);

/*ajoute une optionMot dans la structure*/
bool ajouter_option_mot(char * motOption);

/*verifie si l'option est active ou non*/
int option_lettre_active(char lettreOption);

/*verifie si l'option est active ou non*/
int option_mot_actif(char* motOption);

#endif
