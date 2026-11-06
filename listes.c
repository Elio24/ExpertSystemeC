#include "listes.h"

Liste creerListe() {
    return NULL;
}

int estVide(Liste l) {
    return l == NULL;
}

char* tete(Liste l) {
    if (estVide(l)) return NULL;
    return l->donnee;
}

Liste reste(Liste l) {
    if (estVide(l)) return NULL;
    return l->suivant;
}

Liste ajouterFin(Liste l, char* val) {
    Cellule* nouv = (Cellule*)malloc(sizeof(Cellule));
    if (!nouv) {
        perror("Erreur allocation mémoire (ajouterFin)");
        exit(EXIT_FAILURE);
    }
    
    // Duplication de la chaine pour garantir l'indépendance de la mémoire
    nouv->donnee = strdup(val);
    nouv->suivant = NULL;

    if (estVide(l)) return nouv;

    /* Parcours jusqu'au dernier élément */
    Cellule* cur = l;
    while (cur->suivant != NULL) {
        cur = cur->suivant;
    }
    cur->suivant = nouv;
    return l;
}

Liste supprimerElement(Liste l, char* val) {
    if (estVide(l)) return NULL;

    if (strcmp(l->donnee, val) == 0) {
        Liste suite = l->suivant;
        free(l->donnee); // Libération de la chaine
        free(l);         // Libération du maillon
        return suite;
    }

    // Appel récursif pour reconstruction du chainage
    l->suivant = supprimerElement(l->suivant, val);
    return l;
}

int appartient(Liste l, char* val) {
    if (estVide(l)) return 0;
    if (strcmp(l->donnee, val) == 0) return 1;
    return appartient(l->suivant, val);
}

void afficherListe(Liste l) {
    if (estVide(l)) {
        printf("(vide)\n");
        return;
    }
    while (!estVide(l)) {
        printf("[%s] -> ", l->donnee);
        l = l->suivant;
    }
    printf("NULL\n");
}

void libererListe(Liste l) {
    if (estVide(l)) return;
    libererListe(l->suivant);
    free(l->donnee);
    free(l);
}