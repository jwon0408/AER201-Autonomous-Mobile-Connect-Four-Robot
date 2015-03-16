char const me = 'w'; 
char const oppo = 'b'; 
char board[6*7]; 

//NBL: Number of Balls in Line 
//NBLC: NBL Count 

typedef struct 
{
	int meNBLC[5];
	int oppoNBLC[5];
	int meExtraNBL; 
	int oppoExtraNBL; 
} hScoreInfo;

void initializehScore(); 
void updateColhScore();
void updateRowhScore(); 
void updateDiaghScore(); 
//long calculatehScore(); 
 
