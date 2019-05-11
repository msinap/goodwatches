#include "Film.h"
#include "CommandManager.h"

const vector<string> Film::validKeysForPost = {"name", "year", "length", "price", "summary", "director"};
const vector<bool> Film::shouldExistKeysForPost = {true, true, true, true, true};

Film::Film(vector<string> &remainingWordsOfLine, Publisher* _owner, CommandManager* _commandManager)
    : owner(_owner), commandManager(_commandManager) {
    map<string, string> map = commandManager->setValuesInKeys(remainingWordsOfLine, validKeysForPost,
                                                              shouldExistKeysForPost);
    name = map["name"];
    summary = map["summary"];
    director = map["director"];
    year = stringToInt(map["year"]);
    length = stringToInt(map["length"]);
    price = stringToInt(map["price"]);

    cout << year << ' ' << price << ' ' << length << endl;
}
