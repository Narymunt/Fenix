#include <string.h>
#include "KDataItem.h"

KDataItem::KDataItem( KStoreType kStoreType )
{
	_kStoreType = kStoreType ;
	_buffer = NULL ;
	_size = 0;
}


KDataItem::~KDataItem( )
{
	if ( (kCopyData == _kStoreType) && (NULL != _buffer) )
	{
		delete[] _buffer ;
		_size = 0 ;
	}
}

KDataItem::KDataItem( const KDataItem & rkDataItem )
{
	if ( NULL != _buffer )
	{
		delete[] _buffer ;
	}
	_size = rkDataItem . _size ;
	_kStoreType = rkDataItem . _kStoreType ;
	_kPacketType = rkDataItem . _kPacketType ;
	_buffer = new char[ _size ] ;
	if ( _buffer == NULL )
	{
		return ;
	}
	memcpy( _buffer , rkDataItem . _buffer , _size ) ;
}

KDataItem & KDataItem::operator=( const KDataItem & rkDataItem )
{
	if ( NULL != _buffer )
	{
		delete[] _buffer ;
	}
	_size = rkDataItem . _size ;
	_kStoreType = rkDataItem . _kStoreType ;
	_kPacketType = rkDataItem . _kPacketType ;
	_buffer = new char[ _size ] ;
	if ( _buffer != NULL )		 
	{
		memcpy( _buffer , rkDataItem . _buffer , _size ) ;
	}
	return *this ;	
}

void KDataItem::set( KPacketType kPacketType, void *buffer, long size )
{
	_size   = size ;
	_kPacketType = kPacketType ;
	
	if ( kCopyData == _kStoreType )
	{
		if ( NULL == _buffer )
		{
			_buffer = new char[ _size ] ;		
		}
		memcpy( _buffer , buffer , size ) ;
	}
	
	else
	{
		_buffer = (char*)buffer ;
	}
}

void *KDataItem::get()
{
	return (void*)_buffer ;
}

long KDataItem::getSize()
{
	return _size ;
}

KPacketType KDataItem::getPacketType()
{
	return _kPacketType ;
}

bool KDataItem::isUdpPacket()
{
	return _kPacketType == kUdp ;
}

bool KDataItem::isTcpPacket()
{
	return _kPacketType == kTcp ;
}

