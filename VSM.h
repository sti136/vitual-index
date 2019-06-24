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
};
struct stock {
	string number;
	string name;
	float  percent;
	float c_price;
	float p_price;
	double* history;
	stock() {
		number = " ";
		name = " ";
		p_price = 0;
		c_price = 0;
		percent = 0;
		
	}
};
struct index {
	int n = 50;
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
		change = -0.127;
		break;

	case(1):
		change = -0.0151;
		break;

	case(2):
		change = -0.0087;
		break;

	case(3):
		change = -0.0045;
		break;

	case(4):
		change = -0.0017;
		break;

	case(5):
		change = 0.0004;
		break;

	case(6):
		change = 0.0027;
		break;
	case(7):
		change = 0.0053;
		break;
	case(8):
		change = 0.0094;
		break;
	case(9):
		change = 0.0158;
		break;
	case(10):
		change = 0.1435;
		break;
	
	}
	
	return change;
}
void generate_stock(stock *&hsi, int n) {
	srand(time(NULL));
	for (int i = 0; i < n - 1; i++) {
		hsi[i].c_price = hsi[i].p_price*(1+generate_change());
	}
	for (int i = 0; i < n - 1; i++)
		cout << hsi[i].c_price << endl;


}
void create_space(stock& a) {
	for (int i = 0; i < a.name.length(); i++)
	{
		if (a.name[i]=='1')
			a.name[i] = ' ';
	}
}
void set_stock(stock*&a,index& index,string b) {
	index.longest_string = 0;
	ifstream infile(b);
	infile >> index.p_index;
	cout.precision(7);
	cout << index.p_index << endl;
	for (int i = 0; i < 33; i++) {
		infile >> a[i].name >> a[i].number >> a[i].percent >> a[i].p_price;
		create_space(a[i]);
		if (a[i].name.length() > index.longest_string)
			index.longest_string = a[i].name.length();

	}
}
void show_component(stock*a, index b) {
	cout << "Welcome to stock market ,This is the market today:" << endl;
	cout << "The hang seng index is now " <<"                          "<< b.p_index << endl;
	cout << "stock code" << "            " << "stock name" << setw(b.longest_string + 13 - 10) << "stock price" << endl;
	for (int i = 0; i < 33; i++) {
		cout << a[i].number << "                "<<a[i].name  << setw(b.longest_string+13-a[i].name.length()) << a[i].p_price << endl;
	}

}
void vitrual_market(goal a,index hsi) {
	stock *component = new stock[33];
	string b = "vi(1).txt";
	set_stock(component,hsi,b);
	show_component(component, hsi);
	//generate_stock(component,50);

 
}
void generate_index(stock*data,index hsi) {

}
