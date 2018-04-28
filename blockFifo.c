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




