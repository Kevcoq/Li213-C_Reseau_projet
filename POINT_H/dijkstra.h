#ifndef __DIJKSTRA__
#define __DIJKSTRA__

#include "reseau.h"

// Voir le .c pour plus d'info
void dijkstra(int, int, double*, double*, int*, Reseau*);
void dijkstraGamma(int, int, double*, double*, int*, Reseau*);

void dijkstra_xfig(FILE *f, Reseau *r, int zoom, int epaisseur, int arrivee, int *pere);
#endif
