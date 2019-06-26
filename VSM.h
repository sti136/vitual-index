#pragma once
#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
struct goal {
	int day;
	int goal;
	int count;
};
struct stock {
	string number;
	string name;
	float  percent;
	float c_price;
	float p_price;
	double* history;
	float change;
	stock() {
		number = " ";
		name = " ";
		p_price = 0;
		c_price = 0;
		percent = 0;
		change = 0;
	}
};
struct index {
	int n = 33;
	float index;
	float p_change;
	double p_index;
	double* history;
	int longest_string;
};
void welcome(goal &a) {//tested
	cout << "How many day you want to play?" << endl;
	cin >> a.day;
	cout << "What is your goal?" << endl;
	cin >> a.goal;
	cout << "Let's start the game! Enjoy and have fun!" << endl;
}


float generate_change() {
	int random0 = rand() % 200;
	int i = 0;
	int random = 0;
	float change = 0;
	
	while (i < random0) {
		random = rand() % 10;
		i++;
	}

	switch (random)
	{
	case(0):
		change = -0.0167;
		break;

	case(1):
		change = -0.00201;
		break;

	case(2):
		change = -0.00187;
		break;

	case(3):
		change = -0.00045;
		break;

	case(4):
		change = -0.00017;
		break;

	case(5):
		change = 0.0004;
		break;

	case(6):
		change = 0.0017;
		break;
	case(7):
		change = 0.0023;
		break;
	case(8):
		change = 0.0044;
		break;
	case(9):
		change = 0.0058;
		break;
	case(10):
		change = 0.0065;
		break;
	
	}
	
	return change;
}
void generate_stock(stock *&stock, int n,goal a) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		stock[i].change = generate_change();
		stock[i].c_price = stock[i].p_price*(1+stock[i].change);
		stock[i].history[a.count] = stock[i].p_price;
		stock[i].p_price = stock[i].c_price;

	}
	


}
void create_space(stock& a) {
	for (int i = 0; i < a.name.length(); i++)
	{
		if (a.name[i]=='1')
			a.name[i] = ' ';
	}
}
int compare(const void *a, const void *b) {
	stock *p1 = (stock*)a;
	stock *p2 = (stock*)b;
	for (int i = 1; i < 5; i++) {
		if (p1->number[i] < p2->number[i])
			return -1;
		else if (p1->number[i] > p2->number[i])
			return 1;
  }
	return 0;
}
void set_stock(stock*&a,index& index,string b) {
	index.longest_string = 0;

	ifstream infile(b);
	infile >> index.p_index;
	//cout.precision(7);
	cout << endl;
	cout << "This is the real data of the stock market of Hong Kong at 26/04/1999" << endl << endl;
	for (int i = 0; i < 33; i++) {
		infile >> a[i].name >> a[i].number >> a[i].percent >> a[i].p_price;
		create_space(a[i]);
		if (a[i].name.length() > index.longest_string)
			index.longest_string = a[i].name.length();

	}
	qsort(a, 33, sizeof(stock), compare);
}
void show_component(stock*a, index b,goal c) {
	cout << "Welcome to stock market ,This is the market today:" <<" (Day "<<c.count<<")"<< endl;
	cout.precision(7);
	cout << "The hang seng index is now " <<"                          "<<(long long) b.p_index << endl;
	cout.precision(4);
	cout << "stock code" << "            " << "stock name" << setw(b.longest_string + 13 - 10) << "stock price";
	if (c.count == 0)
		cout << endl;
	else
	cout<<setw(13) << "change(%)" << endl;
	
	for (int i = 0; i < 33; i++) {
		cout << a[i].number << "                " << a[i].name << setw(b.longest_string + 13 - a[i].name.length()) << a[i].p_price;
		if (c.count == 0)
			cout << endl;
		else
			cout<< setw(13) <<100*a[i].change<< endl;
	}
	
}
void create_history(goal& a, stock *&s,int n) {
	for (int i = 0; i < n; i++)
		s[i].history = new double[a.day];
}
void generate_index(stock*&data, index& hsi, goal a) {
	double dummy_up, dummy_down;
	dummy_down = dummy_up = 0;
	for (int i = 0; i < hsi.n; i++) {
		dummy_down += (data[i].history[a.count] * data[i].percent);
		dummy_up += (data[i].c_price * data[i].percent);
	}
	hsi.history = new double[a.day];
	hsi.history[a.count] = hsi.p_index;
	hsi.index = dummy_up / dummy_down * hsi.p_index;
	hsi.p_index = hsi.index;
	

}void vitrual_market(goal a,index hsi) {
	stock *component = new stock[33];
	string b = "vi(1).txt";
	set_stock(component,hsi,b);
	create_history(a, component, 33);
	a.count = 0;
	for (int i = 0 ; i < a.day; i++) {
		show_component(component, hsi,a);
		generate_stock(component,33,a);
		generate_index(component, hsi, a);
		a.count++;
	}
}
