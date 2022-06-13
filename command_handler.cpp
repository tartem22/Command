#include "command_handler.h"
#include "dynamic_command_block.h"
#include "static_command_block.h"

void CommandHandler::handle(std::string cmd)
{
    if (cmd == "{")
    {
        if(currBlock != nullptr)
        {
            if(!currBlock->isDynamic())
            {
                releaseCurrentBlock();
            }
        }
        createNewDynamicBlock();
    }
    else if (cmd == "}")
    {
        releaseCurrentBlock();
    }
    else
    {
        if (currBlock == nullptr)
        {
            createNewStaticBlock();
        }
        std::shared_ptr<Command> command = std::make_shared<Command>(cmd);
        currBlock->add(command);
    }
}

void CommandHandler::createNewDynamicBlock()
{
    currBlock = std::make_shared<DynamicCommandBlock>();
    if(!blocks.empty())
    {
        if(blocks.top()->isDynamic())
            currBlock->setAsIgnored();
    }
    blocks.push(currBlock);
}

void CommandHandler::createNewStaticBlock()
{
    currBlock = std::make_shared<StaticCommandBlock>(staticBlockSize);
    blocks.push(currBlock);
}

void CommandHandler::releaseCurrentBlock()
{
    if (currBlock != nullptr)
    {
        currBlock->release();
        blocks.pop();
        if(!blocks.empty())
            currBlock = blocks.top();
        else
            currBlock = nullptr;
    }
}
