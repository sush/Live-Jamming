#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <iostream>
#include <string>
#include <Protocol.h>
#include <assert.h>

#define RESPONSETONOTHING 0


#define SEND		1
#define RECV		2
#define BIDIRECTIONNAL	3

#define RETRY		true
#define NORETRY		false

class Request
{
public:
  Request(field_t, int, std::string const &, field_t);
  Request(field_t, int, std::string const &, bool, field_t);
  virtual ~Request();

  field_t		getId() const;
  std::string const &	getName() const;
  bool			getRetry() const;
  field_t		getResponseTo() const;
  bool			IsSend() const;
  bool			IsResponseTo() const;

private:
  field_t		_id;
  std::string const 	_name;
  int			_type;
  bool			_retry;
  field_t		_response_to;
};

#endif // ! __REQUEST_H__
