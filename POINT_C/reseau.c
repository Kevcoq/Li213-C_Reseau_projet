#include "../POINT_H/reseau.h"
#include "../POINT_H/entree_sortie.h"


// Creer un reseau à partir d'une fichier
void lecture_fichier_reseau(FILE *f, Reseau *R) {
  Reseau r;
  char buf[20];
  GetChaine(f,20,buf);
  GetChaine(f,20,buf);
  GetChaine(f,20,buf);
  r.nbNoeuds=GetEntier(f);
  SkipLine(f);
  SkipLine(f);
  GetChaine(f,20,buf);
  GetChaine(f,20,buf);
  GetChaine(f,20,buf);
  r.gamma=GetEntier(f);
  r.LCommodites=NULL;
  r.LNoeuds=NULL;
  
  CelluleLCommodite  *CLC=NULL, *CLCP=NULL;
  CelluleLNoeud *CLN=NULL, *CLNP=NULL;


  char c;
  int numn, numv;
  while (fscanf(f,"%c",&c)==1) {
    if(c=='v') {      
      CelluleLNoeud *cln=(CelluleLNoeud*)malloc(sizeof(CelluleLNoeud)); cln->noeudSuiv=NULL;
      Noeud *n=(Noeud*)malloc(sizeof(Noeud));
      n->u=GetEntier(f);
      n->x=GetReel(f);
      n->y=GetReel(f);

      cln->ptrnoeud=n;

      if(!CLN) 
	CLN=cln;
      else
	CLNP->noeudSuiv=cln;

      CLNP=cln;
    }

    if(c=='a') {
      numn=GetEntier(f);
      numv=GetEntier(f);
      
      CelluleLNoeud *cln;
      int bidouille=0;
      for(cln=CLN; cln && bidouille<2 ;cln=cln->noeudSuiv) {
	if(cln->ptrnoeud) {
	  if(numn==cln->ptrnoeud->u) {
	    Voisin *vois=(Voisin*)malloc(sizeof(Voisin));
	    vois->v=numv;
	    
	    if(!cln->ptrnoeud->LVoisins)
	      cln->ptrnoeud->LVoisins=vois;
	    
	    else {
	      vois->voisSuiv=cln->ptrnoeud->LVoisins;
	      cln->ptrnoeud->LVoisins=vois;
	    }
	    bidouille++;
	  }

	  if(numv==cln->ptrnoeud->u) {
	    Voisin *vois=(Voisin*)malloc(sizeof(Voisin));
	    vois->v=numn;
	    
	    if(!cln->ptrnoeud->LVoisins)
	      cln->ptrnoeud->LVoisins=vois;
	    
	    else {
	      vois->voisSuiv=cln->ptrnoeud->LVoisins;
	      cln->ptrnoeud->LVoisins=vois;
	    }
	    bidouille++;
	  }
	}
      }
    }
    if(c=='k') {
      CelluleLCommodite *clc=(CelluleLCommodite*)malloc(sizeof(CelluleLCommodite)); clc->commSuiv=NULL;
      clc->extr1=GetEntier(f);
      clc->extr2=GetEntier(f);

      if(!CLC)
	CLC=clc;
      else
	CLCP->commSuiv=clc;

      CLCP=clc;
    }

    //else    
    // SkipLine(f);
  }
  r.LCommodites=CLC;
  r.LNoeuds=CLN;
  *R=r;
}










// Compte le nombre de cable utilisé dans le reseau
int compteCable(Reseau *R) {
  int cpt=0;
  CelluleLNoeud *cln=R->LNoeuds;
  for(;cln;cln=cln->noeudSuiv) {
    if(cln->ptrnoeud) {
      Voisin *vois=cln->ptrnoeud->LVoisins;
      for(;vois;vois=vois->voisSuiv) 
	cpt++;
    }
  }

  return (cpt/2);
}
   





  
// Ecrit le reseau sur le disque (format .res)
void ecrit_reseau_disque(Reseau *R, FILE *f) {
  if(!R) {
    fprintf(stderr,"Reseau non ini\n");
    exit(1);
  }
  CelluleLNoeud *cln=R->LNoeuds;
  fprintf(f,"c NbNodes: %d\n", R->nbNoeuds);
  fprintf(f,"c NbCables: %d\n", compteCable(R));
  fprintf(f,"c Gamma: %d\nc\n", R->gamma);
  for(;cln;cln=cln->noeudSuiv) {
    fprintf(f,"v %d %f %f\n",cln->ptrnoeud->u, cln->ptrnoeud->x, cln->ptrnoeud->y);
  }

  fprintf(f,"c\n");
  cln=R->LNoeuds;
  Voisin *vois;
  for(;cln;cln=cln->noeudSuiv) {
    vois=cln->ptrnoeud->LVoisins;
    for(;vois;vois=vois->voisSuiv) {
      fprintf(f,"a %d %d\n",cln->ptrnoeud->u,vois->v);
    }
  }

  fprintf(f,"c\n");
  CelluleLCommodite *clc=R->LCommodites;
  for(;clc;clc=clc->commSuiv) {
    fprintf(f,"k %d %d\n",clc->extr1,clc->extr2);
  }
}





// Ecrit le reseau sur le disque au format xfig (dessin)
void ecrit_reseau_xfig(Reseau *R,FILE *f,int zoom, int epaisseur){ 
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

  float i=0;
  CelluleLNoeud *cln=NULL;
  Voisin *v=NULL;
  Noeud *n=NULL;
  for(cln=R->LNoeuds;cln;cln=cln->noeudSuiv) {
    fprintf(f,"1 4 0 %d 0 7 50 0 -1 0.000 1 0.0000 %.0f %.0f 20 20 0 0 0 0\n",epaisseur,zoom*(cln->ptrnoeud->x),zoom*(cln->ptrnoeud->y));

    for(v=cln->ptrnoeud->LVoisins;v;v=v->voisSuiv) {
      n=cherche_noeud(R,v->v);
      if(n)
	fprintf(f,"2 1 1 %d 8 7 50 0 -1 %.000f 0 0 -1 0 0 2         \n%.0f %.0f %.0f %.0f\n",(int)epaisseur/2,fmod(i,4),zoom*cln->ptrnoeud->x,zoom*cln->ptrnoeud->y,zoom*n->x,zoom*n->y);
      i+=0.5;
    }
  }
}




// Cherche un noeud dans un réseau à partir de son numéro
Noeud *cherche_noeud(Reseau *R,int num){
  CelluleLNoeud *cln=R->LNoeuds;
  for(;cln;cln=cln->noeudSuiv) {
    if(cln->ptrnoeud->u==num)
      return cln->ptrnoeud;
  }
  printf("Noyau non trouvé\n");
  return NULL;
}




// Renvoie 0 si le noeud nd à comme voisin un noeud de numéro u
int recherche_Voisin(Noeud *nd, int u) {
  Voisin *v=nd->LVoisins;
  for(;v;v=v->voisSuiv)
    if(v->v==u) 
      return 0;
  return -1;
}




// Affiche le reseau r
void lecture_reseau(Reseau *R){
  if(R) {
    CelluleLNoeud *cln=R->LNoeuds;
    CelluleLCommodite *clc;
    Voisin *vois;
    int cpt=compteCable(R);
    printf("c NbNodes: %d\nc NbCables: %d\nc Gamma: %d\nc\n",R->nbNoeuds,cpt,R->gamma);
    
    
    for(cln=R->LNoeuds;cln;cln=cln->noeudSuiv)
      printf("v %d %lg %lg\n",cln->ptrnoeud->u,cln->ptrnoeud->x,cln->ptrnoeud->y);
    
    
    printf("c\n");
    
    for(cln=R->LNoeuds;cln;cln=cln->noeudSuiv) 
      for(vois=cln->ptrnoeud->LVoisins;vois;vois=vois->voisSuiv)
	printf("a %d %d\n",cln->ptrnoeud->u,vois->v);
    
    printf("c\n");
    
    for(clc=R->LCommodites;clc;clc=clc->commSuiv)
      printf("k %d %d\n",clc->extr1,clc->extr2);
  }
}
