#ifndef AUDIOSETTINGSWIDGET_H
#define AUDIOSETTINGSWIDGET_H

#include <QWidget>
#include "audiomanager.h"

namespace Ui {
    class AudioSettingsWidget;
}

class AudioSettingsWidget : public QWidget {
    Q_OBJECT
public:
    AudioSettingsWidget(QWidget *parent = 0);
    ~AudioSettingsWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AudioSettingsWidget *ui;
    AudioManager*           audio;
};

#endif // AUDIOSETTINGSWIDGET_H
