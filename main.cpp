#include <iostream>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1e6;
const int maxm=5e6;
int n,m,cnt;
//链式前向星
struct edge{
    int to;
    int next;
}edges[maxm],edges_reverse[maxm];
stack<int> nodes;
vector<int> group[maxn];
int pos[maxn]={0};
int head[maxn],head_reverse[maxn];
int distribution[maxn]={0};//记录每个点的分组情况
void add_edge(int u,int v){
    edges[cnt].to =v;
    edges_reverse[cnt].to=u;
    edges[cnt].next=head[u];
    edges_reverse[cnt].next=head_reverse[v];
    head[u]=cnt;
    head_reverse[v]=cnt++;
}
void init(){
    for(int i=0;i<=n;++i) head[i]=head_reverse[i]=-1;
    cnt=0;
}
void dfs_reverse(int root){
    pos[root]=1;
    for(int i=head_reverse[root];i!=-1;i=edges_reverse[i].next){
        if(!pos[edges_reverse[i].to]){
            dfs_reverse(edges_reverse[i].to);
        }
    }
    nodes.push(root);
}
void dfs(int root,int g){
    group[g].push_back(root);
    distribution[root]=g;
    pos[root]=1;
    for(int i=head[root];i!=-1;i=edges[i].next){
        if(!pos[edges[i].to]){
            dfs(edges[i].to,g);
        }
    }
}

int main() {
     cin>>n>>m;
     init();
     int u,v;
     for(int _=0;_<m;++_){
         cin>>u>>v;
         add_edge(u,v);
     }
     //第一次反向dfs,逆后序遍历
     for(int i=1;i<=n;++i){
         if(!pos[i]) dfs_reverse(i);
     }
     //第二次正向dfs,求强连通分量
     for(int i=1;i<=n;++i) pos[i]=0;
     int group_num=0;
     while(!nodes.empty()){
         int temp=nodes.top();
         nodes.pop();
         if(!pos[temp]) dfs(temp,group_num++);
     }
//     for(int j=0;j<group_num;++j){
//         vector<int> ed=group[j];
//         for(int i : ed){
//             cout<<i<<' ';
//         }
//         cout<<endl;
//     }
     //算出出度
     int answer=0;
     for(int j=0;j<group_num;++j){
         vector<int> ed=group[j];
         for(int i:ed){
             bool flag=false;
             for(int id=head[i];id!=-1;id=edges[id].next){
                 if(distribution[edges[id].to]!=j){
                     answer+=ed.size();
                     flag=true;
                     break;
                 }
             }
             if(flag) break;
         }
     }
     cout<<answer;

}
