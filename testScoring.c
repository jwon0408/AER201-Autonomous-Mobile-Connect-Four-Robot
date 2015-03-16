#include <stdio.h> 
#include "initialize.h"

hScoreInfo myhScoreInfo; 

int main() 
{
	for (int i=0; i<6*7; i++) 
	{
		board[i] = 'e'; 
	} 
 
	initializehScore();

	board[0*7+0] = 'e'; 
	board[1*7+0] = 'e'; 
	board[2*7+0] = 'e'; 
	board[3*7+0] = 'w'; 
	board[4*7+0] = 'w'; 
	board[5*7+0] = 'w'; 

	board[0*7+1] = 'e'; 
	board[1*7+1] = 'e'; 
	board[2*7+1] = 'e'; 
	board[3*7+1] = 'e'; 
	board[4*7+1] = 'e'; 
	board[5*7+1] = 'e'; 
	
	board[0*7+2] = 'e';
	board[1*7+2] = 'e'; 
	board[2*7+2] = 'e'; 
	board[3*7+2] = 'b';
	board[4*7+2] = 'b'; 
	board[5*7+2] = 'w';

	board[0*7+3] = 'b'; 
	board[1*7+3] = 'w';
	board[2*7+3] = 'b'; 
	board[3*7+3] = 'b'; 
	board[4*7+3] = 'w';
	board[5*7+3] = 'b';

	board[0*7+4] = 'w'; 
	board[1*7+4] = 'b'; 
	board[2*7+4] = 'b'; 
	board[3*7+4] = 'w'; 
	board[4*7+4] = 'b'; 
	board[5*7+4] = 'b'; 

	board[0*7+5] = 'e'; 
	board[1*7+5] = 'b'; 
	board[2*7+5] = 'w'; 
	board[3*7+5] = 'b'; 
	board[4*7+5] = 'w'; 
	board[5*7+5] = 'b'; 

	board[0*7+6] = 'w';
	board[1*7+6] = 'w'; 
	board[2*7+6] = 'b'; 
	board[3*7+6] = 'w'; 
	board[4*7+6] = 'w'; 
	board[5*7+6] = 'b';  
	  

	updateColhScore();
	updateRowhScore();
	updateDiaghScore();  
}