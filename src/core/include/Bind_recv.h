#ifndef __BIND_RECV_H__
#define __BIND_RECV_H__

class Bind_recv;
class MainWindow;

#include <boost/asio.hpp>
#include <boost/threadpool.hpp>
#include <IComponent.h>
#include <Protocol.h>
#include <Session.h>
#include <Packet_v1.h>
#ifdef _GUI
 #include <mainwindow.h>
#endif
// template this class too
// to get bind_recv for servermanager and bind_recv for clientmanager
// maybe put a generic manager so no template is needed after all
// -> generic manager abstract class and inheritants client + server managers
class Bind_recv
{
public:
  friend class Manager;
#ifdef _GUI
  Bind_recv(IComponent *, IComponent::pMethod, MainWindow* = 0, MainWindow::pMethod = 0);
#else
  Bind_recv(IComponent *, IComponent::pMethod);
#endif
  virtual				~Bind_recv();

  void					Receive(Packet_v1 const *, Session *) const;

private:
  IComponent *				_instance;
  IComponent::pMethod			_method;
#ifdef _GUI
  MainWindow *				_guiInstance;
  MainWindow::pMethod			_guiMethod;
#endif
  bool					_needsAuth;
};

#endif // ! __BIND_RECV_H__
