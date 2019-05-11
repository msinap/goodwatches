#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "utility.h"

class CommandManager {
public:
    void inputCommands();

private:
    vector<string> splitLine(string line);

};

#endif
