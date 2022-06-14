#include "command_block.h"

#include <chrono>
#include <ctime>
#include <sstream>
#include <filesystem>

bool CommandBlock::add(std::shared_ptr<Command> cmd)
{
    if (commands.size() == 0)
        setTimeCode();
    commands.emplace_back(cmd);
    return true;
}
void CommandBlock::release()
{
    if(!isIgnored_)
    {
        logToFile();
        logToCommandLine();
    }
    commands.clear();
}

bool CommandBlock::isIgnored()
{
    return isIgnored_;
}

void CommandBlock::setAsIgnored()
{
    isIgnored_ = true;
}

void CommandBlock::setTimeCode()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    auto localTime = std::localtime(&in_time_t);

    timeCode = std::to_string(localTime->tm_hour) +
            std::to_string(localTime->tm_min) +
            std::to_string(localTime->tm_sec);
}

void CommandBlock::logToCommandLine()
{
    for (auto &command : commands)
    {
        std::cout << command->get() << std::endl;
    }
}

void CommandBlock::logToFile()
{
    std::string filePath = "./log/" + timeCode + ".log";
    FileLogger fileLogger;
    if(!fileLogger.open(filePath))
    {
        std::filesystem::path path("./log");
        if(!std::filesystem::exists(path))
        {
            std::filesystem::create_directory(path);
            fileLogger.open(filePath);
        }
    }

    for (auto &command : commands)
    {
        fileLogger << command->get();
    }
}

bool CommandBlock::FileLogger::open(std::string fileName)
{
    file.open(fileName);
    if (!file.is_open())
        return false;
    return true;
}

void CommandBlock::FileLogger::close()
{
    if (file.is_open())
        file.close();
}

void CommandBlock::FileLogger::operator<<(const std::string &str)
{
    if (file.is_open())
    {
        file << str.c_str() << std::endl;
    }
}
