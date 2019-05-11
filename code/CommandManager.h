#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "utility.h"
#include "UserRepository.h"

class CommandManager {
public:
    CommandManager();
    void inputCommands();
    map<string, string> setValuesInKeys(vector<string> &remainingWordsOfLine, const vector<string> &validKeys,
                                        const vector<bool> &shouldExistKeys);
private:
    vector<string> splitLine(string line);
    void proccessPostCommands(vector<string> &remainingWordsOfLine);
    void proccessPutCommands(vector<string> &remainingWordsOfLine);
    void proccessGetCommands(vector<string> &remainingWordsOfLine);
    void proccessDeleteCommands(vector<string> &remainingWordsOfLine);

    UserRepository* userRepository;
};

#endif
