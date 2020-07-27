#pragma once

#include "../CCard.h"
#include "../constants.h"

#include <string>

/** Classes of cards have not got big implementation and will not be splited in '.cpp' and '.h' files. */

class CDynamite : public CCard
{
  public:
    CDynamite ( ESuit suit, int number, int priority, EColor color )
      : CCard ( DYNAMITE, suit, number, priority, color )
    {}

    /**
    * PC's move. Sets the Dynamite.
    *
    * @param[in, out] m_Interface Interaction with user.
    * @param[in, out] pl1 Represents player1.
    * @param[in, out] pl2 Represents player2.
    *
    * @return Returns always true.
    */
    virtual bool DoPC ( CInterface &, CPlayer &, CPlayer & );

    /**
    * Ask user if he sure he wants to set Dynamite - card wiith long effect.
    *
    * @param[in, out] m_Interface Interaction with user.
    * @param[in, out] pl1 Represents player1.
    * @param[in, out] pl2 Represents player2.
    *
    * @return Returns true if card was used and false if was not.
    */
    virtual bool Do ( CInterface &, CPlayer &, CPlayer & );
};
