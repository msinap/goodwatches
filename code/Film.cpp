#include "Film.h"

Film::Film(Map &parameters)
    : data(parameters), isForSale(true) {
    checkMustHave({"name", "year", "length", "price", "summary", "director"}, data);

    checkNumeric(parameters["year"]);
    addLeadingZeros(parameters["year"]);
    checkNumeric(parameters["length"]);
    addLeadingZeros(parameters["length"]);
    checkNumeric(parameters["price"]);
    addLeadingZeros(parameters["price"]);
}

void Film::edit(Map &parameters) {
    checkMayHave({"film_id", "name", "year", "length", "price", "summary", "director"}, parameters);
    for (auto x : parameters)
        data.insert(x);
}
