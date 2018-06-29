/*
	Techno_crypt.cpp
	
	Purpose : This program encrypts and decrypts a file.
	
	Input : file name, encryption/decryption, if encryption chosen-provide the algorithm.
	Output : Encrypted/Decrypted file.
	
*/

//------------------------------------------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string.h>
#include"Message.h"						//header providing the array of messages : msg[]

using namespace std;

/*
	Encrypt class provides the member functions 
	crypt_alpha() : Alfa Encryption
	crypt_beta() : Beta Encryption
	crypt_gamma() : Gamma Encryption
	crypt_theta() : Theta Encryption
	crypt_delta() : Delta Encryption
	decrypt() : Decryption

*/

class Encrypt
{
public:

	//Signature : (InputFile pointer, OutputFile pointer, Encrypt/Decrypt Flag,)
	
	void crypt_alpha(ifstream & fin,ofstream & fout,int flag);
	void crypt_beta(ifstream & fin,ofstream & fout,int flag);
	void crypt_gamma(ifstream & fin,ofstream & fout,int flag,int choice);  //Choice : select Gama Version
	void crypt_theta(ifstream & fin,ofstream & fout,int flag);
	void crypt_delta(ifstream & fin,ofstream & fout,int flag);
	void decrypt(ifstream & fin,ofstream & fout,int flag);

};

//-------------------------------------------------------------------------------------

/*

	crypt_alpha()
	
	Logic : 1's Complement of bits
	
	For Encryption : Encrypts the input file and writes 'A' in the beginning to denote Alfa Encryption
	
	For Decryption : Determines the Encryption used on the basis of First letter and then decrypts the file.
	
	Input : Input file pointer, output file pointer, flag(determines whether to encrypt or decrypt)
	
	Output : Output File

*/

void Encrypt::crypt_alpha(ifstream & fin,ofstream & fout,int flag)    	//Alfa Encryption
{
	char id,charin,charout;
	
	//if encryption, put 'A' in the beginning of output file
					
    if(flag==1)
    {
    	id='A';
    	fout.put(id);
    }
    
    //calculating size of file
    
    fin.seekg(0,ios::end);
	long int size=fin.tellg();
	fin.seekg(0,ios::beg);
	
	//if decryption, skip the first letter as it denotes the type of encryption used
    
    if(flag==2)
    {
    	fin.seekg(1,ios::beg);
    	size--;
    }
    
    //1's Complement (using EXOR)
    
	while(size>0)
	{
		fin.get(charin);
		charout=(charin^0xFF);		
		fout.put(charout);
		size--;
	}
	fin.close();
	fout.close();

}

//--------------------------------------------------------------------------------------

/*

	crypt_beta()
	
	Logic : Reversing all the bit positions in a byte by first performing nibble swap : hgfe dcba
	
	For Encryption : Encrypts the input file and writes 'B' in the beginning to denote Beta Encryption
	
	For Decryption : Determines the Encryption used on the basis of First letter and then decrypts the file.
	
	Input : Input file pointer, output file pointer, flag(determines whether to encrypt or decrypt)
	
	Output : Output File

*/


void Encrypt::crypt_beta(ifstream & fin,ofstream & fout,int flag)		//Beta Encryption
{
	char id,charin;
	
	//if encryption, put 'B' in the beginning of output file
	
	if(flag==1)
	{
		id='B';
		fout.put(id);
	}															
	
	//calculating size of file
	
	fin.seekg(0,ios::end);
	long int size=fin.tellg();
	fin.seekg(0,ios::beg);
	
	//if decryption, skip the first letter as it denotes the type of encryption used
	
	if(flag==2)
	{
		fin.seekg(1,ios::beg);
		size--;
	}
		
	while(size>0)
	{
		fin.get(charin);
		
		//nibble shifting
		//abcd efgh :
		
		char temp= (charin & 0x0f) << 4;	// (efgh 0000)
		char temp1= (charin & 0xf0) >> 4;	// (0000 abcd)	
		
		//bit shifting
		char a1= (temp & 0x80) >>3;			// (000e 0000)
		char a2= (temp & 0x40) >>1;			// (00f0 0000)
		char a3= (temp & 0x20) <<1;			// (0g00 0000)
		char a4= (temp & 0x10) <<3;			// (h000 0000)
		
		temp= ((a1 | a2) | (a3 | a4));		// (hgfe 0000)
		
		//bit shifting
		a1= (temp1 & 0x08) >>3;				// (0000 000a)
		a2= (temp1 & 0x04) >>1;				// (0000 00b0)
		a3= (temp1 & 0x02) <<1;				// (0000 0c00)
		a4= (temp1 & 0x01) <<3;				// (0000 d000)
		
		//reversed bits
		temp1= ((a1 | a2) | (a3 | a4));		// (0000 dcba)
		
		
		char charout= temp | temp1;			// (hgfe dcba)
		
		fout.put(charout);
		size--;
	}

	fin.close();
	fout.close();

}



//---------------------------------------------------------------------------------------------

/*

	crypt_gamma()
	
	Logic : Reversing all the bit positions in a byte
	
	For Encryption : Encrypts the input file and writes 'X' or 'Y' in the beginning to denote Gamma Encryption based on the version
	
	For Decryption : Determines the Encryption used on the basis of First letter and then decrypts the file.
	
	Input : Input file pointer, output file pointer, flag(determines whether to encrypt or decrypt)
	
	Output : Output File

*/


void Encrypt::crypt_gamma(ifstream & fin,ofstream & fout, int flag ,int choice)		//Gamma Encryption
{
	char id;																
	
	if(flag==1)
   	{
   	
   		//version 1
   		if(choice==1)
   		{
   			id='X';
   			fout.put(id);
   		}
   		else   //version 2
   		{
   			id='Y';
   			fout.put(id);
   		}
   	}
   	
   	fin.seekg(0,ios::end);
	long int size=fin.tellg();
	fin.seekg(0,ios::beg);
    
    if(flag==2)
    {
    	fin.seekg(1,ios::beg);
    	size--;
    }
	
	
	switch(choice)
	{
		case 1 :												//Version 1
		{	
			char charin;
			while(size>0)
			{
				fin.get(charin);
				
				//(0000 000a) | (0000 00b0) | (0000 0c00) | (0000 d000) | (000e 0000) | (00f0 0000) | (0g00 0000) | (h000 0000)  -> (hgfe dcba)
				
                charin = (((charin&0x80)>>7) | ((charin&0x40)>>5) | ((charin&0x20)>>3) | ((charin&0x10)>>1) | ((charin&0x08)<<1) | ((charin&0x04)<<3) | ((charin&0x02)<<5) | ((charin&0x01)<<7));

                fout.put(charin);
                size--;

			}

			fin.close();
			fout.close();

			break;
		}
	    case 2:													//Version 2
		{
		    
		    char charin;
		    while(size>0)
		    {
		    	
			    fin.get(charin);
			    
			    //abcd efgh :
			    
			    //(abcd 0000 >> 4) | (0000 efgh << 4) -> efgh abcd
			    charin = ((charin & 0xF0) >> 4 | (charin & 0x0F) << 4);
		        
		        //(ef00 ab00 >> 2) | (00gh 00cd << 2) -> ghef cdab
	            charin = ((charin & 0xCC) >> 2 | (charin & 0x33) << 2);
	            
	            //(g0e0 c0a0 >> 1) | (0h0f 0d0b << 1) -> hgfe dcba
	            charin = ((charin & 0xAA) >> 1 | (charin & 0x55) << 1);

	            fout.put(charin);
	            size--;

			}

			fin.close();
			fout.close();
			
			break;
		default:
			return;	
	   }
	}
}


//------------------------------------------------------------------------------------------------------

/*

	crypt_theta()
	
	Logic : Iteratng over the file from the end, and performing inter nibble swap on the third character
	
	For Encryption : Encrypts the input file and writes 'T' in the beginning to denote Theta Encryption.
	
	For Decryption : Determines the Encryption used on the basis of First letter and then decrypts the file.
	
	Input : Input file pointer, output file pointer, flag(determines whether to encrypt or decrypt)
	
	Output : Output File

*/


void Encrypt::crypt_theta(ifstream & fin,ofstream & fout,int flag)			//Theta Encryption
{
	
	char x;	
	
	//if encryption, put 'T' in the beginning of output file
	
	if(flag==1)
	{
	    x='T';
        fout.put(x);
    }
        
    //calculating size of file
    
	fin.seekg(0,ios::end);
	long int size=fin.tellg();
	fin.seekg(1,ios::end);
	
	long int z=size;
	
	if(flag==2)
		z--;
		
	while(z>0)
	{
	
		//Taking third character from the current postion of file pointer
        fin.seekg(-2,ios::cur);
		fin.get(x);
		
		//abcd efgh :
		//(ab00 ef00 >> 2) | (00cd 00gh) << 2 -> cdab ghef
		x = ((x & 0xCC) >> 2 | (x & 0x33) << 2);
		fout.put(x);
		z--;
	}
	

	fin.close();
	fout.close();

}

//------------------------------------------------------------------------------------------------------

/*

	crypt_delta()
	
	Logic : Performing 1's complement and then swapping all the bit positions : hgfe dcba
	
	For Encryption : Encrypts the input file and writes 'T' in the beginning to denote Theta Encryption.
	
	For Decryption : Determines the Encryption used on the basis of First letter and then decrypts the file.
	
	Input : Input file pointer, output file pointer, flag(determines whether to encrypt or decrypt)
	
	Output : Output File

*/

void Encrypt::crypt_delta(ifstream & fin,ofstream & fout,int flag)			//Delta Encryption
{
	char id,charin;
	
	//if encryption, put 'D' in the beginning of output file
	
	if(flag==1)
	{
	    id='D';
        fout.put(id);
    }
    
    //calculating size of file
    
	fin.seekg(0,ios::end);
	long int size=fin.tellg();
	fin.seekg(0,ios::beg);
	
	if(flag==2)
    {
    	fin.seekg(1,ios::beg);
    	size--;
    }
	
	while(size>0)
	{
	
		fin.get(charin);
		
		//1's complement	
		char x=(charin^0xFF);
		
		//nibble swapping
			
		char nib1=(x &  0x0f);
		char nib2=(x & 0xf0);
		
		char x1=(nib1 & 0x08)>>1;
		char x2=(nib1 & 0x04)<<1;
		char x3=(nib1 & 0x02)>>1;
		char x4=(nib1 & 0x01)<<1;
			
		nib1=((x1 | x2) | (x3 | x4));
			
		char x5=(nib2 & 0x80)>>1;
		char x6=(nib2 & 0x40)<<1;
		char x7=(nib2 & 0x20)>>1;
		char x8=(nib2 & 0x10)<<1;
			
		nib2=((x5 | x6) | (x7 | x8));
			
		charin=(nib1 | nib2);
		
		fout.put(charin);
		size--;
		
	}
	
	fin.close();
	fout.close();
	
}

//-------------------------------------------------------------------------------------------------

/*
	decrypt()
	
	Logic : Takes the first letter of the file and determines which encryption was used.
			Accordingly calls the respective function
			
	Input : Input file pointer, Output file pointer, flag=2

*/

void Encrypt::decrypt(ifstream & fin,ofstream & fout,int flag)			//Decryption
{
        char id;
        int choice;
        choice=0;
        fin.get(id);
        
        
        if(id=='A')
        	crypt_alpha(fin,fout,flag);
        	
        else if(id=='B')
            crypt_beta(fin,fout,flag);
            
        else if(id=='X')
        {
        	choice=1;													//version 1
            crypt_gamma(fin,fout,flag,choice);
        }
        
        else if(id=='Y')
        {
        	choice=2;													//version 2
        	crypt_gamma(fin,fout,flag,choice);
        }
        
        else if(id=='T')
            crypt_theta(fin,fout,flag);
            
        else if(id=='D')
        	crypt_delta(fin,fout,flag);
}

//----------------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	        // as the computation is faster it does not take absolutely any time to complete!
	        // We will use delay of 5 sec to just get the effect of loading a program! 

	Encrypt e;
	ifstream fin;
	ofstream fout;
	
	int errorFlag=0;
	
	enum msgs													//Enum : For all Messages
	{
		no_name,
		ip_err,
		op_err,
		arg_err,
		algo_err,
		algo_name_err,
		e_d_err,
		op_name,
		alfa_done,
		beta_done,
		gama_done,
		tita_done,
		dlta_done,
		d_done,
		g_two,
		choose_g,
		enter_g,
		more_help,
		alfa_d,
		beta_d,
		gama1_d,
		gama2_d,
		tita_d,
		dlta_d,
		op_ip_same,
		invalid_arg,
		op_saved,
		op_exist,
		e_d_exist,
		duplicate_args_e,
		duplicate_args_d,
		duplicate_args_algo,
		duplicate_args_i,
		duplicate_args_o,
		help_arg,
		full_help
	};
	msgs m;

	if(argc==1)               	//if only one argument is present, it is just the program name(./file).
	{
		msgs m;
		m=arg_err;
		cout<<msg[m];
		m=more_help;
		cout<<msg[m];
		return 0;
	}
	
	int ar;
	ar=strcmp(argv[1],"--help");
	
	if((argc==2) && (ar!=0))	//Checking if there are 2 arguments, whether the 2nd argument is "--help"
	{
		m=arg_err;
		cout<<msg[m];
	    errorFlag=1;
	}
	
	if((!strcmp(argv[1],"--help")) && (argc>2))		//If there are any other arguments with --help
	{
		m=help_arg;
		cout<<msg[m];
		m=more_help;
		cout<<msg[m];
		return 0;
	}
	
	if((argc==2) && !strcmp(argv[1],"--help"))		//if --help given, print full help
	{
		m=full_help;
		cout<<msg[m];
		return 0;
	}
	
										//Initializing variables to NULL before argument comparison
	char* inpFile=NULL;
	char* outFile = (char*)"technoOut.txt";
	char* algorithm=NULL;
	int flag=0;
	
	//If technoOut.txt already exists, rename new file as technoOut(<num>).txt
	
    char num[3]="1";
    while(1)
    {
        
        if(ifstream(outFile))
        {
        	char temp[20] = "technoOut(";
	        strcat(temp,num);
	        strcat(temp,").txt");
	        outFile = temp;
	        num[0]+=1;
	        
        }	
        else
        {
            break;
        }
	}
	
//------------------------------------ Argument Parsing ---------------------------------------------------

	int count=1;									//to keep a count of valid arguments
	int inp_exist=0;
	int e_exist=0;
	int d_exist=0;
	int algo_exist=0;
	int o_exist=0;
	
	for (int i = 1; i < argc; i++) 
	{ 									/* We will iterate over argv[] to get the parameters stored inside.
                                       	* Note that we're starting on 1 because we don't need to know the 
                                        * path of the program, which is stored in argv[0] */
    //-----------------------------------------------------------------------------------------
        
        if (!strcmp(argv[i],"-i")) 					//FOR -i <InputFile_name>
        {
		    if(inpFile==NULL)
		    {            	
		    	inp_exist=1;						// The next argument *should* be the filename:
		    	if(i==(argc-1))	
		    	{									//If -i is the last argument, give error message and exit
		    		errorFlag=1;
		        }
		        else if(!ifstream(argv[i + 1]))		//Checking if next argument is a valid InputFile
		       	{
		       		errorFlag=1;
		       	}  	
		        else
		        {
		            inpFile=argv[i + 1];
		            count=count+2;
		        }   	       		
		    }    
        } 
        
    //-----------------------------------------------------------------------------------------
        
        if (!strcmp(argv[i],"-o")) 					//FOR -o <OutputFile_name>
        {
			if(o_exist!=1)
			{  
				o_exist=1;							
				
				if(inp_exist!=1)		//Checking if Valid Inputfile given. Only then will -o get assigned.
				{
					for(int j=1;j<argc;j++)
					{
					
						if(!strcmp(argv[j],"-i")) 
						{
							inp_exist=1;
						
							if(j==(argc-1))			//if -i is the last argument
							{
								errorFlag=1;
							}	    		
							else if(!ifstream(argv[j + 1]))
						   	{
						   		errorFlag=1;	
						   	}  	
							else
							{
								inpFile=argv[j+ 1];
								count=count+2;
							}   	       		
							break;	    		
						 }
					}
					 
				}
				
				if((i<(argc-1)) && inpFile!=NULL)	//if valid Inputfile Given and If -o is not the last argument
				{
					char* opFile=argv[i + 1];
				
					if(!strcmp(opFile,inpFile))				//Checking if outputFile name is same as InputFile name
					{
						m=op_ip_same;
						cout<<msg[m];
						errorFlag=1;
					}
					else if(!strcmp(argv[i+1],"-i") || !strcmp(argv[i+1],"-e") || !strcmp(argv[i+1],"-algo") || !strcmp(argv[i+1],"-d"))										//if -o is folled by -i/-e/-algo/-d
					{
					   	outFile=NULL;
					   	errorFlag=1;
					}
					
					else if(ifstream(argv[i+1]))			//if output file with given name already exists
					{
					   	m=op_exist;
					   	cout<<msg[m];
					   	outFile=NULL;
					   	errorFlag=1;
					} 
					else if(!ofstream(argv[i+1]))
					{
					   	m=op_name;
					  	cout<<msg[m]; 
					  	outFile=NULL;
					   	errorFlag=1;
					}
					else
					{
						outFile=argv[i + 1];
					   	count=count+2;	
					   	i++;
					}
				}
			
				else 
				{
					errorFlag=1; 
				} 
			}
			else
		    {
		    	m=duplicate_args_o;
		    	cout<<msg[m];
		    	errorFlag=1;
		    }	 	        	
        } 
        
    //---------------------------------------------------------------------------------------
        
        if (!strcmp(argv[i],"-algo") )					//FOR -algo <algorithm_name>
        {
		    if(algo_exist!=1)
		    {
		    	algo_exist=1;
		    
		     	if(i<(argc-1))
		     	{
		     		
		     		algorithm=argv[i+1];
		     		
		     		for(int k=0;k<4;k++)				//Converting to lower case
		     		{
		     			algorithm[k]=tolower(algorithm[k]);
		     		}   
		     		
				    if(!strcmp(algorithm,"alfa") | !strcmp(algorithm,"beta") | !strcmp(algorithm,"gama") | !strcmp(algorithm,"tita") | !strcmp(algorithm,"dlta"))
				    {
				    	algorithm = argv[i + 1];
				    	count=count+2;
				    }
				    else
				    {
				    	algorithm=NULL;
				   		errorFlag=1;
				    } 
		       	}
		       	else
		       	{
		          	errorFlag=1;
		        } 
		    }   
		    else
		    {
		    	m=duplicate_args_algo;
		    	cout<<msg[m];
		    	errorFlag=1;
		    }	
        } 
        
    //----------------------------------------------------------------------------------
        
        if (!strcmp(argv[i],"-e"))   					//For -e (Encryption)
        {
		    if(e_exist!=1)
		    {
		    	flag=1;
		    	count++;
		    	e_exist=1;
		    }
		    else
		    {
		    	m=duplicate_args_e;
		    	cout<<msg[m];
		    	errorFlag=1;
		    }
        }
        
    //----------------------------------------------------------------------------------
        
        if (!strcmp(argv[i] , "-d"))					//For -d (Decryption)
        {
		    if(d_exist!=1)
		    {
		    	flag=2;
		    	count++;
		    	d_exist=1;
		    }
		    else
		    {
		    	m=duplicate_args_d;
		    	cout<<msg[m];
		    	errorFlag=1;
		    }
        }
        
	}
	
//-------------------------------------------------------------------------------------------------------
	
	if(inpFile==NULL)									//If no Input File given
    {
    	m=no_name;
       	cout<<msg[m];
        errorFlag=1;
    }  
	
  	if(flag==0)											//If neither encryption nor decryption selected
    {
    	m=e_d_err;
        cout<<msg[m];
        errorFlag=1;
    }
    
    if((e_exist==1) && (d_exist==1))					//If -e and -d, both are given as arguments
    {
    	m=e_d_exist;
    	cout<<msg[m];
    	errorFlag=1;
    }
        	
    if((flag!=2) && (algorithm==NULL))					//If Encryption selected but algorithm not specified
    {
    	m=algo_err;
        cout<<msg[m];
        errorFlag=1;
    }
    
    if(outFile==NULL)									//If Valid Output file name not followed after -o
    {
    	m=op_name;
    	cout<<msg[m];
    	errorFlag=1;
    }
    
    if(count!=argc)										//To check if there are other non required arguments
    {
    	m=invalid_arg;
    	cout<<msg[m];
    	errorFlag=1;
    }
    
    if(errorFlag==1)									//To print all the error messages and exit
    {
        m=more_help;
	    cout<<msg[m];
	    if(outFile!=NULL)
	    {
	    	int status=remove(outFile);
	    }
        return 0;
    }
    
    fin.open(inpFile);
    
    if(!fin)             								//Error opening Input file
    {
        m=ip_err;
		cout<<msg[m];
		return 0;
    }
    
    fout.open(outFile);
    
    if(!fout)											//Error opening output File
	{
		msgs m;
		m=op_err;
		cout<<msg[m];
		fin.close();
		m=more_help;
		cout<<msg[m];
		return 0;
	}	
     
//------------------------------------- Algorithms for Encryption ---------------------------------
     
    if(flag==1)
	{
				
                                
		//------------------------------------------------------------------
			
		if(!strcmp(algorithm,"alfa"))					//Alfa Encryption
		{
			e.crypt_alpha(fin,fout,flag);
			m=alfa_done;
			cout<<msg[m];
				
		}

		//------------------------------------------------------------------

		else if(!strcmp(algorithm,"beta"))				//Beta Encryption
		{
			e.crypt_beta(fin,fout,flag);
			m=beta_done;
			cout<<msg[m];
		}


		//----------------------------------------------------------------

		else if(!strcmp(algorithm,"gama"))				//Gamma Encryption
		{
			m=g_two;		
			cout<<msg[m];
			m=choose_g;
			cout<<msg[m];
			m=enter_g;
			cout<<msg[m];
			int choice;
			cin>>choice;

			 e.crypt_gamma(fin,fout,flag,choice);
			 
			 m=gama_done;
			 
			 cout<<msg[m];
		}

		//------------------------------------------------------------------

		else if(!strcmp(algorithm,"tita"))				//Theta Encryption
		{
			e.crypt_theta(fin,fout,flag);
			m=tita_done;
			cout<<msg[m];
		}
		
		//------------------------------------------------------------------
		
		else if(!strcmp(algorithm,"dlta"))				//Delta Encryption
		{
			e.crypt_delta(fin,fout,flag);
			m=dlta_done;
			cout<<msg[m];
		}
		
		//------------------------------------------------------------------
		
		m=op_saved;
		cout<<msg[m]<<outFile;
		cout<<endl<<endl;
					
	}

//--------------------------------------------------------------------------------------
			
	else if(flag==2)									//Decryption
	{
		e.decrypt(fin,fout,flag);
		m=d_done;
		cout<<msg[m];	
		m=op_saved;
		cout<<msg[m]<<outFile;
		cout<<endl<<endl;
	}
		
	return 0;
	
}

//-----------------------------------------------------------------------------------------------------


