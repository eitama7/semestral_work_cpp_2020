#pragma once
#ifndef CPLAYER_H
#define CPLAYER_H

#include <memory>
#include <vector>
#include <set>

#include "CCard.h"
#include "CCharacter.h"

/**
  * Class presents one player. Each player has 2 characters for playing.
  */

class CPlayer
{
  public:
    /**
      * Constructor creats an instance of player and set name and turn.
      *
      * @param[in] turn If player goes first in a game.
      * @param[in] name Sets player's name.
      */
    CPlayer ( bool turn, const std::string name )
      : m_UsedBang           (false),
        m_Turn               (turn),
        m_Name               (name),
        m_ActiveCharacter    (nullptr),
        m_PassiveCharacter   (nullptr)
    {}

    /** If card Bang! was already used in a round. */
         bool                              m_UsedBang;

    /** If it is my turn in a game. */
         bool                              m_Turn;

    /** Name of player. */
    std::string                            m_Name;

    /** Pointer holds active character for playing. */
    std::shared_ptr <CCharacter>           m_ActiveCharacter;

    /** Pointer holds passive character for playing. */
    std::shared_ptr <CCharacter>           m_PassiveCharacter;

    /** Pointers on cards for playing each player has during the game. */
    std::vector <std::shared_ptr <CCard> > m_PlayingCards;

    /** Pointers on cards for playing with long effect in game. */
    std::set <std::shared_ptr <CCard> >    m_CardsInGame;
};
#endif
