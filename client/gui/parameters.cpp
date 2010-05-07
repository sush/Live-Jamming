#include "parameters.h"

Parameters::Parameters()
{
}

bool    Parameters::haveId()
{
    return login.isEmpty() == false && password.isEmpty() == false;
}
