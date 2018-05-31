#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

int zm = 255;

void inputLut(unsigned char *lut,unsigned char input);


int main(int argc, char *argv[])
{
  imgdata idata;
  double c;
  int x, y;

  unsigned char lut[256];
  int i;
  for(i=0;i<256;i++){
    lut[i] = -1;
  }

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {

      for (y = 0; y < idata.height; y++){
	       for (x = 0; x < idata.width; x++){
          inputLut(lut,idata.source[RED][y][x]);
          inputLut(lut,idata.source[GREEN][y][x]);
          inputLut(lut,idata.source[BLUE][y][x]);
          }
      }
      for (y = 0; y < idata.height; y++){
        for (x = 0; x < idata.width; x++){
          unsigned char r = idata.source[RED][y][x];
          unsigned char g = idata.source[GREEN][y][x];
          unsigned char b = idata.source[BLUE][y][x];
          idata.results[RED][y][x] = lut[r];
          idata.results[GREEN][y][x] = lut[g];
          idata.results[BLUE][y][x] = lut[b];
        }
      }
      if (writeBMPfile(argv[2], &idata) > 0)
        printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
      }
  }
}

void inputLut(unsigned char *lut,unsigned char input){
  double gain = -7.0;
  double index = gain * (((double)input / zm) - 0.5) ;
  lut[input] = zm * (1.0 / (1.0 + exp(index)));
}
