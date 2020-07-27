# Semestral work in C++
### RPG "Bang!" was made only for educational purposes.

To run the game compile the program with "**$make all**" and run the project with "**$run ./korshmar**".

This game allows you to choose game mode: '**vs player**'/'**vs PC**'. In both you have to choose 2 characters you want to play with and after choose active one.
After choosing you will get cards from the playing deck in amount how many points of health your active character does have.
In every round you can play cards '**Bang!**', '**Cat Balou**', '**Beer**', '**Dynamite**', '**Gatling**' or '**Missed!**'. Each of them has it's own effect.
* *Bang!*     - to shoot your enemy. Damage depends on kind of weapon: **Colt** = 1 / **Schofield** = 2 / **Remington** = 3 / **Volcanic** = 1, but there is unlimited usage of Bang! in a round.
* *Cat Balou* - to choose which card your opponent will lose.
* *Beer*      - to save your life and add one point of health when you are near to die.
* *Dynamite*  - after adding this card in your cards 'in a game' every round there will be trying a luck by checking a card from the deck with playing cards. If it has a suit and number we need, it won't explode and you will pass card Dynamite to next player (to your opponent), otherwise it expodes and you lose 3 points of health.
* *Gatling*   - to shoot all you enemies.
* *Missed!*   - to avoid of shooting by another player.

After killing both of opponent's characters you win.
