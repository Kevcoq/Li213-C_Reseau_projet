#ifndef __NOEUD__
#define __NOEUD__

#include "reseau.h"
#include "liste.h"

// Voir le .c pour plus d'info
int compare(double x1, double y1, double x2, double y2);
int compareN(Noeud *n1, Noeud *n2);
void affiche_noeud(Noeud *n);
Voisin *creer_voisin(int v);
void ajouter_voisin(Voisin *vois,Noeud *n);
Noeud *creer_noeud(int x);
Noeud *recherche_cree_noeud(Reseau *R, double x, double y);
void recree_reseau(ListeChaine *L, Reseau *R) ;

#endif
