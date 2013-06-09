#ifndef TAS__H
#define TAS__H

// Structure d'un élément
// c : la clé (ici ce sera la distance entre le pts courant et le départ)
// num : le numéro du noeud
typedef struct _elem {
  double c;
  int num;
} Elem;


// Strucutre d'un tas
// elem : tableau de pointeur vers des éléments
// n : le nombre d'élément maximal du tas (puisqu'il n'y a pas de fct pour l'agrandir, on le définit de la taille du réseau. Pour une utilisation optimale il faudrait le faire de taille plus petite et l'agrandir en cas de besoin, la réalocation prenant du temps, notre solution évite de chercher la bonne taille de tas pour chaque instance).
// nb_elt : nombre d'élément actuel dans le tas
typedef struct _tas {
  Elem **elem;
  int n;
  int nb_elt;
} Tas;


// Voir .c pour plus d'info
Tas *creer_tas(int n);
Elem *creer_elem(int num, double clef);
void affiche_elem(Elem *elt);
void affiche_tas(Tas *tas);
void insertion_tas(Tas *tas, Elem *elt);
Elem *extraire_min(Tas *tas);
void supprimer_elem(Tas *tas, int i);
Elem *recherche(Tas *tas, int i);



#endif
