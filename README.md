# Pokemon TCGP Battler

Ce projet est un projet de C++ dans le cadre du cours IN201. Il s'agit d'un simulateur de combats de Pokémon TCG Pocket. Il est également accompagné d'un scraper permettant de récupérer et d'adapter toutes les données nécessaires au jeu depuis le site [Limitles TCG](https://pocket.limitlesstcg.com).

## Installation

### Battler

Installez g++ et [SFML](https://www.sfml-dev.org/tutorials/3.0/getting-started/migrate/)  
Par exemple, sur Debian, utilisez :  
```shell
sudo apt-get install g++
sudo apt-get install libsfml-dev
```

Clonez le projet et rendez vous à sa racine (*./PROJETPOKEMON*). Utilisez le *Makefile* pour compiler, puis lancer le programme dans *build*.

```shell
make
./build/pokemon_game
```

### Scrapper

Installez *Node.js* et *npm* si besoin.
```shell
sudo apt-get update
sudo apt-get install nodejs npm
```
Rendez-vous dans le dossier *./src/db* et installez les dépendances, lancez le scrapper.

```shell
cd ./src/db
npm install
npm start
```

## Règles

Chaque joueur a un deck avec des cartes pokémon. Seul les pokémons dits de base peuvent être posés sur le terrain, les autre devront être placés via évolution. Le jeu se joue tour par tour.  
Chaque pokémon a des attaques, un type et des points de vie. Si ses points de vies tombent à 0, il est considéré *K.O.* et doit quitter le terrain. Pour attaquer, il doit avoir suffisament d'énergie du type correspondant (n'importe quelle énergie peut remplacer une énergie *Normale*/*Colorless*). Attaquer met fin au tour.  
Chaque joueur a un deck, une main avec des cartes qu'il peut jouer, un pokémon actif et un banc qui contient 1 à 3 pokémons. Au début de chaque tour, le joueur pioche une carte. Il peut ensuite choisir son action.
Au début du jeu, chaque joueur pioche 5 cartes (dont au moins un pokémon de base) et choisit son premier pokémon actif. Au premier tour, le joueur 1 ne peut pas attacher d'énergie ni attaquer.  
Liste des actions possible pendant un tour :
- Attacher une énergie aléatoire parmi les énergies du deck au pokémon actif (1 fois par tour).
- Évoluer un pokémon sur le terrain avec un pokémon dans la main. Le pokémon doit avoir été placé il y a au moins un tour, et chaque pokémon ne peut évoluer qu'un fois. Il faut que l'évolution "évolue" depuis le pokémon du terrain.
- Placer un pokémon de base sur le banc.
- Battre en retraite : remplacer la pokémon actif par un des pokémons du banc, en utilisant des énergies attachées au pokémon actif.
- Attaquer si le pokémon actif a assez d'énergie (met fin au tour).
- Finir le tour
Quand le pokémon actif de l'adversaire est mis K.O., le joueur gagne 1 point de victoire (2 si le pokémon portait la mention "ex"). Le premier jouer à 3 points gagne. L'adversaire doit remplacer son pokémon actif par l'un des pokémons de son banc. Si son banc est vide, il a perdu.


## Fonctionnalités

- Combats simples : attaque, retraite, évolution
- Gestion du système d'énergie
- Importation de cartes et de decks

### Création des decks

Les decks sont stockés dans *./src/db/data/decks/*, dans un fichier .json. Il faut choisir le ou les types d'énergies, et les cartes pokémons (voir l'exemple [deck2](./src/db/data/decks/deck2.json)), en s'assurant de mettre au moins un pokémonde base. Il faut ensuite modifier le deck d'un des joueurs dans le [main](./src/main.cpp).

### Pistes d'améliorations :

gestion des effets, ajout des cartes objets et supporters, création d'une IA, inputs graphiques, vérification de la validité des decks, choix du deck au lancement, attacher des énergies au pokémon du banc.

## Problèmes connus

Au moment de lancer le jeu, il peut arriver d'obtenir un *pure virtual method called*. Il faut attendre une dizaine de secondes avant de relancer. Il peut arriver de devoir répéter l'opération plusieurs fois.

## Crédits

Module JSON for Modern C++ de Niels Lohmann. License :

Copyright © 2013-2025 Niels Lohmann

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.