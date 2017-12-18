#ifndef UTILS_KKH_STD_VECTOR_H
#define UTILS_KKH_STD_VECTOR_H


// Copyright (C) 2017 Kyaw Kyaw Htike @ Ali Abdul Ghafur. All rights reserved.


// various utility functions/classes to support std::vector usage.

#include <iostream>
#include <vector>

// this class wraps (without copying) std::vector and allows slicing (either continuous
// range or indices), accessing elements, deleting multiple elements
// with indices, overloaded operators ==, >, etc. for finding and indexing, etc.

template <class T>
class stdvec_wrap
{
public:

	stdvec_wrap() = delete;
	
	stdvec_wrap(std::vector<T> &vecIn)
		: v(vecIn)
	{
		r1 = 0; r2 = vecIn.size()-1;
		cont_range = true;
	}

	stdvec_wrap(std::vector<T> &vecIn, int r1_, int r2_)
		: v(vecIn)
	{		
		r1 = r1_; r2 = r2_;
		if(r1==-1) r1 = vecIn.size()-1;
		if(r2==-1) r2 = vecIn.size()-1;
		cont_range = true;
	}

	stdvec_wrap(std::vector<T> &vecIn, std::vector<int>indices_)
		: v(vecIn)
	{
		indices = indices_; 
		cont_range = false;
	}	
	
	int size()
	{
		if (cont_range)
			return r2-r1+1;
		else
			return indices.size();
	}
	
	// individual element access (read)
	T operator[](int linear_index) const
	{
		if (cont_range)
			return v[linear_index+r1];
		else
			return v[indices[linear_index]];
	}
	
	// individual element access (write)
	T& operator[](int linear_index)
	{
		if (cont_range)
			return v[linear_index+r1];
		else
			return v[indices[linear_index]];
	}
	
	void operator=(const std::vector<T> &vecIn)
	{
		if (cont_range)
		{		
			std::copy(vecIn.begin(), vecIn.begin()+size(), v.begin()+r1);
		}

		else
		{
			for (size_t i = 0; i < indices.size(); i++)
				v[indices[i]] = vecIn[i];
		}
	}	
	
	void operator=(T val)
	{
		if (cont_range)
		{		
			std::fill(v.begin()+r1, v.begin()+r2+1, val);
		}

		else
		{
			for (size_t i = 0; i < indices.size(); i++)
				v[indices[i]] = val;
		}
	}	
	
	void operator=(stdvec_wrap<T> &vwIn)
	{
		if(vwIn.size() != size()) 
			throw std::runtime_error("Imcompatible sizes");
		
		for(size_t i=0; i<size(); i++)
			operator[](i) = vwIn[i];
	}	

	// find indices
	std::vector<int> operator==(std::vector<T> vecIn)
	{
		
		if(size() != vecIn.size()) 
			throw std::runtime_error("Imcompatible sizes");
		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] == vecIn[i])
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] = vecIn[i])
					res.push_back(i);				
			}
		}
		
		return res;
	}	
	
	// find indices
	std::vector<int> operator==(T val)
	{		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] == val)
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] == val)
					res.push_back(i);				
			}
		}
		
		return res;
	}	

	// find indices
	std::vector<int> operator>=(std::vector<T> vecIn)
	{
		
		if(size() != vecIn.size()) 
			throw std::runtime_error("Imcompatible sizes");
		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] >= vecIn[i])
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] >= vecIn[i])
					res.push_back(i);				
			}
		}
		
		return res;
	}	
	
	// find indices
	std::vector<int> operator>=(T val)
	{		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] >= val)
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] >= val)
					res.push_back(i);				
			}
		}
		
		return res;
	}	
	
	// find indices
	std::vector<int> operator>(std::vector<T> vecIn)
	{
		
		if(size() != vecIn.size()) 
			throw std::runtime_error("Imcompatible sizes");
		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] > vecIn[i])
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] > vecIn[i])
					res.push_back(i);				
			}
		}
		
		return res;
	}	
	
	// find indices
	std::vector<int> operator>(T val)
	{		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] > val)
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] > val)
					res.push_back(i);				
			}
		}
		
		return res;
	}	
	
	
	// find indices
	std::vector<int> operator<=(std::vector<T> vecIn)
	{
		
		if(size() != vecIn.size()) 
			throw std::runtime_error("Imcompatible sizes");
		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] <= vecIn[i])
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] <= vecIn[i])
					res.push_back(i);				
			}
		}
		
		return res;
	}	
	
	// find indices
	std::vector<int> operator<=(T val)
	{		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] <= val)
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] <= val)
					res.push_back(i);				
			}
		}
		
		return res;
	}	
	
	// find indices
	std::vector<int> operator<(std::vector<T> vecIn)
	{
		
		if(size() != vecIn.size()) 
			throw std::runtime_error("Imcompatible sizes");
		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] < vecIn[i])
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] < vecIn[i])
					res.push_back(i);				
			}
		}
		
		return res;
	}	
	
	// find indices
	std::vector<int> operator<(T val)
	{		
		std::vector<int> res;
		res.reserve(size());
		
		if(cont_range)
		{
			for(size_t i=0; i<size(); i++)
			{
				if(v[i+r1] < val)
					res.push_back(i);
			}
		}
		else
		{
			for(size_t i=0; i<indices.size(); i++)
			{
				if(v[indices[i]] < val)
					res.push_back(i);				
			}
		}
		
		return res;
	}	
	
	// printing with cout; e.g. cout << v << endl;
	template<typename T>
	friend std::ostream& operator<<(std::ostream &os, stdvec_wrap<T> &vw)
	{
		for (size_t i = 0; i < vw.size(); i++)
		{
			os << std::setprecision(4) << std::fixed << vw[i] << "\t";
			if ((i+1) % 10 == 0) os << endl;
		}
		os << endl;
			
		return os;
	}	


	
	std::vector<T> deep()
	{
		std::vector<T> vecOut(size());
		
		if (cont_range)
		{		
			std::copy(v.begin()+r1, v.begin()+r2+1, vecOut.begin());
		}

		else
		{
			for (size_t i = 0; i < indices.size(); i++)
				vecOut[i] = v[indices[i]];
		}
		
		return vecOut;
	}
	
	// this is O(1) with respect to the original referenced vector v 
	// (private data member).
	// Simply change the indices.
	// Use deep() to get the resulting std::vector
	void del(int idx)
	{
		if(cont_range)
		{
			indices.clear();
			indices.reserve(r2-r1+1);
			for(size_t i=r1; i<=r2; i++)
			{
				// if not idx to delete, will keep it
				if(i!=idx)
					indices.push_back(i);
			}
			cont_range = false;
		}	

		else
		{
			std::vector<int> indices_new;
			indices_new.reserve(indices.size());
			for(size_t i=0; i<indices.size(); i++)
			{
				// if not idx to delete, will keep it
				if(i!=idx)
					indices_new.push_back(indices[i]);				
			}			
			indices = indices_new;
		}		
		
	}	

	// this is O(1) with respect to the original referenced vector v 
	// (private data member).
	// Simply change the indices.
	// Use deep() to get the resulting std::vector
	void del(std::vector<int> idxs_del)
	{
		// sort idxs to remove in ascending order and remove any duplicates
		std::sort(idxs_del.begin(), idxs_del.end()); 
		idxs_del.erase( unique( idxs_del.begin(), idxs_del.end() ), idxs_del.end() );
			
		if(cont_range)	
		{
			indices.clear();
			indices.reserve(r2-r1+1);
			int cc = 0;
			for(size_t i=r1; i<=r2; i++)
			{ 
				// if not idx to delete, will keep it
				if(i!=idxs_del[cc])
					indices.push_back(i);
				else
					cc++;
			}
			cont_range = false;
		}	

		else
		{
			std::vector<int> indices_new;
			indices_new.reserve(indices.size());
			int cc = 0;
			for(size_t i=0; i<indices.size(); i++)
			{
				// if not idx to delete, will keep it
				if(i!=idxs_del[cc])
					indices_new.push_back(indices[i]);
				else
					cc++;
			}			
			indices = indices_new;
		}	
		
	}
	
	// sample with replacement
	void sample(int nsamples)
	{	
		std::default_random_engine eng((std::random_device())());
		std::uniform_int_distribution<int> idis(0, size()-1);
		
		std::vector<int> indices_new(nsamples);
		
		int idx_sampled;
		
		for(size_t i=0; i<nsamples; i++)
		{			
			idx_sampled = idis(eng);

			if(cont_range)
				indices_new[i] = r1+idx_sampled;
			else
				indices_new[i] = indices[idx_sampled];
		}
		
		cont_range = false;
		indices = indices_new;
	}
	
	void sample_no_replace(int nsamples)
	{
		if(nsamples > size())
			throw std::runtime_error("nsamples must be <= size().\n");		
	
		std::vector<int> temp(size());
		int n = 0;	
		temp[0] = 0; 
		std::generate(temp.begin()+1, temp.end(), [&n] { return n=n+1; });
		std::random_shuffle(temp.begin(), temp.end());	
			
		if(cont_range)
		{
			indices.resize(nsamples);
			for(size_t i=0; i<nsamples; i++)
				indices[i] = r1+temp[i];
			cont_range = false;
		}
		
		else
		{
			std::vector<int> indices_new(nsamples);
			for(size_t i=0; i<nsamples; i++)
				indices_new[i] = indices[temp[i]];
			indices = indices_new;
		}
				
	}
	
	void random_shuffle()
	{
		sample_no_replace(size());
	}

// private:
public:
	std::vector<T> &v; // will hold reference to the vector object
	bool cont_range;
	int r1, r2; // if cont_range==1, will use these values
	std::vector<int> indices; // if cont_range==0, will use these values
};


// printing with cout; e.g. cout << v << endl;
template<typename T>
std::ostream& operator<<(std::ostream &os, std::vector<T> &v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		os << std::setprecision(4) << std::fixed << v[i] << "\t";
		if ((i+1) % 10 == 0) os << endl;
	}
	os << endl;
		
	return os;
}	



// // get subvector from given range
// template<typename T>
// vector<T> stdvec_slice(const std::vector<T> &v, int r1, int r2) const
// {
	// int ndata = v.size();	
	// if (r1 == -1) r1 = ndata - 1; // -1 is a special notation for last element
	// if (r2 == -1) r2 = ndata - 1; // -1 is a special notation for last element

	// vector<T> vecOut(r2 - r1 + 1);
	// std::copy(v.begin()+r1, v.begin()+r2+1, vecOut.begin());
	
	// return vecOut;
// }	

// // get subvector from given indices
// template<typename T>
// vector<T> stdvec_slice(const std::vector<T> &v, const std::vector<int> &indices) const
// {	
	// vector<T> vecOut(indices.size());
	// for(size_t i=0; i<indices.size(); i++)
		// vecOut[i] = v[indices[i]];
	// return vecOut;
// }	



/*
Demo:

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	cout << stdvec_wrap<int>(v) << endl;
	
Output:

	1       2       3       4       5       6       7       8       9       10
	11      12      13

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	cout << stdvec_wrap<int>(v, 3, -1) << endl;
	
Output:	
	
	4       5       6       7       8       9       10      11      12      13

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	stdvec_wrap<int> a(v, 3, -1);
	cout << a << endl;
	
Output:

	4       5       6       7       8       9       10      11      12      13

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v, 3, -1);
	a[0] = 99;
	cout << v << endl;
	
Output:
	
	1       2       3       99      5       6       7       8       9       10

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	a[0] = 99;
	cout << v << endl;
	
Output:
	
	99      2       3       4       5       6       7       8       9       10

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int>(v, 3, -1)[0] = 999;
	cout << v << endl;
	
Output:
	1       2       3       999     5       6       7       8       9       10
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	std::vector<int> v2 = { 11,12,13,14,15,16,17 };
	stdvec_wrap<int> a(v, 3, -1);
	a = v2;
	cout << v << endl;
	
Output:

	1       2       3       11      12      13      14      15      16      17
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	std::vector<int> v2 = { 11,12,13,14,15,16,17 };
	stdvec_wrap<int>(v, 3, -1) = v2;
	cout << v << endl;
	
Output:

1       2       3       11      12      13      14      15      16      17

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	std::vector<int> v2 = stdvec_wrap<int>(v, 3, -1).deep();
	cout << v2 << endl;	

Output:

	4       5       6       7       8       9       10
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};	
	std::vector<int> v2 = stdvec_wrap<int>(v, {0, 3, 8}).deep();
	cout << v2 << endl;
	
Output:

	1       4       9
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	cout << stdvec_wrap<int>(v, { 0, 3, 8 }) << endl;
	
Output:

	1       4       9
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int>(v, { 0, 3, 8 }) = {99,100,101};
	cout << v << endl;
	
Output:

	99      2       3       100     5       6       7       8       101     10

Code: 

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int>(v, { 0, 3, 8 }) = std::vector<int>({ 99,100,101 });
	cout << v << endl;
	
Output:

	99      2       3       100     5       6       7       8       101     10
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int>(v, { 0, 3, 8 }) = stdvec_wrap<int>(v, { 5, 9, 2 });
	cout << v << endl;
	
Output:

	6       2       3       10      5       6       7       8       3       10	
	
Note: NO copying was ever made for the entire vectors. Just replace the elements
at its own positions.

Code:

	std::vector<int> v = { 3,2,3,4,5,6,7,8,9,3};
	stdvec_wrap<int> a(v);
	// find indices where "3" occurs
	cout << (a == 3) << endl;
	
Output:

	0       2       9
	
Code:

	// replace all values "3" in v with 100	
	std::vector<int> v = { 3,2,3,4,5,6,7,8,9,3};
	stdvec_wrap<int> a(v);
	stdvec_wrap<int>(v, a == 3) = 100;
	cout << v << endl;
	
Output:

	100     2       100     4       5       6       7       8       9       100

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	stdvec_wrap<int>(v, a == 3) = 100;
	cout << v << endl;
	
Output:

	1       2       100     4       5       6       7       8       9       10
	
Code: 

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	stdvec_wrap<int>(v, a <= 3) = 100;
	cout << v << endl;
	
Output:

	100     100     100     4       5       6       7       8       9       10
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	stdvec_wrap<int>(v, a > 8) = 45;
	cout << v << endl;
	
Output:
	1       2       3       4       5       6       7       8       45      45
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	// show vector of indices
	cout << (a > 8) << endl;
	
Output:

	8       9

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	std::vector<int> pp = a > 8;
	cout << pp << endl;
	
Output:

	8       9
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	stdvec_wrap<int>(v, a <= 4) = 45;
	cout << v << endl;
	
Output:

	45      45      45      45      5       6       7       8       9       10
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v, 2, -1);
	std::vector<int> v2 = a.deep();
	stdvec_wrap<int>(v2, a <= 4) = 45;
	cout << v2 << endl;
	
Output:

	45      45      5       6       7       8       9       10

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	// delete 3rd element
	a.del(2);
	// original v
	cout << v << endl;
	// the wrapper object
	cout << a << endl;
	// it shouldn't affect v as it's just O(1) operation
	cout << v << endl;
	// only when use deep, it will produce a new std::vector
	// with all the latest changes.
	v = a.deep();
	cout << v << endl;
	
Output:

1       2       3       4       5       6       7       8       9       10


1       2       4       5       6       7       8       9       10

1       2       3       4       5       6       7       8       9       10


1       2       4       5       6       7       8       9       10


Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	a.del({ 2,4,5 });
	std::vector<int> v2 = a.deep();
	cout << v2 << endl;	
	
Output:

1       2       4       7       8       9       10

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	cout << v << endl;
	a.del(2);
	cout << a.deep() << endl;
	a.del(4);
	cout << a.deep() << endl;
	a.del(5);
	cout << a.deep() << endl;
	
Output:

	1       2       3       4       5       6       7       8       9       10


	1       2       4       5       6       7       8       9       10

	1       2       4       5       7       8       9       10

	1       2       4       5       7       9       10
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10};
	stdvec_wrap<int> a(v);
	cout << v << endl;
	a.del({0,2,4});
	cout << a.deep() << endl;
	a.del(0);
	cout << a.deep() << endl;
	a.del({ 0,1 });
	cout << a.deep() << endl;
	a.del(0);
	cout << a.deep() << endl;
	
Output:

1       2       3       4       5       6       7       8       9       10


2       4       6       8       9       10

4       6       8       9       10

8       9       10

9       10

Code:

	// due to the use of reference instead of copying, it is possible
	// to "chain" operations without ever making a copy
	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	// wrap a slice
	stdvec_wrap<int> w(v, 4, -1);
	// find indices where number is less than 7
	cout << (w < 7) << endl;
	// wrap the whole vector
	stdvec_wrap<int> w2(v);
	// find indices where number is less than 7
	cout << (w2 < 7) << endl;
	
Output:

	0       1

	0       1       2       3       4       5
	
Code:

	stdvec_wrap<int> w(v);
	w.sample(4);
	cout << w.deep() << endl;
	
Output:

	5       10      1       7
	
Code:

	stdvec_wrap<int> w(v);
	w.sample(40);
	cout << w.deep() << endl;
	
Output:

	4       8       10      5       2       2       10      1       7       9
	10      8       9       7       7       2       9       7       8       5
	2       10      10      7       8       10      6       9       7       9
	10      1       7       9       7       8       2       5       10      7
	
Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };	
	stdvec_wrap<int> w(v);
	w.sample(10);
	cout << w.deep() << endl;

Output:

	4       5       4       1       4       9       2       5       10      3

Code:

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	stdvec_wrap<int> w(v);
	w.sample_no_replace(10);
	cout << w.deep() << endl;

Output:

	9       2       10      3       1       6       8       4       5       7
	

*/



#endif