#include "CWeapon.h"
#include "CInterface.h"
#include <unistd.h>
#include <climits>
#include <string>
#include <iostream>

bool CWeapon::Do ( CInterface & m_Interface, CPlayer & pl1, CPlayer & pl2 )
{
  std::string answer;
  m_Interface.DrawPlayZone ( pl1, pl2, CHANGEWEAPON, true );
  std::getline ( std::cin, answer );

  while ( answer != "y" && answer != "n" )
  {
    m_Interface.DrawPlayZone ( pl1, pl2, ANNOUN_INCORRECTCHOICE, true );
    std::cin.ignore ( INT_MAX, '\n' );
    m_Interface.DrawPlayZone ( pl1, pl2, CHANGEWEAPON, true );
    std::getline ( std::cin, answer );
  }
  if ( answer == "y" )
  {
    pl1.m_ActiveCharacter->SetWeapon ( GetName () );
    pl1.m_ActiveCharacter->SetDamage ( GetDamage() );
    return true;
  }
  return false;
}

bool CWeapon::DoPC ( CInterface & m_Interface, CPlayer & pc, CPlayer & pl )
{
  pc.m_ActiveCharacter->SetWeapon ( GetName() );
  pc.m_ActiveCharacter->SetDamage ( GetDamage() );
  m_Interface.DrawPlayZone ( pl, pc, CHANGEWEAPONPC, true );
  std::getchar ();
  return true;
}
