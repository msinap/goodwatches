#ifndef FILM_H
#define FILM_H

#include "utility.h"

class CommandManager;
class Publisher;

class Film {
public:
    Film(vector<string> &remainingWordsOfLine, Publisher* _owner, CommandManager* _commandManager);
private:
    string name;
    string summary;
    string director;
    int year;
    int length;
    int price;
    Publisher* owner;

    CommandManager* commandManager;

    const static vector<string> validKeysForPost;
    const static vector<bool> shouldExistKeysForPost;
};

#endif
