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


## Fonctionnalités

- Combats simples : attaque, retraite, évolution
- Gestion du système d'énergie
- Importation de cartes et de decks

Pistes d'améliorations : gestion des effets, ajout des cartes objets et supporters, création d'une IA

## Crédits

Module JSON for Modern C++ de Niels Lohmann. License :

Copyright © 2013-2025 Niels Lohmann

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.