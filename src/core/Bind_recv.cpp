#include <Bind_recv.h>

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// do not forget to set theses in respective manager;

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

Bind_recv::Bind_recv(IComponent *instance, IComponent::pMethod method)
  :_instance(instance), _method(method), _needsAuth(true)
{}

Bind_recv::~Bind_recv()
{

}

void					Bind_recv::Receive(Packet_v1 const * packet_v1, Session * session) const
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
//       if (_componentId && _requestId != RESPONSETONOTHING)
// 	session->CancelTimer(_componentId, _requestId);
      if (_instance != 0 && _method != 0)
	(_instance->*_method)(packet_v1, session);
    }
    // send a need_auth_request to clients if in   !   S E R V E R   !!   S E R V E R   !
    // pop a error message in client requesting auth in   !   C L I E N T   !!   C L I E N T   !
}

