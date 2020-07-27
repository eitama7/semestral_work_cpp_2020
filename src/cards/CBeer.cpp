#include "CBeer.h"
#include "../CInterface.h"
#include <unistd.h>
#include <iostream>
#include <climits>

bool CBeer::Do ( CInterface & m_Interface, CPlayer & pl1, CPlayer & pl2 )
{
  m_Interface.DrawPlayZone ( pl1, pl2, BEERNOT, true );
  std::cin.ignore ( INT_MAX, '\n' );
  m_Interface.DrawPlayZone ( pl1, pl2, USECARD, true );
  return false;
}

bool CBeer::DoPC ( CInterface & m_Interface, CPlayer & pl1, CPlayer & pl2 )
{
  return false;
}
