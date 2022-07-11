#include <iostream>
#include <stdlib.h>
#include <bitset>
#include <stdio.h>

using namespace std;
//16-bit registers
#define AX genregs16[0]
#define CX genregs16[1]
#define DX genregs16[2]
#define BX genregs16[3]



//8-bit registers
#define AL genregs8[0]
#define CL genregs8[1]
#define DL genregs8[2]
#define BL genregs8[3]
#define AH genregs8[4]
#define CH genregs8[5]
#define DH genregs8[6]
#define BH genregs8[7]

class registers{

public:
unsigned short genregs8[8];
unsigned short genregs16[4];
registers();
void updateRegs8(unsigned short AL1, unsigned short CL1, unsigned short DL1, unsigned short BL1, unsigned short AH1, unsigned short CH1, 
        unsigned short DH1, unsigned short BH1);
void updateRegs16(unsigned short AX1, unsigned short CX1, unsigned short DX1, unsigned short BX1);
void display(unsigned short* G);
void printregs();	
};
void registers::printregs(){
    cout <<"---------------------------------------------------------------------------" << endl;
    cout << hex;
	cout << "AX= " << AX << " " << "AH= "  << AH << " " << "AL= " << AL << " " << endl;  
	cout << "CX= " << CX << " " << "CH= " << CH << " " << "CL= " << CL << " " << endl;
	cout << "DX= " << DX << " " << "DH= " << DH << " " << "DL= " << DL << " " << endl;
	cout << "BX= " << BX << " " << "BH= " << BH << " " << "BL= " << BL << " " << endl;
	cout << dec;

}

void registers::updateRegs16(unsigned short AX1, unsigned short CX1, unsigned short DX1, unsigned short BX1){
AX=AX1;
CX=CX1;
DX=DX1;
BX=BX1;

AH = (AX/256)*256;
CH = (CX/256)*256;   
DH = (DX/256)*256;                            
BH = (BX/256)*256;
AL = AX - AH;
CL = CX - CH;   
DL = DX - DH;             
BL = BX - BH;


}
registers::registers(){ //default constructor
	AX=0,CX=0,DX=0,BX=0,AL=0,CL=0,DL=0,BL=0,AH=0,CH=0,DH=0,BH=0;
}
void registers::updateRegs8(unsigned short AL1, unsigned short CL1, unsigned short DL1, unsigned short BL1, unsigned short AH1, unsigned short CH1, 
        unsigned short DH1, unsigned short BH1)
{
	AL=AL1;
	CL=CL1;
	DL=DL1;
	BL=BL1;
	AH=AH1*256;
	CH=CH1*256;
	DH=DH1*256;
	BH=BH1*256;

   
    AX = AH+AL;
    CX = CH+CL;
    DX = DH+DL;
    BX = BH+BL; 
    
}
void updatedumreg(unsigned short &AX2,unsigned short &BX2,unsigned short &CX2,unsigned short &DX2,unsigned short &AL2,unsigned short &CL2
,unsigned short &DL2,unsigned short &BL2,unsigned short &AH2,unsigned short &CH2,unsigned short &DH2,unsigned short &BH2 )
{
if(AX2==0){
AX2=AH2+AL2;
}
else if(BX2==0){
BX2=BH2+BL2;
}
else if(CX2==0){
CX2=CH2+CL2;
}
else if(DX2==0){
DX2=DH2+DL2;
}

if(AX2!=0){
    AL2=AX2-AH2;
    AH2=(AX2/256)*256;
}
else if(BX2!=0){
    BL2=BX2-BH2;
    BH2=(BX2/256)*256;
}
else if(CX2!=0){
    CL2=CX2-CH2;
    CH2=(CX2/256)*256;
}
else if(DX2!=0){
    DL2=DX2-DH2;
    DH2=(DX2/256)*256;
}
  }
  void emulatordisplay(unsigned short *arr,int num1){
cout << "------------------DISPLAY-------------------" << endl;
     for(int i=0;i<num1+1;i++){
        printf("%c ",arr[i]);
     }
cout << endl;

  }
int main(){
bool show=0;
int num;
unsigned short display[100];
registers GEN;
unsigned short AX1,BX1,CX1,DX1,AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1;
int start = 100;
unsigned char memory[100000];
unsigned short IP = 100; 
unsigned short placeholder;
//Enter a ".com" file to be executed 
 FILE *filee = fopen("helloEX1.com", "rb"); 
    
    if (!filee) { 
        cout<<"FILE NOT FOUND"<<endl;
    }
    else
    {
        fseek(filee,0,SEEK_END);
        long ss = ftell(filee);
        fseek(filee,0,SEEK_SET);
        fread(start + memory, 1, ss, filee);
        fclose(filee);

       
    }
    cout << "Staring IP: " << IP << endl;
     unsigned char byte;
while(1){
	byte = memory[IP++];
	//updatedumreg(AX1,BX1,CX1,DX1,AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1); 
	switch (byte)
	{
//xchg 8bit with 8bit 
case 0x86:
byte=memory[IP++];
for(int i=0;i<8;i++){
    if((0xC0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){placeholder=AL1;
            AL1=AL1;
            AL1=placeholder;
        }
        else if(i==1){placeholder=AL1;
            AL1=CL1;
            CL1=placeholder;
        }
        else if(i==2){placeholder=AL1;
            AL1=DL1;
            DL1=placeholder;
        }
        else if(i==3){placeholder=AL1;
            AL1=BL1;
            BL1=placeholder;
        }
        else if(i==4){placeholder=AL1;
            AL1=AH1;
            AH1=placeholder;
        }
        else if(i==5){placeholder=AL1;
            AL1=CH1;
            CH1=placeholder;
        }
        else if(i==6){placeholder=AL1;
            AL1=DH1;
            DH1=placeholder;
        }
        else if(i==7){placeholder=AL1;
            AL1=BH1;
            BH1=placeholder;
        }
        
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    
    cout << IP << " XCHG " << " AL,"<<regarray[i] << endl; 
    break;
    }
    if((0xC8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){placeholder=CL1;
            CL1=AL1;
            AL1=placeholder;
        }
        else if(i==1){placeholder=CL1;
            CL1=CL1;
            CL1=placeholder;
        }
        else if(i==2){placeholder=CL1;
            CL1=DL1;
            DL1=placeholder;
        }
        else if(i==3){placeholder=CL1;
            CL1=BL1;
            BL1=placeholder;
        }
        else if(i==4){placeholder=CL1;
            CL1=AH1;
            AH1=placeholder;
        }
        else if(i==5){placeholder=CL1;
            CL1=CH1;
            CH1=placeholder;
        }
        else if(i==6){placeholder=CL1;
            CL1=DH1;
            DH1=placeholder;
        }
        else if(i==7){placeholder=CL1;
            CL1=BH1;
            BH1=placeholder;
        }
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " XCHG " << " CL,"<<regarray[i] << endl; 
    break;
    }
    if((0xD0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){placeholder=DL1;
            DL1=AL1;
            AL1=placeholder;
        }
        else if(i==1){placeholder=DL1;
            DL1=CL1;
            CL1=placeholder;
        }
        else if(i==2){placeholder=DL1;
            DL1=DL1;
            DL1=placeholder;
        }
        else if(i==3){placeholder=DL1;
            DL1=BL1;
            BL1=placeholder;
        }
        else if(i==4){placeholder=DL1;
            DL1=AH1;
            AH1=placeholder;
        }
        else if(i==5){placeholder=DL1;
            DL1=CH1;
            CH1=placeholder;
        }
        else if(i==6){placeholder=DL1;
            DL1=DH1;
            DH1=placeholder;
        }
        else if(i==7){placeholder=DL1;
            DL1=BH1;
            BH1=placeholder;
        }
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " XCHG " << " DL,"<<regarray[i] << endl; 
    break;
    }
    if((0xD8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){placeholder=BL1;
            BL1=AL1;
            AL1=placeholder;
        }
        else if(i==1){placeholder=BL1;
            BL1=CL1;
            CL1=placeholder;
        }
        else if(i==2){placeholder=BL1;
            BL1=DL1;
            DL1=placeholder;
        }
        else if(i==3){placeholder=BL1;
            BL1=BL1;
            BL1=placeholder;
        }
        else if(i==4){placeholder=BL1;
            BL1=AH1;
            AH1=placeholder;
        }
        else if(i==5){placeholder=BL1;
            BL1=CH1;
            CH1=placeholder;
        }
        else if(i==6){placeholder=BL1;
            BL1=DH1;
            DH1=placeholder;
        }
        else if(i==7){placeholder=BL1;
            BL1=BH1;
            BH1=placeholder;
        }
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " XCHG " << " BL,"<<regarray[i] << endl; 
    break;
    }
if((0xE0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){placeholder=AH1;
            AH1=AL1;
            AL1=placeholder;
        }
        else if(i==1){placeholder=AH1;
            AH1=CL1;
            CL1=placeholder;
        }
        else if(i==2){placeholder=AH1;
            AH1=DL1;
            DL1=placeholder;
        }
        else if(i==3){placeholder=AH1;
            AH1=BL1;
            BL1=placeholder;
        }
        else if(i==4){placeholder=AH1;
            AH1=AH1;
            AH1=placeholder;
        }
        else if(i==5){placeholder=AH1;
            AH1=CH1;
            CH1=placeholder;
        }
        else if(i==6){placeholder=AH1;
            AH1=DH1;
            DH1=placeholder;
        }
        else if(i==7){placeholder=AH1;
            AH1=BH1;
            BH1=placeholder;
        }
        
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    
    cout << IP << " XCHG " << " AH,"<<regarray[i] << endl; 
    break;
    }
    if((0xE8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){placeholder=CH1;
            CH1=AL1;
            AL1=placeholder;
        }
        else if(i==1){placeholder=CH1;
            CH1=CL1;
            CL1=placeholder;
        }
        else if(i==2){placeholder=CH1;
            CH1=DL1;
            DL1=placeholder;
        }
        else if(i==3){placeholder=CH1;
            CH1=BL1;
            BL1=placeholder;
        }
        else if(i==4){placeholder=CH1;
            CH1=AH1;
            AH1=placeholder;
        }
        else if(i==5){placeholder=CH1;
            CH1=CH1;
            CH1=placeholder;
        }
        else if(i==6){placeholder=CH1;
            CH1=DH1;
            DH1=placeholder;
        }
        else if(i==7){placeholder=CH1;
            CH1=BH1;
            BH1=placeholder;
        }
        
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    
    cout << IP << " XCHG " << " CH,"<<regarray[i] << endl; 
    break;
    }
    if((0xF0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){placeholder=DH1;
            DH1=AL1;
            AL1=placeholder;
        }
        else if(i==1){placeholder=DH1;
            DH1=CL1;
            CL1=placeholder;
        }
        else if(i==2){placeholder=DH1;
            DH1=DL1;
            DL1=placeholder;
        }
        else if(i==3){placeholder=DH1;
            DH1=BL1;
            BL1=placeholder;
        }
        else if(i==4){placeholder=DH1;
            DH1=AH1;
            AH1=placeholder;
        }
        else if(i==5){placeholder=DH1;
            DH1=CH1;
            CH1=placeholder;
        }
        else if(i==6){placeholder=DH1;
            DH1=DH1;
            DH1=placeholder;
        }
        else if(i==7){placeholder=DH1;
            DH1=BH1;
            BH1=placeholder;
        }
        
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    
    cout << IP << " XCHG " << " DH,"<<regarray[i] << endl; 
    break;
    }
if((0xF8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){placeholder=BH1;
            BH1=AL1;
            AL1=placeholder;
        }
        else if(i==1){placeholder=BH1;
            BH1=CL1;
            CL1=placeholder;
        }
        else if(i==2){placeholder=BH1;
            BH1=DL1;
            DL1=placeholder;
        }
        else if(i==3){placeholder=BH1;
            BH1=BL1;
            BL1=placeholder;
        }
        else if(i==4){placeholder=BH1;
            BH1=AH1;
            AH1=placeholder;
        }
        else if(i==5){placeholder=BH1;
            BH1=CH1;
            CH1=placeholder;
        }
        else if(i==6){placeholder=BH1;
            BH1=DH1;
            DH1=placeholder;
        }
        else if(i==7){placeholder=BH1;
            BH1=BH1;
            BH1=placeholder;
        }
        
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    
    cout << IP << " XCHG " << " BH,"<<regarray[i] << endl; 
    break;
    }

}break;
//xchg 16bitregs with 16bitregs
case 0x87:
byte=memory[IP++];
for(int i=0;i<3;i++){
if((0xC9+i)==byte){
unsigned short subArray[3]={CX1,DX1,BX1};
string regarray[3]={"CX","DX","BX"};
        if(i==0){
            placeholder=CX1;
            CX1=CX1;
            CX1=placeholder;}
        else if(i==1){placeholder=CX1;
            CX1=DX1;
            DX1=placeholder;}
        else if(i==2){placeholder=CX1;
                      CX1=BX1;
                      BX1=placeholder;}
        
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " XCHG " <<" CX," << regarray[i] << endl;
   break; 
 }
 else if((0xD1+i)==byte){
  unsigned short subArray[3]={CX1,DX1,BX1};
  string regarray[3]={"CX","DX","BX"};
        if(i==0){
            placeholder=DX1;
            DX1=CX1;
            CX1=placeholder;}
        else if(i==1){placeholder=DX1;
            DX1=DX1;
            DX1=placeholder;}
        else if(i==2){placeholder=DX1;
                      DX1=BX1;
                      BX1=placeholder;}
        
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " XCHG " <<" DX," << regarray[i] << endl;
   break; 
  }
else if((0xD9+i)==byte){
  unsigned short subArray[3]={CX1,DX1,BX1};
  string regarray[3]={"CX","DX","BX"};
        if(i==0){
            placeholder=BX1;
            BX1=CX1;
            CX1=placeholder;}
        else if(i==1){
            placeholder=BX1;
            BX1=DX1;
            DX1=placeholder;}
        else if(i==2){placeholder=BX1;
                      BX1=BX1;
                      BX1=placeholder;}
        
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " XCHG " <<" BX," << regarray[i] << endl;
   break;
  } 
}break;
//xchg 16bitregs AX
case 0x93:

placeholder=AX1;
AX1=BX1;
BX1=placeholder;
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " XCHG " << " AX,BX " << endl;
break;

case 0x92:

placeholder=AX1;
AX1=DX1;
DX1=placeholder;
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " XCHG " << " AX,DX " << endl;
break;

case 0x91:

placeholder=AX1;
AX1=CX1;
CX1=placeholder;
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " XCHG " << " AX,CX " << endl;
break;
case 0x90://this does nothing
cout << IP << " DEC " << " AX" << endl;
break;
case 0x48:
AX1--;
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " DEC " << " AX" << endl;
break;
case 0x49:
CX1--;
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " DEC " << " CX" << endl;
break;
case 0x4A:
DX1--;
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " DEC " << " DX" << endl;
break;
case 0x4B:
BX1--;
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " DEC " << " BX" << endl;
break;
case 0xFE:
byte=memory[IP++];
for(int i=0;i<8;i++){
    if((0xC0+i)==byte){
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){AL1++;}
        else if(i==1){CL1++;}
        else if(i==2){DL1++;}
        else if(i==3){BL1++;}
        else if(i==4){AH1++;}
        else if(i==5){CH1++;}
        else if(i==6){DH1++;}
        else if(i==7){BH1++;}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " INC " << regarray[i] << endl;
    break;
    }
else if((0xC8+i)==byte){
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){AL1--;}
        else if(i==1){CL1--;}
        else if(i==2) {DL1--;}
        else if(i==3){BL1--;}
        else if(i==4){AH1--;}
        else if(i==5){CH1--;}
        else if(i==6){DH1--;}
        else if(i==7){BH1--;}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " DEC " << regarray[i] << endl;
    break;
       }
}break;
case 0x40:
AX1++;
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << " INC " << " AX" << endl; 
break;  
case 0x41:
CX1++;
GEN.updateRegs16(AX1,CX1,DX1,BX1); 
cout << " INC " << " CX" << endl; 
break; 
case 0x42:
DX1++;
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << " INC " << " DX" << endl;  
break;
case 0x43:
BX1++;
GEN.updateRegs16(AX1,CX1,DX1,BX1); 
cout << " INC " << " BX" << endl; 
break;    
case 0x2A:
byte=memory[IP++];
for(int i=0;i<8;i++){
 if((0xC0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){AL1-=subArray[0];}
        else if(i==1){AL1-=subArray[1];}
        else if(i==2) {AL1-=subArray[2];}
        else if(i==3){AL1-=subArray[3];}
        else if(i==4){AL1-=subArray[4];}
        else if(i==5){AL1-=subArray[5];}
        else if(i==6){AL1-=subArray[6];}
        else if(i==7){AL1-=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " SUB " <<" AL, " << regarray[i] << endl;
}
else if((0xC8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){CL1-=subArray[0];}
        else if(i==1){CL1-=subArray[1];}
        else if(i==2){CL1-=subArray[2];}
        else if(i==3){CL1-=subArray[3];}
        else if(i==4){CL1-=subArray[4];}
        else if(i==5){CL1-=subArray[5];}
        else if(i==6){CL1-=subArray[6];}
        else if(i==7){CL1-=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " SUB " <<" CL, " << regarray[i] << endl;
    }
else if((0xD8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){BL1-=subArray[0];}
        else if(i==1){BL1-=subArray[1];}
        else if(i==2){BL1-=subArray[2];}
        else if(i==3){BL1-=subArray[3];}
        else if(i==4){BL1-=subArray[4];}
        else if(i==5){BL1-=subArray[5];}
        else if(i==6){BL1-=subArray[6];}
        else if(i==7){BL1-=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " SUB " <<" BL, " << regarray[i] << endl;
    }
else if((0xD0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){DL1-=subArray[0];}
        else if(i==1){DL1-=subArray[1];}
        else if(i==2){DL1-=subArray[2];}
        else if(i==3){DL1-=subArray[3];}
        else if(i==4){DL1-=subArray[4];}
        else if(i==5){DL1-=subArray[5];}
        else if(i==6){DL1-=subArray[6];}
        else if(i==7){DL1-=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " SUB " <<" DL, " << regarray[i] << endl;
    }
else if((0xE0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){AH1-=subArray[0];}
        else if(i==1){AH1-=subArray[1];}
        else if(i==2){AH1-=subArray[2];}
        else if(i==3){AH1-=subArray[3];}
        else if(i==4){AH1-=subArray[4];}
        else if(i==5){AH1-=subArray[5];}
        else if(i==6){AH1-=subArray[6];}
        else if(i==7){AH1-=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " SUB " <<" AH, " << regarray[i] << endl;
   }
else if((0xF8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){BH1-=subArray[0];}
        else if(i==1){BH1-=subArray[1];}
        else if(i==2){BH1-=subArray[2];}
        else if(i==3){BH1-=subArray[3];}
        else if(i==4){BH1-=subArray[4];}
        else if(i==5){BH1-=subArray[5];}
        else if(i==6){BH1-=subArray[6];}
        else if(i==7){BH1-=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " SUB " <<" BH, " << regarray[i] << endl;
   }
else if((0xF0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){DH1-=subArray[0];}
        else if(i==1){DH1-=subArray[1];}
        else if(i==2){DH1-=subArray[2];}
        else if(i==3){DH1-=subArray[3];}
        else if(i==4){DH1-=subArray[4];}
        else if(i==5){DH1-=subArray[5];}
        else if(i==6){DH1-=subArray[6];}
        else if(i==7){DH1-=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " SUB " <<" DH, " << regarray[i] << endl;
   }
else if((0xE8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){CH1-=subArray[0];}
        else if(i==1){CH1-=subArray[1];}
        else if(i==2){CH1-=subArray[2];}
        else if(i==3){CH1-=subArray[3];}
        else if(i==4){CH1-=subArray[4];}
        else if(i==5){CH1-=subArray[5];}
        else if(i==6){CH1-=subArray[6];}
        else if(i==7){CH1-=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " SUB " <<" CH, " << regarray[i] << endl;
   }

}break;
//sub al - 8bit immdt
case 0x2C:
AL1-=memory[IP++];
GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
cout << IP << " SUB " <<" AL " << endl;
break;

//8bit reg + 8bit reg
case 0x02:
byte=memory[IP++];
for(int i=0;i<8;i++){
    if((0xC8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){CL1+=subArray[0];}
        else if(i==1){CL1+=subArray[1];}
        else if(i==2) {CL1+=subArray[2];}
        else if(i==3){CL1+=subArray[3];}
        else if(i==4){CL1+=subArray[4];}
        else if(i==5){CL1+=subArray[5];}
        else if(i==6){CL1+=subArray[6];}
        else if(i==7){CL1+=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " ADD " <<" CL, " << regarray[i] << endl;
    }
    else if((0xD8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){BL1+=subArray[0];}
        else if(i==1){BL1+=subArray[1];}
        else if(i==2) {BL1+=subArray[2];}
        else if(i==3){BL1+=subArray[3];}
        else if(i==4){BL1+=subArray[4];}
        else if(i==5){BL1+=subArray[5];}
        else if(i==6){BL1+=subArray[6];}
        else if(i==7){BL1+=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " ADD " <<" BL, " << regarray[i] << endl;
    }
    else if((0xD0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){DL1+=subArray[0];}
        else if(i==1){DL1+=subArray[1];}
        else if(i==2) {DL1+=subArray[2];}
        else if(i==3){DL1+=subArray[3];}
        else if(i==4){DL1+=subArray[4];}
        else if(i==5){DL1+=subArray[5];}
        else if(i==6){DL1+=subArray[6];}
        else if(i==7){DL1+=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " ADD " <<" DL, " << regarray[i] << endl;
    }
    else if((0xC0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){AL1+=subArray[0];}
        else if(i==1){AL1+=subArray[1];}
        else if(i==2) {AL1+=subArray[2];}
        else if(i==3){AL1+=subArray[3];}
        else if(i==4){AL1+=subArray[4];}
        else if(i==5){AL1+=subArray[5];}
        else if(i==6){AL1+=subArray[6];}
        else if(i==7){AL1+=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " ADD " <<" AL, " << regarray[i] << endl;
    }
    else if((0xE0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){AH1+=subArray[0];}
        else if(i==1){AH1+=subArray[1];}
        else if(i==2){AH1+=subArray[2];}
        else if(i==3){AH1+=subArray[3];}
        else if(i==4){AH1+=subArray[4];}
        else if(i==5){AH1+=subArray[5];}
        else if(i==6){AH1+=subArray[6];}
        else if(i==7){AH1+=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " ADD " <<" AH, " << regarray[i] << endl;
}
else if((0xF8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){BH1+=subArray[0];}
        else if(i==1){BH1+=subArray[1];}
        else if(i==2){BH1+=subArray[2];}
        else if(i==3){BH1+=subArray[3];}
        else if(i==4){BH1+=subArray[4];}
        else if(i==5){BH1+=subArray[5];}
        else if(i==6){BH1+=subArray[6];}
        else if(i==7){BH1+=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " ADD " <<" BH, " << regarray[i] << endl;

}
else if((0xF0+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){DH1+=subArray[0];}
        else if(i==1){DH1+=subArray[1];}
        else if(i==2){DH1+=subArray[2];}
        else if(i==3){DH1+=subArray[3];}
        else if(i==4){DH1+=subArray[4];}
        else if(i==5){DH1+=subArray[5];}
        else if(i==6){DH1+=subArray[6];}
        else if(i==7){DH1+=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " ADD " <<" DH, " << regarray[i] << endl;
}
else if((0xE8+i)==byte){
        unsigned short subArray[8]={AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1};
        string regarray[8]={"AL","CL","DL","BL","AH","CH","DH","BH"};
        if(i==0){CH1+=subArray[0];}
        else if(i==1){CH1+=subArray[1];}
        else if(i==2){CH1+=subArray[2];}
        else if(i==3){CH1+=subArray[3];}
        else if(i==4){CH1+=subArray[4];}
        else if(i==5){CH1+=subArray[5];}
        else if(i==6){CH1+=subArray[6];}
        else if(i==7){CH1+=subArray[7];}
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " ADD " <<" CH, " << regarray[i] << endl;
   }

}break;
  //add 8bit regs + 8bit immds     
case 0x80:
byte=memory[IP++];
for(int i=0;i<7;i++){
    if((0xC1+i)==byte){
        unsigned short subArray[7]={0,0,0,0,0,0,0};
        string regarray[7]={"CL","DL","BL","AH","CH","DH","BH"};
        subArray[i]=memory[IP++];
        CL1+=subArray[0];
        DL1+=subArray[1];
        BL1+=subArray[2];
        AH1+=subArray[3];
        CH1+=subArray[4];
        DH1+=subArray[5];
        BH1+=subArray[6];
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " ADD " << regarray[i] << endl;
    break;
    }

else if((0xE9+i)==byte){
        unsigned short subArray[7]={0,0,0,0,0,0,0};
        string regarray[7]={"CL","DL","BL","AH","CH","DH","BH"};
        subArray[i]=memory[IP++];
        CL1-=subArray[0];
        DL1-=subArray[1];
        BL1-=subArray[2];
        AH1-=subArray[3];
        CH1-=subArray[4];
        DH1-=subArray[5];
        BH1-=subArray[6];
    GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
    cout << IP << " SUB " << regarray[i] << endl;
    break;
    }
}break;
//ADD AL to imm8
case 0x04:
AL1+=memory[IP++];
GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
cout << IP << " ADD " <<" AL " << endl; 
break;

case 0x2D: //AX-16 bit imd
AX1-= memory[IP++]+(memory[IP++]*256);
GEN.updateRegs16(AX1,CX1,DX1,BX1);
cout << IP << " SUB " <<" AX " << endl; 
   break;

case 0x2B://16bit regs - 16bit regs
byte=memory[IP++];
if(0xC0==byte){//AX-16bit regs
	AX1-=AX1;
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "AX, AX" << endl;
   break;
}
else if(0xC1==byte){
	AX1-=CX1;
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "AX, CX" << endl;
   break;
}
else if(0xC2==byte){
	AX1-=DX1;
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "AX, DX" << endl;
   break;
}
else if(0xC3==byte){
	AX1-=BX1;
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "AX, BX" << endl;
   break;
}
else if(0xCB==byte){
	CX1-=BX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "CX, BX" << endl;
   break;
}
else if(0xC9==byte){
	CX1-=CX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "CX, CX" << endl;
   break;
}
else if(0xCA==byte){
	CX1-=DX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "CX, DX" << endl;
   break;
}
else if(0xC8==byte){
   CX1-=AX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "CX, AX" << endl;
   break;
}
else if(0xD3==byte){
   DX1-=BX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "DX, BX" << endl;
   break;
}
else if(0xD1==byte){
   DX1-=CX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "DX, CX" << endl;
   break;
}
else if(0xD2==byte){
   DX1-=DX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "DX, DX" << endl;
   break;
}
else if(0xD0==byte){
   DX1-=AX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "DX, AX" << endl;
   break;
}
else if(0xD8==byte){
   BX1-=AX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "BX, AX" << endl;
   break;
}
else if(0xD9==byte){
	BX1-=CX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "BX, CX" << endl;
   break;
}
else if(0xDA==byte){
	BX1-=DX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "BX, DX" << endl;
   break;
}
else if(0xDB==byte){
	BX1-=BX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " SUB " << "BX, BX" << endl;
   break;
}
else { 
	cout << "Something went wrong" << endl;
}break;


//ADD instruction
case 0x03://16bit regs + 16bit regs
byte = memory[IP++];
if(0xD8==byte){//add AX to BX
   BX1+=AX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "BX, AX" << endl;
   break;
}
else if(0xD9==byte){//add CX to BX
	BX1+=CX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "BX, CX" << endl;
   break;
}
else if(0xDA==byte){// add DX to BX
	BX1+=DX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "BX, DX" << endl;
   break;
}
else if(0xDB==byte){// add BX to BX
	BX1+=BX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "BX, BX" << endl;
   break;
}
else if(0xC0==byte){
	AX1+=AX1;
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "AX, AX" << endl;
   break;
}
else if(0xC1==byte){
	AX1+=CX1;
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "AX, CX" << endl;
   break;
}
else if(0xC2==byte){
	AX1+=DX1;
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "AX, DX" << endl;
   break;
}
else if(0xC3==byte){
	AX1+=BX1;
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "AX, BX" << endl;
   break;
}
else if(0xCB==byte){
	CX1+=BX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "CX, BX" << endl;
   break;
}
else if(0xC9==byte){
	CX1+=CX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "CX, CX" << endl;
   break;
}
else if(0xCA==byte){
	CX1+=DX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "CX, DX" << endl;
   break;
}
else if(0xC8==byte){
   CX1+=AX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "CX, AX" << endl;
   break;
}
else if(0xD3==byte){
   DX1+=BX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "DX, BX" << endl;
   break;
}
else if(0xD1==byte){
   DX1+=CX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "DX, CX" << endl;
   break;
}
else if(0xD2==byte){
   DX1+=DX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "DX, DX" << endl;
   break;
}
else if(0xD0==byte){
   DX1+=AX1;
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD " << "DX, AX" << endl;
   break;
}
else { 
	cout << "Something went wrong" << endl;
}break;

case 0x83://add 16 bit regs to 8bit immd & sub 16 bit regs 
byte = memory[IP++];

if(0xC1==byte){// add cx case 8bits
  CX1+= memory[IP++];
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
  cout << IP << " ADD8bit "<< "CX" << endl;
  break;
}
else if(0xC3==byte){// add bx case 8bits
  BX1+= memory[IP++];
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
  cout << IP << " ADD8bit "<< "BX" << endl;
  break;
}
else if(0xC2==byte){// add dx case 8bits
  DX1+= memory[IP++];
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
  cout << IP << " ADD8bit "<< "DX" << endl;
  break;
}
else if(0xEB==byte){
	BX1-=memory[IP++];
	GEN.updateRegs16(AX1,CX1,DX1,BX1);
    cout << IP << " SUB8bit "<< "BX" << endl;
  break;
}
else if(0xEA==byte){
	DX1-=memory[IP++];
	GEN.updateRegs16(AX1,CX1,DX1,BX1);
    cout << IP << " SUB8bit "<< "DX" << endl;
  break;
}
else if(0xE9==byte){
	CX1-=memory[IP++];
	GEN.updateRegs16(AX1,CX1,DX1,BX1);
    cout << IP << " SUB8bit "<< "CX" << endl;
  break;
}
else { 
	cout << "Something went wrong" << endl;
}break;

//ADD instruction & sub
case 0x81://add & sub 16 bit regs to 16 bit immdts

byte=memory[IP++];

if(0xC1==byte){// add cx case 16bits
  CX1+= memory[IP++]+(memory[IP++]*256);
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
  cout << IP << " ADD "<< "CX" << endl;
  break;
}
else if(0xC3==byte){// add bx case 16bits
  BX1+= memory[IP++]+(memory[IP++]*256);
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
  cout << IP << " ADD "<< "BX" << endl;
  break;
}
else if(0xC2==byte){// add dx case 16bits
  DX1+= memory[IP++]+(memory[IP++]*256);
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
  cout << IP << " ADD "<< "DX" << endl;
  break;
}
else if(0xEB==byte){
  BX1-= memory[IP++]+(memory[IP++]*256);
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
  cout << IP << " SUB "<< "BX" << endl;
  break;
}
else if(0xEA==byte){ // add dx case 16bits
  DX1-= memory[IP++]+(memory[IP++]*256);
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
  cout << IP << " SUB "<< "DX" << endl;
  break;
}
  else if(0xE9==byte){ // add dx case 16bits
  CX1-= memory[IP++]+(memory[IP++]*256);
  GEN.updateRegs16(AX1,CX1,DX1,BX1);
  cout << IP << " SUB "<< "CX" << endl;
  break;
}
else { 
	cout << "Something went wrong" << endl;
}break;


 case 0x05://AX
   AX1+= memory[IP++]+(memory[IP++]*256);
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " ADD" <<" AX " << endl; 
   break;
 //MOV 16 bit registers
 case 0xBA://DX
   DX1 = memory[IP++] + (memory[IP++]*256);
   GEN.updateRegs16(AX1,CX1,DX1,BX1);
   cout << IP << " MOV" <<" DX " << endl; 
     break;
 case 0xBB://BX
    BX1 = memory[IP++] + (memory[IP++]*256);
    GEN.updateRegs16(AX1,CX1,DX1,BX1);
    cout << IP << " MOV" <<" BX " << endl; 
     break;
     
 case 0xB8://AX
	AX1 = memory[IP++] + (memory[IP++]*256);
	GEN.updateRegs16(AX1,CX1,DX1,BX1);
	cout << IP << " MOV" <<" AX " << endl; 
     break;

 case 0xB9://CX
     CX1= memory[IP++] + (memory[IP++]*256);
     GEN.updateRegs16(AX1,CX1,DX1,BX1);	
     cout << IP << " MOV" <<" CX " << endl; 
     break;
//8bit reg to 8bit immd
  case 0xB0:
  AL1= memory[IP++];
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AL " << endl;
  break;
  case 0xB3:
  BL1=memory[IP++];
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BL " << endl;
  break;
  case 0xB1:
  CL1=memory[IP++];
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CL " << endl;
  break;
  case 0xB2:
  DL1=memory[IP++];
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DL " << endl;
  break;
  case 0xB4:
  AH1=memory[IP++];
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AH " << endl;
  break;
  case 0xB7:
  BH1=memory[IP++];
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BH " << endl;
  break;
  case 0xB5:
  CH1=memory[IP++];
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CH " << endl;
  break;
  case 0xB6:
  DH1=memory[IP++];
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DH " << endl;
  break;
  //mov 8bit reg to 8bit reg
  case 0x8A:
  byte=memory[IP++];
  if(0xC3==byte){
  AL1=BL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AL,BL " << endl;
  break;
  }
  else if(0xC1==byte){
  AL1=CL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AL,CL " << endl;
  break;
  }
  else if(0xC2==byte){
  AL1=DL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AL,DL " << endl;
  break;
  }
  else if(0xC0==byte){
  AL1=AL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AL,AL " << endl;
  break;
  }
  else if(0xC4==byte){
  AL1=AH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AL,AH " << endl;
  break;
  }
  else if(0xC7==byte){
  AL1=BH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AL,BH " << endl;
  break;
  }
  else if(0xC6==byte){
  AL1=DH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AL,DH " << endl;
  break;
  }
  else if (0xC5==byte){
  AL1=CH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AL,CH " << endl;
  break;
  }
  else if(0xDB==byte){
  BL1=BL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BL,BL " << endl;
  break;
  }
  else if(0xD9==byte){
  BL1=CL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BL,CL " << endl;
  break;
}
  else if(0xDA==byte){
  BL1=DL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BL,DL " << endl;
  break;
  }
  else if(0xD8==byte){
  BL1=AL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BL,AL " << endl;
  break;
}
else if(0xDC==byte){
    BL1=AH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BL,AH " << endl;
  break;
}
else if(0xDF==byte){
    BL1=BH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BL,BH " << endl;
  break;
}
else if(0xDE==byte){
    BL1=DH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BL,DH " << endl;
  break;
}
else if(0xDD==byte){
  BL1=CH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BL,CH " << endl;
  break;
}
else if(0xD3==byte){
  DL1=BL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DL,BL " << endl;
  break;
}
else if(0xD1==byte){
  DL1=CL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DL,CL " << endl;
  break;
}
else if(0xD2==byte){
  DL1=DL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DL,DL " << endl;
  break;
}
else if(0xD0==byte){
  DL1=AL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DL,AL " << endl;
  break;
}
else if(0xD4==byte){
  DL1=AH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DL,AH " << endl;
  break;
}
else if(0xD7==byte){
  DL1=BH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DL,BH " << endl;
  break;
}
else if(0xD6==byte){
  DL1=DH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DL,DH " << endl;
  break;
}
else if(0xD5==byte){
  DL1=CH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DL,CH " << endl;
  break;
}
else if(0xCB==byte){
  CL1=BL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CL,BL " << endl;
  break;
}
else if(0xC9==byte){
  CL1=CL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CL,CL " << endl;
  break;
}
else if(0xCA==byte){
  CL1=DL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CL,DL " << endl;
  break;
}
else if(0xC8==byte){
  CL1=AL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CL,AL " << endl;
  break;
}
else if(0xCC==byte){
  CL1=AH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CL,AH " << endl;
  break;
}
else if(0xCF==byte){
  CL1=BH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CL,BH " << endl;
  break;
}
else if(0xCE==byte){
  CL1=DH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CL,DH " << endl;
  break;
}
else if(0xCD==byte){
  CL1=CH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CL,CH " << endl;
  break;
}
else if(0xE3==byte){
  AH1=BL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AH,BL " << endl;
  break;
}
else if(0xE1==byte){
  AH1=CL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AH,CL " << endl;
  break;
}
else if(0xE2==byte){
  AH1=DL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AH,DL " << endl;
  break;
}
else if(0xE0==byte){
  AH1=AL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AH,AL " << endl;
  break;
}
else if(0xE4==byte){
  AH1=AH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AH,AH " << endl;
  break;
}
else if(0xE7==byte){
  AH1=BH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AH,BH " << endl;
  break;
}
else if(0xE6==byte){
  AH1=DH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AH,DH " << endl;
  break;
}
else if(0xE5==byte){
  AH1=CH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " AH,CH " << endl;
  break;
}
else if(0xFB==byte){
  BH1=BL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BH,BL " << endl;
  break;
}
else if(0xF9==byte){
  BH1=CL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BH,CL " << endl;
  break;
}
else if(0xFA==byte){
  BH1=DL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BH,DL " << endl;
  break;
}
else if(0xF8==byte){
  BH1=AL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BH,AL " << endl;
  break;
}
else if(0xFC==byte){
  BH1=AH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BH,AH " << endl;
  break;
}
else if(0xFF==byte){
  BH1=BH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BH,BH " << endl;
  break;
}
else if(0xFE==byte){
  BH1=DH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BH,DH " << endl;
  break;
}
else if(0xFD==byte){
  BH1=CH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " BH,CH " << endl;
  break;
}
else if(0xEB==byte){
  CH1=BL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CH,BL " << endl;
  break;
}
else if(0xE9==byte){
  CH1=CL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CH,CL " << endl;
  break;
}
else if(0xEA==byte){
  CH1=DL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CH,DL " << endl;
  break;
}
else if(0xE8==byte){
  CH1=AL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CH,AL " << endl;
  break;
}
else if(0xEC==byte){
  CH1=AH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CH,AH " << endl;
  break;
}
else if(0xEF==byte){
  CH1=BH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CH,BH " << endl;
  break;
}
else if(0xEE==byte){
  CH1=DH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CH,DH " << endl;
  break;
}
else if(0xED==byte){
  CH1=CH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " CH,CH " << endl;
  break;
}
else if(0xF3==byte){
  DH1=BL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DH,BL " << endl;
  break;
}
else if(0xF1==byte){
  DH1=CL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DH,CL " << endl;
  break;
}
else if(0xF2==byte){
  DH1=DL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DH,DL " << endl;
  break;
}
else if(0xF0==byte){
  DH1=AL1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DH,AL " << endl;
  break;
}
else if(0xF4==byte){
  DH1=AH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DH,AH " << endl;
  break;
}
else if(0xF7==byte){
  DH1=BH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DH,BH " << endl;
  break;
}
else if(0xF6==byte){
  DH1=DH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DH,DH " << endl;
  break;
}
else if(0xF5==byte){
  DH1=CH1;
  GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
  cout << IP << " MOV"<< " DH,CH " << endl;
  break;
}
  else { 

    cout << "Something went wrong" << endl;
}break;

  

  

  case 0xCD:
  byte=memory[IP++];
  if(byte==0x20){
    cout<<"END" << endl;
    GEN.printregs();
    cout << "IP: "<< IP << endl;
    if(show==1){
    emulatordisplay(display,num);
}
    return 0;
    }
 else if(byte==0x21){
    if(AH1==6){
        show=1;
        AL1=DL1;
        display[num]=DL1;
        num++;
        cout << IP << " INT " << "21h" << endl;
        GEN.updateRegs8(AL1,CL1,DL1,BL1,AH1,CH1,DH1,BH1);
         break;
    }
      else{
        cout <<"Intrupt not supported" << endl;
      }             
     }break;
  }
 }
 
 
	return 0; 
}