#include "Stats.hpp"
#include <iostream>

void Stats::recordArrival(const Patient& p) {
    waitingCount++;
    maxSeverity = std::max(maxSeverity, p.severity);
}

void Stats::recordAdmission(const Patient& p) {
    waitingCount--;
    admittedCount++;
    totalWaitTime += (p.arrivalTime - p.arrivalTime); // Placeholder for actual wait time
    waitTimeCount++;
}

void Stats::recordDischarge(const Patient& p) {
    admittedCount--;
}

void Stats::display() const {
    std::cout << "\n=== Statistics Dashboard ===\n";
    std::cout << "Waiting patients: " << waitingCount << "\n";
    std::cout << "Admitted patients: " << admittedCount << "\n";
    std::cout << "Maximum severity observed: " << maxSeverity << "\n";
    std::cout << "Average wait time: " << (waitTimeCount ? totalWaitTime / waitTimeCount : 0) << " units\n";
}
