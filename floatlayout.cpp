#include "floatlayout.h"

FloatLayout::FloatLayout(QList<CustomDevice *> customDeviceList,
                         QWidget * parent) :
    QGraphicsView (parent) {
    graphicsScene = new QGraphicsScene(this);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 去掉垂直滚动条能防止下方图像残留
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 去掉垂直滚动条能防止右侧图像残留

    total = customDeviceList.size(); // 子控件的总数

    if (total > 0) { // 如果存在子控件
        graphicsRectItem = graphicsScene->addRect(0, 0, width(), height());
        graphicsRectItem->setFlags(QGraphicsItem::ItemIsMovable); // 让矩形图元可以被拖动
        graphicsWidgetList = customDeviceList;
        for (count = 0; count < total; count++) {
            graphicsWidgetList[count]->setParentItem(graphicsRectItem);
        }

        setAlignment(Qt::AlignTop | Qt::AlignLeft); // 设置图形视图的左上角为开始位置
        setSceneRect(0, 0, width(), height());
        graphicsScene->setSceneRect(0, 0, width(), height());

        setScene(graphicsScene);

        marginY = 10;
        scaleValue = 1;
        scaleStep = 0.01;
    }
}
FloatLayout::~FloatLayout() {}
/* 控件的大小变化事件 */
void FloatLayout::resizeEvent(QResizeEvent * size) {
    QWidget::resizeEvent(size);
    if (total > 0) {
        allShow();
        checkFreeSpace();
    }
}
/* 鼠标滚动过滤事件 */
bool FloatLayout::eventFilter(QObject *widget, QEvent *event) {
    if (widget && total > 0) {
        if (event->type() == QEvent::Wheel) {
            QWheelEvent * wheelEvent = static_cast<QWheelEvent *>(event);
            int y = wheelEvent->angleDelta().y();
            if (y < 0) {
                scale(1.0 / 1.2, 1.0 / 1.2); // 缩小图形视图
            } else if (y > 0) {
                scale(1.2, 1.2); // 放大图形视图
            }
        }
    }
    return true;
}
/* 计算控件宽高行列以及设备控件x轴的外边距 */
void FloatLayout::widgetCalculate() {
    qreal width = this->width();  // 滚动区域的宽度
    count = 0;
    customDeviceWidth = graphicsWidgetList[count]->geometry().width() * scaleValue; // 子控件的宽度
    customDeviceHeight = graphicsWidgetList[count]->geometry().height() * scaleValue; // 子控件的高度

    column = (int(width) % int(customDeviceWidth)) > 0
            ? (int(width / customDeviceWidth) - 1) > 0
              ? int(width / customDeviceWidth) - 1
              : 1
              : int(width / customDeviceWidth); // 通过滚动区域的宽度除于(自定义设备控件的宽度和水平外边距相加的和)得到每行的列数
    row = total % column > 0
            ? (total / column) + 1
            : (total / column); // 通过子控件总数和列数取模,有剩余时行数增1,否则为实际行数
    marginX = (width - (column * customDeviceWidth)) / (column + 1);
}
/* 宽度变化时调整控件位置 */
void FloatLayout::widthChanged() {
    qreal width = this->width();  // 滚动区域的宽度
    qreal height = this->height();
    widgetCalculate();
    for (int rowSequence = 0; rowSequence < row; rowSequence++) {
        for (int columnSequence = 0; columnSequence < column; columnSequence++, count++) {
            if (count >= total) { // 如控件计数值超过控件总数表示子控件已全部设置好位置区域
                break;
            } else {
                graphicsWidgetList[count]
                        ->setGeometry(QRectF(marginX * (columnSequence + 1)
                                             + customDeviceWidth * columnSequence,
                                             marginY * (rowSequence + 1)
                                             + customDeviceHeight * rowSequence,
                                             (marginX * ((columnSequence + 1) == column
                                                         ? columnSequence + 2
                                                         : columnSequence + 1))
                                             + customDeviceWidth * (columnSequence),
                                             (marginY * ((rowSequence + 1) == column
                                                         ? rowSequence + 2
                                                         : rowSequence + 1))
                                             + customDeviceHeight * (rowSequence + 1))); // 为子控件设置位置区域
            }
        }
    }
    graphicsRectItem->setRect(0, 0, width, height);
}
/* 缩小设备控件以展示全部的设备控件 */
void FloatLayout::allShow() {
    qreal height = this->height();
    while ((row * customDeviceHeight) + marginY * (row + 1) > height) {
        count = 0;
        scaleValue -= scaleStep;
        widgetCalculate();
        for (; count < total; count++) {
            graphicsWidgetList[count]->setScale(scaleValue);
        }
    }
    widthChanged();
}
/* 检查控件空余的空间来放大设备控件 */
void FloatLayout::checkFreeSpace() {
    qreal height = this->height();
    while ((height - (row * customDeviceHeight + marginY * (row + 1)))
           > (marginY * 2 + customDeviceHeight)) {
        count = 0;
        scaleValue += scaleStep;
        widgetCalculate();
        for (; count < total; count++) {
            graphicsWidgetList[count]->setScale(scaleValue);
        }
    }
    widthChanged();
}
/* 设置total(自定义设备数量)的值 */
void FloatLayout::setTotalValue(int total) {
    for (count = this->total - 1; total <= count; --count) {
        graphicsScene->removeItem(graphicsWidgetList[count]);
        graphicsWidgetList.removeAt(count);
    }
    this->total = count + 1;
    widthChanged();
}
