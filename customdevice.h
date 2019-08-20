#ifndef CUSTOMDEVICE_H
#define CUSTOMDEVICE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>

class CustomDevice :
        public QGraphicsProxyWidget {
    Q_OBJECT

public:
    explicit CustomDevice(QGraphicsItem * parent = nullptr);
    explicit CustomDevice(QString name, QString icon, QString status,
                          QGraphicsItem * parent = nullptr);
    ~CustomDevice();
    void setCustomDeviceContent(QString name, QString iconPath, QString status); // 设置(修改)自定义设备的内容

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    void initCustomDevice();          // 初始化自定义设备按钮部件
    void initCustomStyle();           // 自定义样式
    QString name;                     // 自定义设备的名字
    QString iconPath;                 // 自定义设备的图标位置
    QString status;                   // 自定义设备的状态
    QPushButton * customDeviceButton; // 自定义设备按钮部件
    QLabel * titleName;               // 自定义设备标题名字
    QLabel * iconControl;             // 自定义设备图标
    QLabel * statusPrompt;            // 自定义设备状态

};

#endif // CUSTOMDEVICE_H
