#include "../../POINT_H/liste.h"
#include "../../POINT_H/reseau.h"
#include "../../POINT_H/noeud.h"
#include "../../POINT_H/abr.h"

#include <stdio.h>
#include <stdlib.h>

/* Ce programme convertit un fichier .cha donnés en argument en un .res, avec les fonctions sur les arbres 
*/

int main (int argc, char *argv[]) {
 if(!argv[1] || !argv[2]) {
    fprintf(stderr,"Parametre manquant\n\t1 : Fichier lut .cha\n\t2 : Fichier de sauvegarde .res\n\t3 : Facultatif : emplacement de sauvegarde xfig si voulu\n");
    return 1;
  }
  FILE 
    *f=fopen(argv[1],"r"),
    *svr=fopen(argv[2],"w");
  
  if(!f || !svr) {
    fprintf(stderr,"Erreur ouverture fichier\n");
    return 1;
  }

  ListeChaine l;
  lecture_chaine(f,&l);

  //printf("### ARBRE ###\n");
  ABRe *abr=NULL;
  Reseau r3;
  r3.nbNoeuds=0; r3.LNoeuds=NULL;  r3.LCommodites=NULL;
  recree_reseau_ABRE(&l,&r3,&abr);
  //lecture_reseau(&r);
  ecrit_reseau_disque(&r3,svr);
  //affiche(abr);
  //aff(abr, 0);


  if(argv[3]) {
    FILE *xfig=fopen(argv[3],"w");
    ecrit_reseau_xfig(&r3,xfig,500,2);
    fclose(xfig);
    printf("Fichier rendu : %s\t %s\n", argv[2], argv[3]);
  }
  else
    printf("Fichier rendu : %s\n", argv[2]);

  printf("Fini\n");
  
  
  fclose(f);
  fclose(svr);
  return 0;
}
