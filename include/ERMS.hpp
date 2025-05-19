#ifndef ERMS_HPP
#define ERMS_HPP

#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include "Types.hpp"
#include "Stats.hpp"

struct Cmp {
    bool operator()(const std::pair<int, Patient>& a, const std::pair<int, Patient>& b) const {
        if (a.second.severity != b.second.severity)
            return a.second.severity < b.second.severity; // Higher severity first
        return a.first > b.first; // Earlier arrival first
    }
};

class ERMS {
private:
    struct Node; // Forward declaration

public:
    ERMS(std::vector<Doctor> docs);
    ~ERMS();

    void arrive(const Patient& p);
    void admitNext();
    void discharge(int id);
    void lookupDoctor(int id) const;
    void listActive() const;
    void displayStats() const;
    void saveData() const;
    int getTimestamp() const { return timestamp; }
    bool hasActivePatients() const { return head != nullptr; }
    const Node* getHead() const { return head; }
    void addActivePatient(const Patient& p); // New: For loading admitted patients

private:
    struct Node {
        Patient data;
        Node* prev = nullptr;
        Node* next = nullptr;
        Node(const Patient& p) : data(p) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    std::vector<Doctor> doctors;
    std::unordered_map<int, std::string> history;
    Cmp cmp;
    std::priority_queue<std::pair<int, Patient>, std::vector<std::pair<int, Patient>>, Cmp> triagePQ{cmp};
    std::queue<Patient> arrivalQ;
    Stats stats;
    int timestamp = 0;

    Node* findNode(int id);
};

#endif // ERMS_HPP
