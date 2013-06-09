#ifndef __RESEAU_H__
#define __RESEAU_H__
#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/* Element de la liste des noeuds voisins d’un noeud du reseau */
typedef struct voisin {
  /* Numero du voisin dans le Reseau*/
  int v ;
  /* Pointeur sur le voisin suivant */
  struct voisin * voisSuiv ;
} Voisin ;


/* Noeud du reseau */
typedef struct noeud {
  /* Numero du noeud dans le Reseau */
  int u ;
  double x , y ; /* Coordonnees du noeud */
  Voisin * LVoisins ; /* Liste des noeuds voisins de u*/
} Noeud ;


/* Element de la liste chainee des noeuds du reseau */
typedef struct celluleLNoeud {
  Noeud * ptrnoeud ; /* Pointeur sur un noeud du reseau */
  struct celluleLNoeud * noeudSuiv ; /* Noeud suivant dans la liste des noeuds */
} CelluleLNoeud ;


/* Element de la liste chainee des commodites du reseau */
typedef struct celluleLCommodite {
  int extr1 , extr2 ;
  struct celluleLCommodite *commSuiv ;
} CelluleLCommodite ;


/* Un reseau */
typedef struct {
  /* Nombre total de noeuds dans le Reseau */
  int nbNoeuds ;
  /* Nombre maximal de fibres dans un cable */
  int gamma ;
  CelluleLCommodite * LCommodites ; /* Liste des commodites a relier */
  /* Liste des noeuds du Reseau */
  CelluleLNoeud * LNoeuds ;
} Reseau ;


// Voir le .c pour plus d'info
void lecture_fichier_reseau(FILE *f, Reseau *R);
int compteCable(Reseau *R);
void ecrit_reseau_disque(Reseau *R, FILE *f);
void ecrit_reseau_xfig(Reseau *R, FILE *f, int zoom, int epaisseur);
Noeud *cherche_noeud(Reseau *R,int num);
int recherche_Voisin(Noeud *nd,int u);
void lecture_reseau(Reseau *R);

#endif
