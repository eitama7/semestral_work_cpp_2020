#pragma once

#include <string>


/* Cards for playing */

const int JACK                             = 11;
const int QUEEN                            = 12;
const int KING                             = 13;
const int ACE                              = 14;
const int HEALTHMAX                        = 5;
//---------------------------------------------------------------------------------------------------------------

/* Define playing cards. */

const std::string CARD                     = "CARD";
const std::string BANG                     = "Bang!";
const std::string BEER                     = "Beer";
const std::string CATBALOU                 = "Cat_Balou";
const std::string GATLING                  = "Gatling";
const std::string MISSED                   = "Missed!";
const std::string DYNAMITE                 = "Dynamite";

/** Weapon.  */
const std::string COLT                     = "Colt";        // damage = 1
const std::string SCHOFIELD                = "Schofield";   // damage = 2
const std::string REMINGTON                = "Remington";   // damage = 3
const std::string VOLCANIC                 = "Volcanic";    // damage = 1, may play any number of BANG! cards during his turn.
//---------------------------------------------------------------------------------------------------------------

/* Define announcements and strings. */
const std::string ANNOUN_CHOOSE14          = "Choose please from 1 to 4.";
const std::string ANNOUN_CHOOSE12          = "Choose please from 1 to 2.";
const std::string ANNOUN_ERRORFINDINGRULES = "Sorry, can not find file with rules.";
const std::string ANNOUN_ERRORCREATINGGAME = "Sorry, can not find file with definition of cards and create new game.";
const std::string ANNOUN_ERRORLOADINGGAME  = "Sorry, can not find any saved games. Please create a new one.";
const std::string ANNOUN_INCORRECTCHOICE   = "Your choice is incorrect. Please choose one more time.";
const std::string ANNOUN_CHOSESECONDCHAR   = "Please choose the second character.";
const std::string ANNOUN_CHOSEACTIVE       = "Please choose 1 or 2 as your active character:";
const std::string ANNOUN_COMPCHOICE1       = "Computer's 1st choice is";
const std::string ANNOUN_COMPCHOICE2       = "Computer's 2nd choice is";
const std::string ANNOUN_PLAYERCHOICE1     = "Your 1st choice is";
const std::string ANNOUN_PLAYERCHOICE2     = "Your 2nd choice is";
const std::string ANNOUN_ACTIVECHARACTER   = "Your active character is ";
const std::string ANNOUN_CHANGEPLAYER      = "[ IT IS ANOTHER PLAYER'S TURN. DON'T LOOK AT HIS CARDS! PRESS ENTER ]";
const std::string ANNOUN_PLAYERSCHOOSE1    = "[ THE 1st PLAYER CHOOSES CHARACTER. PRESS ENTER ]";
const std::string ANNOUN_PLAYERSCHOOSE2    = "[ THE 2nd PLAYER CHOOSES CHARACTER. PRESS ENTER ]";
const std::string ANNOUN_SAVEDGAMECANTFIND = "Sorry. Can not find saved game.";
const std::string ANNOUN_LOADEDGAMEERROR   = "Sorry. Can not load saved game.";
//---------------------------------------------------------------------------------------------------------------

/* Strings for the menu. */
const std::string CHOSEMODE                = "Choose mode:";
const std::string CHOSECHAR1               = "Choose the first character:";
const std::string CHOSECHAR2               = "Choose the second character:";
const std::string PLVSPL                   = "[1] Player vs Player";
const std::string PLVSPC                   = "[2] Player vs PC";
const std::string PLAYER1                  = "PLAYER 1";
const std::string PLAYER2                  = "PLAYER 2";
const std::string PLAYER                   = " PLAYER ";
const std::string COMPUTER                 = "COMPUTER";
const std::string BOARDER                  = "--------------------------------------------------------------------------------";
const std::string SMALLBOARDER             = "------------";
const std::string NEWGAME                  = "[1] New game";
const std::string LOADGAME                 = "[2] Load game";
const std::string HELP                     = "[3] Help";
const std::string QUIT                     = "[4] Quit";
const std::string START                    = "[ Press ENTER to start the game ]";
const std::string GETCARDS                 = "[ Game starts. Press ENTER to get 2 more cards ]";
const std::string CHECKDYNAMITE            = "[ Press enter to check Dynamite ]";
const std::string CHECKDYNAMITEPC          = "[ Checking Dynamite ]";
const std::string USECARD                  = "[ Choose card | enter 0 to finish round | enter 42 to end the game ]";
const std::string NOCARDS                  = "[ You have no cards anymore. Now it is turn of your opponent ]";
const std::string NOCARDSPC                = "[ PC has no cards anymore. Now it is your turn ]";
const std::string PLTURN                   = "[ It is your turn now ]";
const std::string PCTURN                   = "[ It is PC turn now ]";
const std::string DISCARDCARD              = "[ Enter number of card you want to discard ]";
const std::string DISCARDCARDPC            = "[ PC chooses cards to discard ]";
const std::string CHANGEWEAPON             = "[ Do you really want to change weapon? [y]/[n] ]";
const std::string CHANGEWEAPONPC           = "[ PC changed weapon ]";
const std::string BANGACT                  = "[ Bang! is activated. Your opponent loses health! ]";
const std::string BANGACTPC                = "[ PC shooted you with Bang!. You lose health! ]";
const std::string GATLINGACT               = "[ Gatling is activated. All alive enemies will be shooted ]";
const std::string GATLINGACTPC             = "[ PC activated Gatling. All your alive characters will be shooted ]";
const std::string BANGUSED                 = "[ You can use Bang! only once in a round ]";
const std::string MISSEDUSED               = "[ Ha-ha! Your enemy used Missed! and you can not shot him ]";
const std::string MISSEDUSEDPC             = "[ Ha-ha! PC was trying to shoot you but you saved your life with Missed! ]";
const std::string BEERUSED                 = "[ Ha-ha! Your enemy drinked Beer and he is still alive! ]";
const std::string BEERUSEDPC               = "[ Ha-ha! PC was trying to kill you, but you saved your life drinked Beer ]";
const std::string BEERNOT                  = "[ It seems that you are alive. Don't drink when you don't need it ]";
const std::string MISSEDNOT                = "[ No one is shooting you. Don't use this card only because you want to ]";
const std::string KILLED                   = "[ You killed him! Gratulation! ]";
const std::string KILLEDPC                 = "[ Oops! PC killed your character ]";
const std::string CATBALOUCHOSE            = "[ Chose number of card of your opponent you want to throw off ]";
const std::string CATBALOUCANT             = "[ Your opponent has no cards. You can not use Cat Balou ]";
const std::string CATBALOUPC               = "[ PC uses Cat Balou and throws off randomly one of your cards ]";
const std::string LOSTCARD                 = "[ You lost one of your card ]";
const std::string DYNAMITEUSE              = "[ Do you want to add Dynamite in your cards? [y]/[n] ]";
const std::string DYNAMITEUSEPC            = "[ PC takes Dynamite ]";
const std::string CHARDEAD                 = "[ Your character is dead! ]";
const std::string CHARDEADPC               = "[ Character of PC is dead! ]";
const std::string DYNAMITEEXPLODES         = "[ Dynamite explodes! ]";
const std::string LOSEHEALTH               = "[ Your character loses 3 units of health! ]";
const std::string LOSEHEALTHPC             = "[ Character of PC loses 3 units of health! ]";
const std::string TRYLUCK                  = "[ If card from the deck is CLUBS and from 2 to 10, Dynamite will explode ]";
const std::string LUCKY                    = "[ You are lucky! Dynamite goes to your enemy ]";
const std::string LUCKYPC                  = "[ He is lucky! Dynamite goes to you ]";
const std::string ENDOFGAME                = "[ End of game! ]";

const std::string HEALTH                   = "health: ";
const std::string MAX                      = "max ";
const std::string SPACE                    = " ";
const std::string SPACE4                   = "    ";
const std::string SPACE5                   = "     ";
const std::string SPACE6                   = "      ";
const std::string SPACE11                  = "           ";
const std::string SPACE13                  = "             ";
const std::string SPACE16                  = "                ";
const std::string VERTICAL                 = "|";
const std::string NO1                      = "[1] ";
const std::string NO2                      = "[2] ";
const std::string NO3                      = "[3] ";
const std::string NO4                      = "[4] ";

/* Load and save game. */
const std::string PATH                     = "src/game/saved.txt";
const std::string PATHDEFINITION           = "src/characters/characters.txt";
const std::string RULES                    = "www.bang.cz/en/rules-and-faq/special-rules/60-rules-for-2-players.html";
