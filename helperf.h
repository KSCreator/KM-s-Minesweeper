#ifndef KM_HELPERF_H
#define KM_HELPERF_H

#define MS_MINE 10           //according to Data
#define MSFLAG 10           //according to Map

#define PSIZE 40

//set mines in random location
void setTarget(short* map);
//open all the tiles to show
void OpenAll(short*,short*);
//open all tiles near the tile[i,j]
void OpenTiles(short*,short*,int,int,unsigned&);
//reset the game
void ResetGame(short*,short*);
//read game statics
void ReadGameData(short&,short&);
//write game statics
void WriteGameData(short,short);
#endif // KM_HELPERF_H
