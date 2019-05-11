#include "CommandManager.h"

CommandManager::CommandManager() {
    userRepository = new UserRepository();
}

void CommandManager::inputCommands() {
    string inputLine;
    while (getline(cin, inputLine)) {
        vector<string> wordsOfLine = splitLine(inputLine);
        reverse(wordsOfLine.begin(), wordsOfLine.end());
        if (wordsOfLine.empty())
            continue;
        try {
            if (wordsOfLine.back() == "POST") {
                wordsOfLine.pop_back();
                proccessPostCommands(wordsOfLine);
            }else if (wordsOfLine.back() == "PUT") {
                wordsOfLine.pop_back();
                proccessPutCommands(wordsOfLine);
            }else if (wordsOfLine.back() == "GET") {
                wordsOfLine.pop_back();
                proccessGetCommands(wordsOfLine);
            }else if (wordsOfLine.back() == "DELETE") {
                wordsOfLine.pop_back();
                proccessDeleteCommands(wordsOfLine);
            }else {
                throw BadRequestError();
            }
        }catch (BadRequestError) {
            cout << "Bad Request" << endl;
        }catch (NotFoundError) {
            cout << "Not Found" << endl;
        }catch (PermissionDeniedError) {
            cout << "Permission Denied" << endl;
        }
    }
}

void CommandManager::proccessPostCommands(vector<string> &remainingWordsOfLine) {
    if (remainingWordsOfLine.empty())
        throw NotFoundError();
    string word = remainingWordsOfLine.back();
    if (word == "signup") {

    }
}

void CommandManager::proccessPutCommands(vector<string> &remainingWordsOfLine) {

}

void CommandManager::proccessGetCommands(vector<string> &remainingWordsOfLine) {

}

void CommandManager::proccessDeleteCommands(vector<string> &remainingWordsOfLine) {

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
