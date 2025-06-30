// Released under MIT License
/*
 Copyright (c) 2010 by Julien Meyer. Web: http://www.jmApp.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "KWeb.h"
#include "Foundation/Foundation.h"

#import <UIKit/UIKit.h>

KWeb::KWeb( ) 
{
	//hInternet = 0 ;		//handle internet
	//hIurl	= 0 ;
	_dataBuffer = NULL ;
	_dataBufferSize = 0 ;
}

KWeb::~KWeb( ) 
{
	freeInternetHandles( ) ;
	freeDataBuffer( ) ;
}

unsigned long KWeb::getBufferSize( void ) 
{
	return	_dataBufferSize ;
}

void KWeb::freeDataBuffer( void ) 
{
	if ( _dataBuffer != NULL )
	{
		delete	[]	_dataBuffer ;
		_dataBuffer 		= NULL ;
		_dataBufferSize 	= 0 ;
	}
}

void KWeb::freeInternetHandles( void ) 
{
}

void KWeb::showURL( char	*paramURL ) 
{
	NSString *urlstring = [NSString stringWithUTF8String: paramURL];
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString: urlstring]];
}

char * KWeb::callURL( char	*paramURL , bool 	asynchronous ) 
{
	NSString *myRequestString = [NSString stringWithUTF8String: paramURL];
	NSMutableURLRequest *request = [ [ NSMutableURLRequest alloc ] initWithURL: [ NSURL URLWithString: myRequestString ] ]; 
	[ request setHTTPMethod: @"POST" ];

	NSData *returnData = [ NSURLConnection sendSynchronousRequest: request returningResponse: nil error: nil ];
	
	if(returnData!=0)
	{
		unsigned long	bufferSize=[returnData length]+1;
		_dataBuffer = new		char[bufferSize] ;
		memset( _dataBuffer , 0 , bufferSize ) ;
			
		[returnData getBytes:_dataBuffer];
		_dataBufferSize=bufferSize;
		return _dataBuffer;
	}
	[request release]; // Correction PTRO
	return 0;
}

