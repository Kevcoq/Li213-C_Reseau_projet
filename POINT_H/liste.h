# ifndef __CHAINE_H__
# define __CHAINE_H__
#include <stdio.h>


/* Structure d’un point d’une chaine */
typedef struct point {
  /* Coordonnees du point */
  double x , y ;
  /* Pointeur vers le point suivant dans la chaine */
  struct point * ptSuiv ;
} Point ;


/* Element de la liste chaine des chaines */
typedef struct chaine {
  int numero ; /* Numero de la chaine */
  /* Une des 2 extremites de la chaine */
  Point * uneExtremite ;
  /* Lien vers la chaine suivante */
  struct chaine * chSuiv ;
} Chaine ;



/* Liste chainee des chaines */
typedef struct {
  int gamma ; /* Nombre maximal de fibres par chaine */
  /* Nombre de chaines */
  int nbchaine ;
  /* La liste des chaines */
  Chaine * LCh ;
} ListeChaine ;

// Voir .c pour plus d'info
void lecture_chaine(FILE *f,ListeChaine *l);
void ecrit_chaine_txt (ListeChaine *l, FILE *f);
double distancePts(Point *p1, Point *p2);
double longueurChaine(Chaine *l);
double longueurTotale(ListeChaine *lc);
int compte_point(ListeChaine *lc);
void ecrit_chaine_xfig(ListeChaine *L, FILE *f, int zoom,int epaisseur);
void afficher_liste(ListeChaine *l);

# endif
