#ifndef FLOATLAYOUT_H
#define FLOATLAYOUT_H

#include "customdevice.h"

#include <QWheelEvent>
#include <QGraphicsView>
#include <QScrollBar>

class FloatLayout : public QGraphicsView {
    Q_OBJECT

public:
    explicit FloatLayout(QGraphicsProxyWidget * customDevice,
                             QWidget * parent);
    explicit FloatLayout(QList<QGraphicsProxyWidget *> customDeviceList,
                         QWidget * parent = nullptr);
    ~FloatLayout();
    void setTotalValue(int total); // 设置total的值
    /* 添加部件 */
    void addWidget(QGraphicsProxyWidget * customDevice);
    void addWidget(QWidget * qWidget);
    void addWidget(QGraphicsProxyWidget * customDevice, int x, int y);
    void addWidget(QWidget * qWidget, int x, int y);
    /* 移除部件 */
    void removeWidget(int pos);
    void removeWidget(int x, int y);

private:
    int row;                                            // 行
    int column;                                         // 列
    int total;                                          // 设备总数
    int count;                                          // 设备计数
    qreal marginX;                                      // 水平外边距
    int marginY;                                        // 垂直外边距
    double customDeviceWidth;                           // 设备宽度
    double customDeviceHeight;                          // 设备高度
    qreal scaleValue;                                   // 缩放值
    qreal scaleStep;                                    // 缩放步进值
    QGraphicsScene * graphicsScene;                     // 图形场景
    QGraphicsRectItem * graphicsRectItem;               // 矩形图元(用于拖动)
    QList<QGraphicsProxyWidget *> graphicsWidgetList;   // 图形代理部件的列表
    void resizeEvent(QResizeEvent * size);              // 大小变化事件
    bool eventFilter(QObject * widget, QEvent * event); // 鼠标滚动过滤事件
    void widthChanged();                                // 宽度改变时调整部件位置的函数
    void widgetCalculate();                             // 计算部件宽、高、行、列和设备部件x轴的外边距的函数
    void allShow();                                     // 缩小设备部件以显示全部设备部件的函数
    void checkFreeSpace();                              // 检查部件是否有空余位置以放大设备部件

};

#endif // FLOATLAYOUT_H
