/*
 * SSD1306.h
 *
 *  Created on: Feb 4, 2020
 *      Author: ajose
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#ifndef SSD1306_H_
#define SSD1306_H_

#define SSD1306_SADDR1   0x78
#define SSD1306_SADDR2   0x7A    //Requires resistor (SA0) population change
#define SSD1306_64x128_BUFSIZE     1025    //1024 bytes plus first 0x40 byte indicating OLED data

#define SET_MEMADDR_MODE              0x20
#define MEMADDR_MODE_HORIZONTAL       0x00
#define SET_COL_ADDR                  0x21
#define SET_PAGE_ADDR                 0x22
#define SET_MULTIPLEX_RATIO           0xA8
#define SET_DISPLAY_OFFSET            0xD3
#define SET_DISPLAY_START_LINE        0x40
#define SET_SEG_REMAP                 0xA1
#define SET_COM_DIR_REMAP             0xC8
#define SET_COM_HWCFG                 0xDA
#define SET_CONTRAST                  0x81
#define SET_NORMAL_DISP               0xA6
#define SET_INVERSE_DISP              0xA7
#define CHARGE_PUMP_SETTING           0x8D
#define CHARGE_PUMP_ON                0x14

#define DISP_OFF                      0xAE
#define DISP_ON                       0xAF

typedef struct __attribute__ ((__packed__))
{
    uint8_t sAddr;
    void (*i2c_write_ptr)(uint8_t sAddr, uint8_t *pData, uint16_t len);
    uint8_t dispBufs[2][SSD1306_64x128_BUFSIZE];
    uint8_t *pFrontBuf;   //Screen update pointer swapped when writing out a new frame
    uint8_t *pBackBuf;

} SSD1306_I2c_Inst_t;


#define NUM_CHARS_ONDISPLAY_MAX     128
typedef struct __attribute__ ((__packed__))
{
    uint8_t cursorPosInArray;
    uint8_t characterMemory[NUM_CHARS_ONDISPLAY_MAX];

} SSD1306_TypeModeCtx_t;


void SSD1306_Write_Cmd(uint8_t cmd);
void SSD1306_Write_Cmd2(uint8_t cmd1, uint8_t cmd2);
void SSD1306_Write_Cmd3(uint8_t cmd1, uint8_t cmd2, uint8_t cmd3);
void SSD1306_Write_Data(uint8_t *pData, uint16_t len);
void SSD1306_ClearBackBuffer();
void SSD1306_UpdateScreen();
unsigned short GetBufIndexFromCoords(uint8_t x, uint8_t y);
void SSD1306_SetPixel(uint8_t x, uint8_t y);
void SSD1306_ClearPixel(uint8_t x, uint8_t y);
void SSD1306_TogglePixel(uint8_t x, uint8_t y);
void SSD1306_SetBackBufByte(uint16_t bufIdx, uint8_t byte);
void SSD1306_DrawLine(int x0, int y0, int x1, int y1);
void SSD1306_DrawRectangle(uint8_t pos_x, uint8_t pos_y, uint8_t width, uint8_t height);
void SSD1306_DrawFilledRectangle(uint8_t pos_x, uint8_t pos_y, uint8_t width, uint8_t height);
void SSD1306_DrawAsciiChar(uint8_t c, uint8_t pos_x, uint8_t pos_y);
void SSD1306_TypeModeSetCursor(uint8_t pos_x, uint8_t pos_y);
void SSD1306_TypeModeTypeCh(uint8_t c);
void SSD1306_Printf(const char *format, ...);
void SSD1306_SwapVramBufs();
int SSD1306_Oled_Init(uint8_t sAddr, void (*i2c_write_ptr)(uint8_t sAddr, uint8_t *pData, uint16_t len));



#endif /* SSD1306_H_ */
