#include "expert.h"

/* -------------------------------------------------------------------------
   Implémentation du TA Regle
   ------------------------------------------------------------------------- */

Regle creerRegle() {
    return creerListe();
}

Regle ajouterPremisse(Regle r, char* prop) {
    /* Ajout séquentiel : la conclusion devra être ajoutée en dernier */
    return ajouterFin(r, prop);
}

Regle ajouterConclusion(Regle r, char* conc) {
    return ajouterFin(r, conc);
}

int appartientPremisse(Regle r, char* prop) {
    /* Cas d'arrêt : liste vide ou liste contenant un seul élément (la conclusion) */
    if (estVide(r) || estVide(reste(r))) return 0;
    
    if (strcmp(tete(r), prop) == 0) return 1;
    
    /* Appel récursif (Exigence explicite du sujet) */
    return appartientPremisse(reste(r), prop);
}

Regle supprimerPropPremisse(Regle r, char* prop) {
    /* Protection : on ne supprime jamais le dernier élément (conclusion) */
    if (estVide(r) || estVide(reste(r))) return r;
    
    /* Si l'élément courant est celui recherché */
    if (strcmp(tete(r), prop) == 0) {
        Regle suite = reste(r);
        /* Note: free(r->donnee) et free(r) gérés implicitement si on utilisait
           supprimerElement, mais ici on manipule la structure Regle */
        free(r->donnee);
        free(r);
        return suite;
    }
    
    /* Reconstruction du chainage */
    r->suivant = supprimerPropPremisse(reste(r), prop);
    return r;
}

int estPremisseVide(Regle r) {
    /* La prémisse est vide si la liste ne contient QUE la conclusion (taille = 1) */
    if (estVide(r)) return 1;        // Liste vide (anormal mais géré)
    if (estVide(reste(r))) return 1; // Un seul élément => c'est la conclusion
    return 0;
}

char* tetePremisse(Regle r) {
    /* Précondition : la prémisse n'est pas vide */
    return tete(r);
}

char* accederConclusion(Regle r) {
    if (estVide(r)) return NULL;
    
    /* La conclusion est le dernier élément de la liste */
    if (estVide(reste(r))) return tete(r);
    
    return accederConclusion(reste(r));
}

/* -------------------------------------------------------------------------
   Implémentation du TA BC (Base de Connaissances)
   ------------------------------------------------------------------------- */

BC creerBC() {
    return NULL;
}

BC ajouterRegle(BC base, Regle r) {
    CelluleRegle* nouv = (CelluleRegle*)malloc(sizeof(CelluleRegle));
    if (!nouv) exit(EXIT_FAILURE);

    nouv->regle = r;
    nouv->suivant = NULL;

    if (base == NULL) return nouv;

    /* Ajout en queue */
    CelluleRegle* cur = base;
    while (cur->suivant != NULL) {
        cur = cur->suivant;
    }
    cur->suivant = nouv;
    return base;
}

Regle teteRegle(BC base) {
    if (base) return base->regle;
    return NULL;
}

BC resteRegle(BC base) {
    if (base) return base->suivant;
    return NULL;
}

int estBCVide(BC base) {
    return base == NULL;
}

/* -------------------------------------------------------------------------
   Moteur d'inférence (Chainage avant / Saturation)
   ------------------------------------------------------------------------- */

Liste moteurInference(BC baseC, Liste baseFaits) {
    int faitDeduit = 1; /* Booléen : y a-t-il eu un changement ce tour ? */
    
    printf("\n>>> Lancement du moteur d'inference <<<\n");

    /* Boucle principale : tant qu'on apprend de nouveaux faits */
    while (faitDeduit) {
        faitDeduit = 0;
        BC curBC = baseC;

        /* Parcours de toutes les règles de la base */
        while (!estBCVide(curBC)) {
            Regle r = teteRegle(curBC);
            
            /* Pour la règle courante, on vérifie chaque fait de notre base de faits */
            Liste curFait = baseFaits;
            while (!estVide(curFait)) {
                char* f = tete(curFait);
                
                /* Si le fait appartient à la prémisse, on le retire de la règle */
                if (appartientPremisse(r, f)) {
                    /* On modifie la règle en mémoire via l'opération abstraite */
                    /* Note : curBC->regle est mis à jour car la tête de liste peut changer */
                    curBC->regle = supprimerPropPremisse(r, f);
                    r = curBC->regle; 
                }
                curFait = reste(curFait);
            }

            /* Si la prémisse est devenue vide, la règle se déclenche */
            if (estPremisseVide(r)) {
                char* conclusion = accederConclusion(r);
                
                /* Si la conclusion est nouvelle, on l'ajoute aux faits */
                if (!appartient(baseFaits, conclusion)) {
                    printf("   [+] Regle declenchee -> Nouveau fait : %s\n", conclusion);
                    baseFaits = ajouterFin(baseFaits, conclusion);
                    faitDeduit = 1; /* On force un nouveau tour de boucle */
                }
            }
            /* Passage à la règle suivante */
            curBC = resteRegle(curBC);
        }
    }
    
    printf(">>> Saturation terminee. Aucun nouveau fait deduit. <<<\n");
    return baseFaits;
}