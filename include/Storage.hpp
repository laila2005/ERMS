#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "Types.hpp"
#include "Stats.hpp"

class ERMS; // Forward declaration

namespace Storage {
    void saveDoctors(const std::vector<Doctor>& doctors);
    void loadDoctors(std::vector<Doctor>& doctors);
    void saveHistory(const std::unordered_map<int, std::string>& history);
    void loadHistory(std::unordered_map<int, std::string>& history);
    void saveActivePatients(const ERMS& erms);
    void loadActivePatients(ERMS& erms);
    void saveStats(const Stats& stats);
    void loadStats(Stats& stats);
}

#endif // STORAGE_HPP
