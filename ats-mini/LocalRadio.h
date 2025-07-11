#ifndef LOCAL_RADIO_H
#define LOCAL_RADIO_H

void doBand(int dir);
void doMode(int dir);
void doStep(int dir);
void doTune(int8_t dir);
void doSeek(int8_t dir);
void doBandwidth(int dir);
void doFmRegion(int dir);
void doCal(int dir);
void doAgc(int dir);
void doAvc(int dir);
void doSoftMute(int dir);
void selectBand(uint8_t idx);
void doMemory(int dir);
void doSeekMemory(int dir);
void doSaveMemory();
void processRssiSnr();

#endif
