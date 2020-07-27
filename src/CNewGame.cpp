#include <queue>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>      // srand ()
#include <time.h>
#include <cctype>       // isdigit ()
#include <vector>
#include <sstream>
#include <climits>
#include <string>
#include <memory>       // shared_ptr <...>

using namespace std;

#include "CNewGame.h"

//==================================================================================
struct TFindChar {
  TFindChar ( const std::string & name )
  : m_Name (name)
  {}

  bool operator () ( const std::shared_ptr <CCharacter> & card )
  { return card->GetName () == m_Name; }

  private:
    std::string m_Name;
};
//==================================================================================
struct TFindCard {
  TFindCard ( const std::string & name )
  : m_Name (name)
  {}

    bool operator () ( const std::shared_ptr <CCard> & card )
    { return card->GetName () == m_Name; }

  private:
    std::string m_Name;
};
//==================================================================================
bool CNewGame::DoIt ( CInterface & m_Interface, bool ifLoad )
{
  if ( ifLoad )
    return LoadGame ( m_Interface);

  if ( ! Initialize () )
    return false;
  m_Interface.ChooseMode ();
  int res;

  std::string choice;
  getline ( std::cin, choice );

  while ( choice != "1" && choice != "2" )
  {
    m_Interface.Announcement (ANNOUN_INCORRECTCHOICE);
    std::getchar();
    m_Interface.ChooseMode ();
    getline ( std::cin, choice );
  }

  res = std::stoi (choice);
  m_Mode = ( res == 1 ) ? VS_PLAYER : VS_PC;
  Preparing ( m_Interface );

  return true;
}
//==================================================================================
bool CNewGame::LoadCards ( CInterface & m_Interface, std::ifstream & ifs, CPlayer & pl, bool cardsInGame )
{
  std::string line, word;

  std::getline ( ifs, line );
  std::stringstream ss ( line );
  if ( line != "0" )
  {
    while ( ss >> word )
    {
      auto it = find_if ( m_AllCards.begin(), m_AllCards.end(), [&]( std::shared_ptr <CCard> card )
                                                                    { return card->GetName () == word; } );
      if ( it == m_AllCards.end () )
      {
        m_Interface.Announcement ( "2. Haven't found " + word );
        std::getchar ();
        return false;
      }
      if ( cardsInGame )
        pl.m_CardsInGame.insert ( *it );
      else
        pl.m_PlayingCards.push_back ( *it );
    }
  }
  return true;
}
//==================================================================================
bool CNewGame::LoadWeapon ( std::ifstream & ifs, CPlayer & player )
{
  std::string line;
  std::getline ( ifs, line );
  if ( line == COLT )
  {
    player.m_ActiveCharacter->GetWeapon () = COLT;
    player.m_ActiveCharacter->SetDamage (1);
  }
  else
  {
    auto it = find_if ( m_AllCards.begin(), m_AllCards.end(), TFindCard (line) );
    if ( it == m_AllCards.end() )
      return false;
    player.m_ActiveCharacter->GetWeapon () = (*it)->GetName ();
    if ( (*it)->GetName () == SCHOFIELD ) player.m_ActiveCharacter->SetDamage (2);
    else if ( (*it)->GetName () == REMINGTON ) player.m_ActiveCharacter->SetDamage (3);
    else player.m_ActiveCharacter->SetDamage (1);
  }
  return true;
}
//==================================================================================
bool CNewGame::LoadCharacter ( std::ifstream & ifs, CPlayer & player, bool isActive )
{
  std::string line;
  std::getline ( ifs, line );
  auto it = find_if ( m_AllCharacters.begin (), m_AllCharacters.end (), TFindChar (line) );
  std::getline ( ifs, line );
  int health = std::stoi ( line );

  if ( it == m_AllCharacters.end ()
    || health < 0
    || health > HEALTHMAX )
    return false;
  if ( isActive )
  {
    player.m_ActiveCharacter = *it;
    player.m_ActiveCharacter->SetHealth(health);
  }
  else
  {
    player.m_PassiveCharacter = *it;
    player.m_PassiveCharacter->SetHealth(health);
    if ( !health )
      player.m_PassiveCharacter->SetAlive(false);
  }
  m_AllCharacters.erase ( it );

  return true;
}
//==================================================================================
bool CNewGame::LoadGame ( CInterface & m_Interface )
{
  std::ifstream ifs;
  std::string line;
  bool isActive = true;
  bool cardsInGame = true;
  bool turnPlayer = true;

  ifs.open ( PATH, std::ios::in );
  Initialize ();

  if ( ! ifs )
  {
    m_Interface.Announcement ( ANNOUN_SAVEDGAMECANTFIND );
    std::getchar ();
    return false;
  }

  std::getline ( ifs, line );
  if ( line != "VSPC" && line != "VSPLAYER" )
  {
    m_Interface.Announcement ( "mode" );
    std::getchar ();
    return false;
  }

  m_Mode = ( line == "VSPC" ) ? VS_PC : VS_PLAYER;

  std::string name1 = ( m_Mode == VS_PC ) ? PLAYER   : PLAYER1;
  std::string name2 = ( m_Mode == VS_PC ) ? COMPUTER : PLAYER2;

  CPlayer player1 (turnPlayer, name1), player2 (!turnPlayer, name2);
  if ( ! LoadCharacter ( ifs, player2, isActive )
    || ! LoadCharacter ( ifs, player2, !isActive )
    || ! LoadWeapon ( ifs, player2 )
    || ! LoadCards ( m_Interface, ifs, player2, cardsInGame )
    || ! LoadCards ( m_Interface, ifs, player2, !cardsInGame )
    || ! LoadCharacter ( ifs, player1, isActive )
    || ! LoadCharacter ( ifs, player1, !isActive )
    || ! LoadWeapon ( ifs, player2 )
    || ! LoadCards ( m_Interface, ifs, player1, cardsInGame )
    || ! LoadCards ( m_Interface, ifs, player1, !cardsInGame ) )
    return false;

  m_AllCharacters.clear();
  StartGame ( m_Interface, player1, player2 );
  return true;
}
//==================================================================================
bool CNewGame::LoadCardsDefinition ()
{
  std::ifstream ifs;
  std::string input;
  std::string name, hint;
  int health;

  ifs.open ( PATHDEFINITION, std::ios::in );
  if ( ! ifs )
    return false;

  std::getline ( ifs, input );
  int linesSize = std::stoi ( input );
  if ( linesSize < 4 )
    return false;
  while ( linesSize -- )
  {
    std::getline ( ifs, name );
    std::getline ( ifs, hint );
    std::getline ( ifs, input );
    health = std::stoi ( input );
    if ( health < 1 )
      return false;
    m_AllCharacters.push_back ( make_shared <CCharacter> ( health, name, hint ));
  }
  return true;
}
//==================================================================================
bool CNewGame::Initialize ()
{
  if ( ! LoadCardsDefinition () )
    return false;

  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, 2, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, 3, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, 4, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, 5, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, 6, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, 7, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, 8, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, 9, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, 10, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, JACK, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, QUEEN, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, KING, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( DIAMONDS, ACE, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( CLUBS, 2, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( CLUBS, 3, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( CLUBS, 4, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( CLUBS, 5, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( CLUBS, 6, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( CLUBS, 7, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( CLUBS, 8, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( CLUBS, 9, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( HEARTS, QUEEN, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( HEARTS, KING, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( HEARTS, ACE, 1, BROWN ) );
  m_AllCards.push_back ( make_shared <CBang> ( SPADES, ACE, 1, BROWN ) );

  m_AllCards.push_back ( make_shared <CMissed> ( CLUBS, 3, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( CLUBS, 10, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( CLUBS, QUEEN, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( CLUBS, KING, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( CLUBS, ACE, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( SPADES, 2, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( SPADES, 3, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( SPADES, 4, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( SPADES, 5, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( SPADES, 6, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( SPADES, 7, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CMissed> ( SPADES, 8, 0, BROWN ) );

  m_AllCards.push_back ( make_shared <CBeer> ( HEARTS, 6, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CBeer> ( HEARTS, 7, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CBeer> ( HEARTS, 8, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CBeer> ( HEARTS, 9, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CBeer> ( HEARTS, 10, 0, BROWN ) );
  m_AllCards.push_back ( make_shared <CBeer> ( HEARTS, JACK, 0, BROWN ) );

  m_AllCards.push_back ( make_shared <CCatBalou> ( HEARTS, KING, 6, BROWN ) );
  m_AllCards.push_back ( make_shared <CCatBalou> ( DIAMONDS, 8, 6, BROWN ) );
  m_AllCards.push_back ( make_shared <CCatBalou> ( DIAMONDS, 9, 6, BROWN ) );
  m_AllCards.push_back ( make_shared <CCatBalou> ( DIAMONDS, 10, 6, BROWN ) );

  m_AllCards.push_back ( make_shared <CGatling> ( HEARTS, 10, 5, BROWN ) );

  m_AllCards.push_back ( make_shared <CDynamite> ( HEARTS, 2, 7, BLUE ) );

  m_AllCards.push_back ( make_shared <CWeapon> ( SCHOFIELD, CLUBS, KING, 2, BLUE, 2 ) );
  m_AllCards.push_back ( make_shared <CWeapon> ( SCHOFIELD, SPADES, JACK, 2, BLUE, 2 ) );
  m_AllCards.push_back ( make_shared <CWeapon> ( REMINGTON, SPADES, QUEEN, 3, BLUE, 3 ) );
  m_AllCards.push_back ( make_shared <CWeapon> ( VOLCANIC, CLUBS, 10, 4, BLUE, 1 ) );
  return true;
}
//==================================================================================
void CNewGame::SaveGame ( CPlayer & atacker, CPlayer & victim )
{
  std::ofstream ofs ( PATH, ios::out );
  if ( ! ofs.is_open () )
  {
    ofs.close ();
    std::cout << "Sorry, it is imposible to save game." << std::endl;
    return;
  }

  std::string mode = ( m_Mode == VS_PLAYER ) ? "VSPLAYER" : "VSPC";
  ofs << mode << "\n";
  ofs << victim.m_ActiveCharacter->GetName () << "\n";
  ofs << victim.m_ActiveCharacter->GetHealth () << "\n";
  ofs << victim.m_PassiveCharacter->GetName () << "\n";
  ofs << victim.m_PassiveCharacter->GetHealth () << "\n";
  ofs << victim.m_ActiveCharacter->GetWeapon () << "\n";
  if ( ! victim.m_CardsInGame.size () ) ofs << "0" << '\n';
  else
  {
    for ( auto it = victim.m_CardsInGame.begin(); it != victim.m_CardsInGame.end(); it ++ )
      ofs << (*it)->GetName () << "\n";;
    ofs << "-" << '\n';
  }
  if ( ! victim.m_PlayingCards.size () ) ofs << "0";
  else
  {
    for ( auto it2 = victim.m_PlayingCards.begin(); it2 != victim.m_PlayingCards.end(); it2 ++ )
      ofs << (*it2)->GetName () << " ";
  } ofs << "\n";

  ofs << atacker.m_ActiveCharacter->GetName () << "\n";
  ofs << atacker.m_ActiveCharacter->GetHealth () << "\n";
  ofs << atacker.m_PassiveCharacter->GetName () << "\n";
  ofs << atacker.m_PassiveCharacter->GetHealth () << "\n";
  ofs << atacker.m_ActiveCharacter->GetWeapon () << "\n";
  if ( ! atacker.m_CardsInGame.size () ) ofs << "0" << '\n';
  else
  {
    for ( auto it = atacker.m_CardsInGame.begin(); it != atacker.m_CardsInGame.end(); it ++ )
    ofs << (*it)->GetName () << "\n";
    ofs << "-" << '\n';
  }
  if ( ! atacker.m_PlayingCards.size () ) ofs << "0";
  else
  {
    for ( auto it2 = atacker.m_PlayingCards.begin(); it2 != atacker.m_PlayingCards.end(); it2 ++ )
      ofs << (*it2)->GetName () << " ";
  } ofs << "\n";

  ofs.close ();
}
//==================================================================================
void CNewGame::ShuffleDeck ()
{
  size_t random;
  srand ( ( unsigned int ) ( time ( NULL ) / 2 ) );
  for ( size_t i = 0; i < m_AllCards.size(); i ++ )
  {
    random = i + ( rand () % ( m_AllCards.size() - i ) );
    swap ( m_AllCards[i], m_AllCards[random] );
  }
}
//==================================================================================
void CNewGame::GenerateCharacter ( vector < shared_ptr <CCharacter> > & out )
{
  srand ( ( unsigned int ) ( time ( NULL ) / 2 ) );
  random_shuffle ( m_AllCharacters.begin (), m_AllCharacters.end () );

  for ( int i = 0; i < 4; i ++ )
  {
    out.emplace_back ( m_AllCharacters.front () );
    m_AllCharacters.erase ( m_AllCharacters.begin() );
  }
}
//==================================================================================
void CNewGame::TakeCardFromDeck ( CPlayer & player )
{
  m_AllCards.emplace_back ( m_AllCards.front () );
  player.m_PlayingCards.emplace_back ( m_AllCards.front () );
  m_AllCards.erase ( m_AllCards.begin () );
}
//==================================================================================
void CNewGame::GiveCardsToPlayer ( CPlayer & player )
{
  int cardsNumber = player.m_ActiveCharacter->GetHealthCap ();
  for ( auto it = m_AllCards.begin(); cardsNumber; it ++, cardsNumber -- )
  {
    m_AllCards.emplace_back ( m_AllCards.front () );
    player.m_PlayingCards.emplace_back ( m_AllCards.front () );
    m_AllCards.erase ( m_AllCards.begin () );
  }
}
//==================================================================================
bool CNewGame::Round ( CInterface & m_Interface, CPlayer & atacker, CPlayer & victim )
{
  atacker.m_UsedBang = false;

  TakeCardFromDeck ( atacker );
  TakeCardFromDeck ( atacker );

  auto it = find_if ( atacker.m_CardsInGame.begin(), atacker.m_CardsInGame.end(), TFindCard (DYNAMITE) );
  if ( it != atacker.m_CardsInGame.end() )
  {
    m_Interface.DrawPlayZone ( atacker, victim, CHECKDYNAMITE, true );
    std::cin.ignore ( INT_MAX, '\n' );

    m_Interface.DrawPlayZone ( atacker, victim, TRYLUCK, true );
    std::cin.ignore ( INT_MAX, '\n' );
    if (    (*m_AllCards.begin())->GetSuit () == CLUBS
        &&  (  (*m_AllCards.begin())->GetNumber () >= 2
            && (*m_AllCards.begin())->GetNumber () <= 10 ) )
    {
      m_Interface.DrawPlayZone ( atacker, victim, DYNAMITEEXPLODES, true );
      std::cin.ignore ( INT_MAX, '\n' );
      if ( atacker.m_ActiveCharacter->GetHealth () <= 3 )
      {
        atacker.m_ActiveCharacter->SetHealth (0);
        atacker.m_ActiveCharacter->SetAlive(false);
        if ( ! atacker.m_PassiveCharacter->GetAlive () )
        return false;
        m_Interface.DrawPlayZone ( atacker, victim, CHARDEAD, true );
        std::cin.ignore ( INT_MAX, '\n' );
        swap ( atacker.m_ActiveCharacter, atacker.m_PassiveCharacter );
        atacker.m_ActiveCharacter->SetAlive(true);
        atacker.m_PassiveCharacter->SetAlive(false);
        return true;
      }
      atacker.m_ActiveCharacter->SetHealth ( atacker.m_ActiveCharacter->GetHealth() - 3 );
      m_Interface.DrawPlayZone ( atacker, victim, LOSEHEALTH, true );
      std::cin.ignore ( INT_MAX, '\n' );
    }
    else
    {
      m_Interface.DrawPlayZone ( atacker, victim, LUCKY, true );
      victim.m_CardsInGame.insert ( *it );
      atacker.m_CardsInGame.erase ( it );
      std::getchar();
    }
  }

  if ( ! atacker.m_ActiveCharacter->GetAlive() )
  {
    if ( ! atacker.m_PassiveCharacter->GetAlive() )
    return false;

    swap ( atacker.m_ActiveCharacter, atacker.m_PassiveCharacter );
    atacker.m_ActiveCharacter->SetAlive(true);
    atacker.m_PassiveCharacter->SetAlive(false);
  }

  int choice;

  while ( ( choice = m_Interface.CardUse ( atacker, victim ) ) )
  {
    if ( choice == 42 )
    {
      SaveGame ( atacker, victim );
      return false;
    }

    if ( atacker.m_PlayingCards[choice - 1]->Do ( m_Interface, atacker, victim ) )
    {
      atacker.m_PlayingCards.erase ( atacker.m_PlayingCards.begin () + choice - 1 );

      if ( ! victim.m_ActiveCharacter->GetAlive() )
      {
        if ( ! victim.m_PassiveCharacter->GetAlive() ) return false;

        swap ( victim.m_ActiveCharacter, victim.m_PassiveCharacter );
        victim.m_ActiveCharacter->SetAlive(true);
        victim.m_PassiveCharacter->SetAlive(false);
        return true;
      }

      m_Interface.DrawPlayZone ( atacker, victim, USECARD, true );
      if ( ! atacker.m_PlayingCards.size () )
      {
        m_Interface.DrawPlayZone ( atacker, victim, NOCARDS, true );
        usleep ( 2000000 );
        break;
      }
    }
    m_Interface.DrawPlayZone ( atacker, victim, USECARD, true );
  }

  while ( (int)atacker.m_PlayingCards.size () > atacker.m_ActiveCharacter->GetHealth() )
  m_Interface.DiscardCards ( atacker, victim );
  return true;
}
//==================================================================================
bool CNewGame::RoundPC ( CInterface & m_Interface, CPlayer & computer, CPlayer & player )
{
  computer.m_UsedBang = false;
  TakeCardFromDeck ( computer );
  TakeCardFromDeck ( computer );

  auto it = find_if ( computer.m_CardsInGame.begin(), computer.m_CardsInGame.end(), TFindCard (DYNAMITE) );
  if ( it != computer.m_CardsInGame.end() )
  {
    m_Interface.DrawPlayZone ( player, computer, CHECKDYNAMITEPC, true );
    std::getchar ();
    if (    (*m_AllCards.begin())->GetSuit() == CLUBS
         && (    (*m_AllCards.begin())->GetNumber() >= 2
              && (*m_AllCards.begin())->GetNumber() <= 10 ) )
    {
      m_Interface.DrawPlayZone ( player, computer, DYNAMITEEXPLODES, true );
      std::getchar ();
      if ( computer.m_ActiveCharacter->GetHealth() <= 3 )
      {
        computer.m_ActiveCharacter->SetHealth(0);
        computer.m_ActiveCharacter->SetAlive(false);
        if ( ! computer.m_PassiveCharacter->GetAlive() )
          return false;
        m_Interface.DrawPlayZone ( player, computer, CHARDEADPC, true );
        std::getchar ();
        swap ( computer.m_ActiveCharacter, computer.m_PassiveCharacter );
        computer.m_ActiveCharacter->SetAlive(true);
        computer.m_PassiveCharacter->SetAlive(false);
        return true;
      }
      computer.m_ActiveCharacter->SetHealth (computer.m_ActiveCharacter->GetHealth () - 3);
      m_Interface.DrawPlayZone ( player, computer, LOSEHEALTHPC, true );
      std::getchar ();
    }
    else
    {
      m_Interface.DrawPlayZone ( player, computer, LUCKYPC, true );
      player.m_CardsInGame.insert ( (*it) );
      computer.m_CardsInGame.erase ( it );
      std::getchar ();
    }
  }

  if ( ! computer.m_ActiveCharacter->GetAlive() )
  {
    if ( ! computer.m_PassiveCharacter->GetAlive() )
      return false;

    swap ( computer.m_ActiveCharacter, computer.m_PassiveCharacter );
    computer.m_ActiveCharacter->SetAlive(true);
    computer.m_PassiveCharacter->SetAlive(false);
  }

  size_t choice;
  while ( ( choice = m_Interface.CardUsePC ( computer, player ) ) )
  {
    if ( computer.m_PlayingCards[choice]->DoPC ( m_Interface, computer, player ) )
    {
      computer.m_PlayingCards[choice]->SetIsChecked(false);
      computer.m_PlayingCards.erase ( computer.m_PlayingCards.begin () + choice );
      if ( ! computer.m_ActiveCharacter->GetAlive() )
      {
        if ( ! computer.m_PassiveCharacter->GetAlive() ) return false;
        swap ( computer.m_ActiveCharacter, computer.m_PassiveCharacter );
        computer.m_ActiveCharacter->SetAlive(true);
        computer.m_PassiveCharacter->SetAlive(false);
        return true;
      }
      if ( ! computer.m_PlayingCards.size () )
      {
        m_Interface.DrawPlayZone ( player, computer, NOCARDSPC, true );
        std::getchar ();
        break;
      }
    }
  }

  while ( (int)computer.m_PlayingCards.size () > computer.m_ActiveCharacter->GetHealth() )
    m_Interface.DiscardCardsPC ( computer, player );
  return true;
}
//==================================================================================
void CNewGame::GamePL ( CInterface & m_Interface, CPlayer & player1, CPlayer & player2 )
{
  bool turnPlayer1 = true;
  while ( ( player2.m_ActiveCharacter->GetAlive() || player2.m_PassiveCharacter->GetAlive() )
       && ( player1.m_ActiveCharacter->GetAlive() || player1.m_PassiveCharacter->GetAlive() ) )
  {
    m_Interface.Announcement ( ANNOUN_CHANGEPLAYER );
    std::getchar ();
    if ( turnPlayer1 )
    {
      if ( ! Round ( m_Interface, player1, player2 ) )
        return;
    }
    else
      if ( ! Round ( m_Interface, player2, player1 ) )
        return;
    turnPlayer1 = !turnPlayer1;
  }
}
//==================================================================================
void CNewGame::GamePC ( CInterface & m_Interface, CPlayer & player, CPlayer & computer )
{
  bool turnPlayer = true;
  while ( ( computer.m_ActiveCharacter->GetAlive() || computer.m_PassiveCharacter->GetAlive() )
         && ( player.m_ActiveCharacter->GetAlive() || player.m_PassiveCharacter->GetAlive() ) )
  {
    if ( turnPlayer )
    {
      m_Interface.DrawPlayZone ( player, computer, PLTURN, true );
      std::getchar ();
      if ( ! Round ( m_Interface, player, computer ) )
        return;
    }
    else
    {
      m_Interface.DrawPlayZone ( player, computer, PCTURN, true );
      std::getchar ();
      if ( ! RoundPC ( m_Interface, computer, player ) )
        return;
    }
    turnPlayer = !turnPlayer;
  }
}
//==================================================================================
void CNewGame::StartGame ( CInterface & m_Interface, CPlayer & player1, CPlayer & player2 )
{
  ShuffleDeck ();
  m_Interface.DrawPlayZone ( player1, player2, START, true );
  std::getchar ();

  m_Interface.DrawPlayZone ( player1, player2, GETCARDS, true );
  std::getchar ();

  if ( m_Mode == VS_PC )
    GamePC ( m_Interface, player1, player2 );
  else
    GamePL ( m_Interface, player1, player2 );

  m_Interface.DrawPlayZone ( player1, player2, ENDOFGAME, true );
  player1.m_PlayingCards.clear ();
  player2.m_PlayingCards.clear ();
  player1.m_CardsInGame.clear ();
  player2.m_CardsInGame.clear ();
  m_AllCards.clear ();
  std::getchar ();
}
//==================================================================================
void CNewGame::Preparing ( CInterface & m_Interface )
{
  bool turnPlayer1 = true;
  bool withPlayer = true;
  int player1char1, player1char2, player2char1, player2char2;

  std::string name1 = ( m_Mode == VS_PC ) ? PLAYER   : PLAYER1;
  std::string name2 = ( m_Mode == VS_PC ) ? COMPUTER : PLAYER2;

  CPlayer player1 ( turnPlayer1, name1 ),
          player2 ( !turnPlayer1, name2 );

  std::vector <shared_ptr <CCharacter> > charactersToChoose;
  GenerateCharacter ( charactersToChoose );

  if ( m_Mode == VS_PC  )
  {
    m_Interface.ChooseCharacter ( charactersToChoose, CHOSECHAR1 );
    m_Interface.getCharacter ( charactersToChoose, !withPlayer, player1char1, player1char2, player2char1, player2char2 );
    m_Interface.ChooseActive ( charactersToChoose, player1char1, player2char1, player1.m_ActiveCharacter, player1.m_PassiveCharacter );
    player2.m_ActiveCharacter = charactersToChoose[player1char2];
    player2.m_PassiveCharacter = charactersToChoose[player2char2];
    player2.m_ActiveCharacter->SetActive(true);
  }
  else
  {
    m_Interface.getCharacter ( charactersToChoose, withPlayer, player1char1, player2char1, player1char2, player2char2 );
    m_Interface.ChooseActive ( charactersToChoose, player1char1, player1char2, player1.m_ActiveCharacter, player1.m_PassiveCharacter );
    m_Interface.ChooseActive ( charactersToChoose, player2char1, player2char2, player2.m_ActiveCharacter, player2.m_PassiveCharacter );
  }
  charactersToChoose.clear();
  m_AllCharacters.clear();

  m_Interface.DrawPlayZone ( player1, player2, START, true );
  std::getchar ();
  ShuffleDeck ();
  GiveCardsToPlayer ( player1 );
  GiveCardsToPlayer ( player2 );
  StartGame ( m_Interface, player1, player2 );
}
