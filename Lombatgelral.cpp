#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
const ld inf=1e7+1;
string t,s;
int n,m;
bool use[sz];
vector<int>adj[sz];
int a[sz];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
vector<int>col_num;
ll mx_col,mx_c;
int lr[sz];
int trs[sz];
int col[sz];
ll ans[sz];
void dfs(int u=1,int p=0){
    trs[u]=1;
    for(auto v:adj[u]){
        if(v==p) continue;
        dfs(v,u);
        trs[u]+=trs[v];
    }
}
void add_edge(int u,int p,int add){
    col[a[u]]+=add;
    if(mx_col<col[a[u]]){
        mx_col=col[a[u]];
        mx_c=a[u];
    }
    else if(mx_col==col[a[u]]) mx_c+=a[u];
    for(auto v:adj[u]){
        if(v==p or lr[v]) continue;
        add_edge(v,u,add);
    }
}
void dfs_hld(int u,int p,bool keep){
    int mx=-1;
    int big=-1;
    for(auto v:adj[u]){
        if(v==p) continue;
        if(mx<trs[v]){
            mx=trs[v];
            big=v;
        }
    }
    for(auto v:adj[u]){
        if(v==p or v==big) continue;
        dfs_hld(v,u,0);
    }
    if(big!=-1){
        dfs_hld(big,u,1);
        lr[big]=1;
    }
    add_edge(u,p,1);
    if(big!=-1) lr[big]=0;
    ans[u]=mx_c;
    if(!keep){
        add_edge(u,p,-1);
        mx_c=mx_col=-1;
    }
}
int main(){   
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        auto it=find(col_num.begin(),col_num.end(),a[i]);
        if(it==col_num.end()) col_num.push_back(a[i]);
    }
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs();
    dfs_hld(1,0,1);
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
}
