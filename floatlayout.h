#ifndef FLOATLAYOUT_H
#define FLOATLAYOUT_H

#include "customdevice.h"

#include <QScrollArea>
#include <QPushButton>
#include <QScrollBar>

class FloatLayout : public QScrollArea {
    Q_OBJECT
public:
    explicit FloatLayout(QWidget * parent = nullptr);
    ~FloatLayout();
private:
    int row;
    int column;
    int total;
    int marginX; // 水平外边距
    int marginY; // 垂直外边距
    QList<CustomDevice *> childCustomDevice; // 自定义设备控件列表
    QWidget * devicePage; // 放置设备控件的页面
    void resizeEvent(QResizeEvent * size); // 大小变化事件
};

#endif // FLOATLAYOUT_H
