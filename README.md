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


TRACE:
-
If you compile the sources with #define DEBUG set (in general.h), the program will output a trace of the execution, showing - so to speak - 'the cogwheels turning' for the Finite State Automaton, the boolean interpreter and the abstract stack machine. This can also be a way to get a deeper insight into the algorithm, as well as a means of pinpointing the location of a runtime error for further debugging.

A version of the *ac* program compiled with 'DEBUG' enabled is included as: *ac-d*, and an example of the output from *ac-d* is captured in: *'ac.out'*.


DISCLAIMER   (aka: "A tour down memory lane...")
-
This code was developed in the start of the 1990'ies, and it includes macros to make it compile on a PC and run on different target architectures, such as MSDOS, OS/2 (!) and POSIX UNIX.

The C-code was made fully compliant to K&R C (1978) and ANSI C (1989) standards, as checked by Lint, and it has been included in a commercial product that was deployed to and ran on several DOS and UNIX versions, *without any failures* (Excluding one, which was caused by a non-compliant UNIX implementation. -- And was easily corrected :-).
     
For fun, I have now ported this ancient C-code to a modern platform (UBUNTU Linux on Windows-10 WSL), using gcc v.13.3 (Ubuntu 13.3). 
The gcc v.13 compiler is complient with the ISO/IEC 9899:2024 standard, as can be checked by a modern Tidy syntax verifyer (e.g. the built-in Clang-Tidy v.21 in CLion).

Running gcc v.13 on ancient K&R/ANSI C-code did result in a few errors (such as: contrary to K&R C, in 'modern C' a null-pointer cannot be treated as an integer value 0) but circumventing this, I have made the code compile and run on UBUNTU using gcc. The Tidy syntax checker will still throw a ton of "warnings", but to fully silence these would require a serious rewrite of the code, -- and that was not the scope for this project.
