// Header File for BMP
// "BMPData.h"

#ifndef _BMP_DATA_H
#define _BMP_DATA_H

#define FH_Size 14
#define IH_Size 40

#define ByteOf_bfType 2
#define ByteOf_bfSize 4
#define ByteOf_bfReserved1 2
#define ByteOf_bfReserved2 2
#define ByteOf_bfOffBits 4

#define ByteOf_biSize 4
#define ByteOf_biWidth 4
#define ByteOf_biHeight 4
#define ByteOf_biPlanes 2
#define ByteOf_biBitCount 2
#define ByteOf_biCompression 4
#define ByteOf_biSizeImage 4
#define ByteOf_biXPelsPerMeter 4
#define ByteOf_biYPelsPerMeter 4
#define ByteOf_biClrUsed 4
#define ByteOf_biClrImportant 4

typedef struct tagBitmapFileHeader { // bmfh
    char			bfType[2];
    unsigned int	bfSize;
    unsigned short int	bfReserved1;
    unsigned short int	bfReserved2;
	unsigned int	bfOffBits;
} BitmapFileHeader; 

typedef struct tagBitmapInfoHeader{ // bmih
    unsigned int	biSize; 
    unsigned int	biWidth;
    unsigned int	biHeight;
    unsigned short int	biPlanes; 
    unsigned short int	biBitCount;
    unsigned int	biCompression;
    unsigned int	biSizeImage; 
    unsigned int	biXPelsPerMeter;
    unsigned int	biYPelsPerMeter;
    unsigned int	biClrUsed; 
    unsigned int	biClrImportant;
} BitmapInfoHeader; 

typedef struct tagRGBQuad{
	unsigned char rgbBlue;
    unsigned char rgbGreen; 
    unsigned char rgbRed;
    unsigned char gbReserved;
}RGBQuad;

typedef unsigned char BitSet; 

typedef struct tagBMPStruct{
	BitmapFileHeader *bfh;
	BitmapInfoHeader *bih;
	RGBQuad *rgbQ;
	BitSet *bitSet;
}BMPStruct;

typedef struct tagRGB{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}RGB;

// File Reading
void readBMP(BMPStruct *bmpStruct, char *filename);


// File Writing
void writeBMP(BMPStruct bmpStruct, char *filename);

//File Making
void makeBMP(BMPStruct *bmpStruct, int width, int height, RGB rgb);

//Free
void freeBMP(BMPStruct *bmpStruct);


//Get or Put Color
int getColor(BMPStruct bmp, int i, int h, RGB *rgb);
int putColor(BMPStruct bmp, int i, int h, RGB rgb);


#endif