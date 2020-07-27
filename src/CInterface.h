#pragma once
#include "CCharacter.h"
#include "CPlayer.h"
#include "constants.h"

class CInterface
{
  public:
    /**
      * Draws the start menu.
      */
    void StartMenu ();

    /**
      * Choosing mode : [Pl. vs Pl.] or [Pl. vs PC]
      */
    void ChooseMode ();

    /**
      * For CHelp call. Shows the rules of game.
      */
    void ShowRules ();

    /**
      * Mode vs Player.
      * Check users answers.
      *
      * @param[in, out] vec Vector with 4 characters for choosing.
      * @param[in] number What characters is being choosing: first or second.
      * @param[in] announ String that will be written for user.
      * @param[in] prevChoice1 Comparing with previous choice for validate input.
      * @param[in] prevChoice2 Comparing with previous choice for validate input.
      * @param[in] prevChoice3 Comparing with previous choice for validate input.
      *
      * @return Made choice.
      */
    int MakeChoicePC ( const std::vector < std::shared_ptr <CCharacter> > &, const std::string, const std::string, int, int, int );

    /**
      * Mode vs PC.
      * Generate answers.
      *
      * @param[in, out] vec Vector with 4 characters for choosing.
      * @param[in] number What characters is being choosing: first or second.
      * @param[in] announ String that will be written for user.
      * @param[in] prevChoice1 Comparing with previous choice for validate input.
      * @param[in] prevChoice2 Comparing with previous choice for validate input.
      * @param[in] prevChoice3 Comparing with previous choice for validate input.
      *
      * @return Made choice.
      */
    int MakeChoicePl ( const std::vector < std::shared_ptr <CCharacter> > &, const std::string, const std::string, int, int, int );

    /**
      * Get chosen character for Player1 and Player2.
      *
      * @param[in, out] vec Vector with characters to choose.
      * @param[in] withPlayer Which mode we have. Depending on it it will (not) write in output instructions for user.
      * @param[in, out] player1char1 Loading number of choice.
      * @param[in, out] player2char1 Loading number of choice.
      * @param[in, out] player1char2 Loading number of choice.
      * @param[in, out] player2char2 Loading number of choice.
      */
    void getCharacter ( const std::vector < std::shared_ptr <CCharacter> > &, bool, int &, int &, int &, int & );

    /**
      * Drawing asking menu for user - choosing characters.
      *
      * @param[in] vec Has all names and hints of characters for choosing.
      * @param[in] str First or second character we choose.
      */
    void ChooseCharacter ( const std::vector <std::shared_ptr <CCharacter> > &, const std::string str );

    /**
      * Printing message.
      *
      * @param[in] str What message will be printed.
      */
    void Announcement ( const std::string );

    /**
      * Show cards of opponent in hidden mode.
      *
      * @param[in, out] pl Who owns cards.
      */
    void ShowHiddenCards ( CPlayer & );

    /**
      * Show cards that player owns in open mode.
      *
      * @param[in, out] pl Who owns cards.
      */
    void ShowCards ( CPlayer & );

    /**
      * Show cards that player has in a game - with long effect.
      *
      * @param[in, out] pl Who owns cards.
      */
    void ShowCardsInGame ( CPlayer & );

    /**
      * Choose active and passive characters.
      *
      * @param[in, out] vec Vector with characters to choose.
      * @param[in] idx1 Where is each character in vector vec
      * @param[in] idx2 Where is each character in vector vec
      * @param[in, out] active Here will be loaded active character.
      * @param[in, out] passive Here will be loaded active character.
      */
    void ChooseActive ( std::vector <std::shared_ptr <CCharacter> > &, int, int, std::shared_ptr <CCharacter> &, std::shared_ptr <CCharacter> & );


    /**
      * Method for discarding cards in mode vs PC when their number is bigger than current health.
      *
      * @param[in, out] pc Presents PC.
      * @param[in, out] pl Presents player.
      */
    void   DiscardCardsPC  ( CPlayer &, CPlayer & );

    /**
      * Method for discarding cards in mode vs Player when their number is bigger than current health.
      *
      * @param[in, out] pl1 Presents player1.
      * @param[in, out] pl2 Presents player2.
      */
    void   DiscardCards    ( CPlayer &, CPlayer & );

    /**
      * Checks users input and get number of chosen card.
      *
      * @param[in, out] pl1 Presents player1.
      * @param[in, out] pl2 Presents player2.
      *
      * @return Returns number of chosen card.
      */
    int    CardUse         ( CPlayer &, CPlayer & );

    /**
      * Comparing priority of cards and choose ine for playing.
      *
      * @param[in, out] pc Presents PC.
      * @param[in, out] pl Presents player.
      *
      * @return Returns number of chosen card.
      */
    int    CardUsePC       ( CPlayer &, CPlayer & );

    /**
      * Draws plaing zone.
      *
      * @param[in, out] pl1 Presents player1.
      * @param[in, out] pl2 Presents player2.
      * @param[in] str What message will be printed in a center of playing zone.
      * @param[in] turnPlayer Desides which player's cards will be shown.
      */
    void DrawPlayZone ( CPlayer &, CPlayer &, const std::string, bool );
};
