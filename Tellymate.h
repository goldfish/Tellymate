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

*/

#ifndef Tellymate_h
#define Tellymate_h

#define CHAR_ESC "\x1B"

#define MAX_X 38
#define MAX_Y 25

//#include "WProgram.h"
#include <inttypes.h>

class Tellymate
{
  public:
    Tellymate( long );
    void init();
    void diagnostic();
    void clearscreen();
    void cursoron();
    void cursoroff();
    void cursorto( uint8_t, uint8_t );
    void cursorup( int );
    void cursordown( int );
    void cursorleft( int );
    void cursorright( int );
    void cursorhome();
    void newline();
    void blockcursor( bool );
    void lineoverflow( bool );
    void print( char[] );
    void println( char[] );
    void fontdoubleheight( int );
    void fontdoublewidth( int );
    void fontlarge( int );
    void fontnormal( int );
    void fill( int, int, int, int, unsigned char );
    void box( int, int, int, int );
    void printchar( unsigned char );
    void putchar( int, int, unsigned char);
  private:
    long _serialRate;
    int _xloc;
    int _yloc;
};

#endif
