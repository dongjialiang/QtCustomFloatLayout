#include "floatlayout.h"

FloatLayout::FloatLayout(QWidget * parent) :
    QScrollArea (parent) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    devicePage = new QWidget(this);
    setWidget(devicePage); // 设置(摆放自定义设备控件)的控件
    marginX = 10;
    marginY = 10;
}
FloatLayout::~FloatLayout() {}
/* 滚动区域的大小变化事件 */
void FloatLayout::resizeEvent(QResizeEvent * size) {
    QWidget::resizeEvent(size);
    childCustomDevice = devicePage->findChildren<CustomDevice *>(); // 自定义的设备子控件
    total = childCustomDevice.size(); // 子控件的总数
    if (total != 0) { // 如果存在子控件
        int width = this->width();  // 滚动区域的宽度
        int count = 0; // 控件计数值
        int customDeviceWidth = childCustomDevice.at(count)->width(); // 子控件的宽度
        int customDeviceHeight = childCustomDevice.at(count)->height(); // 子控件的高度

        column = width / (customDeviceWidth + marginX * 2); // 通过滚动区域的宽度除于(自定义设备控件的宽度和水平外边距相加的和)得到每行的列数
        row = total % column > 0
                ? (total / column) + 1
                : (total / column); // 通过子控件总数和列数取模,有剩余时行数增1,否则为实际行数
        for (int rowSequence = 0; rowSequence < row; rowSequence++) {
            for (int columnSequence = 0; columnSequence < column; columnSequence++, count++) {
                if (count >= total) { // 如控件计数值超过控件总数表示子控件已全部设置好位置区域
                    break;
                } else {
                    childCustomDevice.at(count)->setGeometry(
                                (marginX * (columnSequence + 1)) + customDeviceWidth * columnSequence,
                                (marginY * (rowSequence + 1)) + customDeviceHeight * rowSequence,
                                customDeviceWidth * (columnSequence + 1),
                                customDeviceHeight * (rowSequence + 1)); // 为子控件设置位置区域
                }
            }
        }
        devicePage->setGeometry(0, 0, column * (customDeviceWidth + marginX), row * (customDeviceHeight + marginY) + marginY); // 设备页面的位置宽高
        verticalScrollBar()->setSliderPosition(verticalScrollBar()->value() - 3); // 使滚动条向上移动(当滚动区域的宽度变大时,最下面的子控件的下部会被遮盖,向上移动滚动条后高度就恢复正常了)
        setMinimumSize(customDeviceWidth + marginX * 2, customDeviceHeight + marginY * 2); // 设置滚动区域的最小宽高使滚动条出现
    }
}
