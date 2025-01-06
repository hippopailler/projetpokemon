#include "pokemon.h"
#include "move.h"
#include "energy.h"
#include "player.h"
#include "game.h"
#include <iostream>

int main() {

    Pokemon pikachu("Pikachu", 100, LIGHTING);
    Pokemon charmander("Salamèche", 120, FIRE);

        // Ajout des attaques
    std::vector<typeEnergy> thunderCost = {LIGHTING};
    pikachu.addMove(Move("Tonnerre", 50, thunderCost));
    pikachu.addMove(Move("Queue de Fer", 40));

    charmander.addMove(Move("Flammeche", 45));
    charmander.addMove(Move("Griffe", 35));

    Player player1(pikachu);
    Player player2(charmander);
    Game game(&player1, &player2);

    while (!pikachu.isFainted() && !charmander.isFainted()){
        game.chooseAction();
    }

/*
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
*/
    return 0;
}
