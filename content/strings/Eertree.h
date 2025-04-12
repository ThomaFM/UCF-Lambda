/**
 * Author: Jacob Steinebronn/Thomas Meeks
 * Date: 2022-09-20
 * Description: Generates an eertree on str. $cur$ is accurate at the end of the main loop before the final assignment to $t$.
 * Time: $O(|S|)$
 * Status: Works but not stress-tested
 */

#pragma once

struct eertree{
    static constexpr int ALPHA = 26; 
    struct node{ //sInd is starting index of an occurrence
        array<int,ALPHA> down; 
        int slink, ln, sInd, freq = 0;
        node(int slink, int ln, int eInd = -1): 
            slink(slink), ln(ln), sInd(eInd-ln+1) {
                fill(begin(down),begin(down)+ALPHA,-1);
            }
    };
    vector<node> t = {node(0,-1),node(0,0)}; 
    eertree(string &s){
        int cur = 0, k = 0;
        for(int i = 0; i < sz(s); i++){
            char c = s[i]; int cID = c-'a'; //first chracter
            while(k<=0 || s[k-1] != c)
                k = i - t[cur = t[cur].slink].ln;
            #define TCD t[cur].down[cID] 
            if(TCD == -1){
                TCD = sz(t);
                t.emplace_back(-1,t[cur].ln+2,i);
                if(t.back().ln > 1){
                    do k = i - t[cur = t[cur].slink].ln;
                    while(k<=0 || s[k-1] != c);
                    t[sz(t)-1].slink = TCD;
                } else t[sz(t)-1].slink = 1;
                cur = sz(t)-1;
            } else cur = TCD;
            t[cur].freq++;
            k = i - t[cur].ln+1;
        }
        for(int i = sz(t)-1; i > 1; i--) //update frequencies 
            t[t[i].slink].freq += t[i].freq;
    }
};

