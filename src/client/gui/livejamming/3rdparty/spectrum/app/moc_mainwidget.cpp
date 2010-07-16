/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created: Fri Jul 16 17:14:59 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   12,   11,   11, 0x0a,
      71,   64,   11,   11, 0x0a,
     124,   99,   11,   11, 0x0a,
     191,  173,   11,   11, 0x0a,
     231,  216,   11,   11, 0x0a,
     270,  261,   11,   11, 0x0a,
     303,  294,   11,   11, 0x0a,
     333,   11,   11,   11, 0x08,
     350,   11,   11,   11, 0x08,
     371,   11,   11,   11, 0x08,
     397,   11,   11,   11, 0x08,
     416,  294,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWidget[] = {
    "MainWidget\0\0mode,state\0"
    "stateChanged(QAudio::Mode,QAudio::State)\0"
    "format\0formatChanged(QAudioFormat)\0"
    "position,length,spectrum\0"
    "spectrumChanged(qint64,qint64,FrequencySpectrum)\0"
    "message,timeoutMs\0infoMessage(QString,int)\0"
    "heading,detail\0errorMessage(QString,QString)\0"
    "position\0positionChanged(qint64)\0"
    "duration\0bufferDurationChanged(qint64)\0"
    "showFileDialog()\0showSettingsDialog()\0"
    "showToneGeneratorDialog()\0initializeRecord()\0"
    "dataDurationChanged(qint64)\0"
};

const QMetaObject MainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWidget,
      qt_meta_data_MainWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateChanged((*reinterpret_cast< QAudio::Mode(*)>(_a[1])),(*reinterpret_cast< QAudio::State(*)>(_a[2]))); break;
        case 1: formatChanged((*reinterpret_cast< const QAudioFormat(*)>(_a[1]))); break;
        case 2: spectrumChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< const FrequencySpectrum(*)>(_a[3]))); break;
        case 3: infoMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: errorMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: positionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: bufferDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: showFileDialog(); break;
        case 8: showSettingsDialog(); break;
        case 9: showToneGeneratorDialog(); break;
        case 10: initializeRecord(); break;
        case 11: dataDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
