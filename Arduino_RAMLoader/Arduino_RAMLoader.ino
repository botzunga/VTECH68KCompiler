// include the SD library:
#include <SPI.h>
#include <SD.h>

/* C:\Users\Andrea\Desktop\68KCompiler\LOADER.BIN (30/12/2018 20:12:48)
   DébutPosition: 00000000, FinPosition: 00000165, Longueur: 00000166 */
const int LDR_STAGE1_LEN=358;
const unsigned char LDR_STAGE1[358] PROGMEM = {
  0x49, 0x51, 0x50, 0x20, 0x51, 0x41, 0x20, 0x54, 0x45, 0x53, 0x54, 0x49,
  0x4E, 0x47, 0x20, 0x50, 0x52, 0x4F, 0x47, 0x00, 0x13, 0xFC, 0x00, 0x82,
  0x00, 0x60, 0x10, 0x01, 0x20, 0x7C, 0x00, 0xA0, 0x10, 0x00, 0x22, 0x7C,
  0x00, 0x20, 0xA0, 0x00, 0x20, 0x3C, 0x00, 0x00, 0x08, 0x00, 0x32, 0xD8,
  0x51, 0xC8, 0xFF, 0xFC, 0x4E, 0xF9, 0x00, 0x20, 0xA0, 0x00, 0x22, 0x7C,
  0x00, 0x30, 0x00, 0x00, 0x20, 0x3C, 0x00, 0x00, 0x3F, 0xFF, 0x22, 0xC1,
  0x51, 0xC8, 0xFF, 0xFC, 0x4E, 0x75, 0x20, 0x7C, 0x00, 0xA0, 0x00, 0x00,
  0x30, 0xBC, 0x00, 0x00, 0x23, 0xFC, 0xAB, 0xCD, 0xAB, 0xCD, 0x00, 0xA0,
  0x00, 0x06, 0x23, 0xFC, 0xDE, 0xAD, 0xF0, 0x0D, 0x00, 0xA0, 0x00, 0x02,
  0x20, 0x7C, 0x00, 0xA0, 0x00, 0x00, 0x30, 0xBC, 0x00, 0x00, 0x10, 0x39,
  0x00, 0x60, 0x08, 0x03, 0x0C, 0x00, 0x00, 0x00, 0x66, 0xF4, 0x13, 0xFC,
  0x00, 0x01, 0x00, 0x60, 0x01, 0x01, 0x10, 0x39, 0x00, 0xA0, 0x00, 0x01,
  0x13, 0xFC, 0x00, 0x00, 0x00, 0x60, 0x01, 0x01, 0x0C, 0x00, 0x00, 0x01,
  0x67, 0x00, 0x00, 0x20, 0x0C, 0x00, 0x00, 0x02, 0x67, 0x00, 0x00, 0x22,
  0x0C, 0x00, 0x00, 0x03, 0x67, 0x00, 0x00, 0x52, 0x0C, 0x00, 0x00, 0x04,
  0x67, 0x00, 0x00, 0xA4, 0x4E, 0xF9, 0x00, 0xA0, 0x00, 0x76, 0x10, 0xBC,
  0x00, 0x68, 0x4E, 0xF9, 0x00, 0xA0, 0x00, 0x58, 0x13, 0xFC, 0x00, 0x01,
  0x00, 0x60, 0x01, 0x01, 0x20, 0x79, 0x00, 0xA0, 0x00, 0x02, 0x22, 0x7C,
  0x00, 0xA0, 0x10, 0x00, 0x20, 0x3C, 0x00, 0x00, 0x04, 0x00, 0x32, 0xD8,
  0x51, 0xC8, 0xFF, 0xFC, 0x23, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0,
  0x00, 0x00, 0x13, 0xFC, 0x00, 0x00, 0x00, 0x60, 0x01, 0x01, 0x4E, 0xF9,
  0x00, 0xA0, 0x00, 0x58, 0x13, 0xFC, 0x00, 0x01, 0x00, 0x60, 0x01, 0x01,
  0x20, 0x7C, 0x00, 0xA0, 0x10, 0x00, 0x22, 0x79, 0x00, 0xA0, 0x00, 0x02,
  0x23, 0xFC, 0xCA, 0xFE, 0xCA, 0xFE, 0x00, 0xA0, 0x00, 0x06, 0x23, 0xFC,
  0x00, 0x00, 0xCA, 0xFE, 0x00, 0xA0, 0x00, 0x08, 0x33, 0xFC, 0xCA, 0xFE,
  0x00, 0xA0, 0x00, 0x00, 0x20, 0x3C, 0x00, 0x00, 0x08, 0x00, 0x20, 0x3C,
  0x00, 0x00, 0x07, 0xFF, 0x32, 0xD8, 0x51, 0xC8, 0xFF, 0xFC, 0x23, 0xFC,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x13, 0xFC, 0x00, 0x00,
  0x00, 0x60, 0x01, 0x01, 0x4E, 0xF9, 0x00, 0xA0, 0x00, 0x58, 0x4E, 0xF9,
  0x00, 0x31, 0x00, 0x00, 0x4E, 0xF9, 0x00, 0xA0, 0x00, 0x58
};

/* C:\Users\Andrea\Desktop\68KCompiler\PROGRAM.BIN (30/12/2018 20:12:48)
   DébutPosition: 00000000, FinPosition: 000004EB, Longueur: 000004EC */
const int LDR_STAGE2_LEN=1454;
const unsigned char LDR_STAGE2[1454] PROGMEM = {
  0x4E, 0xF9, 0x00, 0x20, 0xA4, 0x36, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04,
  0x00, 0x14, 0x19, 0x86, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x48, 0xE7,
  0xC0, 0x00, 0x10, 0x39, 0x00, 0x60, 0x10, 0x09, 0x02, 0x80, 0x00, 0x00,
  0x00, 0x04, 0x72, 0x04, 0xB2, 0x80, 0x66, 0xEA, 0x08, 0x39, 0x00, 0x02,
  0x00, 0x60, 0x10, 0x09, 0x66, 0xF6, 0x4C, 0xDF, 0x00, 0x03, 0x4E, 0x75,
  0x48, 0xE7, 0x60, 0x00, 0x24, 0x3C, 0x00, 0x00, 0x00, 0x07, 0xE9, 0x98,
  0x22, 0x00, 0xC2, 0xBC, 0x00, 0x00, 0x00, 0x0F, 0x0C, 0x01, 0x00, 0x0A,
  0x6D, 0x00, 0x00, 0x06, 0x06, 0x01, 0x00, 0x07, 0x06, 0x01, 0x00, 0x30,
  0x13, 0xC1, 0x00, 0x20, 0xA0, 0x10, 0x4E, 0xB9, 0x00, 0x20, 0xA1, 0x0E,
  0x51, 0xCA, 0xFF, 0xD8, 0x4C, 0xDF, 0x00, 0x06, 0x4E, 0x75, 0x48, 0xE7,
  0x80, 0x00, 0x20, 0x79, 0x00, 0x20, 0xA0, 0x12, 0x10, 0x18, 0x0C, 0x00,
  0x00, 0x00, 0x67, 0x00, 0x00, 0x14, 0x13, 0xC0, 0x00, 0x20, 0xA0, 0x10,
  0x4E, 0xB9, 0x00, 0x20, 0xA1, 0x0E, 0x4E, 0xF9, 0x00, 0x20, 0xA0, 0x80,
  0x4C, 0xDF, 0x00, 0x01, 0x4E, 0x75, 0x42, 0x79, 0x00, 0x20, 0xA0, 0x06,
  0x42, 0x79, 0x00, 0x20, 0xA0, 0x08, 0x22, 0x7C, 0x00, 0x30, 0x00, 0x00,
  0x12, 0x39, 0x00, 0x20, 0xA0, 0x0B, 0x16, 0x01, 0xE9, 0x1B, 0x86, 0x01,
  0x14, 0x03, 0xE1, 0x9A, 0x14, 0x03, 0xE1, 0x9A, 0x14, 0x03, 0xE1, 0x9A,
  0x14, 0x03, 0x22, 0x02, 0x20, 0x3C, 0x00, 0x00, 0x3F, 0xFF, 0x22, 0xC1,
  0x51, 0xC8, 0xFF, 0xFC, 0x4E, 0x75, 0x22, 0x7C, 0x00, 0x31, 0x00, 0x00,
  0x12, 0x39, 0x00, 0x20, 0xA0, 0x0B, 0x16, 0x01, 0xE9, 0x1B, 0x86, 0x01,
  0x14, 0x03, 0xE1, 0x9A, 0x14, 0x03, 0xE1, 0x9A, 0x14, 0x03, 0xE1, 0x9A,
  0x14, 0x03, 0x22, 0x02, 0x20, 0x3C, 0x00, 0x00, 0x3F, 0xFF, 0x22, 0xC1,
  0x51, 0xC8, 0xFF, 0xFC, 0x4E, 0x75, 0x48, 0xE7, 0xFE, 0xE0, 0x13, 0xF9,
  0x00, 0x20, 0xA0, 0x0A, 0x00, 0x60, 0x10, 0x1F, 0x13, 0xF9, 0x00, 0x20,
  0xA0, 0x0B, 0x00, 0x60, 0x10, 0x1D, 0x12, 0x39, 0x00, 0x20, 0xA0, 0x10,
  0x0C, 0x01, 0x00, 0x0D, 0x67, 0x00, 0x00, 0x1A, 0x0C, 0x01, 0x00, 0x0A,
  0x67, 0x00, 0x00, 0xCC, 0x30, 0x39, 0x00, 0x20, 0xA0, 0x06, 0x0C, 0x40,
  0x01, 0xF4, 0x6C, 0x00, 0x00, 0x04, 0x60, 0x20, 0x33, 0xFC, 0x00, 0x00,
  0x00, 0x20, 0xA0, 0x06, 0x30, 0x39, 0x00, 0x20, 0xA0, 0x08, 0x06, 0x40,
  0x00, 0x0B, 0x33, 0xC0, 0x00, 0x20, 0xA0, 0x08, 0x0C, 0x01, 0x00, 0x0D,
  0x67, 0x00, 0x00, 0x9C, 0x30, 0x39, 0x00, 0x20, 0xA0, 0x08, 0x0C, 0x40,
  0x00, 0xFB, 0x6C, 0x00, 0x00, 0x04, 0x60, 0x4E, 0x20, 0x7C, 0x00, 0x30,
  0x0B, 0x00, 0x22, 0x7C, 0x00, 0x30, 0x00, 0x00, 0x24, 0x3C, 0x00, 0x00,
  0x3D, 0x3F, 0x22, 0xD8, 0x51, 0xCA, 0xFF, 0xFC, 0x12, 0x39, 0x00, 0x20,
  0xA0, 0x0B, 0x16, 0x01, 0xE9, 0x1B, 0x86, 0x01, 0x14, 0x03, 0xE1, 0x9A,
  0x14, 0x03, 0xE1, 0x9A, 0x14, 0x03, 0xE1, 0x9A, 0x14, 0x03, 0x26, 0x02,
  0x20, 0x7C, 0x00, 0x30, 0xF5, 0x00, 0x24, 0x3C, 0x00, 0x00, 0x02, 0xBF,
  0x20, 0xC3, 0x51, 0xCA, 0xFF, 0xFC, 0x33, 0xFC, 0x00, 0xF3, 0x00, 0x20,
  0xA0, 0x08, 0x33, 0xF9, 0x00, 0x20, 0xA0, 0x06, 0x00, 0x60, 0x10, 0x18,
  0x33, 0xF9, 0x00, 0x20, 0xA0, 0x08, 0x00, 0x60, 0x10, 0x1A, 0x12, 0x39,
  0x00, 0x20, 0xA0, 0x10, 0x13, 0xC1, 0x00, 0x60, 0x06, 0x0B, 0x10, 0x39,
  0x00, 0x60, 0x10, 0x11, 0x02, 0x00, 0x00, 0x02, 0x66, 0xF4, 0x30, 0x39,
  0x00, 0x20, 0xA0, 0x06, 0x06, 0x40, 0x00, 0x0B, 0x33, 0xC0, 0x00, 0x20,
  0xA0, 0x06, 0x4C, 0xDF, 0x07, 0x7F, 0x4E, 0x75, 0x48, 0xE7, 0xF8, 0xC0,
  0x10, 0x3C, 0x00, 0x04, 0x4E, 0xB9, 0x00, 0x20, 0xA2, 0x90, 0x48, 0xE7,
  0x00, 0x80, 0x20, 0x7C, 0x00, 0xA0, 0x00, 0x0E, 0x20, 0xD9, 0x20, 0xD9,
  0x20, 0xD9, 0x4C, 0xDF, 0x01, 0x00, 0x10, 0x3C, 0x00, 0x03, 0x4E, 0xB9,
  0x00, 0x20, 0xA2, 0x90, 0x0C, 0x00, 0x00, 0x01, 0x67, 0x00, 0x00, 0x3A,
  0x10, 0x3C, 0x00, 0x05, 0x4E, 0xB9, 0x00, 0x20, 0xA2, 0x90, 0x0C, 0x00,
  0x00, 0x01, 0x67, 0x00, 0x00, 0x28, 0x0C, 0x44, 0x00, 0x00, 0x67, 0x00,
  0x00, 0x2E, 0x04, 0x44, 0x00, 0x01, 0x30, 0x04, 0x22, 0x7C, 0x00, 0xA0,
  0x10, 0x00, 0x10, 0xD9, 0x51, 0xCC, 0xFF, 0xFC, 0x0C, 0x40, 0x0F, 0xFF,
  0x67, 0xCE, 0x4E, 0xF9, 0x00, 0x20, 0xA2, 0x86, 0x4C, 0xDF, 0x03, 0x1F,
  0x10, 0x3C, 0x00, 0x01, 0x4E, 0xF9, 0x00, 0x20, 0xA2, 0x8E, 0x4C, 0xDF,
  0x03, 0x1F, 0x10, 0x3C, 0x00, 0x00, 0x4E, 0x75, 0x4E, 0xB9, 0x00, 0x20,
  0xA2, 0xD4, 0x33, 0xC0, 0x00, 0xA0, 0x00, 0x00, 0x23, 0xC1, 0x00, 0xA0,
  0x00, 0x02, 0x33, 0xC3, 0x00, 0xA0, 0x00, 0x0A, 0x4E, 0xB9, 0x00, 0x20,
  0xA2, 0xDE, 0x4E, 0xB9, 0x00, 0x20, 0xA2, 0xE8, 0x30, 0x39, 0x00, 0xA0,
  0x00, 0x00, 0x22, 0x39, 0x00, 0xA0, 0x00, 0x02, 0x24, 0x39, 0x00, 0xA0,
  0x00, 0x06, 0x36, 0x39, 0x00, 0xA0, 0x00, 0x0A, 0x38, 0x39, 0x00, 0xA0,
  0x00, 0x0C, 0x4E, 0x75, 0x13, 0xFC, 0x00, 0x01, 0x00, 0x60, 0x01, 0x01,
  0x4E, 0x75, 0x13, 0xFC, 0x00, 0x00, 0x00, 0x60, 0x01, 0x01, 0x4E, 0x75,
  0x48, 0xE7, 0x80, 0x00, 0x10, 0x39, 0x00, 0x60, 0x08, 0x03, 0x0C, 0x00,
  0x00, 0x00, 0x67, 0xF4, 0x10, 0x39, 0x00, 0x60, 0x08, 0x03, 0x0C, 0x00,
  0x00, 0x00, 0x66, 0xF4, 0x4C, 0xDF, 0x00, 0x01, 0x4E, 0x75, 0x13, 0xFC,
  0x00, 0xCC, 0x00, 0x60, 0x04, 0x01, 0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x22,
  0x13, 0xFC, 0x00, 0x00, 0x00, 0x60, 0x04, 0x01, 0x4E, 0x75, 0x48, 0xE7,
  0x08, 0x00, 0x28, 0x3C, 0x00, 0x00, 0x20, 0x00, 0x4E, 0x71, 0x51, 0xCC,
  0xFF, 0xFC, 0x4C, 0xDF, 0x00, 0x10, 0x4E, 0x75, 0x4E, 0xB9, 0x00, 0x20,
  0xA3, 0x22, 0x4E, 0xF9, 0x00, 0x20, 0xA3, 0x38, 0x4E, 0xF8, 0x00, 0x00,
  0x00, 0x39, 0x00, 0x08, 0x00, 0x60, 0x05, 0x01, 0x4E, 0x75, 0x02, 0x39,
  0x00, 0xF7, 0x00, 0x60, 0x05, 0x01, 0x4E, 0x75, 0x00, 0x39, 0x00, 0x08,
  0x00, 0x60, 0x05, 0x01, 0x48, 0xE7, 0x80, 0x00, 0x10, 0x3C, 0x00, 0xF9,
  0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x7E, 0x4C, 0xDF, 0x00, 0x01, 0x4E, 0xB9,
  0x00, 0x20, 0xA3, 0x7E, 0x4E, 0x75, 0x13, 0xC0, 0x00, 0x60, 0x03, 0x01,
  0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x22, 0x4E, 0x75, 0x56, 0x54, 0x45, 0x43,
  0x48, 0x20, 0x42, 0x6F, 0x6F, 0x74, 0x73, 0x74, 0x72, 0x61, 0x70, 0x20,
  0x2D, 0x20, 0x41, 0x4C, 0x45, 0x58, 0x41, 0x4E, 0x44, 0x52, 0x45, 0x40,
  0x42, 0x4F, 0x54, 0x5A, 0x55, 0x4E, 0x47, 0x2E, 0x46, 0x52, 0x0D, 0x0D,
  0x20, 0x2D, 0x3E, 0x20, 0x4D, 0x6F, 0x75, 0x6E, 0x74, 0x69, 0x6E, 0x67,
  0x20, 0x53, 0x44, 0x20, 0x63, 0x61, 0x72, 0x64, 0x20, 0x2E, 0x20, 0x2E,
  0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E, 0x20, 0x2E,
  0x00, 0x20, 0x2D, 0x3E, 0x20, 0x43, 0x6F, 0x70, 0x79, 0x69, 0x6E, 0x67,
  0x20, 0x50, 0x52, 0x4F, 0x47, 0x52, 0x41, 0x4D, 0x2E, 0x42, 0x49, 0x4E,
  0x20, 0x74, 0x6F, 0x20, 0x24, 0x32, 0x31, 0x30, 0x30, 0x30, 0x30, 0x20,
  0x2E, 0x00, 0x50, 0x52, 0x4F, 0x47, 0x52, 0x41, 0x4D, 0x2E, 0x42, 0x49,
  0x4E, 0x00, 0x4F, 0x4B, 0x0D, 0x0D, 0x00, 0x00, 0x45, 0x52, 0x52, 0x4F,
  0x52, 0x0D, 0x0D, 0x00, 0x00, 0x50, 0x72, 0x65, 0x73, 0x73, 0x20, 0x53,
  0x50, 0x41, 0x43, 0x45, 0x20, 0x74, 0x6F, 0x20, 0x72, 0x65, 0x73, 0x74,
  0x61, 0x72, 0x74, 0x2E, 0x0D, 0x00, 0x00, 0x0D, 0x00, 0xFF, 0x10, 0x3C,
  0x00, 0x00, 0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x5C, 0x4E, 0xB9, 0x00, 0x20,
  0xA0, 0xA2, 0x13, 0xFC, 0x00, 0x0A, 0x00, 0x60, 0x10, 0x07, 0x06, 0x79,
  0x00, 0x0B, 0x00, 0x20, 0xA0, 0x08, 0x23, 0xFC, 0x00, 0x20, 0xA3, 0x8C,
  0x00, 0x20, 0xA0, 0x12, 0x4E, 0xB9, 0x00, 0x20, 0xA0, 0x76, 0x4E, 0xB9,
  0x00, 0x20, 0xA5, 0x9C, 0x10, 0x3C, 0x00, 0x00, 0x4E, 0xB9, 0x00, 0x20,
  0xA2, 0x90, 0x10, 0x3C, 0x00, 0x02, 0x4E, 0xB9, 0x00, 0x20, 0xA2, 0x90,
  0x0C, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x18, 0x23, 0xFC, 0x00, 0x20,
  0xA4, 0x10, 0x00, 0x20, 0xA0, 0x12, 0x4E, 0xB9, 0x00, 0x20, 0xA0, 0x76,
  0x4E, 0xF9, 0x00, 0x20, 0xA5, 0x3E, 0x23, 0xFC, 0x00, 0x20, 0xA4, 0x0A,
  0x00, 0x20, 0xA0, 0x12, 0x4E, 0xB9, 0x00, 0x20, 0xA0, 0x76, 0x23, 0xFC,
  0x00, 0x20, 0xA3, 0xD9, 0x00, 0x20, 0xA0, 0x12, 0x4E, 0xB9, 0x00, 0x20,
  0xA0, 0x76, 0x20, 0x7C, 0x00, 0x21, 0x00, 0x00, 0x22, 0x7C, 0x00, 0x20,
  0xA3, 0xFE, 0x4E, 0xB9, 0x00, 0x20, 0xA2, 0x0C, 0x0C, 0x00, 0x00, 0x00,
  0x67, 0x00, 0x00, 0x18, 0x23, 0xFC, 0x00, 0x20, 0xA4, 0x10, 0x00, 0x20,
  0xA0, 0x12, 0x4E, 0xB9, 0x00, 0x20, 0xA0, 0x76, 0x4E, 0xF9, 0x00, 0x20,
  0xA5, 0x3E, 0x23, 0xFC, 0x00, 0x20, 0xA4, 0x0A, 0x00, 0x20, 0xA0, 0x12,
  0x4E, 0xB9, 0x00, 0x20, 0xA0, 0x76, 0x4E, 0xB9, 0x00, 0x20, 0xA5, 0x9C,
  0x4E, 0xB9, 0x00, 0x20, 0xA5, 0x9C, 0x10, 0x3C, 0x00, 0x04, 0x4E, 0xB9,
  0x00, 0x20, 0xA3, 0x5C, 0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x22, 0x4E, 0xB9,
  0x00, 0x20, 0xA3, 0x22, 0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x22, 0x4E, 0xB9,
  0x00, 0x20, 0xA3, 0x52, 0x4E, 0xB9, 0x00, 0x20, 0xA0, 0xA2, 0x4E, 0xB9,
  0x00, 0x21, 0x00, 0x00, 0x4E, 0xF9, 0x00, 0x20, 0xA4, 0x36, 0x23, 0xFC,
  0x00, 0x20, 0xA4, 0x19, 0x00, 0x20, 0xA0, 0x12, 0x4E, 0xB9, 0x00, 0x20,
  0xA0, 0x76, 0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x0A, 0x10, 0x3C, 0x00, 0x02,
  0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x5C, 0x4E, 0xB9, 0x00, 0x20, 0xA5, 0x7A,
  0x10, 0x3C, 0x00, 0x04, 0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x5C, 0x4E, 0xB9,
  0x00, 0x20, 0xA5, 0x7A, 0x4E, 0xF9, 0x00, 0x20, 0xA5, 0x54, 0x48, 0xE7,
  0x08, 0x00, 0x28, 0x3C, 0x00, 0x00, 0x20, 0x00, 0x30, 0x39, 0x00, 0x60,
  0x03, 0x00, 0x0C, 0x00, 0x00, 0x4B, 0x67, 0x00, 0xFE, 0xA6, 0x51, 0xCC,
  0xFF, 0xF0, 0x4C, 0xDF, 0x00, 0x10, 0x4E, 0x75, 0x24, 0x3C, 0x00, 0x00,
  0x00, 0x10, 0x4E, 0xB9, 0x00, 0x20, 0xA3, 0x22, 0x51, 0xCA, 0xFF, 0xF8,
  0x4E, 0x75
};

















// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
const int SD_ChipSelect = 53;


#define RAM_CE A7//A10-> A7    64
#define RAM_RW A6 //A9 -> A6    63
#define RAM_OE A5 //A8 -> A5    62
#define RAM_ADDR0 49
#define RAM_ADDR1 48
#define RAM_ADDR2 47
#define RAM_ADDR3 46
#define RAM_ADDR4 45
#define RAM_ADDR5 44
#define RAM_ADDR6 43
#define RAM_ADDR7 42
//#define RAM_ADDR8 53
//#define RAM_ADDR9 52
//#define RAM_ADDR10 51
//#define RAM_ADDR11 50
#define RAM_ADDR8 A8
#define RAM_ADDR9 A9
#define RAM_ADDR10 A10
#define RAM_ADDR11 A11

#define RAM_DAT0 22
#define RAM_DAT1 23
#define RAM_DAT2 24
#define RAM_DAT3 25
#define RAM_DAT4 26
#define RAM_DAT5 27
#define RAM_DAT6 28
#define RAM_DAT7 29

#define RAM_DAT8 37
#define RAM_DAT9 36
#define RAM_DAT10 35
#define RAM_DAT11 34
#define RAM_DAT12 33
#define RAM_DAT13 32
#define RAM_DAT14 31
#define RAM_DAT15 30
#define NOT_SYSTEMRESET 4
uint8_t BUFFER_LO[2048];
uint8_t BUFFER_HI[2048];
unsigned int i = 0;
unsigned int j = 0;
unsigned int k = 0;
unsigned long test = 0;
unsigned long test2 = 0;
unsigned char FRAM_STATUS = 0;
volatile unsigned char drapeau_semaphore = 0;
unsigned char PCramdisk_enabled = 0;

unsigned int compteur = 0;
unsigned char buffeur = 0;
unsigned char buffeur2 = 0;
unsigned int cmdstat = 0;
//unsigned char stat=0;
unsigned long longa = 0;
unsigned long longb = 0;
unsigned int worda = 0;
unsigned int wordb = 0;

char lefichier[13] = "FILENAME.XXX";
File dataFile;

unsigned char semaphore = 0;

uint8_t xLEN = 0;
void setup() {
  // Partie SEMAPHORE
  pinMode(2, OUTPUT); // ARDUINO -> VTECH : CARD 1 du Vtech
  digitalWrite(2, LOW); // Active le mode cartouche pour le Vtech
  pinMode(3, INPUT);  // VTECH -> ARDUINO D0 du // ($600101)
  // Partie Controle (Lien RESET du SYSTEME)
  pinMode(NOT_SYSTEMRESET, OUTPUT);
  //digitalWrite(NOT_SYSTEMRESET, LOW);
  //delay(200);
  digitalWrite(NOT_SYSTEMRESET, HIGH);


  //Serial.begin(9600);
  //Serial.begin(115200);
  Serial.begin(500000);
  //Serial.begin(1000000); // FASTER!!!!! (Fastest available on this platform)
  DDRA = 0x0;  /// DATA LO - INPUT
  DDRC = 0x0;  /// DATA HI - INPUT
  DDRL = 0xFF; PORTL = 0; /// ADDR LO - OUTPUT
  //DDRB = 0xFF;PORTB=0; /// ADDR HI - OUTPUT
  DDRK = 0XFF; PORTK = 0; /// ADDR HI - OUTPUT
  //DDRK = 0xFF;PORTK=0; /// CTRL    - OUTPUT
  DDRF = 0xFF; PORTF = 0; /// CTRL    - OUTPUT
  // Configuration de l'interruption pour la détection de fin de traitement coté VTECH.

  drapeau_semaphore = 0;
  attachInterrupt(digitalPinToInterrupt(3), INTERRUPTION_semaphore, FALLING);//RISING);

  init_bootloader(); // Envoie la le bootloader dans la SRAM
}

void INTERRUPTION_semaphore() {
  // Gestion de l'interruption du sémaphore.
  // TODO: Compléter l'interruption
  drapeau_semaphore = 1;
}


void BUFFER_to_SRAM(unsigned int datlen) {
  digitalWrite(RAM_OE, HIGH);
  digitalWrite(RAM_RW, LOW );
  digitalWrite(RAM_CE, HIGH);
  //DDRK=0xFF;
  //PORTK = B10111111;
  // Bus data en sortie
  DDRA = 0xFF;
  DDRC = 0xFF;

  for (i = 0; i <= datlen; i++) {
    // Configure les adresses
    PORTL = (i & 0xFF);
    //PORTB = ((i >> 8) & 0xFF);
    PORTK = ((i >> 8) & 0xFF);
    PORTA = BUFFER_LO[i];
    PORTC = BUFFER_HI[i];
    digitalWrite(RAM_CE, 0);
    digitalWrite(RAM_OE, 0);
    //OE=b0 RW=b1 CE=b2
    //PORTK = B00011111; // Baisse OE et CE
    //delayMicroseconds(1);
    //PORTK = B10111111; // Monte OE et CE
    digitalWrite(RAM_OE, 1);
    digitalWrite(RAM_CE, 1);
  }
}

void BUFFER_to_HISRAM() {
  digitalWrite(RAM_OE, HIGH);
  digitalWrite(RAM_RW, LOW );
  digitalWrite(RAM_CE, HIGH);
  //DDRK=0xFF;
  //PORTK = B10111111;
  // Bus data en sortie
  DDRA = 0xFF;
  DDRC = 0xFF;

  for (i = 2048; i <= 4095; i++) {
    j = i - 2048;
    // Configure les adresses
    PORTL = (i & 0xFF);
    //PORTB = ((i >> 8) & 0x0F);
    PORTK = ((i >> 8) & 0x0F);
    PORTA = BUFFER_LO[j];
    PORTC = BUFFER_HI[j];
    digitalWrite(RAM_CE, 0);
    digitalWrite(RAM_OE, 0);
    //OE=b0 RW=b1 CE=b2
    //PORTK = B00011111; // Baisse OE et CE
    //delayMicroseconds(1);
    //PORTK = B10111111; // Monte OE et CE
    digitalWrite(RAM_OE, 1);
    digitalWrite(RAM_CE, 1);
  }
  //Serial.write('*');
}

void SRAM_to_BUFFER(unsigned int datlen) {
  digitalWrite(RAM_OE, HIGH);
  digitalWrite(RAM_RW, HIGH);
  digitalWrite(RAM_CE, HIGH);
  //OE=b0 RW=b1 CE=b2
  //PORTK = B11011111; // OE=RW=CE= High
  // Bus data en input

  pinMode(RAM_DAT0, INPUT);
  pinMode(RAM_DAT1, INPUT);
  pinMode(RAM_DAT2, INPUT);
  pinMode(RAM_DAT3, INPUT);
  pinMode(RAM_DAT4, INPUT);
  pinMode(RAM_DAT5, INPUT);
  pinMode(RAM_DAT6, INPUT);
  pinMode(RAM_DAT7, INPUT);
  pinMode(RAM_DAT8, INPUT);
  pinMode(RAM_DAT9, INPUT);
  pinMode(RAM_DAT10, INPUT);
  pinMode(RAM_DAT11, INPUT);
  pinMode(RAM_DAT12, INPUT);
  pinMode(RAM_DAT13, INPUT);
  pinMode(RAM_DAT14, INPUT);
  pinMode(RAM_DAT15, INPUT);
  //DDRA = 0; PORTA = 0;
  //DDRC = 0; PORTC = 0;
  for (i = 0; i <= datlen; i++) {
    // Configure les adresses
    PORTL = (i & 0xFF);
    //PORTB = ((i >> 8) & 0xFF);
    PORTK = ((i >> 8) & 0xFF);
    digitalWrite(RAM_CE, LOW);
    digitalWrite(RAM_OE, 0);
    //OE=b0 RW=b1 CE=b2

    //PORTK = B01011111; // Baisse OE et CE

    //delayMicroseconds(2);
    BUFFER_LO[i] = PINA;
    BUFFER_HI[i] = PINC;
    delayMicroseconds(1);
    //PORTK = B11111111; // Monte OE et CE
    digitalWrite(RAM_OE, 1);
    digitalWrite(RAM_CE, HIGH);

  }
}

void HISRAM_to_BUFFER() {
  digitalWrite(RAM_OE, HIGH);
  digitalWrite(RAM_RW, HIGH);
  digitalWrite(RAM_CE, HIGH);
  //OE=b0 RW=b1 CE=b2
  //PORTK = B11011111; // OE=RW=CE= High
  // Bus data en input
  pinMode(RAM_DAT0, INPUT);
  pinMode(RAM_DAT1, INPUT);
  pinMode(RAM_DAT2, INPUT);
  pinMode(RAM_DAT3, INPUT);
  pinMode(RAM_DAT4, INPUT);
  pinMode(RAM_DAT5, INPUT);
  pinMode(RAM_DAT6, INPUT);
  pinMode(RAM_DAT7, INPUT);
  pinMode(RAM_DAT8, INPUT);
  pinMode(RAM_DAT9, INPUT);
  pinMode(RAM_DAT10, INPUT);
  pinMode(RAM_DAT11, INPUT);
  pinMode(RAM_DAT12, INPUT);
  pinMode(RAM_DAT13, INPUT);
  pinMode(RAM_DAT14, INPUT);
  pinMode(RAM_DAT15, INPUT);
  //DDRA = 0; PORTA = 0;
  //DDRC = 0; PORTC = 0;
  for (i = 2048; i <= 4095; i++) {
    // Configure les adresses
    j = i - 2048;
    PORTL = (i & 0xFF);
    //PORTB = ((i >> 8) & 0x0F);
    PORTK = ((i >> 8) & 0x0F);
    digitalWrite(RAM_CE, LOW);
    digitalWrite(RAM_OE, 0);
    //OE=b0 RW=b1 CE=b2

    //PORTK = B01011111; // Baisse OE et CE

    //delayMicroseconds(2);
    BUFFER_LO[j] = PINA;
    BUFFER_HI[j] = PINC;
    delayMicroseconds(1);
    //PORTK = B11111111; // Monte OE et CE
    digitalWrite(RAM_OE, 1);
    digitalWrite(RAM_CE, HIGH);

  }
  //Serial.write('%');
}

void UARTtoBUFFER() {
  k = 0;
  for (i = 0; i <= 127; i++) {
    while (Serial.available() != 32) {} // Attends le chunk de données
    for (j = 0; j <= 15; j++) {               // Je traite 32 mots
      BUFFER_HI[k] = Serial.read();
      BUFFER_LO[k] = Serial.read();
      k++;
    }
    Serial.write('!');               // Plus de données PLZ!
  }
}

void UARTtoBUFFER_HEADER() {
  k = 0;
  while (Serial.available() != 32) {} // Attends le chunk de données
  for (j = 0; j <= 15; j++) {               // Je traite 8 mots (16octets)
    BUFFER_HI[k] = Serial.read();
    BUFFER_LO[k] = Serial.read();
    k++;
  }
  //Serial.write('!');               // Done!
}

void BUFFERtoUART_HEADER() {
  for (i = 0; i <= 15; i++) {
    Serial.write(BUFFER_HI[i]);
    Serial.write(BUFFER_LO[i]);
  }
}

void BUFFERtoUART() {
  for (i = 0; i <= 2047; i++) {
    Serial.write(BUFFER_HI[i]);
    Serial.write(BUFFER_LO[i]);
  }
}

unsigned long BUFFER_to_long(unsigned int addrmem) {
  unsigned long temp = 0;
  unsigned long temp2 = 0;
  temp2 = BUFFER_LO[addrmem]; temp = temp + temp2; temp = (temp << 8);
  temp2 = BUFFER_HI[addrmem]; temp = temp + temp2; temp = (temp << 8);
  temp2 = BUFFER_LO[addrmem + 1]; temp = temp + temp2; temp = (temp << 8);
  temp2 = BUFFER_HI[addrmem + 1]; temp = temp + temp2;
  return temp;
}

unsigned int BUFFER_to_word(unsigned int addrmem) {
  unsigned int temp = 0;
  unsigned int temp2 = 0;
  temp2 = BUFFER_LO[addrmem]; temp = temp + temp2; temp = (temp << 8);
  temp2 = BUFFER_HI[addrmem]; temp = temp + temp2;
  return temp;
}

unsigned char BUFFER_to_byte(unsigned int addrmem) {
  unsigned int temp = 0;
  temp = addrmem;
  if (temp > 0) {
    temp = addrmem / 2;
  }

  if (addrmem % 2 == 0) {
    return BUFFER_LO[temp]; // PAIRE
  } else {
    return BUFFER_HI[temp]; // IMPAIRE
  }
}

void byte_to_BUFFER(unsigned int addrmem, unsigned char valeur) {
  unsigned int temp = 0;
  temp = addrmem;
  if (temp > 0) {
    temp = addrmem / 2;
  }

  if (addrmem % 2 == 0) {
    //return BUFFER_LO[temp]; // PAIRE
    BUFFER_LO[temp] = valeur;
  } else {
    //return BUFFER_HI[temp]; // IMPAIRE
    BUFFER_HI[temp] = valeur;
  }
}

void word_to_BUFFER(unsigned int addrmem, unsigned int valeur) {
  BUFFER_HI[addrmem] = (valeur & 0xFF); valeur = (valeur >> 8);
  BUFFER_LO[addrmem] = (valeur & 0xFF);
}

void long_to_BUFFER(unsigned int addrmem, unsigned long valeur) {
  unsigned long temp = 0;
  temp = (valeur & 0xFF); valeur = (valeur >> 8); BUFFER_HI[addrmem + 1] = (temp & 0xFF);
  temp = (valeur & 0xFF); valeur = (valeur >> 8); BUFFER_LO[addrmem + 1] = (temp & 0xFF);
  temp = (valeur & 0xFF); valeur = (valeur >> 8); BUFFER_HI[addrmem] = (temp & 0xFF);
  temp = (valeur & 0xFF); valeur = (valeur >> 8); BUFFER_LO[addrmem] = (temp & 0xFF);



  //  BUFFER_HI[addrmem+1]=(valeur & 0xFF);valeur=(valeur>>8);
  //  BUFFER_LO[addrmem+1]=(valeur & 0xFF);valeur=(valeur>>8);
  //  BUFFER_HI[addrmem]=(valeur & 0xFF);valeur=(valeur>>8);
  //  BUFFER_LO[addrmem]=(valeur & 0xFF);
}

void string_to_BUFFER() {
  for (int counti = 0; counti <= 13; counti++)
  {
    byte_to_BUFFER(counti + 14, lefichier[counti]);
  }
}

void BUFFER_to_string() {
  unsigned char temp = 0;
  for (temp = 0; temp <= 13; temp++)
  {
    lefichier[temp] = BUFFER_to_byte(temp + 14); //byte_to_BUFFER(temp+14,lefichier[temp]);
  }
  lefichier[13] = 0;
}

void init_bootloader() {
  digitalWrite(2, LOW); // Baisse le sémaphore ... (dans le doute...)
  //delay(2000); //attends un peu...
  for(compteur=0;compteur<=LDR_STAGE1_LEN;compteur++)
  {
    byte_to_BUFFER(compteur, pgm_read_byte_near(LDR_STAGE1+compteur));
  }
  BUFFER_to_SRAM(2048); //COMMIT les changements dans la banque BASSE
  for(compteur=0;compteur<=LDR_STAGE2_LEN;compteur++)
  {
    byte_to_BUFFER(compteur, pgm_read_byte_near(LDR_STAGE2+compteur));
  }
  BUFFER_to_HISRAM(); //COMMIT les changements dans la banque HAUTE
  delay(50);
  digitalWrite(NOT_SYSTEMRESET, LOW);
  delay(200);
  digitalWrite(NOT_SYSTEMRESET, HIGH);
  //delay(2000);
}












void init_bootloader_dbgtrace() {
  Serial.print("INIT_BOOTLDR");
  digitalWrite(NOT_SYSTEMRESET, LOW);
  delay(1000); //attends un peu...
  Serial.print("...COPY...");
  for(compteur=0;compteur<=LDR_STAGE1_LEN;compteur++)
  {
    byte_to_BUFFER(compteur, pgm_read_byte_near(LDR_STAGE1+compteur));
  }
  BUFFER_to_SRAM(2048); //COMMIT les changements dans la banque BASSE
  for(compteur=0;compteur<=LDR_STAGE2_LEN;compteur++)
  {
    byte_to_BUFFER(compteur, pgm_read_byte_near(LDR_STAGE2+compteur));
  }
  BUFFER_to_HISRAM(); //COMMIT les changements dans la banque HAUTE
  delay(50);
  /* A cet endroit, on devrait avoir la mémoire correctement programmé, mais pour une raison inconnue, le VTECH ne boot pas. . . */
  Serial.write(10);
  Serial.print("DLO");
  SRAM_to_BUFFER(2048);
  for(compteur=0;compteur<=2047;compteur++)
  {
    //buffeur=byte_to_BUFFER(compteur, pgm_read_byte_near(LDR_STAGE1+compteur)); // Lis un octet du LDR1
    Serial.print(BUFFER_to_byte(compteur),HEX);
    delay(4);
  }
  Serial.print("DHI");
  HISRAM_to_BUFFER();
  for(compteur=0;compteur<=2047;compteur++)
  {
    //buffeur=byte_to_BUFFER(compteur, pgm_read_byte_near(LDR_STAGE1+compteur)); // Lis un octet du LDR1
    Serial.print(BUFFER_to_byte(compteur),HEX);
    delay(4);
  }

  Serial.print("***END OF DUMP***");
  digitalWrite(NOT_SYSTEMRESET, HIGH);
  while(1){} // SOFTLOCK
  delay(50);
  digitalWrite(NOT_SYSTEMRESET, LOW);
  delay(200);
  digitalWrite(NOT_SYSTEMRESET, HIGH);
}

void loop() {
  if (PCramdisk_enabled == 0) {
    if (drapeau_semaphore == 1) { // SOUS-ROUTINE FASTRAM
      // ----------------------------------- DEBUT DE L'INTERUPTION STANDALONE MODE *CARTE SD* --------------------------------------------------------------------
      drapeau_semaphore = 0; // BAISSE LE DRAPEAU!
      digitalWrite(2, HIGH); // Active le sémaphore de l'arduino -> VTECH
      SRAM_to_BUFFER(16);   // Télécharge l'entete de la banque LO vers le buffer.

      cmdstat = BUFFER_to_word(0);
      cmdstat = (cmdstat & 0xFF); // Ne récupère que la partie basse....
      longa = BUFFER_to_long(1); // MOT 1 LOHI+ MOT 2 LOHI
      longb = BUFFER_to_long(3); // MOT 3 LOHI+ MOT 4 LOHI
      worda = BUFFER_to_word(5); // MOT 5 LOHI
      wordb = BUFFER_to_word(6); // MOT 6 LOHI
      if (cmdstat == 0) { // COMMANDE 0 : Ne fait RIEN. N'ecris pas en mémoire. Réponds par le semaphore.
        delay(10);
      }
      if (cmdstat == 1) { // COMMANDE 1 : Interroge l'Arduino. Renvoie son status dans LONGA et CMDSTAT
        //long_to_BUFFER(1, 0xABBACDDC); // LONGA
        //long_to_BUFFER(3, 0xBEEFDEAD); // LONGB
        //word_to_BUFFER(5, 0x1234);     // WORDA
        //word_to_BUFFER(6, 0x89AB);     // WORDB
        //string_to_BUFFER();
        word_to_BUFFER(0, 0x0); // VERSION 0 !
        long_to_BUFFER(1, 0xCAFEDEAD);
        BUFFER_to_SRAM(16);    // Envoie les changements - COMMIT
      }
      if (cmdstat == 2) { // COMMANDE 2 : Initialise la carte SD. Renvoie le status dans CMDSTAT.
        if (!SD.begin(SD_ChipSelect)) {
          word_to_BUFFER(0, 1); // FAIL
        } else {
          word_to_BUFFER(0, 0); // SD Card OK
        }
        BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
      }
      if (cmdstat == 3) { // COMMANDE 3 : Ouvre un fichier depuis la carte SD. Renvoie le résultat dans CMDSTAT
        BUFFER_to_string();
        if(dataFile){
          dataFile.close();
        }
        if (worda == 0x42) { // Ouvre le fichier en ecriture ? (il est crée si il n'existe pas)
          dataFile = SD.open(lefichier, FILE_WRITE);
        } else {
          dataFile = SD.open(lefichier, FILE_READ);
          Serial.print(lefichier);
        }
        if (!dataFile) {
          word_to_BUFFER(0, 1); // FAIL
        } else {
          word_to_BUFFER(0, 0); // OK
        }
        BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
      }
      if (cmdstat == 4) { // COMMANDE 4 : Ferme un fichier. Renvoie systématiquement 0 dans CMDSTAT
        if(dataFile){
          dataFile.close();
        }
        word_to_BUFFER(0, 0); // OK
        BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
      }
      if (cmdstat == 5) { // COMMANDE 5 : Lis un fichier depuis la carte SD. Taille des données à lire est dans WORDA. Renvoie dans WORDB le nombre de données lues. CMDSTAT est changé si il ya un stress.
        if (dataFile) {
          for(compteur=0;compteur<=4095;compteur++) { // TODO : Il y a (VRAIMENT) plus efficace comme méthode...!
            if(dataFile.available()){
              buffeur=dataFile.read();//buffeur, 1);
              //Serial.write(buffeur2);
              //buffeur='A';
              byte_to_BUFFER(compteur, buffeur);
              
            } else {
              break; // Quitte la boucle
            }
          }
          BUFFER_to_HISRAM();
          word_to_BUFFER(0, 0);    // OK
          word_to_BUFFER(6, compteur); // WORDB - Le buffer HI est plein / Quelques données lues (voir compteur)
          BUFFER_to_SRAM(16);      // Envoie les changements - COMMIT
        } else {
          word_to_BUFFER(0, 1); // FAIL
          word_to_BUFFER(6, 0); // WORDB - Aucune donnée lue.
          BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
        }
      }


      //Serial.print("END!");
      digitalWrite(2, LOW); // A cet endroit, l'adruino devrait avoir fini de traiter l'interruption.
    }
    // ----------------------------------- FIN DE L'INTERUPTION STANDALONE MODE *CARTE SD* -----------------------------------------------------------------------
  } else {
    // ----------------------------------- DEBUT DE L'INTERUPTION PCRAMDISK MODE *PORT SERIE* --------------------------------------------------------------------
    if (drapeau_semaphore == 1) { // SOUS-ROUTINE FASTRAM
      drapeau_semaphore = 0;      // BAISSE LE DRAPEAU!
      digitalWrite(2, HIGH);      // Active le sémaphore de l'arduino -> VTECH
      SRAM_to_BUFFER(16);         // Télécharge l'entete de la banque LO vers le buffer.
      
      cmdstat = BUFFER_to_word(0);// Récupère l'instruction
      cmdstat = (cmdstat & 0xFF); // Ne récupère que la partie basse....

      if (cmdstat==6) {           // (API) Ecriture vers un fichier
        Serial.write('D');          // """'D'ouble""" interruption !
        BUFFERtoUART_HEADER();      // Envoi de l'entête au format binaire +
        HISRAM_to_BUFFER();
        BUFFERtoUART();             // Envoi du buffer HI vers l'UART (4128 octets au total)
      } else {
        Serial.write('I');          // 'I'nterruption !
        BUFFERtoUART_HEADER();      // Envoi de l'entête au format binaire...
      }

      while(!Serial.available()){}// ...attends une réponse de l'ordinateur.
      switch (Serial.read()) {
        case 'X' :                // Récupère que l'entête (32 octets)
          UARTtoBUFFER_HEADER();  // Télécharge 32 octets de l'UART vers le BUFFER
          BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
          break;
        case 'Y' :                // Récupère l'entête + buffer HI (4128 octets)
          UARTtoBUFFER_HEADER();  // Télécharge 32 octets de l'UART vers le BUFFER
          BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
          Serial.write('i');      // J'ai fini de COMMIT, commence l'envoi du stream!
          UARTtoBUFFER();         // Télécharge 4096 octets de l'UART vers le BUFFER
          BUFFER_to_HISRAM();     // Envoi des données - COMMIT
          break;          
        case 'Z' :                // Récupère que le buffer HI (4096 octets) INUTILISE
          break;          
        default :                 // OPCode inconnu ? Fait chier, FAIL et ERROR générique logiciel
          Serial.write('F');      // Indique quand même que l'Arduino et le PC à FAIL misérablement...
          word_to_BUFFER(0, 1);   // FAIL
          BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
          break; 
      }

      /*cmdstat = BUFFER_to_word(0);
      cmdstat = (cmdstat & 0xFF); // Ne récupère que la partie basse....
      longa = BUFFER_to_long(1); // MOT 1 LOHI+ MOT 2 LOHI
      longb = BUFFER_to_long(3); // MOT 3 LOHI+ MOT 4 LOHI
      worda = BUFFER_to_word(5); // MOT 5 LOHI
      wordb = BUFFER_to_word(6); // MOT 6 LOHI
      if (cmdstat == 0) { // COMMANDE 0 : Ne fait RIEN. N'ecris pas en mémoire. Réponds par le semaphore.
        delay(10);
      }
      if (cmdstat == 1) { // COMMANDE 1 : Interroge l'Arduino. Renvoie son status dans LONGA et CMDSTAT
        word_to_BUFFER(0, 0x0); // VERSION 0 !
        long_to_BUFFER(1, 0xCAFEDEAD);
        BUFFER_to_SRAM(16);    // Envoie les changements - COMMIT
      }
      if (cmdstat == 2) { // COMMANDE 2 : Initialise le lien série<-->PC. Renvoie le status dans CMDSTAT.
        if (!SD.begin(SD_ChipSelect)) {
          word_to_BUFFER(0, 1); // FAIL
        } else {
          word_to_BUFFER(0, 0); // SD Card OK
        }
        BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
      }
      if (cmdstat == 3) { // COMMANDE 3 : Ouvre un fichier depuis la carte SD. Renvoie le résultat dans CMDSTAT
        BUFFER_to_string();
        if(dataFile){
          dataFile.close();
        }
        if (worda == 0x42) { // Ouvre le fichier en ecriture ? (il est crée si il n'existe pas)
          dataFile = SD.open(lefichier, FILE_WRITE);
        } else {
          dataFile = SD.open(lefichier, FILE_READ);
          Serial.print(lefichier);
        }
        if (!dataFile) {
          word_to_BUFFER(0, 1); // FAIL
        } else {
          word_to_BUFFER(0, 0); // OK
        }
        BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
      }
      if (cmdstat == 4) { // COMMANDE 4 : Ferme un fichier. Renvoie systématiquement 0 dans CMDSTAT
        if(dataFile){
          dataFile.close();
        }
        word_to_BUFFER(0, 0); // OK
        BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
      }
      if (cmdstat == 5) { // COMMANDE 5 : Lis un fichier depuis la carte SD. Taille des données à lire est dans WORDA. Renvoie dans WORDB le nombre de données lues. CMDSTAT est changé si il ya un stress.
        if (dataFile) {
          for(compteur=0;compteur<=4095;compteur++) { // TODO : Il y a (VRAIMENT) plus efficace comme méthode...!
            if(dataFile.available()){
              buffeur=dataFile.read();//buffeur, 1);
              //Serial.write(buffeur2);
              //buffeur='A';
              byte_to_BUFFER(compteur, buffeur);
              
            } else {
              break; // Quitte la boucle
            }
          }
          BUFFER_to_HISRAM();
          word_to_BUFFER(0, 0);    // OK
          word_to_BUFFER(6, compteur); // WORDB - Le buffer HI est plein / Quelques données lues (voir compteur)
          BUFFER_to_SRAM(16);      // Envoie les changements - COMMIT
        } else {
          word_to_BUFFER(0, 1); // FAIL
          word_to_BUFFER(6, 0); // WORDB - Aucune donnée lue.
          BUFFER_to_SRAM(16);     // Envoie les changements - COMMIT
        }
      }


      Serial.print("END!");*/
      digitalWrite(2, LOW); // A cet endroit, l'adruino devrait avoir fini de traiter l'interruption.
      // ----------------------------------- FIN DE L'INTERUPTION PCRAMDISK MODE *PORT SERIE* --------------------------------------------------------------------
    }
  }
    
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FIN DE LA GESTION D'INTERRUPTION LOGICIEL ARDUINO<--->VTECH ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CI-DESSOUS SE TROUVE LE CODE POUR PCRAMDISK ; PERMETTANT DE SE PASSER DE CARTE SD ~~~~~~~~~~

  if (Serial.available() > 0) {
    switch (Serial.read()) {
      case 'A' :      // 'A'ctive le mode PCramdisk
        PCramdisk_enabled = 1;
        //init_bootloader_dbgtrace(); // Envoie le bootloader dans la SRAM+reset du VTECH
        init_bootloader();
        Serial.write('A');
        break;
      case 'a' :      // des'a'ctive le mode PCramdisk
        PCramdisk_enabled = 0;
        Serial.write('a');
        break;
      default :       // OPCode inconnu ? OSEF
        break; 
    }
  }



// ~~~~~~~~~~~~~LE CODE **CI-DESSOUS** APPARTIENT AU MODE SERIE V1 - QUI PERMET AU PC(MAITRE) D'INTERAGIR AVEC LA SRAM DIRECTEMENT VIA L'ARDUINO(ESCLAVE) ~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~ CET PARTIE EST ABANDONNEE AU PROFIT D'UN MODE OU L'ARDUINO EST MAITRE DE LA COMMUNICATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /*if (Serial.available() > 0) {
    switch (Serial.read()) {
      case 'F' :           // Active le mode FASTRAM!
        FRAM_STATUS = 1;
        break;
      case 'f' :           // desActive le mode FASTRAM!
        FRAM_STATUS = 0;
        break;
      case 'i' :           // UART to BUFFER
        UARTtoBUFFER();
        break;
      case 'o' :           // BUFFER to UART
        BUFFERtoUART();
        break;
      case '?' :           // Question ; BONJOUR!
        Serial.write('$'); // Réponse  ; Salut!
        break;
      case '>' :           // Copie le BUFFER dans la SRAM
        if (semaphore == 1) {
          while (digitalRead(3) == 1) {} //Attends que le Vtech donne la main
        }
        digitalWrite(2, HIGH); // Je prend la main sur la mémoire
        BUFFER_to_SRAM(2047);
        Serial.write('>');
        digitalWrite(2, LOW); // C'est bon
        break;
      case '*' :           // Copie le BUFFER dans la SRAM haute
        if (semaphore == 1) {
          while (digitalRead(3) == 1) {} //Attends que le Vtech donne la main
        }
        digitalWrite(2, HIGH); // Je prend la main sur la mémoire
        BUFFER_to_HISRAM();
        digitalWrite(2, LOW); // C'est bon
        break;
      case '%' :           // Copie la SRAM haute vers le buffer
        if (semaphore == 1) {
          while (digitalRead(3) == 1) {} //Attends que le Vtech donne la main
        }
        digitalWrite(2, HIGH); // Je prend la main sur la mémoire
        HISRAM_to_BUFFER();
        digitalWrite(2, LOW); // C'est bon
        break;
      case '<' :           // Copie la SRAM dans le BUFFER
        if (semaphore == 1) {
          while (digitalRead(3) == 1) {} //Attends que le Vtech donne la main
        }
        digitalWrite(2, HIGH); // Je prend la main sur la mémoire
        SRAM_to_BUFFER(2047);
        Serial.write('<');
        digitalWrite(2, LOW); // C'est bon
        break;
      case 'S' :      //Active l'utilisation de semaphores
        semaphore = 1;
        break;
      case 's' :      //Desactive l'utilisation de semaphores
        semaphore = 0;
        break;
      case 'X' :      //Ecris 16 octets du buffer vers la SRAM
        if (semaphore == 1) {
          while (digitalRead(3) == 1) {} //Attends que le Vtech donne la main
        }
        digitalWrite(2, HIGH); // Je prend la main sur la mémoire
        BUFFER_to_SRAM(15);
        Serial.write('>');
        digitalWrite(2, LOW); // C'est bon
        break;
      case 'x' :      //Lis 16 octets de la SRAM vers le buffer
        if (semaphore == 1) {
          while (digitalRead(3) == 1) {} //Attends que le Vtech donne la main
        }
        digitalWrite(2, HIGH); // Je prend la main sur la mémoire
        SRAM_to_BUFFER(15);
        Serial.write('<');
        digitalWrite(2, LOW); // C'est bon
        break;
      case 'Y' :      //Ecris 16 octets de l'UART vers le buffer
        UARTtoBUFFER_16bytes();
        break;
      case 'y' :      //Lis 16 octets du BUFFER vers l'UART
        BUFFERtoUART_16bytes();
        break;
      case 'r' :      //Déclanche la réinitialisation logiciel du Vtech
        digitalWrite(NOT_SYSTEMRESET, LOW);
        delay(200);
        digitalWrite(NOT_SYSTEMRESET, HIGH);
        break;
      case 'z' :      // Status (DEBUG)
        // 1. Lis 64 octets de la FASTRAM
        if (semaphore == 1) {
          while (digitalRead(3) == 1) {} //Attends que le Vtech donne la main
        }
        digitalWrite(2, HIGH); // Je prend la main sur la mémoire
        SRAM_to_BUFFER(32);
        digitalWrite(2, LOW); // C'est bon
        // 2. Déduire la valeur à @0

        //test2=BUFFER_to_long(0);//BUFFER_to_long(0);
        test2 = BUFFER_to_byte(0);
        Serial.print(test2, HEX);
        Serial.print('-');
        test2 = BUFFER_to_byte(1);
        Serial.print(test2, HEX);
        Serial.print('-');
        test2 = BUFFER_to_byte(2);
        Serial.print(test2, HEX);
        Serial.print('-');
        test2 = BUFFER_to_byte(3);
        Serial.print(test2, HEX);
        Serial.print('-');
        Serial.write(0x00);
        break;

      default :       // Un truc à faire ? GLANDE!
        break;
    }
  }*/
}
