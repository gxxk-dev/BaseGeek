# `devlib` -- 掌控板内设操作库
## 按钮与触摸键
&emsp;&emsp;本库提供了对掌控板按钮和触摸键的功能操作，包括检测按钮和触摸键是否被按下，以及为按钮和触摸键添加事件等。
### 按钮
&emsp;&emsp;有两个按钮对象`button_a(button_A)`和`button_b(button_B)`，分别对应A和B按钮。这两个按钮对象由`Button`类创建，均继承`machine.Pin`。
```python
class devlib.Button(pinname)
```
&emsp;&ensp;按键类。
- `pinname`：引脚编号。
#### 来自Button类的方法
```python
Button.is_pressed() -> bool
```
&emsp;&ensp;返回按键是否被按住。`True`表示被按住，`False`表示未被按住。
```python
Button.event_pressed: Callable(pin)
```
&emsp;&ensp;按键被按下时触发的事件。此值可被修改，但应是一个具有一个输入参数的可调用对象。默认值为空函数。
- `pin`：按键对应引脚的machine.Pin对象。
```python
Button.event_released: Callable(pin)
```
&emsp;&ensp;按键被释放时触发的事件。此值可被修改，但应是一个具有一个输入参数的可调用对象。默认值为空函数。
- `pin`：按键对应引脚的machine.Pin对象。
```python
Button.schedule_event: bool
```
&emsp;&ensp;是否将按键事件（即`Button.event_pressed`和`Button.event_released`）放在`micropython.schedule`内运行。放在`micropython.schedule`内运行意味着将按键事件安排在ISR（中断处理程序）之外运行，在按键事件运行时仍能检测中断触发信号，但容易导致按钮事件的重复触发。默认值为`False`。
#### 来自`machine.Pin`类的方法
自行查找。
### 触摸键
&emsp;&emsp;有六个触摸键对象`touchpad_p(touchpad_P)`、`touchpad_y(touchpad_Y)`、`touchpad_t(touchpad_T)`、`touchpad_h(touchpad_H)`、`touchpad_o(touchpad_O)`和`touchpad_n(touchpad_N)`，分别对应触摸键P、Y、T、H、O和N。这六个触摸键对象由`Touch`类创建，均继承`machine.TouchPad`。
```python
class devlib.Touch(pin)
```
&emsp;&ensp;触摸键类。
- `pin`：需要被初始化为触摸键的引脚对象。
#### 来自Touch类的方法
```python
Touch.is_pressed() -> bool
```
&emsp;&ensp;返回触摸键是否被按住。`True`表示被按住，`False`表示未被按住。
```python
Touch.value: Literal[0,1]
```
&emsp;&ensp;触摸键是否被按住的值。`1`表示被按住，`0`表示未被按住。
```python
Touch.event_pressed: Callable(value)
```
&emsp;&ensp;触摸键被按下时触发的事件。此值可被修改，但应是一个具有一个输入参数的可调用对象。默认值为空函数。
- `value`：触摸键是否被按住的值。`1`表示被按住，`0`表示未被按住。
```python
Touch.event_released: Callable(value)
```
&emsp;&ensp;触摸键被释放时触发的事件。此值可被修改，但应是一个具有一个输入参数的可调用对象。默认值为空函数。
- `value`：触摸键是否被按住的值。`1`表示被按住，`0`表示未被按住。
```python
Touch.schedule_event: bool
```
&emsp;&ensp;是否将触摸键事件（即`Touch.event_pressed`和`Touch.event_released`）放在`micropython.schedule`内运行。放在`micropython.schedule`内运行意味着将触摸键事件安排在ISR（中断处理程序）之外运行，在触摸键事件运行时仍能检测中断触发信号，但容易导致触摸键事件的重复触发。默认值为`False`。
#### 来自`machine.TouchPad`类的方法
```python
Touch.read() -> int
```
&emsp;&ensp;读取触摸键的电平。当触摸时，是很小的数字（通常在20以内）；当没有触摸时，是较大的数字（通常大于1000）。
```python
Touch.config(value)
```
&emsp;&ensp;设置触摸键的阈值。
- `value`：整数阈值。当触摸键的电平小于阈值时，认为触摸键被按下。默认值为`500`。  

其余的自行查找。
## 屏幕（oled对象）
&emsp;&emsp;oled对象为重写过的来自mpython的`ssd1106.SSD1106_I2C`的衍生类，继承`ssd1106.SSD1106_I2C`和`FrameBuffer`的方法。相较于mpython拥有更好的性能表现和更丰富的玩法。
### 来自oled类的方法
```python
oled.DispChar(s,x,y,mode=Colormode.normal,out=Outmode.stop,*,maximum_x=128,space=1,newlinecode=True,return_x=0,return_addy=16,ellipsis="...",end="",buffer=None)
```
&emsp;&ensp;显示文本。采用 [Google Noto Sans CJK](http://www.google.cn/get/noto/help/cjk/) 开源无衬线字体字体。字体高度16像素点,支持英文,简体中文繁体中文，日文和韩文语言。
#### &emsp;&ensp;固定参数
- `s`：需要显示的文本
- `x`、`y`：文本的起始坐标（即文本的左上角坐标）
- `mode`：文本显示模式。默认为 `Colormode.normal`。有这几种模式：
    - `Colormode.normal`：正常显示。
    - `Colormode.reverse`：反色显示。
    - `Colormode.nobg`：正常显示，但是背景透明。
    - `Colormode.reverse_nobg`：反转显示，并且背景透明。
    - `Colormode.xor`：自动对每个字符切换显示模式。在字符显示前，如果字符显示的位置为黑，则使用`Colormode.normal`模式；否则使用`Colormode.reverse`模式。每个字符都按照上述逻辑自动切换显示模式。
    - `Colormode.xor_nobg`：类似于`Colormode.xor`模式，但是每个字的背景都是透明的。
    - `Colormode.noshow`：不显示字符，但仍会计数。当仅需获取统计数据而不显示文本时，这个参数十分有用。
    - `Colormode.black`：将字符替换成等宽等高的黑色色块来显示。
    - `Colormode.white`：将字符替换成等宽等高的白色色块来显示。
    - `Colormode.xor_fill`：自动把每个字符转换成特定颜色的等宽等高色块来显示。在色块显示前，如果色块显示的位置为黑，则色块为黑，否则为白。
    - `Colormode.xor_fill_reverse`：类似于`Colormode.xor_fill`模式，但是逻辑相反：如果色块显示的位置为黑，则色块为白，否则为黑。
- `out`：文本超过`x`坐标最大值 (`maximum_x`) 时（本段称作超出范围）的处理方式。默认为 `Outmode.stop`。有这几种模式：
    - `Outmode.keepon`：继续绘制文本。
    - `Outmode.stop`（推荐）：停止显示。在文本超出范围时，该模式会让文字完整的显示在范围内。相比显示效果一模一样的`Colormode.keepon`更省时
    - `Outmode.stop2`：停止显示，但更具有预见性。在文本超出范围时，该模式会让文字完全只显示在范围内
    - `Outmode.autoreturn`（推荐）：自动换行。当文本将要超出范围时，将剩余的文本安排到新的一行继续显示。这种模式更具有预见性，会使文本完全只显示在范围内。
    - `Outmode.autoreturn2`：自动换行，与`Outmode.autoreturn`类似，但没有预见性，即文本可能会超出范围。
    - `Outmode.ellipsis`（推荐）：自动省略。当文本将要超出范围时，将剩余的文本用省略号代替，能确保文本不会超出范围。
#### &emsp;&ensp;可选参数
- `maximum_x`：文本的x坐标最大值。默认为 `128`（即ssd1106屏幕宽度）。
- `space`：字符间距，默认为`1`
- `newlinecode`：是否启用换行符`\n`作为换行符。默认为`True`。如果为`False`，则换行符`\n`将被当做普通字符一样显示（通常为空）。
- `return_x`：新行文本的x坐标。当一段文本被安排到新的一行时，此参数决定了这段文本的初始`x`坐标。默认为`0`。
- `return_addy`：换行时文本增加的y坐标。当一段文本被安排到新的一行时，此参数决定了这段文本增加的`y`坐标。默认为`16`（即默认字体的高度）。
- `ellipsis`：省略值。当文本将要超出范围并且指定了`out=Colormode.ellipsis`时，剩余的文本将被此参数的值代替。默认为 `...`（三个小数点） 。
- `end`：结束符。在文本显示结束时，将会接着显示此参数给定的值。默认为空字符串（`""`）。当`out=Outmode.ellipsis`时，此参数给定的字符串不会被省略，而是会显示在省略号后面。
- `buffer`：自定义缓冲区。若指定了其值为FrameBuffer及其衍生类，则将会将文字绘制在指定的缓冲区上而不是oled。
#### &emsp;&ensp;返回值
&emsp;&emsp;返回一个由两个元组组成的元组：`((w,h),(chars,returns))`
- `w`：文本的总宽度
- `h`：文本的总高度
- `chars`：文本的可用总字符数
- `returns`：文本的换行次数（若没有换行则为`0`）
#### &emsp;&ensp;参数使用技巧
- `end`：需要显示`thisisalongnamefile.txt`，但是只希望自动省略文件名不省略后缀名时，可以指定`s="thisisalongnamefile",out=Outmode.ellipsis,end=".txt"`。最终会显示为`thisisalongnam....txt`。此时若将`thisisalongnamefile`替换成`short`，那么
最终会显示为`short.txt`。
- `return_x`：需要显示一段文字，能自动换行，但是希望这段文本只在右半边显示，那么可以指定`out=Outmode.autoreturn,return_x=64`。
- `maxinum_x`与`buffer`：需要将一段文字显示在FrameBuffer缓冲区`buf`内，但是`buf`的宽度只有`72`，那么可以指定`maximum_x=72,buffer=buf`。

&emsp;
```python
oled.DispChar_font(font,s,x,y,mode=Colormode.normal,out=Outmode.stop,*,maximum_x=128,space=1,newlinecode=True,return_x=0,return_addy=16,ellipsis="...",end="",buffer=None)
```
&emsp;&ensp;自定义字体显示。用户可根据自己需求,在将 otf 、 ttf 标准字体文件通过Python脚本 [font-to-py.py](https://github.com/peterhinch/micropython-font-to-py/blob/master/font_to_py.py) 转为输出含字体Bitmap的python源码，放入掌控板文件系统中，并使用import导入调用。
#### &emsp;&ensp;固定参数
- `font`：字体对象。通过Python脚本 [font-to-py.py](https://github.com/peterhinch/micropython-font-to-py/blob/master/font_to_py.py) 转为输出含字体Bitmap的python源码，放入掌控板文件系统中，并使用import导入调用。
- `s`：需要显示的文本
- `x`、`y`：文本的起始坐标（即文本的左上角坐标）
- `mode`：文本显示模式。默认为 `Colormode.normal`。有这几种模式：
    - `Colormode.normal`：正常显示。
    - `Colormode.reverse`：反色显示。
    - `Colormode.nobg`：正常显示，但是背景透明。
    - `Colormode.reverse_nobg`：反转显示，并且背景透明。
    - `Colormode.xor`：自动对每个字符切换显示模式。在字符显示前，如果字符显示的位置为黑，则使用`Colormode.normal`模式；否则使用`Colormode.reverse`模式。每个字符都按照上述逻辑自动切换显示模式。
    - `Colormode.xor_nobg`：类似于`Colormode.xor`模式，但是每个字的背景都是透明的。
    - `Colormode.noshow`：不显示字符，但仍会计数。当仅需获取统计数据而不显示文本时，这个参数十分有用。
    - `Colormode.black`：将字符替换成等宽等高的黑色色块来显示。
    - `Colormode.white`：将字符替换成等宽等高的白色色块来显示。
    - `Colormode.xor_fill`：自动把每个字符转换成特定颜色的等宽等高色块来显示。在色块显示前，如果色块显示的位置为黑，则色块为黑，否则为白。
    - `Colormode.xor_fill_reverse`：类似于`Colormode.xor_fill`模式，但是逻辑相反：如果色块显示的位置为黑，则色块为白，否则为黑。
- `out`：文本超过`x`坐标最大值 (`maximum_x`) 时（本段称作超出范围）的处理方式。默认为 `Outmode.stop`。有这几种模式：
    - `Outmode.keepon`：继续绘制文本。
    - `Outmode.stop`（推荐）：停止显示。在文本超出范围时，该模式会让文字完整的显示在范围内。相比显示效果一模一样的`Colormode.keepon`更省时
    - `Outmode.stop2`：停止显示，但更具有预见性。在文本超出范围时，该模式会让文字完全只显示在范围内
    - `Outmode.autoreturn`（推荐）：自动换行。当文本将要超出范围时，将剩余的文本安排到新的一行继续显示。这种模式更具有预见性，会使文本完全只显示在范围内。
    - `Outmode.autoreturn2`：自动换行，与`Outmode.autoreturn`类似，但没有预见性，即文本可能会超出范围。
    - `Outmode.ellipsis`（推荐）：自动省略。当文本将要超出范围时，将剩余的文本用省略号代替，能确保文本不会超出范围。
#### &emsp;&ensp;返回值
&emsp;&emsp;返回一个由两个元组组成的元组：`((w,h),(chars,returns))`
- `w`：文本的总宽度
- `h`：文本的总高度
- `chars`：文本的可用总字符数
- `returns`：文本的换行次数（若没有换行则为`0`）
#### &emsp;&ensp;可选参数
- `maximum_x`：文本的x坐标最大值。默认为 `128`（即ssd1106屏幕宽度）。
- `space`：字符间距，默认为`1`
- `newlinecode`：是否启用换行符`\n`作为换行符。默认为`True`。如果为`False`，则换行符`\n`将被当做普通字符一样显示（通常为空）。
- `return_x`：新行文本的x坐标。当一段文本被安排到新的一行时，此参数决定了这段文本的初始`x`坐标。默认为`0`。
- `return_addy`：换行时文本增加的y坐标。当一段文本被安排到新的一行时，此参数决定了这段文本增加的`y`坐标。默认为`16`（即默认字体的高度）。
- `ellipsis`：省略值。当文本将要超出范围并且指定了`out=Colormode.ellipsis`时，剩余的文本将被此参数的值代替。默认为 `...`（三个小数点） 。
- `end`：结束符。在文本显示结束时，将会接着显示此参数给定的值。默认为空字符串（`""`）。当`out=Outmode.ellipsis`时，此参数给定的字符串不会被省略，而是会显示在省略号后面。
- `buffer`：自定义缓冲区。若指定了其值为FrameBuffer及其衍生类，则将会将文字绘制在指定的缓冲区上而不是oled。  

&emsp;
```python
oled._reverse(buf:bytearray)
```
&emsp;&emsp;工具函数，已经过原生代码优化。将`buf`中的所有内容反转。不返回值。在需要反色时非常有用。
- `buf`：需要反转的缓冲区。
### 来自`ssd1106.SSD1106_I2C`类的方法
```python
oled.show()
```
&emsp;&ensp;刷新OLED内容（将缓冲区的内容发送至OLED显示）。
```python
oled.contrast(value)
```
&emsp;&ensp;设置OLED亮度。
- `value`：亮度值。范围为`0-255`。   
```python
oled.invert(n)
```
&emsp;&ensp;是否反转显示。反转对之后的每一次显示都有效。
- `n`：是否反转显示的值。`1`为反转，`0`为不反转。   
```
oled.poweron()
```
&emsp;&ensp;开启OLED电源。
```python
oled.poweroff()
```
&emsp;&ensp;关闭OLED电源。
```python
oled.init_display()
```
&emsp;&ensp;初始化（重新初始化）OLED显示。
### 来自`FrameBuffer`类的方法
```python
oled.fill(c)
```
&emsp;&ensp;使用指定颜色填充整个缓冲区。
- `c`：颜色值
```python
oled.pixel(x,y[,c]) -> int | None
```
&emsp;&ensp;获取或设定指定像素点的颜色值。
- `x`、`y`：像素点的坐标
- `c`：如果指定了此值，那么将指定像素的颜色设为此值并返回`None`（即无返回值）；如果未指定，则返回指定像素的颜色值。
```python
oled.hline(x,y,w,c)
```
&emsp;&ensp;从指定坐标开始绘制指定长度的水平线。
- `x`、`y`：水平线的起始坐标
- `w`：水平线的长度。将会从起始坐标的右侧（`x+`）延伸`w`个像素形成水平线。若此值为负，则不绘制。
- `c`：颜色值
```python
oled.vline(x,y,h,c)
```
&emsp;&ensp;从指定坐标开始绘制指定长度的垂直线。
- `x`、`y`：垂直线的起始坐标
- `h`：垂直线的长度。将会从起始坐标的下方（`y+`）延伸`h`个像素形成垂直线。若此值为负，则不绘制。
- `c`：颜色值
```python
oled.line(x1,y1,x2,y2,c)
```
&emsp;&ensp;在两个坐标之间绘制一条直线。
- `x1`、`y1`：直线的起始坐标
- `x2`、`y2`：直线的结束坐标
- `c`：颜色值
```python
oled.rect(x,y,w,h,c)
```
&emsp;&ensp;绘制一个空心矩形。
- `x`、`y`：矩形的起始坐标
- `w`：矩形的宽度
- `h`：矩形的高度
- `c`：颜色值
```python
oled.fill_rect(x,y,w,h,c)
```
&emsp;&ensp;绘制一个实心矩形。
- `x`、`y`：矩形的起始坐标
- `w`：矩形的宽度
- `h`：矩形的高度
- `c`：颜色值
```python
oled.circle(x,y,r,c)
```
&emsp;&ensp;绘制一个空心圆。
- `x`、`y`：圆的中心坐标
- `r`：圆的半径
- `c`：颜色值
```python
oled.fill_circle(x,y,r,c)
```
&emsp;&ensp;绘制一个实心圆。
- `x`、`y`：圆的中心坐标
- `r`：圆的半径
- `c`：颜色值
```python
oled.quarter_circle(x,y,r,code,c)
oled.drawCircleHelper(x,y,r,code,c)
```
&emsp;&ensp;按照二进制数绘制一些同心的四分之一圆。
- `x`、`y`：圆的中心坐标
- `r`：圆的半径
- `code`：二进制数，用于指定需要的四分之一圆。例如，`0b1010`将会绘制一个右上部分和左下部分的四分之一圆。具体值参照表：
  | 二进制数 | 圆的部位 |
  | :--- | :--- |
  | `0b0001(1)` | 左上部分（第一象限） |
  | `0b0010(2)` | 右上部分（第二象限） |
  | `0b0100(4)` | 右下部分（第三象限） |
  | `0b1000(8)` | 左下部分（第四象限） |
  | `0b0011(3)` | 右上部分和左上部分 |
  | `0b1001(9)` | 左下部分和左上部分 |
  | . . . . . . | . . . . . . |
  | `0b1111(15)` | 整个圆（包含四个部分） |

  注：数为普通的`int`类型值，且只取二进制后四位进行指定。
- `c`：颜色值
```python
oled.round_rect(x,y,w,h,r,c)
oled.RoundRect(x,y,w,h,r,c)
```
&emsp;&ensp;绘制一个弧角矩形。
- `x`、`y`：弧角矩形的左上角坐标
- `w`：弧角矩形的宽度
- `h`：弧角矩形的高度
- `r`：弧角半径
- `c`：颜色值
```python
oled.triangle(x0,y0,x1,y1,x2,y2,c)
```
&emsp;&ensp;绘制一个空心三角形。
- `x0`、`y0`：第一个顶点的坐标
- `x1`、`y1`：第二个顶点的坐标
- `x2`、`y2`：第三个顶点的坐标
- `c`：颜色值
```python
oled.fill_triangle(x0,y0,x1,y1,x2,y2,c)
```
&emsp;&ensp;绘制一个实心三角形。
- `x0`、`y0`：第一个顶点的坐标
- `x1`、`y1`：第二个顶点的坐标
- `x2`、`y2`：第三个顶点的坐标
- `c`：颜色值
```python
oled.bitmap(x,y,bitmap,w,h,x)
oled.Bitmap(x,y,bitmap,w,h,x)
```
&emsp;&ensp;在指定的位置显示一个图像。
- `x`、`y`：图像的左上角坐标
- `bitmap`：图像数据。类型为`bytearray`，内容格式为`framebuf.MONO_HLSB`。
- `w`：图像的宽度
- `h`：图像的高度
- `x`：无效变量。这个变量的值不影响显示效果。建议值为`1`。
```python
oled.blit(fbuf,x,y[,key])
```
&emsp;&ensp;在给定的坐标将一个`FrameBuffer`的内容覆盖在当前缓冲区上。
- `fbuf`：需要覆盖的`FrameBuffer`缓冲区。
- `x`、`y`：覆盖的左上角坐标。
- `key`：若指定了此值，那么此颜色值将会被替换为透明色（即不绘制此颜色值的像素）。
```python
oled.text(s,x,y[,c])
```
&emsp;&ensp;在给定的坐标显示内置字体的文本。文本的背景是透明的。所有字符的尺寸均为8x8像素。
- `s`：文本内容。
- `x`、`y`：文本的左上角坐标。
- `c`：文本的颜色值。若指定了此值，那么文本将会用此颜色值显示，否则使用默认颜色值（即白色）。
```python
oled.scroll(xstep,ystep)
```
&emsp;&ensp;沿指定的步长移动缓冲区上的内容。
- `xstep`：沿x轴移动的步长。若此值为正，则向右（`x+`）移动；若此值为负，则向左（`x-`）移动；若此值为0，则不移动。
- `ystep`：沿y轴移动的步长。若此值为正，则向下（`y+`）移动；若此值为负，则向上（`y-`）移动；若此值为0，则不移动。

&emsp;&ensp;可能会留下之前的颜色足迹。



## 内嵌参数
&emsp;&ensp;内嵌参数为初始化时所调用的一些特殊参数，这些参数在初始化后就会无效。若需更改，请在本库的源代码中修改。
```python
devlib.overclock: bool #line 15
```
&emsp;&ensp;是否开启I2C总线超频，默认为`True`。开启超频后，I2C总线频率将从标准频率`400KHz`提升至`1250KHz`，能够更快地与内外设进行通信，但可能会降低I2C总线的稳定性。若连接了`P19`和`P20`引脚的I2C外设在超频时无法正常工作，则应关闭超频。
```python
devlib.font_address: int #line 42
```
&emsp;&ensp;字体分区的起始地址，默认为`0x400000`。字体分区决定了`oled.DispChar`时调用的字体。
```python
devlib.maximum_fontbitmaplen: int #line 43
```
&emsp;&ensp;字体图像的最大字节大小，默认为`64`，用于`oled.DispChar`的缓冲优化。该值由统计得出。





```c
/*OLED:
__class__       _reverse        DispChar        DispChar_font*/
```
```c
FrameBuffer:
scroll          text
```
```c
/*SSD1106_I2C:
__class__       init_display    poweroff        poweron
contrast        invert          show*/
```