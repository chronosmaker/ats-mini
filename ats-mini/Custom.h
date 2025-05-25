#ifndef CUSTOM_H
#define CUSTOM_H

#include "ExtensionIOXL9555.hpp"

#define AUDIO_MUTE 13     // GPIO13   Hardware L/R mute, controlled via SI4735 code (1 = Mute)
#define RESET_PIN 16      // GPIO16   SI4732/5 Reset
#define ESP32_I2C_SDA 17  // GPIO17   SI4732/5 Data
#define ESP32_I2C_SCL 18  // GPIO18   SI4732/5 Clock

#define PIN_PCM5102A_DIN 11
#define PIN_PCM5102A_BCLK 10
#define PIN_PCM5102A_LRCLK 12

// IO配置参数
#define TCA9555_ADDR 0x20  // 默认I2C地址（A0-A2接地）
#define IOINT_PIN 15       // 中断引脚连接GPIO15
// 引脚定义（0-15对应芯片的16个IO）
#define PIN_RADIO_EN 8  // External LDO regulator enable (1 = Enable)
#define PIN_PCM5102_EN 9
#define PIN_MAX97220_EN 12
#define PIN_NS4160_EN 13  // Hardware Audio Amplifer enable (1 = Enable)
#define PIN_BT_CON 14
#define PCF85063_INT 15
#define ENCODER1_PUSH_BUTTON 10
#define ENCODER2_PUSH_BUTTON 11

// Rotary Enconder PINs
#define ENCODER1_PIN_A 21  // GPIO21
#define ENCODER1_PIN_B 14  // GPIO14
#define ENCODER2_PIN_A 1   // GPIO01
#define ENCODER2_PIN_B 2   // GPIO02

extern ExtensionIOXL9555 io;

#endif  // CUSTOM_H
