# 通信协议 - 数据帧

数据帧是通信中的最小数据单元，它定义了发送一段数据的格式，包括数据的起始和结束标志、数据本身，下面我们来看一个例子：

> 再次重申，单片机仅能处理二进制数据，因此数据帧中的任何标志和数据都必须是二进制的。

<br />

- A设备: 我希望发送数据 `0101 1010` 给B，我们两个都认为 `0000` 标志数据的开始，而 `1111` 表示数据的结尾。所以我会向B发送 `0000 0101 1010 1111`
- B设备: 我收到了一个报文 `0000 0101 1010 1111`，我知道`0000`是开始， `1111`是结束，这下我就拿到了数据 `0101 1010`了

在这个例子中，`0000 0101 1010 1111` 就是一个数据帧，其中 `0000` 是起始标志，`1111` 是结束标志，`0101 1010` 是数据。

在真正的协议中，数据帧可能会包含更多的内容，比如校验位、地址位等，但是基本的结构都如上所述。