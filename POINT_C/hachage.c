#include "../POINT_H/hachage.h"
#include "../POINT_H/liste.h"
#include "../POINT_H/reseau.h"
#include "../POINT_H/noeud.h"

#include <stdio.h>

// Affiche une table de hachage
void affiche_tbl_hach(Hachage *H) {
  if(!H) {
    fprintf(stderr,"Pas de table de hachage\n");
    exit(-1);
  }

  int i;
  CelluleLNoeud *cln;
  for(i=0;i<H->taille;i++) {
    if(H->tbl[i]) {
      printf("Case %d :\n",i);
      for(cln=H->tbl[i];cln;cln=cln->noeudSuiv)
	printf("\tv %d %lg %lg\n", cln->ptrnoeud->u, cln->ptrnoeud->x, cln->ptrnoeud->y);
    }
  }
}




// La fonction de hachage, celle donné
int fct_hach(double x, double y) {
  return y+(x+y)*(x+y +1)/2;
}





// Creer une table de hachage avec le nombre de case données en parametre
Hachage *creer_hachage(size_t nbCase) {
  Hachage *h=(Hachage*)malloc(sizeof(Hachage));
  h->tbl=(CelluleLNoeud**)malloc(nbCase*sizeof(CelluleLNoeud*));
  h->taille=nbCase;
  int i;
  for(i=0;i<h->taille;i++)
    h->tbl[i]=NULL;
  return h;
}





// Creer une table de hachage rempli à partir d'un réseau déjà initialisé
Hachage *recree_hachage(Reseau *R) {
  if(!R) {
    fprintf(stderr, "Pas de reseau\n");
    exit(-1);
  }

 
  Hachage *H=creer_hachage(100);

  CelluleLNoeud *cln;
  for(cln=R->LNoeuds;cln;cln=cln->noeudSuiv) {
    CelluleLNoeud *nv=(CelluleLNoeud*)malloc(sizeof(CelluleLNoeud));
    nv->ptrnoeud=cln->ptrnoeud;
    nv->noeudSuiv=H->tbl[fct_hach(nv->ptrnoeud->x,nv->ptrnoeud->y)%H->taille];
    H->tbl[fct_hach(nv->ptrnoeud->x,nv->ptrnoeud->y)%H->taille]=nv;
  }
  return H;
}



// Recherche un noeud dans une table de hachage et le renvoie, sinon l'ajoute au réseau et à la table
Noeud* recherche_cree_noeud_hachage(Reseau *R, Hachage **H,double x, double y) {
  if(!(*H))
    (*H)=creer_hachage(5000);

  int indice=fct_hach(x,y)%(*H)->taille;
  CelluleLNoeud *cln=NULL, *cl2=NULL;
  for(cln=(*H)->tbl[indice];cln;cln=cln->noeudSuiv){
    if(compare(x,y,cln->ptrnoeud->x,cln->ptrnoeud->y)==0) {
      return cln->ptrnoeud;
    }
  }
  Noeud *n=creer_noeud(++R->nbNoeuds);
  n->x=x; n->y=y;

  cln=(CelluleLNoeud*)malloc(sizeof(CelluleLNoeud));
  cln->ptrnoeud=n;
  cl2=(CelluleLNoeud*)malloc(sizeof(CelluleLNoeud));
  cl2->ptrnoeud=n;

  cln->noeudSuiv=(*H)->tbl[indice];
  (*H)->tbl[indice]=cln;
  cl2->noeudSuiv=R->LNoeuds;
  R->LNoeuds=cl2;
  return n;
}
  
  



// Creer un reseau à partir d'une liste en s'appuyant sur une table de hachage
void recree_reseau_hachage(ListeChaine *L, Reseau *R, Hachage **H){
  R->gamma=L->gamma;

  Chaine *ch=NULL;
  Point *p=NULL;
  Noeud *n=NULL, *nprec=NULL;
  for(ch=L->LCh;ch;ch=ch->chSuiv) {
    CelluleLCommodite *clc=(CelluleLCommodite*)malloc(sizeof(CelluleLCommodite));
    int i=0;
    for(p=ch->uneExtremite;p;p=p->ptSuiv) {
      if(!i) {
	nprec=recherche_cree_noeud_hachage(R,H,p->x,p->y);
	clc->extr1=nprec->u;
	i++;
      }
      else {
	if(!p->ptSuiv) {
	  clc->extr2=recherche_cree_noeud_hachage(R,H,p->x,p->y)->u;
	}
	else {
	  n=recherche_cree_noeud_hachage(R,H,p->x,p->y);
	  ajouter_voisin(creer_voisin(nprec->u),n);
	  ajouter_voisin(creer_voisin(n->u),nprec);
	  nprec=n;
	}
      }
    }
    if(!R->LCommodites)
      R->LCommodites=clc;
    else {
      clc->commSuiv=R->LCommodites;
      R->LCommodites=clc;
    }
  }
}
