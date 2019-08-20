# QtCustomFloatLayout

I used **cpp** to build a custom floating layout class in **Qt**. 

![FloatLayout][floatLayout]

### Development Environment

* **Qt 5.12.1**
* **MinGW 7.3.0 64-bit(Windows10)**

### How does it work ?

 ```c++
	#include "customdevice.h" // 自定义设备部件
	#include "floatlayout.h"  // 自定义浮动布局
 ```

#### Create a custom device widget

```c++
	CustomDevice * customDevice = new CustomDevice(); // 默认只是一个按钮
	CustomDevice * customDevice_1 = new CustomDevice("SmartLogger2000", ":/images/icon.jpg", "正常"); // 第一个参数设备名称，第二个参数是图标图片地址，第三个参数是设备状态 
```

#### Create a floating layout widget

```c++
	QList<CustomDevice *> customDeviceList;
	customDeviceList << new CustomDevice();
    FloatLayout * floatLayout = new FloatLayout(customDeviceList, this);
```

#### Set the number of child widget in a floating layout widget

```c++
	floatLayout->setTotalValue(18); // 设置浮动布局中的子部件数量为18
```

#### Set/Update custom device content

```c++
	customDeviceList[9]->setCustomDeviceContent("0001", ":/images/icon.jpg", "离线"); // 设置/修改第10个自定义设备部件的内容
```



[floatLayout]: markdownResource/floatLayout.gif