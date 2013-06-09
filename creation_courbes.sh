#! /bin/bash
# creation_res
#set -x

if [ $# -ne 2 ];then
    echo 2 solutions avec rep ou avec un fichier : 
    echo 1 : Il faut entrer l\'emplacement du dossier des instances
    echo 1bis : Il aut entret l\'emplacement du fichier .cha
    echo 2 : Il faut entrer le nom du fichier de sauvegarde des courbes
    exit 1
fi

if [ -f $2 ];then
    rm -f $2;fi

make creerC
rm -f $1*.res *~
cpt=0

if [ -f $1 ];then
    if [ ${1##*.} = 'cha' ];then
	cpt=`expr 1 + $cpt`
	./bin/creerC $1 ${1%.*}.res ${1%.*}_hachage.res ${1%.*}_abr.res ${1%.*}_liste.fig ${1%.*}.fig `cat $1 | wc -l` > $2
    else
	echo Le fichier n\'a pas l\'extension .cha
	exit 1
    fi

else
    if [ -d $1 ];then
	cpt=0
	echo "Ce script va prendre qques minutes (environ 3)."
	for fic in `ls $1*.cha`;do
	    cpt=`expr 1 + $cpt`
	    ./bin/creerC $fic ${fic%.*}.res ${fic%.*}_hachage.res ${fic%.*}_abr.res ${fic%.*}_liste.fig ${fic%.*}.fig `cat $fic | wc -l`
	done > $2

    else
	echo Le parametre 1 n\'est ni un fichier .cha, ni un dossier.
	exit 1
    fi
fi
#gnuplot commande.txt
echo $cpt fichier traité.