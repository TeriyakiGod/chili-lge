# esp-lge
TODO:
- [ ] Fix loading roms
- [ ] Add a description
- [ ] Refactor the project structure
- [x] Move project to platformio/arduino
- [ ] Try to move to platformio/esp-idf
- [ ] configure the project for vscode
- [ ] Add a CI/CD pipeline
- [ ] Create a makefile to automate the build process

## Quick Start

1. Clone the repository
2. Install and start Arduino IDE
3. Go to arduino settings
4. Install the ESP8266 board using link: https://arduino.esp8266.com/stable/package_esp8266com_index.json,https://espressif.github.io/arduino-esp32/package_esp32_index.json
5. Set sketchbook folder to arduino folder in the repository
6. Open the project in Arduino IDE
7. Select the board and port
8. Compile and upload the project

### To upload games
1. Copy arduino-littlefs-upload-1.1.8.vsix to {user_home}/.arduinoIDE/plugins/
2. CTRL+SHIFT+P -> Upload LittleFS
