#include "Film.h"

Film::Film(Map &parameters)
    : data(parameters), forSale(true) {
    checkMustHave({"name", "year", "length", "price", "summary", "director"}, data);

    checkNumeric(data["year"]);
    data["year"] = addLeadingZeros(data["year"]);
    checkNumeric(data["length"]);
    checkNumeric(data["price"]);
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

Map Film::getData() {
    return data;
}
