/*
 This code is TFTLCD Library Example
*/
#include <Adafruit_GFX.h>       
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h> 
//#include <MCUFRIEND_kbv.h>
#include <SD.h>
#include <SPI.h>
#define YP A1  
#define XM A2  
#define YM 7   
#define XP 6   
#define TS_MINX 880
#define TS_MINY 120
#define TS_MAXX 110
#define TS_MAXY 890
//MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define SD_CS 10 
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
  
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4);
#define BOXSIZE 30
int PENRADIUS ;
int oldcolor, currentcolor;
void setup()
{
  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(SD_CS)) {
    Serial.println(F("failed!"));
   return;
 }
  bmpDraw("pic.bmp", 0, 0);
  //delay(1000);
    //tft.fillScreen(WHITE);
   tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
  tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
  tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
  tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
  tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, WHITE);
    tft.fillRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = RED;
 #define MINPRESSURE 10
#define MAXPRESSURE 1000
  pinMode(13, OUTPUT);
}

void loop()
{
 digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
 
   pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
 
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
 
    
    if (p.y < (TS_MINY-5)) {
      Serial.println("erase");
 
      tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
    }
    
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MAXY, TS_MINY, tft.height(), 0); 
    if (p.y < BOXSIZE) {
       oldcolor = currentcolor;
 
       if (p.x < BOXSIZE) { 
         currentcolor = RED; 
         tft.drawRect(0, 0, BOXSIZE, BOXSIZE, RED);
       } else if (p.x < BOXSIZE*2) {
         currentcolor = YELLOW;//PENRADIUS=1;
         tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, RED);
       } else if (p.x < BOXSIZE*3) {
         currentcolor = GREEN;//PENRADIUS=2;
         tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, RED);
       } else if (p.x < BOXSIZE*4) {
         currentcolor = CYAN;//PENRADIUS=3;
         tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, RED);
       } else if (p.x < BOXSIZE*5) {
         currentcolor = BLUE;//PENRADIUS=4;
         tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, RED);
       } else if (p.x < BOXSIZE*6) {
         currentcolor = MAGENTA;//PENRADIUS=6;
         tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, RED);         
       } else if (p.x < BOXSIZE*7) {
         currentcolor = WHITE;
         tft.drawRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, RED);
       } else if (p.x < BOXSIZE*8) {
         currentcolor = BLACK;
         tft.drawRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, RED);
       } 
      // else if (p.x < BOXSIZE*7) { currentcolor = MAGENTA; tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, RED); } 
       if (oldcolor != currentcolor) { if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED); if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW); if (oldcolor == GREEN) tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN); if (oldcolor == CYAN) tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN); if (oldcolor == BLUE) tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE); if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);if (oldcolor == WHITE) tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, WHITE);if (oldcolor == BLACK) tft.fillRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, BLACK); } } if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
      tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
    }
  }
}


#define BUFFPIXEL 20
void bmpDraw(char *filename, int x, int y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');
  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.println(F("File not found"));
    return;
  }
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.println(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed
        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);
         rowSize = (bmpWidth * 3 + 3) & ~3;
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;
       tft.setAddrWindow(x, y, x+w-1, y+h-1);
        for (row=0; row<h; row++) { // For each scanline...
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each column...
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              if(lcdidx > 0) {
                tft.pushColors(lcdbuffer, lcdidx, first);
                lcdidx = 0;
                first  = false;
              }
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = tft.color565(r,g,b);
          } // end pixel
        } // end scanline
        // Write any remaining data to LCD
        if(lcdidx > 0) {
          tft.pushColors(lcdbuffer, lcdidx, first);
        } 
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}
uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

