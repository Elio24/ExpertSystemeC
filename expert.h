#ifndef EXPERT_H
#define EXPERT_H

#include "listes.h"

/* =========================================================================
 * PARTIE 1 : Type Abstrait Regle
 * Une Règle est une liste de propositions.
 * Convention: [P1, P2, ..., Pn, C] où Pi sont les prémisses et C la conclusion.
 * ========================================================================= */
typedef Liste Regle;

Regle creerRegle();
Regle ajouterPremisse(Regle r, char* prop);
Regle ajouterConclusion(Regle r, char* conc);

/* Teste l'appartenance à la prémisse de manière récursive (Exigence Q1) */
int appartientPremisse(Regle r, char* prop);

/* Supprime une proposition de la prémisse sans toucher à la conclusion */
Regle supprimerPropPremisse(Regle r, char* prop);

/* Vérifie si la prémisse est vide (ne reste que la conclusion) */
int estPremisseVide(Regle r);

char* tetePremisse(Regle r);
char* accederConclusion(Regle r);


/* =========================================================================
 * PARTIE 2 : Type Abstrait BC (Base de Connaissances)
 * Une BC est une liste de Règles.
 * ========================================================================= */
typedef struct CelluleRegle {
    Regle regle;
    struct CelluleRegle* suivant;
} CelluleRegle;

typedef CelluleRegle* BC;

BC creerBC();
BC ajouterRegle(BC base, Regle r);

/* Accesseurs pour le parcours de la BC */
Regle teteRegle(BC base);
BC resteRegle(BC base);
int estBCVide(BC base);


/* =========================================================================
 * PARTIE 3 : Moteur d'inférence
 * Sature la base de faits à partir de la BC.
 * ========================================================================= */
Liste moteurInference(BC base, Liste baseFaits);

#endif