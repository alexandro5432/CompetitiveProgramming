#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
#define FOR(i,a) for (int i=0;i<(a);++i)
#define FORD(i,a) for (int i=(a)-1;i>=0;i--)
#define FORT(i,a,b) for (int i=(a);i<=(b);++i)
#define FORTD(i,b,a) for (int i=(b);i>=(a);--i)
#define trav(i,v) for (auto i : v)
#define fr first
#define sc second
#define pir pair<int,int>
 
const int N=2e5+6;
const int MOD=30013;
 
bool dzn(char k){
    if (k=='a' || k=='o' || k=='i' || k=='u' || k=='e')return true;
    return false;
}
 
 
struct node{
    int sum,mx;
} dp[N],sg[4*N];
node operator +(const node &firstNode,const node &secondNode){
    node c;
    if (firstNode.mx>secondNode.mx)return firstNode;
    else if (secondNode.mx>firstNode.mx) return secondNode;
    c.sum=(firstNode.sum+secondNode.sum)%MOD;
    c.mx=max(firstNode.mx,secondNode.mx);
    return c;
}
 
void update(int v,int tl,int tr,int ind,node del){
    if (tl==tr){
        sg[v]=del;
        return;
    }
    int tm=(tl+tr)/2;
    if (ind<=tm){
        update(v+v,tl,tm,ind,del);
    }
    else{
        update(v+v+1,tm+1,tr,ind,del);
    }
    sg[v]=sg[v+v]+sg[v+v+1];
}
 
node get(int v,int tl,int tr,int l,int r){
    if (l>r) return {0,0};
    if (tl==l && tr==r){
        return sg[v];
    }
    int tm=(tl+tr)/2;
    return get(v+v,tl,tm,l,min(tm,r))+get(v+v+1,tm+1,tr,max(tm+1,l),r);
}
 
 
int a[N],b[N],c[N],d[N];
map <int,int> mp;
int ver[N];
vector<int> buck[N];
 
 
 
int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin>>n;
    set<int> s;
    vector<pair<pir,pir> > v;
    FOR(i,n){
        cin>>a[i]>>b[i]>>c[i]>>d[i];
        s.insert(c[i]);
        s.insert(d[i]);
    }
    int qan=0;
    trav (tv,s){
        mp[tv]=qan++;
    }
    FOR(i,n){
        c[i]=mp[c[i]];
        d[i]=mp[d[i]];
        v.push_back({{b[i],a[i]},{c[i],d[i]}});
    }
    sort(v.begin(),v.end());
    vector<int> bin;
    FOR(i,n){
        dp[i]={1,1};
        buck[lower_bound(bin.begin(),bin.end(),v[i].fr.sc)-bin.begin()-1].push_back(i);
        bin.push_back(v[i].fr.fr);
    }
    FOR(i,n){
        update(1,0,qan-1,v[i].sc.sc,dp[i]);
        trav(tv,buck[i]){
            node cur=get(1,0,qan-1,0,v[tv].sc.fr);
            dp[tv]=cur;
            dp[tv].mx++;
            if (dp[tv].mx==1)dp[tv].sum=1;
        }
    }
    node ans=get(1,0,qan-1,0,qan-1);
    cout<<ans.mx<<" "<<ans.sum<<endl;
    return 0;
}
