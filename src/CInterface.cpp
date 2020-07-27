#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>
#include <unistd.h>
#include <string>
#include <memory>
#include <climits>

#include "CInterface.h"

//==============================================================================================================
void CInterface::StartMenu ()
{
  system ("clear");
  size_t fill;

  std::cout << BOARDER << std::endl;
  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  fill = 38 + NEWGAME.size() / 2;
  std::cout << VERTICAL << std::setw (fill) << NEWGAME << std::setw (79 - fill) << VERTICAL << std::endl;
  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  fill = 38 + LOADGAME.size() / 2;
  std::cout << VERTICAL << std::setw (fill) << LOADGAME << std::setw (79 - fill) << VERTICAL << std::endl;
  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL    << std::setw (79) << VERTICAL << std::endl;
  fill = 38 + HELP.size() / 2;
  std::cout << VERTICAL << std::setw (fill) << HELP << std::setw (79 - fill) << VERTICAL << std::endl;
  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL    << std::setw (79) << VERTICAL << std::endl;
  fill = 38 + QUIT.size() / 2;
  std::cout << VERTICAL << std::setw (fill) << QUIT << std::setw (79 - fill) << VERTICAL << std::endl;
  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL    << std::setw (79) << VERTICAL << std::endl;
  std::cout << BOARDER << std::endl;
}
//==============================================================================================================
void CInterface::ChooseMode ()
{
  system ("clear");
  size_t fill;

  std::cout << BOARDER << std::endl;
  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL     << std::setw (79) << VERTICAL << std::endl;
  fill = 38 + CHOSEMODE.size() / 2;
  std::cout << VERTICAL << std::setw (fill) << CHOSEMODE << std::setw (79 - fill) << VERTICAL << std::endl;
  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL     << std::setw (79) << VERTICAL << std::endl;
  fill = 38 + PLVSPL.size() / 2;
  std::cout << VERTICAL << std::setw (fill) << PLVSPL << std::setw (79 - fill) << VERTICAL << std::endl;
  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL     << std::setw (79) << VERTICAL << std::endl;
  fill = 38 + PLVSPC.size() / 2;
  std::cout << VERTICAL << std::setw (fill) << PLVSPC << std::setw (79 - fill) << VERTICAL << std::endl;
  for (int i = 0; i < 7; i ++ )
    std::cout << VERTICAL     << std::setw (79) << VERTICAL << std::endl;
  std::cout << BOARDER << std::endl;
}
//==============================================================================================================
void CInterface::ShowRules ()
{
  Announcement( RULES );
  std::getchar ();
}
//==============================================================================================================
void CInterface::Announcement ( const std::string str )
{
  system ("clear");
  std::cout << BOARDER << std::endl;
  for (int i = 0; i < 8; i ++ )
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  size_t tmp = 38 + str.size() / 2;
  std::cout << VERTICAL   << std::setw(tmp) << str << std::setw(79-tmp) << VERTICAL << std::endl;
  for (int i = 0; i < 10; i ++ )
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << BOARDER << std::endl;
}
//==============================================================================================================
int CInterface::MakeChoicePl ( const std::vector < std::shared_ptr <CCharacter> > & vec, const std::string number,
                                                                                   const std::string announ,
                                                                                            int prevChoice1,
                                                                                            int prevChoice2,
                                                                                            int prevChoice3 )
{
  std::string input;
  ChooseCharacter (vec, number);
  std::getline ( std::cin, input );
  while ( ( input != "1" && input != "2" && input != "3" && input != "4" )
         || input == std::to_string (prevChoice1)
         || input == std::to_string (prevChoice2)
         || input == std::to_string (prevChoice3) )
  {
    Announcement (ANNOUN_INCORRECTCHOICE);
    std::getchar ();
    ChooseCharacter (vec, number);
    getline ( std::cin, input );
  }
  int choice = std::stoi ( input );
  Announcement ( announ + " " + vec[choice-1]->GetName () + "." );
  vec[choice-1]->SetTaken (true);
  std::cin.ignore ( INT_MAX, '\n' );
  return choice;
}
//==============================================================================================================
int CInterface::MakeChoicePC ( const std::vector < std::shared_ptr <CCharacter> > & vec, const std::string number,
                                                                                   const std::string announ,
                                                                                            int prevChoice1,
                                                                                            int prevChoice2,
                                                                                            int prevChoice3 )
{
  int choice = 0;
  ChooseCharacter (vec, number);
  srand ( ( unsigned int ) ( time ( NULL ) / 2 ) );

  while ( ! choice
         || choice == prevChoice1
         || choice == prevChoice2
         || choice == prevChoice3 )
    choice = rand() % 5;

  Announcement ( announ + " " + vec[choice-1]->GetName () + ".");
  vec[choice-1]->SetTaken (true);
  std::cin.ignore ( INT_MAX, '\n' );
  return choice;
}
//==============================================================================================================
void CInterface::getCharacter ( const std::vector < std::shared_ptr <CCharacter> > & vec, bool withPlayer,
                                                                                       int & player1char1,
                                                                                       int & player2char1,
                                                                                       int & player1char2,
                                                                                       int & player2char2 )
{
  if ( withPlayer )
  {
    Announcement (ANNOUN_PLAYERSCHOOSE1);
    std::cin.ignore ( INT_MAX, '\n' );
  }
  player1char1 = MakeChoicePl ( vec, CHOSECHAR1, ANNOUN_PLAYERCHOICE1, 0, 0, 0 );

  if ( withPlayer )
  {
    Announcement (ANNOUN_PLAYERSCHOOSE2);
    std::getchar ();
    player2char1 = MakeChoicePl ( vec, CHOSECHAR1, ANNOUN_PLAYERCHOICE1, player1char1, 0, 0 );
  }
  else
    player2char1 = MakeChoicePC ( vec, CHOSECHAR1, ANNOUN_COMPCHOICE1, player1char1, 0, 0 );

  if ( withPlayer )
  {
    Announcement (ANNOUN_PLAYERSCHOOSE1);
    std::getchar ();
  }
  player1char2 = MakeChoicePl ( vec, CHOSECHAR2, ANNOUN_PLAYERCHOICE2, player1char1, player2char1, 0 );

  if ( withPlayer )
  {
    Announcement (ANNOUN_PLAYERSCHOOSE2);
    std::getchar ();
    player2char2 = MakeChoicePl ( vec, CHOSECHAR2, ANNOUN_PLAYERCHOICE2, player1char1, player2char1, player1char2 );
  }
  else
    player2char2 = MakeChoicePC ( vec, CHOSECHAR2, ANNOUN_COMPCHOICE2, player1char1, player2char1, player1char2 );

  player1char1 --;
  player2char1 --;
  player1char2 --;
  player2char2 --;
}
//==============================================================================================================
void CInterface::ChooseCharacter ( const std::vector <std::shared_ptr <CCharacter> > & vec, const std::string str )
{
  char prev;
  std::string isTaken;
  system ("clear");
  std::cout << BOARDER << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (30) << str << std::setw (49) << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
//------------------------------------------------------------------------------
  std::cout << VERTICAL;
  std::cout.width (6);
  prev = std::cout.fill (' ');
  isTaken = vec[0]->GetTaken () ? "x " : "  ";
  std::cout << isTaken << NO1 << vec[0]->GetName ();
  std::cout.fill (prev);
  int tmp = 69 - vec[0]->GetName ().size();
  std::cout << std::setw (tmp) << VERTICAL << std::endl;

  std::cout << VERTICAL + SPACE6;
  tmp = 73 - vec[0]->GetHint ().size ();
  std::cout << vec[0]->GetHint () << std::setw(tmp) << VERTICAL << std::endl;
//------------------------------------------------------------------------------
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;

  std::cout << VERTICAL;
  std::cout.width (6);
  prev = std::cout.fill (' ');
  isTaken = vec[1]->GetTaken () ? "x " : "  ";
  std::cout << isTaken << NO2 << vec[1]->GetName ();
  std::cout.fill (prev);
  tmp = 69 - vec[1]->GetName ().size();
  std::cout << std::setw (tmp) << VERTICAL << std::endl;

  std::cout << VERTICAL + SPACE6;
  tmp = 73 - vec[1]->GetHint ().size();
  std::cout << vec[1]->GetHint () << std::setw(tmp) << VERTICAL << std::endl;
//------------------------------------------------------------------------------
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;

  std::cout << VERTICAL;
  std::cout.width (6);
  prev = std::cout.fill (' ');
  isTaken = vec[2]->GetTaken () ? "x " : "  ";
  std::cout << isTaken << NO3 << vec[2]->GetName ();
  std::cout.fill (prev);
  tmp = 69 - vec[2]->GetName ().size();
  std::cout << std::setw (tmp) << VERTICAL << std::endl;

  std::cout << VERTICAL + SPACE6;
  tmp = 73 - vec[2]->GetHint ().size();
  std::cout << vec[2]->GetHint () << std::setw(tmp) << VERTICAL << std::endl;
//------------------------------------------------------------------------------
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;

  std::cout << VERTICAL;
  std::cout.width (6);
  prev = std::cout.fill (' ');
  isTaken = vec[3]->GetTaken () ? "x " : "  ";
  std::cout << isTaken << NO4 << vec[3]->GetName ();
  std::cout.fill (prev);
  tmp = 69 - vec[3]->GetName ().size();
  std::cout << std::setw (tmp) << VERTICAL << std::endl;

  std::cout << VERTICAL + SPACE6;
  tmp = 73 - vec[3]->GetHint ().size();
  std::cout << vec[3]->GetHint () << std::setw(tmp) << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << BOARDER << std::endl;
}
//==============================================================================================================
void CInterface::ChooseActive ( std::vector <std::shared_ptr <CCharacter> > & vec, int idx1, int idx2,
                                                                std::shared_ptr <CCharacter> & active,
                                                                std::shared_ptr <CCharacter> & passive )
{
  system ("clear");
  std::cout << BOARDER << std::endl;
  for (int i = 0; i < 6; i ++ )
    std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << VERTICAL << SPACE16 + ANNOUN_CHOSEACTIVE + SPACE16 << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << VERTICAL << SPACE16 + SPACE13 + NO1 << vec[idx1]->GetName () << std::setw (46 - vec[idx1]->GetName ().size() ) << VERTICAL << std::endl;
  std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << VERTICAL << SPACE16 + SPACE13 + NO2 << vec[idx2]->GetName () << std::setw (46 - vec[idx2]->GetName ().size() ) << VERTICAL << std::endl;
  for (int i = 0; i < 7; i ++ )
    std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  std::cout << BOARDER << std::endl;

  std::string choice;
  std::getline ( std::cin, choice );
  while ( choice != "1" && choice != "2" )
  {
    Announcement ( ANNOUN_CHOOSE12 );
    std::getline ( std::cin, choice );
  }

  if ( choice == "2" )
  {
    active = vec[idx2];
    passive = vec[idx1];
  }
  else
  {
    active = vec[idx1];
    passive = vec[idx2];
  }
  Announcement ( ANNOUN_ACTIVECHARACTER + active->GetName () );
  active->SetActive (true);
}
//==============================================================================================================
void CInterface::ShowHiddenCards ( CPlayer & pl )
{
  unsigned int namesSize = 0, fill = 0;
  unsigned int cardsCount = pl.m_PlayingCards.size ();

  namesSize = cardsCount * 8;

  fill = ( 79 - namesSize ) / ( cardsCount + 1 );
  std::cout << VERTICAL;
  std::string color;
  for ( size_t i = 0; i < cardsCount; i ++ )
  {
    for (size_t j = 0; j < fill; j ++ )
      std::cout << ' ';
    std::cout << '[' << i+1 << "] " << CARD;
  }
  std::cout << std::setfill (' ') << std::setw (79 - fill*cardsCount - namesSize ) << VERTICAL << std::endl;
}
//==============================================================================================================
void CInterface::ShowCards ( CPlayer & pl )
{
  unsigned int namesSize = 0, fill = 0;
  unsigned int cardsCount = pl.m_PlayingCards.size ();

  for ( size_t i = 0; i < cardsCount; i ++ )
    namesSize += ( pl.m_PlayingCards[i]->GetName ().size () + 4 );  // "[i] " in each string.

  if (namesSize == 79)
    namesSize = 78;

  fill = ( 79 - namesSize ) / ( cardsCount + 1 );
  std::cout << VERTICAL;
  std::string color;
  for ( size_t i = 0; i < cardsCount; i ++ )
  {
    color = pl.m_PlayingCards[i]->GetColor () ? "\033[;34m" : "\033[;33m";
    for (size_t j = 0; j < fill; j ++ )
      std::cout << ' ';
    std::cout << color << '[' << i+1 << "] " << pl.m_PlayingCards[i]->GetName ();
    std::cout << "\033[0m";
  }
  std::cout << std::setfill (' ') << std::setw (79 - fill*cardsCount - namesSize  ) << VERTICAL << std::endl;
}
//==============================================================================================================
void CInterface::ShowCardsInGame ( CPlayer & pl )
{
  unsigned int namesSize = 0, fill = 0;
  unsigned int cardsCount = pl.m_CardsInGame.size ();
  std::string color = "\033[;34m";

  if ( pl.m_CardsInGame.size () )
  {
    for ( auto it = pl.m_CardsInGame.begin(); it != pl.m_CardsInGame.end(); it ++ )
      namesSize += ( (*it)->GetName ().size() ); // "[i] " in each string.
  }

  fill = ( 79 - namesSize ) / ( cardsCount + 1 );
  std::cout << VERTICAL;

  auto it = pl.m_CardsInGame.begin();
  for ( size_t i = 0; i < cardsCount; i ++ )
  {
    for ( size_t j = 0; j < fill; j ++ )
      std::cout << ' ';
    std::cout << color << (*it++)->GetName ();
    std::cout << "\033[0m";
  }
  std::cout << std::setfill (' ') << std::setw (79 - fill*cardsCount - namesSize  ) << VERTICAL << std::endl;
}
//==============================================================================================================
void CInterface::DiscardCards ( CPlayer & pl1, CPlayer & pl2 )
{
  int res;
  std::string choice = "";
  std::string possibleSize = std::to_string ( pl1.m_PlayingCards.size () );
  DrawPlayZone ( pl1, pl2, DISCARDCARD, true );
  std::getline ( std::cin, choice );

  while ( choice.length () != 1 || choice < "1" || choice > possibleSize )
  {
    DrawPlayZone ( pl1, pl2, ANNOUN_INCORRECTCHOICE, true );
    std::cin.ignore ( INT_MAX, '\n' );
    DrawPlayZone ( pl1, pl2, DISCARDCARD, true );
    std::getline ( std::cin, choice );
  }

  res = std::stoi ( choice );
  pl1.m_PlayingCards.erase ( pl1.m_PlayingCards.begin () + res - 1 );
}
//==============================================================================================================
void CInterface::DiscardCardsPC ( CPlayer & pc, CPlayer & pl )
{
  DrawPlayZone ( pl, pc, DISCARDCARDPC, true );
  std::getchar ();
  int min = 8;
  auto iter = pc.m_PlayingCards.begin ();

  for ( auto it = pc.m_PlayingCards.begin(); it != pc.m_PlayingCards.end(); it ++ )
  {
    if ( (*it)->GetPriotity () < min )
    {
      min = (*it)->GetPriotity ();
      iter = it;
    }
  }
  pc.m_PlayingCards.erase ( iter );
}
//==============================================================================================================
struct TFindCard {
    TFindCard ( const std::string & name )
      : m_Name (name)
    {}

    bool operator () ( const std::shared_ptr <CCard> & card )
    { return card->GetName () == m_Name; }

  private:
    std::string m_Name;
};
//==============================================================================================================
int CInterface::CardUsePC ( CPlayer & pc, CPlayer & pl )
{
  int max = 0;
  auto iter = pc.m_PlayingCards.begin ();

  for ( auto it = pc.m_PlayingCards.begin(); it != pc.m_PlayingCards.end(); it ++ )
  {
    if ( !( (*it)->GetIsChecked () ) && (*it)->GetPriotity () > max )
    {
      max = (*it)->GetPriotity ();
      iter = it;
    }
  }
  if ( ! max )
    return max;

  (*iter)->SetIsChecked (true);
  return iter - pc.m_PlayingCards.begin ();
}
//==============================================================================================================
int CInterface::CardUse ( CPlayer & pl1, CPlayer & pl2 )
{
  std::string choice = "";
  std::string possibleSize = std::to_string ( pl1.m_PlayingCards.size () );
  DrawPlayZone ( pl1, pl2, USECARD, true );
  std::getline ( std::cin, choice );

  while ( choice < "0" || ( choice > possibleSize && choice != "42" ) )
  {
    DrawPlayZone ( pl1, pl2, ANNOUN_INCORRECTCHOICE, true );
    std::cin.ignore ( INT_MAX, '\n' );
    DrawPlayZone ( pl1, pl2, USECARD, true );
    std::getline ( std::cin, choice );
  }
  return std::stoi ( choice );
}
//==============================================================================================================
void CInterface::DrawPlayZone ( CPlayer & pl1, CPlayer & pl2, const std::string str, bool turnPlayer )
{
  system ("clear");
  std::string color;
  std::cout << BOARDER << std::endl;
  std::cout << VERTICAL << SPACE16 << SPACE16 << "\033[1;37m" << VERTICAL << SPACE << pl2.m_Name << SPACE << VERTICAL << "\033[0m" << SPACE16 << SPACE16<< SPACE << SPACE << VERTICAL << std::endl;
  std::cout << VERTICAL << SPACE16 << SPACE16 << "\033[1;37m" << SMALLBOARDER << "\033[0m" << SPACE16 << SPACE16 << SPACE << SPACE << VERTICAL << std::endl;
  color = pl2.m_PassiveCharacter->GetAlive () ? "\033[0m" : "\033[;30m"; // white : black
  std::cout << VERTICAL << "\033[1;31m" << std::setw (26) << pl2.m_ActiveCharacter->GetName () << "\033[0m" << color << std::setw (39) << pl2.m_PassiveCharacter->GetName () << "\033[0m" << std::setw (14) << VERTICAL << std::endl;
  std::cout << VERTICAL + SPACE5 + HEALTH << pl2.m_ActiveCharacter->GetHealth () << SPACE6 << SPACE << MAX + HEALTH << pl2.m_ActiveCharacter->GetHealthCap ();
  std::cout << SPACE11 + HEALTH << pl2.m_PassiveCharacter->GetHealth () << SPACE6 << SPACE << MAX + HEALTH << pl2.m_PassiveCharacter->GetHealthCap () << SPACE4 + VERTICAL << std::endl;
  size_t tmp = ( 79 + pl2.m_ActiveCharacter->GetWeapon ().size () ) / 2;
  std::cout << VERTICAL << "\033[1;34m" << std::setw (tmp) <<  pl2.m_ActiveCharacter->GetWeapon () << "\033[0m" << std::setw (79-tmp) <<  VERTICAL << std::endl;
  ShowCardsInGame ( pl2 );
  ShowHiddenCards ( pl2 );

  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
  tmp = 39 + str.size() / 2;
  std::cout << VERTICAL << std::setw (tmp) << str << std::setw (79-tmp) << VERTICAL << std::endl;
  for (int i = 0; i < 3; i ++ )
    std::cout << VERTICAL << std::setw (79) << VERTICAL << std::endl;
    
  ShowCards ( pl1 );
  ShowCardsInGame ( pl1 );
  tmp = ( 79 + pl1.m_ActiveCharacter->GetWeapon ().size () ) / 2;
  std::cout << VERTICAL << "\033[1;34m" << std::setw (tmp) << pl1.m_ActiveCharacter->GetWeapon () << "\033[0m" << std::setw (79-tmp) <<  VERTICAL << std::endl;
  std::cout << VERTICAL + SPACE5 + HEALTH << pl1.m_PassiveCharacter->GetHealth () << SPACE6 << SPACE << MAX + HEALTH << pl1.m_PassiveCharacter->GetHealthCap ();
  std::cout << SPACE11 + HEALTH << pl1.m_ActiveCharacter->GetHealth () << SPACE6 << SPACE << MAX + HEALTH << pl1.m_ActiveCharacter->GetHealthCap () << SPACE4 + VERTICAL << std::endl;
  color = pl1.m_PassiveCharacter->GetAlive () ? "\033[0m" : "\033[;30m";
  std::cout << VERTICAL << color << std::setw (25) << pl1.m_PassiveCharacter->GetName () << "\033[1;31m" << std::setw (40) << pl1.m_ActiveCharacter->GetName () << "\033[0m" << std::setw (14) << VERTICAL << std::endl;
  std::cout << VERTICAL << SPACE16 << SPACE16 << "\033[1;37m" << SMALLBOARDER << "\033[0m" << SPACE16 << SPACE16 << SPACE << SPACE << VERTICAL << std::endl;
  std::cout << VERTICAL << SPACE16 << SPACE16 << "\033[1;37m" << VERTICAL << SPACE << pl1.m_Name << SPACE << VERTICAL << "\033[0m" << SPACE16 << SPACE16<< SPACE << SPACE << VERTICAL << std::endl;
  std::cout << BOARDER << std::endl;
}
