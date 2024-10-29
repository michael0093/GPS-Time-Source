/*
As this library is practically a a port of some of the functions available in
the Adafruit OLED library, all work here falls under their licencing aggreement:

Software License Agreement (BSD License)

Copyright (c) 2012 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef OLED_H
#define	OLED_H

#include <stdint.h>
#include <stdbool.h>
#include "ti_msp_dl_config.h"
#include "string.h"

#ifdef	__cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////

#define OLED_SETCONTRAST 0x81
#define OLED_DISPLAYALLON_RESUME 0xA4
#define OLED_DISPLAYALLON 0xA5
#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7
#define OLED_DISPLAYOFF 0xAE
#define OLED_DISPLAYON 0xAF
#define OLED_SETDISPLAYOFFSET 0xD3
#define OLED_SETCOMPINS 0xDA
#define OLED_SETVCOMDETECT 0xDB
#define OLED_SETDISPLAYCLOCKDIV 0xD5
#define OLED_SETPRECHARGE 0xD9
#define OLED_SETMULTIPLEX 0xA8
#define OLED_SETLOWCOLUMN 0x00
#define OLED_SETHIGHCOLUMN 0x10
#define OLED_SETSTARTLINE 0x40
#define OLED_MEMORYMODE 0x20
#define OLED_COLUMNADDR 0x21
#define OLED_PAGEADDR   0x22
#define OLED_COMSCANINC 0xC0
#define OLED_COMSCANDEC 0xC8
#define OLED_SEGREMAP 0xA0
#define OLED_CHARGEPUMP 0x8D

///////////////////////////////////////////////////////////////////////////////

static const unsigned char OLED_characters[] = {
    0x00, 0x00, 0x00, 0x00, 0x00,	 // 	(Space)
  	0x00, 0x00, 0x5F, 0x00, 0x00,	 // 	!
  	0x00, 0x07, 0x00, 0x07, 0x00,	 // 	"
  	0x14, 0x7F, 0x14, 0x7F, 0x14,	 // 	#
  	0x24, 0x2A, 0x7F, 0x2A, 0x12,	 // 	$
  	0x23, 0x13, 0x08, 0x64, 0x62,	 // 	%
  	0x36, 0x49, 0x56, 0x20, 0x50,	 // 	&
  	0x00, 0x08, 0x07, 0x03, 0x00,	 // 	'
  	0x00, 0x1C, 0x22, 0x41, 0x00,	 // 	(
  	0x00, 0x41, 0x22, 0x1C, 0x00,	 // 	)
  	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,	 // 	*
  	0x08, 0x08, 0x3E, 0x08, 0x08,	 // 	+
  	0x00, 0x00, 0x70, 0x30, 0x00,	 // 	,
  	0x08, 0x08, 0x08, 0x08, 0x08,	 // 	-
  	0x00, 0x00, 0x60, 0x60, 0x00,	 // 	.
  	0x20, 0x10, 0x08, 0x04, 0x02,	 // 	/
  	0x3E, 0x51, 0x49, 0x45, 0x3E,	 // 	0
  	0x00, 0x42, 0x7F, 0x40, 0x00,	 // 	1
  	0x72, 0x49, 0x49, 0x49, 0x46,	 // 	2
  	0x21, 0x41, 0x49, 0x4D, 0x33,	 // 	3
  	0x18, 0x14, 0x12, 0x7F, 0x10,	 // 	4
  	0x27, 0x45, 0x45, 0x45, 0x39,	 // 	5
  	0x3C, 0x4A, 0x49, 0x49, 0x31,	 // 	6
  	0x41, 0x21, 0x11, 0x09, 0x07,	 // 	7
  	0x36, 0x49, 0x49, 0x49, 0x36,	 // 	8
  	0x46, 0x49, 0x49, 0x29, 0x1E,	 // 	9
  	0x00, 0x00, 0x14, 0x00, 0x00,	 // 	:
  	0x00, 0x40, 0x34, 0x00, 0x00,	 // 	;
  	0x00, 0x08, 0x14, 0x22, 0x41,	 // 	<
  	0x14, 0x14, 0x14, 0x14, 0x14,	 // 	=
  	0x00, 0x41, 0x22, 0x14, 0x08,	 // 	>
  	0x02, 0x01, 0x59, 0x09, 0x06,	 // 	?
  	0x3E, 0x41, 0x5D, 0x59, 0x4E,	 // 	@
  	0x7C, 0x12, 0x11, 0x12, 0x7C,	 // 	A
  	0x7F, 0x49, 0x49, 0x49, 0x36,	 // 	B
  	0x3E, 0x41, 0x41, 0x41, 0x22,	 // 	C
  	0x7F, 0x41, 0x41, 0x41, 0x3E,	 // 	D
  	0x7F, 0x49, 0x49, 0x49, 0x41,	 // 	E
  	0x7F, 0x09, 0x09, 0x09, 0x01,	 // 	F
  	0x3E, 0x41, 0x41, 0x51, 0x73,	 // 	G
  	0x7F, 0x08, 0x08, 0x08, 0x7F,	 // 	H
  	0x00, 0x41, 0x7F, 0x41, 0x00,	 // 	I
  	0x20, 0x40, 0x41, 0x3F, 0x01,	 // 	J
  	0x7F, 0x08, 0x14, 0x22, 0x41,	 // 	K
  	0x7F, 0x40, 0x40, 0x40, 0x40,	 // 	L
  	0x7F, 0x02, 0x1C, 0x02, 0x7F,	 // 	M
  	0x7F, 0x04, 0x08, 0x10, 0x7F,	 // 	N
  	0x3E, 0x41, 0x41, 0x41, 0x3E,	 // 	O
  	0x7F, 0x09, 0x09, 0x09, 0x06,	 // 	P
  	0x3E, 0x41, 0x51, 0x21, 0x5E,	 // 	Q
  	0x7F, 0x09, 0x19, 0x29, 0x46,	 // 	R
  	0x26, 0x49, 0x49, 0x49, 0x32,	 // 	S
  	0x03, 0x01, 0x7F, 0x01, 0x03,	 // 	T
  	0x3F, 0x40, 0x40, 0x40, 0x3F,	 // 	U
  	0x1F, 0x20, 0x40, 0x20, 0x1F,	 // 	V
  	0x3F, 0x40, 0x38, 0x40, 0x3F,	 // 	W
  	0x63, 0x14, 0x08, 0x14, 0x63,	 // 	X
  	0x03, 0x04, 0x78, 0x04, 0x03,	 // 	Y
  	0x61, 0x59, 0x49, 0x4D, 0x43,	 // 	Z
  	0x00, 0x7F, 0x41, 0x41, 0x41,	 // 	[
  	0x02, 0x04, 0x08, 0x10, 0x20,	 // 	"\"
  	0x00, 0x41, 0x41, 0x41, 0x7F,	 // 	]
  	0x04, 0x02, 0x01, 0x02, 0x04,	 // 	^
  	0x40, 0x40, 0x40, 0x40, 0x40,	 // 	_
  	0x00, 0x03, 0x07, 0x08, 0x00,	 // 	`
  	0x20, 0x54, 0x54, 0x38, 0x40,	 // 	a
  	0x7F, 0x28, 0x44, 0x44, 0x38,	 // 	b
  	0x38, 0x44, 0x44, 0x44, 0x28,	 // 	c
  	0x38, 0x44, 0x44, 0x28, 0x7F,	 // 	d
  	0x38, 0x54, 0x54, 0x54, 0x18,	 // 	e
  	0x00, 0x08, 0x7E, 0x09, 0x02,	 // 	f
  	0x0C, 0x52, 0x52, 0x4A, 0x3C,	 // 	g
  	0x7F, 0x08, 0x04, 0x04, 0x78,	 // 	h
  	0x00, 0x44, 0x7D, 0x40, 0x00,	 // 	i
  	0x20, 0x40, 0x40, 0x3D, 0x00,	 // 	j
  	0x7F, 0x10, 0x28, 0x44, 0x00,	 // 	k
  	0x00, 0x41, 0x7F, 0x40, 0x00,	 // 	l
  	0x7C, 0x04, 0x78, 0x04, 0x78,	 // 	m
  	0x7C, 0x08, 0x04, 0x04, 0x78,	 // 	n
  	0x38, 0x44, 0x44, 0x44, 0x38,	 // 	o
  	0x7C, 0x18, 0x24, 0x24, 0x18,	 // 	p
  	0x18, 0x24, 0x24, 0x18, 0x7C,	 // 	q
  	0x7C, 0x08, 0x04, 0x04, 0x08,	 // 	r
  	0x48, 0x54, 0x54, 0x54, 0x24,	 // 	s
  	0x04, 0x04, 0x3F, 0x44, 0x24,	 // 	t
  	0x3C, 0x40, 0x40, 0x20, 0x7C,	 // 	u
  	0x1C, 0x20, 0x40, 0x20, 0x1C,	 // 	v
  	0x3C, 0x40, 0x30, 0x40, 0x3C,	 // 	w
  	0x44, 0x28, 0x10, 0x28, 0x44,	 // 	x
  	0x4C, 0x50, 0x50, 0x50, 0x3C,	 // 	y
  	0x44, 0x64, 0x54, 0x4C, 0x44,	 // 	z
  	0x00, 0x08, 0x36, 0x41, 0x00,	 // 	{
  	0x00, 0x00, 0x77, 0x00, 0x00,	 // 	|
  	0x00, 0x41, 0x36, 0x08, 0x00,	 // 	}
  	0x02, 0x01, 0x02, 0x04, 0x02,	 // 	~
};

// Based on Courier New, Bold, 19pt. Fixed 16x16 size
static const unsigned char OLED_numbers_16x16[] = {
	/* @0 '0' (12 pixels wide) */
	//     #####   
	//    #######  
	//   ###   ### 
	//   ##     ## 
	//  ##       ##
	//  ##       ##
	//  ##       ##
	//  ##       ##
	//  ##       ##
	//  ##       ##
	//  ##       ##
	//  ##       ##
	//   ##     ## 
	//   ###   ### 
	//    #######  
	//     #####   
	0x00, 0xF0, 0xFC, 0x0E, 0x07, 0x03, 0x03, 0x03, 0x07, 0x0E, 0xFC, 0xF0, 
	0x00, 0x0F, 0x3F, 0x70, 0xE0, 0xC0, 0xC0, 0xC0, 0xE0, 0x70, 0x3F, 0x0F, 

	/* @24 '1' (12 pixels wide) */
	//       #     
	//    ####     
	//  ######     
	//  ### ##     
	//      ##     
	//      ##     
	//      ##     
	//      ##     
	//      ##     
	//      ##     
	//      ##     
	//      ##     
	//      ##     
	//      ##     
	// ############
	// ############
	0x00, 0x0C, 0x0C, 0x0E, 0x06, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 

	/* @48 '2' (12 pixels wide) */
	//     ####    
	//   ########  
	//  ###    ##  
	//  ##      ## 
	//  ##      ## 
	//          ## 
	//         ### 
	//        ###  
	//       ###   
	//      ###    
	//     ##      
	//    ##       
	//   ##        
	//  ##         
	// ########### 
	// ########### 
	0x00, 0x1C, 0x1E, 0x06, 0x03, 0x03, 0x03, 0x83, 0xC6, 0xFE, 0x78, 0x00, 
	0xC0, 0xE0, 0xF0, 0xD8, 0xCC, 0xC6, 0xC3, 0xC3, 0xC1, 0xC0, 0xC0, 0x00, 

	/* @72 '3' (12 pixels wide) */
	//     #####   
	//    #######  
	//   ###   ### 
	//   ##     ## 
	//          ## 
	//          ## 
	//         ##  
	//      ####   
	//      #####  
	//         ### 
	//          ###
	//           ##
	//           ##
	//  ##      ###
	//  ########## 
	//   #######   
	0x00, 0x00, 0x0C, 0x0E, 0x07, 0x83, 0x83, 0x83, 0xC7, 0x7E, 0x3C, 0x00, 
	0x00, 0x60, 0xE0, 0xC0, 0xC0, 0xC1, 0xC1, 0xC1, 0xC3, 0x67, 0x7E, 0x3C, 

	/* @96 '4' (12 pixels wide) */
	//        ###  
	//       ####  
	//       ####  
	//      ## ##  
	//      ## ##  
	//     ##  ##  
	//     ##  ##  
	//    ##   ##  
	//    ##   ##  
	//   ##    ##  
	//  ##     ##  
	//  ###########
	//  ###########
	//         ##  
	//      #######
	//      #######
	0x00, 0x00, 0x00, 0x80, 0xE0, 0x78, 0x1E, 0x07, 0xFF, 0xFF, 0x00, 0x00, 
	0x00, 0x1C, 0x1E, 0x1B, 0x19, 0xD8, 0xD8, 0xD8, 0xFF, 0xFF, 0xD8, 0xD8, 

	/* @120 '5' (12 pixels wide) */
	//  ########## 
	//  ########## 
	//  ##         
	//  ##         
	//  ##         
	//  ## #####   
	//  #########  
	//  ###     ## 
	//  ##       ##
	//           ##
	//           ##
	//           ##
	//           ##
	// ###      ## 
	// ##########  
	//   #######   
	0x00, 0xFF, 0xFF, 0xC3, 0x63, 0x63, 0x63, 0x63, 0x63, 0xC3, 0x83, 0x00, 
	0x60, 0x61, 0xE1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x60, 0x3F, 0x1F, 

	/* @144 '6' (12 pixels wide) */
	//       ##### 
	//     ########
	//    ####   ##
	//   ###       
	//   ##        
	//  ###        
	//  ## #####   
	//  #########  
	//  ####   ### 
	//  ###     ###
	//  ##       ##
	//  ##       ##
	//   ##      ##
	//   ###    ###
	//    ######## 
	//     #####   
	0x00, 0xE0, 0xF8, 0xBC, 0xCE, 0xC6, 0xC7, 0xC3, 0xC3, 0x83, 0x07, 0x06, 
	0x00, 0x0F, 0x3F, 0x73, 0xE1, 0xC0, 0xC0, 0xC0, 0xC1, 0x63, 0x7F, 0x3E, 

	/* @168 '7' (12 pixels wide) */
	//  ###########
	//  ###########
	//  ##       ##
	//  ##      ## 
	//          ## 
	//          ## 
	//         ##  
	//         ##  
	//        ##   
	//        ##   
	//        ##   
	//       ##    
	//       ##    
	//      ###    
	//      ##     
	//      ##     
	0x00, 0x0F, 0x0F, 0x03, 0x03, 0x03, 0x03, 0x03, 0xC3, 0xFB, 0x3F, 0x07, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0x3F, 0x07, 0x00, 0x00, 0x00, 

	/* @192 '8' (12 pixels wide) */
	//     #####   
	//   ######### 
	//   ##     ## 
	//  ##       ##
	//  ##       ##
	//  ##       ##
	//   ##     ## 
	//    #######  
	//    #######  
	//   ##     ## 
	//  ##       ##
	//  ##       ##
	//  ##       ##
	//   ##     ## 
	//   ######### 
	//     #####   
	0x00, 0x38, 0x7E, 0xC6, 0x83, 0x83, 0x83, 0x83, 0x83, 0xC6, 0x7E, 0x38, 
	0x00, 0x1C, 0x7E, 0x63, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0x63, 0x7E, 0x1C, 

	/* @216 '9' (12 pixels wide) */
	//     ####    
	//    #######  
	//   ##    ### 
	//  ##      ## 
	//  ##       ##
	//  ##       ##
	//  ##       ##
	//  ###     ###
	//   ###   ####
	//    #########
	//     ##### ##
	//          ## 
	//         ### 
	//  ##    ###  
	//  ########   
	//   #####     
	0x00, 0xF8, 0xFC, 0x86, 0x03, 0x03, 0x03, 0x03, 0x06, 0x8E, 0xFC, 0xF0, 
	0x00, 0x60, 0xE1, 0xC3, 0xC7, 0xC6, 0xC6, 0x66, 0x77, 0x3B, 0x1F, 0x07, 

	/* @240 ':' (12 pixels wide) */
	//             
	//             
	//             
	//             
	//             
	//     ####    
	//     ####    
	//     ####    
	//             
	//             
	//             
	//             
	//             
	//     ####    
	//     ####    
	//     ####    
	0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00
};

// Based on Arial Narrow Bold, 24pt. Fixed 16x24 size
static const unsigned char OLED_numbers_16x24[] = {
	/* @0 '0' (14 pixels wide) */
	//     #####     
	//    #######    
	//   #########   
	//  ###########  
	//  ####   ####  
	//  ####   ####  
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	//  ####   ####  
	//  ####   ####  
	//  ###########  
	//   #########   
	//    #######    
	//     #####     
	0xC0, 0xF8, 0xFC, 0xFE, 0x3F, 0x0F, 0x0F, 0x0F, 0x3F, 0xFE, 0xFC, 0xF8, 0xC0, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
	0x01, 0x0F, 0x1F, 0x3F, 0x7E, 0x78, 0x78, 0x78, 0x7E, 0x3F, 0x1F, 0x0F, 0x01, 0x00, 

	/* @42 '1' (14 pixels wide) */
	//        ###    
	//       ####    
	//      #####    
	//     ######    
	//   ########    
	//  #########    
	//  #### ####    
	//  ###  ####    
	//  #    ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	0x00, 0xE0, 0xF0, 0xF0, 0x78, 0x3C, 0xFE, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 

	/* @84 '2' (14 pixels wide) */
	//     #####     
	//   #########   
	//  ###########  
	//  ###########  
	// #####   ##### 
	// ####     #### 
	// ####     #### 
	//          #### 
	//          #### 
	//         ####  
	//         ####  
	//        #####  
	//       #####   
	//      #####    
	//     #####     
	//    #####      
	//    ####       
	//   ####        
	//  #####        
	//  ############ 
	//  ############ 
	// ############# 
	// ############# 
	0x70, 0x7C, 0x7E, 0x7E, 0x1F, 0x0F, 0x0F, 0x0F, 0x1F, 0xFE, 0xFE, 0xFC, 0xF0, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0x7E, 0x3F, 0x1F, 0x0F, 0x01, 0x00, 
	0x60, 0x7C, 0x7E, 0x7F, 0x7F, 0x7F, 0x79, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x00, 

	/* @126 '3' (14 pixels wide) */
	//     #####     
	//   #########   
	//   ##########  
	//  ###########  
	//  ####   ##### 
	// ####     #### 
	// ####     #### 
	//          #### 
	//         ####  
	//      #######  
	//      ######   
	//      ######   
	//      #######  
	//         ##### 
	//          #### 
	//          #### 
	// ####     #### 
	// ####     #### 
	//  ####   ##### 
	//  ###########  
	//   ##########  
	//   #########   
	//     #####     
	0x60, 0x78, 0x7E, 0x7E, 0x1F, 0x0F, 0x0F, 0x0F, 0x1F, 0xFE, 0xFE, 0xFC, 0xF0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x1E, 0x1E, 0x3F, 0xFF, 0xFF, 0xF3, 0xE0, 0x00, 
	0x03, 0x0F, 0x3F, 0x3F, 0x7C, 0x78, 0x78, 0x78, 0x7C, 0x3F, 0x3F, 0x1F, 0x07, 0x00, 

	/* @168 '4' (14 pixels wide) */
	//         ####  
	//         ####  
	//        #####  
	//       ######  
	//       ######  
	//      #######  
	//      #######  
	//     ### ####  
	//    #### ####  
	//    ###  ####  
	//   ####  ####  
	//   ###   ####  
	//  ###    ####  
	// ####    ####  
	// ##############
	// ##############
	// ##############
	// ##############
	//         ####  
	//         ####  
	//         ####  
	//         ####  
	//         ####  
	0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0x7C, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 
	0xE0, 0xF0, 0xFC, 0xFF, 0xCF, 0xC7, 0xC1, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x7F, 0x7F, 0x7F, 0x7F, 0x03, 0x03, 

	/* @210 '5' (14 pixels wide) */
	//   ##########  
	//   ##########  
	//   ##########  
	//  ###########  
	//  ####         
	//  ####         
	//  ####         
	//  #### ###     
	//  ##########   
	//  ###########  
	// ############  
	// ####    ##### 
	// ###      #### 
	//          #### 
	//          #### 
	//          #### 
	// ####     #### 
	// ####     #### 
	//  ####   ####  
	//  ###########  
	//   #########   
	//   ########    
	//     #####     
	0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0x0F, 0x8F, 0x8F, 0x8F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 
	0x1C, 0x1F, 0x1F, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x0F, 0xFF, 0xFF, 0xFE, 0xF8, 0x00, 
	0x03, 0x0F, 0x3F, 0x3F, 0x7C, 0x78, 0x78, 0x78, 0x7C, 0x3F, 0x1F, 0x0F, 0x03, 0x00, 

	/* @252 '6' (14 pixels wide) */
	//      #####    
	//    ########   
	//   ##########  
	//   ##########  
	//  ####   ##### 
	//  ####    #### 
	// ####          
	// ####          
	// #### ####     
	// ###########   
	// ############  
	// ############  
	// #####   ##### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	//  ###     #### 
	//  ####   ##### 
	//  ###########  
	//   ##########  
	//    ########   
	//     #####     
	0xC0, 0xF0, 0xFC, 0xFE, 0x3E, 0x0F, 0x0F, 0x0F, 0x1F, 0x3F, 0x3E, 0x3C, 0x30, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x1E, 0x0F, 0x0F, 0x0F, 0x1F, 0xFE, 0xFE, 0xFC, 0xF0, 0x00, 
	0x01, 0x0F, 0x1F, 0x3F, 0x7C, 0x78, 0x78, 0x78, 0x7C, 0x3F, 0x3F, 0x1F, 0x07, 0x00, 

	/* @294 '7' (14 pixels wide) */
	// ############# 
	// ############# 
	// ############# 
	// ############# 
	//         ####  
	//        ####   
	//        ####   
	//       ####    
	//       ####    
	//      ####     
	//      ####     
	//     ####      
	//     ####      
	//     ####      
	//    ####       
	//    ####       
	//    ####       
	//    ####       
	//   ####        
	//   ####        
	//   ####        
	//   ####        
	//   ####        
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x8F, 0xEF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0x00, 
	0x00, 0x00, 0x00, 0xC0, 0xF8, 0xFE, 0xFF, 0x3F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7C, 0x7F, 0x7F, 0x7F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	/* @336 '8' (14 pixels wide) */
	//     #####     
	//   #########   
	//  ###########  
	// ############# 
	// #####   ##### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	//  ####   ####  
	//  ###########  
	//    ########   
	//   #########   
	//  ###########  
	//  ####   ####  
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// #####   ##### 
	//  ###########  
	//  ###########  
	//   #########   
	//     #####     
	0xF8, 0xFC, 0xFE, 0xFE, 0x1F, 0x0F, 0x0F, 0x0F, 0x1F, 0xFE, 0xFE, 0xFC, 0xF8, 0x00, 
	0xC0, 0xF3, 0xFB, 0xFF, 0x3F, 0x1E, 0x1E, 0x1E, 0x3F, 0xFF, 0xFF, 0xF3, 0xC0, 0x00, 
	0x07, 0x1F, 0x3F, 0x3F, 0x7C, 0x78, 0x78, 0x78, 0x7C, 0x3F, 0x3F, 0x1F, 0x07, 0x00, 

	/* @378 '9' (14 pixels wide) */
	//     #####     
	//   ########    
	//  ##########   
	//  ###########  
	// #####   ####  
	// ####     ###  
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// ####     #### 
	// #####   ##### 
	//  ############ 
	//  ############ 
	//   ########### 
	//     #### #### 
	//          #### 
	//          #### 
	// ####    ####  
	// #####   ####  
	//  ##########   
	//  ##########   
	//   ########    
	//    #####      
	0xF0, 0xFC, 0xFE, 0xFE, 0x1F, 0x0F, 0x0F, 0x0F, 0x1F, 0xFE, 0xFC, 0xF8, 0xC0, 0x00, 
	0x07, 0x1F, 0x3F, 0x3F, 0x7C, 0x78, 0x78, 0x78, 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
	0x06, 0x1E, 0x3E, 0x7E, 0x7C, 0x78, 0x78, 0x78, 0x3E, 0x3F, 0x1F, 0x07, 0x01, 0x00, 

	/* @420 ':' (14 pixels wide) */
	//               
	//               
	//               
	//               
	//               
	//               
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	//               
	//               
	//               
	//               
	//               
	//               
	//               
	//               
	//               
	//       ####    
	//       ####    
	//       ####    
	//       ####    
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x78, 0x78, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0F, 0x0F, 0x06, 0x00, 0x00, 0x00, 0x00
};

static char OLED_buffer[128 * 32 / 8] = {   // Prepopulated with logo and "No Signal" message
	//        ####        ####     ####   #####         ####           ####                        ####                                
	//       ######       ####     ####    ####        #####           ####                        ####                                
	//       ######       ####     ####    #####      #####            ####                        ####                                
	//       #######      ####     ####     #####     #####            ####                        ####                                
	//       #######      ####     ####     #####    #####             ####                        ####                                
	//       ########     ####     ####      #####   ####              ####                        ####                                
	//       ########     ####     ####       ####  #####              ####      ############      ############       ###########      
	//       #########    ####     ####       ##########               ####      #############     #############     ############      
	//       #########    ####     ####        #########               ####      #############     #############    #############      
	//       ####  ####   ####     ####        ########                ####               ####     ######   #####   ####               
	//       ####  ####   ####     ####         #######                ####               #####    ####      ####   ####               
	//       ####   ####  ####     ####        ########                ####        ############    ####      ####   ########           
	//       ####   ####  ####     ####       ##########               ####      ##############    ####      ####    ##########        
	//       ####    #########     ####       ####  #####              ####      ##############    ####      ####     ###########      
	//       ####    #########     ####      #####   ####              ####      ####     #####    ####      ####       #########      
	//       ####     ########     ####      ####    #####             ####      ####     #####    ####      ####            #####     
	//       ####     ########     ####     #####     ####             ####      ####    ######    ####     #####             ####     
	//       ####      #######     ####     ####      #####            #######   ##############    ##############    #############     
	//       ####      #######     ####    #####       #####           ########  ##############    #############     ############      
	//       ####       ######     ####   #####        #####            #######   #############    ############     #############      
	//       ####        ####      ####   #####         #####            #####     #####   ####      #########      ###########        
	//                                                                                                                                 
	//                                                                                                                                 
	//                         ##   ##     ####             ####    ######    #####    ##   ##      ##      ##                         
	//                         ###  ##    ######           ######   ######   #######   ###  ##     ####     ##                         
	//                         ###  ##   ###  ###          ##         ##     ##        ###  ##     ####     ##                         
	//                         #### ##   ##    ##          ####       ##     ##        #### ##    ##  ##    ##                         
	//                         #######   ##    ##           ####      ##     ## ####   #######    ##  ##    ##                         
	//                         ## ####   ##    ##             ###     ##     ## ####   ## ####    ######    ##                         
	//                         ##  ###   ###  ###              ##     ##     ##   ##   ##  ###   ########   ##                         
	//                         ##  ###    ######           ######   ######   #######   ##  ###   ##    ##   #######                    
	//                         ##   ##     ####             ####    ######    ######   ##   ##   ##    ##   #######                    
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1F, 0x3F, 0xFF, 0xFC, 0xF8, 0xE0, 0x80, 0x80, 0xC0, 0xF0, 0xFC, 0xFE, 0x7F, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x07, 0x1F, 0x7F, 0xFE, 0xF8, 0xE0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xFB, 0xFF, 0x7F, 0x1F, 0x1F, 0x3F, 0xFF, 0xFF, 0xF1, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF1, 0xF1, 0xF9, 0xF9, 0x39, 0x39, 0x39, 0x39, 0x39, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x03, 0x01, 0x01, 0x01, 0x03, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x3F, 0x79, 0x79, 0x79, 0x79, 0x71, 0xF1, 0xF1, 0xE1, 0xE1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x00, 0x80, 0x80, 0x00, 0x00, 0x1F, 0x9F, 0x9F, 0x1F, 0x00, 0x00, 0x00, 0x18, 0x9C, 0x9F, 0x9F, 0x9F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x1F, 0x1E, 0x1C, 0x90, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x87, 0x8F, 0x9F, 0x1F, 0x1E, 0x1E, 0x1E, 0x8C, 0x80, 0x80, 0x87, 0x8F, 0x1F, 0x1F, 0x1E, 0x1E, 0x9E, 0x8E, 0x0F, 0x0F, 0x1F, 0x9F, 0x9F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x8F, 0x9F, 0x1F, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x9F, 0x9F, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x18, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x0F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x0F, 0x1C, 0x78, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x3E, 0x7F, 0xE3, 0xC1, 0xC1, 0xE3, 0x7F, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0xCF, 0xCD, 0xDD, 0xF9, 0x71, 0x00, 0x00, 0x00, 0xC1, 0xC1, 0xFF, 0xFF, 0xC1, 0xC1, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xC1, 0xD9, 0xD9, 0xF9, 0xF9, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x0F, 0x1C, 0x78, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xE0, 0xFC, 0x3F, 0x33, 0x33, 0x3F, 0xFC, 0xE0, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define OLED_ADDR 0x3C
    
void OLED_Init();
char OLED_command(char command);
char OLED_data(char data);
char OLED_write();
void OLED_clear();
void OLED_invert();
void OLED_rscroll(char start, char stop);
void OLED_lscroll(char start, char stop);
void OLED_stopscroll();
void OLED_pixel(short x, short y, char color);
void OLED_char(char character, short x, short y);
void OLED_num(char num, short x, short y);
void OLED_string(char* str, short x, short y);

#ifdef	__cplusplus
}
#endif

#endif	

