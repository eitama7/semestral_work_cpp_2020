#include "CCatBalou.h"
#include "../CInterface.h"
#include "../CPlayer.h"

#include <unistd.h>
#include <iostream>
#include <string>
#include <climits>

bool CCatBalou::Do ( CInterface & m_Interface, CPlayer & pl1, CPlayer & pl2 )
{
  std::string choice;
  if ( ! pl2.m_PlayingCards.size() )
  {
    m_Interface.DrawPlayZone ( pl1, pl2, CATBALOUCANT, true );
    std::cin.ignore ( INT_MAX, '\n' );
    return false;
  }
  m_Interface.DrawPlayZone ( pl1, pl2, CATBALOUCHOSE, true );
  std::getline ( std::cin, choice );
  std::string possibleSize = std::to_string ( pl2.m_PlayingCards.size () );

  while ( choice < "1" || choice > possibleSize )
  {
    m_Interface.DrawPlayZone ( pl1, pl2, ANNOUN_INCORRECTCHOICE, true );
    std::cin.ignore ( INT_MAX, '\n' );
    m_Interface.DrawPlayZone ( pl1, pl2, CATBALOUCHOSE, true );
    std::getline ( std::cin, choice );
  }
  int res = std::stoi ( choice );

  pl2.m_PlayingCards.erase ( pl2.m_PlayingCards.begin () + res - 1 );
  m_Interface.DrawPlayZone ( pl1, pl2, "", true );
  return true;
}

bool CCatBalou::DoPC ( CInterface & m_Interface, CPlayer & pc, CPlayer & pl )
{
  if ( ! pl.m_PlayingCards.size() )
    return false;

  m_Interface.DrawPlayZone ( pl, pc, CATBALOUPC, true );
  std::getchar ();

  int choice = 0;
  srand ( ( unsigned int ) ( time ( NULL ) / 2 ) );
  while ( ! choice )
    choice = rand() % ( pl.m_PlayingCards.size () + 1 );

  pl.m_PlayingCards.erase ( pl.m_PlayingCards.begin () + choice - 1 );
  m_Interface.DrawPlayZone ( pl, pc, LOSTCARD, true );
  std::getchar ();
  return true;
}
