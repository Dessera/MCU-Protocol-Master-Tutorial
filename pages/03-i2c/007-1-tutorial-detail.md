# 最终实验 - 详细信息

```cpp
// 向OLED发送一段指令
size_t _command_impl(uint8_t* data, size_t size);
// 向OLED发送一段数据（显示内容）
size_t _data_impl(uint8_t* data, size_t size);
```

这两个需要实现的函数具有相同格式，接受一个`uint8_t`类型的数组`data`，其长度为`size`。

> `size_t`类型是一个整数类型，指代语言中可能会出现的长度变量

在实验中不需要进行`begin()`和`end()`操作，初始化方法已被提前调用。

大体来说，我们要遵守以下流程：

1. 调用`Wire.beginTransmission(0x3C)`启动一次数据传输
2. 根据要传输的内容，依照上文提到的OLED数据格式，用`Wire.write`发送数据
3. 使用`Wire.endTransmission`结束一次传输
