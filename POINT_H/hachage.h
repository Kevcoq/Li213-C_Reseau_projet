#ifndef __hach__
#define __hach__
#include "noeud.h"
#include "reseau.h"
#include "liste.h"

// Table de hachage
// tbl : un tableau de pointeur vers des liste de noeuds
// taille : la taille
typedef struct _hachage {
  //Tableau où on va stocker tout ça 
  CelluleLNoeud **tbl;
  size_t taille;
  //Tailel du reseau
} Hachage;


// Voir le .c pour plus d'info
void affiche_tbl_hach(Hachage *H);
int fct_hach(double x, double y);
Hachage *creer_hachage(size_t nbCase);
Hachage *recree_hachage(Reseau *R);
void recree_reseau_hachage(ListeChaine *L, Reseau *R, Hachage **H);

#endif
