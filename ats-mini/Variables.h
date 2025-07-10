#ifndef VARIABLES_H
#define VARIABLES_H

#include "Common.h"

extern Memory memories[];
extern Band bands[];
extern const char* bandModeDesc[];
extern const Bandwidth fmBandwidths[];
extern const Bandwidth ssbBandwidths[];
extern const Bandwidth amBandwidths[];
extern const Step fmSteps[];
extern const Step ssbSteps[];
extern const Step amSteps[];
extern const FMRegion fmRegions[];
extern const UTCOffset utcOffsets[];

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
