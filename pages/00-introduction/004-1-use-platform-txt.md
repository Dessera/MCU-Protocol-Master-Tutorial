# 使用`platform.txt`文件

使用我们提供的`platform.txt`文件替换原有的`platform.txt`文件，然后重启Arduino IDE。

> 建议不要移除原有的`platform.txt`文件，只是将其重命名为`platform.txt.bak`，以便于在本次实验结束后恢复。

<br />

## 修改内容

我们的`platform.txt`文件主要对编译参数做了以下几个修改：

- 移除了`-std=gnu++11`，添加了`-std=gnu++2a`，以支持C++20标准
- 添加了`-fconcepts`，以支持C++20概念特性