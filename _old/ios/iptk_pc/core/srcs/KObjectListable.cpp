/******************************************************************************
 * Listable object class implementation
 ******************************************************************************
 * Atlantis (c) 2005 FunPause
 ******************************************************************************
 * $Id: KObjectListable.cpp,v 1.2 2005/06/06 16:01:03 emarty Exp $
 ******************************************************************************
 */

#include "KObjectListable.h"
#include "KDebug.h"

/**** PUBLIC ****/

/** Constructor */
KObjectListable::KObjectListable (void) :
      _lpListNext (NULL),
      _lpListPred (NULL) {
}

/** Destructor */
KObjectListable::~KObjectListable () {
   /* Make sure it isn't still inserted in a list */
//   KAssert ((_lpListNext == NULL) && (_lpListPred == NULL));
}

/** Copy constructor */
KObjectListable::KObjectListable (const KObjectListable &refObject) {
//	&refObject = &refObject ;
   /* Don't copy links to the list */
   _lpListNext = NULL;
   _lpListPred = NULL;
}

/** Copy operator */
KObjectListable &KObjectListable::operator = (KObjectListable refObject) {
   if (this != &refObject) {
      /* Call assignment operator for KObjectBase */
      this->KObjectListable::operator = (refObject);

      /* Don't copy links to the list */
      _lpListNext = NULL;
      _lpListPred = NULL;
   }

   return *this;
}
