#include "../../POINT_H/tas.h"
#include "../../POINT_H/dijkstra.h"
#include "../../POINT_H/noeud.h"
#include "../../POINT_H/liste.h"

#include "../../POINT_H/noeud.h"
#include "../../POINT_H/liste.h"
#include "../../POINT_H/chaine.h"

#include <stdio.h>


int main (int argc, char *argv[]) {
  if(!argv[1]) {
    fprintf(stderr,"Parametre manquant\n\t1 : Fichier lut .cha\n");
    return 1;
  }


  FILE *f=fopen(argv[1],"r"), *f2=fopen(argv[1], "r");

  if(!f) {
    fprintf(stderr,"Erreur ouverture fichier");
    return 1;
  }
  
  ListeChaine l, lbis;
  lecture_chaine(f,&l);
  lecture_chaine(f2, &lbis);

  Reseau r;
  r.nbNoeuds=0; r.LNoeuds=NULL;  r.LCommodites=NULL;
  recree_reseau(&l,&r);

  printf("Debut\n");
  printf("Long totale (avant) : %f\n", longueurTotale(&l));
  dijkListe(&l, &r);
  printf("Long totale (ss gamma) : %f\n", longueurTotale(&l));
  dijkListeGamma(&lbis, &r);
  printf("Long totale (avec gamma) : %f\n", longueurTotale(&lbis));

  fclose(f);
  fclose(f2);
  return 0;
}
