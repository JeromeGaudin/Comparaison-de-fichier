#ifndef LECTUREDEFICHIER_H
#define LECTUREDEFICHIER_H

#include "option.h"

/* ouvre un fichier et enregistre les lignes en mémoire avec malloc*/
char** charger_fichier_en_memoire(char* nomFichier, long* nbLigne);

/* nb d'occurence dans un fichier */
long occurence_fichier(FILE* f, char occurence);

/* retourne un long qui correspond a la position de la lettre par rapport a la position du curseur avant la fonction( ne bouge pas le curseur)*/
long chercher_lettre_dans_fichier(FILE* f, char lettre);

/* gère l'option e et t si on lui passe le string a traiter */
void gere_option_e_et_t(char ** string);

/* enlève les caractères à exclure avant et après le string*/
void super_trim(char ** string, char* exclure, int tailleExclure);

#endif
