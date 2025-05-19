# ERMS – Emergency Room Management System

[![Build](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License: Educational](https://img.shields.io/badge/license-Educational-lightgrey.svg)](#license)

> **Repo:** <https://github.com/laila2005/ERMS>

---

## ✨ About

**ERMS** is a **C++17** console application that mimics an emergency-room workflow:

* Tracks **patients** & **doctors**.
* Prioritises treatment by **severity (1 – 5)**.
* Persists everything in human-readable **JSON**.

Ideal for learning data structures, file I/O, and basic OOP in C++.

---

## 🚀 Features

| Category | Details |
|----------|---------|
| **Patient flow** | Add, _admit next_ (highest severity), discharge |
| **Instant views** | List active patients • Lookup doctors • Live ER statistics |
| **Persistence** | Saves to `doctors.json`, `active_patients.json`, etc. |
| **Pre-loaded data** | 3 doctors + 3 patients ready on first launch |

---

## 📋 Requirements

| Tool | Version |
|------|---------|
| **OS** | Linux (tested on Ubuntu 22.04) |
| **Compiler** | `g++` with C++17 |
| **Build** | `cmake` ≥ 3.16, `make` |
| **Library** | [`nlohmann/json`](https://github.com/nlohmann/json) |

---

## 🔧 Installation

```bash
# 1 · Clone
git clone https://github.com/laila2005/ERMS.git ~/ERMS
cd ~/ERMS
```

# 2 · Install build deps
``` ruby
sudo apt update
sudo apt install build-essential cmake
```

# 3 · Install nlohmann/json header
``` ruby
sudo mkdir -p /usr/include/nlohmann
sudo wget -qO /usr/include/nlohmann/json.hpp \
     https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
```

# 4 · Build and Run
``` ruby
cmake -B build
cmake --build build
./build/erms
```
```
ERMS/
├── include/
│   ├── ERMS.hpp          # core class
│   ├── Storage.hpp       # JSON I/O
│   ├── Stats.hpp         # statistics
│   └── Types.hpp         # Patient / Doctor structs
├── src/
│   ├── ERMS.cpp
│   ├── Storage.cpp
│   ├── Stats.cpp
│   └── main.cpp
└── CMakeLists.txt
```
## 🕹️ Usage
ERMS boots into an 8-item menu and auto-loads any *.json in ~/ERMS/.
|  #  | Option                   | Description                    |
| :-: | ------------------------ | ------------------------------ |
|  1  | **Add Patient**          | Enter ID, name, severity       |
|  2  | **Admit Next**           | Pulls highest-severity patient |
|  3  | **Discharge**            | Remove by ID                   |
|  4  | **List Active Patients** | Current in-treatment list      |
|  5  | **Lookup Doctor**        | Doctor details by ID           |
|  6  | **Display Stats**        | Waiting, admitted, etc.        |
|  7  | **Save Data**            | Manual save (auto on exit)     |
|  8  | **Exit**                 | Quit & auto-save               |

## 🤝 Contributing
This is a student project—issues and PRs are welcome!
Feel free to fork, improve, or suggest features.

## 📜 License
Educational use only – not licensed for commercial deployment.

## Team Members
- Laila Mohamed Fikry
- Eslam Mohamed Ahmed
- Sara Ahmed Mohamed 
