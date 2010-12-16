#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <celt/celt.h>

#include <Component_Jam.h>
#include <jackinput.h>
#include <jackoutput.h>

class Component_Jam;
class JackInput;

class AudioEngine
{
 public:
    AudioEngine(Component_Jam&);
    ~AudioEngine();
    void start();
    void stop();

 public:
    JackOutput  *output;
    JackInput   *input;

 private:
    Component_Jam&  jam;

private:
    CELTMode	*celt_mode;
    CELTEncoder	*celt_encoder;
    CELTDecoder	*celt_decoder;
};

#endif // AUDIOENGINE_H
