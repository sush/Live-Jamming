#include "parameters.h"

Parameters::Parameters() : login("dude"), password("12345678")
{
}

bool    Parameters::haveId()
{
    return login.isEmpty() == false && password.isEmpty() == false;
}
