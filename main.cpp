#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<fstream>
#include<chrono>
#include<algorithm>
using namespace std;
long maxim;
void bubble(long n, long v[])
{
    long i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (v[j] > v[j+1])
                {swap(v[j],v[j+1]);}

}

void counting(long v[], long n)
{long Max=v[0];
long x=0;
    for(long i=1;i<n;i++)
    {
        if(v[i]>Max)
            Max=v[i];
    }
    long *nr = new long[Max];
    for(long i=0;i<=Max;i++)
        nr[i]=0;
    for(long i=0;i<n;i++)
    {
        nr[v[i]]++;
    }
    for(long i=0;i<=Max;i++)
    {
        while(nr[i]>0)
        {
            v[x]=i;
            x++;
            nr[i]--;
        }
    }
    delete []nr;
}
void counting_radix(long v[], long n, long p)
{   long nr[10];
    long *sorted=new long[n];
    for(long i=0;i<10;i++)
        nr[i]=0;
    for(long i=0;i<n;i++)
        nr[(v[i]/p)%10]++;
    for(long i=0;i<9;i++)
        nr[i+1]+=nr[i];
    long I=n-1;
    while(I>=0)
    {
        sorted[nr[(v[I]/p)%10]-1]=v[I];
        nr[(v[I]/p)%10]--;
        I--;
    }
      for(long i=0;i<n;i++)
        v[i]=sorted[i];
}
void radix(long v[],long n)
{long ma=v[0];
    for(long i=0;i<n;i++)
        if(v[i]>ma)
            ma=v[i];
    for(long p=1;p<=ma;p*=10)
        counting_radix(v,n,p);

}
void mergesort(long v[],long st, long dr,long aux[])
{long I,J,mij,i,k;
    if (st<dr)
    {
        mij=(st+dr)/2;
        mergesort(v,st,mij,aux);
        mergesort(v,mij+1,dr,aux);
        I=st;
        J=mij+1;
        k=0;
        while(I<=mij && J<=dr)
        {
            if(v[I]<=v[J])
            {
                aux[k]=v[I];
                I++;
                k++;
            }
            else
            {
                aux[k]=v[J];
                J++;
                k++;
            }
        }
        while(I<=mij)
        {
            aux[k]=v[I];
            I++;
            k++;
        }
        while(J<=dr)
        {
            aux[k]=v[J];
            J++;
            k++;
        }
        for(i=st;i<=dr;i++)
            v[i]=aux[i-st];

}
}
void quicksort(long v[],long st,long dr)
{
    long d=0;
    long piv,i,j;
    piv=(st+dr)/2;
    swap(v[st],v[piv]);
    i=st;
    j=dr;
    while(i<j)
    {
        if(d==0)
        {
            if(v[i]>v[j])
            {
                swap(v[i],v[j]);
                i++;
                d=1;
            }
            else
                j--;
        }
        else
        {
            if(v[i]>v[j])
            {
                swap(v[i],v[j]);
                d=0;
                j--;
            }
            else
                i++;
        }
    }
    if(st<i-1)
        quicksort(v,st,i-1);
    if(i+1<dr)
        quicksort(v,i+1,dr);

}
void generare(long  n, long  v2[], long  maxim) {
    srand(time(0));
    for (long  i = 0; i < n; i++)
    {
        v2[i] =(rand() % maxim) + 1;

    }

}
void generare_constant(long n, long maxim, long v[]){
    srand(time(NULL));
    long x=1+rand()%maxim;
    for(long i=0;i<n;i++){
        v[i]=x;
    }
}
void duplicare(long v[],long n,long nou[])
{
    for(long i=0;i<n;i++){
        nou[i]=v[i];
}
}
bool verificare(long n, long V1[], long V2[]){
    for(long i=0;i<n;i++){
        if(V1[i]!=V2[i]){
            return 0;
        }
    }
    return 1;
}

int main()
{
    long test,i;
    long n;
    while(1)
    {
     cout<<"Pentru generarea unor numere random -> 1"<<'\n';
     cout<<"Pentru vector constant -> 2"<<'\n';
     cout<<"Pentru vector crescator -> 3"<<'\n';
     cout<<"Pentru vector descrescator -> 4"<<'\n';
     cout<<"Pentru vector aproape crescator -> 5"<<'\n';
     cin>>test;
     cout<<"Valoarea maxima?"<<'\n';
     cin>>maxim;
     cout<<"Cate numere?"<<'\n';
     cin>>n;
     if(n>10000000){
        cout<<"nu se poate executa programul";
     }
     else{
     long *v=new long[n];
     long *nou=new long[n];
     long *corect=new long[n];
     if(test==1)
        {generare(n,v,maxim);
        }
     else
        if(test==2)
            {generare_constant(n,maxim,v);
            }
    else
        if(test==3)
            {generare(n,v,maxim);
            sort(v,v+n);
            }
    else
        if(test==4)
            {generare_constant(n,maxim,v);
            }
    else
        if(test==5)
            {generare_constant(n,maxim,v);
            }

     else
        {
            cout<<"Esto no es una opcion"<<'\n';
            continue;
        }
    cout<<"SORTARE NATIVA"<<'\n';
    duplicare(v,n, nou);
        auto  start1 = std::chrono::steady_clock::now();
        sort(nou, nou+n);


        auto stop1= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff1 = stop1 - start1;
        cout<<diff1.count()<<" secunde"<<'\n';
        duplicare(nou, n, corect);
    duplicare(v,n,nou);
    cout<<"BUBBLE SORT"<<'\n';
    if(n>=100000){
        cout<<"Dureaza prea mult"<<'\n';
    }
    else{
    auto  start2 = std::chrono::steady_clock::now();
    bubble(n,nou);
        auto stop2= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff2 = stop2 - start2;
        cout<<diff2.count()<<" secunde"<<'\n';
        if(verificare(n,nou,corect)==1){
            cout<<"Corect"<<'\n';
        }
        else
        cout<<"Gresit"<<'\n';
    duplicare(v,n,nou);
    }
    cout<<"COUNTING SORT"<<'\n';


        auto  start3 = std::chrono::steady_clock::now();
    counting(nou,n);
        auto stop3= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff3 = stop3 - start3;
        cout<<diff3.count()<<" secunde"<<'\n';
        if(verificare(n,nou,corect)==1){
            cout<<"Corect"<<'\n';
        }
        else
        cout<<"Gresit"<<'\n';
         duplicare(v,n,nou);
    cout<<"RADIX SORT"<<'\n';
        auto  start4 = std::chrono::steady_clock::now();
    radix(nou,n);
        auto stop4= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff4 = stop4 - start4;
        cout<<diff4.count()<<" secunde"<<'\n';
        if(verificare(n,nou,corect)==1){
            cout<<"Corect"<<'\n';
        }
        else
        cout<<"Gresit"<<'\n';
     duplicare(v,n,nou);
    cout<<"MERGE SORT"<<'\n';
     long *aux=new long[n];
    auto  start5 = std::chrono::steady_clock::now();
    mergesort(nou,0,n-1,aux);
    auto stop5= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff5 = stop5 - start5;
        cout<<diff5.count()<<" secunde"<<'\n';

        if(verificare(n,nou,corect)==1){
            cout<<"Corect"<<'\n';
        }
        else
        cout<<"Gresit"<<'\n';
        duplicare(v,n,nou);

    cout<<"QUICK SORT"<<'\n';
    if(n>1000000 || (n>=100000 && (test == 2 || test == 4 || test == 5))){
        cout<<"Dureaza prea mult"<<'\n';
    }
    else{
        auto  start6 = std::chrono::steady_clock::now();
    quicksort(nou,0,n-1);
    auto stop6= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff6 = stop6 - start6;
        cout<<diff6.count()<<" secunde"<<'\n';
        if(verificare(n,nou,corect)==1){
            cout<<"Corect"<<'\n';
        }
        else
        cout<<"Gresit"<<'\n';
    }
    }
    }
}
