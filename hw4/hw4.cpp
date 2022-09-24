#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
void init(bool **bits, int num_of_bits, int num_of_hash_func, int **arr, int **brr, int prime)
{
    /*
    1. Create an array with m bits for bits
    2. Create an array with r elements uniformly chosen from [1, p-1] for pointer a using srand(1) (hint: use rand())
    3. Create an array with r elements uniformly chosen from [1, p-1] for pointer b using srand(2) (note: a[i] and b[i] should be independent)
    */

    *bits=(bool*)malloc(sizeof(bool)*num_of_bits);
    *arr=(int*)malloc(sizeof(int)*num_of_hash_func);
    *brr=(int*)malloc(sizeof(int)*num_of_hash_func);
    srand(1);
    for(int i=0;i<num_of_hash_func;i++)
    {

        (*arr)[i] = (rand()%(prime-1))+1;

    }
    srand(2);
    for(int i=0;i<num_of_hash_func;i++)
    {
        (*brr)[i] =(rand()%(prime-1))+1;
    }

}
int myhash(char *str, int num_of_bits,int num_of_hash_func,int *arr, int *brr,int prime,int counter)
{
    /*
    1. Use hash in <string> to covert str to an integer key
    // You may use class string and class hash <string> 會用到p
    // note that 0 <= count <= r-1
    2. Return (a[count] * key + b[count]) % p  % m; count is 呼叫時從0~r-1
    */

    //hash<string> hasher;
    // unsigned long long key = hasher(str);//把字串轉為hash key
    unsigned long long key = hash<string>{}(str);
    return(arr[counter]*key+brr[counter])%prime %num_of_bits;

}
void ins(char *str, int num_of_bits, int num_of_hash_func, int *arr, int *brr, int prime,bool *bits)
{
    /*
    1. Find all the mapped bits in the following positions,bits[myhash(str, count, m, r, p, a, b)] for 0 ≤ count ≤ num_of_hash_func -1
    2. Set all of the mapped bits above to true
    */
    for(int counter=0;counter<num_of_hash_func;counter++)
    {
        bits[myhash(str,num_of_bits,num_of_hash_func,arr,brr,prime,counter)]=true;
    }
}
bool query( char *str,int num_of_bits,int num_of_hash_func, int *arr, int *brr, int prime, bool *bits )
{
    /*
    1. Examine whether all the mapped bits are true  所有都是true 才是true
    bits[myhash(str, count, m, r, p, a, b)] for 0 ≤ count ≤ num_of_hash_func
    */
    bool ans=true;
    for(int counter=0;counter<num_of_hash_func;counter++)
    {
        if(bits[myhash(str,num_of_bits,num_of_hash_func,arr,brr,prime,counter)]==false) ans=false;
    }
    return ans;
}
int main()
{
    int num_of_bits,num_of_hash_func,words,tests,prime;
    cin>>num_of_bits>>num_of_hash_func>>words>>tests>>prime;
    bool* bits;//bool陣列宣告
    int* arr;//int陣列宣告
    int* brr;
    init(&bits,num_of_bits,num_of_hash_func,&arr,&brr,prime);//傳入陣列地址
    for(int i=0;i<words;i++)
    {
        char str[100];
        cin>>str;
        ins(str,num_of_bits,num_of_hash_func,arr,brr,prime,bits);
    }
    for(int i=0;i<tests;i++)
    {
        char str[100];
        cin>>str;
        if(query(str,num_of_bits,num_of_hash_func,arr,brr,prime,bits)==true) cout<<str<<": true"<<endl;
        else cout<<str<<": false"<<endl;
    }
    free(arr);
    free(brr);
    free(bits);

}
/*
50 10 10 3 1019
data
structures
serve
as
the
basis
for
abstract
data
type
type
data
object
*/

