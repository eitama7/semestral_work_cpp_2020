#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unistd.h>
#include <climits>

#include "CApplication.h"

CApplication::CApplication ()
  : m_Rules ("There are rules for this game.")
{
}

CApplication & CApplication::InicializeStartMenu ()
{
  m_StartMenu.push_back ( make_unique <CNewGame> () );
  m_StartMenu.push_back ( make_unique <CHelp> () );
  return *this;
}

void CApplication::Run ()
{
  InicializeStartMenu ();
  m_Interface.StartMenu ();
  std::string choice;
  bool loadGame = false;
  int res;

  getline ( std::cin, choice );
  while ( choice != "1" && choice != "2" && choice != "3" && choice != "4" )
  {
    m_Interface.Announcement (ANNOUN_INCORRECTCHOICE);
    std::getchar();
    m_Interface.StartMenu ();
    getline ( std::cin, choice );
  }

  res = std::stoi (choice);
  switch ( res )
  {
    case 1:
      loadGame = false;
      if ( ! m_StartMenu[0]->DoIt ( m_Interface, loadGame ) )
        m_Interface.Announcement ( ANNOUN_ERRORCREATINGGAME );
      break;

    case 2:
      loadGame = true;
      if ( ! m_StartMenu[0]->DoIt ( m_Interface, loadGame ) )
        m_Interface.Announcement ( ANNOUN_ERRORLOADINGGAME );
      break;

    case 3:
      loadGame = false;
      if ( ! m_StartMenu[1]->DoIt ( m_Interface, loadGame ) )
        m_Interface.Announcement ( ANNOUN_ERRORFINDINGRULES );
      break;

    case 4:
      return;

    default:
      return;
  }
}
