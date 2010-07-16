/****************************************************************************
** Meta object code from reading C++ file 'engine.h'
**
** Created: Fri Jul 16 17:14:58 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "engine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'engine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Engine[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,    8,    7,    7, 0x05,
      79,   60,    7,    7, 0x05,
     119,  104,    7,    7, 0x05,
     156,  149,    7,    7, 0x05,
     193,  184,    7,    7, 0x05,
     223,  184,    7,    7, 0x05,
     260,  251,    7,    7, 0x05,
     290,  251,    7,    7, 0x05,
     348,  318,    7,    7, 0x05,
     403,  378,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     452,    7,    7,    7, 0x0a,
     469,    7,    7,    7, 0x0a,
     485,    7,    7,    7, 0x0a,
     502,  495,    7,    7, 0x0a,
     540,  495,    7,    7, 0x0a,
     579,    7,    7,    7, 0x08,
     599,  593,    7,    7, 0x08,
     632,    7,    7,    7, 0x08,
     658,  649,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Engine[] = {
    "Engine\0\0mode,state\0"
    "stateChanged(QAudio::Mode,QAudio::State)\0"
    "message,durationMs\0infoMessage(QString,int)\0"
    "heading,detail\0errorMessage(QString,QString)\0"
    "format\0formatChanged(QAudioFormat)\0"
    "duration\0bufferDurationChanged(qint64)\0"
    "dataDurationChanged(qint64)\0position\0"
    "recordPositionChanged(qint64)\0"
    "playPositionChanged(qint64)\0"
    "rmsLevel,peakLevel,numSamples\0"
    "levelChanged(qreal,qreal,int)\0"
    "position,length,spectrum\0"
    "spectrumChanged(qint64,qint64,FrequencySpectrum)\0"
    "startRecording()\0startPlayback()\0"
    "suspend()\0device\0setAudioInputDevice(QAudioDeviceInfo)\0"
    "setAudioOutputDevice(QAudioDeviceInfo)\0"
    "audioNotify()\0state\0"
    "audioStateChanged(QAudio::State)\0"
    "audioDataReady()\0spectrum\0"
    "spectrumChanged(FrequencySpectrum)\0"
};

const QMetaObject Engine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Engine,
      qt_meta_data_Engine, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Engine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Engine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Engine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Engine))
        return static_cast<void*>(const_cast< Engine*>(this));
    return QObject::qt_metacast(_clname);
}

int Engine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateChanged((*reinterpret_cast< QAudio::Mode(*)>(_a[1])),(*reinterpret_cast< QAudio::State(*)>(_a[2]))); break;
        case 1: infoMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: errorMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: formatChanged((*reinterpret_cast< const QAudioFormat(*)>(_a[1]))); break;
        case 4: bufferDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: dataDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: recordPositionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: playPositionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: levelChanged((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: spectrumChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< const FrequencySpectrum(*)>(_a[3]))); break;
        case 10: startRecording(); break;
        case 11: startPlayback(); break;
        case 12: suspend(); break;
        case 13: setAudioInputDevice((*reinterpret_cast< const QAudioDeviceInfo(*)>(_a[1]))); break;
        case 14: setAudioOutputDevice((*reinterpret_cast< const QAudioDeviceInfo(*)>(_a[1]))); break;
        case 15: audioNotify(); break;
        case 16: audioStateChanged((*reinterpret_cast< QAudio::State(*)>(_a[1]))); break;
        case 17: audioDataReady(); break;
        case 18: spectrumChanged((*reinterpret_cast< const FrequencySpectrum(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Engine::stateChanged(QAudio::Mode _t1, QAudio::State _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Engine::infoMessage(const QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Engine::errorMessage(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Engine::formatChanged(const QAudioFormat & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Engine::bufferDurationChanged(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Engine::dataDurationChanged(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Engine::recordPositionChanged(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Engine::playPositionChanged(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Engine::levelChanged(qreal _t1, qreal _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Engine::spectrumChanged(qint64 _t1, qint64 _t2, const FrequencySpectrum & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
