#include "../POINT_H/tas.h"
#include "../POINT_H/reseau.h"
#include "../POINT_H/dijkstra.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Calcule la distance entre 2 noeuds
double distance(int n1, int n2, Reseau *r) {
  Noeud 
    *noeud1 = cherche_noeud(r, n1),
    *noeud2 = cherche_noeud(r, n2);
  
  return sqrt(pow(noeud2->x - noeud1->x, 2) + pow(noeud2->y - noeud1->y, 2));
}
  






// Mise à jour du tas avec les voisins du noeuds
void maj(int nNoeud, double etats[], double dist[], int pere[], Tas *tas, Reseau *r) {
  Noeud *n = cherche_noeud(r, nNoeud);
  
  Voisin *v;
  for(v=n->LVoisins;v;v=v->voisSuiv){
    if(etats[v->v]==0) {
      int d=distance(nNoeud, v->v, r) + dist[nNoeud];
      Elem *elt = creer_elem(v->v, d);
      insertion_tas(tas, elt);
      etats[v->v]=1;
      dist[v->v]=d;
      pere[v->v]=nNoeud;
    }
    else {
      if(etats[v->v]==1) {
	int d=distance(nNoeud, v->v, r) + dist[nNoeud];
	if(dist[v->v] > d) {
	  supprimer_elem(tas, v->v);
	  
	  Elem *elt = creer_elem(v->v, d);
	  insertion_tas(tas, elt);

	  dist[v->v]=d;
	  pere[v->v]=nNoeud;
	}
      }
    }
  }
}

  
  





// Dijkstra ;p
void dijkstra(int depart, int arrivee, double *dist, double *etats, int *pere, Reseau *r) {
  //Etat 0 pas traité
  //Etat 1 bordures
  //Etat 2 ne sera plus touché

  if(!r) {
    fprintf(stderr, "LE reseau est vide\n");
    exit(1);
  }


  if(depart==arrivee)
    return;


  int i;
  for(i=0;i<r->nbNoeuds;i++) {
    dist[i]=-1;
    etats[i]=0;
    pere[i]=-1;
  }

  etats[depart]=2;
  dist[depart]=0;

  Tas *bordures=creer_tas(r->nbNoeuds);
  insertion_tas(bordures, creer_elem(depart, 0));

  while(bordures && etats[arrivee]!=2) {
    int nCourant = extraire_min(bordures)->num;
    etats[nCourant]=2;
    
    maj(nCourant, etats, dist, pere, bordures, r);
  }
}






// Fct avec gamma 



// Mise à jour du tas en prenant en compte les gammas
void majGamma(int nNoeud, double etats[], double dist[], int pere[], int gamma[], Tas *tas, Reseau *r) {
  Noeud *n = cherche_noeud(r, nNoeud);
  
  Voisin *v;
  for(v=n->LVoisins;v;v=v->voisSuiv){
    if(etats[v->v]==0 && gamma[nNoeud]<r->gamma && gamma[v->v]<r->gamma) {
      gamma[nNoeud]++;
      gamma[v->v]++;
      int d=distance(nNoeud, v->v, r) + dist[nNoeud];
      Elem *elt = creer_elem(v->v, d);
      insertion_tas(tas, elt);
      etats[v->v]=1;
      dist[v->v]=d;
      pere[v->v]=nNoeud;
    }
    else {
      if(etats[v->v]==1 && gamma[nNoeud]<r->gamma && gamma[v->v]<r->gamma) {
	gamma[nNoeud]++;
	gamma[v->v]++;
	int d=distance(nNoeud, v->v, r) + dist[nNoeud];
	if(dist[v->v] > d) {
	  supprimer_elem(tas, v->v);
	  
	  Elem *elt = creer_elem(v->v, d);
	  insertion_tas(tas, elt);

	  dist[v->v]=d;
	  pere[v->v]=nNoeud;
	}
      }
    }
  }
}


// Dijkstra avec les gammas :p
void dijkstraGamma(int depart, int arrivee, double *dist, double *etats, int *pere, Reseau *r) {
  //Etat 0 pas traité
  //Etat 1 bordures
  //Etat 2 ne sera plus touché

  if(!r) {
    fprintf(stderr, "LE reseau est vide\n");
    exit(1);
  }


  if(depart==arrivee)
    return;


  int i, gamma[r->nbNoeuds];
  for(i=0;i<r->nbNoeuds;i++) {
    dist[i]=-1;
    etats[i]=0;
    pere[i]=-1;
    gamma[i]=0;
  }

  etats[depart]=2;
  dist[depart]=0;

  Tas *bordures=creer_tas(r->nbNoeuds);
  insertion_tas(bordures, creer_elem(depart, 0));

  while(bordures && etats[arrivee]!=2) {
    int nCourant = extraire_min(bordures)->num;
    etats[nCourant]=2;
    
    majGamma(nCourant, etats, dist, pere, gamma, bordures, r);
  }
}





// Creation du graphe avec dijkstra en rouge
void dijkstra_xfig(FILE *f, Reseau *r, int zoom, int epaisseur, int arrivee, int *pere) {
  int nc=arrivee;
  Noeud *n1=cherche_noeud(r, nc), *n2=NULL;
  while(pere[nc]!=-1) {
    nc=pere[nc];
    n2=cherche_noeud(r, nc);
    fprintf(f,"2 1 1 %d 4 7 50 0 -1 %d 0 0 -1 0 0 2         \n%.0f %.0f %.0f %.0f\n", (int)epaisseur/2, 0, zoom*n1->x, zoom*n1->y, zoom*n2->x, zoom*n2->y);
    n1=n2;
  }
}



