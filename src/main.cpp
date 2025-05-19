#include "ERMS.hpp"
#include <iostream>
#include <limits>

int main() {
    // Predefined doctors
    std::vector<Doctor> doctors = {
        {101, "Mariam Omar", "Neurology"},
        {102, "Ahmed Hassan", "Cardiology"},
        {103, "Sara Ali", "General Surgery"}
    };

    // Initialize ERMS with doctors
    ERMS erms(doctors);

    // Preload sample patients only if no active patients were loaded
    if (!erms.hasActivePatients()) {
        erms.arrive({1, "Eslam Mohamed", 4, erms.getTimestamp()});
        erms.arrive({2, "Sara Ahmed", 2, erms.getTimestamp()});
        erms.arrive({3, "Laila Mohamed", 5, erms.getTimestamp()});
    }

    // Interactive menu
    while (true) {
        std::cout << "\n=== Emergency Room Management System ===\n";
        std::cout << "1. Add patient\n2. Admit next patient\n3. Discharge patient\n";
        std::cout << "4. List active patients\n5. Lookup doctor\n6. Display stats\n";
        std::cout << "7. Save data\n8. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::string name;
            int severity, id;
            std::cout << "Enter patient ID: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Enter patient name: ";
            std::getline(std::cin, name);
            std::cout << "Enter severity (1-5): ";
            std::cin >> severity;
            erms.arrive({id, name, severity, erms.getTimestamp()});
        } else if (choice == 2) {
            erms.admitNext();
        } else if (choice == 3) {
            int id;
            std::cout << "Enter patient ID to discharge: ";
            std::cin >> id;
            erms.discharge(id);
        } else if (choice == 4) {
            erms.listActive();
        } else if (choice == 5) {
            int id;
            std::cout << "Enter doctor ID: ";
            std::cin >> id;
            erms.lookupDoctor(id);
        } else if (choice == 6) {
            erms.displayStats();
        } else if (choice == 7) {
            erms.saveData();
        } else if (choice == 8) {
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Invalid option\n";
        }
    }
    return 0;
}
