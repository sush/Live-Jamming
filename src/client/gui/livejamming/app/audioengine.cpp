#include "audioengine.h"

AudioEngine::AudioEngine(QObject *parent)
    :   QObject(parent)
    ,   _availableInputDevices(QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
    ,   _inputDevice(QAudioDeviceInfo::defaultInputDevice())
    ,   _input(0)
    ,   _inputIODevice(0)

{
    initialize();
}

const QStringList AudioEngine::inputDevices(){
    QStringList list;
    foreach(const QAudioDeviceInfo &deviceInfo, _availableInputDevices){
        if(!deviceInfo.isNull())
        list << deviceInfo.deviceName();
    }
    return list;
}

//-----------------------------------------------------------------------------
// Private functions
//-----------------------------------------------------------------------------
void AudioEngine::reset(){
   stopRecording();
   setInputState(QAudio::StoppedState);
   setInputFormat(QAudioFormat());
   delete _input;
   _input = 0;
   _inputIODevice = 0;
   /* NOT A PROPER _output END*/
}

bool AudioEngine::initialize(){
    bool result = false;

    reset();

    if (selectInputFormat()){
        _input = new QAudioInput(_inputDevice, _inputFormat, this);
        result = true;
    }
    return result;
}

void AudioEngine::stopRecording(){
    if(_input){
        _input->stop();
        _input->disconnect();
    }
    _inputIODevice = 0;
}

bool AudioEngine::selectInputFormat(){
    bool foundSupportedFormat = false;

    QAudioFormat format;
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setFrequency(8000);
    format.setChannels(1);

    if (_inputDevice.isFormatSupported(format))
        foundSupportedFormat = true;
    else
        format = QAudioFormat();

    setInputFormat(format);
    return foundSupportedFormat;
}

void AudioEngine::setInputFormat(const QAudioFormat &format){
    _inputFormat = format;
}

void AudioEngine::setInputState(QAudio::State state)
{
    _inputState = state;
}
