# 起始条件与终止条件

在空闲状态下，`SDA`与`SCL`均处于高电平（挂起）状态。

- `SCL`高电平时，拉低`SDA`即通知所有设备一次通信开始。
- `SCL`高电平时，释放（拉高）`SDA`即通知所有设备一次通信结束。

![I2C 起始和终止条件](/03/000-i2c-start-end.jpg)