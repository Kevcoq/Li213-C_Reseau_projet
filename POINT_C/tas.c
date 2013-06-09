#include <stdio.h>
#include <stdlib.h>

#include "../POINT_H/tas.h"

// Creer tas
Tas *creer_tas(int n) {
  Tas *tas=(Tas*)malloc(sizeof(Tas));
  tas->elem=(Elem**)malloc(sizeof(Elem*)*n);
  tas->n=n;
  tas->nb_elt=0;
  return tas;
}

// Creer element
Elem *creer_elem(int num, double clef) {
  Elem *e=(Elem*)malloc(sizeof(Elem));
  e->num=num;
  e->c=clef;
  return e;
}


// Affiche l'element
void affiche_elem(Elem *elt) {
  printf("%d\t%f\n", elt->num, elt->c);
}


// Affiche le tas
void affiche_tas(Tas *tas) {
  int i;
  for(i=0;i<tas->n;i++)
    if(tas->elem[i])
      printf("%d\t", tas->elem[i]->num);
  printf("\n");
}

// Echange 2 éléments du tas
void echanger(Tas *tas, int i, int j){
  Elem *tmp=tas->elem[i];
  tas->elem[i]=tas->elem[j];
  tas->elem[j]=tmp;
}

// 0 si i a un pere
int a_un_pere(int i) {
  if(i!=0)
    return 0;
  return 1;
}

// Rend le pere du sommet courant
int pere(int i) {
  if(i%2==0)
    return (i-1)/2;
  return i/2;
}

// Fct pour remonter un elt dans le tas
void monter(Tas *tas, int i){
  if(a_un_pere(i))
    return;
  int index=pere(i);
  if((tas->elem[index]->c)>(tas->elem[i]->c)) {
    echanger(tas, i, index);
    monter(tas, index);
  }
}


// Fct pour descendre un elt dans le tas
void descendre(Tas *tas, int i){
  if(i*2+2 < tas->nb_elt) {
    if((tas->elem[i*2+1]->c < tas->elem[i*2+2]->c) && (tas->elem[i]->c > tas->elem[i*2+1]->c)) {
      echanger(tas, i, i*2+1);
      descendre(tas, i*2+1);
      return;
    }	
    
    if((tas->elem[i*2+1]->c >= tas->elem[i*2+2]->c) && (tas->elem[i]->c > tas->elem[i*2+2]->c)){
      echanger(tas, i, i*2+2);
      descendre(tas, i*2+2);
      return;
    }
  }
  
  if((i*2+1 < tas->nb_elt) && (tas->elem[i]->c > tas->elem[i*2+1]->c)) {
    echanger(tas, i, i*2+1);
    descendre(tas, i*2+1);
    return;
  }
}


// Fct d'insertion d'un élément dans un tas
void insertion_tas(Tas *tas, Elem *elt) {
  tas->elem[tas->nb_elt++]=elt;
  monter(tas,tas->nb_elt-1);
}


// Extraction du plus petit élément d'un tas
Elem *extraire_min(Tas *tas) {
  Elem *stock=tas->elem[0];
  tas->elem[0]=tas->elem[--tas->nb_elt];
  tas->elem[tas->nb_elt]=NULL;
  descendre(tas,0);
  return stock;
}


// Suppresion d'un elt 
void supprimer_elem(Tas *tas, int n) {
  int i, index=0;
  for(i=0;i<tas->nb_elt;i++)
    if(tas->elem[i]->num==n) {
      index=i;
      i=tas->nb_elt;
    }
  tas->elem[index]=tas->elem[--tas->nb_elt];
  monter(tas, index);
  descendre(tas, index);
}

// Recherche d'un élément de numéro n
Elem *recherche(Tas *tas, int n) {
  int i;
  for(i=0;i<tas->nb_elt;i++) 
    if(tas->elem[i]->num==n)
      return tas->elem[i];
  return NULL;
}
