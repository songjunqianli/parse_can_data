# CAN数据读取功能使用
创建一个`enable_CAN.sh`以实现系统启动时自动配置
```bash
touch /enable_CAN.sh
chmod 777 /enable_CAN.sh
```
将orin板子上CAN口开启，`enable_CAN.sh`：
```bash
#!/bin/bash
#设置 can0 为 canfd 模式，波特率 500Kbps，数据段波特率 2Mbps
sudo ip link set can0 type can bitrate 500000 dbitrate 2000000 fd on
#打开CAN0
sudo ip link set up can0

#设置 can1 为 canfd 模式，波特率 500Kbps，数据段波特率 2Mbps
sudo ip link set can1 type can bitrate 500000 dbitrate 2000000 fd on
#打开CAN1
sudo ip link set up can1

exit 0
```
创建自启动文件`/etc/rc.local`：
```bash
printf '%s\n' '#!/bin/bash' 'exit 0' | sudo tee -a /etc/rc.local
sudo chmod +x /etc/rc.local
```
在`/etc/rc.local`中添加：
`sh /enable_CAN.sh &`

## usage:
``` bash
mkdir build
cd build
camke ..
make -j8

#比如测试radar数据读取
./testParseSpecialSignal can1 /home/songj/work/数据采集/data_collection_v2/CanDataCollection/dbc/06.3_ARS410OD_ObjectCAN_v191016_CANFD版_私can.dbc

```

## 代码的主要功能函数在`can_data.cc`中。


## test文件夹中：
`test_can_port.cc`主要测试读取can口数据是否正常；

`test_load_dbc.cc`主要测试读取DBC文件是否正常；

`testParseSpecialSignal.cc.cc`主要离线测试解析报文是否正常；

`test_parse_candata_online.cc.cc`主要在线测试解析报文是否正常。
