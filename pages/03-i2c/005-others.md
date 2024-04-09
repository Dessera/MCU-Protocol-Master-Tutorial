# 其他机制

除上述时序之外，I2C还有一些特殊的机制，这里只做了解：

- I2C支持在一次数据传输结束时发送一个特殊的“重启信号（Sr）”以继续进行下一次数据传输
- I2C支持多主机，但同一时刻只能有一个主机使用总线
- I2C可以通过“时钟拉伸”来暂时停止数据传输