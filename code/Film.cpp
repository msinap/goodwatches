#include "Film.h"

Film::Film(Map &parameters, int _id, int _publisherId)
    : data(parameters), forSale(true), commentRepository(new CommentRepository()), uncollectedEarning(0), 
      publisherId(_publisherId), sumOfRates(0), adminShare(0) {
    checkMustHave({"name", "year", "length", "price", "summary", "director"}, data);
    checkNumeric(data["year"]);
    checkNumeric(data["length"]);
    checkNumeric(data["price"]);
	data["id"] = intToString(_id);
}

vector<string> Film::getOutput(bool allDetails) {
    vector<string> output;
    output.push_back(data["id"]);
    output.push_back(data["name"]);
    output.push_back(data["length"]);
    if (allDetails) {
		output.push_back(data["price"]);
    	output.push_back(makePrecisionTwo(to_string(getRate())));
    	output.push_back(data["year"]);
	}
    output.push_back(data["director"]);
    return output;
}

void Film::outputDetails(Map &parameters) {
	if (!forSale)
		throw NotFoundError();
	checkMustHave({"film_id"}, parameters);
	checkMayHave({"film_id"}, parameters);
	vector<string> output;
	output.push_back("Details of Film " + data["name"]);
	output.push_back("Id = " + data["id"]);
	output.push_back("Director = " + data["director"]);
	output.push_back("Length = " + data["length"]);
	output.push_back("Year = " + data["year"]);
	output.push_back("Summary = " + data["summary"]);
	output.push_back("Rate = " + makePrecisionTwo(to_string(getRate())));
	output.push_back("Price = " + data["price"]);
	output.push_back("");
	print(output);
	commentRepository->outputAllComments();
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
	if (!forSale)
        throw NotFoundError();
	int score = stringToInt(parameters["score"]);
	if (score < 0 || score > 10)
		throw BadRequestError();
	sumOfRates += score - userRates[userId];
	userRates[userId] = score;
}

void Film::deleteComment(Map &parameters) {
	if (!forSale)
		throw NotFoundError();
	int id = stringToInt(parameters["comment_id"]);
	commentRepository->getCommentWithId(id)->hide(parameters);
}

void Film::replyComment(Map &parameters) {
	if (!forSale)
		throw NotFoundError();
	int id = stringToInt(parameters["comment_id"]);
	commentRepository->getCommentWithId(id)->reply(parameters);
}

void Film::edit(Map &parameters) {
    checkMayHave({"film_id", "name", "year", "length", "price", "summary", "director"}, parameters);
	if (!forSale)
		throw NotFoundError();
    for (auto x : parameters)
        data[x.first] = x.second;
}

void Film::stopSale(Map &parameters) {
    checkMayHave({"film_id"}, parameters);
    if (!forSale)
        throw NotFoundError();
    forSale = false;
}

void Film::addComment(Map &parameters, int senderId) {
	checkMustHave({"film_id", "content"}, parameters);
	checkMayHave({"film_id", "content"}, parameters);
	if (!forSale)
        throw NotFoundError();
	commentRepository->addComment(parameters["content"], senderId);
}

int Film::getSenderOfCommentId(int commentId) {
	return commentRepository->getCommentWithId(commentId)->getSenderId();
}

double Film::getRate() {
	if (userRates.empty())
		return 0.0;
	return (1.0 * sumOfRates) / (1.0 * userRates.size());
}

void Film::sell() {
	if (!forSale)
		throw NotFoundError();
	double rate = getRate();
	double price = getPrice();
	double ratioForPublisher;
	if (rate < 5)
		ratioForPublisher = 0.80;
	else if (rate < 8)
		ratioForPublisher = 0.90;
	else
		ratioForPublisher = 0.95;
	uncollectedEarning += ratioForPublisher * price;
	adminShare += price - (ratioForPublisher * price);
}

int Film::getPrice() {
	return stringToInt(data["price"]);
}

int Film::collectEarning() {
	int ret = uncollectedEarning;
	uncollectedEarning = 0;
	return ret;
}

bool Film::isForSale() {
    return forSale;
}

int Film::getPublisherId() {
	return publisherId;
}

string Film::getName() {
	return data["name"];
}

int Film::getAdminShare() {
	return adminShare;
}

int Film::getUncollectedMoney() {
	return uncollectedEarning;
}

Map Film::getData() {
	data["rate"] = makePrecisionTwo(to_string(getRate()));
	return data;
}

vector<string> Film::getComments() {
	return commentRepository->getAllComments();
}