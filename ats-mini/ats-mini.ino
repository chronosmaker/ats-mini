// =================================
// INCLUDE FILES
// =================================

#include "Common.h"
#include <Wire.h>
#include "EEPROM.h"
#include "Rotary.h"
#include "Menu.h"
#include "Utils.h"
#include "PageMain.h"
#include "PageLocalRadio.h"
#include "PageNetRadio.h"
#include "PageAlarm.h"
#include "PageSetting.h"
#include "PageSettingWiFi.h"
#include "PageSettingBluetooth.h"
#include "PageSettingTime.h"
#include "PageSettingScreen.h"
#include "PageSettingSleep.h"
#include "PageSettingOperation.h"
#include "PageSettingAbout.h"

// SI473/5 and UI
#define ELAPSED_COMMAND 10000    // time to turn off the last command controlled by encoder. Time to goes back to the VFO control // G8PTN: Increased time and corrected comment
#define DEFAULT_VOLUME 15        // change it for your favorite sound volume
#define DEFAULT_SLEEP 0          // Default sleep interval, range = 0 (off) to 255 in steps of 5
#define RDS_CHECK_TIME 250       // Increased from 90
#define SEEK_TIMEOUT 600000      // Max seek timeout (ms)
#define NTP_CHECK_TIME 60000     // NTP time refresh period (ms)
#define SCHEDULE_CHECK_TIME 2000 // How often to identify the same frequency (ms)

// =================================
// CONSTANTS AND VARIABLES
// =================================
int8_t agcIdx = 0;
uint8_t disableAgc = 0;
int8_t agcNdx = 0;
int8_t softMuteMaxAttIdx = 4;

long elapsedButton = millis();

long lastRDSCheck = millis();
long lastNTPCheck = millis();
long lastScheduleCheck = millis();

long elapsedCommand = millis();

// AGC/ATTN index per mode (FM/AM/SSB)
int8_t FmAgcIdx = 0;  // Default FM  AGGON  : Range = 0 to 37, 0 = AGCON, 1 - 27 = ATTN 0 to 26
int8_t AmAgcIdx = 0;  // Default AM  AGCON  : Range = 0 to 37, 0 = AGCON, 1 - 37 = ATTN 0 to 36
int8_t SsbAgcIdx = 0; // Default SSB AGCON  : Range = 0 to 1,  0 = AGCON,      1 = ATTN 0

// AVC index per mode (AM/SSB)
int8_t AmAvcIdx = 48;  // Default AM  = 48 (as per AN332), range = 12 to 90 in steps of 2
int8_t SsbAvcIdx = 48; // Default SSB = 48, range = 12 to 90 in steps of 2

// SoftMute index per mode (AM/SSB)
int8_t AmSoftMuteIdx = 4;  // Default AM  = 4, range = 0 to 32
int8_t SsbSoftMuteIdx = 4; // Default SSB = 4, range = 0 to 32

uint8_t FmRegionIdx = 0; // FM Region

uint16_t currentSleep = DEFAULT_SLEEP; // Display sleep timeout, range = 0 to 255 in steps of 5
long elapsedSleep = millis();          // Display sleep timer
int8_t scrollDirection = 1;            // Menu scroll direction

//
// Current parameters
//
bool ioInterrupt = false;

volatile int encoderCount1 = 0;
volatile int encoderCount2 = 0;

//
// Devices
//
ExtensionIOXL9555 io;
IOStatus ioStatus;

Rotary encoder1 = Rotary(ENCODER1_PIN_B, ENCODER1_PIN_A);
Rotary encoder2 = Rotary(ENCODER2_PIN_B, ENCODER2_PIN_A);

ButtonTracker pb1 = ButtonTracker();
ButtonTracker pb2 = ButtonTracker();

ButtonTracker::State pb1st;
ButtonTracker::State pb2st;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[TFT_WIDTH * TFT_HEIGHT];

TFT_eSPI tft = TFT_eSPI(TFT_HEIGHT, TFT_WIDTH);
SI4735_fixed rx;

//
// Hardware initialization and setup
//

// 刷屏回调函数
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  // 通知LVGL刷新完成
  lv_disp_flush_ready(disp_drv);
}

void tft_init()
{
  tft.begin();        /* TFT init */
  tft.setRotation(3); /* Landscape orientation, flipped */

  // Detect and fix the mirrored & inverted display
  // https://github.com/esp32-si4732/ats-mini/issues/41
  if (tft.readcommand8(ST7789_RDDID, 3) == 0x93)
  {
    tft.invertDisplay(0);
    tft.writecommand(TFT_MADCTL);
    tft.writedata(TFT_MAD_MV | TFT_MAD_MX | TFT_MAD_MY | TFT_MAD_BGR);
  }

  tft.fillScreen(TFT_BLACK);
  // spr.createSprite(TFT_HEIGHT, TFT_WIDTH);
  // spr.setTextDatum(MC_DATUM);
  // spr.setSwapBytes(true);
  // spr.setFreeFont(&Orbitron_Light_24);
  // spr.setTextColor(TH.text, TH.bg);

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, sizeof(buf));

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = TFT_HEIGHT;
  disp_drv.ver_res = TFT_WIDTH;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
}

void setup()
{
  // Enable serial port
  Serial.begin(115200);

  Serial0.begin(115200);
  Serial0.println("AT+POWER_OFF");

  // Initialize flash file system
  diskInit();

  if (psramFound())
  {
    Serial.print("Free PSRAM: ");
    Serial.println(ESP.getFreePsram()); // 输出剩余PSRAM容量
  }
  else
  {
    Serial.println("PSRAM未启用, 请检查配置!");
    while (1)
      ;
  }

  // The line below may be necessary to setup I2C pins on ESP32
  Wire.begin(ESP32_I2C_SDA, ESP32_I2C_SCL);

  // 初始化扩展 IO
  if (!io.begin(Wire, TCA9555_ADDR, ESP32_I2C_SDA, ESP32_I2C_SCL))
  {
    Serial.println("TCA9555 not detected");
    while (1)
      ;
  }

  // IO 中断引脚
  pinMode(IOINT_PIN, INPUT);
  // Encoder pins. Enable internal pull-ups
  pinMode(ENCODER1_PIN_A, INPUT);
  pinMode(ENCODER1_PIN_B, INPUT);
  pinMode(ENCODER2_PIN_A, INPUT);
  pinMode(ENCODER2_PIN_B, INPUT);

  // 配置扩展 IO 方向
  io.configPort(ExtensionIOXL9555::PORT0, 0xff);
  io.pinMode(PIN_BT_CON, INPUT);
  io.pinMode(PCF85063_INT, INPUT);

  io.pinMode(ENCODER1_PUSH_BUTTON, INPUT);
  io.pinMode(ENCODER2_PUSH_BUTTON, INPUT);

  // Enable audio amplifier
  // Initally disable the audio amplifier until the SI4732 has been setup
  io.pinMode(PIN_NS4160_EN, OUTPUT);
  io.pinMode(PIN_MAX97220_EN, OUTPUT);
  io.digitalWrite(PIN_NS4160_EN, LOW);
  io.digitalWrite(PIN_MAX97220_EN, LOW);

  // Enable SI4732 VDD
  io.pinMode(PIN_RADIO_EN, OUTPUT);
  io.pinMode(PIN_PCM5102_EN, OUTPUT);
  io.digitalWrite(PIN_RADIO_EN, HIGH);
  io.digitalWrite(PIN_PCM5102_EN, LOW);

  // TFT display brightness control (PWM)
  // Note: At brightness levels below 100%, switching from the PWM may cause power spikes and/or RFI
  ledcAttach(PIN_LCD_BL, 16000, 8); // Pin assignment, 16kHz, 8-bit
  ledcWrite(PIN_LCD_BL, 0);         // Default value 0%

  // TFT display setup
  tft_init();

  // Press and hold Encoder button to force an EEPROM reset
  // Note: EEPROM reset is recommended after firmware updates
  if (io.digitalRead(ENCODER1_PUSH_BUTTON) == LOW)
  {
    netClearPreferences();
    eepromInvalidate();
    diskInit(true);

    // ledcWrite(PIN_LCD_BL, 255);  // Default value 255 = 100%
    // tft.setTextSize(2);
    // tft.setTextColor(TH.text, TH.bg);
    // tft.println(getVersion(true));
    // tft.println();
    // tft.setTextColor(TH.text_warn, TH.bg);
    // tft.print("EEPROM Resetting");
    Serial.println("EEPROM Resetting");
    while (io.digitalRead(ENCODER1_PUSH_BUTTON) == LOW)
      delay(100);
  }

  // Check for SI4732 connected on I2C interface
  // If the SI4732 is not detected, then halt with no further processing
  rx.setI2CFastModeCustom(100000);

  // Looks for the I2C bus address and set it.  Returns 0 if error
  int16_t si4735Addr = rx.getDeviceI2CAddress(RESET_PIN);
  if (!si4735Addr)
  {
    // ledcWrite(PIN_LCD_BL, 255);  // Default value 255 = 100%
    // tft.setTextSize(2);
    // tft.setTextColor(TH.text_warn, TH.bg);
    // tft.println("Si4732 not detected");
    Serial.println("Si4732 not detected");
    while (1)
      ;
  }

  rx.setup(RESET_PIN, MW_BAND_TYPE);
  // Comment the line above and uncomment the three lines below if you are using external ref clock (active crystal or signal generator)
  // rx.setRefClock(32768);
  // rx.setRefClockPrescaler(1);   // will work with 32768
  // rx.setup(RESET_PIN, 0, MW_BAND_TYPE, SI473X_ANALOG_AUDIO, XOSCEN_RCLK);

  // Attached pin to allows SI4732 library to mute audio as required to minimise loud clicks
  rx.setAudioMuteMcuPin(AUDIO_MUTE);

  delay(300);

  // Audio Amplifier Enable. G8PTN: Added
  // After the SI4732 has been setup, enable the audio amplifier
  io.pinMode(PIN_NS4160_EN, INPUT);
  io.pinMode(PIN_MAX97220_EN, INPUT);

  // If EEPROM contents are ok...
  if (eepromVerify())
  {
    // Load configuration from EEPROM
    eepromLoadConfig();

    int total = getTotalMemories();
    char local_seek_options[256] = "自动搜索\n手动搜索";
    for (int i = 0; i < total; i++)
    {
      char buffer[10];
      if (memories[i].freq)
      {
        sprintf(buffer, "\n%02u-%u", i + 1, memories[i].freq);
      }
      else
      {
        sprintf(buffer, "\n%02u-_____", i + 1);
      }
      strncat(local_seek_options, buffer, sizeof(local_seek_options) - strlen(local_seek_options) - 1);
    }
    set_var_local_seek_options(local_seek_options);

    total = getTotalBands();
    size_t total_len = 1; // 包含结尾 '\0'
    for (size_t i = 0; i < total; i++)
    {
      total_len += strlen(bands[i].bandName) + 1; // 每个字符串长度 + 换行符
    }
    char *local_band_options = (char *)malloc(total_len);
    *local_band_options = '\0'; // 确保初始为空字符串
    for (size_t i = 0; i < total; i++)
    {
      if (i > 0)
      {
        strcat(local_band_options, "\n"); // 非首元素添加换行
      }
      strcat(local_band_options, bands[i].bandName); // 安全追加（因预分配足够空间）
    }
    set_var_local_band_options(local_band_options);
    free(local_band_options); // 避免内存泄漏

    total = getTotalModes();
    total_len = 1; // 包含结尾 '\0'
    for (size_t i = 0; i < total; i++)
    {
      total_len += strlen(bandModeDesc[i]) + 1; // 每个字符串长度 + 换行符
    }
    char *local_mode_options = (char *)malloc(total_len);
    *local_mode_options = '\0'; // 确保初始为空字符串
    for (size_t i = 0; i < total; i++)
    {
      if (i > 0)
      {
        strcat(local_mode_options, "\n"); // 非首元素添加换行
      }
      strcat(local_mode_options, bandModeDesc[i]); // 安全追加（因预分配足够空间）
    }
    set_var_local_mode_options(local_mode_options);
    free(local_mode_options); // 避免内存泄漏

    total = getTotalFmSteps();
    total_len = 1; // 包含结尾 '\0'
    for (size_t i = 0; i < total; i++)
    {
      total_len += strlen(fmSteps[i].desc) + 1; // 每个字符串长度 + 换行符
    }
    char *local_fmstep_options = (char *)malloc(total_len);
    *local_fmstep_options = '\0'; // 确保初始为空字符串
    for (size_t i = 0; i < total; i++)
    {
      if (i > 0)
      {
        strcat(local_fmstep_options, "\n"); // 非首元素添加换行
      }
      strcat(local_fmstep_options, fmSteps[i].desc); // 安全追加（因预分配足够空间）
    }
    set_var_local_fmstep_options(local_fmstep_options);
    free(local_fmstep_options); // 避免内存泄漏

    total = getTotalSsbSteps();
    total_len = 1; // 包含结尾 '\0'
    for (size_t i = 0; i < total; i++)
    {
      total_len += strlen(ssbSteps[i].desc) + 1; // 每个字符串长度 + 换行符
    }
    char *local_ssbstep_options = (char *)malloc(total_len);
    *local_ssbstep_options = '\0'; // 确保初始为空字符串
    for (size_t i = 0; i < total; i++)
    {
      if (i > 0)
      {
        strcat(local_ssbstep_options, "\n"); // 非首元素添加换行
      }
      strcat(local_ssbstep_options, ssbSteps[i].desc); // 安全追加（因预分配足够空间）
    }
    set_var_local_ssbstep_options(local_ssbstep_options);
    free(local_ssbstep_options); // 避免内存泄漏

    total = getTotalAmSteps();
    total_len = 1; // 包含结尾 '\0'
    for (size_t i = 0; i < total; i++)
    {
      total_len += strlen(amSteps[i].desc) + 1; // 每个字符串长度 + 换行符
    }
    char *local_amstep_options = (char *)malloc(total_len);
    *local_amstep_options = '\0'; // 确保初始为空字符串
    for (size_t i = 0; i < total; i++)
    {
      if (i > 0)
      {
        strcat(local_amstep_options, "\n"); // 非首元素添加换行
      }
      strcat(local_amstep_options, amSteps[i].desc); // 安全追加（因预分配足够空间）
    }
    set_var_local_amstep_options(local_amstep_options);
    free(local_amstep_options); // 避免内存泄漏

    total = getTotalFmBandwidths();
    total_len = 1; // 包含结尾 '\0'
    for (size_t i = 0; i < total; i++)
    {
      total_len += strlen(fmBandwidths[i].desc) + 1; // 每个字符串长度 + 换行符
    }
    char *local_fmbandwidth_options = (char *)malloc(total_len);
    *local_fmbandwidth_options = '\0'; // 确保初始为空字符串
    for (size_t i = 0; i < total; i++)
    {
      if (i > 0)
      {
        strcat(local_fmbandwidth_options, "\n"); // 非首元素添加换行
      }
      strcat(local_fmbandwidth_options, fmBandwidths[i].desc); // 安全追加（因预分配足够空间）
    }
    set_var_local_fmbandwidth_options(local_fmbandwidth_options);
    free(local_fmbandwidth_options); // 避免内存泄漏

    total = getTotalSsbBandwidths();
    total_len = 1; // 包含结尾 '\0'
    for (size_t i = 0; i < total; i++)
    {
      total_len += strlen(ssbBandwidths[i].desc) + 1; // 每个字符串长度 + 换行符
    }
    char *local_ssbbandwidth_options = (char *)malloc(total_len);
    *local_ssbbandwidth_options = '\0'; // 确保初始为空字符串
    for (size_t i = 0; i < total; i++)
    {
      if (i > 0)
      {
        strcat(local_ssbbandwidth_options, "\n"); // 非首元素添加换行
      }
      strcat(local_ssbbandwidth_options, ssbBandwidths[i].desc); // 安全追加（因预分配足够空间）
    }
    set_var_local_ssbbandwidth_options(local_ssbbandwidth_options);
    free(local_ssbbandwidth_options); // 避免内存泄漏

    total = getTotalAmBandwidths();
    total_len = 1; // 包含结尾 '\0'
    for (size_t i = 0; i < total; i++)
    {
      total_len += strlen(amBandwidths[i].desc) + 1; // 每个字符串长度 + 换行符
    }
    char *local_ambandwidth_options = (char *)malloc(total_len);
    *local_ambandwidth_options = '\0'; // 确保初始为空字符串
    for (size_t i = 0; i < total; i++)
    {
      if (i > 0)
      {
        strcat(local_ambandwidth_options, "\n"); // 非首元素添加换行
      }
      strcat(local_ambandwidth_options, amBandwidths[i].desc); // 安全追加（因预分配足够空间）
    }
    set_var_local_ambandwidth_options(local_ambandwidth_options);
    free(local_ambandwidth_options); // 避免内存泄漏
  }
  else
  {
    // Save default configuration to EEPROM
    eepromSaveConfig();
  }

  // ** SI4732 STARTUP **
  // Uses values from EEPROM (Last stored or defaults after EEPROM reset)
  selectBand(get_var_local_band_index(), false);
  delay(50);
  rx.setVolume(get_var_speaker_volume() * 2);
  rx.setMaxSeekTime(SEEK_TIMEOUT);

  // Show help screen on first run
  if (eepromFirstRun())
  {
    // Clear screen buffer
    // spr.fillSprite(TH.bg);
    // drawAboutHelp(0);
    ledcWrite(PIN_LCD_BL, get_var_screen_brightness() * 10);
    delay(1000);
    while (io.digitalRead(ENCODER1_PUSH_BUTTON) != LOW)
      delay(100);
    while (io.digitalRead(ENCODER1_PUSH_BUTTON) == LOW)
      delay(100);
  }

  // Draw display for the first time
  ui_init();
  ledcWrite(PIN_LCD_BL, get_var_screen_brightness() * 10);

  // Connect WiFi, if necessary
  // netInit(wifiModeIdx);

  // Interrupt actions for Rotary encoder
  // Note: Moved to end of setup to avoid inital interrupt actions
  // ICACHE_RAM_ATTR void rotaryEncoder(); see rotaryEncoder implementation below.
  attachInterrupt(digitalPinToInterrupt(ENCODER1_PIN_A), rotaryEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER1_PIN_B), rotaryEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_PIN_A), rotaryEncoder2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_PIN_B), rotaryEncoder2, CHANGE);

  // 配置 IO 中断
  attachInterrupt(digitalPinToInterrupt(IOINT_PIN), handleIOInterrupt, CHANGE);
  updateIOStatus();

  Serial.println("System Ready");
}

// 中断服务函数（IRAM_ATTR确保在RAM中运行）
ICACHE_RAM_ATTR void handleIOInterrupt()
{
  ioInterrupt = true;
}

//
// Reads encoder via interrupt
// Uses Rotary.h and Rotary.cpp implementation to process encoder via
// interrupt. If you do not add ICACHE_RAM_ATTR declaration, the system
// will reboot during attachInterrupt call. The ICACHE_RAM_ATTR macro
// places this function into RAM.
//
ICACHE_RAM_ATTR void rotaryEncoder1()
{
  // Rotary encoder events
  uint8_t encoderStatus = encoder1.process();
  if (encoderStatus)
  {
    encoderCount1 = encoderStatus == DIR_CW ? 1 : -1;
    // seekStop = true;
  }
}

ICACHE_RAM_ATTR void rotaryEncoder2()
{
  // Rotary encoder events
  uint8_t encoderStatus = encoder2.process();
  if (encoderStatus)
  {
    encoderCount2 = encoderStatus == DIR_CW ? 1 : -1;
  }
}

void updateIOStatus()
{
  uint16_t all_val = io.read();
  for (int i = 0; i <= 15; i++)
  {
    int val = all_val & 1;
    if (!val)
      Serial.printf("GPIO: %d is LOW\n", i);
    if (i == PIN_RADIO_EN)
      ioStatus.localRadioEnable = val;
    if (i == PIN_PCM5102_EN)
      ioStatus.netRadioEnable = val;
    if (i == PIN_MAX97220_EN)
      ioStatus.epAmpEnable = val;
    if (i == PIN_NS4160_EN)
      ioStatus.spAmpEnable = val;
    if (i == PIN_BT_CON)
      ioStatus.btCon = val;
    if (i == PCF85063_INT)
      ioStatus.timeInt = val;
    if (i == ENCODER1_PUSH_BUTTON)
      ioStatus.pb1 = val;
    if (i == ENCODER2_PUSH_BUTTON)
      ioStatus.pb2 = val;
    all_val >>= 1;
  }
}

//
// Main event loop
//
void loop()
{
  if (ioInterrupt)
  {
    ioInterrupt = false;
    updateIOStatus();
  }

  pb1st = pb1.update(ioStatus.pb1 == LOW);
  pb2st = pb2.update(ioStatus.pb2 == LOW);

  switch (get_var_page_name())
  {
  case PageName_Main:
    updatePageMain();
    break;
  case PageName_LocalRadio:
    updatePageLocalRadio();
    break;
  case PageName_NetRadio:
    updatePageNetRadio();
    break;
  case PageName_Alarm:
    updatePageAlarm();
    break;
  case PageName_Setting:
    updatePageSetting();
    break;
  case PageName_SettingWiFi:
    updatePageSettingWiFi();
    break;
  case PageName_SettingBluetooth:
    updatePageSettingBluetooth();
    break;
  case PageName_SettingTime:
    updatePageSettingTime();
    break;
  case PageName_SettingScreen:
    updatePageSettingScreen();
    break;
  case PageName_SettingSleep:
    updatePageSettingSleep();
    break;
  case PageName_SettingOperation:
    updatePageSettingOperation();
    break;
  case PageName_SettingAbout:
    updatePageSettingAbout();
    break;
  default:
    break;
  }

  if (encoderCount1)
  {
    encoderCount1 = 0;
  }

  if (encoderCount2)
  {
    encoderCount2 = 0;
  }

  // Tick EEPROM time, saving changes if the occurred and there has been no activity for a while
  eepromTickTime();

  ui_tick();
  lv_timer_handler();
  delay(5);
}
