/*
 * my_fbcopy.c
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <bcm_host.h>

#include "tft.h"
#include "RAIO8870.h"


int main(int argc, char **argv)
{
	DISPMANX_DISPLAY_HANDLE_T main_display_handle;
	DISPMANX_RESOURCE_HANDLE_T screen_resource_handle;
	
	VC_RECT_T rectangle;
	
	int ret;
	uint32_t image_prt;
	uint16_t image[2][ PICTURE_PIXELS ];
	uint32_t current_frame = 0, old_frame=1;
	uint32_t i, x, y, start, end, count;
	uint16_t *p_current_frame, *p_old_frame, *p_start;
		
	bcm_host_init();
	
	if ( !bcm2835_init() )
	return ( -1 );
	
	TFT_init_board();
	
	TFT_hard_reset();
	
	RAIO_init();

	//clear old image 
	p_old_frame     = &image[ old_frame ][0];
	for(x=0; x<76800; x++)
	{
		*p_old_frame++ = 0x1111;
	}
	
	
	// open main framebuffer device
	main_display_handle = vc_dispmanx_display_open( 0 );
    if ( !main_display_handle )
    {
        printf("\n Unable to open primary display");
        return( -1 );
    }
    
    // now build up the shadow area for RAIO
    screen_resource_handle = vc_dispmanx_resource_create( VC_IMAGE_RGB565, DISPLAY_WIDTH, DISPLAY_HEIGHT, &image_prt );       
    if ( !screen_resource_handle )
    {
        printf("\n Unable to create screen buffer");
        vc_dispmanx_display_close( main_display_handle );
        return ( -1 );
    }

	vc_dispmanx_rect_set( &rectangle, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT );    
    
    while( 1 )
    {    
		ret = vc_dispmanx_snapshot( main_display_handle, screen_resource_handle, DISPMANX_NO_ROTATE );  
    
		vc_dispmanx_resource_read_data( screen_resource_handle, &rectangle, &image[ current_frame ][0], DISPLAY_WIDTH*2 ); 

		
		i=0;
		p_current_frame = &image[ current_frame ][ 0 ];
		p_old_frame     = &image[ old_frame ][ 0 ];	
		
		while (i<PICTURE_PIXELS)
		{		
			while (( *p_current_frame == *p_old_frame) && (i<PICTURE_PIXELS) )
			{
				p_current_frame++;
				p_old_frame++;
				i = i+1;
			}
			p_start = p_current_frame;
			start = i;
			
			
			while (( *p_current_frame != *p_old_frame) && (i<PICTURE_PIXELS) )
			{
				p_current_frame++;
				p_old_frame++;
				i = i+1;
			}
			count = i - start;
			
			y=start/DISPLAY_WIDTH;
			x=start-y*DISPLAY_WIDTH;
			RAIO_set_cursor( x, y );
			RAIO_Write_Picture( p_start, count );				
		}
		
		
		old_frame = current_frame;
		if ( current_frame == 0 )
			current_frame = 1;
		else
			current_frame = 0;
			
			
		// 100ms -> 10 fps
		usleep( 100 * 1000 );
	
	}


	return ( 0 );
}

