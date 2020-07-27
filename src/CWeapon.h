#pragma once

#include "constants.h"
#include "CCard.h"
#include <string>

/**
  * Weapon for using for the whole game by one player.
  * Each weapon has it's own level of damage.
  */
class CWeapon : public CCard
{
  public:
    /**
      * Constructor sets all options of card (name, suit, number, color, priority)
      * by calling CCard constructor and damage.
      *
      * @param[in] name Goes to CCard constructor.
      * @param[in] suit Goes to CCard constructor.
      * @param[in] number Goes to CCard constructor.
      * @param[in] priority Goes to CCard constructor.
      * @param[in] color Goes to CCard constructor.
      * @param[in] damage How much the enemy will be hurted.
      */
    CWeapon ( const std::string name,
                         ESuit suit,
                         int number,
                         int priority,
                         EColor color,
                         int damage )
      : CCard         ( name, suit, number, priority, color ),
        m_Damage      ( damage )
    {}


    /**
      * Getter for the damage of the weapon.
      *
      * @return Returns thee value of damage of the weapon.
      */
    int GetDamage () { return m_Damage; }

    /**
      * Setter for a damage of the weapon.
      *
      * @param[in] value Sets the damage of the weapon.
      */
    void SetDamage ( int value ) { m_Damage = value; }

    /**
      * Setter for a name of the weapon.
      *
      * @param[in] value Sets a name of the weapon.
      */
    void SetName ( std::string value ) { SetName ( value ); }


    /**
      * Method asks user if he is sure he want to set this weapon.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] pl1 Represents one of player.
      * @param[in, out] pl2 Represents one of player.
      *
      * @return If user desided to set weapon.
      */
    virtual bool Do   ( CInterface &, CPlayer &, CPlayer & );

    /**
      * Method sets new weapon for PC.
      *
      * @param[in, out] m_Interface Interaction with user.
      * @param[in, out] pc Represents PC.
      * @param[in, out] pl Represents player.
      *
      * @return Returns always true.
      */
    virtual bool DoPC ( CInterface &, CPlayer &, CPlayer & );

  private:
    /** How much the enemy will be hurted. */
    int m_Damage;
};
