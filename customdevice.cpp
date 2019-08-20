#include "customdevice.h"

CustomDevice::CustomDevice(QGraphicsItem * parent) :
    QGraphicsProxyWidget (parent) {
    initCustomDevice();
}
CustomDevice::~CustomDevice() {};
CustomDevice::CustomDevice(QString name, QString iconPath, QString status,
                           QGraphicsItem * parent) :
    QGraphicsProxyWidget (parent) {
    this->name = name;
    this->iconPath = iconPath;
    this->status = status;
    initCustomDevice();
}
/* 初始化自定义设备的样式 */
void CustomDevice::initCustomStyle() {
    customDeviceButton->setFixedSize(120, 160);
    customDeviceButton->setStyleSheet("background: rgb(0, 95, 108);"
                                      "border: 0;"
                                      "color: white;");
}
/* 初始化自定义设备 */
void CustomDevice::initCustomDevice() {
    customDeviceButton = new QPushButton();
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QVBoxLayout * vBoxLayout = new QVBoxLayout(customDeviceButton);
    vBoxLayout->setSpacing(0);
    vBoxLayout->setMargin(0);
    customDeviceButton->setLayout(vBoxLayout);
    /* 设备名字部件 */
    titleName = new QLabel(customDeviceButton);
    titleName->setObjectName("titleName");
    titleName->setAlignment(Qt::AlignCenter);
    titleName->setFixedHeight(35);
    /* 图标部件 */
    iconControl = new QLabel(customDeviceButton);
    iconControl->setObjectName("iconControl");
    /* 状态部件 */
    statusPrompt = new QLabel(customDeviceButton);
    statusPrompt->setObjectName("statusPrompt");
    statusPrompt->setAlignment(Qt::AlignCenter);
    statusPrompt->setFixedHeight(35);

    vBoxLayout->addWidget(titleName);
    vBoxLayout->addWidget(iconControl);
    vBoxLayout->addWidget(statusPrompt);
    /* 初始化自定义样式和内容 */
    initCustomStyle();
    setCustomDeviceContent(name, iconPath, status);

    setWidget(customDeviceButton);
}
/* 自定义设备的鼠标点击事件 */
void CustomDevice::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if (event) {
        customDeviceButton->clicked();
    }
}
/* 设置或修改自定义设备内容的接口函数 */
void CustomDevice::setCustomDeviceContent(QString name, QString iconPath, QString status) {
    titleName->setText(name);
    QString iconBackground = QStringLiteral("border-image: url(\"%1\");").arg(iconPath);
    iconControl->setStyleSheet(iconBackground);
    statusPrompt->setText(status);
    if (status == "离线") {
        statusPrompt->setStyleSheet("color: red;");
    }
}
