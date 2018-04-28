
# C_BlockFIFO
data FIFO use block. Simple but useful .

Not task-safe in embedded system 

HOW TO:

#define LineNum		20

#define BlockSize	 5
  
T_BlkFifo gBlkFifo;

unsigned char testArray[LineNum][BlockSize] = {0};

unsigned char *(pp[LineNum]);

for(i=0;i<LineNum;i++)
{
	pp[i] = &testArray[i][0];
}

//the pointer array "pp", Separate storage can be used.

InitBlockFifo(&gBlkFifo,pp,LineNum,BlockSize);
  
//you can use WriteBlockFifo(&gBlkFifo,(unsigned char*)"abc") in the [dma]interrupt code.
//Carefully . "abc".length <= BlockSize 
  
//you can use ReadBlockFifo(&gBlkFifo,rrrr) in the application code.
//Carefully . rrrr.length >= BlockSize   

//if application code is slowly and cache is full, Early data will be override.


                                          
