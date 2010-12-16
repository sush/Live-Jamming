#include "audioengine.h"

AudioEngine::AudioEngine(Component_Jam& jam_):
        jam(jam_)
{
    output = new JackOutput();
    input = new JackInput(jam);
}

void AudioEngine::start(){
    input->start();
    output->start();
}

void AudioEngine::stop(){
    input->stop();
    output->stop();
}

//void AudioEngine::celtCreate(){
//    celt_mode = celt_mode_create(sample_rate, buffer_size, NULL);
//    celt_encoder = celt_encoder_create(celt_mode, 1, NULL);
//    celt_decoder = celt_decoder_create(celt_mode, 1, NULL);
//}


//void AudioEngine::celtDestroy(){
//    celt_encoder_destroy(celt_encoder);
//    celt_decoder_destroy(celt_decoder);
//    celt_mode_destroy(celt_mode);
//}

AudioEngine::~AudioEngine(){
    delete input;
    delete output;
}
