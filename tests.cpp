#include <gtest/gtest.h>
#include <filesystem>
#include <algorithm>
#include <map>
#include <chrono>
#include <thread>
#include <fstream>

#include "command_handler.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

//--- helper function convert timepoint to usable timestamp
template <typename TP>
time_t to_time_t(TP tp)
{
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp -
                                                                                  TP::clock::now() +
                                                                                  std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(sctp);
}

std::vector<std::string> getSortedByTimestampFileList(const std::string &path)
{
    std::vector<std::string> fileList;

    std::multimap<time_t, std::filesystem::directory_entry> sortedByTime;

    //--- sort the files in the map by time
    for (auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            auto time = to_time_t(entry.last_write_time());
            sortedByTime.insert({time, entry});
        }
    }

    fileList.reserve(sortedByTime.size());

    for (auto const &[time, entry] : sortedByTime)
    {
        fileList.emplace_back(entry.path());
    }

    return fileList;
}

std::vector<std::string> getCommandsFromFile(const std::string &path)
{
    std::vector<std::string> cmds;
    cmds.reserve(1000);

    std::ifstream file(path);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            cmds.emplace_back(line);
        }
        file.close();
    }

    cmds.shrink_to_fit();
    return cmds;
}

TEST(command_handler, console_output)
{
    int maxStaticBlockSize = 3;
    CommandHandler handler(maxStaticBlockSize);

    testing::internal::CaptureStdout();

    handler.handle("cmd_1");
    handler.handle("cmd_2");
    handler.handle("cmd_3");
    handler.handle("cmd_16");
    handler.handle("{");
    handler.handle("cmd_4");
    handler.handle("{");
    handler.handle("cmd_10");
    handler.handle("cmd_11");
    handler.handle("{");
    handler.handle("cmd_13");
    handler.handle("cmd_14");
    handler.handle("cmd_15");
    handler.handle("}");
    handler.handle("cmd_12");
    handler.handle("}");
    handler.handle("cmd_5");
    handler.handle("cmd_6");
    handler.handle("}");
    handler.handle("{");
    handler.handle("cmd_7");
    handler.handle("cmd_8");
    handler.handle("cmd_9");
    handler.handle("}");

    std::vector<std::string> expected;
    expected.push_back("cmd_1");
    expected.push_back("cmd_2");
    expected.push_back("cmd_3");
    expected.push_back("cmd_16");
    expected.push_back("cmd_4");
    expected.push_back("cmd_5");
    expected.push_back("cmd_6");
    expected.push_back("cmd_7");
    expected.push_back("cmd_8");
    expected.push_back("cmd_9");

    std::string output = testing::internal::GetCapturedStdout();

    std::vector<std::string> result = split(output, '\n');
    result.erase(result.end() - 1);

    EXPECT_EQ(expected, result);
}

TEST(command_handler, file_output)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    int maxStaticBlockSize = 3;
    CommandHandler handler(maxStaticBlockSize);

    handler.handle("cmd_1");
    handler.handle("cmd_2");
    handler.handle("cmd_3");
    handler.handle("cmd_16");
    handler.handle("{");
    handler.handle("cmd_4");
    handler.handle("{");
    handler.handle("cmd_10");
    handler.handle("cmd_11");
    handler.handle("{");
    handler.handle("cmd_13");
    handler.handle("cmd_14");
    handler.handle("cmd_15");
    handler.handle("}");
    handler.handle("cmd_12");
    handler.handle("}");
    handler.handle("cmd_5");
    handler.handle("cmd_6");
    handler.handle("}");
    handler.handle("{");
    handler.handle("cmd_7");
    handler.handle("cmd_8");
    handler.handle("cmd_9");
    handler.handle("}");

    std::vector<std::vector<std::string>> expected;
    expected.push_back(std::vector<std::string>{
        "cmd_1",
        "cmd_2",
        "cmd_3"});
    expected.push_back(std::vector<std::string>{
        "cmd_16"});
    expected.push_back(std::vector<std::string>{
        "cmd_4",
        "cmd_5",
        "cmd_6"});
    expected.push_back(std::vector<std::string>{
        "cmd_7",
        "cmd_8",
        "cmd_9"});

    std::vector<std::string>
        fileList = getSortedByTimestampFileList("../log");

    std::vector<std::string> resultFiles(4);
    for (int i = 0; i < 4; i++)
    {
        resultFiles.at(i) = fileList.at(fileList.size() - i - 1);
    }
    std::sort(resultFiles.begin(), resultFiles.end());

    std::vector<std::vector<std::string>> result;
    for (int i = 0; i < 4; i++)
    {
        result.emplace_back(getCommandsFromFile(resultFiles.at(i)));
    }
    
    EXPECT_EQ(expected, result);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}