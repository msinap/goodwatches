#include "Film.h"

Film::Film(Map &parameters, Publisher* _owner, int _id)
    : data(parameters), owner(_owner), id(_id) {
    checkMustHave({"name", "year", "length", "price", "summary", "director"}, data);

    checkNumeric(parameters["year"]);
    addLeadingZeros(parameters["year"]);
    checkNumeric(parameters["length"]);
    addLeadingZeros(parameters["length"]);
    checkNumeric(parameters["price"]);
    addLeadingZeros(parameters["price"]);
}
