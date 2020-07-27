#pragma once

#include <string>
class CInterface;
class CPlayer;

/**
  * Which suit card has.
  */
enum ESuit
{
  CLUBS,
  DIAMONDS,
  HEARTS,
  SPADES
};

/**
  * Which color card has.
  */
enum EColor
{
  BROWN,
  BLUE
};

/**
  * Class represents one card for playing. Each card has unique identifier: suit, color, number.
  */
class CCard
{
  public:
    /**
      * Constructors sets name of card, suit, number and color.
      * Also it sets priority and if card was already checked by PC (mode vs PC).
      *
      * @param[in] name Name of card.
      * @param[in] suit Suit of card.
      * @param[in] number Number of card
      * @param[in] priority Priority of card
      * @param[in] color Color of card.
      */
                CCard ( const std::string name, ESuit suit, int number, int priority, EColor color )
      : m_Name      (name),
        m_Suit      (suit),
        m_Number    (number),
        m_Priority  (priority),
        m_Color     (color),
        m_IsChecked (false)
    {}

      /**
        * Getter for name of the card.
        *
        * @return Returns name of the card.
        */
      std::string GetName      () { return m_Name; }
      /**
        * Getter for color of the card.
        *
        * @return Returns color of the card.
        */
         EColor GetColor     () { return m_Color; }

         /**
           * Getter for suit of the card.
           *
           * @return Returns suit of the card.
           */
         ESuit  GetSuit      () { return m_Suit; }

         /**
           * Getter for number of the card.
           *
           * @return Returns number of the card.
           */
         int    GetNumber    () { return m_Number; }

         /**
           * Getter for priority of the card.
           *
           * @return Returns priority of the card.
           */
         int    GetPriotity  () { return m_Priority; }

         /**
           * Getter for checked status of the card.
           *
           * @return Returns true if card was already checked by PC while choosing card in round in mode VS_PC.
           */
         bool   GetIsChecked () { return m_IsChecked; }

         /**
           * Setter for status of the card.
           *
           * @param[in] value Sets value of m_IsChecked.
           */
         void SetIsChecked ( bool value ) { m_IsChecked = value; }

         /**
           * Setter for name of the card.
           *
           * @param[in] value Sets value of m_Name.
           */
         void SetName      ( std::string value ) { m_Name = value; }

   virtual bool    Do   ( CInterface & m_Interface, CPlayer &, CPlayer & ) = 0;
   virtual bool    DoPC ( CInterface & m_Interface, CPlayer &, CPlayer & ) = 0;

  private:
    /** Name of card. */
    std::string     m_Name;

    /** Suit of card. */
    ESuit           m_Suit;

    /** Number of card. */
    int             m_Number;

    /** Value priority we use in playing mode with PC, when PC desides which card is more important. */
    int             m_Priority;

    /** Color of card. */
    EColor          m_Color;

    /** When PC controls all cards in a round to choose more 'expensive' he makes marks on each of them. */
    bool            m_IsChecked;

};
