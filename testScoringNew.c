#include <stdio.h> 

char const me = 'w'; 
char const oppo = 'b'; 
char board[6*7]; 

//NBL: Number of Balls in Line 
//NBLC: NBL Count 

typedef struct 
{
	int meBC; 
	int oppoBC; 
	int meNBLC[5];
	int oppoNBLC[5];
	int meExtraNBL; 
	int oppoExtraNBL; 
} hScoreInfo;

hScoreInfo myhScoreInfo;

void initializehScoreInfo();
void updateBC(); 
void updateNBLC_col();
void updateNBLC_row(); 
void updateNBLC_diag(); 
int calculatehScore(); 
int main() 
{
	for (int i=0; i<6*7; i++) 
	{
		board[i] = 'e'; 
	} 
 
	initializehScoreInfo();

	board[0*7+0] = 'w'; 
	board[1*7+0] = 'w'; 
	board[2*7+0] = 'w'; 
	board[3*7+0] = 'w'; 
	board[4*7+0] = 'w'; 
	board[5*7+0] = 'w'; 

	board[0*7+1] = 'b'; 
	board[1*7+1] = 'b'; 
	board[2*7+1] = 'b'; 
	board[3*7+1] = 'b'; 
	board[4*7+1] = 'b'; 
	board[5*7+1] = 'b'; 
	
	board[0*7+2] = 'e';
	board[1*7+2] = 'b'; 
	board[2*7+2] = 'w'; 
	board[3*7+2] = 'w';
	board[4*7+2] = 'w'; 
	board[5*7+2] = 'w';

	board[0*7+3] = 'e'; 
	board[1*7+3] = 'w';
	board[2*7+3] = 'w'; 
	board[3*7+3] = 'w'; 
	board[4*7+3] = 'w';
	board[5*7+3] = 'b';

	board[0*7+4] = 'w'; 
	board[1*7+4] = 'w'; 
	board[2*7+4] = 'w'; 
	board[3*7+4] = 'w'; 
	board[4*7+4] = 'b'; 
	board[5*7+4] = 'b'; 

	board[0*7+5] = 'e'; 
	board[1*7+5] = 'e'; 
	board[2*7+5] = 'b'; 
	board[3*7+5] = 'b'; 
	board[4*7+5] = 'b'; 
	board[5*7+5] = 'w'; 

	board[0*7+6] = 'e';
	board[1*7+6] = 'e'; 
	board[2*7+6] = 'e'; 
	board[3*7+6] = 'e'; 
	board[4*7+6] = 'e'; 
	board[5*7+6] = 'b';  
	  

	updateBC(); 
	updateNBLC_col();
	updateNBLC_row();
	updateNBLC_diag();
	
	int score = calculatehScore();
	//printf("score = %d\n", score);  
	  
}

void initializehScoreInfo()
{
	myhScoreInfo.meBC = 0;
	myhScoreInfo.oppoBC = 0;

	for (int i=0; i<5; i++) 
	{
		myhScoreInfo.meNBLC[i] = 0;
		myhScoreInfo.oppoNBLC[i] = 0;
	}

	myhScoreInfo.meExtraNBL = 0;
	myhScoreInfo.oppoExtraNBL = 0;
}

void updateBC()
{
	for (int i=0; i<42; i++) 
	{
		myhScoreInfo.meBC += (board[i] == me)? 1:0;
		myhScoreInfo.oppoBC += (board[i] == oppo)? 1:0; 
	}
}

void updateNBLC_col() 
{
	//Moving from left end column to right end column 
	for (int c=0; c<7; c++) 
	{ 
		int NBL4Present = 0; 
 
		//Base moving from bottom row to 3rd row. 
		//There are only 3 possible arrays of 4 in a column.  
		for (int base=5; base>=3 && !NBL4Present; base--) 
		{ 
			if (board[base*7+c] == 'e')
			{  
				break; 
			}

			int meNBL = 0; 
			int oppoNBL = 0; 
		
			//Go through the array of 4
			int offset, r; 

			for (offset = 0; offset<4; offset++) 
			{
				r = base - offset; 
				meNBL += (board[r*7+c] == me)? 1:0;
				oppoNBL += (board[r*7+c] == oppo)? 1:0; 
			}

			if (!(meNBL > 0 && oppoNBL > 0))
			{
				myhScoreInfo.meNBLC[meNBL]++; 
				myhScoreInfo.oppoNBLC[oppoNBL]++; 
			} 

			//My array of 4 
			if (meNBL == 4) 
			{ 
				int upwardOffset = offset; 
				r = base - upwardOffset; 

				while (r >= 0 && board[r*7+c] == me) 
				{
					upwardOffset++; 
					r = base - upwardOffset;
				}

				myhScoreInfo.meExtraNBL += upwardOffset - offset;
				NBL4Present = 1;   
			}

			//Opponent's array of 4 
			else if (oppoNBL == 4)  
			{
				int upwardOffset = offset; 
				r = base - upwardOffset; 

				while (r >= 0 && board[r*7+c] == oppo) 
				{
					upwardOffset++; 
					r = base - upwardOffset;
				}
 
				myhScoreInfo.oppoExtraNBL += upwardOffset - offset;
				NBL4Present = 1;  
			}  
		}
	}
}

void updateNBLC_row() 
{
	for (int r=0; r<6; r++) 
	{
		int NBL4Present = 0; 

		//There are 4 possible arrays of 4 in a row. 
		for (int base=0; base<4 &!NBL4Present; base++) 
		{
			int meNBL = 0; 
			int oppoNBL = 0; 

			//Go through the array of 4
			int offset, c; 
 
			for (offset=0; offset<4; offset++)
			{
				c = base + offset; 
				meNBL += (board[r*7+c] == me)? 1:0; 
				oppoNBL += (board[r*7+c] == oppo)? 1:0;
			} 	

			if (!(meNBL > 0 && oppoNBL > 0))
			{
				myhScoreInfo.meNBLC[meNBL]++; 
				myhScoreInfo.oppoNBLC[oppoNBL]++; 
			}

			//My array of 4
			if (meNBL == 4) 
			{ 	
				//Check the left side
				int leftOffset = 1;
				c = base - leftOffset; 
 
				while (c >= 0 && board[r*7+c] == me) 
				{
					leftOffset++;
					c = base - leftOffset;  
				}

				myhScoreInfo.meExtraNBL += leftOffset-1; 

				//Check the right side 
				int rightOffset = offset; 
				c = base + rightOffset; 
				
				while (c <= 6 && board[r*7+c] == me) 
				{
					rightOffset++; 
					c = base + rightOffset; 
				}

				myhScoreInfo.meExtraNBL += rightOffset-offset;
				NBL4Present = 1;  
			} 

			//Opponent's array of 4 
			else if (oppoNBL == 4) 
			{ 	
				//Check the left side
				int leftOffset = 1;
				c = base - leftOffset; 
 
				while (c >= 0 && board[r*7+c] == oppo) 
				{
					leftOffset++;
					c = base - leftOffset;  
				}

				myhScoreInfo.oppoExtraNBL += leftOffset-1; 

				//Check the right side 
				int rightOffset = offset; 
				c = base + rightOffset; 
				
				while (c <= 6 && board[r*7+c] == oppo) 
				{
					rightOffset++; 
					c = base + rightOffset; 
				}

				myhScoreInfo.oppoExtraNBL += rightOffset-offset;
				NBL4Present = 1;
			}
		} 
	}	
}

void updateNBLC_diag() 
{  
	int numDiags = 6; 
	int numArrays[] = {1,2,3,3,2,1}; 
	int rowBases[] = {3,4,5,5,5,5}; 

	//Dianogals from bottom left to top right  
	int colBases1[] = {0,0,0,1,2,3}; 
	
	for (int diag = 0; diag < numDiags; diag++) 
	{ 
		int NBL4Present = 0; 

		for (int base=0; base < numArrays[diag] &!NBL4Present; base++) 
		{
			int meNBL = 0; 
			int oppoNBL = 0; 

			int offset, r, c;
			for (offset=0; offset<4; offset++) 
			{
				r = rowBases[diag] - base - offset; 
				c = colBases1[diag] + base + offset; 

				meNBL += (board[r*7+c] == me)? 1:0;
				oppoNBL += (board[r*7+c] == oppo)? 1:0;  
			}

			if (!(meNBL > 0 && oppoNBL > 0))
			{
				myhScoreInfo.meNBLC[meNBL]++; 
				myhScoreInfo.oppoNBLC[oppoNBL]++; 
			}

			//My array of 4
			if (meNBL == 4) 
			{
				myhScoreInfo.meNBLC[meNBL]++;

				//Check downard left 
				int downwardLeftOffset = 1; 
				r = rowBases[diag] - base + downwardLeftOffset; 
				c = colBases1[diag] + base - downwardLeftOffset; 

				while (r<6 && c >= 0 && board[r*7+c] == me)
				{
					downwardLeftOffset++; 
					r = rowBases[diag] - base + downwardLeftOffset; 
					c = colBases1[diag] + base - downwardLeftOffset; 
				} 

				myhScoreInfo.meExtraNBL += downwardLeftOffset - 1; 

				//Check upward right 
				int upwardRightOffset = offset; 
				r = rowBases[diag] - base - upwardRightOffset; 
				c = colBases1[diag] + base + upwardRightOffset;

				while (r >= 0 && c<7 && board[r*7+c] == me) 
				{
					upwardRightOffset++; 
					r = rowBases[diag] - base - upwardRightOffset; 
					c = colBases1[diag] + base + upwardRightOffset;
				} 

				myhScoreInfo.meExtraNBL += upwardRightOffset - offset;
				NBL4Present = 1; 
			}

			//Opponent's array of 4 
			else if (oppoNBL == 4) 
			{ 
				//Check downard left 
				int downwardLeftOffset = 1; 
				r = rowBases[diag] - base + downwardLeftOffset; 
				c = colBases1[diag] + base - downwardLeftOffset; 

				while (r<6 && c >= 0 && board[r*7+c] == oppo)
				{
					downwardLeftOffset++; 
					r = rowBases[diag] - base + downwardLeftOffset; 
					c = colBases1[diag] + base - downwardLeftOffset; 
				} 

				myhScoreInfo.oppoExtraNBL += downwardLeftOffset - 1;  

				//check upward right 
				int upwardRightOffset = offset; 
				r = rowBases[diag] - base - upwardRightOffset; 
				c = colBases1[diag] + base + upwardRightOffset;

				while (r >= 0 && c<7 && board[r*7+c] == oppo) 
				{
					upwardRightOffset++; 
					r = rowBases[diag] - base - upwardRightOffset; 
					c = colBases1[diag] + base + upwardRightOffset;
				} 

				myhScoreInfo.oppoExtraNBL += upwardRightOffset - offset;
				NBL4Present = 1; 
			}
		}
	}

	//Diagnoals from bottom right to top left  
	int colBases2[] = {6,6,6,5,4,3}; 

	for (int diag = 0; diag < numDiags; diag++) 
	{ 
		int NBL4Present = 0; 

		for (int base=0; base < numArrays[diag] && !NBL4Present; base++) 
		{
			int meNBL = 0; 
			int oppoNBL = 0; 

			int offset, r, c;
			for (offset=0; offset<4; offset++) 
			{
				r = rowBases[diag] - base - offset; 
				c = colBases2[diag] - base - offset; 

				meNBL += (board[r*7+c] == me)? 1:0;
				oppoNBL += (board[r*7+c] == oppo)? 1:0;  
			}

			if (!(meNBL > 0 && oppoNBL > 0))
			{
				myhScoreInfo.meNBLC[meNBL]++; 
				myhScoreInfo.oppoNBLC[oppoNBL]++; 
			}

			//My array of 4
			if (meNBL == 4) 
			{ 
				//Check upward left 
				int upwardLeftOffset = offset; 
				r = rowBases[diag] - base - upwardLeftOffset; 
				c = colBases1[diag] - base - upwardLeftOffset;

				while (r >= 0 && c >= 0 && board[r*7+c] == me) 
				{
					upwardLeftOffset++; 
					r = rowBases[diag] - base - upwardLeftOffset; 
					c = colBases2[diag] - base - upwardLeftOffset;
				} 

				myhScoreInfo.meExtraNBL += upwardLeftOffset - offset;

				//Check downward right 
				int downwardRightOffset = 1; 
				r = rowBases[diag] - base + downwardRightOffset; 
				c = colBases2[diag] - base + downwardRightOffset; 

				while (r<6 && c<7 && board[r*7+c] == me) 
				{
					downwardRightOffset++;
					r = rowBases[diag] - base + downwardRightOffset; 
					c = colBases2[diag] - base + downwardRightOffset; 
				}

				myhScoreInfo.meExtraNBL += downwardRightOffset - 1;
				NBL4Present = 1;  
			}

			//Opponent's array of 4
			else if (oppoNBL == 4) 
			{ 
				//check upward left
				int upwardLeftOffset = offset; 
				r = rowBases[diag] - base - upwardLeftOffset; 
				c = colBases2[diag] - base - upwardLeftOffset;

				while (r >= 0 && c >= 0 && board[r*7+c] == oppo) 
				{
					upwardLeftOffset++; 
					r = rowBases[diag] - base - upwardLeftOffset; 
					c = colBases1[diag] - base - upwardLeftOffset;
				} 

				myhScoreInfo.oppoExtraNBL += upwardLeftOffset - offset;

				//Check downward right 
				int downwardRightOffset = 1; 
				r = rowBases[diag] - base + downwardRightOffset; 
				c = colBases2[diag] - base + downwardRightOffset; 

				while (r<6 && c<7 && board[r*7+c] == oppo) 
				{
					downwardRightOffset++;
					r = rowBases[diag] - base + downwardRightOffset; 
					c = colBases2[diag] - base + downwardRightOffset; 
				}

				myhScoreInfo.oppoExtraNBL += downwardRightOffset - 1;
				NBL4Present = 1;  
			}
		}
	}		
}

int calculatehScore() 
{
	int myhScore = 0;
	int oppohScore = 0;	 

	//BC 
	myhScore += myhScoreInfo.meBC; 
	oppohScore += myhScoreInfo.oppoBC; 

	//NBL = 1, weight = 1;
	myhScore += myhScoreInfo.meNBLC[1]*1;
	oppohScore += myhScoreInfo.oppoNBLC[1]*1; 

	//NBL = 2, weight = 1; 
	myhScore += myhScoreInfo.meNBLC[2]*1; 
	oppohScore += myhScoreInfo.oppoNBLC[2]*1; 

	//NBL = 3, weight = 1; 
	myhScore += myhScoreInfo.meNBLC[3]*1; 
	oppohScore += myhScoreInfo.oppoNBLC[3]*1;

	//NBL = 4, weight = 1; 
	myhScore += myhScoreInfo.meNBLC[4]*1;
	oppohScore += myhScoreInfo.oppoNBLC[4]*1;

	//extrNBL, weight = 1;
	myhScore += myhScoreInfo.meExtraNBL*1; 
	oppohScore += myhScoreInfo.oppoExtraNBL*1; 

	//Deduct points for arrays of 4 of the other 
	myhScore -= myhScoreInfo.oppoNBLC[4]*2; 
	oppohScore -= myhScoreInfo.meNBLC[4]*2;

	if (myhScore < myhScoreInfo.meBC) 
	myhScore = myhScoreInfo.meBC;

	if (oppohScore < myhScoreInfo.oppoBC) 
	oppohScore = myhScoreInfo.oppoBC; 

	return myhScore - oppohScore;    
}
