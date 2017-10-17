#include<iostream>
#include<cmath>
#include<cstdlib>
#include <vector>
#include<iomanip>
#include<fstream>
using namespace std;

struct auto_mpg{
 double mpg;
 int cylinders;
 double displacement;
 int horsepower;
 int weight;
 double acceleration;
};

double mpgMin = 99999999999999,
 mpgMax =-1,
 displacementMin=9999999999999,
 displacementMax=-1,
 accelerationMin=9999999999999,
 accelerationMax=-1;
int cylindersMin = 9999999999999,
cylindersMax = -1,
horsepowerMin = 999999999999999,
horsepowerMax = -1
weightMin = 999999999999,
weightMax = -1;

const int setSize = 401;
const int subSetSize = 398;

vector<auto_mpg> set (setSize);
double m[5]= {0,0,0,0,0};
double b = 1;

//functions
void readSet();
void gradientDescent();

int main(){
 readSet();
 gradientDescent();
 double guess;

   guess = (m[0]*set[398].cylinders)+(m[1]*set[398].displacement)+
   (m[2]*set[398].horsepower)+(m[3]*set[398].weight)+ (m[4]*set[398].acceleration)+b;
   cout<<"guess mpg for the first one is..."<<guess;
   cout<<m[0]<<endl;

  //cout<<set[400].mpg<<" "<<set[400].acceleration<<endl;

}

void readSet(){
  ifstream auto_mpg;
  auto_mpg.open("auto_mpg.txt");
  char Q;
  for(int i =0; i<setSize;i++){
    if(i<398){
    auto_mpg>>set[i].mpg>>set[i].cylinders>>set[i].displacement>>set[i].horsepower
    >>set[i].weight>>set[i].acceleration;
    }
    else{
      auto_mpg>>Q;
      if( Q =='?'){
        set[i].mpg = -1;
        auto_mpg>>set[i].cylinders>>set[i].displacement>>set[i].horsepower
        >>set[i].weight>>set[i].acceleration;
      }
    }

  }
}
void setMinMax(){
  for( int i =0; i<subSetSize;i++){
     if(mpgMin>set[i].mpg){
        mpgMin=set[i].mpg;
     }
     if(mpgMax<set[i].mpg){
        mpgMax=set[i].mpg;
     }
     if(cylindersMin>set[i].cylinders){
        cylindersMin=set[i].cylinders;
     }
     if(cylindersMax<set[i].cylinders){
        cylindersMax=set[i].cylinders;
     }
     if(displacementMin>set[i].displacement){
        displacementMin=set[i].displacement;
     }
     if(displacementMax<set[i].displacement){
        displacementMax=set[i].displacement;
     }
     if(horsepowerMin>set[i].horsepower){
        horsepowerMin=set[i].horsepower;
     }
     if(horsepowerMax<set[i].horsepower){
        horsepowerMax=set[i].horsepower;
     }
     if(weightMin>set[i].weight){
        weightMin=set[i].weight;
     }
     if(weightMax<set[i].weight){
        weightMax=set[i].weight;
     }
     if(accelerationMin>set[i].acceleration){
        accelerationMin=set[i].acceleration;
     }
     if(accelerationMax<set[i].acceleration){
        accelerationMax=set[i].acceleration;
     }
  }
}

void normalize(){
  for( int i = 0; i< setSize; i++ ){
    set[i].mpg = (set[i].mpg - mpgMin)/(mpgMin-mpgMax);
    set[i].cylinders = (set[i].cylinders - cylindersMin)/(cylindersMin-cylindersMax);
    set[i].displacement = (set[i].displacement - displacementMin)/(displacementMax-displacementMin);
    set[i].horsepower = (set[i].horsepower  - horsepowerMin)/(horsepowerMax-horsepowerMin);
    set[i].weight = (set[i].weight  - weightMin)/(weightMax-weightMin);
    set[i].accelaration = (set[i].accelaration  - accelarationMin)/(accelarationMax-accelarationMin);
  }
}
//
// void gradientDescent(){
//
//   double learning_rate = 0.05;
//
//   for( int j =0; j<6; j++){
//     for(int i = 0; i < setSize; i++)
//     {
//       double y = auto_mpg[i].mpg;
//       if(j == 0){
//         int xj = auto_mpg[i].cylinders;
//       }
//       else if( j == 1)
//       {
//           double xj = auto_mpg[i].displacement;
//       }
//       else if( j == 2)
//       {
//           int x2 = auto_mpg[i].horsepower;
//       }
//       else if( j == 3)
//       {
//           int x3 = auto_mpg[i].weight;
//       }
//       else if( j == 4)
//       {
//           double x4 = auto_mpg[i].acceleration;
//       }
//     }
//
//     m[j]=m[j]-learning_rate*(1/setSize)*val;
//   }
//
// }



void gradientDescent(){

  double learning_rate = 0.05;
  for(int i = 0; i < subSetSize; i++)
  {
    double y = set[i].mpg;
    int x0 = set[i].cylinders;
    double x1 = set[i].displacement;
    int x2 = set[i].horsepower;
    int x3 = set[i].weight;
    double x4 = set[i].acceleration;
    double guess = (m[0]*x0)+(m[1]*x1)+(m[2]*x2)+(m[3]*x3)+(m[4]*x4)+b;
    cout<<" guess in func is "<< guess<<endl;
    double error =  guess - y ;
    cout<<"error in func is "<< error<<endl;
    m[0] = (m[0] + error) * x0 * learning_rate;
    cout<<"now m[0] is "<< m[0]<<endl;
    m[1] = (m[1] + error) * x1 * learning_rate;
    m[2] = (m[2] + error) * x2 * learning_rate;
    m[3] = (m[3] + error) * x3 * learning_rate;
    m[4] = (m[4] + error) * x4 * learning_rate;
    b = b + (error) * learning_rate;
  }
}
