#include "../../POINT_H/tas.h"
#include "../../POINT_H/dijkstra.h"
#include "../../POINT_H/noeud.h"
#include "../../POINT_H/liste.h"

#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
  if(!argv[1]) {
    fprintf(stderr,"Parametre manquant\n\t1 : Fichier lut .cha\n\t(opt)2 : Fichier de sauvegarde xfig\n\t(opt)3 : Fichier de sauvegarde xfig_dijkstra\n");
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


  double dist[r.nbNoeuds], etats[r.nbNoeuds];
  int pere[r.nbNoeuds], arrivee=r.nbNoeuds-1;
  printf("Debut\n");
  dijkstra(0, arrivee, dist, etats, pere, &r); 

  int i;
  for(i=0;i<r.nbNoeuds;i++)
    printf("%.2f\t", dist[i]);

  if(argv[2] && argv[3]) {
    FILE 
      *fig=fopen(argv[2],"w"), 
      *figdijk=fopen(argv[3],"w");
    ecrit_reseau_xfig(&r, fig, 5, 2);

    ecrit_reseau_xfig(&r, figdijk, 5, 2);
    dijkstra_xfig(figdijk, &r, 5, 2, arrivee, pere);
  }

  printf("\n%.2f\nFini\n", dist[arrivee]);


  fclose(f);
  return 0;
}
