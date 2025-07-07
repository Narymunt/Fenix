/******************************************************************************
 * Implementation for handling tape archives (.tar) of resources
 ******************************************************************************
 * (c) 2005 FunPause
 ******************************************************************************
 * $Id: KResourceArchive.cpp,v 1.2 2005/03/14 17:10:50 emarty Exp $
 ******************************************************************************
 */

#include "KResourceArchive.h"

/**** PUBLIC ****/

/** Constructor */
KResourceArchive::KResourceArchive () {
}

/** Destructor */
KResourceArchive::~KResourceArchive () {
}

/** Open archive from name
 *
 * \param lpszArchiveName archive name
 *
 * \return K_RES_OK for success,
 *         K_RES_NOTFOUND if archive cannot be opened,
 *			  K_RES_STATE if an archive is already opened.
 */

KResourceResult KResourceArchive::open (const char *lpszArchiveName) {
   return KResource::open (lpszArchiveName, K_RES_READ);
}

/**
 * Open resource contained in the currently open archive for reading.
 *
 * \param lpszResName resource name
 * \param lpResource instance to open into, if successful
 *
 * \return K_RES_OK for success,
 *         K_RES_NOTFOUND if resource cannot be opened for reading,
 *         K_RES_STATE if failed due to no archive being currently open,
 *         K_RES_IOERR if read error
 */
 
KResourceResult KResourceArchive::openResource (const char *lpszResName,
                                                KResource *lpResource) {
   KResourceResult result;
   k_tar_record record;
   char szArchiveResName[K_MAXPATH];

   strncpy (szArchiveResName, lpszResName, K_MAXPATH - 1);
   szArchiveResName[K_MAXPATH - 1] = '\0';

   /* Convert win32 paths to unix (tar) format */
   for (int i = 0; (i < K_MAXPATH) && (szArchiveResName[i]); i++)
      if (szArchiveResName[i] == '\\')
         szArchiveResName[i] = '/';

   /* Rewind to beginning of archive */
   result = seek (K_RES_BEGIN, 0);
   if (result != K_RES_OK) return result;

   /* Now look for specified resource */
   do {
      unsigned int nSize, i;
      bool bIsEnd;

      result = read (&record, RECORDSIZE);
      if (result != K_RES_OK) return result;

      /* Check if this is the end of the archive */
      for (i = 0, bIsEnd = true; (i < RECORDSIZE) && (bIsEnd); i++)
         if (record.charptr[i]) bIsEnd = false;
      if (bIsEnd) return K_RES_NOTFOUND;

      /* Convert size from octal ascii */
      nSize = strtoul (record.header.size, NULL, 8);

      if (((record.header.linkflag == LF_OLDNORMAL) ||
           (record.header.linkflag == LF_NORMAL)) &&
          (!K_strncasecmp (szArchiveResName, record.header.name, NAMSIZ))) {

         /* Match. Open resource at current archive's position */
         return lpResource->open (this, nSize);
      }

      /* Skip over this resource, to next record */
      nSize = (nSize + (RECORDSIZE - 1)) & ~(RECORDSIZE - 1);
      result = seek (K_RES_CURRENT, nSize);
   }
   while (result == K_RES_OK);

   return result;
}
