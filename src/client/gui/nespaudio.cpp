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

void NespAudio::startIO(){

      QAudioFormat format;
      // set up the format you want, eg.
      format.setFrequency(8000);
      format.setChannels(1);
      format.setSampleSize(8);
      format.setCodec("audio/pcm");
      format.setByteOrder(QAudioFormat::LittleEndian);
      format.setSampleType(QAudioFormat::UnSignedInt);

      QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
      if (!info.isFormatSupported(format)) {
          qWarning()<<"default format not supported try to use nearest";
          format = info.nearestFormat(format);
      }

      input = new QAudioInput(format, this);
      //QTimer::singleShot(3000, this, SLOT(stopRecording()));
      inputBuffer = input->start();
      output = new QAudioOutput(format, this);
      connect(output,SIGNAL(stateChanged(QAudio::State)),SLOT(finishedPlaying(QAudio::State)));
      output->start(inputBuffer);
}
void NespAudio::stopIO(){
    finishedPlaying(QAudio::IdleState);
    stopRecording();
}

/* SLOTS */
void NespAudio::stopRecording()
{
    input->stop();
    delete input;
}

void NespAudio::finishedPlaying(QAudio::State state)
{
  if(state == QAudio::IdleState) {
    output->stop();
    delete output;
  }
}

void NespAudio::stateChanged(QAudio::State newState)
   {
       switch (newState) {
           case QAudio::StoppedState:
               if (output->error() != QAudio::NoError) {
                   // Perform error handling
               } else {
                   // Normal stop
               }
               break;
           }
   }

/* PRIVATE */
QStringList NespAudio::getDevices(QAudio::Mode mode){
    QStringList list;
    foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(mode)){
        if(!deviceInfo.isNull())
        list << deviceInfo.deviceName();
    }
    return list;
}
