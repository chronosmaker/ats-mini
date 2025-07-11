#ifndef LOCAL_RADIO_H
#define LOCAL_RADIO_H

void doAgc(int dir);
void doAvc(int dir);
void doSoftMute(int dir);
void doMemory(int dir);
void doSeekMemory(int dir);
void doSaveMemory();
void doBand(int dir);
void doMode(int dir);
void doStep(int dir);
bool doTune(int8_t dir);
bool doSeek(int8_t dir);
void doBandwidth(int dir);
void selectBand(uint8_t idx, bool drawLoadingSSB = true);
void processRssiSnr();

#endif
