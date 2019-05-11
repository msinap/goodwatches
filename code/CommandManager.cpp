#include "CommandManager.h"

void CommandManager::inputCommands() {
    string inputLine;
    while (getline(cin, inputLine)) {
        vector<string> wordsOfLine = splitLine(inputLine);

        if (wordsOfLine.empty())
            continue;

        if (wordsOfLine[0] == "POST") {

        }else if (wordsOfLine[0] == "PUT") {

        }else if (wordsOfLine[0] == "GET") {

        }else if (wordsOfLine[0] == "DELETE") {

        }else {
            cout << "Bad Request" << endl;
        }
    }
}

vector<string> CommandManager::splitLine(string line) {
    line += ' ';
    vector<string> ret;
    string currentWord = "";

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            if (!currentWord.empty())
                ret.push_back(currentWord);
            currentWord = "";
        }else {
            currentWord += line[i];
        }
    }

    return ret;
}
