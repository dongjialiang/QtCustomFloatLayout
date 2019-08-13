#ifndef CUSTOMDEVICE_H
#define CUSTOMDEVICE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>

class CustomDevice :
        public QPushButton {
    Q_OBJECT
public:
    explicit CustomDevice(QWidget * parent = nullptr);
    explicit CustomDevice(QString name, QString icon, QString status, QWidget * parent = nullptr);
    ~CustomDevice();
private:
    void customStyle(); // 自定义样式
};

#endif // CUSTOMDEVICE_H
