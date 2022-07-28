#include <iostream>

#include "command_handler.h"

int main(int argc, char *argv[])
{
    int maxStaticBlockSize = 3;
    if (argc > 1)
    {
        maxStaticBlockSize = atoi(argv[1]);
    }

    CommandHandler handler(maxStaticBlockSize);
    // for (std::string line; std::getline(std::cin, line);)
    // {
    //     handler.handle(line);
    // }

    // /*
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
    // */

    return 0;
}
