#ifndef CSVBACKUP_H
#define CSVBACKUP_H

#include <QObject>
#include <fstream>
#include <string>

#include "Data.h"

class CSVBackUp : public QObject
{
    Q_OBJECT

public:
    CSVBackUp();
    ~CSVBackUp();

public slots:
    void BackUpData(const Data &);

private:
    std::string backup_fname;
    std::ofstream backup_f;
};

#endif