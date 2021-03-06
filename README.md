# Introduction à la RMN des liquides
 
Ce dépôt fournit l'ouvrage au format pdf qui était jusque-là disponible sur [http://eos.univ-reims.fr/LSD/JmnSoft/livre.pdf](http://eos.univ-reims.fr/LSD/JmnSoft/livre.pdf).

Les sources écrites en LaTeX se trouvent dans le dossier Livre. 

Le script d'assemblage a été créé sous Linux et utilise `make`.

Les codes sources des figures ont deux origines possibles, interne ou externe :
- interne
	- du code LaTeX (pstricks) insérés dans le texte, éventuellement faisant appel à des données numériques produites par du code écrit en Perl
- externes, en langage PostScript.
	- des spectres qui proviennent du logiciel GIFA (à présent non modifiables, désolé)
	- des schémas écrits directement en langage PostScript
	- des schémas produits par du code écrit en langage C et dont l'exécution produit du code en langage PostScript
	- des schémas produits par Gnuplot

Les figures au format eps sont disponibles dans le dossier EPS et ont été produites avec ps2eps.
Les figures au format pdf sont disponibles dans le dossier PDF et ont été produites avec ps2pdf.

Recréer le livre au format pdf à partir des fichiers sources se fait par la commande `make pdf`.

Il faut donc disposer
- de LaTeX (distribution TexLive) et des packages requis par livre.tex
- de make pour construite le fichier pdf final
- d'un compilateur C (gcc) pour fabriquer les binaires exécutables qui produisent du code PostScript
- de Perl pour produire des tables de valeurs numériques lues par le package pstricks de LaTeX
- de ps2eps pour que le code PostScript (.ps) des figures externes puisse être utilisé par LaTeX après transformation en fichier .eps
- éventuellement de Gnuplot pour recréer les graphes de contours et de surfaces dans le dossier ContSurf, directement produits au format eps.
