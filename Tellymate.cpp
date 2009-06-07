/*
  Tellymate.h - Arduino Library for using the Tellymate Shield
  Created by goldfish yo! 
  Copyright (c) 2009, goldfish yo!
  
  Portions based on Tellymate demo code and specifications
  Created and Copyright (c) 2009, Nigel Batten.
  http://www.batsocks.co.uk/
  

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

	1.	Redistributions of source code must retain the above copyright
		notice, this list of conditions and the following disclaimer.
	2.	Redistributions in binary form must reproduce the above copyright
		notice, this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT HOLDER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.

===============================================

TellyMate Serial to Video adapter
=================================
	38x25 character display
	PAL or NTSC composite video output
	Up to 57k6 serial data.
	Autobauding option.
	VT52 escape codes.
	H19 escape codes.
	Double-height / Double-width text.
	Code Page 437 graphics
	White text on black background
*/

#include "WProgram.h"
#include "Tellymate.h"

#define CHAR_ESC "\x1B"

Tellymate::Tellymate( long serialRate )
{
  _serialRate = serialRate;
  _xloc = 0;
  _yloc = 0;
}

void Tellymate::init()
{
  Serial.begin( _serialRate );
  Serial.print( CHAR_ESC "E");
  _xloc = 0;
  _yloc = 0;
  delay( 10 );  // may not be needed.
}

void Tellymate::diagnostic()
{
  Serial.print( CHAR_ESC "Q");
}

void Tellymate::clearscreen()
{ // <ESC>E
  Serial.print( CHAR_ESC "E" ); 
  _xloc = 0;
  _yloc = 0;
}

void Tellymate::cursoron()
{ // <ESC>e 
  Serial.print( CHAR_ESC "e" );
}

void Tellymate::cursoroff()
{ // <ESC>f 
  Serial.print( CHAR_ESC "f" );
}

void Tellymate::cursorup( int moves )
{
  _yloc = _yloc - moves;
  if( _yloc < 0 ){
      _yloc = 0;
  }
  cursorto( _yloc, _xloc);
}

void Tellymate::cursordown( int moves )
{
  _yloc = _yloc + moves;
  if( _yloc > 24 ){
      _yloc = 24;
  }
  cursorto( _yloc, _xloc);
}

void Tellymate::cursorright( int moves )
{
  _xloc = _xloc + moves;
  if( _xloc > 37 ){
      _xloc = 37;
  }
  cursorto( _yloc, _xloc);
}

void Tellymate::cursorleft( int moves )
{
  _xloc = _xloc - moves;
  if( _xloc < 0 ){
      _xloc = 0;
  }
  cursorto( _yloc, _xloc);
}

void Tellymate::printchar( unsigned char char2print )
{
  Serial.print( char2print );
}

void Tellymate::cursorto( uint8_t row , uint8_t col )
{ // <ESC>Yrc
  Serial.print( CHAR_ESC "Y" ) ;
  Serial.print((unsigned char)(32 + row)) ;
  Serial.print((unsigned char)(32 + col)) ;
  _xloc = col;
  _yloc = row;
}
