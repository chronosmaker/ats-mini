#include "Common.h"

//
// Memory Menu
//
Memory memories[MEMORY_COUNT];

//
// Bands Menu
//
// TO CONFIGURE YOUR OWN BAND PLAN:
// Add new bands by inserting new lines in the table below. Remove
// bands by deleting lines. Change bands by editing lines below.
//
// NOTE:
// You have to RESET EEPROM after adding or removing lines in this
// table. Turn your receiver on with the encoder push button pressed
// at first time to RESET the EEPROM.
//

// Band limits are expanded to align with the nearest tuning scale mark
Band bands[] = {
    {"VHF", FM_BAND_TYPE, FM, 6400, 10800, 10390, 2, 0, 0},
    {"ALL", SW_BAND_TYPE, AM, 150, 30000, 15000, 1, 4, 0}, // All band. LW, MW and SW (from 150kHz to 30MHz)
    {"11M", SW_BAND_TYPE, AM, 25600, 26100, 25850, 1, 4, 0},
    {"13M", SW_BAND_TYPE, AM, 21500, 21900, 21650, 1, 4, 0},
    {"15M", SW_BAND_TYPE, AM, 18900, 19100, 18950, 1, 4, 0},
    {"16M", SW_BAND_TYPE, AM, 17500, 18100, 17650, 1, 4, 0},
    {"19M", SW_BAND_TYPE, AM, 15100, 15900, 15450, 1, 4, 0},
    {"22M", SW_BAND_TYPE, AM, 13500, 13900, 13650, 1, 4, 0},
    {"25M", SW_BAND_TYPE, AM, 11000, 13000, 11850, 1, 4, 0},
    {"31M", SW_BAND_TYPE, AM, 9000, 11000, 9650, 1, 4, 0},
    {"41M", SW_BAND_TYPE, AM, 7000, 9000, 7300, 1, 4, 0},
    {"49M", SW_BAND_TYPE, AM, 5000, 7000, 6000, 1, 4, 0},
    {"60M", SW_BAND_TYPE, AM, 4000, 5100, 4950, 1, 4, 0},
    {"75M", SW_BAND_TYPE, AM, 3500, 4000, 3950, 1, 4, 0},
    {"90M", SW_BAND_TYPE, AM, 3000, 3500, 3300, 1, 4, 0},
    {"MW3", MW_BAND_TYPE, AM, 1700, 3500, 2500, 1, 4, 0},
    {"MW2", MW_BAND_TYPE, AM, 495, 1701, 783, 2, 4, 0},
    {"MW1", MW_BAND_TYPE, AM, 150, 1800, 810, 3, 4, 0},
    {"160M", MW_BAND_TYPE, LSB, 1800, 2000, 1900, 5, 4, 0},
    {"80M", SW_BAND_TYPE, LSB, 3500, 4000, 3800, 5, 4, 0},
    {"40M", SW_BAND_TYPE, LSB, 7000, 7300, 7150, 5, 4, 0},
    {"30M", SW_BAND_TYPE, LSB, 10000, 10200, 10125, 5, 4, 0},
    {"20M", SW_BAND_TYPE, USB, 14000, 14400, 14100, 5, 4, 0},
    {"17M", SW_BAND_TYPE, USB, 18000, 18200, 18115, 5, 4, 0},
    {"15M", SW_BAND_TYPE, USB, 21000, 21500, 21225, 5, 4, 0},
    {"12M", SW_BAND_TYPE, USB, 24800, 25000, 24940, 5, 4, 0},
    {"10M", SW_BAND_TYPE, USB, 28000, 29700, 28500, 5, 4, 0},
    {"CB", SW_BAND_TYPE, AM, 25000, 30000, 27135, 0, 4, 0}, // https://www.hfunderground.com/wiki/CB
};

//
// Mode Menu
//
const char* bandModeDesc[] = { "FM", "LSB", "USB", "AM" };

//
// Bandwidth Menu
//
const Bandwidth fmBandwidths[] = {
    {0, "Auto"}, // Automatic - default
    {1, "110k"}, // Force wide (110 kHz) channel filter.
    {2, "84k"},
    {3, "60k"},
    {4, "40k"} };

const Bandwidth ssbBandwidths[] = {
    {4, "0.5k"},
    {5, "1.0k"},
    {0, "1.2k"},
    {1, "2.2k"},
    {2, "3.0k"},
    {3, "4.0k"} };

const Bandwidth amBandwidths[] = {
    {4, "1.0k"},
    {5, "1.8k"},
    {3, "2.0k"},
    {6, "2.5k"},
    {2, "3.0k"},
    {1, "4.0k"},
    {0, "6.0k"} };

const Bandwidth* bandwidths[4] = { fmBandwidths, ssbBandwidths, ssbBandwidths, amBandwidths };

uint8_t bwIdx[4] = { 0, 4, 4, 4 };

//
// Step Menu
//
// FM (kHz * 10)
const Step fmSteps[] = {
    {1, "10k", 1},
    {5, "50k", 5},
    {10, "100k", 10},
    {20, "200k", 20},
    {100, "1M", 10},
};

// SSB (Hz)
const Step ssbSteps[] = {
    {10, "10", 1},
    {25, "25", 1},
    {50, "50", 1},
    {100, "100", 1},
    {500, "500", 1},
    {1000, "1k", 1},
    {5000, "5k", 5},
    {9000, "9k", 9},
    {10000, "10k", 10},
};

// AM (kHz)
const Step amSteps[] = {
    {1, "1k", 1},
    {5, "5k", 5},
    {9, "9k", 9},
    {10, "10k", 10},
    {50, "50k", 10},
    {100, "100k", 10},
    {1000, "1M", 10},
};

const Step* steps[4] = { fmSteps, ssbSteps, ssbSteps, amSteps };

uint8_t stepIdx[4] = { 2, 5, 5, 1 };

const uint8_t ssbFastSteps[] =
{
    3, //  10Hz -> 100Hz
    3, //  25Hz -> 100Hz
    4, //  50Hz -> 500Hz
    5, // 100Hz -> 1kHz
    6, // 500Hz -> 5kHz
    6, //  1kHz -> 5kHz
    8, //  5kHz -> 10kHz
    7, //  9kHz -> 9kHz
    8, // 10kHz -> 10kHz
};

//
// FM Region Menu
//
const FMRegion fmRegions[] = {
  // 50uS de-emphasis
  {0x1, "EU/JP/AU"},
  // 75uS de-emphasis
  {0x2, "US"},
};

//
// UTC Offset Menu
//
const UTCOffset utcOffsets[] = {
    {-8 * 2, "UTC-8", "Fairbanks"},
    {-7 * 2, "UTC-7", "San Francisco"},
    {-6 * 2, "UTC-6", "Denver"},
    {-5 * 2, "UTC-5", "Houston"},
    {-4 * 2, "UTC-4", "New York"},
    {-3 * 2, "UTC-3", "Rio de Janeiro"},
    {-2 * 2, "UTC-2", "Sandwich Islands"},
    {-1 * 2, "UTC-1", "Nuuk"},
    {0 * 2, "UTC+0", "Reykjavik"},
    {1 * 2, "UTC+1", "London"},
    {2 * 2, "UTC+2", "Berlin"},
    {3 * 2, "UTC+3", "Moscow"},
    {4 * 2, "UTC+4", "Yerevan"},
    {5 * 2, "UTC+5", "Astana"},
    {6 * 2, "UTC+6", "Omsk"},
    {7 * 2, "UTC+7", "Novosibirsk"},
    {8 * 2, "UTC+8", "Beijing"},
    {9 * 2, "UTC+9", "Yakutsk"},
    {10 * 2, "UTC+10", "Vladivostok"},
};

uint8_t utcOffsetIdx = 8;

int getTotalMemories() {
  return (ITEM_COUNT(memories));
}

int getTotalBands() {
  return (ITEM_COUNT(bands));
}

int getTotalModes() {
  return (ITEM_COUNT(bandModeDesc));
}

int getTotalFmBandwidths() {
  return (ITEM_COUNT(fmBandwidths));
}
int getTotalSsbBandwidths() {
  return (ITEM_COUNT(ssbBandwidths));
}
int getTotalAmBandwidths() {
  return (ITEM_COUNT(amBandwidths));
}

int getTotalFmSteps() {
  return (ITEM_COUNT(fmSteps));
}
int getTotalSsbSteps() {
  return (ITEM_COUNT(ssbSteps));
}
int getTotalAmSteps() {
  return (ITEM_COUNT(amSteps));
}

int getTotalFmRegions() {
  return (ITEM_COUNT(fmRegions));
}

int getTotalUTCOffsets() {
  return (ITEM_COUNT(utcOffsets));
}

int getTotalSteps() {
  switch (get_var_local_mode_index()) {
  case FM:
    return (ITEM_COUNT(fmSteps));
  case LSB:
    return (ITEM_COUNT(ssbSteps));
  case USB:
    return (ITEM_COUNT(ssbSteps));
  case AM:
    return (ITEM_COUNT(amSteps));
  }
  return 0;
}

int getLastMemory() {
  return (LAST_ITEM(memories));
}

int getLastBand() {
  return (LAST_ITEM(bands));
}

int getLastBandMode() {
  return (LAST_ITEM(bandModeDesc));
}

int getLastBandwidth(int mode) {
  switch (mode) {
  case FM:
    return (LAST_ITEM(fmBandwidths));
  case LSB:
    return (LAST_ITEM(ssbBandwidths));
  case USB:
    return (LAST_ITEM(ssbBandwidths));
  case AM:
    return (LAST_ITEM(amBandwidths));
  }
  return (0);
}

int getLastStep(int mode) {
  switch (mode) {
  case FM:
    return (LAST_ITEM(fmSteps));
  case LSB:
    return (LAST_ITEM(ssbSteps));
  case USB:
    return (LAST_ITEM(ssbSteps));
  case AM:
    return (LAST_ITEM(amSteps));
  }
  return (0);
}

int getLastFmRegion() {
  return (LAST_ITEM(fmRegions));
}

int getLastUtcOffset() {
  return (LAST_ITEM(utcOffsets));
}

Band* getCurrentBand() {
  return (&bands[get_var_local_band_index()]);
}

const Bandwidth* getCurrentBandwidth() {
  return (&bandwidths[get_var_local_mode_index()][bwIdx[get_var_local_mode_index()]]);
}

const Step* getCurrentStep(bool fast) {
  uint8_t idx = stepIdx[get_var_local_mode_index()];
  return (&steps[get_var_local_mode_index()][fast && isSSB() ? ssbFastSteps[idx] : idx]);
}

int getCurrentUTCOffset() {
  return (utcOffsets[utcOffsetIdx].offset);
}

void init_local_seek_options() {
  int total = getTotalMemories();
  const size_t base_len = strlen("自动搜索\n手动搜索");
  const size_t max_entry_len = 12; // "\nXX-XXXXX"格式最大长度
  const size_t buffer_size = base_len + (total * max_entry_len) + 1;

  char* result = (char*)malloc(buffer_size);
  strcpy(result, "自动搜索\n手动搜索");
  for (int i = 0; i < total; i++) {
    char buffer[max_entry_len];
    if (memories[i].freq) {
      snprintf(buffer, sizeof(buffer), "\n%02u-%u", i + 1, memories[i].freq);
    } else {
      snprintf(buffer, sizeof(buffer), "\n%02u-_____", i + 1);
    }
    strncat(result, buffer, buffer_size - strlen(result) - 1);
  }
  set_var_local_seek_options(result);
  free(result);
}

void init_local_band_options() {
  int total = getTotalBands();
  size_t total_len = 1; // 包含结尾 '\0'
  for (size_t i = 0; i < total; i++) {
    total_len += strlen(bands[i].bandName) + 1; // 每个字符串长度 + 换行符
  }
  char* result = (char*)malloc(total_len);
  *result = '\0'; // 确保初始为空字符串
  for (size_t i = 0; i < total; i++) {
    if (i > 0) {
      strcat(result, "\n"); // 非首元素添加换行
    }
    strcat(result, bands[i].bandName); // 安全追加（因预分配足够空间）
  }
  set_var_local_band_options(result);
  free(result); // 避免内存泄漏
}

void init_local_mode_options() {
  int total = getTotalModes();
  size_t total_len = 1; // 包含结尾 '\0'
  for (size_t i = 0; i < total; i++) {
    total_len += strlen(bandModeDesc[i]) + 1; // 每个字符串长度 + 换行符
  }
  char* result = (char*)malloc(total_len);
  *result = '\0'; // 确保初始为空字符串
  for (size_t i = 0; i < total; i++) {
    if (i > 0) {
      strcat(result, "\n"); // 非首元素添加换行
    }
    strcat(result, bandModeDesc[i]); // 安全追加（因预分配足够空间）
  }
  set_var_local_mode_options(result);
  free(result); // 避免内存泄漏
}

void init_local_fmbandwidth_options() {
  int total = getTotalFmBandwidths();
  size_t total_len = 1; // 包含结尾 '\0'
  for (size_t i = 0; i < total; i++) {
    total_len += strlen(fmBandwidths[i].desc) + 1; // 每个字符串长度 + 换行符
  }
  char* result = (char*)malloc(total_len);
  *result = '\0'; // 确保初始为空字符串
  for (size_t i = 0; i < total; i++) {
    if (i > 0) {
      strcat(result, "\n"); // 非首元素添加换行
    }
    strcat(result, fmBandwidths[i].desc); // 安全追加（因预分配足够空间）
  }
  set_var_local_fmbandwidth_options(result);
  free(result); // 避免内存泄漏
}

void init_local_ssbbandwidth_options() {
  int total = getTotalSsbBandwidths();
  size_t total_len = 1; // 包含结尾 '\0'
  for (size_t i = 0; i < total; i++) {
    total_len += strlen(ssbBandwidths[i].desc) + 1; // 每个字符串长度 + 换行符
  }
  char* result = (char*)malloc(total_len);
  *result = '\0'; // 确保初始为空字符串
  for (size_t i = 0; i < total; i++) {
    if (i > 0) {
      strcat(result, "\n"); // 非首元素添加换行
    }
    strcat(result, ssbBandwidths[i].desc); // 安全追加（因预分配足够空间）
  }
  set_var_local_ssbbandwidth_options(result);
  free(result); // 避免内存泄漏
}

void init_local_ambandwidth_options() {
  int total = getTotalAmBandwidths();
  size_t total_len = 1; // 包含结尾 '\0'
  for (size_t i = 0; i < total; i++) {
    total_len += strlen(amBandwidths[i].desc) + 1; // 每个字符串长度 + 换行符
  }
  char* result = (char*)malloc(total_len);
  *result = '\0'; // 确保初始为空字符串
  for (size_t i = 0; i < total; i++) {
    if (i > 0) {
      strcat(result, "\n"); // 非首元素添加换行
    }
    strcat(result, amBandwidths[i].desc); // 安全追加（因预分配足够空间）
  }
  set_var_local_ambandwidth_options(result);
  free(result); // 避免内存泄漏
}

void init_local_fmstep_options() {
  int total = getTotalFmSteps();
  size_t total_len = 1; // 包含结尾 '\0'
  for (size_t i = 0; i < total; i++) {
    total_len += strlen(fmSteps[i].desc) + 1; // 每个字符串长度 + 换行符
  }
  char* result = (char*)malloc(total_len);
  *result = '\0'; // 确保初始为空字符串
  for (size_t i = 0; i < total; i++) {
    if (i > 0) {
      strcat(result, "\n"); // 非首元素添加换行
    }
    strcat(result, fmSteps[i].desc); // 安全追加（因预分配足够空间）
  }
  set_var_local_fmstep_options(result);
  free(result); // 避免内存泄漏
}

void init_local_ssbstep_options() {
  int total = getTotalSsbSteps();
  size_t total_len = 1; // 包含结尾 '\0'
  for (size_t i = 0; i < total; i++) {
    total_len += strlen(ssbSteps[i].desc) + 1; // 每个字符串长度 + 换行符
  }
  char* result = (char*)malloc(total_len);
  *result = '\0'; // 确保初始为空字符串
  for (size_t i = 0; i < total; i++) {
    if (i > 0) {
      strcat(result, "\n"); // 非首元素添加换行
    }
    strcat(result, ssbSteps[i].desc); // 安全追加（因预分配足够空间）
  }
  set_var_local_ssbstep_options(result);
  free(result); // 避免内存泄漏
}

void init_local_amstep_options() {
  int total = getTotalAmSteps();
  size_t total_len = 1; // 包含结尾 '\0'
  for (size_t i = 0; i < total; i++) {
    total_len += strlen(amSteps[i].desc) + 1; // 每个字符串长度 + 换行符
  }
  char* result = (char*)malloc(total_len);
  *result = '\0'; // 确保初始为空字符串
  for (size_t i = 0; i < total; i++) {
    if (i > 0) {
      strcat(result, "\n"); // 非首元素添加换行
    }
    strcat(result, amSteps[i].desc); // 安全追加（因预分配足够空间）
  }
  set_var_local_amstep_options(result);
  free(result); // 避免内存泄漏
}

void init_variables() {
  init_local_seek_options();
  init_local_band_options();
  init_local_mode_options();
  init_local_fmbandwidth_options();
  init_local_ssbbandwidth_options();
  init_local_ambandwidth_options();
  init_local_fmstep_options();
  init_local_ssbstep_options();
  init_local_amstep_options();
}
