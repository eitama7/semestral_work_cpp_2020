#pragma once

#include "../CCard.h"
#include "../constants.h"

#include <string>

/** Classes of cards have not got big implementation and will not be splited in '.cpp' and '.h' files. */

class CCatBalou : public CCard
{
  public:
    CCatBalou ( ESuit suit, int number, int priority, EColor color )
      : CCard ( CATBALOU, suit, number, priority, color )
    {}

    /**
    * PC's move. Randomly throw off one of card of opponent.
    *
    * @param[in, out] m_Interface Interaction with user.
    * @param[in, out] pl1 Represents player1.
    * @param[in, out] pl2 Represents player2.
    *
    * @return Returns false when there are not any cards in opponents vector and true if card was used.
    */
    virtual bool DoPC ( CInterface &, CPlayer &, CPlayer & );

    /**
    * Throw off one of card of opponent.
    *
    * @param[in, out] m_Interface Interaction with user.
    * @param[in, out] pl1 Represents player1.
    * @param[in, out] pl2 Represents player2.
    *
    * @return Returns false when there are not any cards in opponents vector and true if card was used.
    */
    virtual bool Do ( CInterface &, CPlayer &, CPlayer & );
};
