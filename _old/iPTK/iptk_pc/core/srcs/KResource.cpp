/******************************************************************************
 * resource manager class implementation
 ******************************************************************************
 * (c) 2005 FunPause
 ******************************************************************************
 * $Id:$
 ******************************************************************************
 */

#include "KResource.h"
#include "KResourceArchive.h"
#include	"KMiscTools.h"

/**** PUBLIC ****/

/** Constructor */
KResource::KResource () :
	   _lpFile (NULL),
      _bFileInArchive (false),
	   _nMode (K_RES_CLOSED),
      _nBeginPos (0),
      _nSize (0) {
}

/** Destructor */
KResource::~KResource () {
	/* Close open resource if needed */
	close ();
}

/** Open resource from name
 *
 * \param lpszResName resource name
 * \param nMode open mode (K_RES_READ or K_RES_WRITE)
 *
 * \return K_RES_OK for success,
 *         K_RES_NOTFOUND if resource cannot be opened for reading,
 *         K_RES_CREATERR if resource cannot be created for writing,
 *			  K_RES_STATE if resource is already opened,
 *			  K_RES_PARAM if mode is invalid.
 */

KResourceResult KResource::open (const char *lpszResName,	KResourceMode nMode) 
{
   KResource *lpArchive;
   bool bGotNext;
  static	char		inResourceFilename[260]  ;
  static	char		regularFilename[260]  ;
	char		current[260] ="";


	//we need to store the filenames because there's only 1 buffer for makefilepath, 
	//so that would modify  the content of the pointer passed in that function
		strcpy( inResourceFilename , lpszResName ) ;
		strcpy( regularFilename , lpszResName ) ;
	
	strcpy( current , KMiscTools::getCurrentPath( ) );	
	strlwr( current ) ;
	
//	
	//is the makeFilepath path in the filename ?
	if ( strncmp(regularFilename , current , strlen( current) ) == 0 )
	{
		//yes, so only take what is needed
		sprintf( inResourceFilename , "%s", regularFilename+strlen( current)+1 ) ;
		
	}
	else
	{
		//no so take everything
		strcpy( inResourceFilename , lpszResName ) ;
	}
	
	
	/* One resource can be open at a time per instance */
	if (_nMode != K_RES_CLOSED) return K_RES_STATE;

   /* Read mode only */
   if (nMode != K_RES_READ) return K_RES_PARAM;

   /* Try first to open the resource from an archive */
   bGotNext = _lArchives.getHead (lpArchive);
   while (bGotNext) 
   {
      if (lpArchive->openResource (inResourceFilename,  (KResource *) this) == K_RES_OK)
      {      
         return K_RES_OK;
	 }
	
      bGotNext = _lArchives.getNext (lpArchive);
   }

	
   /* Open file. */
   _lpFile = fopen (regularFilename, "rb");
   if (_lpFile == NULL) {
      /* Error opening it */
      return K_RES_NOTFOUND;
   }

	/* Success */
	_nMode = nMode;
   _nBeginPos = 0;
   _nSize = 0;
	return K_RES_OK;
}

/** Open resource for reading from archive file. All resources opened
 * from the same file handle share the same read position.
 *
 * \param lpResource resource of archive file, open for reading,
 *              positioned on first byte of resource to be opened
 * \param nSize size of resource in bytes
 *
 * \return K_RES_OK for success,
 *			  K_RES_STATE if resource is already opened, or supplied resource
 *                     is not open for reading,
 *         K_RES_IOERR if I/O error
 */

KResourceResult KResource::open (KResource *lpResource,    unsigned int nSize) 
{
   KResource *lpResourcePf;


	/* One resource can be open at a time per instance */
   lpResourcePf = (KResource *) lpResource;
	if (_nMode != K_RES_CLOSED) return K_RES_STATE;
   if (lpResourcePf->_nMode != K_RES_READ) return K_RES_STATE;

   /* Steal stream */
   _lpFile = lpResourcePf->_lpFile; 
   if (_lpFile == NULL) {
      /* Failed */
      return K_RES_IOERR;
   }

   _bFileInArchive = true;
   _nMode = K_RES_READ;
   _nBeginPos = ftell (lpResourcePf->_lpFile);
   _nSize = nSize;
   return K_RES_OK;
}

/** Close currently open resource */

void KResource::close (void) {
	if (_nMode != K_RES_CLOSED) {
      if (!_bFileInArchive)
         fclose (_lpFile);

		_lpFile = NULL;
      _bFileInArchive = false;
		_nMode = K_RES_CLOSED;
      _nBeginPos = 0;
      _nSize = 0;
	}
}

/** Change position in open resource, when reading. A subsequent
 * read() will return data starting on the first byte of the specified
 * new position.
 *
 * \param nWhence how to interpret position (K_RES_BEGIN,CURRENT or END)
 * \param nPos new position
 *
 * \return K_RES_OK for success,
 *         K_RES_STATE if failed due to no resource being currently open
 *                     for reading,
 *			  K_RES_PARAM if nWhence is invalid.
 */

KResourceResult KResource::seek (KResourceWhence nWhence,
                                  int nPos) {
   int nMethod;

   if (_nMode != K_RES_READ) return K_RES_STATE;

   switch (nWhence) {
   case K_RES_BEGIN:
      nMethod = SEEK_SET;
      nPos   += _nBeginPos;
      break;

   case K_RES_CURRENT:
      nMethod = SEEK_CUR;
      break;

   case K_RES_END:
      nMethod = SEEK_END;
      if (_nSize) {
         nMethod = SEEK_SET;
         nPos = _nSize + _nBeginPos - nPos;
      }
      break;

   default:
      return K_RES_PARAM;
   }

   fseek (_lpFile, (long) nPos, nMethod);
   return K_RES_OK;
}

/** Tell position in open resource, when reading.
 *
 * \param nPos returned current position
 *
 * \return K_RES_OK for success,
 *         K_RES_STATE if failed due to no resource being currently open
 *                     for reading,
 */

KResourceResult KResource::tell (int &nPos) {
   if (_nMode != K_RES_READ) return K_RES_STATE;

   nPos = (int) ftell (_lpFile);
	nPos -= _nBeginPos;
	return K_RES_OK;
}

/** Read data from open resource
 *
 * \param lpBuffer pointer to first byte of buffer to read into
 * \param nBytes size of data to be read, in bytes
 *
 * \return K_RES_OK for success,
 *         K_RES_STATE if failed due to no resource being currently open,
 *			  K_RES_MODE if failed due to resource being open for writing,
 *         K_RES_IOERR if read error
 */

KResourceResult KResource::read (void *lpBuffer, size_t nBytes) {
	unsigned long nRead = 0;
	int result;

	/* Check that resource is open for reading */
	if (_nMode == K_RES_CLOSED) return K_RES_STATE;
	if (_nMode != K_RES_READ)   return K_RES_MODE;
	if (!nBytes)                return K_RES_IOERR;

	/* Read data */
   result = (int) fread (lpBuffer, 1, nBytes, _lpFile);
	if ((result >= 0) && (result == nBytes)) return K_RES_OK;
	return K_RES_IOERR;
}

/**
 * Add file to the list of archives that are looked up when a resource
 * is opened by Open(), before individual resource files are looked up.
 * This method enables the final product to package resources in one or
 * more archive files. The archive file remains open for the lifetime
 * of the product's process.
 *
 * \param lpszFileName name of archive file to be added
 *
 * \return K_RES_OK for success,
 *         K_RES_NOTFOUND if archive cannot be opened for reading.
 */

KResourceResult KResource::addArchive (const char *lpszFileName) {
   KResourceArchive *lpArchive = new KResourceArchive ();
   KResourceResult result;

   result = lpArchive->open (lpszFileName);
   if (result != K_RES_OK) return result;

   /* Success. Add to list. */
   _lArchives.addToTail (lpArchive);
   return K_RES_OK;
}

/** List of archives to open resources from, before looking at files */
KList<KResource> KResource::_lArchives;
