#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 
using namespace std;

string Formato="";

void EscribirSecuencia(string Id, string Secuencia)
{
	cout<<"\n================================================================================\nId: "<< Id <<"\nSecuencia: "<< Secuencia;	
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
		   string Secuencia;
		   bool esMas=false;				 
		   while ((Formato.compare("error")!=0) && (!Archivo.eof()))
		   { 
			   	 Archivo.getline(linea,1000);		   	 		   	 		   	 		   	 
			   	 string Aux=linea;
			   	 if (Formato.compare("")==0)
			   	 {
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
								EscribirSecuencia(Id,Secuencia);
							}
							Id=Aux.substr(1,Aux.length()-2);				 	
							Secuencia="";
						 }		   	 
						 else
						 {
							Secuencia.append(Aux.substr(0,Aux.length()-1));							
						 }
					 }
					 else //fastq
					 {					 
						 if (linea[0]=='@')
						 {
							esMas=false;
							if (Id.compare("")!=0)
							{
								EscribirSecuencia(Id,Secuencia);
							}
							Id=Aux.substr(1,Aux.length()-1);				 	
							Secuencia="";
						 }		   	 
						 else
						 {
							if (linea[0]=='+')
							{
							  esMas=true;
						    }
							if (!esMas)
							{
								Secuencia.append(Aux.substr(0,Aux.length()));
							}
						 }
					 }
					 
				 }			 
			}
			if (Id.compare("")!=0)
			{
				EscribirSecuencia(Id,Secuencia);
			}
	   }
	   else
	   {
	   		cout<<"El archivo no existe";
	   }
	}
	else
	  cout<<"Debe especificar un archivo *.fasta o *.fastq\n";
   cout<<"\n";
   return 0;
}
