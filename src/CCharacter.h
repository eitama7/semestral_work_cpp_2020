#pragma once

#include <vector>
#include <map>
#include <memory>
#include "CCard.h"
#include "CWeapon.h"
#include "constants.h"

/**
  * Class represents character what players will get in a start of game.
  */
class CCharacter
{
  public:
    /**
      * Constructor sets name, description of character, if character is active and alive.
      * It sets also current health and max health and if that character was already taken by a player.
      *
      * @param[in] health Tells what is max level health.
      * @param[in] name Named character.
      * @param[in] hint Gives description when players choose character.
      */
    CCharacter               ( int health, const std::string name, const std::string hint )
      : m_Weapon             (std::make_shared <CWeapon> (COLT, CLUBS, 10, 0, BLUE, 1)),
        m_Name               (name),
        m_Hint               (hint),
        m_IsActive           (false),
        m_IsAlive            (true),
        m_Health             (health),
        m_HealthCapacity     (health),
        m_Taken              (false)
    {}

    /**
      * Getter for name of character.
      *
      * @return Returns name of character.
      */
    std::string GetName   () { return m_Name; }


    /**
      * Getter for description of the character.
      *
      * @return Returns description of the character.
      */
    std::string GetHint   () { return m_Hint; }

    /**
      * Getter for name of the weapon.
      *
      * @return Returns name of the weapon.
      */
    std::string GetWeapon () { return m_Weapon->GetName (); }

    /**
      * Getter for health of the character.
      *
      * @return Returns health of the character.
      */
         int GetHealth    () { return m_Health; }

     /**
       * Getter for damage of the weapon.
       *
       * @return Returns level of damage of the weapon.
       */
         int GetDamage   () { return m_Weapon->GetDamage (); }

     /**
       * Getter for max health of the character.
       *
       * @return Returns max health character's level.
       */
         int GetHealthCap () { return m_HealthCapacity; }

     /**
       * Getter for taken status of the character.
       *
       * @return Returns the status of the character.
       */
         bool GetTaken    () { return m_Taken; }

     /**
       * Getter for alive status of the character.
       *
       * @return Returns the status of the character.
       */
         bool GetAlive    () { return m_IsAlive; }

     /**
       * Getter for active status of the character.
       *
       * @return Returns the status of the character.
       */
         bool GetActive   () { return m_IsActive; }
     /**
       * Setter for taken status of card.
       *
       * @param[in] value Sets the status of the card.
       */
         void SetTaken    ( bool value ) { m_Taken = value; }

     /**
       * Setter for health of character.
       *
       * @param[in] value Sets health of the character.
       */
         void SetHealth   ( int value ) { m_Health = value; }

     /**
       * Setter for active status of character.
       *
       * @param[in] value Sets status of the character.
       */
         void SetActive   ( bool value ) { m_IsActive = value; }

     /**
       * Setter for alice status of character.
       *
       * @param[in] value Sets status of the character.
       */
         void SetAlive    ( bool value ) { m_IsAlive = value; }

     /**
       * Setter for a damage of the weapon that character uses.
       *
       * @param[in] value Sets the value of damage of the weapon.
       */
         void SetDamage   ( int value ) { m_Weapon->SetDamage ( value ); }

     /**
       * Setter for kind of weapon.
       *
       * @param[in] value Sets the kind of weapon that character uses.
       */
         void SetWeapon ( std::string value ) { m_Weapon->SetName ( value ); }
  private:
    /**  What kind of weapon he owns. */
    std::shared_ptr<CWeapon> m_Weapon;

    /** Name of character. */
    std::string              m_Name;

    /** Description of character. */
    std::string              m_Hint;

    /** If the character is chosen as active. */
    bool                     m_IsActive;

    /** If character is alive. */
    bool                     m_IsAlive;

    /** Current health. */
    int                      m_Health;

    /** Max level of health. */
    int                      m_HealthCapacity;

    /** If the character was already chosen. */
    bool                     m_Taken;
};
