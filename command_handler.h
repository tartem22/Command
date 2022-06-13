#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <memory>
#include <stack>
#include "command_block.h"

class CommandHandler
{
public:
    CommandHandler(int size) : staticBlockSize(size){}
    void handle(std::string cmd);
    
private:
    int staticBlockSize = 0;
    std::shared_ptr<CommandBlock> currBlock = nullptr;
    std::stack<std::shared_ptr<CommandBlock>> blocks;

    void createNewDynamicBlock();
    void createNewStaticBlock();
    void releaseCurrentBlock();
};

#endif // COMMAND_HANDLER_H
