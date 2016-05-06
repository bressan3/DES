# DES
Implementation of the DES encryption algorithm in C. <b>Works only for 64 bit long keys max</b>.

This version of the DES algorithm has been implemented following these steps: [The DES Algorithm Illustrated] 
(http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm).

#Intalling

- Go to the main.c folder
`$cd /path/to/main.c`

- Compile main.c using GCC
`$gcc main.c -o DES`


#Running DES
  
  
  - To encrypt
    
    - Go to the DES executale path:
    
      `$cd /path/to/DESexecutable`
    
    - Run the compiled DES program:
      
      `$./DES -e KEY_FILE MESSAGE_FILE`
      
  - To decrypt
    
    - Go to the DES executale path:
    
      `$cd /path/to/DESexecutable`
    
    - Run the compiled DES program:
    
      `$./DES -d KEY_FILE CYPHERTEXT_FILE`


