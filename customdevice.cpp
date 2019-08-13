#include "customdevice.h"

CustomDevice::CustomDevice(QWidget * parent) : QPushButton(parent) {
    QVBoxLayout * vBoxLayout = new QVBoxLayout();
    vBoxLayout->setSpacing(0);
    vBoxLayout->setMargin(0);
    setLayout(vBoxLayout);
    /* 设备名字控件 */
    QLabel * titleName = new QLabel(this);
    titleName->setObjectName("titleName");
    titleName->setFixedHeight(30);
    /* 图标控件 */
    QLabel * iconControl = new QLabel(this);
    iconControl->setObjectName("iconControl");
    /* 状态控件 */
    QLabel * statusPrompt = new QLabel(this);
    statusPrompt->setObjectName("statusPrompt");
    statusPrompt->setFixedHeight(30);

    vBoxLayout->addWidget(titleName);
    vBoxLayout->addWidget(iconControl);
    vBoxLayout->addWidget(statusPrompt);
    /* 自定义样式 */
    customStyle();
}
CustomDevice::~CustomDevice() {};
CustomDevice::CustomDevice(QString name, QString iconPath, QString status, QWidget * parent) :
    QPushButton (parent) {
    QVBoxLayout * vBoxLayout = new QVBoxLayout();
    vBoxLayout->setSpacing(0);
    vBoxLayout->setMargin(0);
    setLayout(vBoxLayout);
    /* 设备名字控件 */
    QLabel * titleName = new QLabel(this);
    titleName->setText(name);
    titleName->setObjectName("titleName");
    titleName->setAlignment(Qt::AlignCenter);
    titleName->setFixedHeight(30);
    /* 图标控件 */
    QLabel * iconControl = new QLabel(this);
    QString iconBackground = QStringLiteral("border-image: url(\"%1\");").arg(iconPath);
    iconControl->setStyleSheet(iconBackground);
    iconControl->setObjectName("iconControl");
    /* 状态控件 */
    QLabel * statusPrompt = new QLabel(this);
    statusPrompt->setText(status);
    statusPrompt->setObjectName("statusPrompt");
    statusPrompt->setAlignment(Qt::AlignCenter);
    statusPrompt->setFixedHeight(30);

    vBoxLayout->addWidget(titleName);
    vBoxLayout->addWidget(iconControl);
    vBoxLayout->addWidget(statusPrompt);
    /* 自定义样式 */
    customStyle();
}
void CustomDevice::customStyle() {
    setFixedWidth(120);
    setFixedHeight(160);
    QFile customDeviceFile(":/style/customDevice.qss");
    if (customDeviceFile.open(QFile::ReadOnly)) {
        QString customDeviceStyle = QLatin1String(customDeviceFile.readAll());
        setStyleSheet(customDeviceStyle);
        customDeviceFile.close();
    }
}
