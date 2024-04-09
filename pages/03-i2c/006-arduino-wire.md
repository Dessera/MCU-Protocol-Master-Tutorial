# Arduino Wire

实现I2C的方式有硬件和软件两种，我们使用的 ESP32C3 配备有硬件的 I2C 总线支持，因此我们不需要亲自编写上文所述的时序逻辑。

在 Arduino 环境中，该总线被称为 TwoWire, 封装于`Wire.h`中。

使用该库进行 I2C 通信通常有以下几个步骤：

- 使用`Wire.begin()`初始化总线
- 使用`Wire.beginTransmission(<address>)`开始一次数据传输，`<address>`为从设备地址
- 使用`Wire.write(<data>)`发送一字节数据，`<data>`为数据内容
- 使用`Wire.endTransmission()`结束一次数据传输。

以上函数大多数都有其**重载版本**，更详细的内容请参考[Arduino Wire参考](https://www.arduino.cc/reference/en/language/functions/communication/wire/)
