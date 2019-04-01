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
    
    string s = "(x7*(x1*x2))+(x8*(x1*x3))"; //some k-mDNF
    double arr[] = {0.75, 0.25, 0.125, 0.2, 0.6, 0.45, 0.35, 0.15, 0.27, 0.3, 0.4, 0.5}; //array storing probabilities
    double arr2[] = {0.7, 0.9, 0.8, 0.75, 0.65, 0.85};        
    string a = "(x1*x2)+(x3*x4)";
    string b = "(x1+x2)*x1";
    string c = "x1+x2";
    string d = "(x1+x2)*(x3+x4)";
    string e = "x6*(x7+x8)";
    string f = "(x6*(x7+x8))";
    string g = "(((x1+x2)*x3)*((x1*x2)+(x3*x4))*x3)+(x6*(x7+x8))";    
    string h = "(x3*x4*x5)+(x6*x7)";
    string i = "(x1+x2)*((x3*x4*x5)+(x6*x7))";
    string j = "(x1+x2)*((x3*x4*x5)+(x6*x7)+x8)";
    string k = "(x1*(x2+(x4+(x5*x6)+(x7*x8))))";
    string l = "x1*(x2*(x3*x4*(x5)))";
    string m = "(x1*x1*x2)+(x1*x1*x3)";
    string n = "(x6*x2*x3)+(x7*x4*x5)+(x8*(x6*x1*x2)*(x6*x1*x3))";
    string o = "r2*x1*x2+r13*(r13*(x3*(r2*x4*x5+r13*(x6*(r2*x2*x1+r13*(x7*(r13*(x8*(x10+r13*x9*x11+r2*x5*x4))))))))*(x10+r2*x5*x4+r13*(x11*r13*(x12*(r2*x2*x1+r13*(x9*(r2*x4*x5+r13*x8*r13*x3*x7)))))))";
    string q = "(r2*x1*x2)+r13*(r2*x3*x4*x5+r13*x6*r2*x2*x1*x3+r13*x3*x6*x7*x8*x10+r13*x3*x6*x7*x8*x9*x11+r13*r2*x3*x5*x4*x6*x7*x8)*(x10+r2*x5*x4+x11*r13*x12*r2*x2*x1+r13*x9*r2*x4*x5*x11*x12+x9*x8*r13*x3*x7*x11*x12)";
    string r = "(r2*x1*x2)+(((r2*r13*x3*x4*x5)+(r2*r13*x1*x2*x3*x6)+(r13*x3*x6*x7*x8*x10)+(r13*x3*x6*x7*x8*x9*x11)+(r2*r13*x3*x4*x5*x6*x7*x8))*((x10)+(r2*x4*x5)+(r2*r13*x1*x2*x11*x12)+(r2*r13*x4*x5*x9*x11*x12)+(r13*x3*x7*x8*x9*x11*x12)))";
    string t = "x1+(x1*x2)";
    string u = "(x1*x2)+(x1*x3)";
    string v = "(rc*(((r2*(x1*(rb*(x2))))+(r13*((r13*(x3*(rc*(((r2*(x4*(rb*(x5))))+(r13*((rc*(x6))*((r2*(x2*(rb*(x1))))+(r13*(x7*(rc*((r13*((rc*(x8))*((rd*(x9))+(r13*(x10*x11))+(r2*(x5*(rb*(x4)))))))))))))))))))*(rc*(((rd*(x9))+(r2*(x5*(rb*(x4))))+(r13*(x11*(r13*(x12*(rc*(((r2*(x2*(rb*(x1))))+(r13*((rc*(x10))*((r2*(x4*(rb*(x5))))+(r13*(x8*(rc*((r13*(x3*(rc*(x7))))))))))))))))))))))))))";
    
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
    p["r2"] = arr2[0];
    p["r13"] = arr2[1];
    p["ra"] = arr2[2];
    p["rb"] = arr2[3];
    p["rc"] = arr2[4];
    p["rd"] = arr2[5];
    
    cout<<endl;
    DNF dnf (v, p);
    dnf.ShowStructure();
    cout<<dnf.ToString()<<endl;
    
    double epsilon = 0.1; // approximation error
    Suff suff;
    cout<<"Original formula: "<<endl;
    suff.printProv(dnf.getLambda());
    
    
    suff.setSuffProv(dnf.getLambda(), epsilon);
    cout<<"Sufficient lineage: "<<endl;
    suff.printProv(suff.getSuffProv());
    cout<<"Influence:" <<endl;
    suff.setInfluence(dnf.getLambda()/*suff.getSuffProv()*/);
    
    return 0;
}

