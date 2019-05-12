#include "CommandManager.h"

CommandManager::CommandManager() {
    filmRepository = new FilmRepository(this);
    userRepository = new UserRepository(this, filmRepository);
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
    if (getAndPopBack(remainingWordsOfLine) != "?")
        throw BadRequestError();
    Map parameters = setValuesInKeys(remainingWordsOfLine);
    if (word == "signup") {
        userRepository->addUser(parameters);
    }else if (word == "login") {
        userRepository->login(parameters);
    }else if (word == "films") {
        userRepository->postFilm(parameters);
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

map<string, string> CommandManager::setValuesInKeys(vector<string> &remainingWordsOfLine) {
    if (remainingWordsOfLine.size() % 2 == 1)
        throw BadRequestError();
    map<string, string> ret;
    for (int i = 0; i < remainingWordsOfLine.size(); i += 2)
        ret[remainingWordsOfLine[i+1]] = remainingWordsOfLine[i];
    if (ret.size() * 2 != remainingWordsOfLine.size())
        throw BadRequestError();
    return ret;
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
