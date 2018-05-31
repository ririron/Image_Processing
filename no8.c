#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

int zm = 255;

void input_NM(unsigned char (*nm)[256], unsigned char *h, unsigned char M);

void move_PIXEL(unsigned char (*nm)[256], unsigned char (*cnt)[256], imgdata idata);



int main(int argc, char *argv[])
{
  imgdata idata;

  int x, y;
  unsigned char depth = 8;
  unsigned char h[256] = {0};
  unsigned char nm[256][256] = {0};
  unsigned char cnt[256][256] = {0};
  unsigned char input = 0;
  int M = (256 * 256)/ 8;

  int i,s;

  unsigned char (*p_nm)[256];
  unsigned char (*p_cnt)[256];

  p_nm = nm;
  p_cnt = cnt;


  for(i=0;i<256;i++){
    for(s=0;s<256;s++){
      p_nm[i][s] = 0;
      p_cnt[i][s] = 0;
    }
  }

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {

      for (y = 0; y < idata.height; y++){
	       for (x = 0; x < idata.width; x++){
            input = idata.source[RED][y][x];
            h[input]++;
          }
      }
      input_NM(p_nm, h, M);

      move_PIXEL(p_nm, p_cnt, idata);


      if (writeBMPfile(argv[2], &idata) > 0)
        printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
      }
  }
}

void input_NM(unsigned char (*nm)[256],unsigned char *h,unsigned char M){
  int i,s;
  for(i=0;i<256;i++){
    s = i + 1;
    while(h[i] != M){
      if(h[i] > M){
        nm[i][i+1] += 1;
        h[i]--;
        h[i+1]++;
      }
      if(h[i] < M){
        while(h[s] == 0){
          s++;
        }
        nm[s][i] += 1;
        h[i]++;
        h[s]--;
      }
    }
  }
}

void move_PIXEL(unsigned char (*nm)[256], unsigned char (*cnt)[256], imgdata idata){
  int i;
  int j;
  int x, y;
  int x2, y2;

  for(i = 0, j = 1;i <= 254&&j <= 255; i++,j++){
    for (y = idata.height; y > 0; y--) {
      for (x = idata.width; x > 0; x--) {
        if (idata.source[RED][x][y] == i && cnt[i][j] < nm[i][j]) {

          for (y2 = idata.height; y > 0; y--) {
            for (x2 = idata.width; x > 0 && idata.source[RED][x2][y2] != j; x--) {
            }
          }

           idata.results[RED][x2][y2] += 1;
           idata.source[RED][x2][y2] += 1;
           idata.results[RED][x][y] -= 1;
           idata.source[RED][x][y] -= 1;
        }
      }
    }
  }
}
