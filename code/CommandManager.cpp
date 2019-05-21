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
            }else if (word == "GET") {
                proccessGetCommands(wordsOfLine);
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
	if (word == "money" && remainingWordsOfLine.empty()) {
		userRepository->getLoggedinUser()->collectEarning();
		cout << "OK" << endl;
		return;
	}
    if (!remainingWordsOfLine.empty() && getAndPopBack(remainingWordsOfLine) != "?")
        throw BadRequestError();
    Map parameters = setValuesInKeys(remainingWordsOfLine);
    if (word == "signup") {
        userRepository->addUser(parameters);
    }else if (word == "login") {
        userRepository->login(parameters);
    }else if (word == "films") {
        userRepository->getLoggedinUser()->postFilm(parameters);
    }else if (word == "followers") {
        userRepository->getLoggedinUser()->follow(parameters);
    }else if (word == "comments") {
        userRepository->getLoggedinUser()->postComment(parameters);
    }else if (word == "replies") {
		userRepository->getLoggedinUser()->replyComment(parameters);
	}else if (word == "rate") {
		userRepository->getLoggedinUser()->rateFilm(parameters);
	}else if (word == "money") {
		userRepository->getLoggedinUser()->addMoney(parameters);
	}else if (word == "buy") {
		userRepository->getLoggedinUser()->buyFilm(parameters);
	}if (word == "put_films") {
        userRepository->getLoggedinUser()->editFilm(parameters);
    }if (word == "delete_films") {
        userRepository->getLoggedinUser()->deleteFilm(parameters);
    }else if (word == "delete_comments") {
		userRepository->getLoggedinUser()->deleteComment(parameters);
	}else {
        throw NotFoundError();
    }
    cout << "OK" << endl;
}

void CommandManager::proccessGetCommands(vector<string> &remainingWordsOfLine) {
    string word = getAndPopBack(remainingWordsOfLine);
    if (word == "followers") {
        Map parameters = setValuesInKeys(remainingWordsOfLine);
        userRepository->getLoggedinUser()->outputFollowers(parameters);
        return;
    }else if (word == "notifications") {
		if (remainingWordsOfLine.empty()) {
			userRepository->getLoggedinUser()->seeUnreadNotifications();
			return;
		}else {
			if (getAndPopBack(remainingWordsOfLine) != "read")
        		throw BadRequestError();
		}
	}

    if (!remainingWordsOfLine.empty() && getAndPopBack(remainingWordsOfLine) != "?")
        throw BadRequestError();
    Map parameters = setValuesInKeys(remainingWordsOfLine);

    if(word == "published") {
        userRepository->getLoggedinUser()->outputPublishedFilms(parameters);
    }else if (word == "films") {
        if (parameters.find("film_id") != parameters.end()) {
            userRepository->getLoggedinUser()->showFilm(parameters);
        }else {
            userRepository->getLoggedinUser()->findFilms(parameters);
        }
    }else if (word == "purchased") {
		userRepository->getLoggedinUser()->outputPurchasedFilms(parameters);
	}else if (word == "notifications") {
		userRepository->getLoggedinUser()->seeReadNotifications(parameters);
	}else {
        throw NotFoundError();
    }
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
