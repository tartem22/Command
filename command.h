#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command
{
public:
    Command(std::string cmd) : cmd(cmd) {}
    std::string get()
    {
        return cmd;
    }

private:
    std::string cmd;
};

#endif // COMMAND_H