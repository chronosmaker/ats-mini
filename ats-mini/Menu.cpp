#include "Common.h"
#include "Themes.h"
#include "Utils.h"
#include "Menu.h"
#include "Draw.h"
#include "EIBI.h"

static const char* menu[] =
{
    "Mode",
    "Band",
    "Volume",
    "Step",
    "Seek",
    "Memory",
    "Squelch",
    "Bandwidth",
    "AGC/ATTN",
    "AVC",
    "SoftMute",
    "Settings",
    "Scan",
};

static const char* settings[] =
{
    "Brightness",
    "Calibration",
    "RDS",
    "UTC Offset",
    "FM Region",
    "Theme",
    "UI Layout",
    "Zoom Menu",
    "Scroll Dir.",
    "Sleep",
    "Sleep Mode",
    "Load EiBi",
    "Wi-Fi",
    "About",
};

//
// RDS Menu
//

uint8_t rdsModeIdx = 0;
static const RDSMode rdsMode[] =
{
    {RDS_PS, "PS"},
    {RDS_PS | RDS_CT, "PS+CT"},
    {RDS_PS | RDS_PI, "PS+PI"},
    {RDS_PS | RDS_PI | RDS_CT, "PS+PI+CT"},
    {RDS_PS | RDS_PI | RDS_RT | RDS_PT, "ALL-CT (EU)"},
    {RDS_PS | RDS_PI | RDS_RT | RDS_PT | RDS_RBDS, "ALL-CT (US)"},
    {RDS_PS | RDS_PI | RDS_RT | RDS_PT | RDS_CT, "ALL (EU)"},
    {RDS_PS | RDS_PI | RDS_RT | RDS_PT | RDS_CT | RDS_RBDS, "ALL (US)"},
};

uint8_t getRDSMode() { return (rdsMode[rdsModeIdx].mode); }

//
// Sleep Mode Menu
//

uint8_t sleepModeIdx = SLEEP_LOCKED;
static const char* sleepModeDesc[] =
{ "Locked", "Unlocked", "CPU Sleep" };

//
// UI Layout Menu
//
static const char* uiLayoutDesc[] =
{ "Default", "S-Meter" };

//
// WiFi Mode Menu
//

uint8_t wifiModeIdx = NET_OFF;
static const char* wifiModeDesc[] =
{ "Off", "AP Only", "AP+Connect", "Connect", "Sync Only" };

// Seek mode. Pass true to toggle, false to return the current one
uint8_t seekMode(bool toggle) {
  static uint8_t mode = SEEK_DEFAULT;

  mode = toggle ? (mode == SEEK_DEFAULT ? SEEK_SCHEDULE : SEEK_DEFAULT) : mode;

  // Use normal seek on FM or if there is no schedule loaded
  if (get_var_local_mode_index() == FM || !eibiAvailable() || !clockAvailable())
    return (SEEK_DEFAULT);

  return (mode);
}

//
// Encoder input handlers
//
void doVolume(int dir) {
  int32_t volume = clamp_range(get_var_speaker_volume(), dir, 0, 30);
  set_var_speaker_volume(volume);
  if (!muteOn())
    rx.setVolume(volume * 2);
}

static void clickVolume(bool shortPress) {
  if (shortPress)
    muteOn(!muteOn());
}

static void clickSquelch(bool shortPress) {
  if (shortPress)
    set_var_local_squelch(0);
}

static void clickSeek(bool shortPress) {
  if (shortPress)
    seekMode(true);
}

static void doTheme(int dir) {
  themeIdx = wrap_range(themeIdx, dir, 0, getTotalThemes() - 1);
}

static void doUILayout(int dir) {
  // uiLayoutIdx = uiLayoutIdx > LAST_ITEM(uiLayoutDesc) ? UI_DEFAULT : wrap_range(uiLayoutIdx, dir, 0, LAST_ITEM(uiLayoutDesc));
}

void doFmRegion(int dir) {
  // Only allow for FM mode
  if (get_var_local_mode_index() != FM)
    return;

  FmRegionIdx = wrap_range(FmRegionIdx, dir, 0, getLastFmRegion());
  rx.setFMDeEmphasis(fmRegions[FmRegionIdx].value);
}

void doCal(int dir) {
  int32_t bandIdx = get_var_local_band_index();
  bands[bandIdx].bandCal = clamp_range(bands[bandIdx].bandCal, 10 * dir, -MAX_CAL, MAX_CAL);

  // If in SSB mode set the SI4732/5 BFO value
  // This adjusts the BFO while in the calibration menu
  if (isSSB())
    updateBFO(get_var_local_bfo(), true);
}

void doBrt(int dir) {
  int32_t currentBrt = clamp_range(get_var_screen_brightness(), dir, get_var_screen_brightness_min(), get_var_screen_brightness_max());
  set_var_screen_brightness(currentBrt);
  if (!sleepOn())
    ledcWrite(PIN_LCD_BL, currentBrt * 10);
}

static void doSleep(int dir) {
  currentSleep = clamp_range(currentSleep, 5 * dir, 0, 255);
}

static void doSleepMode(int dir) {
  sleepModeIdx = wrap_range(sleepModeIdx, dir, 0, LAST_ITEM(sleepModeDesc));
}

static void doWiFiMode(int dir) {
  wifiModeIdx = wrap_range(wifiModeIdx, dir, 0, LAST_ITEM(wifiModeDesc));
}

static void clickWiFiMode(uint8_t mode, bool shortPress) {
  netInit(mode);
}

static void doRDSMode(int dir) {
  rdsModeIdx = wrap_range(rdsModeIdx, dir, 0, LAST_ITEM(rdsMode));
  if (!(getRDSMode() & RDS_CT))
    clockReset();
}

static void doUTCOffset(int dir) {
  utcOffsetIdx = wrap_range(utcOffsetIdx, dir, 0, getLastUtcOffset());
  clockRefreshTime();
}

static void doZoom(int dir) {
  // zoomMenu = !zoomMenu;
}

static void doScrollDir(int dir) {
  scrollDirection = (scrollDirection == 1) ? -1 : 1;
}

uint8_t doAbout(int dir) {
  static uint8_t aboutScreen = 0;
  aboutScreen = clamp_range(aboutScreen, dir, 0, 2);
  return aboutScreen;
}

static void clickMemory(uint8_t idx, bool shortPress) {
  // // Must have a valid index
  // if (idx > getLastMemory())
  //   return;

  // // If clicking on an empty memory slot, save to it
  // if (!memories[idx].freq)
  //   memories[idx] = newMemory;
  // // On a press, delete memory slot contents
  // else if (shortPress)
  //   memories[idx].freq = 0;
  // // On a click, do nothing, slot already activated in doMemory()
}

void doSquelch(int dir) {
  set_var_local_squelch(clamp_range(get_var_local_squelch(), dir, 0, 127));
}

//
// Handle encoder input in menu
//

static void clickMenu(int cmd, bool shortPress) {
  // switch (cmd)
  // {
  // case MENU_MEMORY:
  // newMemory.freq = get_var_local_frequency() + get_var_local_bfo() / 1000;
  // newMemory.hz100 = (get_var_local_bfo() % 1000) / 100;
  // newMemory.mode = get_var_local_mode_index();
  // newMemory.band = get_var_local_band_index();
  // doMemory(0);
  // break;

  // case MENU_SOFTMUTE:
  // No soft mute in FM mode
  // if (get_var_local_mode_index() != FM)
  // currentCmd = CMD_SOFTMUTE;
  //   break;

  // case MENU_AVC:
  // No AVC in FM mode
  // if (get_var_local_mode_index() != FM)
  // currentCmd = CMD_AVC;
  //   break;

  // case MENU_SCAN:
  // Run a band scan around current frequency with the same
  // step as scale resolution (10kHz for AM, 100kHz for FM)
  // drawMessage("Scanning...");
  // scanRun(get_var_local_frequency(), 10);
  // break;
  // }
}

static void clickSettings(int cmd, bool shortPress) {
  // switch (cmd)
  // {
  // case MENU_CALIBRATION:
  //   // if (isSSB())
  //   //   currentCmd = CMD_CAL;
  //   break;
  // case MENU_FM_REGION:
  //   // Only in FM mode
  //   // if (get_var_local_mode_index() == FM)
  //   //   currentCmd = CMD_FM_REGION;
  //   break;
  // case MENU_LOADEIBI:
  //   eibiLoadSchedule();
  //   break;
  // }
}

bool clickHandler(uint16_t cmd, bool shortPress) {
  switch (cmd) {
  case CMD_MENU:
    // clickMenu(menuIdx, shortPress);
    break;
  case CMD_SETTINGS:
    // clickSettings(settingsIdx, shortPress);
    break;
  case CMD_MEMORY:
    // clickMemory(memoryIdx, shortPress);
    break;
  case CMD_WIFIMODE:
    clickWiFiMode(wifiModeIdx, shortPress);
    break;
  case CMD_VOLUME:
    clickVolume(shortPress);
    break;
  case CMD_SQUELCH:
    clickSquelch(shortPress);
    break;
  case CMD_SEEK:
    clickSeek(shortPress);
    break;
  default:
    return (false);
  }

  // Encoder input handled
  return (true);
}

//
// Draw functions
//

static void drawCommon(const char* title, int x, int y, int sx, bool cursor = false) {
  /*
  spr.setTextDatum(MC_DATUM);

  spr.setTextColor(TH.menu_hdr, TH.menu_bg);
  spr.fillSmoothRoundRect(1+x, 1+y, 76+sx, 110, 4, TH.menu_border);
  spr.fillSmoothRoundRect(2+x, 2+y, 74+sx, 108, 4, TH.menu_bg);

  spr.drawString(title, 40+x+(sx/2), 12+y, 2);
  spr.drawLine(1+x, 23+y, 76+sx, 23+y, TH.menu_border);

  spr.setTextFont(0);
  spr.setTextColor(TH.menu_item, TH.menu_bg);
  if(cursor)
    spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_hl_bg);
  */
}

static void drawMenu(int x, int y, int sx) {
  /*
  spr.setTextDatum(MC_DATUM);

  spr.fillSmoothRoundRect(1+x, 1+y, 76+sx, 110, 4, TH.menu_border);
  spr.fillSmoothRoundRect(2+x, 2+y, 74+sx, 108, 4, TH.menu_bg);
  spr.setTextColor(TH.menu_hdr, TH.menu_bg);

  spr.drawString("Menu", 40+x+(sx/2), 12+y, 2);
  spr.drawLine(1+x, 23+y, 76+sx, 23+y, TH.menu_border);

  spr.setTextFont(0);
  spr.setTextColor(TH.menu_item, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_hl_bg);

  int count = ITEM_COUNT(menu);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(menu[abs((menuIdx+count+i)%count)]);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }
    spr.setTextDatum(MC_DATUM);
    spr.drawString(menu[abs((menuIdx+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawSettings(int x, int y, int sx) {
  /*
  spr.setTextDatum(MC_DATUM);

  spr.fillSmoothRoundRect(1+x, 1+y, 76+sx, 110, 4, TH.menu_border);
  spr.fillSmoothRoundRect(2+x, 2+y, 74+sx, 108, 4, TH.menu_bg);
  spr.setTextColor(TH.menu_hdr, TH.menu_bg);
  spr.drawString("Settings", 40+x+(sx/2), 12+y, 2);
  spr.drawLine(1+x, 23+y, 76+sx, 23+y, TH.menu_border);

  spr.setTextFont(0);
  spr.setTextColor(TH.menu_item, TH.menu_bg);
  spr.fillRoundRect(6+x, 24+y+(2*16), 66+sx, 16, 2, TH.menu_hl_bg);

  int count = ITEM_COUNT(settings);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(settings[abs((settingsIdx+count+i)%count)]);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(settings[abs((settingsIdx+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawMode(int x, int y, int sx) {
  /*
  drawCommon(menu[MENU_MODE], x, y, sx, true);

  int count = ITEM_COUNT(bandModeDesc);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(bandModeDesc[abs((get_var_local_mode_index()+count+i)%count)]);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    if((get_var_local_mode_index()!=FM) || (i==0))
     spr.drawString(bandModeDesc[abs((get_var_local_mode_index()+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawStep(int x, int y, int sx) {
  /*
  int count = getLastStep(get_var_local_mode_index()) + 1;
  int idx   = stepIdx[get_var_local_mode_index()] + count;

  drawCommon(menu[MENU_STEP], x, y, sx, true);

  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(steps[get_var_local_mode_index()][abs((idx+i)%count)].desc);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(steps[get_var_local_mode_index()][abs((idx+i)%count)].desc, 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawSeek(int x, int y, int sx) {
  /*
  drawCommon(menu[MENU_SEEK], x, y, sx);
  drawZoomedMenu(menu[MENU_SEEK]);
  spr.drawSmoothArc(40+x+(sx/2), 66+y, 30, 27, 45, 180, TH.menu_param, TH.menu_bg);
  spr.fillTriangle(40+x+(sx/2)-5, 66+y-32, 40+x+(sx/2)+5, 66+y-27, 40+x+(sx/2)-5, 66+y-22, TH.menu_param);
  spr.drawSmoothArc(40+x+(sx/2), 66+y, 30, 27, 225, 360, TH.menu_param, TH.menu_bg);
  spr.fillTriangle(40+x+(sx/2)+5, 66+y+32, 40+x+(sx/2)-5, 66+y+27, 40+x+(sx/2)+5, 66+y+22, TH.menu_param);

  if(seekMode()==SEEK_SCHEDULE)
  {
    spr.drawCircle(40+x+(sx/2), 66+y, 10, TH.menu_param);
    spr.drawLine(40+x+(sx/2), 66+y, 40+x+(sx/2), 66+y-7, TH.menu_param);
    spr.drawLine(40+x+(sx/2), 66+y, 40+x+(sx/2)+4, 66+y+4, TH.menu_param);
  }
  */
}

static void drawBand(int x, int y, int sx) {
  /*
  drawCommon(menu[MENU_BAND], x, y, sx, true);

  int count = ITEM_COUNT(bands);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(bands[abs((bandIdx+count+i)%count)].bandName);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(bands[abs((bandIdx+count+i)%count)].bandName, 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawBandwidth(int x, int y, int sx) {
  /*
  int count = getLastBandwidth(get_var_local_mode_index()) + 1;
  int idx   = bwIdx[get_var_local_mode_index()] + count;

  drawCommon(menu[MENU_BW], x, y, sx, true);

  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(bandwidths[get_var_local_mode_index()][abs((idx+i)%count)].desc);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(bandwidths[get_var_local_mode_index()][abs((idx+i)%count)].desc, 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawSleepMode(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_SLEEPMODE], x, y, sx, true);

  int count = ITEM_COUNT(sleepModeDesc);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(sleepModeDesc[abs((sleepModeIdx+count+i)%count)]);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(sleepModeDesc[abs((sleepModeIdx+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawWiFiMode(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_WIFIMODE], x, y, sx, true);

  int count = ITEM_COUNT(wifiModeDesc);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(wifiModeDesc[abs((wifiModeIdx+count+i)%count)]);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(wifiModeDesc[abs((wifiModeIdx+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawTheme(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_THEME], x, y, sx, true);

  int count = getTotalThemes();
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(theme[abs((themeIdx+count+i)%count)].name);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(theme[abs((themeIdx+count+i)%count)].name, 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawUILayout(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_UI], x, y, sx, true);

  int count = ITEM_COUNT(uiLayoutDesc);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(uiLayoutDesc[abs((uiLayoutIdx+count+i)%count)]);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    // Prevent repeats for short menus
    if (count < 5 && ((uiLayoutIdx+i) < 0 || (uiLayoutIdx+i) >= count)) {
      continue;
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(uiLayoutDesc[abs((uiLayoutIdx+count+i)%count)], 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawRDSMode(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_RDS], x, y, sx, true);

  int count = ITEM_COUNT(rdsMode);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(rdsMode[abs((rdsModeIdx+count+i)%count)].desc);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(rdsMode[abs((rdsModeIdx+count+i)%count)].desc, 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawUTCOffset(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_UTCOFFSET], x, y, sx, true);

  int count = ITEM_COUNT(utcOffsets);
  uint8_t idx = utcOffsetIdx;

  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0)
    {
      drawZoomedMenu(utcOffsets[abs((idx+count+i)%count)].desc);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    }
    else
    {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(utcOffsets[abs((idx+count+i)%count)].desc, 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawMemory(int x, int y, int sx) {
  /*
  char label_memory[16];
  sprintf(label_memory, "%s %2.2d", menu[MENU_MEMORY], memoryIdx + 1);
  drawCommon(label_memory, x, y, sx, true);

  int count = ITEM_COUNT(memories);
  for(int i=-2 ; i<3 ; i++)
  {
    int j = abs((memoryIdx+count+i)%count);
    char buf[16];
    const char *text = buf;

    if(i==0 && !memories[j].freq)
      text = "Add";
    else if(!memories[j].freq)
      text = "- - -";
    else if(memories[j].mode==FM)
      sprintf(buf, "%3.2f %s", memories[j].freq / 100.0, bandModeDesc[memories[j].mode]);
    else
      sprintf(buf, "%5d %s", memories[j].freq, bandModeDesc[memories[j].mode]);

    if(i==0) {
      drawZoomedMenu(text);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(text, 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawVolume(int x, int y, int sx) {
  /*
  drawCommon(menu[MENU_VOLUME], x, y, sx);
  drawZoomedMenu(menu[MENU_VOLUME]);
  spr.setTextDatum(MC_DATUM);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.drawNumber(volume, 40+x+(sx/2), 66+y, 7);

  if(muteOn())
  {
    for(int i=-3; i<4; i++)
    {
      spr.drawLine(40+x+(sx/2) + 30 + i, 66 + y - 30 + i, 40+x+(sx/2) - 30 + i, 66 + y + 30 + i, TH.menu_param);
    }
  }
  */
}

static void drawAgc(int x, int y, int sx) {
  /*
  drawCommon(menu[MENU_AGC_ATT], x, y, sx);
  drawZoomedMenu(menu[MENU_AGC_ATT]);
  spr.setTextDatum(MC_DATUM);
  spr.setTextColor(TH.menu_param, TH.menu_bg);

  // G8PTN: Read back value is not used
  // rx.getAutomaticGainControl();
  if(!agcNdx && !agcIdx)
  {
    spr.setFreeFont(&Orbitron_Light_24);
    spr.drawString("AGC", 40+x+(sx/2), 48+y);
    spr.drawString("On", 40+x+(sx/2), 72+y);
    spr.setTextFont(0);
  }
  else
  {
    char text[16];
    sprintf(text, "%2.2d", agcNdx);
    spr.drawString(text, 40+x+(sx/2), 60+y, 7);
  }
  */
}

static void drawSquelch(int x, int y, int sx) {
  /*
  drawCommon(menu[MENU_SQUELCH], x, y, sx);
  drawZoomedMenu(menu[MENU_SQUELCH]);
  spr.setTextDatum(MC_DATUM);

  if(currentSquelch)
  {
    spr.drawNumber(currentSquelch, 40+x+(sx/2), 60+y, 4);
    spr.drawString("dBuV", 40+x+(sx/2), 90+y, 4);
  }
  else
  {
    spr.drawString("Off", 40+x+(sx/2), 60+y, 4);
  }
  */
}

static void drawSoftMuteMaxAtt(int x, int y, int sx) {
  /*
  drawCommon(menu[MENU_SOFTMUTE], x, y, sx);
  drawZoomedMenu(menu[MENU_SOFTMUTE]);
  spr.setTextDatum(MC_DATUM);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.drawString("Max Attn", 40+x+(sx/2), 32+y, 2);
  spr.drawNumber(softMuteMaxAttIdx, 40+x+(sx/2), 60+y, 4);
  spr.drawString("dB", 40+x+(sx/2), 90+y, 4);
  */
}

static void drawCal(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_CALIBRATION], x, y, sx);
  drawZoomedMenu(settings[MENU_CALIBRATION]);
  spr.setTextDatum(MC_DATUM);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.drawNumber(getCurrentBand()->bandCal, 40+x+(sx/2), 60+y, 4);
  spr.drawString("Hz", 40+x+(sx/2), 90+y, 4);
  */
}

static void drawAvc(int x, int y, int sx) {
  /*
  drawCommon(menu[MENU_AVC], x, y, sx);
  drawZoomedMenu(menu[MENU_AVC]);
  spr.setTextDatum(MC_DATUM);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.drawString("Max Gain", 40+x+(sx/2), 32+y, 2);

  // Only show AVC for AM and SSB modes
  if(get_var_local_mode_index()!=FM)
  {
    int currentAvc = isSSB()? SsbAvcIdx : AmAvcIdx;
    spr.drawNumber(currentAvc, 40+x+(sx/2), 60+y, 4);
    spr.drawString("dB", 40+x+(sx/2), 90+y, 4);
  }
  */
}

static void drawFmRegion(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_FM_REGION], x, y, sx, true);

  int count = ITEM_COUNT(fmRegions);
  for(int i=-2 ; i<3 ; i++)
  {
    if(i==0) {
      drawZoomedMenu(fmRegions[abs((FmRegionIdx+count+i)%count)].desc);
      spr.setTextColor(TH.menu_hl_text, TH.menu_hl_bg);
    } else {
      spr.setTextColor(TH.menu_item, TH.menu_bg);
    }

    // Prevent repeats for short menus
    if (count < 5 && ((FmRegionIdx+i) < 0 || (FmRegionIdx+i) >= count)) {
      continue;
    }

    spr.setTextDatum(MC_DATUM);
    spr.drawString(fmRegions[abs((FmRegionIdx+count+i)%count)].desc, 40+x+(sx/2), 64+y+(i*16), 2);
  }
  */
}

static void drawBrt(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_BRIGHTNESS], x, y, sx);
  drawZoomedMenu(settings[MENU_BRIGHTNESS]);
  spr.setTextDatum(MC_DATUM);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.drawNumber(currentBrt, 40+x+(sx/2), 60+y, 4);
  */
}

static void drawSleep(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_SLEEP], x, y, sx);
  drawZoomedMenu(settings[MENU_SLEEP]);
  spr.setTextDatum(MC_DATUM);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.drawNumber(currentSleep, 40+x+(sx/2), 60+y, 4);
  */
}

static void drawZoom(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_ZOOM], x, y, sx);
  drawZoomedMenu(settings[MENU_ZOOM]);
  spr.setTextDatum(MC_DATUM);

  spr.setTextColor(TH.menu_param, TH.menu_bg);
  spr.drawString(zoomMenu ? "On" : "Off", 40+x+(sx/2), 60+y, 4);
  */
}

static void drawScrollDir(int x, int y, int sx) {
  /*
  drawCommon(settings[MENU_SCROLL], x, y, sx);
  drawZoomedMenu(settings[MENU_SCROLL]);

  spr.fillRect(37+x+(sx/2), 45+y, 5, 40, TH.menu_param);
  if(scrollDirection>0)
    spr.fillTriangle(39+x+(sx/2)-5, 45+y, 39+x+(sx/2)+5, 45+y, 39+x+(sx/2), 45+y-5, TH.menu_param);
  else
    spr.fillTriangle(39+x+(sx/2)-5, 85+y, 39+x+(sx/2)+5, 85+y, 39+x+(sx/2), 85+y+5, TH.menu_param);
  */
}

static void drawInfo(int x, int y, int sx) {
  /*
  char text[16];

  // Info box
  spr.setTextDatum(ML_DATUM);
  spr.setTextColor(TH.box_text, TH.box_bg);
  spr.fillSmoothRoundRect(1+x, 1+y, 76+sx, 110, 4, TH.box_border);
  spr.fillSmoothRoundRect(2+x, 2+y, 74+sx, 108, 4, TH.box_bg);

  spr.drawString("Step:", 6+x, 64+y+(-3*16), 2);
  spr.drawString(getCurrentStep()->desc, 48+x, 64+y+(-3*16), 2);

  spr.drawString("BW:", 6+x, 64+y+(-2*16), 2);
  spr.drawString(getCurrentBandwidth()->desc, 48+x, 64+y+(-2*16), 2);

  if(!agcNdx && !agcIdx)
  {
    spr.drawString("AGC:", 6+x, 64+y+(-1*16), 2);
    spr.drawString("On", 48+x, 64+y+(-1*16), 2);
  }
  else
  {
    sprintf(text, "%2.2d", agcNdx);
    spr.drawString("Att:", 6+x, 64+y+(-1*16), 2);
    spr.drawString(text, 48+x, 64+y+(-1*16), 2);
  }

  spr.drawString("Vol:", 6+x, 64+y+(0*16), 2);
  if(muteOn() || squelchCutoff)
  {
    spr.setTextColor(TH.box_off_text, TH.box_off_bg);
    sprintf(text, muteOn() ? "Muted" : "%d/sq", volume);
    spr.drawString(text, 48+x, 64+y+(0*16), 2);
    spr.setTextColor(TH.box_text, TH.box_bg);
  }
  else
  {
    spr.setTextColor(TH.box_text, TH.box_bg);
    spr.drawNumber(volume, 48+x, 64+y+(0*16), 2);
  }

  // Draw RDS PI code, if present
  uint16_t piCode = getRdsPiCode();
  if(piCode && get_var_local_mode_index() == FM)
  {
    sprintf(text, "%04X", piCode);
    spr.drawString("PI:", 6+x, 64+y + (1*16), 2);
    spr.drawString(text, 48+x, 64+y + (1*16), 2);
  }
  else
  {
    spr.drawString("AVC:", 6+x, 64+y + (1*16), 2);

    if(get_var_local_mode_index()==FM)
      sprintf(text, "n/a");
    else if(isSSB())
      sprintf(text, "%2.2ddB", SsbAvcIdx);
    else
      sprintf(text, "%2.2ddB", AmAvcIdx);

    spr.drawString(text, 48+x, 64+y + (1*16), 2);
  }

  // Draw current time
  if(clockGet())
  {
    spr.drawString("Time:", 6+x, 64+y+(2*16), 2);
    spr.drawString(clockGet(), 48+x, 64+y+(2*16), 2);
  }
  */
}
