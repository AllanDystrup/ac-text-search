--------------------------------------------------------------------------
   Aho & Corasic algorithm for searching a text for several fixed substrings. 
--------------------------------------------------------------------------

THE PROJECT:
-
   This project implements a simple "Finite State Automaton" (*FSA*) to locate all occurences of any of a number of keywords in a string of text (such as a file...). 
   
   The keywords may be combined by boolean operators (cf. module bool.h/c), and the parsing of the search phrase input string is implemented by a simple compiler that emits intermediate code in reverse polish format for interpretation on a simple stack machine (cf. stack.h/c). Errors are handled by a separate module (error.h/c).
   
All conceptually very interesting (I think...:-).


THE ALGORITHM:
-
   FIRST constructs (configurable at runtime as input parameter)
   -N : a Nondeterministic Finite State Automaton (*NFSA*), or 
   -D : a Deterministic Finite State Automaton (*DFSA*) for pattern matching from the keywords; 
        Construction of the NFSA/DFSA takes time proportional to the sum of the lengths of the keywords, ie. time complexity O(n). 
        
   THEN uses the NFSA or DFSA to process the text in *one* pass; The number of state transitions made by the (D|N)FSA in processing the text is independent of the number of keywords.

   The output from the program are all lines in the input string / file that match the given search phrase.  


USAGE:
-
     ac [<options>] <boolexpr> <file>, where :
     
      <options>   -N to force a NFSA search (default DFSA)
                  -U to force a case-INsensitive search
                  
      <boolexpr>   is a boolean expression of search phrases
                  example: This&^(That/Those)
                  Cf module bool.c:
                     '/'      /* boolean OR       */
                     '%'      /* boolean XOR      */
                     '&'      /* boolean AND      */
                     '^'      /* boolean NOT      */ 
                     '('      /* left parenthesis */
                     ')'      /* right parantesis */ 
                     ':'      /* quoted string    */
                     '\\'     /* escape next char */ 
                  
      <file>     is the file to search for boolexpr, line by line.


DISCLAIMER   (aka: "A tour down memory lane...")
-
This code was developed in the start of the 1990'ies, and it includes macros to make it compile on a PC and run on different target architectures, such as MSDOS, OS/2 (!) and POSIX UNIX.

The C-code was made fully compliant to K&R C (1978) and ANSI C (1989) standards, as checked by Lint, and it has been included in a commercial product that was deployed to and ran on several DOS and UNIX versions, *without any failures* (Excluding one, which was caused by a non-compliant UNIX implementation. -- And was easily corrected :-).
     
For fun, I have now ported this ancient C-code to a modern platform (UBUNTU Linux on Windows-10 WSL), using gcc v.13.3 (Ubuntu 13.3). 
The gcc v.13 compiler is complient with the ISO/IEC 9899:2024 standard, as can be checked by a modern Tidy syntax verifyer (e.g. the built-in Clang-Tidy v.21 in CLion).

Running gcc v.13 on ancient K&R/ANSI C-code did result in a few errors (such as: a null-pointer now cannot be treated as integer 0, as in K&R C) but circumventing this, I have made the code compile and run on UBUNTU using gcc. The Tidy syntax checker still throws a ton of "warnings", but to fully silence these would require a serious rewrite of the code, -- and that was not the scope for this project.
