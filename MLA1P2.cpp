#include<iostream>
#include<cmath>
#include<cstdlib>
#include <ctime>
#include <vector>
#include<iomanip>
#include<fstream>
using namespace std;

const int setSize = 12;
//const int setSize = 6;
struct Point{
  double x;
  double y;
};

struct Cluster{
  int i;
  int m;
};

struct clusterContents{
  vector<Point> clusterPoints;
};

struct Point myPoints[setSize] = {
  { .x = 2, .y = 2},
  { .x = 3.01, .y = 2},
  { .x = 4.02, .y = 2},
  { .x = 5.03, .y = 2},
  { .x = 6.04, .y = 2},
  { .x = 7.05, .y = 2},
  { .x = 2, .y = 3.5},
  { .x = 3.01, .y = 3.5},
  { .x = 4.02, .y = 3.5},
  { .x = 5.03, .y = 3.5},
  { .x = 6.04, .y = 3.5},
  { .x = 7.05, .y = 3.5},
};

vector<Point> set (myPoints, myPoints + sizeof(myPoints) / sizeof(Point) );
clusterContents P[setSize];
vector<Cluster> history (10000);
int minIndex[2];
double cluster[setSize][setSize];
int active[setSize];


void argmax();
void printCM();
void printHistory();
void saveClusterPoints(int index0,int index1);
double sim(Point o, Point p);
double simLinkage(int i, int m, int j);
double simComplete(int i, int m, int j);
double simCentroid(int i, int m, int j);
void updateMatrix(int i, int m, int type);
int main(){
  int type;
  cout<<"Enter 1 for simpleLinkage"<<endl;
  cout<<"Enter 2 for completeLinkage"<<endl;
  cout<<"Enter 3 for centroidLinkage"<<endl;
  cin>>type;
  if(type>3 && type<1){
    cout<<"invalid option terminating program"<<endl;
    return -1;
  }

  for(int o = 0; o < setSize; o++)
  {
    P[o].clusterPoints.push_back(set[o]);
    for (int p = 0; p < setSize; p++)
    {
      cluster[o][p] = sim(set[o],set[p]);
    }
    active[o] = 1;
  }

  cout<<"Starting Set"<<endl;
  double distance=0.0;
  for(int k = 0; k < setSize-1;k++)
  {
      int i,m;
      argmax();

      i = minIndex[0];
      m = minIndex[1];
      history[k].i=i;
      history[k].m=m;

      printCM();
      distance += cluster[i][m];
      cout<<"\nMerges:"<<endl;
      cout<<"(P"<<history[k].m<<") merges with -> (P"<<history[k].i<<") at distance "<<distance<<endl;
      saveClusterPoints(m,i);
      //format better
    //   for(int b=0;b<setSize;b++){
    //   cout<<"points in cluster P"<<b<<endl;
    //   for(int v=0;v<P[b].clusterPoints.size();v++){
    //     cout<<P[b].clusterPoints[v].x<<","<<P[b].clusterPoints[v].y<<" ";
    //   }
    //   cout<<endl;
    // }
      cout<<endl;
      updateMatrix(i,m,type);
      active[m] = 0;
  }
   cout<<"\nFinal result:"<<endl;
   printCM();
   printHistory();


   return 0;
}

void argmax(){
  double min = 10000;
  for(int o = 0; o < setSize; o++)
  {
    for (int p = 0; p < setSize; p++)
    {
      if(active[o]==1 && active[p]==1)
      {
       if((min > cluster[o][p]))
       {
         if (cluster[o][p]>0){
          min = cluster[o][p];
          minIndex[0] = o;
          minIndex[1] = p;
        }
       }
     }
    }
  }
}

void updateMatrix(int i, int m, int type){
  double val;
  for(int j =0;j<setSize;j++){
    if(m!=j&&i!=j){
      if(type==1){
         val = simLinkage(i,m,j);
      }
      else if(type==2){
         val = simComplete(i,m,j);
      }
      else{
         val = simCentroid(i,m,j);
      }
      cluster[i][j] = val;
      cluster[j][i] = val;
    }
  }
}

double sim(Point o, Point p){
  double xDiff = o.x - p.x;
  double yDiff = o.y - p.y;
  double distance = sqrt(pow(xDiff,2) + pow(yDiff,2));
  return distance;
}

double simLinkage(int i, int m, int j){
  double min = cluster[i][j];
  if(min>cluster[m][j]){
     min = cluster[m][j];
  }
  return min;
}

double simComplete(int i, int m, int j){
  double min = cluster[i][j];
  if(min<cluster[m][j]){
     min = cluster[m][j];
  }
  return min;
}

void saveClusterPoints(int m,int i){
  //for saving cluster points for centroid
  for( int v = 0; v< P[m].clusterPoints.size();v++)
  {
    P[i].clusterPoints.push_back(P[m].clusterPoints.at(v));
  }




}
double simCentroid(int i, int m, int j){
  Point centroid1;
  Point centroid2;
  centroid1.x = 0;
  centroid1.y = 0;
  centroid2.x = 0;
  centroid2.y = 0;
  int centroid1_size = P[i].clusterPoints.size();
  int centroid2_size = P[j].clusterPoints.size();
  for( int v = 0; v < centroid1_size; v++)
  {
   centroid1.x+=P[i].clusterPoints[v].x;
   centroid1.y+=P[i].clusterPoints[v].y;
  }
  for( int v = 0; v < centroid2_size; v++)
  {
    centroid2.x+=P[j].clusterPoints[v].x;
    centroid2.y+=P[j].clusterPoints[v].y;
  }
  centroid1.x = centroid1.x/centroid1_size;
  centroid1.y = centroid1.y/centroid1_size;

  centroid2.x = centroid2.x/centroid2_size;
  centroid2.y = centroid2.y/centroid2_size;
  return sim(centroid1,centroid2);
}


void printCM(){
  for(int o = 0; o<setSize; o++){

    // if(o<10 && active[o]!=0){
    //   cout<<" P"<<o<<" ";
    // }
    // else if(active[o]!=0){
    //   cout<<"P"<<o<<" ";
    // }
    if(o<10 ){
      cout<<" P"<<o<<" ";
    }
    else{
      cout<<"P"<<o<<" ";
    }


    for(int p = 0; p<setSize; p++)
    {
      cout<<"|"<<fixed<<setprecision(2)<<cluster[o][p]<<" ";
      // if(cluster[o][p]!=0&&active[o]!=0){
      //   cout<<"|"<<fixed<<setprecision(2)<<cluster[o][p]<<" ";
      // }
      // else if(active[o]!=0){
      //   cout<<"|"<<fixed<<setprecision(2)<<cluster[o][p]<<" ";
      //   break;
      // }
    }
    cout<<endl;
  }
}

void printHistory(){
  cout<<"\nMerge History"<<endl;
  for(int k=0;k<setSize-1;k++){
    cout<<"(P"<<history[k].m<<") merges with -> (P"<<history[k].i<<")"<<endl;
  }
}

// 2 .2
// 3.01 2
// 4.02 2
// 5.03 2
// 6.04 2
// 7.05 2
// 2 3.5
// 3.01 3.5
// 4.02 3.5
// 5.03 3.5
// 6.04 3.5
// 7.05 3.5
//


// 2,.2
// 3.01,2
// 4.02,2
// 5.03,2
// 6.04,2
// 7.05,2
// 2,3.5
// 3.01,3.5
// 4.02,3.5
// 5.03,3.5
// 6.04,3.5
// 7.05,3.5

// .4 .53
// .22 .38
// .35 .32
// .26 .19
// .08 .41
// .45 .30
