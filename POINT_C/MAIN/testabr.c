#include <stdio.h>
#include <stdlib.h>

typedef struct _abr {
  int h;
  int n;
  struct _abr *g;
  struct _abr *d;
} ABR;


// Cette fonction crée un arbre binaire vide, d'étiquette le noeud n (passé en parametre)
ABR *creer_abr(int n) {
  ABR *abr=(ABR*)malloc(sizeof(ABR));
  abr->h=1;
  abr->n=n;
  abr->g=abr->d=NULL;
  return abr;
}



// Fonction annexe renvoyant le maximum de 2 entiers.
int max(int a, int b) {
  if(a>=b)
    return a;
  return b;
}


// Fonction qui calcule recursivement la taille d'un arbre binaire.
int hauteur(ABR *abr) {
  if(abr==NULL) 
    return 0;
  return abr->h;
}


int majHauteur(ABR *abr) {
  if(abr==NULL)
    return 0;
  abr->h=max(majHauteur(abr->g), majHauteur(abr->d))+1;
  return abr->h;
}

// Fonction de rotation à droite (pour équilibrer les arbres)
ABR *rotD(ABR *abr) {
  ABR *tmp=abr->g;
  tmp->h=abr->h;

  abr->g=tmp->d;
  tmp->d=abr;

  abr->h=1+max(hauteur(abr->g), hauteur(abr->d));
  tmp->h=1+max(hauteur(tmp->g), hauteur(tmp->d));
  return tmp;
}

// Fonction de rotation à gauche (pour équilibrer les arbres)
ABR *rotG(ABR *abr) {
  ABR *tmp=abr->d;
  abr->d=tmp->g;
  tmp->g=abr;
  abr->h=1+max(hauteur(abr->g), hauteur(abr->d));
  tmp->h=1+max(hauteur(tmp->g), hauteur(tmp->d));
  return tmp;
}

ABR *rotGD(ABR *abr) {
  if(abr->g)
    abr->g=rotG(abr->g);
  return rotD(abr);
}


ABR *rotDG(ABR *abr) {
  if(abr->d)
    abr->d=rotD(abr->d);
  return rotG(abr);
}




// Fonction d'équilibre
// Teste si il y a besoin d'équilibrer, puis applique la bonne rotation
ABR *equilibre(ABR *abr) {
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
ABR *insertion(ABR *abr, int x) {
  if(!abr)
    return creer_abr(x);
  if(x==abr->n)
    return abr;


  if(x<abr->n) {
    if(!abr->g) {
      ABR *a=creer_abr(x);
      abr->g=a;
    }
    else
      abr->g=equilibre(insertion(abr->g,x));
  }
  else {
    if(!abr->d) {
      ABR *a=creer_abr(x);
      abr->d=a;
    }
    else
      abr->d=equilibre(insertion(abr->d,x));
  }
  majHauteur(abr);
  return equilibre(abr);
}





// Fonction d'affichage très basique d'un arbre
void affiche(ABR *abr) {
  if(abr) {
    printf("%d\t", abr->n);
    affiche(abr->g);
    affiche(abr->d);
  }
}

void aff(ABR *abr, int h)
{
    int i;
    for (i=0;i<h;i++)
    {
        printf("|___ ");
    }
 
    printf("%d\n", abr->n);
    if (abr->g) aff(abr->g, h+1);
    if (abr->d) aff(abr->d, h+1);
}



int main() {
  ABR *a=NULL;
  a=insertion(a,2);
  a=insertion(a,5);
  a=insertion(a,9);
  a=insertion(a,1);
  a=insertion(a,12);
  a=insertion(a,15);
  a=insertion(a,20);
  a=insertion(a,50);
  a=insertion(a,90);
  a=insertion(a,10);
  a=insertion(a,120);
  a=insertion(a,150);
  aff(a,0);
  return 0;
}
