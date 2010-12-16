#ifndef JACKINPUT_H
#define JACKINPUT_H

#include <Component_Jam.h>
#include <Packet.h>
#include <jackdefault.h>

class Component_Jam;

class JackInput : public JackDefault
{
 public:
  JackInput(Component_Jam&);
  ~JackInput();
  Component_Jam&  jam;
};

#endif // JACKINPUT_H
