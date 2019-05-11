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
            string word = getAndPopBack(wordsOfLine);
            if (word == "POST") {
                proccessPostCommands(wordsOfLine);
            }else if (word == "PUT") {
                proccessPutCommands(wordsOfLine);
            }else if (word == "GET") {
                proccessGetCommands(wordsOfLine);
            }else if (word == "DELETE") {
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
    string word = getAndPopBack(remainingWordsOfLine);
    if (word == "signup") {
        if (getAndPopBack(remainingWordsOfLine) != "?")
            throw BadRequestError();
        userRepository->addUser(remainingWordsOfLine);
    }else if (word == "login"){
        if (getAndPopBack(remainingWordsOfLine) != "?")
            throw BadRequestError();
        // userRepository->login(remainingWordsOfLine);
    }else {
        throw NotFoundError();
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
