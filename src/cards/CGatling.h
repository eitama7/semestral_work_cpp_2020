#pragma once

#include "../CCard.h"
#include "../constants.h"

#include <string>

/** Classes of cards have not got big implementation and will not be splited in '.cpp' and '.h' files. */

class CGatling : public CCard
{
  public:
    CGatling ( ESuit suit, int number, int priority, EColor color )
      : CCard ( GATLING, suit, number, priority, color )
    {}


    /**
      * PC's move. Shooting in all alive characters of opponent.
      * Checking for Beer - this card can help to opponent to avoid of dying and add 1 health.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] pc Represents PC.
      * @param[in, out] pl Represents player.
      *
      * @return Returns always true.
      */
    virtual bool DoPC       ( CInterface &, CPlayer &, CPlayer & );

    /**
      * Player's move. Shooting in all alive characters of opponent.
      * Checking for Beer - this card can help to opponent to avoid of dying and add 1 health.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] pc Represents PC.
      * @param[in, out] pl Represents player.
      *
      * @return Returns always true.
      */
    virtual bool Do         ( CInterface &, CPlayer &, CPlayer & );

    /**
      * Helper function for checking beer in opponent's cards.
      *
      * @param[in, out] pl Represents a player we are searching cards in.
      *
      * @return Returns true if Beer was found.
      */
            bool SearchBeer ( CPlayer & );
};
