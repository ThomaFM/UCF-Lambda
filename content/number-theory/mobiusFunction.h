/**
 * Author: Thomas Meeks
 * License: CC0
 * Description: Computes mobius function, example code for counting coprime pairs
 */

//Mobius function
vector<int> mu(maxv); mu[1] = 1;
for(int i = 1; i < mu.size(); i++)
    for(int j = 2*i; j < mu.size(); j+=i)
        mu[j]-=mu[i];

//Count coprime pairs
ll ans = 0;
for(int d = 1; d<maxv; d++){
    ll sum = 0;
    for(int j = 0; j < maxv; j+=d) sum+=freq[j]; 
    ans+=(mu[d]*choose2(sum));
}
