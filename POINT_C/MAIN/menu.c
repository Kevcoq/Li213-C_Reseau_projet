#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h>

// Nom des différentes extensions
char fig[5]=".fig\0",
  lfig[11]="_liste.fig\0",
  res[5]=".res\0",
  hach[13]="_hachage.res\0",
  abr[9]="_abr.res\0";


// Change l'extension de chaine par ext
char *changeExtension(char *chaine, char *ext) {
  char *string=strdup(chaine);

  int i=0, j=0;
  while(string[i]!='.' && string[i]!='\0')
    i++;
  
  while(ext[j]!='\0') {
    string[i]=ext[j];
    i++;
    j++;
  }
  string[i]='\0';
  return string;
}


// Suprimme le nom de l'instance pour laisser celui du dossier
char *supNom(char *chaine) {
  char *string=strdup(chaine);
  int i=0, j=0;
  while(string[i]!='\0') {
    if(string[i]=='/')
      j=i;
    i++;
  }
  
  string[j+1]='\0';
  return string;
}


/* Ne pouvant faire d'affectation dans le switch, chaque case renvoie vers une fonction */
 
void case1(char *nf) {
  char *pfig=changeExtension(nf, fig);
  execlp("./bin/creerL", "creerL", nf, pfig, NULL);
  printf("Fichier rendu : %s\n", pfig);
}

void case2(char *nf) {
  char 
    *pres=changeExtension(nf, res),
    *pfig=changeExtension(nf, fig);
  execlp("./bin/creerR", "creerR", nf, pres, pfig, NULL);
}

void case3(char *nf) {
  char 
    *pres=changeExtension(nf, hach),
    *pfig=changeExtension(pres, fig);
  execlp("./bin/creerH", "creerH", nf, pres, pfig, NULL);
}

void case4(char *nf) {
  char 
    *pres=changeExtension(nf, abr),
    *pfig=changeExtension(pres, fig);
  execlp("./bin/creerA", "creerA", nf, pres, pfig, NULL);
}

void case5(char *nf) {
  printf("Fichier rendu : courbes.txt,\t .fig, _liste.fig, .res, _hachage.res, _abr.res\n");
  execlp("./bin/creation_courbes.sh", "creation_courbes", nf, "courbes.txt", NULL);
}

void case6(char *nf) {
  char *dossier=supNom(nf);

  printf("Fichier rendu : courbes.txt,\t .fig, _liste.fig, .res, _hachage.res, _abr.res\n");
  execlp("./bin/creation_courbes.sh", "creation_courbes", dossier, "courbes.txt", NULL);
}


// Le menu

int main() {
  int choix;
  char *nf=(char*)malloc(sizeof(char)*128);
 
  printf("Bienvenu\n");
  printf("Veuillez saisir le nom du fichier .cha à lire\n");
  scanf("%s",nf);

  while(1) {
    printf("1 : Pour créer une figure avec une liste\n");
    printf("2 : Pour créer un réseau simple\n");
    printf("3 : Pour créer un réseau avec table de hachage\n");
    printf("4 : Pour créer un réseau avec ABRe\n");
    printf("5 : Pour créer un fichier des temps cpu de l'instance\n");
    printf("6 : Pour créer le fichier des temps cpu de l'ensemble\n");
    printf("7 : Quitter\n");

    scanf("%d",&choix);


    switch(choix) {
    case 1 :
      case1(nf);
      break;

    case 2 :
      case2(nf);
      break;

    case 3 :
      case3(nf);
      break;

    case 4 :
      case4(nf);
      break;

    case 5 :
      case5(nf);
      break;

    case 6 :
      case6(nf);
      break;


    default :
      return 0;
    }
  }
}
      
