rubyiot_device
====
  
このソフトウェアはIoTのdevice部をCとmrubyで実装したものです。  
主な機能は以下の通りです。  
  
* 1秒ごとにsensor(温度センサ)より温度(室温)を取得し、gatewayへ送信します
* 指定された温度(室温)の上下限値と比較し、取得した気温が異常温度(高温/低温)であるかどうかを監視します
* gatewayからの指示により機器(ファン)のON/OFFを行うよう、controllerを制御します

## 動作環境
  
Ruby 2.0.0  
mruby 安定版 1.1.0

## 使用するmrbgems

以下のmrbgemsが必要です。

    conf.gem :core => "mruby-sprintf"
    conf.gem :core => "mruby-numeric-ext"
    conf.gem :git => "https://github.com/ossforumjp-app-IoT/mruby-fm3gpio.git"
    conf.gem :git => "https://github.com/ossforumjp-app-IoT/mruby-fm3uart.git"
    conf.gem :git => "https://github.com/ossforumjp-app-IoT/mruby-fm3i2cmaster.git"
  
## ライセンス

個々のファイルについて、個別にライセンス・著作権表記があるものはそのライセンスに従います。  
ライセンス表記がないものに関しては以下のライセンスを適用します。  
  
Copyright 2015 Japan OSS Promotion Forum  
  
Licensed under the Apache License, Version 2.0 (the "License");  
you may not use this file except in compliance with the License.  
You may obtain a copy of the License at  
  
http://www.apache.org/licenses/LICENSE-2.0  
  
Unless required by applicable law or agreed to in writing, software  
distributed under the License is distributed on an "AS IS" BASIS,  
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
See the License for the specific language governing permissions and  
limitations under the License.