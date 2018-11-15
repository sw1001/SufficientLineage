/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: shaobo
 *
 * Created on October 12, 2018, 3:32 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "DNF.h"
#include "Suff.h"

using namespace std;

/*
 * main method to compute the sufficient lineage given a k-mDNF formula and 
 * an approximation error epsilon greater than 0
 */
int main(int argc, char** argv) {
    
    string s = "(x1*x2)+(x1*x3)"; //some k-mDNF
    double arr[] = {0.75, 0.25, 0.125, 0.2, 0.6, 0.45, 0.35, 0.15}; //array holding probabilities
            
    string a = "(x1*x2)+(x3*x4)";
    string b = "(x1+x2)*x3";
    string c = "x1+x2";
    string d = "(x1+x2)*(x3+x4)";
    string e = "x6*(x7+x8)";
    string f = "(x6*(x7+x8))";
    string g = "(((x1+x2)*x3)*((x1*x2)+(x3*x4))*x3)+(x6*(x7+x8))";    
    string h = "(x3*x4*x5)+(x6*x7)";
    string i = "(x1+x2)*((x3*x4*x5)+(x6*x7))";
    string j = "(x1+x2)*((x3*x4*x5)+(x6*x7)+x8)";
    string k = "(x1*(x2+(x4+(x5*x6)+(x7*x8))))";
    
    map<string, double> p;
    int sa = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < sa; i++) {
        string name = "x";
        stringstream ss;
        ss << (i + 1);
        name = name + ss.str();
        cout<<name<<" ";
        p[name] = arr[i];
        cout<<p[name]<<endl;
    }
    cout<<endl;
    DNF dnf (s, p);
    dnf.ShowStructure();
    cout<<dnf.ToString()<<endl;
    
    double epsilon = 0.0625; // approximation error
    Suff suff;
    cout<<"Original formula: "<<endl;
    suff.print(dnf.getLambda());
    cout<<"Sufficient lineage: "<<endl;
    suff.print(suff.findSuff(dnf.getLambda(), epsilon));
    return 0;
}

