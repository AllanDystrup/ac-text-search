/*==========================================================================*/
/*						     <proj>\general.h								*/
/*              Revision 1.2 2025/12/02	11:00:00	Allan_Dystrup			*/
/*				Port to UBUNTU  on Win.10/WSL, Using CLion for Linux		*/
/*				Port to Windows 10 native, Using CLion for Windows			*/
/*==========================================================================*/


#ifndef GENERAL_H               /* Makes sure general.h is included once	*/

	#define GENERAL_H           /* Matching endif is at end of file.		*/

// Chose Build configuration (normal or debug)
//#define DEBUG	//******** DEBUG  ********/
#undef DEBUG	//******** NORMAL ********/
//#define MSDOS	//********  DOS   ********/
#undef MSDOS	//**** UNIX | WINDOWS ****/


	#ifdef  DEBUG
		#define PRIVATE
		#define D(x)     x
		#include <assert.h>
	#else
		#define PRIVATE static
		#define D(x)
		#define assert(x)
	#endif

	#define PUBLIC

	#ifdef MSDOS
		#define MS(x) x
		#define UX(x)
		#define ANSI
		#define _8086

	#else // UNIX or WINDOWS
		#define MS(x)
		#define UX(x) x
		#define UNIX
		#define O_BINARY 0      /* No binary input mode in UNIX open().     */
		#define far             /* Microsoft/Turbo keyword for an 8086      */
								/* 32-bit, far pointer. Ignore in UNIX.     */
		#define const           /* Ignore ANSI const and volatile keywords. */
		#define volatile
		#define memmove(d,s,n) bcopy(s,d,n)
		#define memcpy(d,s,n)  bcopy(s,d,n)

		extern long getpid();

		#define raise(sig) kill( (int)getpid(), sig )
		#define vfprintf(stream, fmt, argp) _doprnt( fmt, argp, stream )
		#define vprintf (fmt, argp) _doprnt( fmt, argp, stdout )
		//typedef long time_t;      /* for the VAX, may have to change this  */
		//typedef unsigned size_t;	/* for the VAX, may have to change this  */
		//extern  char *strdup();   /* Not tolerated by LINUX* /
		//typedef int void;			/* Not tolerated by LINUX* /
	#endif  /* MSDOS - UNIX */

	#ifdef ANSI                 	/* If ANSI is defined, put arg lists into */
		#define P(x)  x           	/* function prototypes.                   */
		#define VA_LIST  ...      	/* and use ellipsis if var number of args */

	#else// Previous to ANSI
	#   define P(x)  ()    		    /* Else, discard arg lists and translate    */
	#   define void  char			/* void keyword to int.                     */
	#   define VA_LIST _a_r_g_s     /* don't use ellipsis                       */
	#endif  /* ANSI - Not ANSI*/

	/* SEG(p)  Evaluates to the segment portion of an 8086 address.		*/
	/* OFF(p)  Evaluates to the offset portion of an 8086 address.		*/
	/* PHYS(p) Evaluates to a long holding a physical address			*/
	#   ifdef _8086
	#      define SEG(p)	( ((unsigned *)&(p))[1] )
	#      define OFF(p)	( ((unsigned *)&(p))[0] )
	#      define PHYS(p)	(((unsigned long)OFF(p)) + ((unsigned long)SEG(p) << 4))

	#   else // NOT Intel
	#      define PHYS(p)	(p)
	#   endif  /* _8086  */

	/* NUMELE(array)		Evaluates to the array size in elements
	*  LASTELE(array)		Evaluates to a pointer to the last element
	*  INBOUNDS(array,p)	Evaluates to true if p points into the array.
	*  RANGE(a,b,c)			Evaluates to true if a <= b <= c
	*  max(a,b)				Evaluates to a or b, whichever is larger
	*  min(a,b)				Evaluates to a or b, whichever is smaller
	*  NBITS(type)			Returns # of bits in a variable of the indicated type;
	*  MAXINT				Evaluates to the value of the largest signed integer
	*/

	#define NUMELE(a)      (sizeof(a)/sizeof(*(a)))
	#define LASTELE(a)     ((a) + (NUMELE(a)-1))
	#define TOOHIGH(a,p)   ((p) - (a) > (NUMELE(a) - 1))
	#define TOOLOW(a,p)    ((p) - (a) <  0 )
	#define INBOUNDS(a,p)  ( ! (TOOHIGH(a,p) || TOOLOW(a,p)) )
	#define IS(t,x) (((t)1 << (x))!=0)	/* valuate true if the width of a    */
                                        /* var of type of t is < x. The != 0 */
                                        /* assures that the answer is 1 or 0 */
	#define NBITS(t)	(4 * (1  + _IS(t, 4) + _IS(t, 8) + _IS(t,12) + _IS(t,16) \
						+ _IS(t,20) + _IS(t,24) + _IS(t,28) + _IS(t,32) ) )
	#define MAXINT (((unsigned)~0) >> 1)


	#ifndef max
		#define max(a,b)    ( ((a) > (b)) ? (a) : (b))
	#endif

	#ifndef min
		#define min(a,b)     ( ((a) < (b)) ? (a) : (b))
	#endif

	#define RANGE(a,b,c)    ( (a) <= (b) && (b) <= (c) )
	#define ISEVEN(n)       ( ((n) & 01) > 0 ? 0 : 1 )

    /* derived types, cf. MS Windows & OS/2 */
    typedef unsigned char	BYTE;
    typedef unsigned short	FLAG;
    typedef unsigned int	WORD;
    typedef long			LONG;
    typedef unsigned long	DWORD;

	#define VOID   void
	#define SHORT  short
	#define TRUE  (FLAG) 1
	#define FALSE (FLAG) 0


#endif 	/* #ifdef GENERAL_H */

/* End of module general.h                                                 */
/*=========================================================================*/
