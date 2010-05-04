#include <Bind_recv.h>

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// do not forget to set theses in respective manager;

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

boost::asio::io_service		*Bind_recv::_io_service;
boost::asio::ip::udp::socket	*Bind_recv::_socket;
boost::threadpool::pool		*Bind_recv::_pool;

Bind_recv::Bind_recv(IComponent *instance, IComponent::pMethod method,
		     proto_v1_packet_type sendType, bool needsAuth)
  :_instance(instance), _method(method), _sendType(sendType), _needsAuth(needsAuth)
{

}
Bind_recv::~Bind_recv()
{

}

void				Bind_recv::setIO(boost::asio::io_service * io_service)
{
  _io_service = io_service;
}

void				Bind_recv::setSocket(boost::asio::ip::udp::socket * socket)
{
  _socket = socket;
}

void				Bind_recv::setPool(boost::threadpool::pool * pool)
{
  _pool = pool;
}

void					Bind_recv::Receive(Packet_v1 const * packet_v1, Session * session)
{
  // on Server:is the client auth
  // on client:are we auth on the server
  // both refer to session->islogged
  //
  // not  implemented yet session->islogged always returns  true

  //
  // no need auth request type implemented so do not uncomment this if
  // unless u have implemented it
  //  if (!_needsAuth || session && _needsAuth == session->IsLogged())
    {
      // if packet received is a response to a waiting send
      if (_sendType != NOREQUEST)
	session->CancelTimer(_sendType);
      (_instance->*_method)(packet_v1, session);
    }
    // send a need_auth_request to clients if in   !   S E R V E R   !!   S E R V E R   !
    // pop a error message in client requesting auth in   !   C L I E N T   !!   C L I E N T   !
}


proto_v1_packet_type			Bind_recv::getSendType() const
{
  return _sendType;
}
