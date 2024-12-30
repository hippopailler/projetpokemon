### Un type carte avec :
	- probablement un id unique pour la carte ? (str)
	- le nom de la carte (str)
	- peut-être le type de carte ? (enum pokemon/objet/supporter)(en fait si on fait des classes dérivées c'est peut être pas utile
Ensuite j'ai pas trop suivi les cours de c++ en vrai mais je pense qu'il faudrait faire des classes dérivées

Pour les types (plante, eau...) je propose une enum

### Carte -> carte pokémon avec :
	- PV (const str)
	- type (const enum type)
	- type faiblesse (const enum type)
	- les attaques (const vector attaques)
	- coût de retraite (const coutenergie)
	- stade d'évolution ? (const base/1/2, pq pas un enum)
	- pokemon depuis lequel il évolue ? (nom de la carte)
	- est ex ? (const bool)
	
### Carte -> carte objet avec :
	- effet

### Carte -> carte supporter avec :
	- effet

### attaque avec :
	- nom (str)
	- coût en énergie (peut être qu'il faudra un type énergie jsp)
	- dégâts (int)
	- éventuellement des effets (genre paralysie, dégâts spéciaux à la célébi)
	
pour gérer les effet le mieux ce serait peut être de faire un type effet mais je propose qu'on voit ça plus tard
si jamais on fait un type *énergie* (je pense que ce serait le plus pratique), je pense à un tableau dynamique d'enum energie, avec des fonctions de manipulations pour ajouter, retirer, vérifier si on a assez d'energie

### deck :
	- tableau dynamique de cartes
	- fonction mélange
	- fonction pioche

### main :
	- tableau dynamique de cartes
	- fonction pioche
	- fonction joue