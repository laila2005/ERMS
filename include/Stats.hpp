#ifndef STATS_HPP
#define STATS_HPP

#include "Types.hpp"

class Stats {
public:
    void recordArrival(const Patient& p);
    void recordAdmission(const Patient& p);
    void recordDischarge(const Patient& p);
    void display() const;

    // Getters for saving
    int getWaitingCount() const { return waitingCount; }
    int getAdmittedCount() const { return admittedCount; }
    int getMaxSeverity() const { return maxSeverity; }
    double getTotalWaitTime() const { return totalWaitTime; }
    int getWaitTimeCount() const { return waitTimeCount; }

    // Setters for loading
    void setWaitingCount(int count) { waitingCount = count; }
    void setAdmittedCount(int count) { admittedCount = count; }
    void setMaxSeverity(int severity) { maxSeverity = severity; }
    void setTotalWaitTime(double time) { totalWaitTime = time; }
    void setWaitTimeCount(int count) { waitTimeCount = count; }

private:
    int waitingCount = 0;
    int admittedCount = 0;
    int maxSeverity = 0;
    double totalWaitTime = 0.0;
    int waitTimeCount = 0;
};

#endif // STATS_HPP
