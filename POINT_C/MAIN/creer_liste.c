#include "../../POINT_H/liste.h"

#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
  if(!argv[1] || !argv[2]) {
    fprintf(stderr,"Parametre manquant\n\t1 : Fichier lut .cha\n\t2 : emplacement de sauvegarde xfig\n");
    return 1;
  }

  printf("Fichier rendu : %s\n", argv[2]);
   FILE  
     *f=fopen(argv[1],"r"),
     *lfig=fopen(argv[2],"w");

  ListeChaine l;
  lecture_chaine(f,&l);
  ecrit_chaine_xfig(&l, lfig,500,2);
  
  return 0;
}
