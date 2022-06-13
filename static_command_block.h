#ifndef STATIC_COMMAND_BLOCK_H
#define STATIC_COMMAND_BLOCK_H

#include "command_block.h"

class StaticCommandBlock : public CommandBlock
{
public:
    StaticCommandBlock(int size) : size(size){}
    bool add(std::shared_ptr<Command> cmd) override
    {
        CommandBlock::add(cmd);
        if(commands.size() == size)
        {
            release();
            return false;
        }
        return true;
    }
    bool isDynamic() override
    {
        return false;
    }

private:
    int size = 0;
};


#endif // STATIC_COMMAND_BLOCK_H
