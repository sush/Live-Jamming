#include <IComponent.h>
#include <Session.h>

field_t		IComponent::getComponentId()
{
  return _componentId;
}
void			IComponent::setBindingsRecv(m_bindings_recv & bindingsRecv)
{
  _bindingsRecv = &bindingsRecv;
}

void			IComponent::setRegisteredRequests(m_request & requests)
{
  _registeredRequests = &requests;
}

Packet_v1  const	*IComponent::getOrigPacket(Packet_v1 const *p, Session *session)
{
  assert(_registeredRequests->find(p->getRequestId())->second->getResponseTo() != RESPONSETONOTHING);
  return session->getOriginatedPacket(_componentId, _registeredRequests->find(p->getRequestId())->second->getResponseTo());
}
