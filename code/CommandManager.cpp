#include "CommandManager.h"

CommandManager::CommandManager() {
    filmRepository = new FilmRepository();
    userRepository = new UserRepository(filmRepository);
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
		userRepository->getCurrentUser()->collectEarning();
		cout << "OK" << endl;
		return;
	}else if (word == "logout") {
		if (!remainingWordsOfLine.empty())
			throw BadRequestError();
		userRepository->logoutCurrentUser();
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
        userRepository->getCurrentUser()->postFilm(parameters);
    }else if (word == "followers") {
        userRepository->getCurrentUser()->follow(parameters);
    }else if (word == "comments") {
        userRepository->getCurrentUser()->postComment(parameters);
    }else if (word == "replies") {
		userRepository->getCurrentUser()->replyComment(parameters);
	}else if (word == "rate") {
		userRepository->getCurrentUser()->rateFilm(parameters);
	}else if (word == "money") {
		userRepository->getCurrentUser()->addMoney(parameters);
	}else if (word == "buy") {
		userRepository->getCurrentUser()->buyFilm(parameters);
	}else if (word == "put_films") {
        userRepository->getCurrentUser()->editFilm(parameters);
    }else if (word == "delete_films") {
        userRepository->getCurrentUser()->deleteFilm(parameters);
    }else if (word == "delete_comments") {
		userRepository->getCurrentUser()->deleteComment(parameters);
	}else {
        throw NotFoundError();
    }
    cout << "OK" << endl;
}

void CommandManager::proccessGetCommands(vector<string> &remainingWordsOfLine) {
    string word = getAndPopBack(remainingWordsOfLine);
    if (word == "followers") {
        Map parameters = setValuesInKeys(remainingWordsOfLine);
        userRepository->getCurrentUser()->outputFollowers(parameters);
        return;
    }else if (word == "notifications") {
		if (remainingWordsOfLine.empty()) {
			userRepository->getCurrentUser()->seeUnreadNotifications();
			return;
		}else {
			if (getAndPopBack(remainingWordsOfLine) != "read")
        		throw BadRequestError();
		}
	}else if (word == "money") {
		if (!remainingWordsOfLine.empty())
			throw BadRequestError();
		userRepository->getCurrentUser()->getMoney();
		return;
	}

    if (!remainingWordsOfLine.empty() && getAndPopBack(remainingWordsOfLine) != "?")
        throw BadRequestError();
    Map parameters = setValuesInKeys(remainingWordsOfLine);

    if(word == "published") {
        userRepository->getCurrentUser()->outputPublishedFilms(parameters);
    }else if (word == "films") {
        if (parameters.find("film_id") != parameters.end()) {
            userRepository->getCurrentUser()->showFilm(parameters);
        }else {
            userRepository->getCurrentUser()->findFilms(parameters);
        }
    }else if (word == "purchased") {
		userRepository->getCurrentUser()->outputPurchasedFilms(parameters);
	}else if (word == "notifications") {
		userRepository->getCurrentUser()->seeReadNotifications(parameters);
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
