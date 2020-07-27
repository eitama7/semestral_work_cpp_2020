#pragma once

#include "CPlayer.h"
#include "CInterface.h"
#include "CCommand.h"
#include "CCharacter.h"
#include "CCard.h"

#include "cards/CBang.h"
#include "cards/CBeer.h"
#include "cards/CCatBalou.h"
#include "cards/CGatling.h"
#include "cards/CMissed.h"
#include "cards/CDynamite.h"

#include "constants.h"  // Suits for cards

/**
  * Variable defines which color every card has.
  */
enum EMode
{
  VS_PLAYER,
  VS_PC
};

/**
  * Class responding for starting new game o loading previous.
  */
class CNewGame : public CCommand
{
  public:
    /**
      * Default constructor creates the instance.
      */
    CNewGame () = default;

    /**
      * Depending on user's choice transfer control
      * to function for playing with player or with PC.
      *
      * @param[in, out] m_Interface Instance of class CInterface, gives methods forinteraction with user.
      * @param[in] ifLoad Tells if we need to load new game.
      *
      * @return Value means if launching was successful.
      */
    virtual bool DoIt     ( CInterface &, bool );

  private:
    /**
      * Pushing all cards for playing to vector m_AllCards.
      * Pushing all characters to vector m_AllCharacters.
      * There are used integers as JACK, QUEEN, KING and ACE from file 'constants.h' in a function.
      *
      * @return Returns true if definition of card was found and succefully loaded.
      */
    bool Initialize ();

    /**
      * Method puts optins for saving played game in games/game.txt
      *
      * @param[in, out] atacker presents one of players.
      * @param[in, out] victim presents one of players.
      */
    void SaveGame ( CPlayer &, CPlayer & );

    /**
      * Method takes optins for saving played game in games/game.txt
      *
      * @param[in, out] m_Interface Instance of class CInterface, gives methods for printing errors.
      *
      * @return Returns true in case loading was successful, returns false if was not.
      */
    bool LoadGame ( CInterface & );

    /**
      * Loading definition of characters.
      *
      * @return Returns true if definition of cards was succefully loaded.
      */
    bool LoadCardsDefinition ();

    /**
      * Method for reading cards from file for loading game.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] ifs File stream with all information about saved game.
      * @param[in, out] player Which player loads cards.
      * @param[in] cardsInGame Tells where we have to insert cards in.
      *
      * @return If loading was successful.
      */
    bool LoadCards ( CInterface &, std::ifstream &, CPlayer &, bool );

    /**
      * Loading character's options from file with saved game.
      *
      * @param[in, out] ifs Input file stream.
      * @param[in, out] player Player for what we are setting options.
      * @param[in] isActive Which character will get options: active or passive.
      *
      * @return Returns true if loading was successful.
      */
    bool LoadCharacter ( std::ifstream &, CPlayer &, bool );

    /**
      * Loading weapon options from file with saved game.
      *
      * @param[in, out] ifs Input file stream.
      * @param[in, out] player Player for what we are setting options.
      *
      * @return Returns true if loading was successful.
      */
    bool LoadWeapon ( std::ifstream &, CPlayer & );

    /**
      * Shuffle the deck before game starts.
      */
    void ShuffleDeck ();

    /**
      * Generate 4 characters for choosing by players.
      *
      * @param[in, out] out Vector for inserting characters for choosing by users.
      */
    void GenerateCharacter ( std::vector < std::shared_ptr <CCharacter> > & );

    /**
      * Takes card from the common deck and gives to player.
      *
      * @param[in, out] player Which player we are giving card.
      */
    void TakeCardFromDeck ( CPlayer & );

    /**
      * Game logic.
      * Round by round while at least one character of each player is alive.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] player1 Presents the first player.
      * @param[in, out] player2 Presents the second player.
      */
    void GamePL ( CInterface &, CPlayer &, CPlayer & );

    /**
      * Game logic.
      * Round by round while at least one character of each player is alive.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] player Presents player.
      * @param[in, out] computer Presents PC.
      */
    void GamePC ( CInterface &, CPlayer &, CPlayer & );

    /**
      * Makes a round for player.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] atacker Presents player.
      * @param[in, out] victim Presents PC.
      *
      * @return If one of characters is still alive and game can continue.
      */
    bool Round ( CInterface &, CPlayer & , CPlayer & );

    /**
      * Makes a round for PC.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] player Presents player.
      * @param[in, out] computer Presents PC.
      *
      * @return If one of characters is still alive and game can continue.
      */
    bool RoundPC ( CInterface &, CPlayer & , CPlayer & );

    /**
      * Give cards to player for starting game.
      *
      * @param[in,out] player Presents one player who will get cards.
      */
    void GiveCardsToPlayer ( CPlayer & );

    /**
      * Preparing cards for plaing.
      * Choosing characters, choosing active characters, starting game.
      *
      * Get ready for game:
      * 1) Show the playing zone.
      * 2) Shuffle the deck of cards.
      * 3) Each player gets cards for playing.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in] withPC Mode: vs player or vs PC.
      */
    void Preparing ( CInterface & );

    /**
      * Starts game in mode 'vs. PC' or 'vs. Player'.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] player1 Represents the first player.
      * @param[in, out] player2 Represents the second player.
      *
      */
    void StartGame ( CInterface &, CPlayer &, CPlayer & );

    /** Vector for random generation of characters to choose. */
    std::vector <std::shared_ptr <CCharacter> > m_AllCharacters;

    /** All playing cards. */
    std::vector <std::shared_ptr <CCard> > m_AllCards;

    /** Player vs Player or Player vs PC. */
    EMode m_Mode;
};
