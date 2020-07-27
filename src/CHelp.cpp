#include "CHelp.h"

bool CHelp::DoIt ( CInterface & m_Interface, bool garbage )
{
  m_Interface.ShowRules ();
  return true;
}
