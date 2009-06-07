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
#define CHAR_CR "\x0D"
#define CHAR_LF "\x0A"

Tellymate::Tellymate( long serialRate )
{
  _serialRate = serialRate;
  _xloc = 0;
  _yloc = 0;
}

void Tellymate::init()
{
  Serial.begin( _serialRate );
  delay(50);
  Serial.print( CHAR_ESC "E");
  _xloc = 0;
  _yloc = 0;
  cursoroff();
  diagnostic();
  fontdoublewidth( 18 );
  cursorto( 18, 0 );
  Serial.println( "Tellymate lib" );
  Serial.print( "ver 0.01" );
  delay( 4000 );
  clearscreen();
}

void Tellymate::diagnostic()
{
  Serial.print( CHAR_ESC "Q");
  delay( 20 ); // tellymate users guide recommends at least 2ms delay
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

void Tellymate::cursorto( uint8_t row , uint8_t col )
{ // <ESC>Yrc
  Serial.print( CHAR_ESC "Y" ) ;
  Serial.print((unsigned char)(32 + row)) ;
  Serial.print((unsigned char)(32 + col)) ;
  _xloc = col;
  _yloc = row;
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

void Tellymate::cursorhome()
{
  Serial.print( CHAR_ESC "H" );
  _xloc = 0;
  _yloc = 0;
}

void Tellymate::blockcursor( bool value )
{
  if( value ){
    Serial.print( CHAR_ESC "x4" );
  }
  else{
    Serial.print( CHAR_ESC "y4" );
  }
}

void Tellymate::lineoverflow( bool value )
{
  if( value ){
    Serial.print( CHAR_ESC "v" );
  }
  else{
    Serial.print( CHAR_ESC "w" );
  }
}

void Tellymate::printchar( unsigned char char2print )
{
  Serial.print( char2print );
}

void Tellymate::putchar( int xloc, int yloc, unsigned char char2print )
{
  cursorto( yloc, xloc );
  Serial.print( char2print );
}

void Tellymate::print( char pstring[])
{
  Serial.print( pstring );
}

void Tellymate::println( char pstring[])
{
  Serial.println( pstring );
}

void Tellymate::fontdoubleheight( int row )
{
  if( row == -1 ){
    for( int i = 0; i < 25; i++ ){
      cursorto( i, 0 );
      Serial.print( CHAR_ESC "_0");
    }
  }
  else{
    cursorto( row, 0 );
    Serial.print( CHAR_ESC "_2");
    cursorto( row+1, 0 );
    Serial.print( CHAR_ESC "_3");
  }
}

void Tellymate::fontdoublewidth( int row )
{
  if( row == -1 ){
    for( int i = 0; i < 25; i++ ){
      cursorto( i, 0 );
      Serial.print( CHAR_ESC "_1");
    }
  }
  else{
    cursorto( row, 0 );
    Serial.print( CHAR_ESC "_1");
  }
}

void Tellymate::fontnormal( int row )
{
  if( row == -1 ){
    for( int i = 0; i < 25; i++ ){
      cursorto( i, 0 );
      Serial.print( CHAR_ESC "_0");
    }
  }
  else{
    cursorto( row, 0 );
    Serial.print( CHAR_ESC "_0");
  }
}

void Tellymate::box( int width, int height, int startx, int starty )
{
  cursorto( starty, startx );
  printchar( 218 );
  int xspace = width - 2;
  int yspace = height - 2;
  for( int i = 0; i < xspace; i++ )
  {
    cursorright(1);
    printchar( 196 );
  }
  cursorright(1);
  printchar( 191 );
  for( int i = 0; i < yspace; i++ )
  {
    cursordown(1);
    printchar( 179 );
  }
  cursordown(1);
  printchar( 217 );
  for( int i = 0; i < xspace; i++ )
  {
    cursorleft(1);
    printchar( 196 );
  }
  cursorleft(1);
  printchar( 192 );
  for( int i = 0; i < yspace; i++ )
  {
    cursorup(1);
    printchar( 179 );
  }
}
