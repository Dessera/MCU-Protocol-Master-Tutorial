# 实验 - 使用`Serial`调试程序

我们使用的ESP32C3的开发API中已经帮助我们设置好了基本的参数，我们现在就来简单的调用API来看看效果。

在 Arduino + ESP32C3 下，调用串口遵循以下步骤：

- 使用 Type-C 接线将电脑与单片机连接
- 调用`Serial.begin(<baud>)`初始化串口，`<baud>`要替换成约定的波特率，一般是`115200`或`9600`
- 使用`Serial.println(<content>)`来输出内容，`<content>`为要输出的内容

<br />

> TIPS:
>
> 学会查询手册是一个嵌入式学习的基本的素养，当我们不知道如何向串口输出东西的时候，我们可以查询官方网站提供的网站，比如说：
>
> [Arduino串口接口参考](https://www.arduino.cc/reference/en/language/functions/communication/serial)
