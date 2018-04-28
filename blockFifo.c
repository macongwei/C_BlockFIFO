#include <string.h>

typedef struct{
	unsigned char **ppSide;
	int sideWidth;
	int sideHeight;
	int wr;
	int num;
}T_BlkFifo;

void InitBlockFifo(T_BlkFifo *pBlkFifo, unsigned char **pp, int blkCapacity, int blkSize)
{
	pBlkFifo->ppSide = pp;
	pBlkFifo->sideWidth = blkSize;
	pBlkFifo->sideHeight = blkCapacity;
	pBlkFifo->wr = blkCapacity;
	pBlkFifo->num = 0;
}

void WriteBlockFifo(T_BlkFifo *pBlkFifo, unsigned char* pBlk)
{
	memcpy((pBlkFifo->ppSide)[(pBlkFifo->wr)%(pBlkFifo->sideHeight)],pBlk,pBlkFifo->sideWidth);
	if(pBlkFifo->num < pBlkFifo->sideHeight)
		(pBlkFifo->num)++;
	pBlkFifo->wr = ((pBlkFifo->wr+1)%(pBlkFifo->sideHeight)) + pBlkFifo->sideHeight;
}

unsigned char ReadBlockFifo(T_BlkFifo *pBlkFifo, unsigned char* pBlk)
{
	if(pBlkFifo->num < 1)
		return 0;
	memcpy(pBlk,(pBlkFifo->ppSide)[(pBlkFifo->wr - pBlkFifo->num)%(pBlkFifo->sideHeight)],pBlkFifo->sideWidth);
	(pBlkFifo->num)--;
	return 1;
}


void example_use_block_fifo()
{
	#define LineNum		2
	#define BlockSize	 5
	
  int i = 0;
	T_BlkFifo gBlkFifo;
	unsigned char testArray[LineNum][BlockSize] = {0};
	unsigned char *(pp[LineNum]);
	for(i=0;i<LineNum;i++)
	{
		pp[i] = &testArray[i][0];
	}

	InitBlockFifo(&gBlkFifo,pp,LineNum,BlockSize);
	
	WriteBlockFifo(&gBlkFifo,(unsigned char*)"abc");
	WriteBlockFifo(&gBlkFifo,(unsigned char*)"xyz");
  //because LineNum is 2, so "mnp" will override "adb"
	WriteBlockFifo(&gBlkFifo,(unsigned char*)"mnp");

	unsigned char rrrr[10] = "";
  ReadBlockFifo(&gBlkFifo,rrrr);//rrrr is xyz
  ReadBlockFifo(&gBlkFifo,rrrr);//rrrr is mnp
  ReadBlockFifo(&gBlkFifo,rrrr);//return 0
  ReadBlockFifo(&gBlkFifo,rrrr);//return 0

}


