#ifndef LISTES_H
#define LISTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Structure générique de liste chainée pour chaines de caractères.
 */
typedef struct Cellule {
    char* donnee;
    struct Cellule* suivant;
} Cellule;

typedef Cellule* Liste;

/* --- Primitives de gestion de liste --- */

/* Initialise une liste vide */
Liste creerListe();

/* Vérifie si la liste est vide (NULL) */
int estVide(Liste l);

/* Retourne la donnée en tête de liste (sans suppression) */
char* tete(Liste l);

/* Retourne la queue de la liste (élément suivant) */
Liste reste(Liste l);

/* Ajoute une chaine en fin de liste. Alloue la mémoire nécessaire. */
Liste ajouterFin(Liste l, char* val);

/* Supprime la première occurrence d'une chaine et libère la mémoire associée. */
Liste supprimerElement(Liste l, char* val);

/* Teste la présence d'une chaine dans la liste (1 si présent, 0 sinon). */
int appartient(Liste l, char* val);

/* Affiche le contenu de la liste (pour debug). */
void afficherListe(Liste l);

/* Libère toute la mémoire allouée pour la liste. */
void libererListe(Liste l);

#endif