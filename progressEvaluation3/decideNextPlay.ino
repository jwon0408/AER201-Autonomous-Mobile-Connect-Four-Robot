void initializeBoard() 
{
	for (int i=0; i<6*7; i++) 
	{
		board[i] = 'e'; 
	}
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
}

void manuallyUpdateBoard()
{
	board[0*7+0] = 'e'; 
	board[1*7+0] = 'e'; 
	board[2*7+0] = 'e'; 
	board[3*7+0] = 'e'; 
	board[4*7+0] = 'e'; 
	board[5*7+0] = 'b'; 

	board[0*7+1] = 'e'; 
	board[1*7+1] = 'e'; 
	board[2*7+1] = 'e'; 
	board[3*7+1] = 'e'; 
	board[4*7+1] = 'b'; 
	board[5*7+1] = 'w'; 
	
	board[0*7+2] = 'e';
	board[1*7+2] = 'e'; 
	board[2*7+2] = 'w'; 
	board[3*7+2] = 'w';
	board[4*7+2] = 'w'; 
	board[5*7+2] = 'w';

	board[0*7+3] = 'e'; 
	board[1*7+3] = 'e';
	board[2*7+3] = 'w'; 
	board[3*7+3] = 'w'; 
	board[4*7+3] = 'w';
	board[5*7+3] = 'w';

	board[0*7+4] = 'e'; 
	board[1*7+4] = 'e'; 
	board[2*7+4] = 'w'; 
	board[3*7+4] = 'w'; 
	board[4*7+4] = 'w'; 
	board[5*7+4] = 'w'; 

	board[0*7+5] = 'e'; 
	board[1*7+5] = 'e'; 
	board[2*7+5] = 'w'; 
	board[3*7+5] = 'w'; 
	board[4*7+5] = 'w'; 
	board[5*7+5] = 'w'; 

	board[0*7+6] = 'e';
	board[1*7+6] = 'e'; 
	board[2*7+6] = 'b'; 
	board[3*7+6] = 'b'; 
	board[4*7+6] = 'b'; 
	board[5*7+6] = 'b';  
}

void updateTopOfColumn() 
{
	for (int c=0; c<7; c++) 
	{
		for (int r=5; r>=0; r--) 
		{
			if (board[r*7+c] == 'e') 
			{
				topOfColumn[c] = r+1; 
				break;
			} 
		}
	}
}

void printBoard() 
{
	for (int r=0; r<6; r++) 
	{
		for (int c=0; c<7; c++) 
		{
			Serial.print(board[r*7+c]);
			Serial.print(" "); 
		}

		Serial.println(); 
	}

	Serial.println("--------------");
}

void makeMove(int moveCol, char player) 
{
	if (topOfColumn[moveCol] > 0) 
	{
		topOfColumn[moveCol]--; 
		board[topOfColumn[moveCol]*7+moveCol] = player; 
	} 
}

void undoMove(int moveCol) 
{
	board[topOfColumn[moveCol]*7+moveCol] = 'e'; 
	topOfColumn[moveCol]++;
}

int negamax_NA(int parentCol, int color, int depth, int spdFactor, int isFaster) 
{ 
	int score = calculatehScore(); 

	if (depth == 0) 
	{
		Serial.println("depth: 0\n");
		undoMove(parentCol);
		return color*score;
	}

	int bestChildCol; 
	int hasChildren = -1; 
	int bestValue = 0;

	for (int col=0; col<7; col++) 
	{
		if (topOfColumn[col] > 0) 
		{
			hasChildren = 1; 
			int childCol = col; 

			char player = (color > 0)? me: oppo; 
			makeMove(childCol, player);

 			initializehScoreInfo();
			updateBC(); 
			updateNBLC_col();
			updateNBLC_row();
			updateNBLC_diag();

			int SCBestVal; //Subsequent Best Children Best Value 

			if (spdFactor > 1 && isFaster) 
			{
				spdFactor--; 
				SCBestVal = negamax_NA(childCol, color, depth-1, spdFactor, isFaster); 
			}  

			else if (spdFactor == 1 && isFaster) 
			{
				SCBestVal = -negamax_NA(childCol, -color, depth-1, spdFactor, !isFaster); 
			}

			else if (!isFaster)
			{
				spdFactor = relativeSpd; 
				SCBestVal = -negamax_NA(childCol, -color, depth-1, spdFactor, !isFaster); 
			}

			if (SCBestVal >= bestValue) 
			{
				bestValue = SCBestVal;
				bestChildCol = childCol; 
			}
		}
	}

	if (parentCol != -1 && hasChildren == 1) 
	{
		undoMove(parentCol); 
		return bestValue;
	}

	else if (parentCol != -1 && hasChildren == -1) 
	{
		undoMove(parentCol); 
		return color*score; 
	}

	else //If it is the parent, return the column number. 
	{
		return bestChildCol; 
	}
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
		for (int base=5; (base>=3) && !NBL4Present; base--) 
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

			if (meNBL == 4 || oppoNBL == 4) 
			{
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
		for (int base=0; (base<4) &!NBL4Present; base++) 
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

			if (meNBL == 4 || oppoNBL == 4) 
			{ 	
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

		for (int base=0; (base < numArrays[diag]) & !NBL4Present; base++) 
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

			if (meNBL == 4 || oppoNBL == 4) 
			{
				NBL4Present = 1; 
			}
		}
	}

	//Diagnoals from bottom right to top left  
	int colBases2[] = {6,6,6,5,4,3}; 

	for (int diag = 0; diag < numDiags; diag++) 
	{ 
		int NBL4Present = 0; 

		for (int base=0; (base < numArrays[diag]) && !NBL4Present; base++) 
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

			if (meNBL == 4 || oppoNBL == 4) 
			{ 
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

	//printf("meBC: %d, oppoBC: %d\n", myhScoreInfo.meBC, myhScoreInfo.oppoBC); 

	//NBL = 1
	myhScore += myhScoreInfo.meNBLC[1]*0;
	oppohScore += myhScoreInfo.oppoNBLC[1]*0; 

	//NBL = 2 
	myhScore += myhScoreInfo.meNBLC[2]*0; 
	oppohScore += myhScoreInfo.oppoNBLC[2]*0; 

	//NBL = 3 
	myhScore += myhScoreInfo.meNBLC[3]*0; 
	oppohScore += myhScoreInfo.oppoNBLC[3]*0;

	//NBL = 4
	myhScore += myhScoreInfo.meNBLC[4]*4;
	oppohScore += myhScoreInfo.oppoNBLC[4]*4;

	//printf("meNBLC[4]: %d, oppoNBLC[4]: %d\n", myhScoreInfo.meNBLC[4], myhScoreInfo.oppoNBLC[4]);

	//Deduct points for arrays of 4 of the other 
	myhScore -= myhScoreInfo.oppoNBLC[4]*2; 
	oppohScore -= myhScoreInfo.meNBLC[4]*2;

	if (myhScore < myhScoreInfo.meBC) 
	{//printf("in if, myhScore = %d\n", myhScore);
	myhScore = myhScoreInfo.meBC;}

	if (oppohScore < myhScoreInfo.oppoBC)
	{//printf("in if, oppohScore = %d\n", oppohScore); 
	oppohScore = myhScoreInfo.oppoBC;}

	//printf("myhScore = %d, oppohScore = %d\n", myhScore, oppohScore); 

	return myhScore - oppohScore;    
}
