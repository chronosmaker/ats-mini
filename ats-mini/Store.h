#ifndef VARIABLES_H
#define VARIABLES_H

typedef struct __attribute__((packed)) {
  uint16_t freq;     // Frequency
  uint8_t band;      // Band
  uint8_t mode : 4;  // Modulation
  uint8_t hz100 : 4; // Hz * 100
} Memory;

typedef struct {
  const char* bandName;  // Band description
  uint8_t bandType;      // Band type (FM, MW, or SW)
  uint8_t bandMode;      // Band mode (FM, AM, LSB, or USB)
  uint16_t minimumFreq;  // Minimum frequency of the band
  uint16_t maximumFreq;  // Maximum frequency of the band
  uint16_t currentFreq;  // Default frequency or current frequency
  int8_t currentStepIdx; // Default frequency step
  int8_t bandwidthIdx;   // Index of the table bandwidthFM, bandwidthAM or bandwidthSSB;
  int16_t bandCal;       // Calibration value
} Band;

typedef struct {
  uint8_t idx;      // SI473X device bandwidth index
  const char* desc; // Bandwidth description
} Bandwidth;

typedef struct {
  int step;         // Step
  const char* desc; // Step description
  uint8_t spacing;  // Seek spacing
} Step;

typedef struct {
  // From https://www.skyworksinc.com/-/media/Skyworks/SL/documents/public/application-notes/AN332.pdf
  // Property 0x1100. FM_DEEMPHASIS
  uint8_t value;
  const char* desc;
} FMRegion;

typedef struct {
  int8_t offset;    // UTC offset in 30 minute intervals
  const char* desc; // Short description
  const char* city; // City name
} UTCOffset;

extern Memory memories[];
extern Band bands[];
extern const char* bandModeDesc[];
extern const Bandwidth fmBandwidths[];
extern const Bandwidth ssbBandwidths[];
extern const Bandwidth amBandwidths[];
extern const Bandwidth* bandwidths[];
extern uint8_t bwIdx[];
extern const Step fmSteps[];
extern const Step ssbSteps[];
extern const Step amSteps[];
extern const Step* steps[];
extern uint8_t stepIdx[];
extern const FMRegion fmRegions[];
extern const UTCOffset utcOffsets[];
extern uint8_t utcOffsetIdx;

extern int getTotalMemories();
extern int getTotalBands();
extern int getTotalModes();
extern int getTotalFmBandwidths();
extern int getTotalSsbBandwidths();
extern int getTotalAmBandwidths();
extern int getTotalFmSteps();
extern int getTotalSsbSteps();
extern int getTotalAmSteps();
extern int getTotalFmRegions();
extern int getTotalUTCOffsets();
extern int getTotalSteps();

extern int getLastMemory();
extern int getLastBand();
extern int getLastBandMode();
extern int getLastBandwidth(int mode);
extern int getLastStep(int mode);
extern int getLastFmRegion();
extern int getLastUtcOffset();

extern Band* getCurrentBand();
extern const Bandwidth* getCurrentBandwidth();
extern const Step* getCurrentStep(bool fast = false);
extern int getCurrentUTCOffset();

void init_local_seek_options();
void init_local_band_options();
void init_local_mode_options();
void init_local_fmbandwidth_options();
void init_local_ssbbandwidth_options();
void init_local_ambandwidth_options();
void init_local_fmstep_options();
void init_local_ssbstep_options();
void init_local_amstep_options();
extern void init_variables();

#endif // VARIABLES_H
