#include "expert.h"
#include "listes.h"
#include <string.h>

/* --- Prototypes des fonctions de test --- */
void test_diagnostic_auto();
void test_classification_animale();

int main(int argc, char *argv[]) {
    printf("=== PROJET LO21 : SYSTEME EXPERT ===\n");

    int mode = 0; // 0 = Tout, 1 = Auto, 2 = Animaux

    /* Gestion des arguments en ligne de commande */
    if (argc > 1) {
        if (strcmp(argv[1], "1") == 0) {
            mode = 1;
        } else if (strcmp(argv[1], "2") == 0) {
            mode = 2;
        }
    }

    if (mode == 0 || mode == 1) {
        test_diagnostic_auto();
    }

    if (mode == 0 || mode == 2) {
        test_classification_animale();
    }

    return 0;
}

/* ==========================================================
   JEU D'ESSAI 1 : DIAGNOSTIC PANNE (Exemple Sujet)
   ========================================================== */
void test_diagnostic_auto() {
    printf("\n\n[JEU D'ESSAI 1] : DIAGNOSTIC AUTOMOBILE\n");
    printf("---------------------------------------\n");

    BC baseAuto = creerBC();

    /* R1 : reservoirVide ET pharesFonctionnent ET moteurDemarre => problemeBougie */
    Regle r1 = creerRegle();
    r1 = ajouterPremisse(r1, "reservoirVide");
    r1 = ajouterPremisse(r1, "pharesFonctionnent");
    r1 = ajouterPremisse(r1, "moteurDemarre");
    r1 = ajouterConclusion(r1, "problemeBougie");
    baseAuto = ajouterRegle(baseAuto, r1);

    /* R2 : moteurDemarre ET pharesFonctionnent => problemeBatterie */
    Regle r2 = creerRegle();
    r2 = ajouterPremisse(r2, "moteurDemarre");
    r2 = ajouterPremisse(r2, "pharesFonctionnent");
    r2 = ajouterConclusion(r2, "problemeBatterie");
    baseAuto = ajouterRegle(baseAuto, r2);

    /* R3 : NONmoteurDemarre ET pharesFonctionnent => problemeStarter */
    Regle r3 = creerRegle();
    r3 = ajouterPremisse(r3, "NONmoteurDemarre");
    r3 = ajouterPremisse(r3, "pharesFonctionnent");
    r3 = ajouterConclusion(r3, "problemeStarter");
    baseAuto = ajouterRegle(baseAuto, r3);

    /* Faits Initiaux */
    Liste faitsAuto = creerListe();
    faitsAuto = ajouterFin(faitsAuto, "NONmoteurDemarre");
    faitsAuto = ajouterFin(faitsAuto, "pharesFonctionnent");

    printf("Base de faits initiale : ");
    afficherListe(faitsAuto);

    /* Moteur */
    faitsAuto = moteurInference(baseAuto, faitsAuto);

    printf("Resultat Final J1 : ");
    afficherListe(faitsAuto);
    
    // Nettoyage partiel
    libererListe(faitsAuto);
    // Note: baseAuto n'est pas libérée ici (simplification projet étudiant)
}

/* ==========================================================
   JEU D'ESSAI 2 : CLASSIFICATION ANIMALE (Chaînage)
   Objectif : Prouver que R1 déclenche R2 (A -> B -> C)
   ========================================================== */
void test_classification_animale() {
    printf("\n\n[JEU D'ESSAI 2] : CLASSIFICATION ANIMALE\n");
    printf("----------------------------------------\n");

    BC baseAnimaux = creerBC();

    /* Règle A1 : aDesPoils ET mangeViande => estCarnivore */
    Regle ra1 = creerRegle();
    ra1 = ajouterPremisse(ra1, "aDesPoils");
    ra1 = ajouterPremisse(ra1, "mangeViande");
    ra1 = ajouterConclusion(ra1, "estCarnivore");
    baseAnimaux = ajouterRegle(baseAnimaux, ra1);

    /* Règle A2 : estCarnivore ET aDesRayures => estTigre */
    Regle ra2 = creerRegle();
    ra2 = ajouterPremisse(ra2, "estCarnivore");
    ra2 = ajouterPremisse(ra2, "aDesRayures");
    ra2 = ajouterConclusion(ra2, "estTigre");
    baseAnimaux = ajouterRegle(baseAnimaux, ra2);

    /* Faits Initiaux */
    Liste faitsAnimaux = creerListe();
    faitsAnimaux = ajouterFin(faitsAnimaux, "aDesPoils");
    faitsAnimaux = ajouterFin(faitsAnimaux, "mangeViande");
    faitsAnimaux = ajouterFin(faitsAnimaux, "aDesRayures");

    printf("Base de faits initiale : ");
    afficherListe(faitsAnimaux);

    /* Moteur */
    faitsAnimaux = moteurInference(baseAnimaux, faitsAnimaux);

    printf("Resultat Final J2 : ");
    afficherListe(faitsAnimaux);
    
    /* Nettoyage final */
    libererListe(faitsAnimaux);
}