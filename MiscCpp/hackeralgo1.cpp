//Test1 
//598
//ezfnjymgqtjnmstbadgdsrxvntnacwljnkgchtjeaoivfcindgxipmrjuqmmcpntpotplodjhijxqpogjmzipygacfdjgmewechuebxvcbnakszzcxkozxwavzgmesrvysonomhvufezislfntgncspthcpneyminpbjildobozfirvcgdratdpmmpkujcywvtzkdytzyfejbytsobvudvutfueveevgrqnxjiwpkrvllsjxmqhotlnpgjxkjnobxfqodlyiqsisdeuwqmntxouzdtisgutdafostmwticvncjwldpknuodmfksusaqpsoosgpiveyxipfklmhypdxpdncpgaswpycoxsuxasqduojpblctcyvyxldcgzevedvxiwinfppkjbtifuuapickknwxxjmjmtxlpfalxdgepmekaxijuphqfafrnezyldokwcnzenhpibktlfuxjfmeqajmvopbhuslnnnlmkmoteceiwbytjhhxqnkuazevswrkaofggfrnapciuoexqogscugzspwuvzkyrdfkhixcaqctfwadewpqksxxvqiigvjjpagvqikuojlwhfyztu
//expected output 
//0
//Test2
//180
//czoczkotespkfjnkbgpfnmtgqhorrzdppcebyybhlcsplqcqogqaszjgorlsrppinhgpaweydclepyftywafupqsjrbkqakpygolyyfksvqetrfzrcmatlicxtcxulwgvlnslazpfpoqrgssfcrfvwbtxaagjfahcgxbjlltfpprpcjyivxu
//6
//
//Test 3
//187
//tlymrvjcylhqifsqtyyzfaugtibkkghfhyzxqbsizkjguqlqwwetyofqihtpkmpdlgthfybfhhmjerjdkybwppwrdapirukcshkpngayrdruanjtziknnwxmsjpnuswllymhkmztsrcwwzmlbcoakswwffveobbvzinkhnmvwqhpfednhsuzmffaebi
//0
#include <bits/stdc++.h>

using namespace std;

int create_alt_str(char a, char b, string s) 
{
    string s1(s);
    //deletable d(a,b);
    //remove_if(begin(s1),end(s1),d());
    s1.erase(std::remove_if(s1.begin(), 
                              s1.end(),
                              [a,b](unsigned char x){return (x!=a && x!=b);}),
               s1.end());
    bool bad=false;
    if(s1.length() > 1)
    {
        if(s1[0]!=s1[1])
        {
            for (int i = 0; i< s1.size() ; ++i) 
            {
                if(i%2==0 && s1[i]!=s1[0])
                {
                    bad = true;
                    break;
                }
                if(i%2==1 && s1[i]!=s1[1])
                {
                    bad = true;
                    break;
                }
            }
        }
        else
        {
            bad = true;
        }
    }
    if(bad)
        return 0;
    cerr << a << " " << b << " " << s1 << " " << s1.size() << endl; 
    return s1.size();
}

/*
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
*/
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
