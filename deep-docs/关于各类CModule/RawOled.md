# 基本信息

位于 `/port/boards/mpython/raw_oled.c`

是内嵌至固件的C模块

> 其实就是`/port/drivers/startup/oled.c`的套壳（

# 可调用对象

|名|参数|返回值|作用|
|-|-|-|-|
|Init|int(工作频率)|bool(是否连接成功)|初始化 连接屏幕|
|Deinit|/|/|断开与OLED屏的连接|
|SetPixel|int(x,y(像素点坐标),color(像素点颜色 1白0黑))|/|设置指定像素的位置|
|DispChar|str(char(显示字符)),int(x,y(绘制起始坐标))|/|绘制指定字符(ASCII32-127 8x8)|
|Clear|/|/|清屏|
|Invert|int(模式 遵循LabP使用的逻辑)|/|翻转像素点|
|Show|/|/|显示当前缓冲区内容|
|PowerOff|/|/|关闭OLED屏|
|PowerOn|/|/|打开OLED屏|
|Contrast|int(亮度)|/|设置亮度|