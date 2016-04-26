class MnjGraph{

    public:
    
    //vector<vector<int> , vector<int> > v;
    
    vector<pvi> v;
    
    void get_nebs(int id, vi &v_neb){
    
        //v_neb.clear();
        v_neb.reserve(v[id].first.size() + v[id].second.size() );
        v_neb.insert( end(v_neb), begin(v[id].first),  end(v[id].first) );
        v_neb.insert( end(v_neb), begin(v[id].second), end(v[id].second) );
    }
};

template <class  BidirectionalIterator >
bool  next_combination( BidirectionalIterator  first1 ,
                        BidirectionalIterator  last1 ,
                        BidirectionalIterator  first2 ,
                        BidirectionalIterator  last2)
{
    if (( first1  == last1) || (first2  == last2)) {
        return  false;
    }
    
    BidirectionalIterator  m1 = last1;
    BidirectionalIterator  m2 = last2; --m2;
    while (--m1 !=  first1  && !(*m1 < *m2)) {
    }

    bool  result = (m1 ==  first1) && !(* first1  < *m2);
    
    if (! result) {
        while (first2  != m2 && !(*m1 < *first2 )) {
        ++ first2;
    }
    
    first1 = m1;
    std:: iter_swap (first1 , first2 );
    
        ++ first1;
        ++ first2;
    }

if (( first1  != last1) && (first2  != last2)) {
    
    m1 = last1;   m2 = first2;
    while ((m1 !=  first1) && (m2 != last2)) {
        std:: iter_swap (--m1, m2);
        ++m2;
    }
    
        std:: reverse (first1 , m1);
        std:: reverse (first1 , last1);
        std:: reverse (m2, last2);
        std:: reverse (first2 , last2);
    }
    return !result;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////    
template <class  BidirectionalIterator >
bool  next_combination(BidirectionalIterator  first ,
BidirectionalIterator  middle ,
BidirectionalIterator  last)
{
    return  next_combination(first , middle , middle , last);
}
///////////////////////////////////////////////////////////////////////////////////////
