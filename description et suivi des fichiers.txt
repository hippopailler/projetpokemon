Ce petit document n'a comme unique vocation de suivre les fichiers que l'on créée.
Pour l'instant il ne se passe pas grand chose car je viens de créer le github


Update du 28/12 : 
- Etat : possibilité de créer des pokémons, de leur attribuer des attaques, de les faire combattre jusqu'au KO

- pokémon.cpp : création de la classe pokémon avec les attributs : nom, PV, type(encore initilisé mais tkt il est là)
    Présence de toutes les fonctions nécessaires pour le mini-jeu et notamment la récupération des données

- move : on va pas se mentir c'est assez bullshit mais ça code pour la classe 'move' ce qui permet d'ajouter facilement des attaques au pokemon

- main : 1) création des pokémon
2) ajout des attaques
3) système de tour par tour avec choix des attaques par le joueur jusqu'au KO


--> Il manque le système de type et donc de faiblesse et d'énergie pour justifier les différentes attaques.
--> Rien ne nous empêche d'attribuer aussi des types aux attaques : à voir