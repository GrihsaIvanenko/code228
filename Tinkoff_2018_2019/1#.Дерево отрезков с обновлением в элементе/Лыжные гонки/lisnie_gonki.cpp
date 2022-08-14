#include <bits/stdc++.h>
using namespace std;
void merge (unsigned long long left,unsigned long long mid,unsigned long long right,vector <unsigned long long> & v ,unsigned long long & ch){

    vector <unsigned long long>  g;
    unsigned long long uk2=mid+1;

    for(unsigned long long i=left;i<=mid;i++){
        while(uk2<=right&&v[uk2]<v[i]){
               g.push_back(v[uk2]);

            uk2++;
            if(uk2-left>g.size()){
                ch+=uk2-g.size()-left;
            }

        }
         g.push_back(v[i]);

    }
     while(uk2<=right){
         g.push_back(v[uk2]);
            uk2++;
       if(uk2-left>g.size()){
                ch+=uk2-g.size()-left;
            }

     }

     for(unsigned long long i=left;i<=right;i++){

        v[i]=g[i-left];
     }
}
void mergesort (unsigned long long left,unsigned long long right,vector <unsigned long long> & v,unsigned long long & ch){
     if(right==left){
        return;
    }
    if(right - left == 1){
        if(v[right] < v[left]){
            swap(v[right],v[left]);
            ch++;
        }
         return;
         }
    unsigned long long mid=(left+right)/2;

    mergesort(left,mid,v,ch);
    mergesort(mid+1,right,v,ch);
    merge(left,mid,right,v,ch);
}

int main()
{
    unsigned long long n,m,z;
    unsigned long long  ch=0;
    cin>>n>>m;
    vector <unsigned long long> v(n);
    for(unsigned long long i=0; i<n; ++i)
    {
        cin>>z;
        v[i]=z*m+i;
    }
   mergesort(0,n-1,v,ch);
   cout<< ch;
    return 0;
}


