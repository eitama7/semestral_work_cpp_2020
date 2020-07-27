#include "CMissed.h"
#include "../CInterface.h"

#include <unistd.h>
#include <iostream>
#include <climits>

bool CMissed::Do ( CInterface & m_Interface, CPlayer & pl1, CPlayer & pl2 )
{
  m_Interface.DrawPlayZone ( pl1, pl2, MISSEDNOT, true );
  std::cin.ignore ( INT_MAX, '\n' );
  m_Interface.DrawPlayZone ( pl1, pl2, USECARD, true );
  return false;
}

bool CMissed::DoPC ( CInterface & m_Interface, CPlayer & pl1, CPlayer & pl2 )
{
  return false;
}
