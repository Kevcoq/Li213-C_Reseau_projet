#include "../../POINT_H/noeud.h"
#include "../../POINT_H/liste.h"
#include "../../POINT_H/chaine.h"

#include <stdio.h>


int main (int argc, char *argv[]) {
  if(!argv[1]) {
    fprintf(stderr,"Parametre manquant\n\t1 : Fichier lut .cha\n");
    return 1;
  }


  FILE *f=fopen(argv[1],"r");

  if(!f) {
    fprintf(stderr,"Erreur ouverture fichier");
    return 1;
  }
  
  ListeChaine l;
  lecture_chaine(f,&l);

  Reseau r;
  r.nbNoeuds=0; r.LNoeuds=NULL;  r.LCommodites=NULL;
  recree_reseau(&l,&r);

  printf("Debut\n");
  printf("Long totale (avant) : %f\n", longueurTotale(&l));
  dijkListeGamma(&l, &r);
  printf("Long totale (après) : %f\n", longueurTotale(&l));

  fclose(f);
  return 0;
}
