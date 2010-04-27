#ifndef __ICOMPONENT_H__
#define __ICOMPONENT_H__

#include <iostream>
#include <map>
#include <Protocol.h>
#include <Packet_v1.h>

class IComponent
{
 public:
  typedef void	(IComponent::*pMethod)(Packet_v1 *);
  typedef struct
  {
    IComponent *	instance;
    pMethod		method;
  }PacketBind;
  typedef std::map<field_t, PacketBind>		m_packet_bindings;
  typedef m_packet_bindings::iterator		m_packet_bindings_it;
  typedef m_packet_bindings::const_iterator	m_packet_bindings_cit;
  
  virtual ~IComponent() {};
  virtual void	PacketBindings() = 0;
};



#endif // ! __ICOMPONENT_H__

