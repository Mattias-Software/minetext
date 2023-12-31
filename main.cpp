#include <iostream>
#include <string.h>
#include <iomanip> 
#include <time.h>
#include <fstream>
#include <cstring>  
//Linux headers//
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <sys/ioctl.h>
#include "combat.h"
//defines//
#define DATA_LEN 512
#define fname "mine-save.sav"
#define sname "game-config.cfg"
#define wsword "Wooden-sword"
#define objsnum 6
#define invnum 9
#define biomesnum 6
#define savfln 600
//leater armor//
#define lh "let_helmet"
#define lc "let_chestplate"
#define ll "let_leggings"
#define lb "let_boots"

using namespace std;
char bufflod[savfln];
fstream myfile;
bool debug=false;
bool expe=false;
//#pragma pack(4)
struct plys{
int hp;
int exp;
string inv[invnum]={"air","air","air","air","air","air","air","air","air"};
string arms[4]={"slot","slot","slot","slot"};
int armor;
int dmg;
string biome;
string sword;
bool poison=false;
bool fire=false;
}player;
struct mobs{
int mhp;
int mdmg;
int resis;
}creeper,zombie,husk;
string crftb[9]={"slot0","slot1","slot2","slot3","slot4","slot5","slot6","slot7","slot8"};
//insert into inventory//
void insinv(string item, int len){
for(int i=0; i<len; i++){
if(player.inv[i]=="air"){
player.inv[i]=item;
break;
}

}

}
//insert into armor slots//
void insarms(string item){
for(int i=0; i<4; i++){
if(player.arms[i]=="slot"){
player.arms[i]=item;
break;
}

}

} 
//clean the crafting table// 
void craftclean(){
crftb[0]="slot0";
crftb[1]="slot1";
crftb[2]="slot2";
crftb[3]="slot3";
crftb[4]="slot4";
crftb[5]="slot5";
crftb[6]="slot6";
crftb[7]="slot7";
crftb[8]="slot8";

}

//check items in the crafting table//
void crafting(){
for(int i=0; i<9; i++){
if(crftb[i]=="Log"){
insinv("Planks",invnum);
cout<<"crafted planks"<<endl;
craftclean();
}
}

if(crftb[7]=="Planks" && crftb[4]=="Planks"){
insinv("Stick",invnum);
cout<<"crafted stick"<<endl;
craftclean();
}

if(crftb[7]=="Stick" && crftb[4]=="Planks" && crftb[1]=="Planks"){
player.sword=wsword;
cout<<"crafted wooden sword"<<endl;
craftclean();
}

if(crftb[3]=="Leather" && crftb[0]=="Leather" && crftb[1]=="Leather" && crftb[2]=="Leather" && crftb[5]=="Leather"){
insarms(lh);
cout<<"crafted leather helmet"<<endl;
craftclean();
}

if(crftb[0]=="Leather" && crftb[3]=="Leather" && crftb[6]=="Leather" && crftb[7]=="Leather" && crftb[4]=="Leather" && crftb[8]=="Leather" && crftb[5]=="Leather" && crftb[2]=="Leather"){
insarms(lc);
cout<<"crafted leather chestplate"<<endl;
craftclean();
}
if(crftb[6]=="Leather" && crftb[3]=="Leather" && crftb[0]=="Leather" && crftb[1]=="Leather" && crftb[2]=="Leather" && crftb[5]=="Leather" && crftb[8]=="Leather"){
insarms(ll);
cout<<"crafted leather leggings"<<endl;
craftclean();
}
if(crftb[6]=="Leather" && crftb[3]=="Leather" && crftb[5]=="Leather" && crftb[8]=="Leather"){
insarms(lb);
cout<<"crafted leather boots"<<endl;
craftclean();
}

}




 
//new save system//
void savload(char type){
string buffer;
int numbuffer=0;
if(type=='s'){
myfile.open(fname, ios::out);
   for(int i=0; i<invnum; i++){
  buffer=player.inv[i];
  myfile <<buffer;
  myfile <<endl;
  //myfile <<"-";
  }
  
  //myfile <<"/";
  //myfile <<endl;
  for(int i=0; i<4; i++){
  buffer=player.arms[i];
  myfile <<buffer;
  myfile <<endl;

  }
  //myfile <<"//";
  //myfile <<endl;
  myfile <<player.sword;
  myfile <<endl;
   myfile <<player.hp;
  myfile <<endl;
   myfile <<player.exp;
  myfile <<endl;
  
  
  myfile.close();
  cout<<"file created"<<endl;
}
if(type=='l'){
ifstream myfile (fname);
//myfile.open (fname);

for(int i=0; i<invnum; i++){
	getline(myfile, buffer);
	cout<<buffer<<endl;
	//if(buffer=="-")i++;
	//if(buffer=="/"){
	//cout<<"Warning: data is not allined correctly, failed to load"<<endl;
	//_exit(0);
	//}
  player.inv[i]=buffer; 
  
  }
  
  for(int i=0; i<4; i++){
	getline(myfile, buffer);
	cout<<buffer<<endl;
	//if(buffer=="/")i++;
	//if(buffer=="//"){
	//cout<<"Warning: data is not allined correctly, failed to load"<<endl;
	//_exit(0);
	//}
  player.arms[i]=buffer; 
  
  }
  cout<<buffer<<endl;
  getline(myfile,buffer);
  cout<<buffer<<endl;
  player.sword=buffer;
  
  getline(myfile,buffer);
  numbuffer=stoi(buffer);
  cout<<numbuffer<<endl;
  player.hp=numbuffer;
  
  getline(myfile,buffer);
  numbuffer=stoi(buffer);
  cout<<numbuffer<<endl;
  player.exp=numbuffer;
  
  
	cout<<"file loaded"<<endl;
	 myfile.close();
 

}
}

//old save system//
//#pragma 
/*int savload(int type){
char* p=new char[player.inv[invnum].length()+1]; 
int fid= open(fpath, O_RDWR+O_CREAT,S_IRWXU);
    
    if (fid == -1) {
        printf("Error (-1): File does not exist\n");
        return -1;
    } else if (fid < -1){
        printf("Error (%d): %s\n", fid, strerror(fid));
        return -2;
    }
if(type==1){
 
   //char* p=c_str(player.inv); 
    
    write(fid, (char*)p[0], sizeof(player.inv));
    
    close(fid);


}
if(type==2){

read(fid, &bufflod,sizeof(bufflod));
int k;
do{
k=strlen((char*)bufflod[k]);
//copy(begin(bufflod),end(bufflod),begin(player.inv));
strcpy((char*)p,(char*)bufflod[k]);
}while(k<64);
 close(fid);
}


return 0;
}
*/
  

//game function//
void game(){
srand ( time(NULL) );
//player varibale//
player.hp=20;
player.exp=0;
player.dmg=1;
//mobs damages//
int dmgt=0;
//Creeper
creeper.mdmg=10;
//Zombie
zombie.mdmg=3;
zombie.mhp=20;

//Husk
husk.mdmg=3;
//variables//
int stptot;
int act;
int invsl;
int crfsl;
char y;
char action;
char actin;
char actcr;
//armor types and protection values//
//Leather
int lhlpr=1; //helmet
int lchpr=1; //chestplate
int llgpr=1; //leggings
int lbtpr=1; //boots
//Iron
int ihlpr=2; //helmet
int ichpr=6; //chestplate
int ilgpr=5; //leggings
int ibtpr=4; //boots
//mob stuff//


string objs[objsnum]={"Tree","Creeper","Cow","Water","Zombie","Lava"};
//string *pobjs =objs;
string biomes[biomesnum]={"Plains","Desert","Forest","Hills","Ice-Peeks","Dark-Forest"};
string buffinv[invnum];
string buffarmor[4]; 
string loadinv[invnum];

//cout<<"tutorial: to play type a number of steps\n every ten steps you may find something"<<endl;

while(true){
srand ( time(NULL) );
if(debug==true)cout << "\033[1;31mATTENTION\033[0m\ndebug menu enabled\ntype 5 to access it"<<endl;
cout<<"type:\n[1] Walk\n[2] Browse and manage the invetory\n[3] Crafting table\n[4] Save or load"<<endl;
//armor calculator//
//if(player.arms[0]=="air")player.armor=player.armor+0;
//if(player.arms[1]=="air")player.armor=player.armor+0;
//if(player.arms[2]=="air")player.armor=player.armor+0;
//if(player.arms[3]=="air")player.armor=player.armor+0;
//leather//

player.armor=0;
if(player.arms[0]==lh)player.armor=player.armor+lhlpr;
if(player.arms[1]==lc)player.armor=player.armor+lchpr;
if(player.arms[2]==ll)player.armor=player.armor+llgpr;
if(player.arms[3]==lb)player.armor=player.armor+lbtpr;


if(player.sword.empty())player.sword="bare-fists";
if(player.sword==wsword)player.dmg=4;
if(debug==true)cout<<player.sword<<endl;
cin>>act;
switch(act){
case 1:{
while(true){
//core gameplay loop//
int RandDis = rand() % 10;
int RandBiomes = rand() % biomesnum;
int RandDrop = rand() % 5;


if(player.biome.empty()){
RandBiomes = rand() % biomesnum;
player.biome=biomes[RandBiomes];
}
cout<<"type 'w' to walk and you may find something or if you want to display the action panel press 'i'"<<endl;
cout<<"current biome: "<<player.biome<<endl;
cout<<"your current weapon: "<<player.sword<<endl;
cin>>action;
if(action=='i')break;
if(action=='m')return;
if(player.hp<=0){
cout<<"you died!"<<endl;
return;
}
if(action=='w'){
int RandStp = rand() % 10;
RandStp = rand() % 10;
stptot=RandStp+10;
if(debug==true){
cout<<"steps: "<<RandStp<<endl; 
cout<<"steps to another biome (if is 20 or 19 you enter into a new biome): "<<stptot<<endl;
cout<<"RandDis: "<<RandDis<<endl;
}
if(stptot==19)stptot=stptot+1;
if(stptot==20){
RandBiomes = rand() % biomesnum;
player.biome=biomes[RandBiomes];
cout<<"congratulation you enter into a new biome: "<<player.biome<<endl;
}
if(RandStp==RandDis){
int RandIndex = rand() % objsnum;
//int RandIndexi = rand() % invnum;
RandIndex = rand() % objsnum;
cout << objs[RandIndex]<<endl;
if(objs[RandIndex]=="Tree"){
cout<<"you found a tree!"<<endl;
cout<<"do you want to harvest it and obtain a tree log?"<<endl;
cin>>y;
if(y=='y')insinv("Log",invnum);//player.inv[RandIndexi]="Log";

}
if(objs[RandIndex]=="Zombie"){
if(expe==true){
player.hp=fight("Zombie",player.sword, player.poison, player.fire, zombie.mhp, zombie.mdmg, player.hp, player.dmg, player.armor);
break;
}
if(player.sword=="bare-fists"){
player.hp=player.hp-zombie.mdmg;
cout<<"you punch the zombie in the face, but is not enough to stop it"<<endl;
cout<<"The zombie hit you"<<endl;
cout<<"now you have "<<player.hp<<" health points"<<endl;
}else cout<<"your mighty "<<player.sword<<" kill the zombie"<<endl;
}


if(objs[RandIndex]=="Creeper"){
//cout<<"you have ten seconds to type 'w' to escape the creeper explosion"<<endl;
//cout<<"due to a stupid bug the creeper is temporany disabled"<<endl;
if(player.sword=="bare-fists"){
player.hp=player.hp-creeper.mdmg;
cout<<"your fists are not enough powerfull to kill the creeper"<<endl;
cout<<"The creeper explode in front of you"<<endl;
cout<<"now you have "<<player.hp<<" health points"<<endl;
}else cout<<"you kill the creeper"<<endl;
}
if(objs[RandIndex]=="Cow"){
RandDrop;
cout<<"do you want to kill the cow to obtain one leather pice?\nand also you might obtain a raw beef piece?"<<endl;
cin>>y;
if(RandDrop==5){
cout<<"you obtain a raw beef piece"<<endl;
insinv("Raw-Beef",invnum);
}
if(y=='y')insinv("Leather",invnum);//player.inv[RandIndexi]="Leather";

}
if(player.biome!="Desert"){
if(objs[RandIndex]=="Water"){
cout<<"you found a water pond"<<endl;
}
}else cout<<"there is no water here"<<endl;  

}

}
}
break;
}

case 2:{
while(true){
//player invemtory//
cout<<"Player health points: "<<player.hp<<endl;
cout<<"PLayer damage points: "<<player.dmg<<endl;
cout<<"PLayer weapon: "<<player.sword<<endl;
cout<<"Player inventory "<<endl;
for (int i=0; i<invnum; i++) 
    cout <<i<<": "<< player.inv[i]<<endl;
cout<<"Player armor points: "<<player.armor<<endl;
cout<<"Player armor"<<endl;
for (int i=0; i<4; i++) 
cout << player.arms[i]<<"; ";
cout<<endl;
//cout<<player.arms[0]<<","<<player.arms[1]<<","<<player.arms[2]<<","<<player.arms[3]<<","<<player.arms[4]<<endl;
cout<<"inventory managment:\n'e' allows you to eat and regain health\ntype 'c' to exit"<<endl;
cin>>action;


if(action=='e'){
cin>>invsl;
if(player.inv[invsl]=="Raw-Beef"){
player.inv[invsl]="air";
if(player.hp<20){
player.hp=player.hp+5;
cout<<"you eat the "<<player.inv[invsl]<<"pice and you regebnrate 5 hp"<<endl;
}
if(player.hp==20)cout<<"no need to eat your health is full"<<endl;
}else cout<<"you can not eat "<< player.inv[invsl]<<endl;
}
if(action=='c')break;
}
break;
}
case 3:{

while(true){
cout<<"Player inventory:"<<endl;
for (int i=0; i<invnum; i++) cout <<i<<": "<< player.inv[i]<<"; ";
 cout<<endl;
cout<<"crafting table:"<<endl;

    cout <<setw(3)<<crftb[0]<<","<<setw(3)<<crftb[1]<<","<<setw(3)<<crftb[2]<<endl;
    cout <<setw(3)<<crftb[3]<<","<<setw(3)<<crftb[4]<<","<<setw(3)<<crftb[5]<<endl;
    cout <<setw(3)<<crftb[6]<<","<<setw(3)<<crftb[7]<<","<<setw(3)<<crftb[8]<<endl;

cout<<"to insert items into the crafting table\nyou need to type the 'i' followed by the inventory slot (remeber slot ranged from 0 to 8)\n followed by the crafting table (that also range from 0 to 8)\n if you want to retrive objects from the crafting table type 'r' followed by the inventory slot (remeber slot ranged from 0 to 8)\n followed by the crafting table (that also range from 0 to 8)"<<endl;
cin>>actin>>invsl>>crfsl;
if(actin=='i'){
crftb[crfsl]=player.inv[invsl];
player.inv[invsl]="air";
}

if(actin=='r'){
player.inv[invsl]=crftb[crfsl];
craftclean();
}

if(actin=='c')break;


cout<<"crafting table:"<<endl;
//for (int i = 9 - 1; i >= 0; i--) 
    cout <<setw(3)<<crftb[0]<<","<<setw(3)<<crftb[1]<<","<<setw(3)<<crftb[2]<<endl;
    cout <<setw(3)<<crftb[3]<<","<<setw(3)<<crftb[4]<<","<<setw(3)<<crftb[5]<<endl;
    cout <<setw(3)<<crftb[6]<<","<<setw(3)<<crftb[7]<<","<<setw(3)<<crftb[8]<<endl;


crafting();
//if((crftb[i]=="Planks")&&(crftb[i]=="Planks")&&(crftb[i]=="Planks")){
//insinv("Wooden-sword",invnum); //temporaney i want a shaped crafting for sword
//player.sword="Wooden-sword";
//}
}
craftclean();


break;

}
case 4:{
cout<<"type 's' to save or 'l' to load\n (ATTENTION this feature is under development)"<<endl;
cin>>action;
savload(action);
//if(action=='s'){
//savload(1);
//}

//if(action=='l')
//savload(2);
break;
}
case 5:{
ifstream testread(fname);
FILE * pFile;
string output;
int z;
int sizestr=sizeof(struct plys);
int sizeinv=sizeof(player.inv[invnum]);//player.inv[invnum].size();
int sizearmor=sizeof(player.arms[4]);//player.arms[4].size();
int sizsinv=player.inv[invnum].size();
int sizsarm=player.arms[4].size();
int leninv=player.inv[invnum].length();
int lenarm=player.arms[4].length();
int aligstr=alignof(struct plys);
int aliginv=alignof(player.inv[invnum]);
int aligarm=alignof(player.arms[4]);
int sizsword=player.sword.size();
int sizbiome=player.biome.size();
int sizhp=sizeof(player.hp);
for(int i=0;i>4;i++)buffarmor[i]="air";

if(debug==true){
cout<<"debug menu:\n[1]remove ten health points\n[2]size of the struct and arrays in it with their alignment\n[3]give you a bunch of stuff\n[4]clear your inventory\n[5]give lether armor \n[6]dump the save file into the console\n[7]trigger zombie fight"<<endl;
cin>>z;
if(z==3){
insinv("Planks",invnum);
insinv("Planks",invnum);
insinv("Planks",invnum);
insinv("Raw-Beef",invnum);
insinv("Log",invnum);
player.sword=wsword;
}
if(z==1)player.hp=player.hp-10;
if(z==2){
cout<<"size of player struct: "<<sizestr<<endl;
cout<<"size of player inventory: "<<sizeinv<<endl;
cout<<"size of player armor: "<<sizearmor<<endl;
cout<<"size (.size()) of inventory: "<<sizsinv<<endl;
cout<<"size (.length()) of inventory: "<<leninv<<endl;
cout<<"size (.size()) of armor: "<<sizsarm<<endl;
cout<<"size (.length()) of armor: "<<lenarm<<endl; 
cout<<"alignamanet of player struct: "<<aligstr<<endl; 
cout<<"alignamanet of inventory: "<<aliginv<<endl;
cout<<"alignment of armor: "<<aligarm<<endl;
//remainder//
//the alignment is a divisor of it size
}
if(z==4){
for(int i=0; i<invnum; i++)
player.inv[i]="air";
}
if(z==5){
insarms("let_helmet");
insarms("let_chestplate");
insarms("let_leggings");
insarms("let_boots");
}
if(z==6){
//print save file in the terminal//
string out;

while (getline (testread,out)) {
  
  cout << out;
}
testread.close();
}

if(z==7){
player.hp=fight("Zombie",player.sword, player.poison, player.fire, zombie.mhp, zombie.mdmg, player.hp, player.dmg, player.armor);
break;
}


}





break;
}
}
}	
}





int main(){
int sel;
char k;
string buffer;
cout<<"Welcome to Mattia's Software minetext"<<endl;
while(true){
cout<<"--Minetext--\n[1] Singleplayer\n[2] Credits\n[3] Comands list\n[4] Settings \n[5] Quit"<<endl;
cin>>sel;
switch(sel){
case 1: 
{
game();
break;
}
case 2:
{
cout<<"Author: Mattia's Software\n Based upon Minecraft"<<endl;
cout<<"Thanks to Loxo, that help me with some stuffs"<<endl;
break;
}
case 3:
{
cout<<"List of useful comands:\n'w': allows you to walk a random number of steps\n'm':allows you to return to the main menu\n'e':allows you to eat and regain health\n to use it you need to type 'e' and then the inventory slot were the food is contained\n'c': allows to quit from inventory managment and form crafting table"<<endl;


break;
}
case 4:
{
cout<<"Do you wish to:\n[g]Generate the settings file\n[l]Load the setting file\n[q]Quit to menu"<<endl;
cin>>k;

if(k=='g'){
myfile.open(sname, ios::out);
myfile <<"debug:0";
myfile <<endl;
myfile <<"experimental-features:0";
myfile <<endl;
cout<<"file created"<<endl;
myfile.close();

}

if(k=='l'){
ifstream myfile (sname);
getline(myfile, buffer);
cout<<buffer<<endl;
if(buffer=="debug:1")debug=true;
if(buffer=="debug:0")debug=false;
getline(myfile, buffer);
cout<<buffer<<endl;
if(buffer=="experimental-features:1")expe=true;
if(buffer=="experimental-features:0")expe=false;
}



break;
}

case 5:
{
exit(0);
}


}
}
}
