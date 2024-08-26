#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <Arduino.h>
#include <EEPROM.h>
#include "settings.h"
#include <progmem/icons.h>

struct RTCData {
  int16_t saveMenuPos;
  int16_t saveStartMenuPos;
  uint32_t crc32;
};

extern RTCData rtcData;

uint32_t calculateCRC32inRTC(const uint8_t *data);
uint8_t drawDialog();
void drawMenuBackground();
void drawSave(uint8_t startPos, uint8_t selectPos);
uint8_t getSaveLength();
void deleteSave(uint8_t num, uint16_t end);
void saveManager();
void drawIco(const uint8_t *a, int16_t x, int16_t y, int16_t w, int16_t h);
void softwareMenu();
void drawVersionInFileList();
void fileList(String path);
void loadBinFromSPIFS(char fileName[]);
void loadLgeFromSPIFS(char fileName[]);

#endif // FILE_MANAGER_HPP
