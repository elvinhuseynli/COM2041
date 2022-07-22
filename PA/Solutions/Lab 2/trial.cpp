#include <iostream>

using namespace std;

void solve(){
	long long int n,a,b,d=0,e=0;
    
        cin>>n>>a>>b;
        d=n-1;
        while(d!=-1 && e!=n)
        {
            cout<<(a*d)+(b*e)<<" ";
            d--;
            e++;
        }
         cout<<endl;
}

int main(){
    
    long long int t;
    cin>>t;
    while(t--){
    	solve();
    }
    return 0;
}