#ifndef DYMANIC_COMMAND_BLOCK_H
#define DYNAMIC_COMMAND_BLOCK_H

#include "command_block.h"

class DynamicCommandBlock : public CommandBlock
{
public:
    bool isDynamic() override
    {
        return true;
    }
};

#endif // DYNAMIC_COMMAND_BLOCK_H
