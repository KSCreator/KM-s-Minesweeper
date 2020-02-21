#include "helperf.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>

void setTarget(short *data)
{
    srand(unsigned(time(0)));

    for(int i = 0; i < 10; i++)
    {
        int c = rand()%10;
        int r = rand()%10;
        if(data[r*10 + c] != MS_MINE)
        {
            data[r*10 + c] = MS_MINE;
            if(r > 0 && data[(r-1)*10 + c] != MS_MINE)
                data[(r-1)*10+c]++;
            if(r < 9 && data[(r+1)*10 + c] != MS_MINE)
                data[(r+1)*10+c]++;
            if(c > 0 && data[r*10 + c - 1] != MS_MINE)
                data[r*10+c-1]++;
            if(c < 9 && data[r*10 + c + 1] != MS_MINE)
                data[r*10+c+1]++;
            if(r > 0 && c > 0 && data[(r-1)*10 + c-1] !=MS_MINE)
                data[(r-1)*10+c-1]++;
            if(r > 0 && c < 9 && data[(r-1)*10 + c+1] != MS_MINE)
                data[(r-1)*10+c+1]++;
            if(r < 9 && c > 0 && data[(r+1)*10 + c-1] != MS_MINE)
                data[(r+1)*10+c-1]++;
            if(r < 9 && c < 9 && data[(r+1)*10 + c+1] != MS_MINE)
                data[(r+1)*10+c+1]++;
        }
        else i--;
    }

}

void OpenTiles(short* map,short* data,int x,int y,unsigned& mnc)
{
    if(x > 0)
    {
        if( map[y*10 + x - 1] != MSFLAG ){
            if (map[y*10 + x - 1] == 0)
                mnc++;
            map[y*10 + x - 1] = data[y*10 + x - 1] + 1;
        }
        if( y > 0){
            if( map[(y-1)*10 + x - 1] != MSFLAG ){
                if (map[(y-1)*10 + x - 1] == 0)
                    mnc++;
                map[(y-1)*10 + x - 1] = data[(y-1)*10 + x - 1] + 1;

            }
        }
        if( y < 9){
            if( map[(y+1)*10 + x - 1] != MSFLAG ){
                if (map[(y+1)*10 + x - 1] == 0)
                    mnc++;
                map[(y+1)*10 + x - 1] = data[(y+1)*10 + x - 1] + 1;

            }
        }
    }
    if(x < 9)
    {
        if(map[y*10 + x + 1] != MSFLAG ){
            if (map[y*10 + x + 1] == 0)
                mnc++;
            map[y*10 + x + 1] = data[y*10 + x + 1] + 1;
        }
        if( y > 0){
            if( map[(y-1)*10 + x + 1] != MSFLAG ){
                if (map[(y-1)*10 + x + 1] == 0)
                    mnc++;
                map[(y-1)*10 + x + 1] = data[(y-1)*10 + x + 1] + 1;

            }
        }
        if( y < 9){
            if( map[(y+1)*10 + x + 1] != MSFLAG ){
                if (map[(y+1)*10 + x + 1] == 0)
                    mnc++;
                map[(y+1)*10 + x + 1] = data[(y+1)*10 + x + 1] + 1;
            }
        }
    }
    if(y > 0)
    {
        if( map[(y-1)*10 + x] != MSFLAG ){
            if (map[(y-1)*10 + x] == 0)
                mnc++;
            map[(y-1)*10 + x] = data[(y-1)*10 + x] + 1;
        }
    }
    if(y < 9)
    {
        if( map[(y+1)*10 + x] != MSFLAG ){
            if (map[(y+1)*10 + x] == 0)
                mnc++;
            map[(y+1)*10 + x] = data[(y+1)*10 + x] + 1;
        }
    }
}

void OpenAll(short *map,short *data)
{
    for(int i = 0; i < 100;i++){
        if(map[i] == MSFLAG && data[i] != MS_MINE)
            map[i] = 12;
        else
            map[i] = data[i] + 1;
    }
}

void ResetGame(short *map,short *data)
{
    for(int i = 0; i < 100; i++){
        map[i] = 0;
        data[i] = 0;
    }
    setTarget(data);
}

void ReadGameData(short &win,short &lose)
{
    FILE *f = fopen("Resource\\statics.dat","rb");
    if(f){
        fscanf(f,"%hi%hi",&win,&lose);
        fclose(f);
    }
    else{
        win = lose = 0;
    }
}

void WriteGameData(short win,short lose){
    FILE *f = fopen("Resource\\statics.dat","wb");
    if(f){
        fprintf(f,"%hi %hi",win,lose);
        fclose(f);
    }
}
