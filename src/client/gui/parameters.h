#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QString>

class Parameters
{
public:
    Parameters();
    bool    haveId();

    QString login;
    QString password;
};

#endif // PARAMETERS_H
