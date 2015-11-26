#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 
using namespace std;

string Formato="";

void EscribiCadena(string Id, string Cadena)
{
	cout<<"\n---------------------------------------------------------------------------------\nId: "<< Id <<"\nCadena: "<< Cadena;	
}

int main(int argc, char* argv[])
{
	if (argc>1)
	{
	   ifstream Archivo;
	   Archivo.open(argv[1]);	   
	   if (Archivo.good())
	   {
		   char linea[1000];		   
		   string Id="";		   	 
		   string Cadena;
		   bool esMas=false;				 
		   while ((Formato.compare("error")!=0) && (!Archivo.eof()))
		   { 
			   	 Archivo.getline(linea,1000);		   	 		   	 		   	 		   	 
			   	 string Aux=linea;
			   	 if (Formato.compare("")==0)
			   	 {
					//diferenciador si es fasta o gastq
					if (linea[0]=='>')
						Formato="fasta";
					else
					  if (linea[0]=='@')
						Formato="fastq";
					  else
					    Formato="error";
				 }
				 if (Formato.compare("error")!=0)
				 {
					 if (Formato.compare("fasta")==0)
					 {
						 if (linea[0]=='>')
						 {
							if (Id.compare("")!=0)
							{
								EscribiCadena(Id,Cadena);
							}
							Id=Aux.substr(1,Aux.length()-2);				 	
							Cadena="";
						 }		   	 
						 else
						 {
							Cadena.append(Aux.substr(0,Aux.length()-1));							
						 }
					 }
					 else //fastq
					 {					 
						 if (linea[0]=='@')
						 {
							esMas=false;
							if (Id.compare("")!=0)
							{
								EscribiCadena(Id,Cadena);
							}
							Id=Aux.substr(1,Aux.length()-1);				 	
							Cadena="";
						 }		   	 
						 else
						 {
							if (linea[0]=='+')
							{
							  esMas=true;
						    }
							if (!esMas)
							{
								Cadena.append(Aux.substr(0,Aux.length()));
							}
						 }
					 }
					 
				 }			 
			}
			if (Id.compare("")!=0)
			{
				EscribiCadena(Id,Cadena);
			}
	   }
	   else
	   {
	   		cout<<"No se encuentra el archivo o no existe";
	   }
	}
	else
	  cout<<"se debe especificar el archivo con *.fasta o *.fastq\n";
   cout<<"\n";
   return 0;
}
