# 使用`platform.txt`文件

首先，找到Arduino IDE的工具链目录，该目录通常位于以下位置：

```shell
C:\Users\<你的用户名>\AppData\Local\Arduino15\packages\esp32\hardware\esp32\<版本号>

```

在该目录下，你会看到一个名为`platform.txt`的文件，这个文件是Arduino IDE的工具链适配文件，用于配置编译和链接的参数。

使用我们提供的`platform.txt`文件替换原有的`platform.txt`文件，然后重启Arduino IDE。

> 建议不要移除原有的`platform.txt`文件，只是将其重命名为`platform.txt.bak`）

<br />

### 修改内容

我们的`platform.txt`文件主要做了以下几个修改：

- 移除了`-std=gnu++11`，添加了`-std=gnu++2a`，以支持C++20标准
- 添加了`-fconcepts`，以支持C++20概念特性