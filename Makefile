CC=gcc

# Les differents repertoires
DIRC=POINT_C
MAIN=$(DIRC)/MAIN
DIRH=POINT_H
DIRO=POINT_O
DIRBIN=bin

# Les éxecutables
BIN=menu dijkListe dijk creerR creerH creerA creerC creerL #main


# Les fichiers sources et objet
SRC=$(wildcard $(DIRC)/*.c)
OBJ=$(SRC:$(DIRC)/%.c=$(DIRO)/%.o)


# Option de compilation
CFLAGS=-Wall -O3
LDFLAGS= -lm

all: $(BIN)

# Regle
$(DIRO)/%.o: $(DIRC)/%.c $(DIRH)/%.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(DIRO)/%.o: $(MAIN)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)


# Création de l'exécutable
menu: $(OBJ) $(DIRO)/menu.o
	$(CC) -o $(DIRBIN)/$@ $^ $(LDFLAGS)

main: $(OBJ) $(DIRO)/main.o
	$(CC) -o $(DIRBIN)/$@ $^ $(LDFLAGS)

dijk: $(OBJ) $(DIRO)/main_dijk.o
	$(CC) -o $(DIRBIN)/$@ $^ $(LDFLAGS)

creerR: $(OBJ) $(DIRO)/creer_reseau.o
	$(CC) -o $(DIRBIN)/$@ $^ $(LDFLAGS)

creerH: $(OBJ) $(DIRO)/creer_reseau_hachage.o
	$(CC) -o $(DIRBIN)/$@ $^ $(LDFLAGS)

creerA: $(OBJ) $(DIRO)/creer_reseau_abr.o
	$(CC) -o $(DIRBIN)/$@ $^ $(LDFLAGS)

creerC: $(OBJ) $(DIRO)/creation_courbes.o
	$(CC) -o $(DIRBIN)/$@ $^ $(LDFLAGS)

creerL: $(OBJ) $(DIRO)/creer_liste.o
	$(CC) -o $(DIRBIN)/$@ $^ $(LDFLAGS)

dijkListe: $(OBJ) $(DIRO)/dijkListe.o
	$(CC) -o $(DIRBIN)/$@ $^ $(LDFLAGS)

efface:
	rm -f instance/*.res instance/*.fig instance/*~ *.ps

clean:
	rm -f $(DIRO)/*.o *~ $(DIRC)/*~ $(DIRH)/*~ $(MAIN)/*~


Clean: efface clean
	rm -f $(DIRBIN)/*
	clear

.PHONY : efface clean Clean