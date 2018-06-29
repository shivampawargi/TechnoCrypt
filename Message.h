/*

	Message.h provides an array of predefined messages.
	These messages have been assigned enum indexes in Techno_crypt.cpp
	enum name : msgs
	enum msgs with the respective indexes are used to display these messages.

*/


#include<iostream>
using namespace std;


const char* msg[]=
{
	"\nNo Valid Input filename given\nShould be immediately followed after -i\n\n",
	"\nError opening the input file\n\n",
	"\nError opening the output file\n\n",
	"\nInsufficient Arguments\n\n",
	"\nAlgorithm to be used for encryption not specified\nShould be immediately followed after -algo\nChoose from : \n alfa , beta , gama , tita , dlta\n\n",
	"\nAlgorithm name incorrect\nChoose from :\n alfa , beta , gama , tita , dlta\n\n",
	"\nWhether to Encrypt or Decrypt not specified ( -e : encryption / -d : decryption )\n\n",
	"\nValid Output Filename must be given\nShould be immediately followed after -o\n\n",
	"\nAlfa Encryption done successfully !\n\n",
	"\nBeta Encryption done successfully !\n\n",
	"\nGamma Encryption done successfully !\n\n",
	"\nTheta Encryption done successfully !\n\n",
	"\nDelta Encryption done successfully !\n\n",
	"\nFile Decrypted successfully\n\n",
	"\nGamma Encrytion has 2 versions :\n\n",
	"\nChoose from : \n1) Version 1 \n2) Version 2 \n",
	"\nPlease enter the Version Number : ",
	"\nENTER --help FOR MORE HELP\n--help should be followed after ./a.out OR ./technocrypt\n\n",
	"\nThe Encryption used was Alfa Encryption\n\n",
	"\nThe Encryption used was Beta Encryption\n\n",
	"\nThe Encryption used was Gamma Version 1 Encryption\n\n",
	"\nThe Encryption used was Gamma Version 2 Encryption\n\n",
	"\nThe Encryption used was Theta Encryption\n\n",
	"\nThe Encryption used was Delta Encryption\n\n",
	"\nOutput Filename should not be same as Input Filename\n\n",
	"\nInvalid Arguments\n\n",
	"\nOutput File saved as ",
	"\nOutput File with the given name already exists\n\n",
	"\nSelect either encryption (-e) or decryption (-d) \nCannot select both simultaneously\n\n",
	"\nDuplicate arguments : -e is repeated\n\n",
	"\nDuplicate arguments : -d is repeated\n\n",
	"\nDuplicate arguments : -algo is repeated\n\n",
	"\nDuplicate arguments : -i is repeated\n\n",
	"\nDuplicate arguments : -o is repeated\n\n",
	"\nNo argument should follow < ./a.out --help >\n\n",
	"\n\nFirst argument has to be : ./a.out\nInput file name is necessary. Filename should be followed immediately after -i \n-e or -d should be specified. \n-e : for encryption\n-d : for decryption\nIf -e given : \nEncryption algorithm needs to be specified. \nAlgorithm can be chosen from : alfa / beta / gama / tita / dlta . Algorithm name should be immediately followed after -algo .\n\n\nIf -d given :\nNo need to give output file name.\n Output file name (if specified) should be specified immediately after -o \nIf no output filename specified, the resultant outputfile will be saved as technoOut.txt \n\n\nIdeal command line argument structure :\n\nFor Encryption : \n\n./a.out -i <inputfilename.txt> -o <outputfilename.txt> -e -algo <algorithm>\n\nFor Decryption :\n\n./a.out -i <inputfilename.txt> -d\n\n"
};

