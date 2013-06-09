#include "../POINT_H/noeud.h"

#define EPS 0.05


// Creer un noeud avec comme numéro celui passé en parametre
Noeud *creer_noeud(int x) {
  Noeud *n=(Noeud*)malloc(sizeof(Noeud));
  n->u=x;
  return n;
}



// Creer un voisin initialisé avec le numéro en parametre
Voisin *creer_voisin(int v){
  Voisin *vois=malloc(sizeof(Voisin));
  if(!vois){    
    fprintf(stderr,"echec alloc memoire voisin\n");    
    return NULL; 
  }
  vois->voisSuiv=NULL;
  vois->v=v;
  return vois;
}




// Ajoute au voisin vois le noeud n comme voisin
void ajouter_voisin(Voisin *vois,Noeud *n){
  if(!vois || !n || vois->v==n->u)
    return;

  Voisin *v=NULL;

  for(v=n->LVoisins;v;v=v->voisSuiv)
    if(v->v==vois->v)
      return;
  
  v=n->LVoisins;
  vois->voisSuiv=v;
  n->LVoisins=vois;
}




// Compare les points A et B, et renvoie 0 si ils sont égaux, -1 si A est "plus petit" que B, ou 1 dans le cas contraire
// Les valeurs étant des doubles, présence d'un EPSILON pour contourner les troncatures de valeurs
int compare(double x1, double y1, double x2, double y2) {
  if(abs(x1-x2)<0.01 && abs(y1-y2)<0.01)
    return 0;

  if(x1 < x2 || (abs(x1-x2)<EPS && y1<y2))
    return -1;
  
  return 1;
}
  
int compareN(Noeud *n1, Noeud *n2) {
  return compare(n1->x, n1->y, n2->x, n2->y);
}





// Fct d'affichage pour un noeud
void affiche_noeud(Noeud *n) {
  if(n) {
    printf("num : %d,\tcoord : (%f;%f)\n",n->u,n->x,n->y);
    Voisin *v;
    for(v=n->LVoisins;v;v=v->voisSuiv)
      printf("\t%d\n",v->v);
  }
}




// Renvoie le noeud recherché, et si il n'existe pas dans le réseau, l'ajoute
Noeud* recherche_cree_noeud(Reseau *R, double x, double y){
  CelluleLNoeud *cln=NULL;;
  for(cln=R->LNoeuds;cln;cln=cln->noeudSuiv) 
    if(compare(x,y,cln->ptrnoeud->x,cln->ptrnoeud->y)==0)
      return cln->ptrnoeud;
  
  Noeud *n=(Noeud*)malloc(sizeof(Noeud));
  n->u=(R->nbNoeuds++); n->x=x; n->y=y;
  CelluleLNoeud 
    *clp=NULL, 
    *ln=(CelluleLNoeud*)malloc(sizeof(CelluleLNoeud));
  ln->ptrnoeud=n; ln->noeudSuiv=NULL;
  for(cln=R->LNoeuds;cln;cln=cln->noeudSuiv) {
    if(compare(x,y,cln->ptrnoeud->x,cln->ptrnoeud->y)==-1) {
      ln->noeudSuiv=cln;
      if(clp)
    	clp->noeudSuiv=ln;
      else
	R->LNoeuds=ln;
      return ln->ptrnoeud;
    }

    clp=cln;
  }
  if(!R->LNoeuds)
    R->LNoeuds=ln;
  if(clp)
    clp->noeudSuiv=ln;
  return ln->ptrnoeud;
}









// Creer le reseau à partir de la liste chainé.
void recree_reseau(ListeChaine *L, Reseau *R) {
  R->gamma=L->gamma;

  Chaine *ch=NULL;
  Point *p=NULL;
  Noeud *n=NULL, *nprec=NULL;
  for(ch=L->LCh;ch;ch=ch->chSuiv) {
    CelluleLCommodite *clc=(CelluleLCommodite*)malloc(sizeof(CelluleLCommodite));
    int i=0;
   
    for(p=ch->uneExtremite;p;p=p->ptSuiv) {
      if(!i) {
	nprec=recherche_cree_noeud(R,p->x,p->y);
	clc->extr1=nprec->u;
	i++;
      }
      if(!p->ptSuiv)
	clc->extr2=n->u;
      else {
	n=recherche_cree_noeud(R,p->ptSuiv->x,p->ptSuiv->y);
	ajouter_voisin(creer_voisin(nprec->u),n);
	ajouter_voisin(creer_voisin(n->u),nprec);
	nprec=n;
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
