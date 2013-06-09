// COQUART
// RYBAEV
#include "../POINT_H/liste.h"
#include "../POINT_H/reseau.h"
#include "../POINT_H/noeud.h"
#include "../POINT_H/dijkstra.h"


// Retourne le 1er noeud de la chaîne
Noeud *debutChaine(Chaine *ch, Reseau *r) {
  return recherche_cree_noeud(r, ch->uneExtremite->x, ch->uneExtremite->y);
}


// Retourne le noeud en fin de chaîne
Noeud *finChaine(Chaine *ch, Reseau *r) {
  Point 
    *p=ch->uneExtremite, 
    *pprec=NULL;

  for(;p;p=p->ptSuiv)
    pprec=p;

  return recherche_cree_noeud(r, pprec->x, pprec->y);
}


// Ecrit le chaine à partir du tableau pere et du pts d'arrivée
Chaine *ecritChaine(Reseau *r, int arrivee, int *pere) {
  Chaine *ch = (Chaine*) malloc(sizeof(Chaine));
  int i=arrivee;
  Point *p, *pprec=NULL;
  while(pere[i]!=-1) {
    p = (Point*) malloc(sizeof(Point));
    Noeud *n=cherche_noeud(r, i);
    p->x=n->x;
    p->y=n->y;
    
    if(pprec)
      pprec->ptSuiv=p;
    else
      ch->uneExtremite=p;

    pprec=p;
    i=pere[i];
  }

  return ch;
}



// Voir dijkListe
Chaine *dijkChaine(Chaine *ch, Reseau *r) {
  double dist[r->nbNoeuds], etats[r->nbNoeuds];
  int pere[r->nbNoeuds];
  
  Noeud 
    *n1=debutChaine(ch, r),
    *n2=finChaine(ch, r);
  dijkstra(n1->u, n2->u, dist, etats, pere, r);
  Chaine *chaine = ecritChaine(r, n2->u, pere);
  chaine->numero=ch->numero;
  chaine->chSuiv=ch->chSuiv;
  return chaine;
}

 
// Applique dijkstra à chaque chaîne de la liste chaînée
void dijkListe(ListeChaine *lCh, Reseau *r) {
  Chaine 
    *ch=NULL,
    *chaine,
    *chprec=NULL;
  int i=1;

  for(ch=lCh->LCh;ch;ch=ch->chSuiv) {
    if(i%(lCh->nbchaine/10)==0)
      printf("%d sur %d\n", i, lCh->nbchaine);
    chaine=dijkChaine(ch, r);

    if(chprec)
      chprec->chSuiv=chaine;
    else
      lCh->LCh=chaine;

    chprec=chaine;
    i++;
  }
}



// Voir dijkListeGamma
Chaine *dijkChaineGamma(Chaine *ch, Reseau *r) {
  double dist[r->nbNoeuds], etats[r->nbNoeuds];
  int pere[r->nbNoeuds];
  
  Noeud 
    *n1=debutChaine(ch, r),
    *n2=finChaine(ch, r);
  dijkstraGamma(n1->u, n2->u, dist, etats, pere, r);
  Chaine *chaine = ecritChaine(r, n2->u, pere);
  chaine->numero=ch->numero;
  chaine->chSuiv=ch->chSuiv;
  return chaine;
}


// Applique dijkstra à chaque chaîne de la liste chaînée, en prenant en cause les gammas
void dijkListeGamma(ListeChaine *lCh, Reseau *r) {
  Chaine 
    *ch=NULL,
    *chaine,
    *chprec=NULL;
  int i=1;

  for(ch=lCh->LCh;ch;ch=ch->chSuiv) {
    if(i%(lCh->nbchaine/10)==0)
      printf("%d sur %d\n", i, lCh->nbchaine);
    chaine=dijkChaineGamma(ch, r);

    if(chprec)
      chprec->chSuiv=chaine;
    else
      lCh->LCh=chaine;

    chprec=chaine;
    i++;
  }
}
