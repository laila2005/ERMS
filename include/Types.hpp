#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

struct Patient {
    int id;
    std::string name;
    int severity; // Higher value = more critical
    int arrivalTime; // Timestamp for wait time calculation
};

struct Doctor {
    int id;
    std::string name;
    std::string specialty;
};

#endif // TYPES_HPP
