#ifndef __BIND_RECV_H__
#define __BIND_RECV_H__

class Bind_recv;

#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <IComponent.h>
#include <Protocol.h>
#include <Session.h>
#include <Packet_v1.h>
  

// template this class too
// to get bind_recv for servermanager and bind_recv for clientmanager
// maybe put a generic manager so no template is needed after all
// -> generic manager abstract class and inheritants client + server managers
class Bind_recv
{
public:
  friend class Manager;
					Bind_recv(IComponent *, IComponent::pMethod,
						  proto_v1_packet_type = NOREQUEST,
						  bool needsAuth = true);
  virtual				~Bind_recv();

  static void				setIO(boost::asio::io_service *);
  static void				setSocket(boost::asio::ip::udp::socket *);
  static void				setPool(boost::threadpool::pool *);

  void					Receive(Packet_v1 const *, Session *);
  proto_v1_packet_type			getSendType() const;

private:
  static boost::asio::io_service	*_io_service;
  static boost::asio::ip::udp::socket	*_socket;
  static boost::threadpool::pool	*_pool;
  IComponent *				_instance;
  IComponent::pMethod			_method;
  proto_v1_packet_type			_sendType;
  bool					_needsAuth;
};

#endif // ! __BIND_RECV_H__
