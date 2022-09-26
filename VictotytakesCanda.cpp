#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=5e5+10;
const int inf=1e6+1;
int n,k,m,q,add,dis;
ll timer=1;
vector<ll>adj[sz];
ll col[sz];
int dp[sz],up[20][sz];
int st[sz],en[sz];
set<array<int,2>>col_num[sz];
int tree[sz<<2];
void update(int val,int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return;
    if(L<=l and r<=R){
        tree[p]+=val;
        return;
    }
    int mid=(l+r)>>1;
    update(val,L,R,l,mid,2*p);
    update(val,L,R,mid+1,r,2*p+1);
    tree[p]=tree[2*p]+tree[2*p+1];
}
int query(int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return 0;
    if(L<=l and r<=R) return tree[p];
    int mid=(l+r)>>1;
    return query(L,R,l,mid,2*p)+query(L,R,mid+1,r,2*p+1);
}
void dfs(int u){
    st[u]=timer++;
    for(int i=1;i<=19;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[up[0][v]=u]+1;
        dfs(v);
    }
    en[u]=timer-1;
}
int lca(int  a, int  b){
    if(dp[a]<dp[b]) swap(a,b);
    int d=dp[a]-dp[b];
    for(int i=0;i<=19;i++){
        if((d>>i)&1) a=up[i][a];
    }
    if(a==b) return a;
    for(int i=19;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) {a=tA; b=tB;}
    } 
    return up[0][a];
} 
void upd(int e,int add){
        auto it=col_num[col[e]].find({st[e],e});
        if(col_num[col[e]].size()!=1){
          if(it==col_num[col[e]].begin()){
                auto itr=++it; it--;
                array<int,2>rpos=(*itr);
                int anc=lca(rpos[1],e);
                update(add,st[anc],st[anc]);
          }
          else if(++it==col_num[col[e]].end()){
                 it--;
                 auto itl=--it; it++;
                 array<int,2>lpos=(*itl);
                 int anc=lca(lpos[1],e);
                 update(add,st[anc],st[anc]);
         }
         else if(it!=col_num[col[e]].begin() and it!=col_num[col[e]].end()){
                  auto itr=it; --it;
                  auto itl=--it;
                  array<int,2>lpos=(*itl);
                  array<int,2>rpos=(*itr);
                  int ancl=lca(e,lpos[1]);
                  int ancr=lca(e,rpos[1]);
                  int anclr=lca(lpos[1],rpos[1]);
                  update(-add,st[anclr],st[anclr]);
                  update(add,st[ancr],st[ancr]);
                  update(add,st[ancl],st[ancl]);
            }
      }
}  

int main(){
    scanf("%d%d%d",&n,&k,&q);
    for(int i=1;i<=n;i++){
          scanf("%d",col+i);
    }
    for(int i=1;i<n;i++){
        int u,v; scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    for(int i=1;i<=n;i++) col_num[col[i]].insert({st[i],i});
    for(int i=1;i<=k;i++){
         for(auto itr=col_num[i].begin();itr!=col_num[i].end();itr++){
             auto it=itr;
             array<int,2>up=*it; 
             update(1,st[up[1]],st[up[1]]);
             if(++it==col_num[i].end()) break;
             array<int,2>vp=*(it); 
             int u=up[1]; int v=vp[1];
             int anc=lca(u,v);
             update(-1,st[anc],st[anc]);
         }
    }
    for(int i=1;i<=q;i++){
        int t;scanf("%d",&t);
        if(t==1){
             int e,x;scanf("%d%d",&e,&x);
             upd(e,1);
             col_num[col[e]].erase({st[e],e});
             col[e]=x;
             col_num[col[e]].insert({st[e],e});
             upd(e,-1);   
        }
        else{
            int u; scanf("%d",&u);
            int ans=query(st[u],en[u]);
            printf("%lld\n",ans);
        }
    }
}
