# TechnoCrypt
C++ program that encrypts and decrypts a given text file.

The program uses Object Oriented Concepts, File Handling Concepts and Concepts of Localisation and Internationalisation.

This program uses two files :

1) Techno_crypt.cpp : This file includes the main logic. There are five encryption algorithms to choose from namely alfa, beta, gama, tita, dlta.
2) Message.h : This file is incuded in "Techno_crypt.cpp". This file provides an array of predefined messages. This is to implement the feature of Localisation and Internationalisation. Enum with the respective indexes are used to display these messages.

-------------------------------------------------------------------------------------------------------

Logic :

1) Five various encryption algorithms are provided, user can choose any one to encrypt the input file.
2) The encrypted output file is appended with a unique character for every algorithm, so that if the user now wishes to decrypt the file, he/she need not specify the algorithm. decrypt() function will identify the algorithm based on that character and decrypt accordingly.
3) The then generated output file will be in the original format.

-------------------------------------------------------------------------------------------------------

Steps for Running on Linux terminal :

1) g++ Techno_crypt.cpp

2) 
  For Encryption :

   ./a.out -i <inputfilename.txt> -o <outputfilename.txt> -e -algo

" Now that the fie is encrypted, you can decrypt it by giving the following command : "

  For Decryption :

  ./a.out -i <inputfilename.txt> -d

-------------------------------------------------------------------------------------------------------

The order of arguments is flexible so long as you follow the below convention.

  First argument has to be : ./a.out 
  Input file name is necessary. Filename should be followed immediately after -i 
  -e or -d should be specified.
  -e : for encryption
  -d : for decryption
  If -e given :
     Encryption algorithm needs to be specified. 
     Algorithm can be chosen from : alfa / beta / gama / tita / dlta . Algorithm name should be immediately followed after -algo .
  If -d given :
     No need to give output file name.
     Output file name (if specified) should be specified immediately after -o
  If no output filename specified, the resultant outputfile will be saved as technoOut.txt
  
  -------------------------------------------------------------------------------------------------------
