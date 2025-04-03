#include "CSVBackUp.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

CSVBackUp::CSVBackUp()
{
    // Generate a name for backup file (current time).
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "backup/%Y%m%d_%H%M%S.csv");
    backup_fname = ss.str();
    backup_f.open(backup_fname);
    backup_f << "Height,Temperature,Pressure\n";
}

void CSVBackUp::BackUpData(const Data &data)
{
    if (!backup_f.is_open())
    {
        std::cerr << "Failed to open the backup file." << std::endl;
        return;
    }
    backup_f << data.height << "," << data.temp << "," << data.pressure << '\n';
}

CSVBackUp::~CSVBackUp() { backup_f.close(); }