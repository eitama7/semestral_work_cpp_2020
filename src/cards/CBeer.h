#pragma once

#include "../CCard.h"
#include "../constants.h"

#include <string>

/** Classes of cards have not got big implementation and will not be splited in '.cpp' and '.h' files. */

class CBeer : public CCard
{
  public:
    CBeer ( ESuit suit, int number, int priority, EColor color )
      : CCard ( BEER, suit, number, priority, color )
    {}

    /**
      * Informates that this card can be used only when someone shootes in a character.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] pl1 Represents player1.
      * @param[in, out] pl2 Represents player2.
      *
      * @return Returns always false - this card will never be used by player, only when it is PC's turn
      */
    virtual bool Do ( CInterface &, CPlayer & , CPlayer & );

  /**
    * PC's move.
    *
    * @param[in, out] m_Interface Interaction with user.
    * @param[in, out] pc Represents PC.
    * @param[in, out] pl Represents player.
    *
    * @return Returns always false - this card will never be ussed by PC, only when it is Player's turn.
    */
    virtual bool DoPC ( CInterface &, CPlayer & , CPlayer & );
};
