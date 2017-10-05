#include<iostream>
#include<cmath>
#include<cstdlib>
#include <ctime>
#include <vector>

using namespace std;
//data structure..
struct Point{
  double x;
  double y;
};
///functions...
Point argmin(int k,int i);
void clusterize(int K);
void generateRandomCenters(int K,int choice);
void init(int K);
void pickCenters(int K);
void printClusters(int K);
void printSet();
void run(int K);
void reCenter( bool change, int K);
double sim (Point set, Point center);

const int setSize = 8;
struct Point myPoints[setSize] = {
  { .x = 2, .y = 10},
  { .x = 2, .y = 5},
  { .x = 8, .y = 4},
  { .x = 5, .y = 8},
  { .x = 7, .y = 5},
  { .x = 6, .y = 4},
  { .x = 1, .y = 2},
  { .x = 4, .y = 9}
};
vector<Point> set (myPoints, myPoints + sizeof(myPoints) / sizeof(Point) );
vector<Point> newSet (setSize);
vector<Point> A(setSize);
vector<Point> centers (3);


int main(){
  int K = 0;
  int choice =0;
  printSet();
  cout<<"How many clusters do you want?"<<endl;
  cin>>K;
  cout<<"Press 1 to generate random centers from within the set"<<endl;
  cout<<"Press 2 to generate random centers with a max of either 10 or 15"<<endl;
  cout<<"Press 3 to pick from the set"<<endl;
  cin>>choice;
  if(choice==1)
  {
      init(K);
  }
  else if(choice == 2){
    int choice2;
    cout<<"Press 1 for a max of (10,10)"<<endl;
    cout<<"Press 2 for a max of (15,15)"<<endl;
    cin>>choice2;
    generateRandomCenters(K,choice2);
  }
  else if(choice == 3){
      pickCenters(K);
  }
  else{
    cout<<"invalid response..terminating";
    return -1;
  }

  cout<<"After first init:"<<endl;
  printClusters(K);
  run(K);
  cout<<"After final run:"<<endl;
  printClusters(K);
}

void generateRandomCenters(int K,int choice){
  //used to generate random centers from (0,0) to (10,10)
  //or (0,0) to (15,15)
  srand(time(NULL));
  Point random;
  int max;
  (choice ==1 )?max=10:max=15;
  cout<<"max = ("<<max<<","<<max<<")"<<endl;
  for ( int i = 0; i<K; i++ )
  {
      random.x = rand() % (max + 1);
      random.y = rand() % (max + 1);
      centers[i] = random;
      cout<<"( "<<centers[i].x <<","<< centers[i].y <<" )"<<endl;
  }
  clusterize(K);
}

void clusterize(int K){
  for ( int i = 0; i<setSize; i++)
  {
    A[i] = argmin(K,i);
  }
}

void printSet(){
  for(int i = 0; i < setSize; i++)
  {
    cout<<"A"<<i+1<<" = ("<< set[i].x <<","<< set[i].y <<")"<<endl;
  }
}

void pickCenters(int K){
  cout<<"Please select the initial centers"<<endl;
  cout<<"A1 = 1, A2 = 2....etc"<<endl;
  int centerIndex;
  for( int i =0; i <3; i++)
  {
    cin>>centerIndex;
    centers[i]=set[centerIndex-1];
  }
  cout<<"new centers are: "<<endl;
  for( int i =0; i <3; i++)
  {
    cout<<"( "<<centers[i].x <<","<< centers[i].y <<" )"<<endl;
  }
  clusterize(K);

}

void init(int K){
  srand(time(NULL));
  for(int i = 0; i < setSize; i++)
  {
    newSet[i] = set[i];
  }

  cout<<endl;
  cout<<"Our first set of centers are:"<<endl;

  for ( int i = 0; i<K; i++ )
  {
      int j = rand() % (setSize-i);
      centers[i] = newSet[j];
      newSet.erase(newSet.begin() + j);

      cout<<"( "<<centers[i].x <<","<< centers[i].y <<" )"<<endl;
  }

  cout<<endl;

  clusterize(K);
}

Point argmin(int K,int i){
  int closestCenter = 0;
  //int min = sim(set[i],centers[0]);
  double min = 10000;
   for( int j=0; j<K; j++)
   {
      if(min > sim(set[i],centers[j]))
      {
          min = sim(set[i],centers[j]);
          closestCenter = j;
      }
   }
   return centers[closestCenter];
}

double sim (Point set, Point center){
     double xDiff = set.x - center.x;
     double yDiff = set.y - center.y;
     double distance = sqrt(pow(xDiff,2) + pow(yDiff,2));
     return distance;
}

void run(int K){
 bool change = true;
 reCenter(change, K);
 Point closestCenter;
 while(change){
   change = false;
   for( int i =0; i<setSize; i++)
   {
     closestCenter = argmin(K,i);
     if ( (closestCenter.x != A[i].x)&&(closestCenter.y != A[i].y))
     {
       A[i] = closestCenter;
       change = true;
     }
   }
   reCenter(change, K);
 }
}

void reCenter( bool change, int K){
  if(change)
  {
    for( int i =0; i<K; i++)
    {
      double meanX = 0.0 , meanY =0.0;
      int count = 0;
      for (int j =0; j<setSize; j++){
        if ((A[j].x==centers[i].x)&&(A[j].y==centers[i].y)){
          meanX += set[j].x;
          meanY += set[j].y;
          count += 1;
        }
      }
      centers[i].x = meanX/count;
      centers[i].y = meanY/count;
    }
  }
}

void printClusters(int K){
  for( int i =0; i<K; i++)
  {
   cout<<"Cluster "<<i+1<<"{|";
    for (int j =0; j<setSize; j++){
      if ((A[j].x==centers[i].x)&&(A[j].y==centers[i].y)){
            cout<<"A"<<j<<"|";
      }
    }
    cout<<"}"<<endl;
  }
}
