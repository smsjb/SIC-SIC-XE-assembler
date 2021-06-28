#include <cmath>
#include <iostream> // cout, endl
#include <fstream> // open, is_open, close, ignore
#include <string> // string, find_last_of, substr
#include <sstream>
#include <vector> // vector, push_back
#include <cstdlib> // system, atoi
#include <stdio.h>
#include <iomanip> // setw
#include <time.h>
#include "stdlib.h"
using namespace std;

struct table{
	//1~4 [0]���� 
	vector<string> one ;
	vector<string> two ;
	vector<string> three ;
	vector<string> four ;
	vector<string> five ;
	vector<string> six ;
	vector<string> sev ;
};

struct tk{
	string name;
	int val=0;
	int tb=0;
};

struct tkgrp{
	tk label ;
	tk opcode ;
	tk op1 ;
	tk op2 ;
};

struct opcode{
	string name;
	string format;
	string opcode;
};

struct mch{
	string addr;
	string mc;
	string done;
};

struct confi{
	string lebal;
	vector<int> mcip;
	vector<string> addr;
	vector<string> format;
	vector<mch> cd;
};

struct lit{
	string lebal;
	int mcip;
	string mc;
	string format;
};

class tablefc {
	public:
	vector<string> instr ;
	vector<tk> altk ;
	table alltb ;
	void build1to4(){ //set table 
	    string str, fname;
		//1	Table1.table 
		fname = "Table1.table";
		fstream _file1( fname.c_str()) ;
		while ( !_file1.eof() ) { //���O�̫�@�� 

   			_file1>>str;
       		alltb.one.push_back(str);

  		} // while
  		
  		fname = "Table2.table";
		fstream _file2( fname.c_str()) ;
		while ( !_file2.eof() ) { //���O�̫�@�� 

   			_file2>>str;
       		alltb.two.push_back(str);

  		} // while
  		
  		fname = "Table3.table";
		fstream _file3( fname.c_str()) ;
		while ( !_file3.eof() ) { //���O�̫�@�� 

   			_file3>>str;
       		alltb.three.push_back(str);

  		} // while
  		
  		fname = "Table4.table";
		fstream _file4( fname.c_str()) ;
		while ( !_file4.eof() ) { //���O�̫�@�� 

   			_file4>>str;
       		alltb.four.push_back(str);

  		} // while
  		
  		alltb.five.resize(100);
  		alltb.six.resize(100);
  		alltb.sev.resize(100);
	}
	
	//Ū���O 
	void read( string & fname){
		int i = 0 ;
		string str; 

		cout<<"input file name: ";
		cin>>fname;
		
		ifstream _file( fname.c_str()) ; // ��W��fname���ɮץ��} 
		if (_file.is_open()) { //�ɮצs�b 
		
	  		while ( !_file.eof() ) { //���O�̫�@�� 

        		getline(_file, str, '\n');  
        		if(str!="\0")
        			instr.push_back(str);

      		} // while
  		} 
  		else{
  			cout<<"wrong file's name"<<endl ;
  			read(fname);
		}
  		
  		_file.close();
  		
	}
	

	
	//��token   
	void cut(){
		
		string token="\0",tmp="\0";
		int val=0;
		int type=0;
		tk temp;
		
		for(int i=0; i<instr.size(); i++){
			//cout<<instr[i]<<endl;
			//��token 
			for(int j=0; j<instr[i].size(); j++){
				tmp=instr[i][j];
				token="\0";
			
				while(instr[i][j]!=' '&& instr[i][j]!='\t'&&instr[i][j]!='\n'&& issame(val, tmp)!=4 && j<instr[i].size() ){ //is not space/tab/enter
					token=token+instr[i][j];
					
		
					j++;
					tmp=instr[i][j];
				}
						
	
				if(issame(val, tmp)==4){
		
					if(tmp=="'" && (token=="C"||token=="X"||token=="c"||token=="x")){
						
						if(token=="C"||token=="c"){
							type=1;

						}
						else if(token=="X"||token=="x"){
							type=2;
						}
							
						token="\0";
					}
					else if(tmp=="'" && type==0) //'string' 
						type=1;
				}
				
				if(token!="\0"){
				
				if((issame(val, token)!=0 && type==0)){  
					temp.tb=issame(val, token);
					temp.val=val;
					temp.name=token;
					altk.push_back(temp);
					//cout<<"("<<issame(val, token)<<","<<val<<") "; 
				} //in table
				else{ 					// hash, string(1)||lebal||int/real(2)
					// check int/real
					for(int k=0; k<token.size() && type==0; k++)
						if((int)token[k]>47 && (int)token[k]<58)
							type=2;
						else
							break;
							
					int tbnum=0;
					for(int i =0; i<alltb.six.size() && type==2; i++){  //check int/real in table
		
		 				string bf = token;
						for (int j=0; j <token.size(); j++){  
							if((int)alltb.six[i][j]>=97 && (int)alltb.six[i][j]<=122) //a~z 
       							token[j] = tolower(token[j]);  //�j�g�ܤp�g  
       						else
       							token[j] = toupper(token[j]); //�p�g�ܤj�g 
						}
       			
						if(token == alltb.six[i]){
							val=i;
							tbnum=6;
						}
				
						token=bf;
					}
		
					for(int i =0; i<alltb.sev.size()&&type==1; i++){  //check string in table
						if(token == alltb.sev[i]){
							val=i;
							tbnum=7;
						}
					}

					if(tbnum==0){
						if(type==2) // is int/real
							hash( token, 6);	
						else if(type==1) // is string
							hash( token, 7);
						else
							hash( token, 5);
					}
					else{
						temp.tb=tbnum;
						temp.val=val;
						temp.name=token;
						altk.push_back(temp);						
						//cout<<"("<<tbnum<<","<<val<<") ";

					} 	

				}
				 
				val=0;
				type=0;
				}
			
				if(issame(val, tmp)==4){  //is delimeter 
					temp.tb=4;
					temp.val=val;
					temp.name=tmp;
					altk.push_back(temp);
					//cout<<"(4"<<","<<val<<") "; 				
				}

			}
			
			//���j 
			temp.tb=0;
			temp.val=0;
			temp.name="\0";
			altk.push_back(temp);
			//cout<<endl;
		}
		
	}
	
	int sum(string str){  //��ascii�`�M 
		int num =0;
		for(int i =0; i<str.size(); i++)
			num = (int)str[i] + num;	
		return num;		
	}
	
	void hash( string str, int tb){

		int ip =sum(str)%100; //���m 
		
		if(tb==5){
		
				while(alltb.five[ip]!="\0"){  //�I�� 
					ip++;
					if(ip>=100)
						ip=ip%100;
				}

			alltb.five[ip] = str;

		}
		else if(tb==6){
			
				for(int i =0; i<str.size(); i++){
					if((int)str[i]>=97 && (int)str[i]<=122) //a~z
						ip=sum(str)-32;
						
				}
				
				ip=ip%100;
				while(alltb.six[ip]!="\0"){
					ip++;
					if(ip>=100)
						ip=ip%100;
				}

				
			alltb.six[ip] = str;
		}
		else {
				while(alltb.sev[ip]!="\0"){
					ip++;
					if(ip>=100)
						ip=ip%100;
				}
				
			alltb.sev[ip] = str;
		}
		
		tk tmp;
		tmp.tb=tb;
		tmp.val=ip;
		tmp.name=str;
		altk.push_back(tmp);
		//cout<<"("<<tb<<","<<ip<<") "; 

	}
	
	int issame(int & val, string key){ //return tbnum & value
		int tbnum =0;
		bool out=false;

		for(int i =0; i<alltb.one.size() && !out; i++){ 
		 	
		 	string bf = key;
			for (int j=0; j <key.size(); j++){  
				if((int)alltb.one[i][j]>=97 && (int)alltb.one[i][j]<=122)  //a~z 
       				key[j] = tolower(key[j]);  //�j�g�ܤp�g  
       			else
       				key[j] = toupper(key[j]); //�p�g�ܤj�g 
			}
			 
			if(key == alltb.one[i]){
				
				out=true;
				val=i+1;
				tbnum=1;
			}
			
			key=bf;
			
		}

		
		for(int i =0; i<alltb.two.size() && !out; i++){
			string bf = key;
			for (int j=0; j <key.size(); j++){  
				if((int)alltb.two[i][j]>=97 && (int)alltb.two[i][j]<=122) //a~z 
       				key[j] = tolower(key[j]);  //�j�g�ܤp�g  
       			else
       				key[j] = toupper(key[j]); //�p�g�ܤj�g 
			}
       			
       		
			if(key == alltb.two[i]){
				out=true;
				val=i+1;
				tbnum=2;
			}
			
			key=bf;
		}	
		

		for(int i =0; i<alltb.three.size() && !out; i++){ 
		 	string bf = key;
			for (int j=0; j <key.size(); j++){  
				if((int)alltb.three[i][j]>=97 && (int)alltb.three[i][j]<=122) //a~z 
       				key[j] = tolower(key[j]);  //�j�g�ܤp�g  
       			else
       				key[j] = toupper(key[j]); //�p�g�ܤj�g 
			}
       			
			if(key == alltb.three[i]){
				out=true;
				val=i+1;
				tbnum=3;
			}
			
			key=bf;
		}
		
		for(int i =0; i<alltb.four.size() && !out; i++){ 
			if(key == alltb.four[i]){
				out=true;
				val=i+1;
				tbnum=4;
			}
		}
		
		for(int i =0; i<alltb.five.size() && !out; i++){ 
			if(key == alltb.five[i]){
				out=true;
				val=i;
				tbnum=5;
			}
		}
		
		for(int i =0; i<alltb.six.size() && !out; i++){ 
		
		 	string bf = key;
			for (int j=0; j <key.size(); j++){  
				if((int)alltb.six[i][j]>=97 && (int)alltb.six[i][j]<=122) //a~z 
       				key[j] = tolower(key[j]);  //�j�g�ܤp�g  
       			else
       				key[j] = toupper(key[j]); //�p�g�ܤj�g 
			}
       			
			if(key == alltb.six[i]){
				out=true;
				val=i;
				tbnum=6;
			}
			
			key=bf;
		}
		
		for(int i =0; i<alltb.sev.size() && !out; i++){ 
			if(key == alltb.sev[i]){
				out=true;
				val=i;
				tbnum=7;
			}
		}
		
		return tbnum;
	}
	
	
};

class Syntax {
public:
	vector<tkgrp> grp;

	void check(vector<tk> altk, vector<string> instr){
		tkgrp temp;
		
		for(int i=0; i < altk.size();){
			tkgrp tmp;
			for(int num=0;altk[i].name != "\0";i++, num++){
			//	cout<<"name: "<<altk[i].name<<altk[i].tb<<endl;
			//	cout<<"op1: "<<tmp.op1.name<<"\tnum: "<<num<<endl;
				if(altk[i].name != "."){
				
				if(num==0){
					if(altk[i].tb==5)	
						tmp.label=altk[i];
					else if(altk[i].tb==1 || altk[i].tb==2)
						tmp.opcode=altk[i];	
					else if(altk[i].name != "+"){
					//	cout<<"syntax erro1"<<endl;
						tmp.opcode.name="syntax erro";
						for(;altk[i].name != "\0";i++);
			
						break;
					}
					
				//	cout<<"num=0: "<<tmp.label
				}
				else if(num==1){
					if(altk[i].tb==1 || altk[i].tb==2){  //has lebal, +addr
						if(altk[i-1].name=="+"){
							tmp.opcode=altk[i];
							tmp.opcode.name="+"+altk[i].name;
						}
						else
							tmp.opcode=altk[i];
					}
					else if(altk[i].tb!=4)
						tmp.op1	=altk[i];
					else{ //,�e�Soperand 
						if(altk[i-1].name!="#" && altk[i-1].name!="@"&&altk[i].name!="#"&&altk[i].name!="@"&&altk[i].name!="="){
							tmp.opcode.name="syntax erro";
						//	cout<<"syntax erro2"<<endl;
							for(;altk[i].name != "\0";i++);
				
							break;
						}
					}				
				}
				else{ 
			//		cout<<"op1\t\t\t: "<<tmp.op1.name<<endl;
					if(tmp.op1.name != "\0" && tmp.op2.name != "\0" && altk[i].tb!=4){
						tmp.opcode.name="syntax erro";
					//	cout<<"syntax erro3"<<endl;
						for(;altk[i].name != "\0";i++);	
					
						break;					
					}
					if(tmp.op1.name != "\0"){   //op*2 
						if(altk[i].name != "," && altk[i].name != "'" &&altk[i-1].name!= ","){  //ex.op1.op2  
							tmp.opcode.name="syntax erro";
						//	cout<<"syntax erro4"<<endl;
							for(;altk[i].name != "\0";i++);
					
							break;
						}
						else{
							if(altk[i].tb!=4)
								tmp.op2=altk[i];
							else if(altk[i].name == "," ){
								if(altk[i+1].name=="\0"){
									tmp.opcode.name="syntax erro";
								//	cout<<"syntax erro5"<<endl;
									for(;altk[i].name != "\0";i++);
									break;								
								}
							}
						}
					}
					else{ //op*1
						if(altk[i].tb!=4){
							tmp.op1=altk[i];
							if(altk[i-1].name=="=")
								tmp.op1.name="="+tmp.op1.name;
						}  
					}
	
				}
			}
			else{
				for(;altk[i].name != "\0";i++);
				num=-1;
			}
		}
		
		
			grp.push_back(tmp);
		//	cout<<"next"<<endl;
			i++;
		}
			
	}	
	
}; 

class MCC{
public:
	vector<lit> literal;
	vector<opcode> opc;
	vector<mch> mc;
	vector<confi> cft;
	tablefc imp;
	void bdopcode(){
		opcode tmp;
		
		tmp.name="ADD";
		tmp.format="3/4";
		tmp.opcode="18";
		opc.push_back(tmp);

		tmp.name="ADDF";
		tmp.format="3/4";
		tmp.opcode="58";
		opc.push_back(tmp);
		
		tmp.name="ADDR";
		tmp.format="2";
		tmp.opcode="90";
		opc.push_back(tmp);
		
		tmp.name="AND";
		tmp.format="3/4";
		tmp.opcode="40";
		opc.push_back(tmp);
		
		tmp.name="CLEAR";
		tmp.format="2";
		tmp.opcode="B4";
		opc.push_back(tmp);
		
		tmp.name="COMP";
		tmp.format="3/4";
		tmp.opcode="28";
		opc.push_back(tmp);
		
		tmp.name="COMPF";
		tmp.format="3/4";
		tmp.opcode="88";
		opc.push_back(tmp);
		
		tmp.name="COMPR";
		tmp.format="2";
		tmp.opcode="A0";
		opc.push_back(tmp);
		
		tmp.name="DIV";
		tmp.format="3/4";
		tmp.opcode="24";
		opc.push_back(tmp);
		
		tmp.name="DIVF";
		tmp.format="3/4";
		tmp.opcode="64";
		opc.push_back(tmp);
		
		tmp.name="DIVR";
		tmp.format="2";
		tmp.opcode="9C";
		opc.push_back(tmp);
		
		tmp.name="FIX";
		tmp.format="1";
		tmp.opcode="C4";
		opc.push_back(tmp);
		
		tmp.name="FLOAT";
		tmp.format="1";
		tmp.opcode="C0";
		opc.push_back(tmp);
		
		tmp.name="HIO";
		tmp.format="1";
		tmp.opcode="F4";
		opc.push_back(tmp);
		
		tmp.name="J";
		tmp.format="3/4";
		tmp.opcode="3C";
		opc.push_back(tmp);
		
		tmp.name="JEQ";
		tmp.format="3/4";
		tmp.opcode="30";
		opc.push_back(tmp);
		
		tmp.name="JGT";
		tmp.format="3/4";
		tmp.opcode="34";
		opc.push_back(tmp);
		
		tmp.name="JLT";
		tmp.format="3/4";
		tmp.opcode="38";
		opc.push_back(tmp);
		
		tmp.name="JSUB";
		tmp.format="3/4";
		tmp.opcode="48";
		opc.push_back(tmp);
		
		tmp.name="LDA";
		tmp.format="3/4";
		tmp.opcode="00";
		opc.push_back(tmp);
		
		tmp.name="LDB";
		tmp.format="3/4";
		tmp.opcode="68";
		opc.push_back(tmp);
		
		tmp.name="LDCH";
		tmp.format="3/4";
		tmp.opcode="50";
		opc.push_back(tmp);
		
		tmp.name="LDF";
		tmp.format="3/4";
		tmp.opcode="70";
		opc.push_back(tmp);
		
		tmp.name="LDL";
		tmp.format="3/4";
		tmp.opcode="08";
		opc.push_back(tmp);
		
		tmp.name="LDS";
		tmp.format="3/4";
		tmp.opcode="6C";
		opc.push_back(tmp);
		
		tmp.name="LDT";
		tmp.format="3/4";
		tmp.opcode="74";
		opc.push_back(tmp);
		
		tmp.name="LDX";
		tmp.format="3/4";
		tmp.opcode="04";
		opc.push_back(tmp);
		
		tmp.name="LPS";
		tmp.format="3/4";
		tmp.opcode="D0";
		opc.push_back(tmp);
		
		tmp.name="MUL";
		tmp.format="3/4";
		tmp.opcode="20";
		opc.push_back(tmp);
		
		tmp.name="MULF";
		tmp.format="3/4";
		tmp.opcode="60";
		opc.push_back(tmp);
		
		tmp.name="MULR";
		tmp.format="2";
		tmp.opcode="98";
		opc.push_back(tmp);
		
		tmp.name="NORM";
		tmp.format="1";
		tmp.opcode="C8";
		opc.push_back(tmp);
		
		tmp.name="OR";
		tmp.format="3/4";
		tmp.opcode="44";
		opc.push_back(tmp);
		
		tmp.name="RD";
		tmp.format="3/4";
		tmp.opcode="D8";
		opc.push_back(tmp);
		
		tmp.name="RMO";
		tmp.format="2";
		tmp.opcode="AC";
		opc.push_back(tmp);
		
		tmp.name="RSUB";
		tmp.format="3/4";
		tmp.opcode="4C";
		opc.push_back(tmp);
		
		tmp.name="SHIFTL";
		tmp.format="2";
		tmp.opcode="A4";
		opc.push_back(tmp);
		
		tmp.name="SHIFTR";
		tmp.format="2";
		tmp.opcode="A8";
		opc.push_back(tmp);
		
		tmp.name="SIO";
		tmp.format="1";
		tmp.opcode="F0";
		opc.push_back(tmp);
		
		tmp.name="SSK";
		tmp.format="3/4";
		tmp.opcode="EC";
		opc.push_back(tmp);
		
		tmp.name="STA";
		tmp.format="3/4";
		tmp.opcode="0C";
		opc.push_back(tmp);
		
		tmp.name="STB";
		tmp.format="3/4";
		tmp.opcode="78";
		opc.push_back(tmp);
		
		tmp.name="STCH";
		tmp.format="3/4";
		tmp.opcode="54";
		opc.push_back(tmp);
		
		tmp.name="STF";
		tmp.format="3/4";
		tmp.opcode="80";
		opc.push_back(tmp);
		
		tmp.name="STI";
		tmp.format="3/4";
		tmp.opcode="D4";
		opc.push_back(tmp);
		
		tmp.name="STL";
		tmp.format="3/4";
		tmp.opcode="14";
		opc.push_back(tmp);
		
		tmp.name="STS";
		tmp.format="3/4";
		tmp.opcode="7C";
		opc.push_back(tmp);
		
		tmp.name="STSW";
		tmp.format="3/4";
		tmp.opcode="E8";
		opc.push_back(tmp);
		
		tmp.name="STT";
		tmp.format="3/4";
		tmp.opcode="84";
		opc.push_back(tmp);
		
		tmp.name="STX";
		tmp.format="3/4";
		tmp.opcode="10";
		opc.push_back(tmp);
		
		tmp.name="SUB";
		tmp.format="3/4";
		tmp.opcode="1C";
		opc.push_back(tmp);
		
		tmp.name="SUBF";
		tmp.format="3/4";
		tmp.opcode="5C";
		opc.push_back(tmp);
		
		tmp.name="SUBR";
		tmp.format="2";
		tmp.opcode="94";
		opc.push_back(tmp);
		
		tmp.name="SVC";
		tmp.format="2";
		tmp.opcode="B0";
		opc.push_back(tmp);
		
		tmp.name="TD";
		tmp.format="3/4";
		tmp.opcode="E0";
		opc.push_back(tmp);
		
		tmp.name="TIO";
		tmp.format="1";
		tmp.opcode="F8";
		opc.push_back(tmp);
		
		tmp.name="TIX";
		tmp.format="3/4";
		tmp.opcode="2C";
		opc.push_back(tmp);
		
		tmp.name="TIXR";
		tmp.format="2";
		tmp.opcode="B8";
		opc.push_back(tmp);
		
		tmp.name="WD";
		tmp.format="3/4";
		tmp.opcode="DC";
		opc.push_back(tmp);
	}

	void lithash( lit str){
		string lit;
		for(int k=0; k<str.lebal.length(); k++)
			if(str.lebal[k]!='=' && str.lebal[k]!='C' && str.lebal[k]!='c' && str.lebal[k]!='X'&& str.lebal[k]!='x'&& (int)str.lebal[k]!=39)
				lit=lit+str.lebal[k];
		int ip =imp.sum(str.lebal)%100; //���m 
		

				while(literal[ip].lebal!="\0"){
					ip++;
					if(ip>=100)
						ip=ip%100;
				}
				
			literal[ip] = str;

		
	}
		
	void mcc(vector<tkgrp> grp, vector<string> instr, string fname){  //literal?????????
		string pc, str, ans;
		int tp=0, ip=0;;
		literal.resize(100);
/*		for(int i=0; i<grp.size(); i++){
			cout<<grp[i].op1.name<<"\t"<<grp[i].op1.isc<<"\t"<<grp[i].op1.isx<<endl;
		}*/
		
		for(int i=0; i<grp.size(); i++, ip++){
			string format;
			mch code;
			if(grp[i].opcode.name=="syntax erro"){
				code.mc="syntax erro";
				code.addr=pc;
				mc.push_back(code);	
			}
			else{
			
			//	cout<<"pc\t"<<pc<<endl;
				while(instr[ip][0] =='.' || instr[ip].find(".") != string::npos)
					ip++;
				//��opcode 
				for(int j=0; j<opc.size();j++){
				
					string key = opc[j].name;
					string del="\0";
				
					for (int m=0; m <opc[j].name.length(); m++){  
						if((int)opc[j].name[m]>=97 && (int)opc[j].name[m]<=122) //a~z 
	       					key[m] = toupper(key[m]);  //�p�g�ܤj�g 
	       				else
	       					key[m] = tolower(key[m]); // �j�g�ܤp�g  
					}	
					
					if(grp[i].opcode.name[0]=='+'){
						for(int k=1; k<grp[i].opcode.name.length(); k++)
							del=del+grp[i].opcode.name[k];
						if(opc[j].name == del || key == del){
							code.mc=opc[j].opcode;
							format=opc[j].format;
						}	
						
					}
					else{
						if(opc[j].name == grp[i].opcode.name || key == grp[i].opcode.name){
							code.mc=opc[j].opcode;
							format=opc[j].format;
						}
					}		
	
				}
				
			//	cout<<"mc:  "<<code.mc<<endl;
				
				if(grp[i].opcode.name=="START" || grp[i].opcode.name=="start"){
					pc=grp[i].op1.name;
					
					while(pc.length()<4)
						pc="0"+pc;
				} 
	
			//	cout<<"pc set: "<<pc<<endl;
				//�պA�� 
				string lebaladdr="\0";
			//	cout<<"name:"<<grp[i].op1.name<<endl;
				for(int m=0; m<i && grp[i].op1.name!="\0"; m++){  //�o��lebal���e���X�{�L 
					if(grp[m].label.name==grp[i].op1.name){ //m���e�X�{  i�{�b operand
						lebaladdr=mc[m].addr;
						break;
					}
				}
				
			//	cout<<"lebaladdr: "<<lebaladdr<<endl;
				//lebaladdr=="\0" forward ref
				if(lebaladdr=="\0"&&i!=0){
					string ok="f";
					for(int m=0; m<cft.size()&&grp[i].op1.name[0]!='='; m++){ //operand�w�b�պA���� 
						if(grp[i].op1.name==cft[m].lebal){
							cft[m].mcip.push_back(i);
							cft[m].addr.push_back(pc);
							cft[m].format.push_back(format);
							code.addr=pc;
							cft[m].cd.push_back(code);
							ok="t";
							break;
							//cout<<"code.addr3:\t"<<code.addr<<endl;
						}
					}
					
					if(ok=="f"){ 
						if(grp[i].op1.name[0]!='='){
					
							confi temp;
							temp.lebal=grp[i].op1.name;
							temp.addr.push_back(pc);
							temp.mcip.push_back(i);
							temp.format.push_back(format);
							code.addr=pc;
							temp.cd.push_back(code);
							cft.push_back(temp);
						}
						else{  //literal
							lit tmp;
							tmp.format=format;
							tmp.lebal=grp[i].op1.name;
							tmp.mcip=i;
							code.addr=pc;
							tmp.mc=code.mc;
							lithash(tmp);							
						}
						//cout<<"code.addr4:\t"<<code.addr<<endl;
					}
				}
				
			//	cout<<"lebaladdr: "<<lebaladdr<<endl;
			if(grp[i].opcode.name=="BYTE" || grp[i].opcode.name=="byte"){
	
					if(instr[ip].find("C'") != string::npos || instr[ip].find("c'") != string::npos){
						code.addr=pc;
						mc.push_back(code);					
						pc=pcadd(pc, 3);
	
					}
					else if(instr[ip].find("X'") != string::npos || instr[ip].find("x'") != string::npos){
						code.addr=pc;
						code.mc=code.mc+grp[i].op1.name;
						mc.push_back(code);						
						pc=pcadd(pc, 1);
					}
					else{
						code.addr=pc;
						mc.push_back(code);				
					}
				
				
				//cout<<pc<<endl;
			}
			else if(grp[i].opcode.name=="WORD" || grp[i].opcode.name=="word"){
				code.mc=cvttotw(grp[i].op1.name, 16);
				code.addr=pc;
				mc.push_back(code);
				pc=pcadd(pc, 3);
			}
			else if(grp[i].opcode.name=="RESW" || grp[i].opcode.name=="resw"){
				code.addr=pc;
				mc.push_back(code);			
			 	str=cvttotw(grp[i].op1.name, 16);
			 	//cout<<"resw   str:\t"<<str<<endl;
				for(tp=0; tp<str.length() && str[tp]=='0'; tp++);
				ans="\0";
				for(;tp<str.length();tp++)
					ans=ans+str[tp];
			//	cout<<"resw   ans\t"<<atoi(ans.c_str())*3<<endl;
				for(int k=atoi(ans.c_str()); k>0; k--)
					pc=pcadd(pc, 3);
			}
			else if(grp[i].opcode.name=="RESB" || grp[i].opcode.name=="resb"){
				code.addr=pc;
				mc.push_back(code);			
				str=cvttotw(grp[i].op1.name, 16);
				//	cout<<"str:\t"<<str<<endl;
			//	if(fname.find("sicxe") != string::npos || fname.find("SICXE") != string::npos){
				//	pc="\0";
				//	pc=pc+str[2]+str[3]+str[4]+str[5];
				//	cout<<"pc after reab:\t\t\t\t\t"<<pc<<endl;
			//	}
			///	else{
				
					for(tp=0; tp<str.length() && str[tp]=='0'; tp++);
					ans="\0";
				//	cout<<str[tp]<<tp<<endl;
					for(;tp<str.length();tp++)
						ans=ans+str[tp];
			
					for(int k=0; ans.length()<4; k++)
						ans="0"+ans;  //000C
					//	cout<<ans<<"\t"<<pc<<endl;
					string six="0000";
					int sub=0;
				for(int k=3; k>=0; k--){
					
							if(ans[k]=='A')
								sub=sub+10;
							else if(ans[k]=='B')
								sub=sub+11;
							else if(ans[k]=='C')
								sub=sub+12;
							else if(ans[k]=='D')
								sub=sub+13;
							else if(ans[k]=='E')
								sub=sub+14;
							else if(ans[k]=='F')
								sub=sub+15;
							else
								sub=(int)ans[k]-48;
						//	cout<<"anssub: "<<sub<<endl;
							if(pc[k]=='A')
								sub=sub+10;
							else if(pc[k]=='B')
								sub=sub+11;
							else if(pc[k]=='C')
								sub=sub+12;
							else if(pc[k]=='D')
								sub=sub+13;
							else if(pc[k]=='E')
								sub=sub+14;
							else if(pc[k]=='F')
								sub=sub+15;
							else
								sub=sub+(int)pc[k]-48;	
							//	cout<<"sub: "<<sub<<endl;				
					if(sub>9){
						if(sub>15){
							sub=sub-16;
							if(sub==10)
								six[k]='A';
							else if(sub==11)
								six[k]='B';
							else if(sub==12)
								six[k]='C';
							else if(sub==13)
								six[k]='D';
							else if(sub==14)
								six[k]='E';
							else if(sub==15)
								six[k]='F';					
							sub=1;
						}
						else{
							if(sub==10)
								six[k]='A';
							else if(sub==11)
								six[k]='B';
							else if(sub==12)
								six[k]='C';
							else if(sub==13)
								six[k]='D';
							else if(sub==14)
								six[k]='E';
							else if(sub==15)
								six[k]='F';
							sub=0;
						}
					}
					else{
						string a=int2str(sub);
						six[k]=a[0];
					
						sub=0;
					}
					//cout<<sub<<"\t"<<six[k]<<endl;
				}		

				//	cout<<"ans\t"<<atoi(ans.c_str())<<endl;
				//	tp=atoi(ans.c_str())+atoi(pc.c_str());
				//	pc=int2str(tp);
				pc=six;
			//	cout<<six<<endl;
				//}
			}
			else if(grp[i].opcode.name=="END" || grp[i].opcode.name=="end"||grp[i].opcode.name=="ltorg"||grp[i].opcode.name=="LTORG"){
				code.addr="\0";
				code.mc="\0";
				pc=pcadd(pc, 3);
				mc.push_back(code);
				//literal
				for(int k=0; k<literal.size(); k++){
					if(literal[k].lebal!="\0"){
				
						if(fname.find("sicxe") != string::npos || fname.find("SICXE") != string::npos){
							string tmpaddr;
							if(format=="1")
								tmpaddr=pcadd(pc, 1);
							else if(format=="2"){
								tmpaddr=pcadd(pc, 1);
								tmpaddr=pcadd(tmpaddr, 1);
							}
							else if(grp[i].opcode.name[0]=='+'){
								tmpaddr=pcadd(pc, 3);
								tmpaddr=pcadd(tmpaddr, 1);
							}
							else
								tmpaddr=pcadd(pc, 3);
							//cout<<"tmpaddr:\t\t\t"<<tmpaddr<<endl;	
							code=createmc( pc, mc[literal[k].mcip], literal[k].format, grp[literal[k].mcip], tmpaddr, grp);
							code.addr=pc;
							if(grp[i].opcode.name!="START" && grp[i].opcode.name!="start") 
								pc=tmpaddr;
						}
						else{
							code=	sic(pc, mc[literal[k].mcip], grp[literal[k].mcip]);
							code.addr=pc;
							if(grp[i].opcode.name!="START" && grp[i].opcode.name!="start") 
								pc=pcadd(pc, 3);
						}
						
					}
				}
			}
			else if(grp[i].opcode.name=="EQU" || grp[i].opcode.name=="equ"){
		
				str=cvttotw(grp[i].op1.name, 16);
					pc="\0";
					pc=pc+str[2]+str[3]+str[4]+str[5];
					//cout<<"pc after reab:\t\t\t\t\t"<<pc<<endl;
					code.addr=pc;
					mc.push_back(code);	
					pc=pcadd(pc, 3);				
			}
			else{
			//	cout<<"code.addr1:\t"<<code.addr<<endl;
				
				if(fname.find("sicxe") != string::npos || fname.find("SICXE") != string::npos){
					string tmpaddr;
					if(format=="1")
						tmpaddr=pcadd(pc, 1);
					else if(format=="2"){
						tmpaddr=pcadd(pc, 1);
						tmpaddr=pcadd(tmpaddr, 1);
					}
					else if(grp[i].opcode.name[0]=='+'){
						tmpaddr=pcadd(pc, 3);
						tmpaddr=pcadd(tmpaddr, 1);
					}
					else
						tmpaddr=pcadd(pc, 3);
					//cout<<"tmpaddr:\t\t\t"<<tmpaddr<<endl;	
					code=createmc( lebaladdr, code, format, grp[i], tmpaddr, grp);
					code.addr=pc;
					if(grp[i].opcode.name!="START" && grp[i].opcode.name!="start") 
						pc=tmpaddr;
				}
				else{
					code=	sic(lebaladdr, code, grp[i]);
					code.addr=pc;
					if(grp[i].opcode.name!="START" && grp[i].opcode.name!="start") 
						pc=pcadd(pc, 3);
				}	
	
				mc.push_back(code);
	
			//	cout<<"done:(code) "<<mc[i].mc<<endl;
						//�ɾ����X (in cofi tb) 
			}
		//	cout<<"code.addr2:\t"<<code.addr<<endl;
						for(int n=0; n<cft.size(); n++){
							if(grp[i].label.name!="\0"){
								if(grp[i].label.name==cft[n].lebal){
									for(int m=0; m<cft[n].mcip.size(); m++){
										if(fname.find("sicxe") != string::npos || fname.find("SICXE") != string::npos){
												string tmpaddr1;
												if(cft[n].format[m]=="1")
													tmpaddr1=pcadd(mc[cft[n].mcip[m]].addr, 1);
												else if(cft[n].format[m]=="2"){
													tmpaddr1=pcadd(mc[cft[n].mcip[m]].addr, 1);
													tmpaddr1=pcadd(tmpaddr1, 1);
												}
												else if( grp[cft[n].mcip[m]].opcode.name[0]=='+'){
													tmpaddr1=pcadd(mc[cft[n].mcip[m]].addr, 3);
													tmpaddr1=pcadd(tmpaddr1, 1);
												}
												else
													tmpaddr1=pcadd(mc[cft[n].mcip[m]].addr, 3);
											//	cout<<"tmpaddr1:\t\t\t"<<tmpaddr1<<endl;
												mc[cft[n].mcip[m]]=createmc( code.addr,cft[n].cd[m] , cft[n].format[m], grp[cft[n].mcip[m]], tmpaddr1, grp);
												
										}
										else
											mc[cft[n].mcip[m]]=sic(code.addr,cft[n].cd[m], grp[cft[n].mcip[m]]);
									//	cout<<"done:(fix code) "<<mc[cft[n].mcip[m]].mc<<endl;
									}
								}
							}
						}
						
			}			//cout<<endl;

		}
		
	/*	cout<<endl<<"aaaaaaa"<<endl;
		for(int i=0; i<mc.size(); i++){ 
			cout<<grp[i].label.name<<"\t"<<grp[i].opcode.name<<"\t"<<grp[i].op1.name<<"\t"<<mc[i].mc<<endl;
	 }*/
	}
	
	mch sic(string lebaladdr, mch code, tkgrp grp){
		if(code.mc!="\0"){
			
			if(lebaladdr!="\0"){
			//	cout<<lebaladdr<<endl;
				string tmp ;
				tmp= tmp+lebaladdr[0];
			//	cout<<tmp<<endl;
				if(grp.op1.name=="X"||grp.op1.name=="x"||grp.op2.name=="X"||grp.op2.name=="x")
					code.mc=code.mc+pcadd( tmp, 8)[3]+lebaladdr[1]+lebaladdr[2]+lebaladdr[3];
				else
					code.mc=code.mc+lebaladdr;
				code.done="t";
			}
			else
				code.done="f";
		}
		
		while(grp.opcode.tb==1 && code.mc.length()<6)
			code.mc=code.mc+"0";
	//	cout<<"code:  "<<code.mc<<endl;
		return code;
	}
	
	mch createmc(string ta, mch code, string format, tkgrp grp, string pc, vector<tkgrp> vgrp){
	//	cout<<"createmc pc/ta: "<<pc<<"\t"<<ta<<endl;
		if(code.mc!="\0"){
	
			if(format=="1"){
				code.done="t";
			}
			else if(format=="2"){
				int tmpv=0;
				if(grp.op1.tb==3 ){
					tmpv=grp.op1.val-1;
					code.mc=code.mc+int2str(tmpv);
				}
				
				if( grp.op2.tb==3){
					tmpv=grp.op2.val-1;
					code.mc=code.mc+int2str(tmpv);
				}
				else
					code.mc=code.mc+"0";


					code.done="t";
			}
			else if(format=="3/4"){
				string xbpe;
					
				if(grp.op1.name=="X"||grp.op1.name=="x"||grp.op2.name=="X"||grp.op2.name=="x")
					xbpe=xbpe+"1";
				else
					xbpe=xbpe+"0";
				string op;								
				//e
				if(grp.opcode.name[0]=='+'){ //e=1 format4 done
					xbpe=xbpe+"001";
					string op=code.mc;
					op= pcadd( op, 3);
					code.mc="\0";
					code.mc=code.mc+op[2]+op[3];
				//	cout<<"op+3:\t\t\t\t\t"<<code.mc<<endl;
					if(ta!="\0"){
						code.mc=code.mc+cvt(xbpe, 2)+"0"+ta;
						code.done="t";
					}
					else
						code.done="f";
				}
				else{ //format3
					//b or p			
					string disp=caldisp(ta, pc);	//b
				
					if(disp.length()<=3){
						while(disp.length()<3)
							disp="0"+disp;
						xbpe=xbpe+"010";
					}
					else{
						
						for(int y=0; y<vgrp.size(); y++){
							if(vgrp[y].opcode.name == "BASE" || vgrp[y].opcode.name == "base"){
								pc=mc[y].addr;
								break;
							}
						}
						
						disp=caldisp(ta, pc);
						while(disp.length()<3)
							disp="0"+disp;
						xbpe=xbpe+"100";
					}
					
					 op=code.mc;
					op= pcadd( op, 3);
					code.mc="\0";
					code.mc=code.mc+op[2]+op[3];
				//	cout<<"op+3:\t\t\t\t\t"<<code.mc<<endl; 
					
					if(cvt(xbpe, 2)=="10")
						code.mc=code.mc+"A";
					else if(cvt(xbpe, 2)=="11")
						code.mc=code.mc+"B";
					else if(cvt(xbpe, 2)=="12")
						code.mc=code.mc+"C";
					else if(cvt(xbpe, 2)=="13")
						code.mc=code.mc+"D";
					else if(cvt(xbpe, 2)=="14")
						code.mc=code.mc+"E";
					else if(cvt(xbpe, 2)=="15")
						code.mc=code.mc+"F";
					else
						code.mc=code.mc+cvt(xbpe, 2);	
					code.mc=code.mc+disp;
				
				}
					
			}
		}
		
		return code;
	}

	string cvt(string pc, int cvt){
				int tenpc=0;
				for(int y=0, z=pc.length()-1; y<pc.length(); y++, z--){
					if(pc[y]=='A')
						tenpc=tenpc+10*pow(cvt, z);
					else if(pc[y]=='B')
						tenpc=tenpc+11*pow(cvt, z);
					else if(pc[y]=='C')
						tenpc=tenpc+12*pow(cvt, z);
					else if(pc[y]=='D')
						tenpc=tenpc+13*pow(cvt, z);
					else if(pc[y]=='E')
						tenpc=tenpc+14*pow(cvt, z);
					else if(pc[y]=='F')
						tenpc=tenpc+15*pow(cvt, z);
					else
						tenpc=tenpc+((int)pc[y]-48)*pow(cvt, z);
				}
				
				return int2str(tenpc);	
	}
	
	string cvttotw(string str, int cvt){ //6 bits
		
		int tmp=atoi(str.c_str());
		string ans, temp;
		
		if(tmp>=pow(cvt, 5)){
			tmp=tmp-pow(cvt, 5);
			ans="1"+ans;
		}
		else
			ans="0"+ans;
		
		if(tmp>=pow(cvt, 4)){
			tmp=tmp-pow(cvt, 4);
			ans="1"+ans;
		}
		else
			ans="0"+ans;
					
		if(tmp>=pow(cvt, 3)){
			tmp=tmp-pow(cvt, 3);
			ans="1"+ans;
		}
		else
			ans="0"+ans;
			
		if(tmp>=pow(cvt, 2)){
			tmp=tmp-pow(cvt, 2);
			ans="1"+ans;
		}
		else
			ans="0"+ans;
					
		if(tmp>=pow(cvt, 1)){
			tmp=tmp-pow(cvt, 1);
			ans="1"+ans;
		}
		else
			ans="0"+ans;
					
		int tlen=ans.length();
	
		for (int i=0;i<tlen/2;i++)
      		ans[i]^=ans[tlen-1-i]^=ans[i]^=ans[tlen-1-i]; 
			  
				if(cvt==16){
				
					if(int2str(tmp)=="10")
						ans=ans+"A";
					else if(int2str(tmp)=="11")
						ans=ans+"B";
					else if(int2str(tmp)=="12")
						ans=ans+"C";
					else if(int2str(tmp)=="13")
						ans=ans+"D";
					else if(int2str(tmp)=="14")
						ans=ans+"E";
					else if(int2str(tmp)=="15")
						ans=ans+"F";
					else
						ans=ans+int2str(tmp);				
				}
				else  
					ans=ans+int2str(tmp);		
		//temp="\0"+ans[5]+ans[4]+ans[3]+ans[2]+ans[1]+ans[0];

		return ans;	
	}
	
string caldisp(string ta, string pc){
	string tenta=cvt(ta, 16);
	string tenpc=cvt(pc, 16);
	string disp, ans;
	int tmp= atoi(tenta.c_str()) - atoi(tenpc.c_str());
	if(tmp>0){ //ta-pc(10�i��)=tmp ->  ��2 ->3 nibber(12 bits)�n�ɺ� -> ��16
		ans=cvttotw(int2str(tmp), 2);
		
		for(int i=ans.length()-1; i<12; i++)
			ans="0"+ans;
		
		string temp="\0";
		for( int k=0; k<12; k=k+4){
			temp=temp+ans[k+3]+ans[k+2]+ans[k+1]+ans[k];
			disp=disp+cvt(temp, 2);
			temp="\0";
		}
		
		return disp;
	}
	else{  //��2-> pc �� 1 to 0�A0 to 1 �� +1 (���G�]��af) -> af�Mta�ۥ[(2�i��) ->  ��16
			//3 nibber(12 bits)�n�ɺ� 
		
		string tmpc=cvttotw(tenpc, 2);
		string	tmta=cvttotw(tenta, 2);
	//	cout<<"(2)pc: "<<tmpc<<"        (2)ta: "<<tmta<<endl;
		
		for( int k=tmpc.length(); k<12; k++)
			tmpc="0"+tmpc;
		for( int k=tmta.length(); k<12; k++)
			tmta="0"+tmta;
						
		for(int k=0; k<tmpc.length(); k++)
			if(tmpc[k]=='1')
				tmpc[k]='0';
			else
				tmpc[k]='1';
		//cout<<"12bits: pc/ta"<<tmpc<<"\t"<<tmta<<endl;
		tmpc=addsix(tmpc, "000000000001");
		//cout<<"add1:  "<<tmpc<<endl;
		 disp=addsix(tmpc, tmta);	
	//	cout<<"10to2:  "<<disp<<endl;

		string temp="\0";	
		for( int k=0; k<12; k=k+4){
			temp=temp+disp[k]+disp[k+1]+disp[k+2]+disp[k+3];
					if(cvt(temp, 2)=="10")
						ans=ans+"A";
					else if(cvt(temp, 2)=="11")
						ans=ans+"B";
					else if(cvt(temp, 2)=="12")
						ans=ans+"C";
					else if(cvt(temp, 2)=="13")
						ans=ans+"D";
					else if(cvt(temp, 2)=="14")
						ans=ans+"E";
					else if(cvt(temp, 2)=="15")
						ans=ans+"F";
					else
						ans=ans+cvt(temp, 2);

		//	cout<<"2to16: "<<ans<<endl;
			temp="\0";
		}		
	//	cout<<"disp:\t\t\t\t"<<ans<<endl;
		return ans;
		
	}

}

string addsix(string num, string num1){  //6bits(2)
	
	int tmp=0;
	string ans="000000000000";
	for(int i=11; i>=0; i--){
		if(num[i]=='1' && num1[i]=='1'){
			if(tmp==1){
				ans[i]='1';
				tmp=0;
			}	
			else	
				ans[i]='0';
			tmp=1;
		}
		else{
			if((num[i]=='1' && num1[i]=='0' )|| (num[i]=='0' && num1[i]=='1'))
				ans[i]='1';
			else if(num[i]=='0' && num1[i]=='0')
				ans[i]='0';
				
			if(tmp==1){
				if(ans[i]=='0'){
					ans[i]='1';
					tmp=0;
				}
				else{
					ans[i]='0';
					tmp=1;
				}
			}			
		}
		


	}
	
	return ans;
}

string int2str(int &i)
{
stringstream ss; //�ϥΪ�??(�q?)���۳y��?
ss << i;
return ss.str();
}

	string pcadd( string tmp, int ADD){
		if(tmp.length()==1)
			tmp="000"+tmp;
		else if(tmp.length()==2)
			tmp="00"+tmp;
		else if(tmp.length()==3)
			tmp="0"+tmp;
		string str="0123456789ABCDEF";
			
		int num=0;
		for(int i=0; i<16; i++){
			if(str[i]==tmp[3]){
				if((i+ADD)>=16){
					tmp[3]=str[i+ADD-16];
					num++;
					break;
				}	
				else{
					tmp[3]=str[i+ADD];
					break;
				}
			}
		}
		

		if(num==1){
			for(int i=0; i<16; i++){
				if(str[i]==tmp[2]){
					if((i+1)>=16){
						tmp[2]=str[i+1-16];
						num++;
						break;
					}	
					else{
						tmp[2]=str[i+1];
						break;
					}
				}
			}			
		}
			
		if(num==2){
			for(int i=0; i<16; i++){
				if(str[i]==tmp[1]){
					if((i+1)>=16){
						tmp[1]=str[i+1-16];
						num++;
						break;
					}	
					else{
						tmp[1]=str[i+1];
						break;
					}
				}
			}			
		}
	
		if(num==3){
			for(int i=0; i<16; i++){
				if(str[i]==tmp[0]){
					if((i+1)>=16){
						tmp[0]=str[i+1-16];
						num++;
						break;
					}	
					else{
						tmp[0]=str[i+1];
						break;
					}
				}
			}			
		}	
	
		return tmp;
	}


};

int main() {
	int val=0;
	bool exit=false;
	string fname, str;
	tablefc tb ;
	tb.build1to4();
	tb.read(fname);
	tb.cut();
	Syntax sy;
	sy.check(tb.altk, tb.instr);
	MCC mkc;
	mkc.bdopcode();
	mkc.mcc(sy.grp, tb.instr, fname);

			str=fname+"_out.txt";
          ofstream out(str.c_str());  //��X�� 
          
			
			if(fname.find("sicxe") != string::npos || fname.find("SICXE") != string::npos){
				out<<"Line  Location  Source code                              Object code"<<endl;
				out<<"----  -------- -------------------------                 -----------"<<endl;
			}
			else
				out<<"Line	Loc	Source statement		             Object code"<<endl;
		//	for(int k=0; k<tb.instr.size(); k++)
			//	cout<<tb.instr[k]<<endl;
          for(int i=0, j=0, num=0; i < tb.instr.size(); i++, num++){
			
		
          	if(tb.instr[i][0]!='.'){
				if(tb.instr[i]=="\0")
					num--;
				else
                	out <<(5*(num+1));
				out<<"\t"<< mkc.mc[j].addr<<"\t"<<std::left<<setw(40)<<tb.instr[i];
				out<<setw(10)<<mkc.mc[j].mc;
				out<<endl;
							if(tb.instr[i]!="\0")
				               cout <<(5*(num+1));
							   cout<<"\t"<<mkc.mc[j].addr;
							   cout<<"\t"<<std::left<<setw(40)<<tb.instr[i];
				cout<<setw(10)<<mkc.mc[j].mc;
				cout<<endl;	
				j++;
			}
			else{
				out <<tb.instr[i]<<endl;	
				cout <<tb.instr[i]<<endl;	
			}

		
				
            } // for
			      
            out.close(); 
   // cout<<"end"<<endl;
}
