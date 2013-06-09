#ifndef __ABR__
#define __ABR__

#include "reseau.h"

// Structure d'un arbre
// h : sa hauteur
// n : un pointeur vers un noeud
// g et d : ses fils respectivement gauche et droit
typedef struct _abr {
  int h;
  Noeud *n;
  struct _abr *g, *d;
} ABRe;
 

// Voir le .c pour plus d'info
ABRe *creer_abr(Noeud *n);
int hauteur(ABRe *abr);
void affiche(ABRe *abr);
void aff(ABRe *abr, int h);
ABRe *recree_abr(Reseau *R);
void recree_reseau_ABRE(ListeChaine *L, Reseau *R, ABRe **abr);
#endif
