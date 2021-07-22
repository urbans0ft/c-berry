/*##############################################################*/
/* 																*/
/* File		: tft_test.c										*/
/*																*/
/* Project	: TFT for Raspberry Pi Revision 2					*/
/* 																*/
/* Date		: 2013-11-22   	    last update: 2013-12-20			*/
/* 																*/
/* Author	: Hagen Ploog   									*/
/*		  	  Kai Gillmann										*/
/*		  	  Timo Pfander										*/
/* 																*/
/* IDE	 	: Geany 1.22										*/
/* Compiler : gcc (Debian 4.6.3-14+rpi1) 4.6.3					*/
/*																*/
/* Copyright (C) 2013 admatec GmbH								*/
/*																*/
/*																*/	
/* Description  :												*/
/* 																*/
/*	This file contains the main loop. The program depict one	*/
/*	BMP file on the TFT and some basic drawings which 			*/
/*	were created with the RAIO graphic controller.				*/
/*																*/
/*																*/
/* License:														*/
/*																*/
/*	This program is free software; you can redistribute it 		*/ 
/*	and/or modify it under the terms of the GNU General			*/ 	
/*	Public License as published by the Free Software 			*/
/*	Foundation; either version 3 of the License, or 			*/
/*	(at your option) any later version. 						*/
/*    															*/
/*	This program is distributed in the hope that it will 		*/
/*	be useful, but WITHOUT ANY WARRANTY; without even the 		*/
/*	implied warranty of MERCHANTABILITY or 						*/
/*	FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 		*/
/*	Public License for more details. 							*/
/*																*/
/*	You should have received a copy of the GNU General 			*/
/*	Public License along with this program; if not, 			*/
/*	see <http://www.gnu.org/licenses/>.							*/
/*																*/
/*																*/
/* Revision History:											*/
/*																*/
/*	Version 1.0 - Initial release								*/
/*																*/
/*																*/
/*																*/
/*##############################################################*/

#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "tft.h"
#include "RAIO8870.h"
#include "bmp.h"


int main( int argc, char **argv )
{		
	uint16_t picture[1][ PICTURE_PIXELS ];
	char my_filename[] = "../bmp/admatec.bmp";
	int j;
	
		
	if (!bcm2835_init())
	return 1;
	
	
	TFT_init_board();
	TFT_hard_reset();
	RAIO_init();
	
	// draw with RAIO
	// ---------------------------------------------
	
	// rectangle	
	Draw_Square(0, 0, 319, 239);
	Text_Foreground_Color( COLOR_BLACK );
	RAIO_StartDrawing( SQUARE_FILL );
	Text_Foreground_Color( COLOR_BLUE );
	Draw_Square(210, 150, 260, 200);
	
	// line
	Draw_Line( 10, 230, 310, 10 );
	Text_Foreground_Color( COLOR_GREEN );
	RAIO_StartDrawing( LINE );
	
	// circle
	Draw_Circle( 90, 65, 25 );
	Text_Foreground_Color( COLOR_RED );
	RAIO_StartDrawing( CIRCLE_FILL );
	
	delay(10000);

	
	// depict a BMP file
	// ---------------------------------------------
	
	Read_bmp2memory ( &my_filename[0], &picture[0][ PICTURE_PIXELS-1 ] );
	RAIO_Write_Picture( &picture[0][0], PICTURE_PIXELS );
	
	
	delay(1000);

    
    bcm2835_close();
  
   	return 0;
}

