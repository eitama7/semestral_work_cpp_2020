#pragma once

#include "CInterface.h"

/**
  * Base class for choosing command by user.
  */
class CCommand
{
  public:
    /**
      * Making action.
      */
    virtual bool DoIt ( CInterface &, bool ) = 0;
};
