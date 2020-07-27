#pragma once

#include "CNewGame.h"
#include "CHelp.h"
#include "CCommand.h"
#include "CInterface.h"

using namespace std;

/**
  * This class is a base of the whole progam.
  * It offers user to choose options.
  */
class CApplication
{
  public:
    /**
      * Constttructor to create the application.
      * Initialize the whole application.
      */
                   CApplication ();

    /**
      * Desuctor for cleaning up after finishing of work.
      */
    ~CApplication () = default;

    /**
      * Method runs the application.
      */
    void Run ();

  private:
    /** Variable which is responsible for all interactions with user. */
    CInterface m_Interface;

    /** Full up container with commands. */
    CApplication & InicializeStartMenu ();

    /** Vector with possible commands for choosing by user. */
    vector <unique_ptr <CCommand>> m_StartMenu;

    /** Written rules. */
    string m_Rules;
};
