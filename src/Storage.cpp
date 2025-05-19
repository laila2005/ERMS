#include "Storage.hpp"
#include "ERMS.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void Storage::saveDoctors(const std::vector<Doctor>& doctors) {
    json j;
    for (const auto& d : doctors) {
        j.push_back({{"id", d.id}, {"name", d.name}, {"specialty", d.specialty}});
    }
    std::ofstream file("/home/laila_2005/ERMS/doctors.json"); // Absolute path
    if (file.is_open()) {
        file << j.dump(2);
        file.close();
    } else {
        std::cerr << "Error: Could not save doctors.json\n";
    }
}

void Storage::loadDoctors(std::vector<Doctor>& doctors) {
    std::ifstream file("/home/laila_2005/ERMS/doctors.json");
    if (!file.is_open()) {
        std::cout << "No existing doctors.json, starting fresh\n";
        return;
    }
    try {
        json j;
        file >> j;
        doctors.clear();
        for (const auto& item : j) {
            doctors.push_back({item["id"], item["name"], item["specialty"]});
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading doctors.json: " << e.what() << "\n";
    }
    file.close();
}

void Storage::saveHistory(const std::unordered_map<int, std::string>& history) {
    json j;
    for (const auto& [id, status] : history) {
        j[std::to_string(id)] = status;
    }
    std::ofstream file("/home/laila_2005/ERMS/history.json");
    if (file.is_open()) {
        file << j.dump(2);
        file.close();
    } else {
        std::cerr << "Error: Could not save history.json\n";
    }
}

void Storage::loadHistory(std::unordered_map<int, std::string>& history) {
    std::ifstream file("/home/laila_2005/ERMS/history.json");
    if (!file.is_open()) {
        std::cout << "No existing history.json, starting fresh\n";
        return;
    }
    try {
        json j;
        file >> j;
        history.clear();
        for (auto it = j.begin(); it != j.end(); ++it) {
            history[std::stoi(it.key())] = it.value();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading history.json: " << e.what() << "\n";
    }
    file.close();
}

void Storage::saveActivePatients(const ERMS& erms) {
    json j;
    for (const auto* n = erms.getHead(); n; n = n->next) {
        const Patient& p = n->data;
        j.push_back({{"id", p.id}, {"name", p.name}, {"severity", p.severity}, {"arrivalTime", p.arrivalTime}});
    }
    std::ofstream file("/home/laila_2005/ERMS/active_patients.json");
    if (file.is_open()) {
        file << j.dump(2);
        file.close();
    } else {
        std::cerr << "Error: Could not save active_patients.json\n";
    }
}

void Storage::loadActivePatients(ERMS& erms) {
    std::ifstream file("/home/laila_2005/ERMS/active_patients.json");
    if (!file.is_open()) {
        std::cout << "No existing active_patients.json, starting fresh\n";
        return;
    }
    try {
        json j;
        file >> j;
        for (const auto& item : j) {
            Patient p = {item["id"], item["name"], item["severity"], item["arrivalTime"]};
            erms.addActivePatient(p); // Directly add to active list
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading active_patients.json: " << e.what() << "\n";
    }
    file.close();
}

void Storage::saveStats(const Stats& stats) {
    json j = {
        {"waitingCount", stats.getWaitingCount()},
        {"admittedCount", stats.getAdmittedCount()},
        {"maxSeverity", stats.getMaxSeverity()},
        {"totalWaitTime", stats.getTotalWaitTime()},
        {"waitTimeCount", stats.getWaitTimeCount()}
    };
    std::ofstream file("/home/laila_2005/ERMS/stats.json");
    if (file.is_open()) {
        file << j.dump(2);
        file.close();
    } else {
        std::cerr << "Error: Could not save stats.json\n";
    }
}

void Storage::loadStats(Stats& stats) {
    std::ifstream file("/home/laila_2005/ERMS/stats.json");
    if (!file.is_open()) {
        std::cout << "No existing stats.json, starting fresh\n";
        return;
    }
    try {
        json j;
        file >> j;
        stats.setWaitingCount(j["waitingCount"]);
        stats.setAdmittedCount(j["admittedCount"]);
        stats.setMaxSeverity(j["maxSeverity"]);
        stats.setTotalWaitTime(j["totalWaitTime"]);
        stats.setWaitTimeCount(j["waitTimeCount"]);
    } catch (const std::exception& e) {
        std::cerr << "Error loading stats.json: " << e.what() << "\n";
    }
    file.close();
}
