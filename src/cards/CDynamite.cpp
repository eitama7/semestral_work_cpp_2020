#include "CDynamite.h"
#include "../CInterface.h"
#include <iostream>
#include <set>
#include <climits>
#include <memory>
#include <string>
#include <unistd.h>

bool CDynamite::Do ( CInterface & m_Interface, CPlayer & pl1, CPlayer & pl2 )
{
  std::string choice;
  m_Interface.DrawPlayZone ( pl1, pl2, DYNAMITEUSE, true );
  std::getline ( std::cin, choice );

  while ( choice != "y" && choice != "n" )
  {
    m_Interface.DrawPlayZone ( pl1, pl2, ANNOUN_INCORRECTCHOICE, true );
    std::cin.ignore ( INT_MAX, '\n' );
    m_Interface.DrawPlayZone ( pl1, pl2, DYNAMITEUSE, true );
    std::getline ( std::cin, choice );
  }
  if ( choice == "y" )
  {
    pl1.m_CardsInGame.insert ( std::make_shared <CDynamite> (*this) );
    return true;
  }
  return false;
}

bool CDynamite::DoPC ( CInterface & m_Interface, CPlayer & pc, CPlayer & pl )
{
  std::string choice;
  m_Interface.DrawPlayZone ( pl, pc, DYNAMITEUSEPC, true );
  std::getchar ();

  pc.m_CardsInGame.insert ( std::make_shared <CDynamite> (*this) );
  return true;
}
