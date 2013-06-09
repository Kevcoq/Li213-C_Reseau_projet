#include "../POINT_H/liste.h"
#include "../POINT_H/entree_sortie.h"
#include <math.h>

// Créer une chaine à partir d'une fichier
void lecture_chaine(FILE *f, ListeChaine *l) {
  int n, i, cpt=0;
  char c;

  Point *ptsprec=NULL;
  Chaine *chprec=NULL;
  
  ListeChaine lc;
  SkipLine(f);
  char buf[20];
  GetChaine(f,20,buf);
  GetChaine(f,20,buf);
  lc.gamma=GetEntier(f);
  lc.LCh=NULL;

  while (fscanf(f,"%c",&c)==1) { 
    if(c=='h') {
      cpt++;
      Chaine *ch=(Chaine*)malloc(sizeof(Chaine));

      ch->numero=GetEntier(f);
      n=GetEntier(f);
      ReadChar(f);
      for(i=0;i<n;i++) {
	Point *pts=(Point*)malloc(sizeof(Point));
  	pts->x=GetReel(f);
  	pts->y=GetReel(f);
  	ReadChar(f);

  	if(i==0) 
  	  ch->uneExtremite=pts;
  	else 
  	  ptsprec->ptSuiv=pts;

  	ptsprec=pts;
      }

      if(chprec)
	chprec->chSuiv=ch;
      else
	lc.LCh=ch;

      chprec=ch;
    }
    else 
      SkipLine(f);
  }
  lc.nbchaine=cpt;
  *l=lc;
}






// Ecrit une chaine sur le disque ("format texte")
void ecrit_chaine_txt (ListeChaine *lc, FILE *f) {
  if (!lc) {
    printf("Erreur liste\n");
    exit(1);
  }


  int i, cpt;
  Chaine *ch=lc->LCh, *tmp;
  Point *pts;


  for(i=0;i<lc->nbchaine;i++) {
    cpt=0;
    
    tmp=ch;
    for(;tmp;tmp=tmp->chSuiv)
      cpt++;
    
    fprintf(f,"h %d %d :", i, cpt);
    pts=ch->uneExtremite;
    
    for(;pts;pts=pts->ptSuiv)
      fprintf(f," %f %f /", pts->x, pts->y);
    
    fprintf(f,"\n");
  }
}



// Fct annexe pour calculer la distance entre 2 pts
double distancePts(Point *p1, Point *p2) {
  double 
    x=(p2->x)-(p1->x),
    y=(p2->y)-(p1->y);

  return sqrt(x*x+y*y);      
}



// Fct annexe pour calculer la longueur d'une chaine
double longueurChaine(Chaine *l) {
  double cpt=0;
  Point *pts;
  
  for(pts=l->uneExtremite;pts && pts->ptSuiv;pts=pts->ptSuiv)
    cpt+=distancePts(pts,pts->ptSuiv);

  return cpt;
}



// Fct annexe pour calculer la longueur de la liste chainé complete
double longueurTotale(ListeChaine *lc) {
  double cpt=0;
  Chaine *ch=lc->LCh;

  for(;ch;ch=ch->chSuiv)
    cpt+=longueurChaine(ch);
   
  return cpt;
}


// Fct qui compte le nombre de pts de la liste chainé
int compte_point(ListeChaine *lc) {
  int cpt=0;
  Chaine *ch=lc->LCh;
  for(;ch;ch=ch->chSuiv) {
    Point *p=ch->uneExtremite;
    for(;p;p=p->ptSuiv)
      cpt++;
  }
  return cpt;
}




// Ecrit sur le disque la chaine au format xfig (dessin de la liste chainé)
void ecrit_chaine_xfig(ListeChaine *L, FILE *f, int zoom,int epaisseur){
  //Initialisation
  fprintf(f,"#FIG 3.2\n");
  fprintf(f,"Landscape\n");
  fprintf(f,"Center\n");
  fprintf(f,"Metric\n");
  fprintf(f,"A4\n");
  fprintf(f,"100.00\n");
  fprintf(f,"Single\n");
  fprintf(f,"-2\n");
  fprintf(f,"1200 2\n");

  //debut
  Chaine *c=NULL;
  Point *p=NULL;
  float i=0.000;
  for(c=L->LCh; c; c=c->chSuiv) {
    for(p=c->uneExtremite; p; p=p->ptSuiv) {
      fprintf(f,"1 4 0 %d 0 7 50 0 -1 0.000 1 0.0000 %.0f %.0f 6 6 0 0 0 0\n",epaisseur,zoom*p->x,zoom*p->y);
      if(p->ptSuiv)
	fprintf(f,"2 1 1 %d 8 7 50 0 -1 %.000f 0 0 -1 0 0 2         \n%.0f %.0f %.0f %.0f\n",(int)epaisseur/2,fmod(i,4),zoom*p->x,zoom*p->y,zoom*p->ptSuiv->x,zoom*p->ptSuiv->y);
      i+=0.5;
    }
  }
}





// Affiche la liste chainé
void afficher_liste(ListeChaine *l){
  printf("gamma : %d, nbchaine : %d\n\n",l->gamma, l->nbchaine);
  Chaine *c=NULL;
  Point *p=NULL;
  
  for(c=l->LCh;c;c=c->chSuiv) {
    printf("numéro de chaine : %d\n",c->numero);
    for(p=c->uneExtremite;p;p=p->ptSuiv)
      printf("\tX : %lg, Y : %lg\n",p->x,p->y);
    printf("\n");
  }
}
