#ifndef _ENTRY_H
#define _ENTRY_H

/*
*   INCLUDE FILES
*/
#include "general.h"  /* must always come first */
#include "vstring.h"


#include <stdio.h>
/*
*   MACROS
*/
#define WHOLE_FILE  -1L

/*
*   DATA DECLARATIONS
*/

typedef struct sTagFields {
	unsigned int count;        /* number of additional extension flags */
	const char *const *label;  /* list of labels for extension flags */
	const char *const *value;  /* list of values for extension flags */
} tagFields;

/*  Information about the current tag candidate.
 */
typedef struct sTagEntryInfo {
	boolean     lineNumberEntry;  /* pattern or line number entry */
	unsigned long lineNumber;     /* line number of tag */
	fpos_t      filePosition;     /* file position of line containing tag */
	boolean     isFileScope;      /* is tag visibile only within source file? */
	boolean     isFileEntry;      /* is this just an entry for a file name? */
	boolean     truncateLine;     /* truncate tag line at end of tag name? */
	const char* language;         /* language of source file */
	const char *sourceFileName;   /* name of source file */
	const char *name;             /* name of the tag */
	const char *kindName;         /* kind of tag */
	char        kind;             /* single character representation of kind */
	struct {
		const char* access;
		const char* fileScope;
		const char* implementation;
		const char* inheritance;
		const char* scope [2];    /* value and key */
		const char* signature;

		/* type (union/struct/etc.) and name for a variable or typedef. */
		const char* typeRef [2];  /* e.g., "struct" and struct name */
	} extensionFields;  /* list of extension fields*/
} tagEntryInfo;

typedef struct  sTagEntryListItem {
	tagEntryInfo tag;
	struct sTagEntryListItem *next;
	} sTagEntryListItem ; 

//  Global pointers to entrys in the list
extern sTagEntryListItem* firstTagEntry ;  //for return it as result
extern sTagEntryListItem* lastTagEntry ;   //for adding entryes

/*
*   FUNCTION PROTOTYPES
*/
extern void makeTagEntry (const tagEntryInfo *const tag);
extern void initTagEntry (tagEntryInfo *const e, const char *const name);
void addEntryToList (const tagEntryInfo *const tag) ;

#endif  /* _ENTRY_H */

/* vi:set tabstop=4 shiftwidth=4: */
