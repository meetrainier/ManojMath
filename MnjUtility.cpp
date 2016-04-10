//Finds that test_it is included within range or not
//Requirement: the input type must be a pair
template<typename T1, typename T2>
bool within(const  T1 range,  const T2 &i    ) {

return  i >= range.first  &&  i < range.second; 

}



template<typename T>
bool within(const  T range,  const T &test_it    ) {
return within<T,decltype(test_it.first)>(range,test_it.first)  &&  within<T,decltype(test_it.first)>(range,test_it.second); 
}
