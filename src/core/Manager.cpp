#include <Manager.h>
#include <Packet_v1.h>
#include <Protocol.h>
#include <Protocol_Session.h>
#include <Packet_v1_Channel.h>

unsigned int		timeOutTest_maxRetry = 3;

Manager::Manager(boost::asio::io_service & io_service, boost::threadpool::pool & pool, boost::asio::ip::udp::socket & socket)
  :_io_service(io_service), _pool(pool), _socket(socket)
{
  // we should be able to remove this lines since none of that info is need for a bind_recv element
  // anymore
  // try to call this pure virtual method in abstract class
  // Init_Components();
}

Manager::~Manager()
{}

boost::threadpool::pool		&Manager::getPool()
{
  return _pool;
}

boost::asio::io_service		&Manager::getIO()
{
  return _io_service;
}

void		Manager::CallBack_handle_send(Packet_v1 *) const
{
  // segfaults
  //  delete packet_v1;
}

void		Manager::CallBack_Send_TimeOut(Session * session, Packet_v1 *packet_v1, boost::system::error_code error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
    _pool.schedule(boost::bind(&Manager::Send_bind, this, packet_v1, session));
  else
    {}//      delete packet_v1;
}

void		Manager::Send_bind(Packet_v1 *packet_v1, Session *session) const
{
  Send(packet_v1, session);
}

void		Manager::Send(Packet_v1 *packet_v1, Session * session) const
{
  packet_v1->setSessionId(session->getSessionId());
  if (getRegisteredRequest(packet_v1->getComponentId(), packet_v1->getRequestId()).getRetry())
    session->setAutoRetry(packet_v1);
#ifdef _DEBUG
  std::cout << "<..... SEND .....> ";
  packet_v1->Print_v1();
#endif
  // schedule a retry after a delay with no expected response for that send
  _socket.async_send_to(boost::asio::buffer(packet_v1->getRawData()), session->getEndpoint(),
			boost::bind(&Manager::CallBack_handle_send, this, packet_v1));
}

void		Manager::Send(Packet_v1 *packet_v1, boost::asio::ip::udp::endpoint const &endpoint) const
{
#ifdef _DEBUG
  std::cout << "<..... SEND .....> ";
  packet_v1->Print_v1();
#endif
  _socket.async_send_to(boost::asio::buffer(packet_v1->getRawData()), endpoint,
			boost::bind(&Manager::CallBack_handle_send, this, packet_v1));
}

void		Manager::Send(field_t componentId, field_t requestId, Session * session) const
{
  Packet_v1	*packet_v1 = new Packet_v1(componentId, requestId);

  packet_v1->setSessionId(session->getSessionId());
  packet_v1->setComponentId(componentId);
  packet_v1->setRequestId(requestId);
  Send(packet_v1, session);
}

void		Manager::Send(field_t componentId, field_t requestId, boost::asio::ip::udp::endpoint const &endpoint) const
{
  Packet_v1	*packet_v1 = new Packet_v1(componentId, requestId);

  packet_v1->setComponentId(componentId);
  packet_v1->setRequestId(requestId);
  Send(packet_v1, endpoint);
}


void		Manager::CallBack_TimeOutTest(Session * session, boost::system::error_code const & error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
    _pool.schedule(boost::bind(&Manager::Send_TimeOutTest, this, session));
}

void		Manager::CallBack_TimeOutOccurred(Session * session, boost::system::error_code const & error_code)
{
  if (error_code != boost::asio::error::operation_aborted)
    {
      session->setTimeOutTestCount(session->getTimeOutTestCount() + 1);
      if (session->getTimeOutTestCount() >= timeOutTest_maxRetry)
	_pool.schedule(boost::bind(&Manager::Disconnect, this, session));
      else
	_pool.schedule(boost::bind(&Manager::Send_TimeOutTest, this, session));
    }
}

void		Manager::Send_TimeOutTest(Session * session)
{
  Send(SESSION_COMPONENTID, SESSION_TIMEOUT, session);
  session->CancelTimeOutTest();
  session->setTimeOutOccurred();
}

unsigned int	Manager::getRetryDelay() const
{
  return _retryDelay;
}

unsigned int	Manager::getTimeOutTestDelay() const
{
  return _timeOutTestDelay;
}

unsigned int	Manager::getTimeOutOccurredDelay() const
{
  return _timeOutOccurredDelay;
}

void		Manager::RegisterComponent(IComponent *component)
{
  std::string	e = "already registered component: [componentId:";
  e += component->getComponentId() +"]";
  if (_componentBindings.find(component->getComponentId()) != _componentBindings.end())
    throw e;

  field_t	componentId = component->getComponentId();
  _componentBindings[componentId] = new component_binding;
  component->setBindingsRecv(_componentBindings.find(componentId)->second->_bindingsRecv);
  component->setRegisteredRequests(_componentBindings.find(componentId)->second->_registeredRequests);
  component->BindingsRecv();
  component->RegisteredRequests();
}

bool					Manager::IsRegisteredComponent(field_t componentId) const
{
  return _componentBindings.find(componentId) != _componentBindings.end();
}

bool					Manager::IsRegisteredRequest(field_t componentId, field_t requestId) const
{
  assert(IsRegisteredComponent(componentId));
  return _componentBindings.find(componentId)->second->_registeredRequests.find(requestId) != _componentBindings.find(componentId)->second->_registeredRequests.end();
}

bool					Manager::IsBindRecv(field_t componentId, field_t requestId) const
{
  assert(IsRegisteredComponent(componentId));
  return _componentBindings.find(componentId)->second->_bindingsRecv.find(requestId) != _componentBindings.find(componentId)->second->_bindingsRecv.end();
}

Bind_recv const		&Manager::getBindRecv(field_t componentId, field_t requestId) const
{
  assert(IsBindRecv(componentId, requestId));
  return *(_componentBindings.find(componentId)->second->_bindingsRecv.find(requestId)->second);
}

Request const		&Manager::getRegisteredRequest(field_t componentId, field_t requestId) const
{
  assert(IsRegisteredRequest(componentId, requestId));
  return *(_componentBindings.find(componentId)->second->_registeredRequests.find(requestId)->second);
}
