# Macro Compute Unit Protocal Master Tutorial Update

## 前言

​	通信是嵌入式的重要组成部分，本次培训的目的是为了从单片机的基础的通讯流程出发，介绍通信的定义，本质，进而延伸出个不同类型的常见通信协议——串口通信和I2C总线通信。

​	我们力求学生尽可能从根本上理解通信概念和通信流程图，对于具体的实现细节，我们将酌情降低难度，以便学生能够在短时间内掌握基本的通信协议。

经过商讨，本节课程内容如下：

- 🌈 基本通信流程
  - 简单的通信定义，本质，以及为什么会需要存在通信协议
  - 数据帧
  - 串行和并行
  - 同步和异步
  - 单工、半双工和全双工
- ⌚ 经典异步通信——串口通信
- 🕰 经典同步通信——I2C通信

### 教学人员

- 常智德
- 陈冠豪

### 设备需求

- 串口 IO
- SSD1306 或其他显示屏设备

### 教学人员

- 常智德
- 陈冠豪

### 设备需求

- 串口 IO
- SSD1306 或其他显示屏设备

## 教学内容

### 零. 通信本身

​	通信是单片机中较为有趣的领域，我们广义的来说，通信指代的是单片机如何向自身或者是外界表达自己的状态。说白的就是信息互通。人跟人间的信息互通、机器跟人间的信息互通、机器跟机器间的信息互通，这些都是信息传递的过程。

​		比如说，我向你打了招呼："Hello!"，你回应了我，"Hey!"，这就是一次通信。官方的说：我们交换了一次Helo报文；又或者是我跟电脑的控制台（现在就像试试？<kbd>Win</kbd> + <kbd>R</kbd>键调出来CMD控制台，你输入`Ping baidu.com`）之间输入指令，他会给我反馈`(feedback)`；或者在你这条指令发出去之后，控制台会告诉你这台主机跟百度的服务器之间的连接如何，这中间又传递了计算机与计算机之间的报文（交流）——换而言之，计算机作为一台电子设备也在跟其他的电子设备做信息的传递与交换

​	但是我们这里要学习的更加底层，我们要扒开这些宏观的，被现实所具象的通信，探究本质。我们将会看到：我们需要学习的通信：也就是单片机的通信。其实是极端朴素的：他就是在发送，接受一大堆的，存在一个序列的0和1（我们叫他们比特流）

​	这就存在问题了：

> 1. **在电子世界中如何表示0和1？**：一台没有安装任何计算机视觉识别程序的机器大概率是看不懂手写的0和1的，即便看得懂，我们不可能驱动芯片的主要性能去识别这些0和1，单次的通讯中，这些0和1可能有成千上万个！
>
> 2. **信息的发送方和接收方如何解析？**：我打个比方：你说0000的意思是你好，我这里的认知里0000是我不知道，如此的通信会变得牛唇不对马嘴。
>
>    -"你好！"
>
>    -"我不知道！"
>
>    -"???"

​	上面这些我们一个一个回答：

1. 我们就是寻求了两种对立的状态来表达了0和1，在电子世界中电压大概是最好寻求的！我们电子世界里0和1的表示，目前大致有两种方式：

- 电平信号
- 差分信号

​	电平信号：简而言之，高电平就是1，低电平就是0。这是一种表达！抑或是反过来：地电平就是1，高电平就是0！

​	差分信号：我们的电压变化中，我们记上升超过阈值的时刻传递了一个1，下降超过一个阈值的时候传递了一个0！

![image-20240128093722171](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128093722171.png)

​	有兴趣的同学可以研究一下我们可以如何使用电压的值或者是变化来表达0和1

2. 这就涉及到信息解析的问题了：信号解析的操作过程而言，其实就是信号解码的过程。发送方通过对01串进行编码发送给接收方，而接收方通过之前约定的编码规则逆向解析。我们的一个发处方按照一定的频率发出了一个根据比特流转换的电磁波信号，接收方拿到了这个电磁波信号，就要对他进行解析反转回0和1的指定序列。

​	这下存在了问题，你们想一下：

> 我们知道对方向自身发送了信息，我们怎么知道哪里是信息的开头，哪里我们应该停止解析了？都是0和1！

​	这引申出来了协议这个概念：协议规定了两个发生通信的主体之间如何交流，就像是英语的语法一样，我想对一个外国人说“你好”，我说了“Hello”，对方接受到了"Hello"（接受信号），他听到我声音的传来就是要准备接受信息（一个熟悉的声波信号的冲击，这何尝不是一个信息呢？），接受到了一个Hello的声波信号（于此处开始解析特定的信息），根据英语的语义语法得到了我说的是你好的意思（根据协议解析信息）。这样我们就完成了一次理想的通讯。

​	还有大量的问题，他们很烧脑：

> 1. 单片机可不是像我们这样聪明，他只认识0和1，我们如何使用单片机的协议来发送单片机看得懂的信息呢？
> 2. 比特流的传递可以串行可以并行，什么意思？
> 3. 接收方是如何知道我们作为发送方开始通讯了？
> 4. 我们有时候会忽略：比特流也是会在一个信道上跑的：就像车辆必须在地面上的道路行驶一样！有的通道是单向的，有的通道是可以在规定时间内正向，另一个时间内反向，有的则是随时随地可以双向的行驶，他们在通信世界又叫做什么呢？

​	建立起简单的通信模型和概念，现在我们可以步入单片机通信的领域了：

### 一，更加详细的概念解释和基本通信流程

#### 1.1 数据帧

> 回答第一个问题：单片机可以理解的信息长啥样呢？

​	再重复一次：单片机只认识0和1！也就是说，在比特流层面上，我们仍然使用一系列的0和1来表达数据的开头和结尾，我们举个例子：

> A设备: 我希望发送数据 0101 1010 给B，我们两个都认为 0000 是预警数据需要开始接受和 1111 表示这就是数据的结尾。所以我会向B发送 0000 0101 1010 1111
>
> B设备: 我收到了一个报文 0000 0101 1010 1111：我知道0000是开始， 1111是结束，这下我就拿到了数据 0101 1010了

​	上面这个0000 0101 1010 1111他就是一个数据帧：即它包含了一个数据的头，尾，它本身！严肃的重复一次：数据帧是通信中最基本的单位，它是一组二进制数据，包含了数据本身和一些用于标识数据的信息。

​	这样，我们可以给出数据帧的一般表示：

> `<数据帧头> <数据> <数据帧尾>`

![image-20240128101212410](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128101212410.png)

#### 1.2 串行和并行

​	回答第二个问题的时候，我们就可以介绍串行和并行了。

​	我们下面来看看我们发出通信的本身工具的特征，第一个就是谈论的串行和并行的事情。简而言之：根据通信中使用的信号线数量，通信可以分为串行和并行两种，在单向通信中，串行通信**只使用一根信号线**（只有一束比特流），而并行通信使用多根信号线（N多条比特流同时传输）。

![串行通信和并行通信](.\Macro Compute Unit Protocal Master Tutorial Update\20210510103406177.png)

​	这里我们的绝大部分的通信协议都是串行通信，因为串行通信只需要一根信号线，可以大大降低通信线路的复杂度。

![在这里插入图片描述](.\Macro Compute Unit Protocal Master Tutorial Update\20210512112251505.png)

#### 1.3 同步和异步

> 回答第三个问题就可以引出同步和异步的概念。

​	我们总是无法回避如何控制收发方的通讯速度的问题：也就是说，我们啥时候收，啥时候发，收发的速度该有多快的问题。双方只有协调好，才能正确的处理收发的信息。

​	单片机内部有一个通信时钟，他像是通讯的心脏一样控制着我们进行通信工作的频率。**根据通信中使用的时钟信号，通信可以分为同步和异步两种**，在同步通信中，通信双方使用同一个时钟信号，以此来同步通信的速度，而异步通信则不需要时钟信号。

​	在同步通讯中，收发设备双方会使用一根信号线表示时钟信号，在时钟信号的驱动下双方进行协调，同步数据。通讯中通常双方会统一规定在时钟信号的上升沿或下降沿对数据线进行采样。

![在这里插入图片描述](.\Macro Compute Unit Protocal Master Tutorial Update\20210512112532592.png)

​	在异步通讯中，不使用时钟信号进行数据同步，它们直接在数据信号中穿插一些同步用的信号位，或者把主体数据进行打包，以数据帧的格式传输数据。例如规定由起始位、数据位、奇偶校验位、停止位等。
某些通讯中还需要双方约定数据的传输速率，以便更好地同步 。**波特率(bps)是衡量数据传送速率的指标。**
![在这里插入图片描述](.\Macro Compute Unit Protocal Master Tutorial Update\20210512112516395.png)

#### 1.4 单工、半双工和全双工

​	最后一个常见的概念就是单工、半双工和全双工，回答了我们的第四个问题。

​	根据通信是否可同时收发，通信可以分为单工、半双工和全双工三种，在单工通信中，通信双方只能单向通信，而半双工通信则可以双向通信，但不能同时收发，全双工通信则可以同时收发。

**单工方式：**
只允许数据按照一个固定的方向传送，在任何时刻都只能进行一个方向的通信，一个设备固定为发送设备，一个设备固定为接收设备。

**半双工方式：**
两个设备之间可以收发数据，但是不能在同一时刻进行，每次只能有一个设备发送，另一个站接收。

**全双工方式：**
在同一时刻，两个设备之间可以同时进行发送和接收数据。

![单工、半双工、双工](.\Macro Compute Unit Protocal Master Tutorial Update\20210510104654671.jpg)

### 二，经典异步通信——串口通信

​	本节将介绍串口通信数据帧格式，以及简单的串口使用方式。

​	串口通信是一种经典的异步通信协议，它使用`RX`接收端与`TX`发送端进行通信，**通信双方不需要时钟信号，意味着我们需要在数据帧上下更多的功夫**，我们的通信速度取决于通信双方约定的**波特率**。这是我们稍后的实验要提到的

​	我们回忆一下，作为异步通讯，他的数据格式一般是数据格式：帧头帧尾+数据+附加功能码（这里是奇偶校验）

```
uart_config_t uart_config = {
    .baud_rate = 115200,			//波特率	-- 指明需要收发的速率，好正确的时间接受正确的信息
    .data_bits = UART_DATA_8_BITS,	//数据位	--数据本身
    .parity = UART_PARITY_DISABLE,	//奇偶校验	-- 负责查看有没有数据传输的丢失的
    .stop_bits = UART_STOP_BITS_1,	//停止位	-- 表明数据位结束
    .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,	//流控
    .rx_flow_ctrl_thresh = 122,		//硬件RTS阈值
}; // BTW:这个是GNU C的初始化方式，看不懂这个初始化的方式的话等价单个的对结构体的赋值
// Configure UART parameters
ESP_ERROR_CHECK(uart_param_config(UART_NUM_2, &uart_config));
```

#### 2.1 实验

- 使用`Serial`模块调试程序

​	我们使用的ESP32C3的开发API中已经帮助我们设置好了基本的参数，我们现在就来简单的调用API来看看效果：

> TIPS:
>
> 学会查询手册是一个嵌入式学习的基本的素养，当我们不知道如何向串口输出东西的时候，我们可以查询官方网站提供的网站：比如说
>
> https://www.arduino.cc/reference/en/language/functions/communication/serial
>
> 这个地方就提供了串口相关的函数及其示例程序，下面我们的介绍依据都从这里来。

##### Serial.begin()初始化串口和Serial.Println打印函数

> 0. 首先，设定好端口：把ESP32单片机通过TypeC的线插到你电脑上，这个时候，前往工具 - 端口这个地方，选中这个多出来的COM口：否则的话会抛出端口不存在的错误导致无法烧录程序。
>
> ![image-20240128120813555](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128120813555.png)

>  I: 熟悉串口最简单的初始化（设置Buad率）和println函数的使用
>
> 使用串口，首先的基本步骤就是配置波特率和相关的参数，设定好我们交流双方收发数据的速率如何
>
> ```
> void Serial.begin(); // 别问，问就是成员函数（不是）
> ```
>
> ![image-20240128115819983](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128115819983.png)
>
> ​	说的很明白了，我们就是向begin传递一个速度参数，这里的速度就是我们说的波特率。这里，我们给一个习惯的速率115200。
>
> ```
> void setup() {
>   Serial.begin(115200);
> }
> ```
>
> ​	干嘛放setup里？初始化一次就够了！不需要反复的折磨串口！
>
> ​	初始化这样就结束了（这就是层次封装调库达人带给我的自信），怎么验证？让他输出点东西！
>
> ```c++
> void loop()
> {
> 	Serial.println("Hello, ESP32C3's UART Experiments! Congratulations from the Serial(Debug)'s successful setup!'");
>     delay(1000);
> }
> ```
>
> ​	delay指代的是延迟，让他等一会再输出，不然的话会出现刷屏的情况
>
> ​	我们的程序全貌异常的简单：
>
> ```c++
> // the setup function runs once when you press reset or power the board
> String receivingBufFromConsole;
> void setup() {
>   // initialize digital pin LED_BUILTIN as an output.
>   Serial.begin(115200);
> }
> 
> // the loop function runs over and over again forever
> void loop() {
> 
>   Serial.println("Hello, ESP32C3's UART Experiments! Congratulations from the Serial(Debug)'s successful setup!'"); // Anything you wanna can be accessible
>   delay(1000);
> 
> }
> ```
>
> ​	下面我们烧录程序，结束
>
> ![image-20240128121151352](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128121151352.png)
>
> ​	到这里，我们前往工具 `->` 串口监视器，就可以看到我们的输出了。（没看到发现还是 waitiing download的话嗯一下开发板上的RST键）
>
> ![image-20240128121142269](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128121142269.png)
>
> ​	大概如此

​	为什么还要大规模的介绍这个东西呢？很简单，我们的嵌入式开发在我们的学习阶段很难得到可视化的验证，想要知道程序运行如何，一个现阶段的良好办法就是学会使用串口来Debug程序，举个例子，我们可以在每一个阶段上一个println来看看程序有没有走到这里，是不是符合我们的预期：

```c++
// the setup function runs once when you press reset or power the board
String receivingBufFromConsole;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  Serial.println("Success setup the Serial"); // Debuging Sentences
}

// the loop function runs over and over again forever
void loop() {

  Serial.println("Hello, ESP32C3's UART Experiments! Congratulations from the Serial(Debug)'s successful setup!'"); // Anything you wanna can be accessible
  delay(1000);

}
```

​	在之后私下学习其他的单片机的时候，也可以灵活运用输出函数来达到debug的方式，从而减少排查bug的难度。

##### 简单的串口回声服务器实现（Serial.writeString()）

​	"亻尔 女 子！！！"我们都玩过回声。现在，我们就是用手头的单片机，让他和我们交互起来！我们回忆上面所讲的两个基本的嵌入式开发素养：

> 1. 学会查手册（无论是硬件配置还是软件的库API接口查询）
> 2. 学会灵活的使用println来帮助我们追踪程序步骤

​	仔细想：我们如何实现一个回声服务器呢？

> 1. 单片机需要读取我们的输入：我们在哪里输入？使用哪个API告知单片机读取我们的输入？
> 2. 单片机需要存储我们的输入：在哪里指定变量？
> 3. 单片机需要根据我们的输入做相同的输出：这个简单，直接根据我们的输入给出输出即可。（上面已经讲过）
>
> 不难猜到API：
>
> ![image-20240128122214529](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128122214529.png)
>
> 可以满足我们的需求。那就用！
>
> 不过，直接用是否会很鲁莽？我们知道，如果我们的串口是不可用的，程序很可能不会直接抛出异常，即使我们通过println知道可能异常发生了，程序还是会直接跑进read函数里，最终因为串口问题导致程序的崩溃。有没有相关的检查函数帮助我们在证明串口可用的情况下使用readString函数呢？有：
>
> ```c++
> String Serial.readString();
> ```
>
> ​	这个函数将会周期性的检查单片机的接受缓冲区，有东西则会将他取出。
>
> ![image-20240128122555126](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128122555126.png)
>
> 读完API，我们很清楚的知道了：只要返回的字节数大于0，就证明了我们的串口还可以读取：用上我们的条件结构：
>
> ```c++
> if(Serial.available()) // If the statement is true, we are supposed to read bytes from the Console
> {
> 	// Do the reading staff
> }
> ```
>
> ​	现在，我们就可以保证我们的程序不会因为串口不可用的问题出现程序的崩溃了。 
>
> ​	下一步就是存储单片机接受的字符串：
>
> ```c++
> String receivingBufFromConsole; // Global variant，which is used in storing our input
> ```
>
> ​	我们把`readString()`的结果存放到这个变量里。这样，我们就可以用它来完成输出了。

```c++
String receivingBufFromConsole; // Global variant，which is used in storing our input
void setup() {
  Serial.begin(115200);
  Serial.println("Program SetUp Success");
}

// the loop function runs over and over again forever
void loop() {
  // If the Serial can be used
  if(Serial.available())
  {
      receivingBufFromConsole = Serial.readString();
      Serial.println("I received the String from Console:> ");
      Serial.println(receivingBufFromConsole);
      Serial.println("Waiting for your next String...");
  }
// 	Following codes are commented, Bonus Question: what will the program behave if we compile the "else" 
// 	part code into the program? try by yourself
    
//  else
//  {
//      Serial.println("Current Serial has nothing to read! Program shell be terminated for 1ms");
//      delay(100);
///  }
}
```

​	下面我们来看看现象，还是老样子。编译烧录，然后打开串口监视台：

​	让我们庄重的发一条信息吧！

```
hello! A Message Wanna Echo from the User Console
```

​	将这条信息发送到

![image-20240128125721449](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128125721449.png)

​	ESP32C3很愉快的回应了我们：

![image-20240128125442072](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128125442072.png)

### 三，经典同步通信——I2C通信

​	玩够了异步通信，我们下面来看看很常见的同步通信，也就是IIC通信（又叫做I2C通信，读作I方C通信）

​	I2C通信是一种经典的同步通信协议，它使用`SDA`数据线和`SCL`时钟线进行通信，通信双方需要通过`SCL`同步时钟信号。

​	先来看布线：I2C 总线是一个多主机的串行总线，由两线组成――串行数据（SDA）和串行时钟（SCL）线在连接到总线的器件间传递信息。总线上可以挂接多个器件，每个器件都有一个唯一的地址识别（无论是微控制器、LCD驱动器存储器或键盘接口），而且都可以作为一个发送器或接收器（由器件的功能决定）。

​	SDA 线上的数据必须在时钟的高电平周期保持稳定。数据线的高或低电平状态只有在 SCL 线的时钟信号是低电平时才能改变

![image-20240128130435096](.\Macro Compute Unit Protocal Master Tutorial Update\image-20240128130435096.png)

#### IIC协议的规定，主机（这里简单的理解位我们的电脑）访问从机（这里简单的理解为我们的单片机）的一般过程如下：

主机想要发送数据给一个从机:
（1）主机发送一个START条件，并向从机发送地址。
（2）主机将数据发送到从机。
（3）主机以STOP条件终止传输。
主机从从机接收/读取数据:
（1）主机发送一个START条件，并向从机发送地址 。
（2）主机将请求的寄存器读给从机。
（3）主机从从机接收数据 。
（4）主机使用STOP条件终止传输 。

这样，I2C通信的数据帧就依据协议可以给出了：
![在这里插入图片描述](.\Macro Compute Unit Protocal Master Tutorial Update\20210711173813165.png)

#### 3.1 实验（待定更加详细的方案）

- SSD1306驱动核心模块实现（实现I2C数据发送）
  - 低难度：使用硬件I2C
  - 高难度：使用软件I2C

> 也许可以的参考: [Arduino/ESP32 使用Wire库实现两路IIC驱动_esp32 wire库解释-CSDN博客](https://blog.csdn.net/qq_33685823/article/details/113796309)
