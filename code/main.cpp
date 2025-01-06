#include "pokemon.h"
#include "move.h"
#include <iostream>

/*int main() {

    Pokemon pikachu("Pikachu", 100,"electric");
    Pokemon charmander("Salamèche", 120, "fire");

    // Ajout des attaques
    pikachu.addMove(Move("Tonnerre", 50));
    pikachu.addMove(Move("Queue de Fer", 40));

    charmander.addMove(Move("Flammeche", 45));
    charmander.addMove(Move("Griffe", 35));

    // Combat simple
    while (!pikachu.isFainted() && !charmander.isFainted()) {
        std::cout << "\n--- Tour de Pikachu ---\n";
        Move chosenMove = pikachu.chooseMove();
        int damage = pikachu.attackWithMove(chosenMove);
        charmander.takeDamage(damage);

        if (charmander.isFainted()) {
            std::cout << charmander.getName() << " est K.O. !\n";
            break;
        }

        std::cout << "\n--- Tour de Salamèche ---\n";
        chosenMove = charmander.chooseMove();
        damage = charmander.attackWithMove(chosenMove);
        pikachu.takeDamage(damage);

        if (pikachu.isFainted()) {
            std::cout << pikachu.getName() << " est K.O. !\n";
            break;
        }
    }

    return 0;
}
*/

#include "GameRender.h"


int main() {
    Game game;
    game.run(); // Démarre la boucle principale du jeu
    return 0;
}