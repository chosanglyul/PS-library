#ifndef __STRING_KMP_H_
#define __STRING_KMP_H_

#include <vector>
#include <string>

class KMP {
    private:
    std::vector<int> pi;
    std::string s;
    
    public:
    KMP(std::string &s) {
        this->s = s;
        pi.resize(s.size(), 0);
        for(int i = 1, j = 0; i < (int)s.size(); i++) {
            while(j > 0 && s[i] != s[j]) j = pi[j-1];
            if(s[i] == s[j]) pi[i] = ++j;
        }
    }

    std::vector<int> match(std::string &t) {
        std::vector<int> ret;
        for(int i = 0, j = 0; i < (int)t.size(); i++) {
            while(j > 0 && s[j] != t[i]) j = pi[j-1];
            if(s[j] == t[i]) j++;
            if(j == (int)s.size()) {
                ret.push_back(i-(int)s.size()+1);
                j = pi[j-1];
            }
        }
        return ret;
    }
};

#endif
