#include "CGatling.h"
#include "../CInterface.h"
#include "../CPlayer.h"

#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <climits>

struct TFindBeer {
    TFindBeer ( const std::string & name )
      : m_Name (name)
    {}

    bool operator () ( const std::shared_ptr <CCard> & card )
    {
        return card->GetName() == m_Name;
    }

  private:
    std::string m_Name;
};

bool CGatling::SearchBeer ( CPlayer & pl )
{
  auto it = find_if ( pl.m_PlayingCards.begin(), pl.m_PlayingCards.end(), TFindBeer (BEER) );
  if ( it != pl.m_PlayingCards.end() )
  {
    pl.m_PlayingCards.erase ( it );
    return true;
  }
  return false;
}

bool CGatling::Do ( CInterface & m_Interface, CPlayer & pl1, CPlayer & pl2 )
{
  m_Interface.DrawPlayZone ( pl1, pl2, GATLINGACT, true );
  std::cin.ignore ( INT_MAX, '\n' );

  if ( pl2.m_ActiveCharacter->GetAlive() )
  {
    if ( pl2.m_ActiveCharacter->GetHealth() <= 1 )
    {
      if ( SearchBeer ( pl2 ) )
      {
        m_Interface.DrawPlayZone ( pl1, pl2, BEERUSED, true );
        std::getchar ();
      }
      else
      {
        pl2.m_ActiveCharacter->SetHealth(0);
        pl2.m_ActiveCharacter->SetAlive(false);
        m_Interface.DrawPlayZone ( pl1, pl2, KILLED, true );
        std::getchar ();
      }
    }
    else
      pl2.m_ActiveCharacter->SetHealth ( pl2.m_ActiveCharacter->GetHealth () - 1 );
  }

  if ( pl2.m_PassiveCharacter->GetAlive() )
  {
    if ( pl2.m_PassiveCharacter->GetHealth() <= 1 )
    {
      if ( SearchBeer ( pl2 ) )
      {
        m_Interface.DrawPlayZone ( pl1, pl2, BEERUSED, true );
        std::getchar ();
      }
      else
      {
        pl2.m_PassiveCharacter->SetHealth(0);
        pl2.m_PassiveCharacter->SetAlive(false);
        m_Interface.DrawPlayZone ( pl1, pl2, KILLED, true );
        std::getchar ();
      }
    }
    else
      pl2.m_PassiveCharacter->SetHealth ( pl2.m_PassiveCharacter->GetHealth () - 1 );
  }

  return true;
}

bool CGatling::DoPC ( CInterface & m_Interface, CPlayer & pc, CPlayer & pl )
{
  m_Interface.DrawPlayZone ( pl, pc, GATLINGACTPC, true );
  std::getchar ();

  if ( pl.m_ActiveCharacter->GetAlive() )
  {
    if ( pl.m_ActiveCharacter->GetHealth() <= 1 )
    {
      if ( SearchBeer ( pl ) )
      {
        m_Interface.DrawPlayZone ( pl, pc, BEERUSEDPC, true );
        std::getchar ();
      }
      else
      {
        pl.m_ActiveCharacter->SetHealth(0);
        pl.m_ActiveCharacter->SetAlive(false);
        m_Interface.DrawPlayZone ( pl, pc, KILLEDPC, true );
        std::getchar ();
      }
    }
    else pl.m_ActiveCharacter->SetHealth ( pl.m_ActiveCharacter->GetHealth () - 1 );
  }

  if ( pl.m_PassiveCharacter->GetAlive() )
  {
    if ( pl.m_PassiveCharacter->GetHealth() <= 1 )
    {
      if ( SearchBeer ( pl ) )
      {
        m_Interface.DrawPlayZone ( pl, pc, BEERUSEDPC, true );
        std::getchar ();
      }
      else
      {
        pl.m_PassiveCharacter->SetHealth(0);
        pl.m_PassiveCharacter->SetAlive(false);
        m_Interface.DrawPlayZone ( pl, pc, KILLEDPC, true );
        std::getchar ();
      }
    }
    else pl.m_PassiveCharacter->SetHealth ( pl.m_PassiveCharacter->GetHealth () - 1 );
  }
  return true;
}
