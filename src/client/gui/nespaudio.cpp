#include "nespaudio.h"

NespAudio::NespAudio()
{
}

QStringList NespAudio::getODevices(){
    return this->getDevices(QAudio::AudioOutput);
}

QStringList NespAudio::getIDevices(){
    return this->getDevices(QAudio::AudioInput);
}

QString NespAudio::getDefaultODevice(){
    return QAudioDeviceInfo::defaultOutputDevice().deviceName();
}

QString NespAudio::getDefaultIDevice(){
    return QAudioDeviceInfo::defaultInputDevice().deviceName();
}

void NespAudio::testAudio(){
    QAudioFormat format;

    format.setFrequency(8000);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning()<<"raw audio format not supported by backend, cannot play audio.";
        return;
    }

}

/* Private */
QStringList NespAudio::getDevices(QAudio::Mode mode){
    QStringList list;
    foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(mode)){
        if(!deviceInfo.isNull())
        list << deviceInfo.deviceName();
    }
    return list;
}
