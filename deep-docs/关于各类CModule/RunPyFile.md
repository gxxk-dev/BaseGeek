# 基本信息

位于`/port/boards/mpython/run_pyfile.c`

是内嵌到固件的C模块

> 其实就是`/port/lib/utils/oled.c`的套壳

# 可调用对象

|名|参数|返回值|作用|
|-|-|-|-|
|RunPyFile|str(文件名)|/|运行指定文件|
|RunFrozenModule|str(模块名)|/|运行指定的写死在固件(被冷冻的)的模块|
|EnterREPL|/|/|进入单次REPL|

> 这玩意具有巨大的特性（例如共享命名空间 `__name__`==`__main__`等）
> 功能强大，非常好用