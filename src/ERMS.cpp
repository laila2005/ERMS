#include "ERMS.hpp"
#include "Storage.hpp"
#include <algorithm>
#include <iostream>

ERMS::ERMS(std::vector<Doctor> docs) : doctors(std::move(docs)) {
    std::sort(doctors.begin(), doctors.end(), [](const Doctor& a, const Doctor& b) { return a.id < b.id; });
    // Load initial data
    Storage::loadDoctors(doctors);
    Storage::loadHistory(history);
    Storage::loadActivePatients(*this);
    Storage::loadStats(stats);
}

ERMS::~ERMS() {
    // Save data before cleanup
    Storage::saveDoctors(doctors);
    Storage::saveHistory(history);
    Storage::saveActivePatients(*this);
    Storage::saveStats(stats);
    // Clean up doubly linked list
    Node* n = head;
    while (n) {
        Node* tmp = n;
        n = n->next;
        tmp->next = nullptr; // Prevent dangling pointers
        tmp->prev = nullptr;
        delete tmp;
    }
    head = nullptr;
    tail = nullptr;
}

ERMS::Node* ERMS::findNode(int id) {
    for (Node* n = head; n; n = n->next)
        if (n->data.id == id)
            return n;
    return nullptr;
}

void ERMS::arrive(const Patient& p) {
    arrivalQ.push(p);
    triagePQ.emplace(timestamp++, p);
    stats.recordArrival(p);
    std::cout << "Arrived: " << p.name << " (sev " << p.severity << ")\n";
    Storage::saveHistory(history);
}

void ERMS::admitNext() {
    if (triagePQ.empty()) {
        std::cout << "No patients waiting\n";
        return;
    }
    Patient p = triagePQ.top().second;
    triagePQ.pop();
    addActivePatient(p); // Use new function to add to list
    stats.recordAdmission(p);
    std::cout << "Admitting: " << p.name << "\n";
    Storage::saveActivePatients(*this);
}

void ERMS::discharge(int id) {
    Node* n = findNode(id);
    if (!n) {
        std::cout << "Patient not found\n";
        return;
    }
    history.emplace(id, "Discharged");
    stats.recordDischarge(n->data);
    if (n->prev)
        n->prev->next = n->next;
    if (n->next)
        n->next->prev = n->prev;
    if (n == head)
        head = n->next;
    if (n == tail)
        tail = n->prev;
    n->next = nullptr; // Prevent dangling pointers
    n->prev = nullptr;
    std::cout << "Discharged: " << n->data.name << "\n";
    delete n;
    Storage::saveActivePatients(*this);
    Storage::saveHistory(history);
}

void ERMS::lookupDoctor(int id) const {
    auto it = std::lower_bound(doctors.begin(), doctors.end(), id,
        [](const Doctor& d, int value) { return d.id < value; });
    if (it == doctors.end() || it->id != id) {
        std::cout << "Doctor not found\n";
        return;
    }
    std::cout << "Doctor: " << it->name << " (" << it->specialty << ")\n";
}

void ERMS::listActive() const {
    std::cout << "Active patients:\n";
    for (Node* n = head; n; n = n->next)
        std::cout << "  [" << n->data.id << "] " << n->data.name << " sev=" << n->data.severity << "\n";
}

void ERMS::displayStats() const {
    stats.display();
}

void ERMS::saveData() const {
    Storage::saveDoctors(doctors);
    Storage::saveHistory(history);
    Storage::saveActivePatients(*this);
    Storage::saveStats(stats);
    std::cout << "Data saved\n";
}

void ERMS::addActivePatient(const Patient& p) {
    Node* n = new Node(p);
    if (!head)
        head = tail = n;
    else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}
