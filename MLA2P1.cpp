#include<iostream>
#include<cmath>
#include<cstdlib>
#include <vector>
#include<iomanip>
#include<fstream>
using namespace std;

struct iris{
  string className;
  double sLength;
  double sWidth;
  double pLength;
  double pWidth;
};
//max and mins for normalizing data set.
double sLMin = 4.3;
double sLMax = 7.9;
double sWMin = 2.0;
double sWMax = 4.4;
double pLMin = 1.0;
double pLMax = 6.9;
double pWMin = 0.1;
double pWMax = 2.5;

const int setSize = 147;
const int testSize = 3;

vector<iris> set (setSize);//assuming the data set size we use is the same
iris test[testSize];
int active[setSize];

//functions
void normalize();
void normalizeTest();
void readSet();
void readTests();
double sim(iris a, iris b);
int argMin(iris a);
void reset();
string predicition(int K, int test);

int main(){
  int K3 = 3;
  int K5 = 5;
  int index = 0;
  readTests();
  readSet();
  normalize();
  normalizeTest();


  for( int i = 0; i<3;i++){
    for( int k = 0; k<5;k+=2){
      cout<<"For Test "<<i<<" with "<<k+1<<"-NN The predicition is "<<predicition(k+1,i)<<endl;
      reset();
    }
    cout<<endl;
  }
}

void reset(){
  for(int i =0; i<setSize; i++)
  {
    active[i]=1;
  }
}
string predicition(int K, int testNum){
  double A = 0, B = 0, C = 0, k = K;
  for( int i = 0; i<K;i++)
  {
      if(set[argMin(test[testNum])].className == "Iris-setosa"){
         A+=1;
      }
      else if(set[argMin(test[testNum])].className == "Iris-versicolor"){
         B+=1;
      }
      else{
        C+=1;
      }
  }
  A = A/K;
  B = B/K;
  C = C/K;
  if((A/K)>(B/K) && (A/K)>(C/K)){
    return "Iris-setosa";
  }
  else if((B/K)>(A/K) && (B/K)>(C/K)){
    return "Iris-Versicolour";
  }
  else{
    return "Iris-virginica";
  }
}

void readTests(){
  ifstream tests;
  tests.open("tests.txt");
  int i = 0;
  char cm;
  while(
    tests>>test[i].sLength>>cm>>test[i].sWidth>>cm>>test[i].pLength>>cm>>test[i].pWidth
    >>cm>>test[i].className
  ){ i++; }
}
void readSet(){
  ifstream iris;
  iris.open("iris.txt");
  int i = 0;
  char cm;
  while(
    iris>>set[i].sLength>>cm>>set[i].sWidth>>cm>>set[i].pLength>>cm>>set[i].pWidth
    >>cm>>set[i].className
  )
  {
    active[i]=1;
    i++;
  }
}
void normalize(){
  for( int i = 0; i< setSize; i++ ){
    set[i].sLength = (set[i].sLength - sLMin)/(sLMax-sLMin);
    set[i].sWidth = (set[i].sWidth - sWMin)/(sWMax-sWMin);
    set[i].pLength = (set[i].pLength - pLMin)/(pLMax-pLMin);
    set[i].pWidth = (set[i].pWidth  - pWMin)/(pWMax-pWMin);
  }
}
void normalizeTest(){
  for( int i = 0; i< testSize; i++ ){
    test[i].sLength = (test[i].sLength - sLMin)/(sLMax-sLMin);
    test[i].sWidth = (test[i].sWidth - sWMin)/(sWMax-sWMin);
    test[i].pLength = (test[i].pLength - pLMin)/(pLMax-pLMin);
    test[i].pWidth = (test[i].pWidth  - pWMin)/(pWMax-pWMin);
  }
}

double sim(iris a, iris b){
  double sLDiff = a.sLength - b.sLength;
  double sWDiff = a.sWidth - b.sWidth;
  double pLDiff = a.pLength - b.pLength;
  double pWDiff = a.pWidth - b.pWidth;
  double distance = sqrt(pow(sLDiff,2) + pow(sWDiff,2) + pow(pLDiff,2) + pow(pWDiff,2));
  return distance;
}

int argMin(iris a){
 double min = 9999999999999;
 int minIndex = 0;
  for( int i =0; i< setSize; i++){
    if(active[i]!=0){
      if((min > sim(a,set[i]))){
        min = sim(a,set[i]);
        minIndex = i;
      }
    }
  }
  active[minIndex]=0;//deactivate the index of min once its found
  return minIndex;
}
