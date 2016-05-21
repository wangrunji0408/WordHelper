## 本文件夹用于处理词库

使用命令：make NAME=cppfile 编译 cppfile.cpp，输出同名程序 cppfile

### WordParse_*.cpp

此系列程序用于解析原始词典数据

它从 worddata_zjl.txt 读取现有词库，添加新词，并覆盖写入该文件。

同时向 failedWord.txt 输出解析失败的词条。

这些程序必须按顺序调用：Senior Junior CET4 CET6，否则会有未知后果。

### DataBaseInit.cpp

用于对生成好的词库做最后处理，目前是初始化，未来也许会加入：去除重复意思等功能。

调用方法：DataBaseInit \<input_file\> \<output_file\>
