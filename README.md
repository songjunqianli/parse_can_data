# CAN数据读取功能使用

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
