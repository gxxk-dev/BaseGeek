<h1 align="center" style="font-size: 3.27em;line-height:0.4;"><b>BaseGeek</b></h1>
<h3 align="center">一款运行在 handPy(掌控板) 上的 面向开发者 的高级工具箱</h3>
<p align='center'>
<a href="https://www.gnu.org/licenses/agpl.txt"><img src="https://img.shields.io/badge/License-AGPL%20v3+-red.svg" alt="开源协议: AGPL3(or later)"></a>
<img alt="项目所在平台:掌控板(基于esp32)" src="https://img.shields.io/badge/Platform-handPy(based%20on%20esp32)-gold">
</p>
<hr class="solid">


传送门 ：[**快速入手**](#快速入手) | [**版权事项**](#版权事项) | [**FAQ(常见问题)**](#FAQ)

# 快速入手

1. 准备基础环境
    > 准备一个可编译hPy[^hPy]官方固件[^官方固件仓库]的环境即可
    > 别忘记`source esp-idf/export.sh`!
2. 进入目录`port` 执行`make`命令
3. 等待编译完成 此时您所需要的固件便位于`port/build/mpython/firmware.bin`

# 版权事项

本项目以 **AGPL v3(or later)** 作为开源协议

您应在源码根目录的`LICENSE.GPL3`中获取到 **AGPL v3(or later)** 源文件的副本，如没有，请访问<https://www.gnu.org/licenses/gpl-3.0.txt>

## 使用到的开源项目

1. hPy官方固件[^官方固件仓库] 包括其所有上游项目
    > 具体版权信息缺失 仅在[文档](https://mpython.readthedocs.io/zh-cn/master/license.html)中有提及 软件部分 应在`GPL v3`下使用
2. [Teno](https://gitee.com/KAIKenny/pola-os/tree/develop/Teno) Copyright (c) 2024, [Kenny](https://gitee.com/KAIKenny)
    > Teno 项目使用`BSD 3-Clause License` 在遵循协议的情况下使用有关 电量计算/获取等 的部分.
3. Devlib Copyright (c) 2024, emofalling
    > Devlib 项目使用`LGPL v3+` 在遵循协议的情况下将其作为模块嵌入BEGK
# FAQ

### 1. 我的适配官方固件[^官方固件仓库]的代码能否在BEGK[^BEGK]内运行？

#### 不能。您可能需要针对BEGK的一部分特性/API进行适配

原因：
> BaseGeek针对hPy[^hPy]官方固件做了极大变动
> 砍掉了用于与大部分hPy[^hPy]独有硬件的具象化API，转而另辟新路，使用更为高性能/简易的解决方法
> 
> 您可能需要针对BEGK的一部分特性进行适配

> 题外话：感谢emofalling为BEGK带来的DevLib，重写了大量`/port/boards/mpython/modules/mpython.py`内的低质代码

[^hPy]: 此处指掌控板(handPy)
[^官方固件仓库]: 此处指`github.com/labplus-cn/mpython`
[^BEGK]: 即本项目，BaseGeek(BEGK)
[^labp]: 即LabPlus，盛思。是掌控板硬/软件的主要开发者/贡献者