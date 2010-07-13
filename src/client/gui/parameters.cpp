#include "parameters.h"

Parameters::Parameters() : login("dude"), password("12345678")
{
}

bool    Parameters::haveId() const
{
    return login.isEmpty() == false && password.isEmpty() == false;
}

void    Parameters::clearId()
{
    login.clear();
    password.clear();
}
