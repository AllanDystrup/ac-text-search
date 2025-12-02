#============================================================================ 
#                           <PROJ>\BOOL\MAKEFILE 
#============================================================================ 
#  FUNCTION      "Plain vanilla" makefile for project bool : 
#                Boolean expression compiler. 
#  SYSTEM        Standard (ANSI/ISO) C. 
#                Tested on PC/MS DOS 5.0 (MSC 600A). 
#  SEE ALSO      Modules : ERROR.C, BOOL.C 
#  PROGRAMMER    Allan Dystrup. #  COPYRIGHT     (c) Allan Dystrup, 1991 
#  VERSION       $Header: d:/cwk/kf/bool/RCS/makefile 1.1 92/10/25 16:54:15 
#                Allan_Dystrup Exp Locker: Allan_Dystrup $ 
#                ------------------------------------------------------------- 
#                $Log: makefile $ 
#                Revision 1.1  92/10/25  16:54:15  Allan_Dystrup 
#                Initial revision 
#=============================================================================  

#============================================================================= 
# Directories and files 
#============================================================================= 
#HF 	=  	..\h\general.h  ..\h\stack.h ..\error\error.h  bool.h 
#CF 	=  	bool.c ..\error\error.c 
#OF 	=  	bool$O ..\error\error$O 

HF	= 	.\general.h .\stack.h .\error.h
CF 	=  	bool.c error.c 
OF 	=  	bool$O error$O 



#=============================================================================== 
# Compilation options 
#=============================================================================== 
# Normal 
#CFLAGS +=     /c /I..\h /I..\error /Za /Od /W4 
#LFLAGS +=  

# For CodeView 
# K&R 
#CFLAGS +=      /c /I..\h /I..\error /Zi /Od /W3 
# ANSI 
CFLAGS 	+= /c /I..\h /I..\error /Za /Zi /Od /W4 
LFLAGS 	+= /CO 


#============================================================================= 
# Dependencies 
#============================================================================= 


#============================================================================= 
# Make bool.exe : executable "MAIN-DEBUG" bool for test 
bool$E: makefile $(OF)       
		$(LD) $(LFLAGS) $(OF),$@,,;   


#============================================================================= 
# Make 	(1:linkable object / 2: linkable debug object / 3: main testdriver) 
bool$O:    $(HF) $(CF) 
		cp bool.c bool.s  
		$(CC) -c $(CFLAGS) bool.c 
		$(CC) -c $(CFLAGS) -DDEBUG bool.c 
		$(CC) -c $(CFLAGS) /Fo.\$@ -DMAIN -DDEBUG bool.c  

 #============================================================================= 
# Miscelaneous   
print : 

