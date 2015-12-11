#include <stdlib.h>
#include <stdio.h>
#include "BMP.h"



void readBFH(BitmapFileHeader *bfh, FILE *fp){
	fread(&(bfh->bfType[0]),   ByteOf_bfType,      1, fp);
	fread(&(bfh->bfSize),      ByteOf_bfSize,      1, fp);
	fread(&(bfh->bfReserved1), ByteOf_bfReserved1, 1, fp);
	fread(&(bfh->bfReserved2), ByteOf_bfReserved2, 1, fp);
	fread(&(bfh->bfOffBits),   ByteOf_bfOffBits,   1, fp);
}

void readBIH(BitmapInfoHeader *bih, FILE *fp){
	fread(&(bih->biSize),          ByteOf_biSize,          1, fp);
	fread(&(bih->biWidth),         ByteOf_biWidth,         1, fp);
	fread(&(bih->biHeight),        ByteOf_biHeight,        1, fp);
	fread(&(bih->biPlanes),        ByteOf_biPlanes,        1, fp);
	fread(&(bih->biBitCount),      ByteOf_biBitCount,      1, fp);
	fread(&(bih->biCompression),   ByteOf_biCompression,   1, fp);
	fread(&(bih->biSizeImage),     ByteOf_biSizeImage,     1, fp);
	fread(&(bih->biXPelsPerMeter), ByteOf_biXPelsPerMeter, 1, fp);
	fread(&(bih->biYPelsPerMeter), ByteOf_biYPelsPerMeter, 1, fp);
	fread(&(bih->biClrUsed),       ByteOf_biClrUsed,       1, fp);
	fread(&(bih->biClrImportant),  ByteOf_biClrImportant,  1, fp);
}

void readRGBQuad(RGBQuad *rgbQ, int bitCount, FILE *fp){
	fread(rgbQ, sizeof(char) * 4, bitCount, fp);
}

void readBitSet(BitSet *bitSet, int size, FILE * fp){
	fread(bitSet, sizeof(BitSet), size, fp);
}


void writeBFH(BitmapFileHeader *bfh, FILE *fp){
	fwrite(&(bfh->bfType[0]),   ByteOf_bfType,      1, fp);
	fwrite(&(bfh->bfSize),      ByteOf_bfSize,      1, fp);
	fwrite(&(bfh->bfReserved1), ByteOf_bfReserved1, 1, fp);
	fwrite(&(bfh->bfReserved2), ByteOf_bfReserved2, 1, fp);
	fwrite(&(bfh->bfOffBits),   ByteOf_bfOffBits,   1, fp);
}

void writeBIH(BitmapInfoHeader *bih, FILE *fp){
	fwrite(&(bih->biSize),          ByteOf_biSize,          1, fp);
	fwrite(&(bih->biWidth),         ByteOf_biWidth,         1, fp);
	fwrite(&(bih->biHeight),        ByteOf_biHeight,        1, fp);
	fwrite(&(bih->biPlanes),        ByteOf_biPlanes,        1, fp);
	fwrite(&(bih->biBitCount),      ByteOf_biBitCount,      1, fp);
	fwrite(&(bih->biCompression),   ByteOf_biCompression,   1, fp);
	fwrite(&(bih->biSizeImage),     ByteOf_biSizeImage,     1, fp);
	fwrite(&(bih->biXPelsPerMeter), ByteOf_biXPelsPerMeter, 1, fp);
	fwrite(&(bih->biYPelsPerMeter), ByteOf_biYPelsPerMeter, 1, fp);
	fwrite(&(bih->biClrUsed),       ByteOf_biClrUsed,       1, fp);
	fwrite(&(bih->biClrImportant),  ByteOf_biClrImportant,  1, fp);
}

void writeRGBQuad(RGBQuad *rgbQ, int bitCount, FILE *fp){
	fwrite(rgbQ, sizeof(char) * 4, bitCount, fp);
}

void writeBitSet(BitSet *bitSet, int size, FILE *fp){
	fwrite(bitSet, sizeof(BitSet), size, fp);
}


void setBFH(BitmapFileHeader *bfh, int bwidth, int height){
  bfh->bfType[0] = 'B';
  bfh->bfType[1] = 'M';
  bfh->bfSize = bwidth * height + FH_Size + IH_Size;
  bfh->bfReserved1 = 0;
  bfh->bfReserved2 = 0;
  bfh->bfOffBits = FH_Size + IH_Size;

}

void setBIH(BitmapInfoHeader *bih, int width, int bwidth, int height){
  bih->biSize = IH_Size;
  bih->biWidth = width;
  bih->biHeight = height;
  bih->biPlanes = 1;
  bih->biBitCount = 24;
  bih->biCompression = 0;
  bih->biSizeImage = bwidth * height;
  bih->biXPelsPerMeter = 0;
  bih->biYPelsPerMeter = 0;
  bih->biClrUsed = 0;
  bih->biClrImportant = 0;
}

void setBitSet(BitSet *bitSet, int width, int bwidth, int height, unsigned char r, unsigned char g, unsigned char b){
  int i, j;

  for(j = 0; j < height; j++){
    for(i =0; i < width; i++){
      *(bitSet + j * bwidth + i * 3 + 2) = r;
      *(bitSet + j * bwidth + i * 3 + 1) = g;
      *(bitSet + j * bwidth + i * 3    ) = b;
    }
  }
}

void readBMP(BMPStruct *bmpStruct,  char *filename){

	FILE *fp;
	int bitCount;

	bmpStruct->bfh = (BitmapFileHeader *)malloc(sizeof(BitmapFileHeader));
	bmpStruct->bih = (BitmapInfoHeader *)malloc(sizeof(BitmapInfoHeader));


	if((fp = fopen(filename,"rb")) == NULL){
	  printf("Can not find %s file\n", filename);
	  exit(1);
	}

	readBFH(bmpStruct->bfh,fp);
	readBIH(bmpStruct->bih,fp);

	if(bmpStruct->bih->biBitCount != 24) {
		bitCount = 1<<bmpStruct->bih->biBitCount;
		bmpStruct->rgbQ = (RGBQuad *)malloc(sizeof(char) * 4 * bitCount);
		readRGBQuad(bmpStruct->rgbQ, bitCount, fp);
	}

	bmpStruct->bitSet = (BitSet *)malloc(sizeof(BitSet) * (bmpStruct->bfh->bfSize - bmpStruct->bfh->bfOffBits));

	readBitSet(bmpStruct->bitSet, bmpStruct->bfh->bfSize - bmpStruct->bfh->bfOffBits, fp);

	fclose(fp);

}

void writeBMP(BMPStruct bmpStruct, char *filename){

	FILE *fp;

	fp = fopen(filename,"wb");

	writeBFH(bmpStruct.bfh,fp);
	writeBIH(bmpStruct.bih,fp);
	if(bmpStruct.bih->biBitCount != 24){
		writeRGBQuad(bmpStruct.rgbQ, 1<<bmpStruct.bih->biBitCount, fp);
	}
	writeBitSet(bmpStruct.bitSet, bmpStruct.bfh->bfSize - bmpStruct.bfh->bfOffBits, fp);

	fclose (fp);
}


void makeBMP(BMPStruct *bmpStruct, int width, int height, RGB rgb){

  int rem;
  int bwidth;

  rem = (width * 3) % 4;
  if(rem == 0){
    bwidth = width * 3;
  }
  else{
    bwidth = width * 3 + 4 - rem;
  }
  
  bmpStruct->bfh = (BitmapFileHeader *)malloc(sizeof(BitmapFileHeader));
  bmpStruct->bih = (BitmapInfoHeader *)malloc(sizeof(BitmapInfoHeader));
  bmpStruct->bitSet = (BitSet *)malloc(bwidth * height);
  
  setBFH(bmpStruct->bfh, bwidth, height);
  setBIH(bmpStruct->bih, width, bwidth, height);
  setBitSet(bmpStruct->bitSet, width, bwidth, height, rgb.r, rgb.g, rgb.b);

}

void freeBMP(BMPStruct *bmp){
  if((bmp->bih)->biBitCount != 24){
    free(bmp->rgbQ);
  }
  free(bmp->bitSet);
  free(bmp->bfh);
  free(bmp->bih);
}



int getColor(BMPStruct bmp, int i, int h, RGB *rgb){

	int width, height;
	int bwidth;
	int rem;

	width = bmp.bih->biWidth;
	height = bmp.bih->biHeight;


	// Exception 
	if(i < 0 || i > width - 1){

		printf("x position is bad\n");
		printf("x = %d\n", i);
		return(1);
	}

	if(h < 0 || h > height - 1){

		printf("y position is bad\n");
		printf("y = %d\n", h);

		return(1);
	}


	rem = (width * 3) % 4;
		if(rem == 0){
		bwidth = width * 3;
	}
	else{
		bwidth = width * 3 + 4 - rem;
	}


	rgb->r = *(bmp.bitSet + h * bwidth + i * 3 + 2);
	rgb->g = *(bmp.bitSet + h * bwidth + i * 3 + 1);
	rgb->b = *(bmp.bitSet + h * bwidth + i * 3    );


	return(0);
}

int putColor(BMPStruct bmp, int i, int h, RGB rgb){

	int width, height;
	int bwidth;
	int rem;

	width = bmp.bih->biWidth;
	height = bmp.bih->biHeight;


	// Exception 
	if(i < 0 || i > width - 1){

		printf("x position is bad\n");
		printf("x = %d\n", i);
		return(1);
	}

	if(h < 0 || h > height - 1){

		printf("y position is bad\n");
		printf("y = %d\n", h);

		return(1);
	}

	rem = (width * 3) % 4;
		if(rem == 0){
		bwidth = width * 3;
	}
	else{
		bwidth = width * 3 + 4 - rem;
	}

	*(bmp.bitSet + h * bwidth + i * 3 + 2) = rgb.r;
	*(bmp.bitSet + h * bwidth + i * 3 + 1) = rgb.g;
	*(bmp.bitSet + h * bwidth + i * 3    ) = rgb.b;

	return(0);
}

