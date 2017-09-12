#ifndef ALGORITHMEDECOMPARAISON_H
#define ALGORITHMEDECOMPARAISON_H

/* lignes qui sont inchanger entre les deux fichiers */
void ligne_inchange( char** tableau, int ligneDebut);

/* ligne supprimer dans le fichierA */
void ligne_suppression( char** tableau,int ligneDebut, int ligneFin);

/* ligne ajouter dans le fichierA */
void ligne_ajout( char** tableau,int ligneDebut, int ligneFin);

/* agorithme pour déterminer les lignes ajoutés supprimé ou inchanger*/
void algo_comparaison_de_fichier( char ** fichierA[], int tailleA, char ** fichierB[], int tailleB);
#endif
