#include <rom.h>
#include <lge_memory.h>
#include <progmem/romFlatRace.h>
#include <progmem/splash.h>

void loadRom()
{
  for (uint i = 0; i < sizeof(rom); i++)
    writeMem(i, pgm_read_byte(&rom[i]));
}

void loadRomIco()
{
  for (uint i = 0; i < sizeof(romImage); i++)
    writeMem(i + 1024, pgm_read_byte(&romImage[i]));
}

void loadSplashscreen()
{
  for (uint i = 0; i < sizeof(splashscreen); i++)
    writeMem(i, pgm_read_byte(&splashscreen[i]));
}