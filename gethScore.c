void initializehScore()
{
	for (int i=0; i<5; i++) 
	{
		myhScoreInfo.meNBLC[i] = 0;
		myhScoreInfo.oppoNBLC[i] = 0;
	}

	myhScoreInfo.meExtraNBL = 0;
	myhScoreInfo.oppoExtraNBL = 0;
}

void updateColhScore() 
{
	//Moving from left end column to right end column 
	for (int c=0; c<7; c++) 
	{
		//Base moving from bottom row to 3rd row. 
		//There are only 3 possible arrays of 4 in a column.  
		for (int base=5; base>=3; base--) 
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

			//My array of 4
			if (meNBL > 0 && oppoNBL == 0) 
			{
				myhScoreInfo.meNBLC[meNBL]++;

				int upwardOffset = offset; 
				r = base - upwardOffset; 

				while (r >= 0 && board[r*7+c] == me) 
				{
					upwardOffset++; 
					r = base - upwardOffset;
				}

				myhScoreInfo.meExtraNBL += upwardOffset - offset;  
			}

			//Opponent's array of 4 
			else if (oppoNBL > 0 && meNBL == 0)  
			{
				myhScoreInfo.oppoNBLC[oppoNBL]++;

				int upwardOffset = offset; 
				r = base - upwardOffset; 

				while (r >= 0 && board[r*7+c] == oppo) 
				{
					upwardOffset++; 
					r = base - upwardOffset;
				}

				myhScoreInfo.oppoExtraNBL += upwardOffset - offset;  
			} 
		}
	}
}

void updateRowhScore() 
{
	for (int r=0; r<6; r++) 
	{
		//There are 4 possible arrays of 4 in a row. 
		for (int base=0; base<4; base++) 
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

			//My array of 4
			if (meNBL > 0 && oppoNBL == 0) 
			{
				myhScoreInfo.meNBLC[meNBL]++; 	
			
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
			} 

			//Opponent's array of 4 
			else if (oppoNBL > 0 && meNBL == 0) 
			{
				myhScoreInfo.oppoNBLC[oppoNBL]++; 	
			
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
			}
		} 
	}	
}

void updateDiaghScore() 
{  
	int numDiags = 6; 
	int numArrays[] = {1,2,3,3,2,1}; 
	int rowBases[] = {3,4,5,5,5,5}; 

	//Dianogals from bottom left to top right  
	int colBases1[] = {0,0,0,1,2,3}; 
	
	for (int diag = 0; diag < numDiags; diag++) 
	{ 
		for (int base=0; base < numArrays[diag]; base++) 
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

			//My array of 4
			if (meNBL > 0 && oppoNBL == 0) 
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
			}

			//Opponent's array of 4 
			else if (oppoNBL > 0 && meNBL == 0) 
			{
				myhScoreInfo.oppoNBLC[oppoNBL]++; 

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
			}
		}
	}

	//Diagnoals from bottom right to top left  
	int colBases2[] = {6,6,6,5,4,3}; 

	for (int diag = 0; diag < numDiags; diag++) 
	{ 
		for (int base=0; base < numArrays[diag]; base++) 
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

			//My array of 4
			if (meNBL > 0 && oppoNBL == 0) 
			{
				myhScoreInfo.meNBLC[meNBL]++; 

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
			}

			//Opponent's array of 4
			else if (oppoNBL > 0 && meNBL == 0) 
			{
				myhScoreInfo.oppoNBLC[oppoNBL]++; 

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
			}
		}
	}		
}
