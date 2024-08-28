#include <input.h>
#include <MCP23017.h>
#include <Wire.h>

TwoWire wire = TwoWire();
MCP23017 mcp = MCP23017(0x20, wire);
uint8_t thiskey = 0;

// Button codes
#define BTN_UP 1
#define BTN_DOWN 2
#define BTN_LEFT 4
#define BTN_RIGHT 8
#define BTN_A 16
#define BTN_SELECT 32
#define BTN_B 64
#define BTN_START 128

void getKey()
{
  thiskey = 0;
  // 0 0 0 0 START B SELECT A 0 0 0 0 RIGHT LEFT DOWN UP
  uint16_t input_raw = mcp.read();
  const uint16_t BITMASK_HIGH = 0x0F00; // 0000 START B SELECT A 0000 0000 0000
  const uint16_t BITMASK_LOW = 0x000F; // 0000 0000 0000 RIGHT LEFT DOWN UP
  uint8_t high_nibble = (~input_raw & BITMASK_HIGH) >> 4;
  uint8_t low_nibble = (~input_raw & BITMASK_LOW);
  thiskey = high_nibble | low_nibble;
}

void keyboardInit()
{
  wire.begin(D2, D1);
  mcp.init();
  //Port A as input (Last pin output only)
  mcp.portMode(MCP23017Port::A, 0x0F);
  //Port B as input (Last pin output only)
  mcp.portMode(MCP23017Port::B, 0x0F); 
  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);  //Reset port A 
  mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);  //Reset port B
}
