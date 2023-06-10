/*
Personal R&D June8, 2023
Tested with Driver 9320 & 9341
Recommended library Adafruit
Arduino Nano ( Atmega 328p ) + 3.2 (OR 2.4 ) Inch Tft Lcd Display Shield Touch Screen with SD Card (320 * 240 pixel)
just Ability to read from SD card
Type file .BMP ( for example 1.bmp - 2.bmp - 3.bmp -...)
*/
#include <Adafruit_GFX.h>    // Core graphics library
//#include <MCUFRIEND_kbv.h>
#include <Adafruit_TFTLCD.h>
//MCUFRIEND_kbv tft;
#include <TouchScreen.h> 
#include <SD.h>
#include <SPI.h>
#define YP A1  
#define XM A2  
#define YM 7   
#define XP 6   
#define TS_MINX 885                     
#define TS_MINY 890                       
#define TS_MAXX 105                      
#define TS_MAXY  100                   
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 2);
#define LCD_RESET A4
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define SD_CS 10
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define BACKLIGHT A5
bool flag=1; 
bool cb=0; 
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4);
#define BOXSIZE 14
int b=1;
int PENRADIUS ;
int oldcolor, currentcolor,oldPENRADIUS;
/*****************************************************************************************************/
  String filename;
  String filenamesave;  
  byte fileindex =1;
  byte fc;
  /*****************************************************************************************************/
void setup()
{
 // fc = filecount();
pinMode(A5, OUTPUT);
digitalWrite(A5,HIGH);

 //Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
//Serial.println(identifier, HEX);
 tft.begin(0x9341);//Driver id
//  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(SD_CS)) {
    return;
  }

//******************************************************************************************            
  currentcolor = RED;
 #define MINPRESSURE 1
#define MAXPRESSURE 1000
}
/**************************************************************************************************************************************************/
void loop(){  
if(flag==1){
tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, WHITE);
tft.fillRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, BLACK);
tft.fillRect(BOXSIZE*8, 0, BOXSIZE, BOXSIZE, WHITE);tft.fillRect(BOXSIZE*8, (BOXSIZE/2)-(BOXSIZE/40), BOXSIZE, BOXSIZE/8, BLUE);
tft.fillRect(BOXSIZE*9, 0, BOXSIZE, BOXSIZE, WHITE);tft.fillRect(BOXSIZE*9, (BOXSIZE/2)-(BOXSIZE/12), BOXSIZE, BOXSIZE/4, BLUE);
tft.fillRect(BOXSIZE*10, 0, BOXSIZE, BOXSIZE, WHITE);tft.fillRect(BOXSIZE*10, (BOXSIZE/2)-(BOXSIZE/5), BOXSIZE, BOXSIZE/2.5, BLUE);
tft.fillRect(BOXSIZE*11, 0, BOXSIZE, BOXSIZE, WHITE);tft.fillRect(BOXSIZE*11,(BOXSIZE/2)-(BOXSIZE/3), BOXSIZE, BOXSIZE/1.5, BLUE);
tft.fillRect(BOXSIZE*12, 0, BOXSIZE, BOXSIZE, WHITE);
tft.fillRect(BOXSIZE*13, 0, BOXSIZE, BOXSIZE, BLACK);
tft.fillRect(BOXSIZE*14, 0, BOXSIZE, BOXSIZE, WHITE);
tft.fillRect(BOXSIZE*15, 0, BOXSIZE, BOXSIZE, WHITE);
tft.fillRect(BOXSIZE*16, 0, BOXSIZE, BOXSIZE, WHITE);
tft.setCursor(200, 2);tft.setTextColor(BLACK);tft.setTextSize(1); tft.println("P");
tft.setCursor(186, 2);tft.setTextColor(WHITE);tft.setTextSize(1); tft.println("B");
tft.setCursor(172, 2);tft.setTextColor(BLACK);tft.setTextSize(1); tft.println("W");
tft.setCursor(214, 2);tft.setTextColor(BLACK);tft.setTextSize(1); tft.println("S");
tft.setCursor(228, 2);tft.setTextColor(BLACK);tft.setTextSize(1); tft.println("L");  
}flag=0; 

  TSPoint p = ts.getPoint();

 
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
 
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    p.x = map(p.x, TS_MINX, TS_MAXX,0, tft.width());
    p.y = map(p.y, TS_MAXY, TS_MINY,0, tft.height()); 
///----------------------------------------------------------------------------------------------------------
    if ( p.y < -10) {
  if(cb==0){
  digitalWrite(A5, LOW);
  cb=1;
  delay(1000);
 }
  else if(cb==1){
  digitalWrite(A5,HIGH);
  cb=0;
  delay(1000);
   }
 }
///-----------------------------------------------------------------------------------------------------------    
    if ( p.y < 8 && p.y > -5) {
       oldcolor = currentcolor;
       oldPENRADIUS = PENRADIUS;
       if (p.x < BOXSIZE) { 
         currentcolor = RED;
         tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
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
       else if (p.x < BOXSIZE*9) {
         PENRADIUS=0;
         tft.drawRect(BOXSIZE*8, 0, BOXSIZE, BOXSIZE, RED);
       //  tft.fillRect(BOXSIZE*8, 0, BOXSIZE/8, BOXSIZE, BLUE);
       } 
       else if (p.x < BOXSIZE*10) {
         PENRADIUS=1;
         tft.drawRect(BOXSIZE*9, 0, BOXSIZE, BOXSIZE, RED);
         //tft.fillRect(BOXSIZE*9, 0, BOXSIZE/6, BOXSIZE, BLUE);
       } 
       else if (p.x < BOXSIZE*11) {
         PENRADIUS=2;
         tft.drawRect(BOXSIZE*10, 0, BOXSIZE, BOXSIZE, RED);
        // tft.fillRect(BOXSIZE*10, 0, BOXSIZE/4, BOXSIZE, BLUE);
       } 
       else if (p.x < BOXSIZE*12) {
         PENRADIUS=3;
         tft.drawRect(BOXSIZE*11, 0, BOXSIZE, BOXSIZE, RED);
         //tft.fillRect(BOXSIZE*11, 0, BOXSIZE/2, BOXSIZE, BLUE);
       }          
          else if (p.x < BOXSIZE*13) {
            tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, WHITE);
       }
          else if (p.x < BOXSIZE*14) {
            tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
       }  else if (p.x < BOXSIZE*15) {
            filename= getFileName(fileindex);
            bmpDraw(0, 14);
       }  else if (p.x < BOXSIZE*16) {
        filenamesave=filename;
       }  else if (p.x < BOXSIZE*17) {
       filename =filenamesave;
        bmpDraw(0, 14);
       } 
       
       if (oldPENRADIUS != PENRADIUS) { if (oldPENRADIUS == 0) tft.fillRect(BOXSIZE*8, 0, BOXSIZE, BOXSIZE, WHITE);tft.fillRect(BOXSIZE*8, (BOXSIZE/2)-(BOXSIZE/40), BOXSIZE, BOXSIZE/8, BLUE);if (oldPENRADIUS == 1) tft.fillRect(BOXSIZE*9, 0, BOXSIZE, BOXSIZE, WHITE);tft.fillRect(BOXSIZE*9, (BOXSIZE/2)-(BOXSIZE/12), BOXSIZE, BOXSIZE/4, BLUE);if (oldPENRADIUS == 2) tft.fillRect(BOXSIZE*10, 0, BOXSIZE, BOXSIZE, WHITE);tft.fillRect(BOXSIZE*10, (BOXSIZE/2)-(BOXSIZE/5), BOXSIZE, BOXSIZE/2.5, BLUE);if (oldPENRADIUS == 3) tft.fillRect(BOXSIZE*11, 0, BOXSIZE, BOXSIZE, WHITE);tft.fillRect(BOXSIZE*11,(BOXSIZE/2)-(BOXSIZE/3), BOXSIZE, BOXSIZE/1.5, BLUE);}

       if (oldcolor != currentcolor) { if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED); if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW); if (oldcolor == GREEN) tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN); if (oldcolor == CYAN) tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN); if (oldcolor == BLUE) tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE); if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE*5 , 0, BOXSIZE, BOXSIZE, MAGENTA);if (oldcolor == WHITE) tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, WHITE);if (oldcolor == BLACK) tft.fillRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, BLACK); } } 
       if (((p.y) > BOXSIZE+2) && ((p.y) < tft.height())) {
      tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);}
      
    }
}

#define BUFFPIXEL 20
void bmpDraw(int x, int y) {

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

  // Parse BMP header
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

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...
          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each column...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              // Push LCD buffer to the display first
              if(lcdidx > 0) {
                tft.pushColors(lcdbuffer, lcdidx, first);
                lcdidx = 0;
                first  = false;
              }
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = tft.color565(r,g,b);
          } // end pixel
        } // end scanline
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
String getFileName(byte i){
  byte o = 0;
  String result;
  File root = SD.open("/");    

    File entry =  root.openNextFile();
    result=entry.name();
         entry.close(); 
 root.close();  
  return result;
}
