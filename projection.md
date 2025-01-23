### Un type carte avec :
- probablement un id unique pour la carte ? (str)
- le nom de la carte (str)
- peut-être le type de carte ? (enum pokemon/objet/supporter)(en fait si on fait des classes dérivées c'est peut être pas utile)
- rareté ???
Ensuite j'ai pas trop suivi les cours de c++ en vrai mais je pense qu'il faudrait faire des classes dérivées

Pour les types (plante, eau...) je propose une enum

### Carte -> carte pokémon avec :
- En paramètres :
	- PV (const str)
	- type (const enum type)
	- type faiblesse (const enum type)
	- les attaques (const vector attaques)
	- coût de retraite (const coutenergie)
	- stade d'évolution ? (const base/1/2, pq pas un enum)
	- pokemon depuis lequel il évolue ? (nom de la carte)
	- est ex ? (const bool)
 	- Les énergies attachées (liste d'énergie)
 	- Peut être enregistrer le tour de pose/un bool peut évoluer 
 - En fonctions :
 	- Accesseurs
  	- Récupérer les pv max (void => void)
 	- Prendre des dégats : nombre de dégats (int) + type des dégâts (const type) => void
  	- Soin : montant du soin (const int) => void
   	- Attacher énergie (énergie => void)
   	- Détacher énergie (liste énergie/énergie ? => void)
   	- Vérification si peut utiliser une attaque (attaque => bool)

	
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
si jamais on fait un type *énergie* (je pense que ce serait le plus pratique), je pense à un tableau dynamique d'enum energie, avec des fonctions de manipulations pour ajouter, retirer, vérifier si on a assez d'energie. ok en fait après réflexion on fait un type énergie

### Energie :

On fait une enum avec tous les types d'énergie. Pour représenter un montant d'énergie, on pourra faire un tableau, et du coup energie\[eau\] ce sera un entier qui correspont au nb d'énergie eau.
Ensuite une fonction pour ajouter une énergie, une fonction pour enlever une énergie, une fonction pour enlever plusieurs énergies, une fonction pour vérifier si on a assez d'énergie pour faire un truc
En fait j'ai reréfléchi et plutôt qu'un tableau il vaudrait mieux utiliser un *dictionnaire* (sparkles), ce sera carrément mieux non ?

### deck :
- tableau dynamique de cartes
- fonction mélange
- fonction pioche

### main :
- tableau dynamique de cartes
- fonction pioche
	- fonction joue

### Comportement de l'IA (tema l'IA facile type TCG, tranquille)
oui oui tkt on va faire une turbo ia qui
- si a un pokemon de base dans la main et de la place sur le terrain, joue
- si peut faire évoluer un pokemon,

## Gestion des tours :

Je propose de faire une classe game, avec comme variables le numéro du tour, le numéro du joueur actuel, et les données des deux joueurs. Du coup il faudrait une autre classe, joueur, avec un deck, une main, un pokemon actif, un banc, le nombre de points de vicoires.

### Joueur :
- En paramètres:
	- Deck (deck)
	- Main (tableau dynamique de cartes)
	- Pokémon actif (carte pokemon)
	- Banc (liste de cartes pokemon)
	- Points de victoire (int)   
- En fonctions :
	- Mélanger le deck
	- Piocher
	- Changer de pokemon actif
	- Prendre/soigner des dégâts
	- Toutes les manipulation d'énergie
	- Gain de points de victoire

### Game :
- En paramètres :
	- Numéro tour (int)
	- Numéro du joueur actuel (0/1)
	- Tableau taille fixe des 2 joueurs
 - En fonctions :
	- Pioche
	- Attaque
	- Fin du tour
	- Attacher une énergie
	- Poser un pokémon
	- Retraite
	- Gestion de la fin de game
