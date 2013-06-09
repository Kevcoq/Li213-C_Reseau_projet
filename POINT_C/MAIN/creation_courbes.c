#include "../../POINT_H/liste.h"
#include "../../POINT_H/reseau.h"
#include "../../POINT_H/noeud.h"
#include "../../POINT_H/hachage.h"
#include "../../POINT_H/abr.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CPU 1e-3

/* Ce fichier est à utilisé avec le script (bash) creation courbe, qui parcour le dossier instance et applique ce programme sur toutes les instances

   Ce programme lit un fichier .cha est crées, tout en calculant le tps nécessaire à son execution, 3 fichiers réseaux : 
   * un sans outils
   * un utilisant une table de hachage
   * un utilisant un arbre binaire de recherche

 */


int main (int argc, char *argv[]) {
  if(!argv[1] || !argv[2] || !argv[3] || !argv[4] || !argv[5] || !argv[6] || !argv[7]) {
    fprintf(stderr,"Parametre manquant\n\t1 : Fichier lut .cha\n\t2 : Fichier de sauvegarde .res\n\t3 : Fichier de sauvegarde hachage.res\n\t4 : Fichier de sauvegarde abr.res\n\t5 : Fichier de sauvegarde liste xfig\n\t6 : Fichier de sauvegarde reseau xfig\n\t7 : Nbr de ligne du fichier .cha\n");
    return 1;
  }
  clock_t tps_i, tps_f;
  float noeud, hachage, arbre;
  FILE
    *f=fopen(argv[1],"r"),
    *svr=fopen(argv[2],"w"),
    *svh=fopen(argv[3],"w"),
    *sva=fopen(argv[4],"w"),
    *lfig=fopen(argv[5],"w"),
    *rfig=fopen(argv[6],"w");


  ListeChaine l;
  lecture_chaine(f,&l);
  ecrit_chaine_xfig(&l, lfig,50,2);

  Reseau r;
  r.nbNoeuds=0; r.LNoeuds=NULL;  r.LCommodites=NULL;
  tps_i=clock();// ###
  recree_reseau(&l,&r);
  tps_f=clock();// ###
  noeud=(tps_f-tps_i)*CPU;// ###
  ecrit_reseau_disque(&r,svr);
  ecrit_reseau_xfig(&r,rfig,50,2);

  Hachage *H=NULL;
  H=creer_hachage(100000);
  Reseau r2;
  r2.nbNoeuds=0; r2.LNoeuds=NULL;  r2.LCommodites=NULL;
  tps_i=clock();// ###
  recree_reseau_hachage(&l,&r2,&H);
  tps_f=clock();// ###
  hachage=(tps_f-tps_i)*CPU;// ###
  ecrit_reseau_disque(&r2,svh);


  ABRe *abr=NULL;
  Reseau *r3=malloc(sizeof(Reseau));
  r3->nbNoeuds=0; r3->LNoeuds=NULL;  r3->LCommodites=NULL;
  tps_i=clock();// ###
  recree_reseau_ABRE(&l,r3,&abr);
  tps_f=clock();// ###
  arbre=(tps_f-tps_i)*CPU;// ###
  ecrit_reseau_disque(r3,sva);


  printf("%s %f %f %f\n", argv[7], noeud, hachage, arbre);


  fclose(f);
  fclose(svr);
  fclose(svh);
  fclose(sva);
  fclose(lfig);
  fclose(rfig);

  return 0;
}
