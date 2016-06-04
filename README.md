# WordHelper
## 面向对象程序设计基础(2016) 大作业

A useful tool helps you remember words better.

Developed by 赵嘉霖 彭炳辉 王润基.

### 编译方法

打开终端至本程序根目录，进入`source/`，使用`make`编译。

make会将所有文件生成在`runtime/$(OS_NAME)/`文件夹中。

其中`OS_NAME`=`Windows`/`Linux`/`Darwin`(Mac)，取决于所在系统。

**Windows用户注意：**

由于Windows文件编码原因，需要手动将词典文件转码：

将词典文件`dictionary.txt`用记事本打开，原地另存为，将编码方式修改为`ANSI`。

### 运行方法

#### Windows

打开终端，进入`runtime/Windows/`，输入`main.exe`运行。

#### Linux

打开终端，进入`runtime/Linux/`，输入`./run_on_linux`运行。

#### Mac

打开终端，进入`runtime/Darwin/`，输入`./main`运行。

### 更多信息

更多信息请参考`docs/`下的：

* 说明文档：`design.md`
* 设计文档：`instruction.pdf`
* 展示PPT：`presentation.key`
