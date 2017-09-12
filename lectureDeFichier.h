#ifndef LECTUREDEFICHIER_H
#define LECTUREDEFICHIER_H

#include "option.h"

/* ouvre un fichier et enregistre les lignes en mémoire avec malloc*/
char** charger_fichier_en_memoire(char* nomFichier, long* nbLigne);

/* nb d'occurence dans un fichier */
long occurence_fichier(FILE* f, char occurence);

/* retourne un long qui correspond a la position de la lettre par rapport a la position du curseur avant la fonction( ne bouge pas le curseur)*/
long chercher_lettre_dans_fichier(FILE* f, char lettre);

/* gère l'option e (espace)*/
/* l'option e n'applique a une ligne avant de l'eenregistrer dans la mémoir */
char* option_e(char ligneLu[], int* tailleRetourne);

#endif
