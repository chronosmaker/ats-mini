#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <screens.h>
#include <vars.h>
#include <actions.h>
#include "Store.h"
#include "Storage.h"
#include "SI4735-fixed.h"
#include "Button.h"
#include "ExtensionIOXL9555.hpp"

#define RECEIVER_NAME "ESP32-SI4732 Receiver"
#define FIRMWARE_NAME "ATS-Mini"
#define FIRMWARE_URL "https://github.com/esp32-si4732/ats-mini"
#define MANUAL_URL "https://esp32-si4732.github.io/ats-mini/manual.html"
#define AUTHORS_LINE1 "Authors: PU2CLR (Ricardo Caratti),"
#define AUTHORS_LINE2 "Volos Projects, Ralph Xavier, Sunnygold,"
#define AUTHORS_LINE3 "Goshante, G8PTN (Dave), R9UCL (Max Arnold),"
#define AUTHORS_LINE4 "Marat Fayzullin"
#define APP_VERSION 227   // FIRMWARE VERSION
#define EEPROM_VERSION 71 // EEPROM VERSION (forces reset)

// Number of memory slots
#define MEMORY_COUNT 30

// Modes
#define FM 0
#define LSB 1
#define USB 2
#define AM 3

// Band Types
#define FM_BAND_TYPE 0
#define MW_BAND_TYPE 1
#define SW_BAND_TYPE 2
#define LW_BAND_TYPE 3

// RDS Modes
#define RDS_PS 0b00000001   // Station name
#define RDS_CT 0b00000010   // Time
#define RDS_PI 0b00000100   // PI code
#define RDS_RT 0b00001000   // Radio text
#define RDS_PT 0b00010000   // Program type
#define RDS_RBDS 0b00100000 // Use US PTYs

// Sleep modes
#define SLEEP_LOCKED 0   // Lock the encoder
#define SLEEP_UNLOCKED 1 // Do not lock the encoder
#define SLEEP_LIGHT 2    // ESP32 light sleep

// SI4732/5 PINs
#define ESP32_I2C_SDA 17 // GPIO17   SI4732/5 Data
#define ESP32_I2C_SCL 18 // GPIO18   SI4732/5 Clock
#define AUDIO_MUTE 13    // GPIO13   Hardware L/R mute, controlled via SI4735 code (1 = Mute)
#define RESET_PIN 16     // GPIO16   SI4732/5 Reset

#define PIN_PCM5102A_DIN 11
#define PIN_PCM5102A_BCLK 10
#define PIN_PCM5102A_LRCLK 12

// Display PINs
// All other pins are defined by the TFT_eSPI library
#define PIN_LCD_BL 38 // GPIO38   LCD backlight (PWM brightness control)

// Rotary Enconder PINs
#define ENCODER1_PIN_A 21 // GPIO21
#define ENCODER1_PIN_B 14 // GPIO14
#define ENCODER2_PIN_A 1  // GPIO01
#define ENCODER2_PIN_B 2  // GPIO02

// Battery Monitor PIN
#define VBAT_MON  4       // GPIO04

// 扩展IO配置参数
#define TCA9555_ADDR 0x20 // 默认I2C地址 (A0-A2接地)
#define IOINT_PIN 15      // 中断引脚连接 GPIO15
// 引脚定义
#define PIN_RADIO_EN 8 // External LDO regulator enable (1 = Enable)
#define PIN_PCM5102_EN 9
#define PIN_MAX97220_EN 12
#define PIN_NS4160_EN 13 // Hardware Audio Amplifer enable (1 = Enable)
#define PIN_BT_CON 14
#define PCF85063_INT 15
#define ENCODER1_PUSH_BUTTON 10
#define ENCODER2_PUSH_BUTTON 11

// BFO and Calibration limits (MAX_BFO + MAX_CAL <= 16000)
#define MAX_BFO 14000 // Maximum range for currentBFO = +/- MAX_BFO
#define MAX_CAL 2000  // Maximum range for currentCAL = +/- MAX_CAL

// Network connection modes
#define NET_OFF 0        // Do not connect to the network
#define NET_AP_ONLY 1    // Create access point, do not connect to network
#define NET_AP_CONNECT 2 // Create access point, connect to a network normally, if possible
#define NET_CONNECT 3    // Connect to a network normally, if possible
#define NET_SYNC 4       // Connect to sync time, then disconnect

// Compute number of items in an array
#define ITEM_COUNT(array) (sizeof(array) / sizeof((array)[0]))
#define LAST_ITEM(array) (ITEM_COUNT(array) - 1)

inline int min(int x, int y) {
  return (x < y ? x : y);
}

inline int wrap_range(int v, int dir, int vMin, int vMax) {
  v += dir;
  v = v > vMax ? vMin + (v - vMax - 1) : v < vMin ? vMax - (vMin - v - 1) : v;
  return (v);
}

inline int clamp_range(int v, int dir, int vMin, int vMax) {
  v += dir;
  v = v > vMax ? vMax : v < vMin ? vMin : v;
  return (v);
}

inline bool isSSB() {
  return (get_var_local_mode_index() > FM && get_var_local_mode_index() < AM);
}

//
// Data Types
//
typedef struct {
  int localRadioEnable;
  int netRadioEnable;
  int epAmpEnable;
  int spAmpEnable;
  int btCon;
  int timeInt;
  int pb1;
  int pb2;
} IOStatus;

typedef struct {
  uint16_t freq;    // Frequency
  const char* name; // Frequency name
} NamedFreq;

//
// Global Variables
//
extern ExtensionIOXL9555 io;
extern IOStatus ioStatus;

extern ButtonTracker pb1;
extern ButtonTracker pb2;

extern ButtonTracker::State pb1st;
extern ButtonTracker::State pb2st;

extern volatile int encoderCount1;
extern volatile int encoderCount2;

extern SI4735_fixed rx;
extern TFT_eSprite spr;
extern TFT_eSPI tft;

extern uint16_t currentSleep;
extern uint8_t sleepModeIdx;
extern int8_t scrollDirection;

extern int8_t FmAgcIdx;
extern int8_t AmAgcIdx;
extern int8_t SsbAgcIdx;
extern int8_t AmAvcIdx;
extern int8_t SsbAvcIdx;
extern int8_t AmSoftMuteIdx;
extern int8_t SsbSoftMuteIdx;
extern uint8_t rdsModeIdx;
extern uint8_t wifiModeIdx;
extern uint8_t FmRegionIdx;

extern int8_t agcIdx;
extern int8_t agcNdx;
extern int8_t softMuteMaxAttIdx;
extern uint8_t disableAgc;

void updateIOStatus();
void useBand(const Band* band);
bool updateBFO(int newBFO, bool wrap = true);
bool doSeek(int8_t dir);
uint8_t doAbout(int dir);

// Battery.c
float batteryMonitor();
bool drawBattery(int x, int y);

// Scan.c
void scanRun(uint16_t centerFreq, uint16_t step);
float scanGetRSSI(uint16_t freq);
float scanGetSNR(uint16_t freq);

// Station.c
const char* getStationName();
const char* getRadioText();
const char* getProgramInfo();
const char* getRdsTime();
uint16_t getRdsPiCode();
bool checkRds();
bool identifyFrequency(uint16_t freq, bool periodic = false);

// Network.cpp
int8_t getWiFiStatus();
char* getWiFiIPAddress();
void netClearPreferences();
void netInit(uint8_t netMode, bool showStatus = true);
void netStop();
bool ntpIsAvailable();
bool ntpSyncTime();

void netRequestConnect();
void netTickTime();

#endif // COMMON_H
