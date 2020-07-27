#pragma once

#include "CCommand.h"
#include "CInterface.h"

class CHelp : public CCommand
{
  public:
    virtual bool DoIt ( CInterface &, bool );
};
