#pragma once

#include "../CCard.h"
#include "../constants.h"

#include <string>

/**
  * Classes of card for shooting.
  */

class CBang : public CCard
{
  public:
    /**
      * Constructor call constructor of base class CCard.
      */
    CBang ( ESuit suit, int number, int priority, EColor color )
      : CCard ( BANG, suit, number, priority, color )
    {}

    /**
      * PC's move. Hiding all card information from user.
      * Shooting in active character of opponent.
      * Checking if weapon is Volcanic - character can shoot many taimes in one round.
      * Checking for card Missed! with which opponent can avoid of shooting.
      * Checking for card Beer! with which opponent can avoid of dying and stay alive.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] pc Represents PC.
      * @param[in, out] pl Represents player.
      *
      * @return Returns true if card was used - to erase it from vector of cards.
      */
    virtual bool DoPC ( CInterface &, CPlayer &, CPlayer & );

    /**
      * Player's move. Showing all card information of user. Interaction.
      * Shooting in active character of opponent.
      * Checking if weapon is Volcanic - character can shoot many taimes in one round.
      * Checking for card Missed! with which opponent can avoid of shooting.
      * Checking for card Beer! with which opponent can avoid of dying and stay alive.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] pl1 Represents player1.
      * @param[in, out] pl2 Represents player2.
      *
      * @return Returns true if card was used - to erase it from vector of cards.
      */
    virtual bool Do ( CInterface &, CPlayer &, CPlayer & );
};
