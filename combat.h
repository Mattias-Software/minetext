#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

int fight(string mob, string pweapon,bool poison, bool fire, int mhp, int mdmg, int php, int pdmg, int parmor){
string ba="basic-attack";
srand ( time(NULL) );
char fact;
int sel=0;


if(mob=="Zombie")sel=1;
switch(sel){
case 1:
{
cout<<"a "<<mob<<" appeard"<<endl;
while(!(php<=0 || mhp<=0)){

if(pweapon=="bare-fists"){
cout<<"zombie attacks first"<<endl;

if(parmor!=0){
int randdmg= rand() % parmor +1;
mdmg=randdmg-mdmg;

if(mdmg<=0)mdmg=0;
if(mdmg>3)mdmg=3;
php=php-mdmg;

}
else{ 
php=php-mdmg;
php=abs(php);
if(php==-1)php=0;
}
cout<<"zombie use "<<ba<<" and deals "<<mdmg<<" points of damage"<<endl;
cout<<"[a] Attack\n[r] Retreat"<<endl;
cout<<"your hp: "<<php<<endl;
cout<<mob<<" hp: "<<mhp<<endl;
cin>>fact;
if(fact=='a')mhp=mhp-pdmg;
if(fact=='r')break;


}
else{
cout<<"you attack first"<<endl;
cout<<"[a] Attack\n[r] Retreat"<<endl;

cin>>fact;
if(fact=='a')mhp=mhp-pdmg;
if(fact=='r')break;


if(parmor!=0){
int randdmg= rand() % parmor +1;
mdmg=randdmg-mdmg;

if(mdmg<=0)mdmg=0;
if(mdmg>3)mdmg=3;
php=php-mdmg;
php=abs(php);
}
else {
php=php-mdmg;

if(php==-1)php=0;
}
cout<<"zombie use "<<ba<<" and deals "<<mdmg<<" points of damage"<<endl;
cout<<"your hp: "<<php<<endl;
cout<<"a "<<mob<<" appeard"<<endl;
}

}

break;
}


}
if(php<=0)exit(0);
return php;
}
