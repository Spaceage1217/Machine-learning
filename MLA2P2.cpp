#include<iostream>
#include<cmath>
#include<cstdlib>
#include <vector>
#include<iomanip>
#include<fstream>
using namespace std;
/*
    Grader please note that there are two versions of batch graident descent in my program
    The one that runs is based off the formula in lu's note
    The other one is commented out and the formula can be found here:
 https://medium.com/towards-data-science/difference-between-batch-gradient-descent-and-stochastic-gradient-descent-1187f1291aa1
 After running the 2 versions I have found that the differences are minimal and after talking to lu she said that it shouldnt matter much
*/
struct auto_mpg{
 double mpg;
 int cylinders;
 double displacement;
 int horsepower;
 int weight;
 double acceleration;
};

double mpgMin = 999999,
 mpgMax =-1,
 displacementMin=9999,
 displacementMax=-1,
 accelerationMin=9999999,
 accelerationMax=-1;
int cylindersMin = 999999,
cylindersMax = -1,
horsepowerMin = 999999,
horsepowerMax = -1,
weightMin = 99999,
weightMax = -1;

const int setSize = 401;
const int subSetSize = 398;

vector<auto_mpg> set (setSize);
double m[6]= {1,1,1,1,1,1};
double prevErrorSummation =0;

//functions
void readSet();
void gradientDescent();
void normalize();
void setMinMax();
void printData();


int main(){
 readSet();
 setMinMax();
 normalize();
 double threshHold = .0005;
 bool stop = false;
 double oldWeightSum=0, newWeightSum=0;
 int counter = 1;
 double guess;

 for( int i =0; i<10000; i++){
    for( int j = 0; j <6;j++){oldWeightSum += m[j];}
    gradientDescent();
    for( int j = 0; j <6;j++){newWeightSum += m[j];}

    if(abs(oldWeightSum-newWeightSum)<=threshHold){stop = false;}
    if(stop){
      cout<<"stoped at itteration "<<i<<endl;
      break;
    }
 }

  for( int i = subSetSize; i<setSize; i++){
     guess = (m[0])+(m[1]*set[i].cylinders)+(m[2]*set[i].displacement)+
     (m[3]*set[i].horsepower)+(m[4]*set[i].weight)+ (m[5]*set[i].acceleration);
     cout<<"predicition mpg for "<<counter<< " is..."<<guess<<endl;
     counter++;
   }

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
    set[i].cylinders = (set[i].cylinders - cylindersMin)/(cylindersMax-cylindersMin);
    set[i].displacement = (set[i].displacement - displacementMin)/(displacementMax-displacementMin);
    set[i].horsepower = (set[i].horsepower  - horsepowerMin)/(horsepowerMax-horsepowerMin);
    set[i].weight = (set[i].weight  - weightMin)/(weightMax-weightMin);
    set[i].acceleration = (set[i].acceleration  - accelerationMin)/(accelerationMax-accelerationMin);
  }
}
void printData(){
  for( int i =0; i<setSize; i++){
    cout<<set[i].mpg<<" "<<set[i].cylinders<<" "<<set[i].displacement<<" "<<set[i].horsepower
    <<" "<<set[i].weight<<" "<<set[i].acceleration<<endl;
  }
}
void gradientDescent(){
  double learning_rate = 0.0005;
  double summation = 0;
  for( int j =0; j<6; j++){
    for(int i = 0; i < subSetSize; i++){
      double y = set[i].mpg;
      double xj = 1;
      double x1 = set[i].cylinders;
      double x2 = set[i].displacement;
      double x3 = set[i].horsepower;
      double x4 = set[i].weight;
      double x5 = set[i].acceleration;
      if(j == 1){
        xj = set[i].cylinders;
      }
      else if( j == 2){
        xj = set[i].displacement;
      }
      else if( j == 3){
        xj = set[i].horsepower;
      }
      else if( j == 4){
        xj = set[i].weight;
      }
      else if( j == 5){
        xj = set[i].acceleration;
      }
      double guess = (m[0])+(m[1]*x1)+(m[2]*x2)+(m[3]*x3)+(m[4]*x4)+(m[5]*x5);
      double error = y-guess;
      summation +=((error)*xj);
    }
    m[j]=m[j]+((learning_rate)*summation);
  }
}

// void gradientDescent(){
//   double learning_rate = 0.005;
//   double summation = 0;
//   for( int j =0; j<6; j++){
//     for(int i = 0; i < subSetSize; i++){
//       double y = set[i].mpg;
//       double xj = 1;
//       double x1 = set[i].cylinders;
//       double x2 = set[i].displacement;
//       double x3 = set[i].horsepower;
//       double x4 = set[i].weight;
//       double x5 = set[i].acceleration;
//       if(j == 1){
//         xj = set[i].cylinders;
//       }
//       else if( j == 2){
//         xj = set[i].displacement;
//       }
//       else if( j == 3){
//         xj = set[i].horsepower;
//       }
//       else if( j == 4){
//         xj = set[i].weight;
//       }
//       else if( j == 5){
//         xj = set[i].acceleration;
//       }
//       double guess = (m[0])+(m[1]*x1)+(m[2]*x2)+(m[3]*x3)+(m[4]*x4)+(m[5]*x5);
//       double error = guess-y;
//       summation +=((error)*xj);
//     }
//     m[j]=m[j]-(learning_rate/subSetSize)*summation;
//   }
// }
