#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;

const int V=50;   

struct station_code
{
    string station_name;
    int code;
    string color;
};
struct station_code station[V];
float graph[V][V];

struct node1
    {
        vector <float>p;
    }P[V];

string capitalize(string str)
{
    for(int i=0;i<str.length();++i)
    {
        if(str[i]>96&&str[i]<123)
            str[i]=str[i]-32;
    }
    return str;
}


void window2();
void clrscreen();
void delay(unsigned int ms);

int timeconsumed(float distance);
int cost(float distance);
void Path(float distance,int e,int st,int inter);
int distance_min(float distance[], bool visited[]);
void dijkstra(float graph[V][V], int src,int targ);
void take_input();
void intro();

int main()
{
    
    int temp,n1,n2;
    float dis;
    ifstream fin;
    ifstream code;
    ifstream color;
    code.open("stationname.txt");
    color.open("colorcodes.txt");
    fin.open("distvalues.txt");
    for(int i=0;i<50;++i)
    {
       for(int j=0;j<50;++j)
        graph[i][j]=0;
    }
    for(int i=1;i<=V;++i)
    {
        fin>>temp;
        fin>>n1;
        for( int j=0;j<temp;++j)
        {
           fin>>n2;
           fin>>dis;
          
           graph[n1-1][n2-1]=dis;
        }
        
    }
    
        string line,col;
        for(int i=0;i<V;++i)
        {
            getline(color,col);
            station[i].color=col;
            getline(code, line);
            station[i].code=i;
            station[i].station_name=line;
        }

    intro();
}

void clrscreen()
{
    system("cls");
    
}

void delay(unsigned int msec)
{
    clock_t time = msec + clock();
    while( time > clock() );   
}   




int timeconsumed(float distance)
{
    float velocity=0.55;
    return ceil(distance/velocity);
}

int cost(float distance)
{
    if(distance<=2)
        return 10;
    else if(distance > 2 && distance <= 5)
        return 20;
    else if(distance > 5 && distance <= 12)
        return 30;
    else if(distance > 12 && distance <= 21)
        return 40;
    else if(distance > 21 && distance <= 32)
        return 50;
    else
        return 60;
}

void Path(float distance,int dest,int st)
{
    int t=dest,s;
    
   cout<<"THE SHORTEST PATH IS : ";

   
    vector <int> path;
    path.push_back(t);
    while(t!=st)
    {
        s=P[t].p.size();
        t=P[t].p[s-1];
        path.push_back(t);
    }
    vector <int>::iterator i=path.end();
    string str;
    string color;
    
    vector<int>::iterator i2=path.end();
    i2--;
    int n_of_stations=0;
    while(i!=path.begin())
    {
        i--;
        color=station[*i].color;
        


        if(i!=i2)
        {
        if(station[*(i2)].color!=station[*(i)].color)
        {
            
           
            cout<<"{change from "<<station[*i2].color<<" to "<<station[*i].color<<"}";
            
        }
        i2--;
        }
        str=station[*i].station_name;
        
            
            cout<<" ->> "<<str;
            
       

        n_of_stations++;
        delay(700);
    }

    
    delay(1000);
    
    cout<<endl<<"PATH LENGTH IS :";
    
    cout<<distance<<" KM"<<endl;
    delay(1000);
   
    cout<<"AVERAGE TIME : ";
    
    cout<<timeconsumed(distance)<<" MIN"<<endl;
    delay(1000);
   
    cout<<"AVERAGE FARE : ";
    
    cout<<" Rs. "<<cost(distance)<<endl;
    delay(1000);
    
    cout<<"NO OF STATIONS : ";
    
    cout<<n_of_stations-1<<endl;
    

    
   
    
  return;
}

int distance_min(float distance[], bool visited[])
{
   float min = INT_MAX;
   int min_index;

   for (int v = 0; v < V; v++)
     if (visited[v] == false && distance[v] <= min)
         min = distance[v], min_index = v;

   return min_index;
}

void dijkstra(float graph[V][V], int src,int targ)
{
     float distance[V];
     bool visited[V];
     for (int i = 0; i < V; i++)        
        distance[i] = INT_MAX, visited[i] = false;
     distance[src] = 0;
     for (int count = 0; count < V-1; count++)
     {
         int u = distance_min(distance, visited);
       visited[u] = true;
       for (int v = 0; v < V; v++)
         if (!visited[v] && graph[u][v] && distance[u] != INT_MAX
                                       && distance[u]+graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v];
                P[v].p.push_back(u);
            }
     }
     Path(distance[targ],targ,src);
}


void take_input()
{
        char ch;
        
        string startStation,endStation,line,col;
        int startcode,endcode;
       
        cout<<"ENTER THE STARTING POINT:";
       
    
        getline(cin,startStation);
       
        cout<<"ENTER THE DESTINATION POINT:";
        
        getline(cin,endStation);
        


        startStation=capitalize(startStation);
        endStation=capitalize(endStation);

        int flag_start=0,flag_end=0;

        for(int i=0;i<50;i++)
        {
            if(station[i].station_name==startStation)
            {
                startcode=station[i].code;
                flag_start=1;
            }
            if(station[i].station_name==endStation)
            {
                endcode=station[i].code;
                flag_end=1;
            }
        }
        int fault=0;
        if(flag_start==0)
        {
            
            cout<<"WRONG STARTING STATION NAME ENTERED"<<endl;
            fault=1;
        }
        if(flag_end==0)
        {
            
            cout<<"WRONG DESTINATION STATION NAME ENTERED"<<endl;
            fault=1;
        }
        scanf("%c",&ch);
      
        if(fault)
        {
          window2();
       
        }

        dijkstra(graph, startcode,endcode);
}



void window2()
{
    clrscreen();
    take_input();
}

void intro(){
    cout<<"WELCOME TO DELHI METRO"<<endl;
   
    cout<<"PRESS ENTER TO CONTINUE";
    char ch;
    scanf("%c",&ch);
    window2();
}

