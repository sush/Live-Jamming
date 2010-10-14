#include <Request.h>

Request::Request(field_t id, int type, std::string const & name, field_t param)
  :_id(id), _name(name), _type(type)
{
  if (type == SEND)
    _retry = param;
  else if (type == RECV)
    _response_to = param;

}

Request::Request(field_t id, int, std::string const & name, bool retry, field_t response_to)
  :_id(id), _name(name), _type(BIDIRECTIONNAL), _retry(retry), _response_to(response_to)
{}

Request::~Request()
{}

field_t		Request::getId() const
{
  return _id;
}

std::string const &	Request::getName() const
{
  return _name;
}

bool			Request::getRetry() const
{
  assert(_type == SEND || _type == BIDIRECTIONNAL);
  return _retry;
}

field_t			Request::getResponseTo() const
{
  assert(_type == RECV || _type == BIDIRECTIONNAL);
  return _response_to;
}

bool			Request::IsResponseTo() const
{
  assert(_type == RECV || _type == BIDIRECTIONNAL);
  return _response_to != RESPONSETONOTHING;
}

bool			Request::IsSend() const
{
  return _type == SEND;
}
