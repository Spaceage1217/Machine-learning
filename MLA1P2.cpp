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
double sim(int i, int m, int j);
void updateMatrix(int i, int m);
int main(){
  for(int o = 0; o < setSize; o++)
  {
    P[o].clusterPoints.push_back(set[o]);
    cout<<P[o].clusterPoints[0].x<<","<<P[o].clusterPoints[0].y<<endl;
    for (int p = 0; p< setSize; p++)
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
      saveClusterPoints(history[k].m,history[k].i);
      cout<<endl;
      updateMatrix(i,m);
      active[m] = 0;
  }
   cout<<"\nFinal result:"<<endl;
   printCM();
   printHistory();
   for( int v =0; v<setSize;v++)
   {
    cout<< P[0].clusterPoints[v].x<<","<<P[0].clusterPoints[v].y<<"\n";
   }
   return 0;
}


void updateMatrix(int i, int m){
  for(int j =0;j<setSize;j++){
    if(m!=j&&i!=j){
      double val = sim(i,m,j);
      cluster[i][j]= val;
      cluster[j][i]= val;
    }
  }
}

void saveClusterPoints(int index0,int index1){
  //for saving cluster points for centroid
  int index[2];
  index[0]=index0;
  index[1]=index1;
  clusterContents c1 = P[index[1]];
  clusterContents c2 = P[index[0]];
  P[index[1]].clusterPoints.reserve(c1.clusterPoints.size()+c2.clusterPoints.size());
  P[index[1]].clusterPoints.insert(P[index[1]].clusterPoints.end(),c2.clusterPoints.begin(),c2.clusterPoints.end());
}

double sim(Point o, Point p){
  // cout<<"HEY IM POint"<<o.x<<","<<o.y<<" and "<<p.x<<","<<p.y<<endl;

  double xDiff = o.x - p.x;
  double yDiff = o.y - p.y;
  double distance = sqrt(pow(xDiff,2) + pow(yDiff,2));
  return distance;
}

double sim(int i, int m, int j){
  //cout<<"TEST TO SEE -->"<<m<<"combines with"<<i<<endl;
  cout<<"\ncurrently in p["<<m<<"]:"<<endl;
  for( int v =0; v<P[m].clusterPoints.size();v++)
  {
   cout<< P[m].clusterPoints[v].x<<","<<P[m].clusterPoints[v].y<<"\n";
  }
  cout<<"\ncurrently in p["<<i<<"]:"<<endl;
  for( int v =0; v<P[i].clusterPoints.size();v++)
  {
   cout<< P[i].clusterPoints[v].x<<","<<P[i].clusterPoints[v].y<<"\n";
  }

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

double simCentroid(int i, int m, int j){
  Point centroid1.x=0;
  centroid1.y=0;
  Point centroid2.x=0;
  centroid2.y=0;
  




  return min;
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

void printCM(){
  for(int o = 0; o<setSize; o++){

    if(o<10 && active[o]!=0){
      cout<<" P"<<o<<" ";
    }
    else if(active[o]!=0){
      cout<<"P"<<o<<" ";
    }

    for(int p = 0; p<setSize; p++)
    {
      //cout<<"|"<<fixed<<setprecision(2)<<cluster[o][p]<<" ";
      if(cluster[o][p]!=0&&active[o]!=0){
        cout<<"|"<<fixed<<setprecision(2)<<cluster[o][p]<<" ";
      }
      else if(active[o]!=0){
        cout<<"|"<<fixed<<setprecision(2)<<cluster[o][p]<<" ";
        break;
      }
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
