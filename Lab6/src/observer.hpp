#pragma once

#include <fstream>
#include <iostream>

class IEntityObserver {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~IEntityObserver() = default;
};

class LogEntityObserver : public IEntityObserver {
public:
    LogEntityObserver(const std::string& path)
        : path_to_logfile(path) {}

    void update(const std::string& message) override {
        std::ofstream file;
        file.open(path_to_logfile, std::ios::app | std::ios::out);

        if (!file) {
            std::cout << "Failed to open file!\n\n";
        }

        file << message << '\n';
    }   

private:
    std::string path_to_logfile;
};


class PrintEntityObserver : public IEntityObserver {
public:
    PrintEntityObserver() {}

    void update(const std::string& message) override {
        std::cout << message << std::endl;
    }
};