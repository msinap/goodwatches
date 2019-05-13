#include "Film.h"

Film::Film(Map &parameters, int _id)
    : data(parameters), forSale(true), id(_id) {
    checkMustHave({"name", "year", "length", "price", "summary", "director"}, data);

    checkNumeric(data["year"]);
    data["year"] = addLeadingZeros(data["year"]);
    checkNumeric(data["length"]);
    checkNumeric(data["price"]);
}

vector<string> Film::getOutput() {
    vector<string> output;
    output.push_back(intToString(id));
    output.push_back(data["name"]);
    output.push_back(data["length"]);
    output.push_back(data["price"]);
    // TODO rate
    output.push_back(deleteLeadingZeros(data["year"]));
    output.push_back(data["director"]);
    return output;
}

bool Film::areFiltersPassed(Map &parameters) {
    for (auto &x : parameters) {
        string key = x.first, value = x.second;
        if (key == "name" || key == "price" || key == "director") {
            if (data[key] != value)
                return false;
        }else if (key == "min_year") {
            if (data["year"] < addLeadingZeros(value))
                return false;
        }else if (key == "max_year") {
            if (data["year"] > addLeadingZeros(value))
                return false;
        }else if (key == "min_rate") {
            //TODO
        }
    }
    return true;
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

bool Film::isForSale() {
    return forSale;
}
