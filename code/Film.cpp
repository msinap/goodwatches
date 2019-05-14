#include "Film.h"

Film::Film(Map &parameters, int _id)
    : data(parameters), forSale(true), commentRepository(new CommentRepository()) {
    checkMustHave({"name", "year", "length", "price", "summary", "director"}, data);
    checkNumeric(data["year"]);
    checkNumeric(data["length"]);
    checkNumeric(data["price"]);
	data["id"] = intToString(_id);
}

vector<string> Film::getOutput() {
    vector<string> output;
    output.push_back(data["id"]);
    output.push_back(data["name"]);
    output.push_back(data["length"]);
    output.push_back(data["price"]);
    output.push_back(to_string(getRate()));
    output.push_back(data["year"]);
    output.push_back(data["director"]);
    return output;
}

void Film::outputDetails(Map &parameters) {
	vector<string> output;
	output.push_back("Details of Film " + data["name"]);
	output.push_back("Id = " + data["id"]);
	output.push_back("Director = " + data["director"]);
	output.push_back("Length = " + data["length"]);
	output.push_back("Year = " + data["year"]);
	output.push_back("Summary = " + data["summary"]);
	output.push_back("Rate = " + to_string(getRate()));
	output.push_back("Price = " + data["price"]);
	output.push_back("");
	print(output);
	commentRepository->outputAllComments();
	// TODO recom
}

bool Film::areFiltersPassed(Map &parameters) {
    if (!forSale)
        return false;
    for (auto &x : parameters) {
        string key = x.first, value = x.second;
        if (key == "name" || key == "price" || key == "director") {
            if (data[key] != value)
                return false;
        }else if (key == "min_year") {
            if (addLeadingZeros(data["year"]) < addLeadingZeros(value))
                return false;
        }else if (key == "max_year") {
            if (addLeadingZeros(data["year"]) > addLeadingZeros(value))
                return false;
        }else if (key == "min_rate") {
			if (addLeadingZeros(intToString(floor(getRate()))) < addLeadingZeros(value))
				return false;
        }
    }
    return true;
}

void Film::newRate(Map &parameters, int userId) {
	checkMustHave({"film_id", "score"}, parameters);
	checkMayHave({"film_id", "score"}, parameters);
	int score = stringToInt(parameters["score"]);
	sumOfRates += score - userRates[userId];
	userRates[userId] = score;
}

void Film::deleteComment(Map &parameters) {
	int id = stringToInt(parameters["comment_id"]);
	commentRepository->getCommentWithId(id)->hide(parameters);
}

void Film::replyComment(Map &parameters) {
	int id = stringToInt(parameters["comment_id"]);
	commentRepository->getCommentWithId(id)->reply(parameters);
}

void Film::edit(Map &parameters) {
    checkMayHave({"film_id", "name", "year", "length", "price", "summary", "director"}, parameters);
    for (auto x : parameters)
        data.insert(x);
}

void Film::stopSale(Map &parameters) {
    checkMayHave({"film_id"}, parameters);
    if (forSale == false)
        throw BadRequestError();
    forSale = false;
}

void Film::addComment(Map &parameters) {
	checkMustHave({"film_id", "content"}, parameters);
	checkMayHave({"film_id", "content"}, parameters);
	commentRepository->addComment(parameters["content"]);
}

double Film::getRate() {
	if (userRates.empty())
		return 0.0;
	return (1.0 * sumOfRates) / (1.0 * userRates.size());
}

bool Film::isForSale() {
    return forSale;
}
