#pragma once

#include "../CCard.h"
#include "../constants.h"

#include <string>

/** Classes of cards have not got big implementation and will not be splited in '.cpp' and '.h' files. */

class CMissed : public CCard
{
  public:
    CMissed ( ESuit suit, int number, int priority, EColor color )
      : CCard ( MISSED, suit, number, priority, color )
    {}

    /**
      * Player's move. Informates that user can not use this card by himself. Only in PC turn.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] pc Represents PC.
      * @param[in, out] pl Represents player.
      *
      * @return Returns always false - this card will never be used by PC, only when it is Player's turn.
      */
    virtual bool Do ( CInterface &, CPlayer &, CPlayer & );

    /**
      * PC's move. Nothing happens. This card will never be used because of priority = 0.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] pc Represents PC.
      * @param[in, out] pl Represents player.
      *
      * @return Returns always false - this card will never be used by PC, only when it is Player's turn.
      */
    virtual bool DoPC ( CInterface &, CPlayer &, CPlayer & );
};
