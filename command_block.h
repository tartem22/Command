#ifndef COMMAND_BLOCK_H
#define COMMAND_BLOCK_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "command.h"

class CommandBlock
{
public:
    virtual bool add(std::shared_ptr<Command> cmd);
    virtual void release();
    virtual bool isDynamic() = 0;
    bool isIgnored();
    void setAsIgnored();

protected:
    std::vector<std::shared_ptr<Command>> commands;

    void setTimeCode();
    void logToCommandLine();
    void logToFile();

private:
    class FileLogger
    {
    public:
        ~FileLogger()
        {
            if (file.is_open())
                file.close();
        }
        bool open(std::string fileName);
        void close();
        void operator<<(const std::string &str);

    private:
        std::ofstream file;
    };

    std::string timeCode;
    bool isIgnored_ = false;
};

#endif // COMMAND_BLOCK_H
