#ifndef AUDIOSETTINGSWIDGET_H
#define AUDIOSETTINGSWIDGET_H

#include <QWidget>

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
};

#endif // AUDIOSETTINGSWIDGET_H
