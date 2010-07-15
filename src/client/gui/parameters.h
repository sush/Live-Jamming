#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QString>

class Parameters
{
public:
    Parameters();
    bool    haveId() const;
    void    clearId();

    QString login;
    QString password;
    QString serverIp;
    QString serverPort;
};

#endif // PARAMETERS_H
