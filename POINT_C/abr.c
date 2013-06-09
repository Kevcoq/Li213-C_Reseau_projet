
#include "../POINT_H/abr.h"
#include "../POINT_H/noeud.h"
#include "../POINT_H/reseau.h"

#include <stdio.h>

// Cette fonction crée un arbre binaire vide, d'étiquette le noeud n (passé en parametre)
ABRe *creer_abr(Noeud *n) {
  ABRe *abr=(ABRe*)malloc(sizeof(ABRe));
  abr->h=1;
  abr->n=n;
  abr->g=abr->d=NULL;
  return abr;
}


// Fonction d'affichage très basique d'un arbre
void affiche(ABRe *abr) {
  if(abr) {
    printf("%d\t", abr->n->u);
    affiche(abr->g);
    affiche(abr->d);
  }
}
void aff(ABRe *abr, int h)
{
    int i;
    for (i=0;i<h;i++)
    {
        printf("|___ ");
    }
 
    printf("%d\n", abr->n->u);
    if (abr->g) aff(abr->g, h+1);
    if (abr->d) aff(abr->d, h+1);
}












// Fonction annexe renvoyant le maximum de 2 entiers.
int max(int a, int b) {
  if(a>=b)
    return a;
  return b;
}


// Fonction qui calcule recursivement la taille d'un arbre binaire.
int hauteur(ABRe *abr) {
  if(abr==NULL) 
    return 0;
  return abr->h;
}

// Met à jour la hauteur d'un abr
int majHauteur(ABRe *abr) {
  if(abr==NULL)
    return 0;
  abr->h=max(majHauteur(abr->g), majHauteur(abr->d))+1;
  return abr->h;
}

// Fonction de rotation à droite (pour équilibrer les arbres)
ABRe *rotD(ABRe *abr) {
  ABRe *tmp=abr->g;
  abr->g=tmp->d;
  tmp->d=abr;

  majHauteur(abr);
  return tmp;
}


// Fonction de rotation à gauche (pour équilibrer les arbres)
ABRe *rotG(ABRe *abr) {
  ABRe *tmp=abr->d;
  abr->d=tmp->g;
  tmp->g=abr;

  majHauteur(abr);
  return tmp;
}

// Rotation double
ABRe *rotGD(ABRe *abr) {
  if(abr->g)
    abr->g=rotG(abr->g);
  return rotD(abr);
}
ABRe *rotDG(ABRe *abr) {
  if(abr->d)
    abr->d=rotD(abr->d);
  return rotG(abr);
}


// Fonction d'équilibre
// Teste si il y a besoin d'équilibrer, puis applique la bonne rotation
ABRe *equilibre(ABRe *abr) {
  if(!abr)
    return abr;

  int d=hauteur(abr->g)-hauteur(abr->d);
  if(abs(d)<=1)
    return abr;

  if(d==2) {
    if(hauteur(abr->g->g)>=hauteur(abr->g->d))
      return rotD(abr);
    return rotGD(abr);
  }

  if(hauteur(abr->d->d)>=hauteur(abr->d->g))
    return rotG(abr);
  return rotDG(abr);
}










// Fonction d'insertion d'un élément dans un arbre
// Insere l'élément au bon endroit
// Equilibre l'arbre
ABRe *insertion(ABRe *abr, Noeud **x) {
  if(!abr)
    return creer_abr(*x);

  if(compareN(*x,abr->n)==0) {
    *x=abr->n;
    return abr;
  }


  if(compareN(*x,abr->n)<0) {
    if(!abr->g) {
      ABRe *a=creer_abr(*x);
      abr->g=a;
    }
    else
      abr->g=equilibre(insertion(abr->g,x));
  }
  else {
    if(!abr->d) {
      ABRe *a=creer_abr(*x);
      abr->d=a;
    }
    else
      abr->d=equilibre(insertion(abr->d,x));
  }
  majHauteur(abr);
  return equilibre(abr);
}











// Cette fonction créer un arbre à partir d'un réseau déjà initialisé
ABRe *recree_abr(Reseau *R) {
  if(!R) {
    fprintf(stderr, "Pas de reseau\n");
    exit(-1);
  }

  ABRe *abr=NULL, *abrprec=NULL;

  CelluleLNoeud *cln;
  for(cln=R->LNoeuds;cln;cln=cln->noeudSuiv) {
    Noeud *nv=(Noeud*)malloc(sizeof(Noeud));
    nv=cln->ptrnoeud;
    ABRe *ab=creer_abr(nv);

    if(!abr)
      abr=ab;
    else {
      ABRe *atmp=abr;
      
      while(atmp) {
	abrprec=atmp;
	int comp=compare(nv->x,nv->y,atmp->n->x,atmp->n->y);
	if(!comp) {};
	if(comp<0)
	  atmp=atmp->g;
	else
	  atmp=atmp->d;
      }
      if(compare(nv->x,nv->y,abrprec->n->x,abrprec->n->y)==-1)
	abrprec->g=ab;
      else
	abrprec->d=ab;
    }
  }
  return abr;
}








// Ajoute le noeud n au réseau R au bon emplacement
void ajoute_au_reseau(Reseau *R, Noeud *n) {
  CelluleLNoeud 
    *cln=NULL,
    *clp=NULL, 
    *ln=(CelluleLNoeud*)malloc(sizeof(CelluleLNoeud));
  ln->ptrnoeud=n; ln->noeudSuiv=NULL;
  for(cln=R->LNoeuds;cln;cln=cln->noeudSuiv) {
    if(compareN(n, cln->ptrnoeud)==-1) {
      ln->noeudSuiv=cln;
      if(clp)
    	clp->noeudSuiv=ln;
      else
	R->LNoeuds=ln;
      return;
    }
    clp=cln;
  }
  if(!R->LNoeuds)
    R->LNoeuds=ln;
  if(clp)
    clp->noeudSuiv=ln;
  return;
}


// Cette fonction recherche si le noeud existe dans l'arbre, si il existe le retourne
// sinon l'ajoute au réseau et à l'insere dans l'arbre
Noeud* recherche_cree_noeud_abr(Reseau *R, ABRe **abr, double x, double y) {
  Noeud *n=creer_noeud(R->nbNoeuds++);
  n->x=x;
  n->y=y;
  *abr=insertion(*abr,&n);
  if(n->u == R->nbNoeuds-1)
    ajoute_au_reseau(R, n);
  else 
    R->nbNoeuds--;
  return n;
}
  

// Cette fonction crée un reseau à partir d'une liste en s'appuyant sur un arbre binaire
void recree_reseau_ABRE(ListeChaine *L, Reseau *R, ABRe **abr) {
  R->gamma=L->gamma;

  Chaine *ch=NULL;
  Point *p=NULL;
  CelluleLCommodite *clcp=NULL;
  Noeud *n=NULL, *nprec=NULL;

  for(ch=L->LCh;ch;ch=ch->chSuiv) {
    CelluleLCommodite *clc=(CelluleLCommodite*)malloc(sizeof(CelluleLCommodite));
    int i=0;
    for(p=ch->uneExtremite;p;p=p->ptSuiv) {
      if(!i) {
	nprec=recherche_cree_noeud_abr(R,abr,p->x,p->y);
	clc->extr1=nprec->u;
	i++;
      }
      else
	if(!p->ptSuiv)
	  clc->extr2=recherche_cree_noeud_abr(R,abr,p->x,p->y)->u;
	else {
	  n=recherche_cree_noeud_abr(R,abr,p->x,p->y);
	  ajouter_voisin(creer_voisin(nprec->u),n);
	  ajouter_voisin(creer_voisin(n->u),nprec);
	  nprec=n;
	}
    }
    if(!R->LCommodites)
      R->LCommodites=clc;
    if(clcp)
      clcp->commSuiv=clc;
    clcp=clc;
  }
}
