#include "CBang.h"
#include "../CInterface.h"
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <climits>

struct TFindCard {
    TFindCard ( const std::string & name )
      : m_Name (name)
    {}

    bool operator () ( const std::shared_ptr <CCard> & card )
    {
        return card->GetName() == m_Name;
    }

  private:
    std::string m_Name;
};

bool CBang::Do ( CInterface & m_Interface, CPlayer & pl1, CPlayer & pl2 )
{
  /** With weapon named Volcanic character has no limited using Bang! */
  if ( pl1.m_UsedBang && pl1.m_ActiveCharacter->GetWeapon() != VOLCANIC )
  {
    m_Interface.DrawPlayZone ( pl1, pl2, BANGUSED, true );
    std::getchar ();
    return false;
  }

  pl1.m_UsedBang = true;

  /** If opponent has card Missed!, he can avoid of being shooted. */
  auto it = find_if ( pl2.m_PlayingCards.begin(), pl2.m_PlayingCards.end(), TFindCard (MISSED) );
  if ( it != pl2.m_PlayingCards.end() )
  {
    pl2.m_PlayingCards.erase ( it );
    m_Interface.DrawPlayZone ( pl1, pl2, MISSEDUSED, true );
    std::getchar ();
    return true;
  }

  pl2.m_ActiveCharacter->SetHealth ( pl2.m_ActiveCharacter->GetHealth() - pl1.m_ActiveCharacter->GetDamage() );

  if ( pl2.m_ActiveCharacter->GetHealth() <= 0 )
  {
    /** If enemy has a beer to save his life. */
    auto it2 = find_if ( pl2.m_PlayingCards.begin(), pl2.m_PlayingCards.end(), TFindCard (BEER) );
    if ( it2 != pl2.m_PlayingCards.end() )
    {
      pl2.m_PlayingCards.erase ( it2 );
      pl2.m_ActiveCharacter->SetHealth(1);
      m_Interface.DrawPlayZone ( pl1, pl2, BEERUSED, true );
      std::getchar ();
      return true;
    }
    pl2.m_ActiveCharacter->SetHealth(0);
    pl2.m_ActiveCharacter->SetAlive(false);
    m_Interface.DrawPlayZone ( pl1, pl2, KILLED, true );
    std::getchar ();
    return true;
  }
  m_Interface.DrawPlayZone ( pl1, pl2, BANGACT, true );
  std::getchar ();

  return true;
}
//--------------------------------------------------------------------------------
bool CBang::DoPC ( CInterface & m_Interface, CPlayer & pc, CPlayer & pl )
{
  if ( pc.m_UsedBang && pc.m_ActiveCharacter->GetWeapon() != VOLCANIC )
    return false;

  pc.m_UsedBang = true;

  auto it = find_if ( pl.m_PlayingCards.begin(), pl.m_PlayingCards.end(), TFindCard (MISSED) );
  if ( it != pl.m_PlayingCards.end() )
  {
    pl.m_PlayingCards.erase ( it );
    m_Interface.DrawPlayZone ( pl, pc, MISSEDUSEDPC, true );
    std::getchar ();
    return true;
  }

  pl.m_ActiveCharacter->SetHealth ( pl.m_ActiveCharacter->GetHealth () - pl.m_ActiveCharacter->GetDamage() );

  if ( pl.m_ActiveCharacter->GetHealth() <= 0 )
  {
    auto it2 = find_if ( pl.m_PlayingCards.begin(), pl.m_PlayingCards.end(), TFindCard (BEER) );
    if ( it2 != pl.m_PlayingCards.end() )
    {
      pl.m_PlayingCards.erase ( it2 );
      pl.m_ActiveCharacter->SetHealth(1);
      m_Interface.DrawPlayZone ( pl, pc, BEERUSEDPC, true );
      return true;
      std::getchar ();
    }
    pl.m_ActiveCharacter->SetHealth(0);
    pl.m_ActiveCharacter->SetAlive(false);
    m_Interface.DrawPlayZone ( pl, pc, KILLEDPC, true );
    std::getchar ();
    return true;
  }
  m_Interface.DrawPlayZone ( pl, pc, BANGACTPC, true );
  std::getchar ();

  return true;
}
