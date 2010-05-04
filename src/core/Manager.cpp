#include <Manager.h>

unsigned int		timeOutTest_maxRetry = 3;

Manager::Manager(boost::asio::io_service & io_service, boost::threadpool::pool & pool, boost::asio::ip::udp::socket & socket)
  :_io_service(io_service), _pool(pool), _socket(socket)
{
  // we should be able to remove this lines since none of that info is need for a bind_recv element
  // anymore
  Bind_recv::_io_service = &io_service;
  Bind_recv::_pool = &_pool;
  Bind_recv::_socket = &_socket;
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
    _pool.schedule(boost::bind(&Manager::Send_bind, this, packet_v1, session, RETRY));
  else
    {}//      delete packet_v1;
}

void		Manager::Send_bind(Packet_v1 *packet_v1, Session *session, bool retry) const
{
  Send(packet_v1, session, retry);
}

void		Manager::Send(Packet_v1 *packet_v1, Session * session, bool retry) const
{
#ifdef _DEBUG
  std::cout << "<..... SEND .....> ";
  packet_v1->Print_v1();
#endif
  packet_v1->setSessionId(session->getSessionId());
  if (retry == RETRY)
    session->setRetry(packet_v1);
  // schedule a retry after a delay with no expected response for that send
  _socket.async_send_to(boost::asio::buffer(packet_v1->getData()), session->getEndpoint(),
			boost::bind(&Manager::CallBack_handle_send, this, packet_v1));
}

void		Manager::Send(Packet_v1 *packet_v1, boost::asio::ip::udp::endpoint &endpoint) const
{
#ifdef _DEBUG
  std::cout << "<..... SEND .....> ";
  packet_v1->Print_v1();
#endif
  _socket.async_send_to(boost::asio::buffer(packet_v1->getData()), endpoint,
			boost::bind(&Manager::CallBack_handle_send, this, packet_v1));
}

void		Manager::Send(proto_v1_packet_type packetType, Session * session, bool retry) const
{
  Packet_v1	*packet_v1 = new Packet_v1(&session->getEndpoint());

  packet_v1->setType(packetType);
  Send(packet_v1, session, retry);
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
  Send(SESSION_TIMEOUT, session, NORETRY);
  session->Print();
  std::cout << "-> sending timeout test" << std::endl;
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
