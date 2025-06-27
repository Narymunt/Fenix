#include <stdio.h>
#include "KDataExchange.h"

//----------------------------------
//|                                |
//|-------KDataItemContainer-------|
//|                                |
//----------------------------------
KDataItemContainer::KDataItemContainer( const KDataItemContainer & rkDataItem ) 
{
	// NA
//	#pragma unused( rkDataItem )
}

KDataItemContainer &KDataItemContainer::operator=( const KDataItemContainer & rkDataItem ) 
{
	// NA
//	#pragma unused( rkDataItem )
	return *this ;
}

KDataItemContainer::KDataItemContainer( ) 
{
	_next = NULL ;
	_prev = NULL ;
	_pkDataItem = NULL ;
}

KDataItemContainer::KDataItemContainer( KDataItem * pkDataItem ) 
{
	_next = NULL ;
	_prev = NULL ;
	_pkDataItem = pkDataItem ;
}

KDataItemContainer::KDataItemContainer( KDataItemContainer *pkNext , KDataItem * pkDataItem ) 
{
	_next = pkNext ;
	_prev = NULL ;
	_pkDataItem = pkDataItem ;
}

KDataItemContainer::KDataItemContainer( KDataItemContainer *pkPrev , KDataItemContainer *pkNext , KDataItem * pkDataItem ) 
{
	_next = pkNext ;
	_prev = pkPrev ;
	_pkDataItem = pkDataItem ;
}

KDataItemContainer::~KDataItemContainer( ) 
{
	// NA
}

void										KDataItemContainer::setKDataItem( KDataItem * item )
{
	_pkDataItem = item ;
}

void										KDataItemContainer::setNext( KDataItemContainer * pkNext ) 
{
	_next = pkNext ;
}

void										KDataItemContainer::setPrev( KDataItemContainer * pkPrev ) 
{
	_prev = pkPrev ;
}

KDataItem * KDataItemContainer::getKDataItem()
{
	return _pkDataItem ;
}

KDataItemContainer	*		KDataItemContainer::getNext( ) 
{
	return _next ;
}

KDataItemContainer	*		KDataItemContainer::getPrev( ) 
{
	return _prev ;
}




//-----------------------------
//|                           |
//|-------KDataExchange-------|
//|                           |
//-----------------------------
KDataExchange::KDataExchange( int stackSize )
{
	_stacksize = stackSize ;
	_head = _foot = NULL ;
	_count = 0 ;
}

KDataExchange::~KDataExchange()
{
}

void KDataExchange::push( KDataItem *item )
{
	if ( _head == NULL )
	{
		_head = new KDataItemContainer( item ) ;
		_foot = _head ;
		_count ++ ;
	}
	else
	{
		if ( _count < _stacksize )
		{
			_foot -> setNext( new KDataItemContainer( _foot, NULL , item ) );
			_foot = _foot -> getNext() ;
			_count ++ ;
		}
		else
		{
			_foot -> setKDataItem( item ) ;
		}
	}
	printf("PUSH KDataExchange::_count(%d)\n",_count ); 
}

KDataItem * KDataExchange::peek( )
{
	if ( _head != NULL )
	{
		return _head -> getKDataItem( ) ;
	}
	return NULL ;
}

KDataItem * KDataExchange::pop( )
{
	KDataItemContainer 	* pkToDelete ;
	KDataItem 					*	pkItem ;
	
	pkToDelete = _head ;
	_head = _head -> getNext();
	pkItem = pkToDelete -> getKDataItem() ;
	delete pkToDelete ;
	_count -- ;
	printf("POP KDataExchange::_count(%d)\n",_count ); 
	return pkItem ;
}
