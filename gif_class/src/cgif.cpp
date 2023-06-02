#include "cgif.h"
#include "conv.h"
#include "CColor.h"

std::string conversionCod(int c){
std::string p;
int aux=c ,aux2=0;
int n=0;
while(aux>0){
    aux=(int)(aux/10);
    n++;
    }
    aux=c;
if(n==0){
    p="0";
    return p;
}

for(int i=n;i>0;i--){

    aux=c;
    aux=(int)(aux/pow(10,i-1))-aux2*10;
    aux2=aux2*10+aux;
    p+=(char)(aux+48);


}}
cgif::cgif(char *ImageName){
    int *p;
    this->name=ImageName;

    this->file.open(ImageName,std::ios::in | std::ios::binary);


    int a,b;
    file.seekg(6,std::ios::beg);
    char aux[7];
    for(int i=0; i<7; i++)
        file.read((char*)&aux[i],sizeof(aux[i]));

    if((int)aux[0]<0)
        a=256+(int)aux[0];
    else
        a=(int)aux[0];
    if((int)aux[1]<0)
        b=256+(int)aux[1];
    else
        b=(int)aux[1];

    this->Canva_width=a+b*256;


    if(((int)aux[2])<0)
        a=256+(int)aux[2];
    else
        a=(int)aux[2];
    if((int)aux[3]<0)
        b=256+(int)aux[3];
    else
        b=(int)aux[3];

    this->Canva_height=a+b*256;


    this->GlobalColorTab=false;

    this->GlobalColorTable_size=0;
    int pos=13;
    p=convBin(convHDec(aux[4]));
    if(p[0]==1)
    {
        this->GlobalColorTab=true;
        this->GlobalColorTable_size=pow(2,p[5]*4+p[6]*2+p[7]+1);
        pos+=GlobalColorTable_size*3;
    }
    delete[]p;


    file.seekg(pos ,ios::beg);
    for(int i=0;i<2;i++)
    file.read((char*)&aux[i] , sizeof(char));


    animation=false;
    if(convHDec(aux[0])==33&&convHDec(aux[1])==255){
        animation=true;
        file.seekg(pos+14,ios::beg);
        pos+=14;
        file.read((char*)&aux[2],sizeof(char));
        animation_tam=convHDec(aux[2]);
        pos+=2+animation_tam;
        }


//animation &&global





//Graphic control extension
    pos+=2;
    char* lect=new char;
    file.seekg(pos,std::ios::beg);
    file.read((char*)&lect[0],sizeof(char));

    this->GraphicControlExtension_block_size=convHDec(lect[0])+4;
     pos+=(GraphicControlExtension_block_size-2);
    delete []lect;

    //Image descriptor
    lect=new char [10];
    file.seekg(pos,std::ios::beg);
    for(int i=0; i<10; i++)
        file.read((char*)&lect[i],sizeof(char));
        pos+=10;


    this->Image_top=convHDec(lect[1])+convHDec(lect[2])*16;
    this->Image_left=convHDec(lect[3])+convHDec(lect[4])*16;
    this->Width=convHDec(lect[5])+convHDec(lect[6])*16;
    this->Height=convHDec(lect[7])+convHDec(lect[8])*16;
    p=convBin(convHDec(lect[9]));
    this->LocalColorTable_size=0;
    this->LocalColorTab=false;
    if(p[0]==1)
    {


        this->LocalColorTab=true;
         this->LocalColorTable_size=pow(2,p[5]*4+p[6]*2+p[7]+1);
    }



    delete[]p;
    delete []lect;

    dictionary_size=LocalColorTable_size+GlobalColorTable_size;



}
bool cgif::type(){
    file.seekg(0,std::ios::beg);
    char aux[3];
    for(int i=0; i<3; i++)
        file.read((char*)&aux[i],sizeof(aux[i]));

    if((int)aux[0]==71)
    {
        if((int)aux[1]==73)
            if((int)aux[2]==70)
                return true;


    }
    return false;
}
std::string cgif::version(){
    std::string ret="";
    file.seekg(3,std::ios::beg);
    char aux[3];
    for(int i=0; i<3; i++)
        file.read((char*)&aux[i],sizeof(aux[i]));
    for(int i=0; i<3; i++)
        ret+=aux[i];
    return ret;
}
void cgif::header(){
     std::cout<<"HEADER\n\t";
    std::string ret="";
    file.seekg(0,std::ios::beg);
    char aux[6];
    for(int i=0; i<6; i++)
        file.read((char*)&aux[i],sizeof(aux[i]));
    for(int i=0; i<6; i++)
    {
        ret=convHex(aux[i]);
        if(ret.size()==1)
            std::cout<<"0";
        std::cout<<convHex(aux[i])+" ";
    }
    std::cout<<"\n\n";
}
void cgif::logicalScreenDescriptor(){
     std::cout<<"LOGICAL SCREEN DESCRIPTOR\n\n\t";
    std::string ret="";
    int *p;
    char pf;
    file.seekg(6,std::ios::beg);
    char aux[7];
    for(int i=0; i<7; i++)
        file.read((char*)&aux[i],sizeof(aux[i]));

    for(int i=0; i<7; i++)
    {
        ret=convHex(aux[i]);
        if(ret.size()==1)
            std::cout<<"0";
        std::cout<<convHex(aux[i])+" ";
        if(i==4)
        {
            pf=aux[i];
            p=convBin(convHDec(aux[i]));

        }



    }
    std::cout<<"\n\n\t\tPacked field("<<convHex(pf)<<") ->";
    for(int i=0; i<8; i++)
        std::cout<<p[i];
    std::cout<<std::endl;

    std::cout<<"\t\tGlobal Color Table Flag:"<<p[0];
    std::cout<<"\n\t\tColor Resolution:"<<p[1]*4+p[2]*2+p[3];
    std::cout<<"\n\t\tSort Flag:"<<p[4];
    std::cout<<"\n\t\tSize of Global Color Table("<<p[5]*4+p[6]*2+p[7]<<"):"<<pow(2,p[5]*4+p[6]*2+p[7]+1)<<"\n\n";



    delete[]p;
}
int* cgif::devolverColor(int  pos){
    char cadena;
    int *p = new int[3];
    std::string c;
    for(int i=0; i<3; i++)
    {

        file.seekg(sizeof(char)*pos+i, std::ios::beg);
        file.read((char*)&cadena, sizeof(char));
        p[i]=convHDec(cadena);
    }

    return p;
}
void cgif::GlobalColorTabl(){
    if(GlobalColorTab)
    {   int pos=13;
        if(animation)
            pos+=29+animation_tam;

        std::ofstream salida("Gcolors.txt");
        std::ofstream desorden("GColoresRaw.dat", std::ios::binary);
        int* aux;
        for(int i=0; i<this->GlobalColorTable_size; i++)
        {
            aux=devolverColor(13+i*3);
            for(int j =0; j<3; j++)
            {
                salida<<aux[j]<<" ";
                desorden.write((char*)&aux[j],sizeof(aux[j]));
            }
            salida<<std::endl;
            delete[]aux;
        }

        desorden.close();
        salida.close();

    }

}
void cgif::GlobalColorTable(){
     std::cout<<"GLOBAL COLOR TABLE\n\n";
    if(GlobalColorTab)
    {
       this->GlobalColorTabl();

        std::cout<<"\tGLOBAL COLOR TABLE\n";
        std::cout<<"\tColor n:"<<GlobalColorTable_size<<"\n";
        std::cout<<"\tSaved in Gcolors.txt in RGB format \n\n";


    }
    else
        std::cout<<"Global Color Table not found..."<<std::endl;

}
void cgif::GraphicControlExtension(){
    int pos=13;
    if(animation)
            pos+=16+animation_tam;

    if(GlobalColorTab)
        pos+=GlobalColorTable_size*3;

    char *p=new char;
    int * bin;

    file.seekg(pos+2,std::ios::beg);
    file.read((char*)&p[0], sizeof(char));

    file.seekg(pos,std::ios::beg);
    int tam= convHDec(p[0])+4;
    delete p;
    std::cout<<"GRAPHIC CONTROL EXTENSION\n\n\t";
    p= new char[tam];

    for(int i=0; i<tam; i++)
    {

        file.read((char*)&p[i], sizeof(char));
        if(convHex((int)p[i]).size()==1)
        {
            std::cout<<"0";
        }
        std::cout<<convHex((int)p[i])<< " ";
    }
    std::cout<<std::endl;



    std::cout<<"\n\t";
    std::cout<<"Block size:"<<convHDec(p[2])<<"\n";
    std::cout<<"\tPacked field("<<convHDec(p[3])<<"):\n";
    bin= convBin(p[3]);
    std::cout<<"\t\tReserved for future use:"<<bin[0]*4+bin[1]*2+bin[2]<<"\n";
    std::cout<<"\t\tDisposal Method:"<<bin[3]*4+bin[4]*2+bin[5]<<"\n";
    std::cout<<"\t\tUser Input Flag:"<<bin[6]<<"\n";
    std::cout<<"\t\tTransparent Color Flag:"<<bin[7]<<std::endl;
    delete[]bin;
    std::cout<<"\tDelay time:"<<convHDec(p[5])+convHDec(p[4])*256<<"\n";
    std::cout<<"\tTransparent color index:"<<convHDec(p[7])<<"\n\n";
    delete[]p;




}
void cgif::ImageDescriptor(){
    char *p=new char;

    int pos=GraphicControlExtension_block_size+13;

    if(animation)
            pos+=16+animation_tam;
    if(GlobalColorTab)
    {
        pos+=GlobalColorTable_size*3;
    }

    delete []p;
    p= new char [10];
    file.seekg(pos,std::ios::beg);
    for(int i=0; i<10; i++)
        file.read((char*)&p[i],sizeof(char));

    std::cout<<"IMAGE DESCRIPTOR\n\n\t";

    for(int i=0; i<10; i++)
    {
        if(convHex((int)p[i]).size()==1)
            std::cout<<"0";

        std::cout<<convHex((int)p[i])<<" ";
    }

    std::cout<<"\n\n\tImage Top:"<<convHDec(p[1])+convHDec(p[2])*16<<"\n";
    std::cout<<"\tImage Left:"<<convHDec(p[3])+convHDec(p[4])*16<<"\n";
    std::cout<<"\tImage width:"<<convHDec(p[5])+convHDec(p[6])*16<<"\n";
    std::cout<<"\tImage height:"<<convHDec(p[7])+convHDec(p[8])*16<<"\n";
    std::cout<<"\tPacked field("<<convHDec(p[9])<<"):\n";

    int* med=convBin(convHDec(p[9]));
    int k=0;
    if(med[0]==1)
        k=1;

    std::cout<<"\tLocal Color Table Flag:"<<med[0]<<"\n";
    std::cout<<"\tInterface flag:"<<med[1]<<"\n";
    std::cout<<"\tSort flag:"<<med[2]<<"\n";
    std::cout<<"\tReserved for future use:"<<med[3]*2+med[4]<<"\n";
    std::cout<<"\tSize of local color table("<<med[5]*4+med[6]*2+med[7]<<"):"<<pow(2,med[5]*4+med[6]*2+med[7]+k)<<"\n"<<std::endl;

}
void cgif::LocalColorTabl(){
if(LocalColorTab){
 int pos=23+GraphicControlExtension_block_size;

    if(animation)
            pos+=16+animation_tam;
    if(GlobalColorTab)
    {
        pos+=GlobalColorTable_size*3+13;
    }

  std::ofstream salida("Lcolors.txt");
        std::ofstream desorden("LColoresRaw.dat", std::ios::binary);
        int* aux;
        for(int i=0; i<this->LocalColorTable_size; i++)
        {
            aux=devolverColor(pos+i*3);
            for(int j =0; j<3; j++)
            {
                salida<<aux[j]<<" ";
                desorden.write((char*)&aux[j],sizeof(aux[j]));
            }
            salida<<std::endl;
            delete[]aux;
        }

        desorden.close();
        salida.close();

}



}
void cgif::LocalColorTable(){
  std::cout<<"LOCAL COLOR TABLE\n\n";
if(LocalColorTab){
        this->LocalColorTabl();
        std::cout<<"\tColor n:"<<LocalColorTable_size<<"\n";
        std::cout<<"\tSaved in Lcolors.txt in RGB format \n\n";



}else{

std::cout<<"\tLocal Color Table not found...\n\n"<<std::endl;
}

}
void cgif::ImageData(){

std::ofstream CodigosT("Codigos.txt");

CodigosT.clear();


int pos=GraphicControlExtension_block_size+23;

if(GlobalColorTab)
    pos+=GlobalColorTable_size*3;
if(LocalColorTab)
    pos+=LocalColorTable_size*3;
if(animation)
    pos+=animation_tam+16;

char* p =new char [2];
char cod;
int *bin;
int tama;
file.seekg(pos ,std::ios::beg);

file.read((char*)&p[0] ,sizeof(char));
file.read((char*)&p[1] ,sizeof(char));
this->dictionary_size=pow(2,convHDec(p[0]))+2;
this->in_code_size=convHDec(p[0])+1;
this->codes_number=convHDec(p[1]);
tama=convHDec(p[0])+1;
delete[]p;


while(!file.eof()){
file.read((char*)&cod , sizeof(cod));
bin=convBin(convHDec(cod));
 for(int i=7;i>-1;i--){

        CodigosT<<bin[i];}
delete []bin;
}




CodigosT.close();




std::string dic[8192];
int codviejo , codnuevo ,  dictam;
std::string cadena ,caracter;
dictam=dictionary_size;

for(int i=0;i<8192;i++)
    dic[i]="";


for(int i=0;i<dictam;i++){
    dic[i]=conversionCod(i)+" ";

 }




std::ifstream Codigos("Codigos.txt");
std::ofstream CodigosTraducidos("Tcods.txt");
std::ofstream CodigosDat("Tcods.dat",std::ios::binary);

//REHACER{
char *precod= new char[tama];


for(int i=0;i<tama;i++){
Codigos>>precod[i];

}



codviejo=0;
codnuevo=0;
for(int i=0;i<tama;i++)
    codviejo+=pow(2,i)*(precod[i]-48);

CodigosTraducidos<<conversionCod(codviejo)<<" ";

for(int i=0;i<tama;i++){
Codigos>>precod[i];

}
codviejo=0 ;
int codviejo2;
codnuevo=0;
for(int i=0;i<tama;i++){
    codviejo+=pow(2,i)*(precod[i]-48);

}

CodigosTraducidos<<conversionCod(codviejo)<<" ";
CodigosDat.write((char*)&codviejo,sizeof(codviejo));
cadena=" ";


//como lo haces con los datos de Codigos puede llevar a fallo lo que es un pco sad , reever el video
while(!Codigos.eof()){
        codnuevo=0;

for(int i=0;i<tama;i++){
Codigos>>precod[i];
codnuevo+=pow(2,i)*(precod[i]-48);

}


    if(dictam==pow(2,tama)-1){
        tama++;
        delete []precod;
        precod= new char [tama];
    }
    if(dic[codnuevo]==""){
        cadena=dic[codviejo];
        cadena=cadena+cadena;
        dic[codnuevo]=cadena;
       // std::cout<<codviejo<<"!n:"<<codnuevo<<":"<<cadena<<std::endl;



    }else{

        //std::cout<<codnuevo<<"sos"<<std::endl;
        cadena=dic[codnuevo];


    }

    CodigosDat.write((char*)&codnuevo,sizeof(codnuevo));
    CodigosTraducidos<<conversionCod(codnuevo);
     caracter=cadena[0];
    dic[dictam]=dic[codviejo]+caracter+" ";
    dictam++;
    codviejo2=codviejo;
    codviejo=codnuevo;


}


dic[codviejo]=dic[codviejo2]+caracter+" ";
//falla por q el ultimo codigo tiene un error y no lo pone es el 413
//AQUI SE MUESTRA EL ERROR


for(int i=0;i<414;i++)
    std::cout<<i<<":"<<dic[i]<<endl;



delete[]precod;
int c;
CodigosTraducidos.close();
CodigosDat.close();

std::ifstream Cods("Tcods.dat",std::ios::binary);
std::ofstream CodF("FinalCods.txt");



while(!Cods.eof()){
    Cods.read((char*)&c,sizeof(c));

    CodF<<dic[c]<<" ";

}
Cods.close();
CodF.close();
std::cout<<"Final codes saved in FinalCods.txt"<<std::endl;
}
void cgif::interpretate(){
this->GlobalColorTabl();
this->LocalColorTabl();
this->ImageData();

std::ifstream codf("FinalCods.txt" ,std::ios::binary);
std::ofstream cod("FinalCods.dat" ,std::ios::binary);
char c;
int s;
std::string p;

std::string tama=conversionCod(this->dictionary_size-1);

//error en creacion de finalcods.txt
//faltan pixeles como 2000
codf.seekg(ios::beg);


while(!codf.eof()){
        codf.read((char*)&c,sizeof(char));
        if((int)c!=32){
            s=(int)c -48;

            if(s<0)
                s=255+s;



            cod.write((char*)&s,sizeof(s));


       if(p==tama)
        break;
        }
}






bool doble=false;
std::ifstream desorden;
std::ifstream g_aux;
if(LocalColorTab && !GlobalColorTab){
     desorden.open("LColoresRaw.dat", std::ios::binary);

}else
if(GlobalColorTab && !LocalColorTab)
    desorden.open("GColoresRaw.dat", std::ios::binary);
else
    {

     desorden.open("LColoresRaw.dat", std::ios::binary);
      g_aux.open("GColoresRaw.dat", std::ios::binary);
      doble=true;
    }





int l[3];
int aux[dictionary_size];
int k=0;
Color color;
while(k<dictionary_size){
    for(int j =0;j<3;j++)
        desorden.read((char*)&l[j],sizeof(int));


        aux[k]=classify_color(l[0],l[1],l[2]);


k++;}

if(doble){

while(!g_aux.eof()){
      for(int j =0;j<3;j++)
        g_aux.read((char*)&l[j],sizeof(int));

aux[k]=classify_color(l[0],l[1],l[2]);
        k++;}}






desorden.close();
codf.close();
cod.close();




ifstream codl("FinalCods.dat" ,ios::binary);
ofstream ensam("pintura.asm");
int codig;

ensam<<".MODEL SMALL"<<"\n\n";
ensam<<".DATA\n\n";
ensam<<"SPRITE DB "<<this->get_Canva_width()<<","<<this->get_Canva_height();
int cont=2;
bool salir=false;
while(!codl.eof()&&!salir){
    codl.read((char*)&codig , sizeof(codig));

    if(codig==(pow(2,in_code_size-1)+1)){


        salir=true;
        break;

    }

    else{
        if(cont==200){
        ensam<<"\nDB ";
        cont=1;
        ensam<<aux[codig];

        }else{

        ensam<<","<<aux[codig];
        cont++;
    }}}
    codl.close();
    ensam<<"\n.CODE"<<"\n\n";
    ensam<<"\tmov ax,seg sprite\n";
	ensam<<"\tmov ds,ax\n";
	ensam<<"\tJMP programa\n";
	ensam<<"dibujar_sprite proc \n";
	ensam<<"push ax\n";
    ensam<<"push bx\n";
    ensam<<"push cx\n";
     ensam<<"push dx\n";
    ensam<<"push si\n";
    ensam<<"push di\n";
    ensam<<"mov di,si\nadd di,2\nxor ax,ax\nmov al,ds:[si]\n";
    ensam<<"bucle1:\nxor bx,bx\nmov bl,ds:[si+1]\nbucle2:\npush cx\npush dx\npush ax\nadd cx,ax\nadd dx,bx\n";
    ensam<<"mov ah,0Ch\nmov al,ds:[di]\nint 10h\ninc di\npop ax\npop dx\npop cx\ndec bx\ncmp bx,0\n	jnz bucle2\ndec ax\ncmp ax,0\njnz bucle1\npop di\npop si\npop dx\n";
    ensam<<"pop cx\npop bx\npop ax\nret\ndibujar_sprite endp\nprograma:\nMOV AX,0A000h\n  MOV ES,AX  \nMOV AH,0\n MOV AL,13h  \n  INT 10h\nmov si,offset sprite\nmov cx,0\nmov dx,0\ncall dibujar_sprite\n\n\n";
    ensam<<"\nfin:\n  MOV AH,4Ch  \n  INT 21h\nEND";
    ensam.close();
    std::cout<<"Fichero 'pintura.asm' creado...";
}
void cgif::sh(){

std::cout<<"\nDATA\n"<<std::endl;
std::cout<<"\tImage:"<<get_name()<<std::endl;
std::cout<<"\tCanva width:"<<get_Canva_width()<<std::endl;
std::cout<<"\tCanva height:"<<get_Canva_height()<<std::endl;
std::cout<<"\tImage top:"<<get_Image_top()<<std::endl;
std::cout<<"\tImage Left:"<<get_Image_left()<<std::endl;
std::cout<<"\tHeight:"<<height()<<std::endl;
std::cout<<"\tWidth:"<<width()<<std::endl;
std::cout<<"\tGlobal color table size:"<<get_GlobalColorTable_size()<<std::endl;
std::cout<<"\tLocal color table size:"<<get_LocalColorTable_size()<<std::endl;
std::cout<<"\tDictionary size:"<<get_Dictionary_size()<<std::endl;
std::cout<<"\tInitial code size:"<<in_code_size<<std::endl<<std::endl;
header();
logicalScreenDescriptor();
GraphicControlExtension();
ImageDescriptor();
LocalColorTable();
GlobalColorTable();
}
cgif::~cgif(){
    file.close();
    delete []name;

}
