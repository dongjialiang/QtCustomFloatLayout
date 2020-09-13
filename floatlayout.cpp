#include "floatlayout.h"
#include <QGraphicsSceneMouseEvent>
#include <QSizePolicy>
#include <QDebug>

FloatLayout::FloatLayout(QGraphicsProxyWidget * customDevice,
                        QWidget * parent) :
    QGraphicsView (parent) {
    graphicsScene = new QGraphicsScene(this);

    total = 1; // 子部件的总数

    if (total > 0) { // 如果存在子部件
    graphicsRectItem = graphicsScene->addRect(0, 0, width(), height());
    graphicsRectItem->setFlags(QGraphicsItem::ItemIsMovable); // 让矩形图元可以被拖动
    graphicsWidgetList << customDevice;

    graphicsWidgetList[0]->setParentItem(graphicsRectItem);

    setAlignment(Qt::AlignTop | Qt::AlignLeft); // 设置图形视图的左上角为开始位置
    verticalScrollBar()->setStyleSheet("width: 1; height: 1;");   // 设置垂直滚动条宽高为1防止下方图像残留
    horizontalScrollBar()->setStyleSheet("width: 1; height: 1;"); // 设置水平滚动条宽高为1防止右侧图像残留
    // setSceneRect(0, 0, width(), height());
    // graphicsScene->setSceneRect(0, 0, width(), height());

        setScene(graphicsScene);

        marginY = 10;
        scaleValue = 1;
        scaleStep = 0.01;
        resize(width(), height());
    }
 }
FloatLayout::FloatLayout(QList<QGraphicsProxyWidget *> customDeviceList,
                        QWidget * parent) :
    QGraphicsView (parent) {
    graphicsScene = new QGraphicsScene(this);

    total = customDeviceList.size(); // 子部件的总数

    if (total > 0) { // 如果存在子部件
        graphicsRectItem = graphicsScene->addRect(0, 0, width(), height());
        graphicsRectItem->setFlags(QGraphicsItem::ItemIsMovable); // 让矩形图元可以被拖动
        graphicsWidgetList = customDeviceList;
        for (count = 0; count < total; count++) {
            graphicsWidgetList[count]->setParentItem(graphicsRectItem);
        }

        setAlignment(Qt::AlignTop | Qt::AlignLeft); // 设置图形视图的左上角为开始位置
        verticalScrollBar()->setStyleSheet("width: 1; height: 1;");   // 设置垂直滚动条宽高为1防止下方图像残留
        horizontalScrollBar()->setStyleSheet("width: 1; height: 1;"); // 设置水平滚动条宽高为1防止右侧图像残留

        setScene(graphicsScene);

        marginY = 10;
        scaleValue = 1;
        scaleStep = 0.01;
        // resize(width(), height());
    }
}
FloatLayout::~FloatLayout() {}
/* 部件的大小变化事件 */
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
            int deltaY = wheelEvent->angleDelta().y();
            // 获取当前鼠标相对于view的位置;
            QPointF cursorPoint = wheelEvent->pos();
            // 获取当前鼠标相对于scene的位置;
            QPointF scenePos = this->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));

            // 获取view的宽高;
            qreal viewWidth = this->viewport()->width();
            qreal viewHeight = this->viewport()->height();

            // 获取当前鼠标位置相当于view大小的横纵比例;
            qreal hScale = cursorPoint.x() / viewWidth;
            qreal vScale = cursorPoint.y() / viewHeight;
            if (deltaY < 0) {
                scale(1.0 / 1.2, 1.0 / 1.2); // 缩小图形视图
            } else if (deltaY > 0) {
                scale(1.2, 1.2); // 放大图形视图
            }
            // 将scene坐标转换为放大缩小后的坐标;
            QPointF viewPoint = this->matrix().map(scenePos);
            horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
            verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));
        }
    }
    return true;
}

/* 计算部件宽高行列以及设备部件x轴的外边距 */
void FloatLayout::widgetCalculate() {
    qreal width = this->width();  // 滚动区域的宽度
    count = 0;
    customDeviceWidth = graphicsWidgetList[count]->geometry().width() * scaleValue;   // 子部件的宽度
    customDeviceHeight = graphicsWidgetList[count]->geometry().height() * scaleValue; // 子部件的高度

    column = (int(width) % int(customDeviceWidth)) > 0
            ? (int(width / customDeviceWidth) - 1) > 0
              ? int(width / customDeviceWidth) - 1
              : 1
              : int(width / customDeviceWidth); // 通过滚动区域的宽度除于(自定义设备部件的宽度和水平外边距相加的和)得到每行的列数
    row = total % column > 0
            ? (total / column) + 1
            : (total / column); // 通过子部件总数和列数取模,有剩余时行数增1,否则为实际行数
    marginX = (width - (column * customDeviceWidth)) / (column + 1);
}
/* 宽度变化时调整部件位置 */
void FloatLayout::widthChanged() {
    qreal width = this->width();  // 滚动区域的宽度
    qreal height = this->height();
    widgetCalculate();
    for (int rowSequence = 0; rowSequence < row; rowSequence++) {
        for (int columnSequence = 0; columnSequence < column; columnSequence++, count++) {
            if (count >= total) { // 如部件计数值超过部件总数表示子部件已全部设置好位置区域
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
                                + customDeviceHeight * (rowSequence + 1))); // 为子部件设置位置区域
            }
        }
    }
    graphicsRectItem->setRect(0, 0, width, height);
}
/* 缩小设备部件以展示全部的设备部件 */
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
/* 检查部件空余的空间来放大设备部件 */
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
}
/* 顺序添加图形代理部件 */
void FloatLayout::addWidget(QGraphicsProxyWidget * customDevice) {
    graphicsWidgetList << customDevice;
    graphicsWidgetList[total]->setParentItem(graphicsRectItem);
    total += 1;
    resize(width() + 1000, height() + 1000);
    resize(width() - 1000, height() - 1000);
}
/* 添加部件 */
void FloatLayout::addWidget(QWidget * qWidget) {
    QSizePolicy sizePolicy;
    sizePolicy.setHeightForWidth(true);
    qWidget->setSizePolicy(sizePolicy);
    qWidget->setFixedWidth(120);
    QGraphicsProxyWidget * customDevice = this->graphicsScene->addWidget(qWidget);
    graphicsWidgetList << customDevice;
    graphicsWidgetList[total]->setParentItem(graphicsRectItem);
    qDebug() << total;
    total += 1;
    resize(width() + 1000, height() + 1000);
    resize(width() - 1000, height() - 1000);
}
/* 按照行列位置添加图形代理部件 */
void FloatLayout::addWidget(QGraphicsProxyWidget * customDevice, int x, int y) {
    graphicsWidgetList.insert(x * column + y, customDevice);
    graphicsWidgetList[x * column + y]->setParentItem(graphicsRectItem);
    total += 1;
    resize(width() + 1000, height() + 1000);
    resize(width() - 1000, height() - 1000);
}
/* 按照行列位置添加部件 */
void FloatLayout::addWidget(QWidget *qWidget, int x, int y) {
    QSizePolicy sizePolicy;
    sizePolicy.setHeightForWidth(true);
    qWidget->setSizePolicy(sizePolicy);
    qWidget->setFixedWidth(120);
    QGraphicsProxyWidget * customDevice = this->graphicsScene->addWidget(qWidget);
    graphicsWidgetList.insert(x * column + y, customDevice);
    graphicsWidgetList[x * column + y]->setParentItem(graphicsRectItem);
    qDebug() << total;
    total += 1;
    resize(width() + 1000, height() + 1000);
    resize(width() - 1000, height() - 1000);
}
/* 根据顺序位置移除部件 */
void FloatLayout::removeWidget(int pos) {
    if ((pos >= 0) && (pos < total) && (total > 0)) {
        graphicsScene->removeItem(graphicsWidgetList[pos]);
        graphicsWidgetList.removeAt(pos);
        qDebug() << total;
        total -= 1;
        resize(width() + 1000, height() + 1000);
        resize(width() - 1000, height() - 1000);
    }
}
/* 根据行列位置移除部件 */
void FloatLayout::removeWidget(int x, int y) {
    int pos = x * column + y;
    if ((pos >= 0) && (pos < total) && (total > 0)) {
        graphicsScene->removeItem(graphicsWidgetList[pos]);
        graphicsWidgetList.removeAt(pos);
        qDebug() << total;
        total -= 1;
        resize(width() + 1000, height() + 1000);
        resize(width() - 1000, height() - 1000);
    }
}
