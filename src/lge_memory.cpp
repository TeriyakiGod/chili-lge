#include <lge_memory.h>
#include <display.h>

void memoryAlloc()
{
  lge_mem = (uint8_t *)malloc(RAM_SIZE * sizeof(uint8_t));
  if (lge_mem == NULL)
    Serial.println(F("Out of memory"));
  screenMemoryAlloc();
}

void memoryFree()
{
  screenMemoryFree();
  free(lge_mem);
}
