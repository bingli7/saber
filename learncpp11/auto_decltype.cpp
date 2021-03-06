#include <iostream>

using namespace std;

int d()
{
	cout<<"This function shouldn't be called."<<endl;
	return 17;
}

int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};
decltype(odd) *get_odd_or_even(int i)
{
	return (i % 2) ? &odd : &even;
}

int main()
{
	// simple auto
	double val1 = 1.1, val2 = 2.2;
	auto sum = val1 + val2;
	auto val3 = 0.3, *p = &val3;
	//auto val4 = 0, val5 = 0.0; // wrong. different types.
	//auto sum2; // wrong, auto type must be initialized.
	double val6 = 1.6, &rval6 = val6;
	auto aval6 = rval6;
	aval6 = 6.0; // aval6 is not a reference.

	cout<<"test simple auto:\n"<<val1<<'\t'<<val2<<'\t'<<sum<<'\t'<<val3<<'\t'<<p<<'\t'<<val6<<'\t'<<rval6<<'\t'<<aval6<<endl;

	// const and auto
	const int val7 = 1, &rval7 = val7;
	auto aval7 = val7; // remove top-level const
	aval7 = 7;
	auto aval8 = rval7; // remove top-level const
	aval8 = 8;
	auto aval9 = &val6; // not const
	*aval9 = 9;
	auto aval10 = &val7; // keep low-level const
	//*aval10 = 10; // wrong. const int can't be changed.
	const auto aval11 = val7; // top-level const auto
	//aval11 = 11; // wrong. const int can't be changed.
	auto &aval12 = val7; // keep top-level const
	//aval12 = 12; // wrong. const reference
	auto &aval13 = val6;
	aval13 = 13.0;
	//auto &aval14 = 42; // wrong. must be const auto
	const auto &aval15 = 15;
	//aval15 = 16; // wrong. const reference.
	//auto &aval16 = aval7, *aval17 = &val7; // wrong. type not consistent
	cout<<"test auto and const:\n"<<val7<<'\t'<<rval7<<'\t'<<aval7<<'\t'<<aval8<<'\t'<<*aval9<<'\t'<<aval10<<'\t'<<aval11<<'\t'<<aval12<<'\t'<<aval13<<'\t'<<aval15<<endl;

	// simple decltype
	decltype(d()) dval17 = 15.2;
	cout<<"test decltype:\n"<<dval17<<endl;

	// decltype and const
	decltype(val7) val18 = 0;
	decltype(rval7) val19 = val18;
	//val19 = 10; // wrong. val19 is a reference to const int.
	cout<<"test decltype and const:\n"<<val18<<'\t'<<val19<<endl;

	//double *pval20 = &val6;
	//decltype(*pval20) val21; // wrong. decltype(*pval20) = double&, must be initialized.
	decltype(rval6 + 0) val22 = 0;
	//decltype((val6)) val23; //wrong. decltype((val6)) == double&, must be initialized.
	decltype(val6) val24 = val6;
	cout<<"test decltype and reference:\n"<<val22<<'\t'<<val24<<endl;

	// using auto to short type
	string name = "Yubo";
	auto length = name.size();
	cout<<"test auto with complex type:\n"<<length<<endl;

	// using auto to simplify declare
	int val25[3][4] = {
		{0, 1, 2, 3},
		{4, 5, 6, 7},
		{8, 9, 10, 11}
	};
	cout<<"test auto to simplify type:\n";
	cout<<"old way:\n";
	for(int (*p)[4] = val25; p != val25 + 3; p++)
	{
		for(int *q = *p; q != *p + 4; q++)
		{
			cout<<*q<<'\t';
		}
		cout<<'\n';
	}
	cout<<"new way:\n";
	for(auto ap = val25; ap != val25 + 3; ap++)
	{
		for(auto aq = *ap; aq != *ap + 4; aq++)
		{
			cout<<*aq<<'\t';
		}
		cout<<'\n';
	}
	// decltype to simplify func return type
	auto val26 = get_odd_or_even(1);
	cout<<"test decltype to simplify func return type:\n";
	for(auto p = begin(*val26); p != end(*val26); p++)
	{
		cout<<p<<' '<<*p<<'\t';
	}
	cout<<endl;
	// auto to new object with a given obj
	auto val27 = new auto(val24);
	auto val28 = new auto(name);
	cout<<"test auto to new object with a given obj:\n";
	cout<<*val27<<'\t'<<*val28<<'\t'<<val28<<'\t'<<&name<<endl;
	auto val29 = new auto(odd); // right. can use auto to new a pointer to an array
	for(auto p = *val29; p != *val29 + 5; p++)
	{
		cout<<p<<' '<<*p<<'\t';
	}
	cout<<endl;

	//auto val30 = new auto[10](val24); // wrong. can't use auto to new an array
	int *val31 = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // this is right
	cout<<val31<<'\t'<<val31[0]<<"to"<<val31[9]<<endl;
}
