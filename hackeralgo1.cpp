//Test1 
//598
//ezfnjymgqtjnmstbadgdsrxvntnacwljnkgchtjeaoivfcindgxipmrjuqmmcpntpotplodjhijxqpogjmzipygacfdjgmewechuebxvcbnakszzcxkozxwavzgmesrvysonomhvufezislfntgncspthcpneyminpbjildobozfirvcgdratdpmmpkujcywvtzkdytzyfejbytsobvudvutfueveevgrqnxjiwpkrvllsjxmqhotlnpgjxkjnobxfqodlyiqsisdeuwqmntxouzdtisgutdafostmwticvncjwldpknuodmfksusaqpsoosgpiveyxipfklmhypdxpdncpgaswpycoxsuxasqduojpblctcyvyxldcgzevedvxiwinfppkjbtifuuapickknwxxjmjmtxlpfalxdgepmekaxijuphqfafrnezyldokwcnzenhpibktlfuxjfmeqajmvopbhuslnnnlmkmoteceiwbytjhhxqnkuazevswrkaofggfrnapciuoexqogscugzspwuvzkyrdfkhixcaqctfwadewpqksxxvqiigvjjpagvqikuojlwhfyztu
//expected output 
//0

#include <bits/stdc++.h>

using namespace std;
int create_alt_str(char a, char b, string s) 
{
    vector<char> vs;
    for (auto x: s) 
    {
        if( x==a && vs.size() == 0)
        {
            vs.push_back(x);
        }
        else if(vs.size()>0) 
        {
               auto c = vs[vs.size()-1];
               if(c==a && x == b)
                   vs.push_back(x);
               else if(c==b && x == a)
                   vs.push_back(x);
        }
    }    
    string tmp(begin(vs),end(vs));
    cerr << a << " " << b << " " << tmp << " " << vs.size() << endl; 
    return vs.size();
}

int get_max_alt_str(char a, char b, string s) 
{
    auto m1 = create_alt_str(a,b,s);
    auto m2 = create_alt_str(b,a,s);
    return max(m1,m2);
}

int twoCharaters(string s) {
    // Complete this function
    auto s1(s);
    std::sort(std::begin(s1),std::end(s1));
    cerr << "sorted = " << s1 << endl;
    auto it = std::unique(std::begin(s1),std::end(s1));
    s1.resize(std::distance(std::begin(s1),it));
    cerr << "unique = " << s1 << endl;
    
    int len = s1.length();
    cerr << "Number of unique chars = " << len << endl;
    int max = 0;
    for (int i = 0 ; i < len ;++i )
    {
        for (int j = i+1; j < len ; ++j)
        {
          auto m = get_max_alt_str(s1[i],s1[j],s);        
          if(m>max) 
          {
              max = m;
          }
        }
    }
    return max;
}

int main() {
    int l;
    cin >> l;
    string s;
    cin >> s;
    int result = twoCharaters(s);
    cout << result << endl;
    return 0;
}
