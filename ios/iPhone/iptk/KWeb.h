#ifndef		DEF_KWEB
#define		DEF_KWEB		

class		KWeb
{
private:

	char					*_dataBuffer ;
	unsigned long		_dataBufferSize	;
	
	char		*openURL( char	*urlStr , bool 	asynchronousFlags );
	void		freeInternetHandles( void );
	void		freeDataBuffer( void );
		
	
public:
	
	KWeb( ) ;
	~KWeb( ) ;
	
	char						*callURL( char	*urlStr , bool 	asynchronousFlags );
	void						showURL( char	*urlStr );
	unsigned long		getBufferSize( void );
	
};

#endif
