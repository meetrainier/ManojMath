

int read_vec (vector<int> &v) {
	int n=0; 
	cin >> n; 
	int tmp =0;
 
	for ( int i = 0; i < n ; i++){
		cin >> tmp; 
		v.push_back(tmp); 
	}

}



int write_vec (const vector<int> &v) {
//Writes the given vector like separated by a blank space
//1  2  3  
	for ( auto x: v){
		
		cout << x << " "; 
	}
return 0;
}

int write_size_vec (const vector<int> &v) {
//Writes the size of the given vector. The it chnages line. On teh Second line is each element
//separated by a blank space.
//3
//1  2  3
	 cout << v.size() << endl; 
	write_vec(v); 
return 0;
}




