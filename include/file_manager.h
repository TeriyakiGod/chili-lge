#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <Arduino.h>
#include <EEPROM.h>
#include "settings.h"

// Icon bitmaps stored in program memory
extern const uint8_t saveIco[] PROGMEM;
extern const uint8_t uploadIco[] PROGMEM;
extern const uint8_t otaIco[] PROGMEM;

// Structure to hold RTC data
struct RTCData {
    int16_t saveMenuPos;
    int16_t saveStartMenuPos;
    uint32_t crc32;
};

// Global variable to store RTC data
extern RTCData rtcData;

// Function to calculate CRC32 for data stored in RTC
uint32_t calculateCRC32inRTC(const uint8_t *data);

// Functions to manage and display file-related operations
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
