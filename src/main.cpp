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
#include <time.h>

using namespace std;

/*
 * main method to compute the sufficient lineage given a k-mDNF formula and 
 * an approximation error epsilon greater than 0
 */
int main(int argc, char** argv) {
    // default
    double arr0[] = {0.7, 0.9, 0.8, 0.75, 0.65, 0.85};
    // knows
    double arr1[] = {0.75, 0.25, 0.125, 0.2, 0.6, 0.45, 0.35, 0.15, 0.27, 0.3, 0.4, 0.5}; //array storing probabilities
    // vqa
    double arr2[] = {1.0, 0.88, 0.324991, 0.163589, 1.0, 0.27, 0.878331, 1.0, 0.151069,
    0.00216412, 0.0360805, 0.0772585, 0.192079, 1.0, 0.25765, 0.170949, 0.314978, 0.176289, 
    0.81, 0.388676, 0.576895, 0.163742, 0.232082, 1.0, 7.71032e-05, 0.103899, 0.102172, 
    0.00314313, 0.155558};
    // trust
    double arr3[] = {0.9, 0.6, 0.75, 0.55, 0.9, 0.75, 0.7, 0.65, 0.9, 0.6, 0.7, 0.8, 0.41, 0.63, 0.27};
    // trust acyclic
    double arr4[] = {0.7, 0.9, 0.65, 0.6, 0.75, 0.9};
    // k-mDNF
    string a = "(x1*x2)+(x1*x3)";
    // vqa
    string b = "((r6*(x1*x2*x3*(ra*(x4))*(rb*(x5))*((r2*(x6))+(r3*(x6*x7*x8*(ra*(x9))*(rb*(x10))*(r1*(x6*x2*x3*(ra*(x11))))))+(r3*(x6*x7*x12*(ra*(x13))*(rb*(x10))*(r1*(x6*x14*x3*(ra*(x15))))))+(r3*(x6*x7*x16*(ra*(x17))*(rb*(x18))*(r1*(x6*x19*x20*(ra*(x21)))))))))+(r6*(x1*x14*x3*(ra*(x22))*(rb*(x23))*((r2*(x6))+(r3*(x6*x7*x8*(ra*(x9))*(rb*(x10))*(r1*(x6*x2*x3*(ra*(x11))))))+(r3*(x6*x7*x12*(ra*(x13))*(rb*(x10))*(r1*(x6*x14*x3*(ra*(x15))))))+(r3*(x6*x7*x16*(ra*(x17))*(rb*(x18))*(r1*(x6*x19*x20*(ra*(x21)))))))))+(r6*(x24*x14*x3*(ra*(x25))*(rb*(x13))*((r2*(x6))+(r3*(x6*x7*x8*(ra*(x9))*(rb*(x10))*(r1*(x6*x2*x3*(ra*(x11))))))+(r3*(x6*x7*x12*(ra*(x13))*(rb*(x10))*(r1*(x6*x14*x3*(ra*(x15))))))+(r3*(x6*x7*x16*(ra*(x17))*(rb*(x18))*(r1*(x6*x19*x20*(ra*(x21)))))))))+(r6*(x24*x2*x3*(ra*(x26))*(rb*(x9))*((r2*(x6))+(r3*(x6*x7*x8*(ra*(x9))*(rb*(x10))*(r1*(x6*x2*x3*(ra*(x11))))))+(r3*(x6*x7*x12*(ra*(x13))*(rb*(x10))*(r1*(x6*x14*x3*(ra*(x15))))))+(r3*(x6*x7*x16*(ra*(x17))*(rb*(x18))*(r1*(x6*x19*x20*(ra*(x21)))))))))+(r6*(x1*x19*x20*(ra*(x27))*(rb*(x28))*((r2*(x6))+(r3*(x6*x7*x8*(ra*(x9))*(rb*(x10))*(r1*(x6*x2*x3*(ra*(x11))))))+(r3*(x6*x7*x12*(ra*(x13))*(rb*(x10))*(r1*(x6*x14*x3*(ra*(x15))))))+(r3*(x6*x7*x16*(ra*(x17))*(rb*(x18))*(r1*(x6*x19*x20*(ra*(x21)))))))))+(r6*(x24*x19*x20*(ra*(x29))*(rb*(x17))*((r2*(x6))+(r3*(x6*x7*x8*(ra*(x9))*(rb*(x10))*(r1*(x6*x2*x3*(ra*(x11))))))+(r3*(x6*x7*x12*(ra*(x13))*(rb*(x10))*(r1*(x6*x14*x3*(ra*(x15))))))+(r3*(x6*x7*x16*(ra*(x17))*(rb*(x18))*(r1*(x6*x19*x20*(ra*(x21))))))))))";
    // trust
    string c = "((r2*(x12*((r2*(x5*x13))+(r2*(x6*(r2*(x2*x14))))+(r2*(x3*((r1*(x10))+(r2*(x7*x14)))))+(r2*(x4*((r2*(x9*x14))+(r1*(x11))+(r2*(x8*(r2*(x2*x14))))))))))+(r2*(x1*(r2*(x2*((r2*(x6*x15))+(r2*(x5*x13))+(r2*(x4*((r2*(x9*x14))+(r1*(x11))+(r2*(x8*x15)))))+(r2*(x3*((r1*(x10))+(r2*(x7*x14)))))))))))";
    // knows modified
    string d = "(r2*x1*x2)+(((r2*r13*x3*x4*x5)+(r2*r13*x1*x2*x3*x6)+(r13*x3*x6*x7*x8*x10)+(r13*x3*x6*x7*x8*x9*x11)+(r2*r13*x3*x4*x5*x6*x7*x8))*((x10)+(r2*x4*x5)+(r2*r13*x1*x2*x11*x12)+(r2*r13*x4*x5*x9*x11*x12)+(r13*x3*x7*x8*x9*x11*x12)))";
    // knows raw
    string e = "(rc*(((r2*(x1*(rb*(x2))))+(r13*((r13*(x3*(rc*(((r2*(x4*(rb*(x5))))+(r13*((rc*(x6))*((r2*(x2*(rb*(x1))))+(r13*(x7*(rc*((r13*((rc*(x8))*((rd*(x9))+(r13*(x10*x11))+(r2*(x5*(rb*(x4)))))))))))))))))))*(rc*(((rd*(x9))+(r2*(x5*(rb*(x4))))+(r13*(x11*(r13*(x12*(rc*(((r2*(x2*(rb*(x1))))+(r13*((rc*(x10))*((r2*(x4*(rb*(x5))))+(r13*(x8*(rc*((r13*(x3*(rc*(x7))))))))))))))))))))))))))";
    // trust acyclic
    string f = "(r3*((r2*((x1)*(r1*(r0*(x2)))))*((r2*((x3)*(r2*((x4)*(r1*(r0*(x5)))))))+(r2*((x6)*(r1*(r0*(x5))))))))";
    
    //sample 10
    string s10 = "(r3*(((r1*(x3))+(r2*((x5)*(r1*(x6)))))*((r1*(x1))+(r2*((x2)*(r1*(x7)))))))";
    double arr_s10[] = {0.9,1,0.9,0.9,0.75,1,0.8,0.85};
    
    //sample 20
    string s20 = "(r3*(((r1*(x8))+(r2*((x9)*((r2*((x13)*((r2*((x17)*(r1*(x14))))+(r1*(x15)))))+(r1*(x10))))))*((r2*((x4)*(r2*((x16)*(r1*(x11))))))+(r2*((x5)*(r2*((x19)*(r1*(x11))))))+(r1*(x1))+(r2*((x2)*(r1*(x11)))))))";
    double arr_s20[] = {0.9,1,0.7,0.9,0.95,0.85,0.6,0.9,0.75,1,0.8,0.85,0.75,0.65,0.9,0.6,0.6,0.85,0.7,0.55,0.65,1};
    
    //sample 30
    string s30 = "(r3*(((r2*((x6)*((r2*((x15)*(r2*((x18)*((r2*((x10)*(r2*((x27)*(r2*((x24)*(r1*(x20))))))))+(r2*((x11)*(r1*(x28)))))))))+(r1*(x14))+(r2*((x16)*(r2*((x24)*(r1*(x20)))))))))+(r1*(x5))+(r2*((x7)*((r2*((x18)*((r2*((x10)*((r2*((x25)*((r2*((x16)*(r2*((x24)*(r1*(x20))))))+(r1*(x14)))))+(r2*((x27)*((r2*((x23)*(r1*(x14))))+(r2*((x24)*(r1*(x20))))))))))+(r2*((x9)*((r2*((x16)*(r2*((x24)*(r1*(x20))))))+(r1*(x14)))))+(r2*((x11)*(r1*(x28)))))))+(r2*((x19)*((r2*((x16)*(r2*((x24)*(r1*(x20))))))+(r1*(x14)))))))))*((r2*((x2)*((r2*((x10)*((r2*((x26)*(r2*((x19)*(r2*((x16)*(r1*(x21))))))))+(r2*((x27)*(r1*(x21))))+(r2*((x25)*(r2*((x16)*(r1*(x21)))))))))+(r2*((x9)*(r2*((x16)*(r1*(x21)))))))))+(r2*((x3)*((r2*((x15)*(r2*((x18)*(r2*((x10)*(r2*((x27)*(r1*(x21))))))))))+(r2*((x16)*(r1*(x21)))))))+(r2*((x4)*(r1*(x21)))))))";
    double arr_s30[] = {0.8,1,0.9,0.85,0.9,0.75,0.75,0.85,0.75,0.9,0.65,0.8,0.65,0.9,0.75,0.65,0.8,0.7,0.65,0.65,0.85,0.85,0.85,0.55,0.45,0.55,0.9,0.95,0.65};
    
    //sample 50
    string s50 = "(r3*(((r2*((x10)*((r2*((x39)*((r2*((x35)*(r2*((x19)*(r1*(x44))))))+(r1*(x33)))))+(r2*((x38)*(r2*((x19)*(r1*(x44)))))))))+(r2*((x8)*((r2*((x19)*((r2*((x46)*(r2*((x26)*(r2*((x32)*(r2*((x39)*(r1*(x33))))))))))+(r1*(x44)))))+(r2*((x18)*(r2*((x39)*(r1*(x33)))))))))+(r2*((x12)*((r2*((x49)*((r2*((x23)*((r2*((x18)*(r2*((x39)*(r1*(x33))))))+(r2*((x19)*(r1*(x44)))))))+(r2*((x26)*((r2*((x32)*((r2*((x39)*((r2*((x35)*(r2*((x19)*(r1*(x44))))))+(r1*(x33)))))+(r2*((x38)*(r2*((x19)*(r1*(x44)))))))))+(r2*((x31)*((r2*((x18)*(r2*((x39)*(r1*(x33))))))+(r2*((x19)*(r1*(x44))))))))))+(r2*((x29)*((r2*((x45)*(r2*((x18)*(r2*((x39)*(r1*(x33))))))))+(r1*(x44))))))))+(r2*((x48)*((r2*((x19)*((r2*((x46)*(r2*((x26)*(r2*((x32)*(r2*((x39)*(r1*(x33))))))))))+(r1*(x44)))))+(r2*((x18)*(r2*((x39)*(r1*(x33)))))))))))))*((r2*((x5)*((r2*((x39)*(r2*((x35)*((r2*((x19)*(r2*((x46)*(r1*(x21))))))+(r1*(x16)))))))+(r2*((x38)*((r2*((x19)*(r2*((x46)*(r1*(x21))))))+(r1*(x16))))))))+(r2*((x4)*((r2*((x29)*(r2*((x45)*(r1*(x16))))))+(r2*((x30)*(r2*((x48)*(r1*(x16))))))+(r2*((x23)*(r1*(x16))))+(r1*(x21))+(r2*((x26)*((r2*((x32)*((r2*((x39)*(r2*((x35)*(r1*(x16))))))+(r2*((x38)*(r1*(x16)))))))+(r2*((x31)*(r1*(x16))))))))))+(r1*(x1))+(r2*((x6)*(x22)))+(r2*((x2)*(r2*((x13)*((r2*((x19)*(r2*((x46)*(r1*(x21))))))+(r1*(x16))))))))))";
    double arr_s50[] = {0.9,0.7,0.6,0.65,0.8,0.55,0.75,0.75,0.75,0.75,0.9,0.6,0.55,0.6,0.75,0.75,0.55,0.7,0.55,1,0.6,0.9,0.55,0.9,0.9,0.6,1,0.6,0.55,0.7,0.7,0.55,0.95,0.65,0.95,0.75,0.75,0.75,0.55,0.55,0.6,0.55,0.6,0.55,0.55,0.55,0.9,0.95,0.65};
    
    map<string, double> p;
    int sa = sizeof(arr_s50)/sizeof(arr_s50[0]);
    cout<<"number of literals: "<<sa<<endl;
    for (int i = 0; i < sa; i++) {
        string name = "x";
        stringstream ss;
        ss << (i + 1);
        name = name + ss.str();
        cout<<name<<" ";
        p[name] = arr_s50[i];
        cout<<p[name]<<endl;
    }

    p["ra"] = 1.0;
    p["rb"] = 1.0;
    p["r0"] = 1.0;
    p["r1"] = 1.0;    
    p["r2"] = 1.0;
    p["r3"] = 0.8;
    p["r4"] = 1.0;
    p["r5"] = 1.0;
    p["r6"] = 1.0;
    
    cout<<endl;
    clock_t t1 = clock();
    DNF dnf (s50, p);
    t1 = clock()-t1;
    cout<<"DNF running time: "<<((float)t1)/CLOCKS_PER_SEC<<" seconds"<<endl;
    dnf.ShowStructure();
    cout<<dnf.ToString()<<endl;
    
    Suff suff;    
    cout<<"Original formula: "<<endl;
    suff.printProv(dnf.getLambda());
    double pLambda = suff.probMC(dnf.getLambda());
    cout<<"pLambda = "<<pLambda<<endl;
    
    clock_t tsuff = clock();
    double epsilon = 0.099*pLambda; // approximation error
    suff.setSuffProv(dnf.getLambda(), epsilon);
    tsuff = clock() - tsuff;
    cout<<"Suff lineage time: "<<((float) tsuff)/CLOCKS_PER_SEC<<" seconds"<<endl;
    cout<<"Sufficient lineage: "<<endl;
    suff.printProv(suff.getSuffProv());
    
    
    cout<<"Influence:" <<endl;
    clock_t t2 = clock();
    suff.setInfluence(/*dnf.getLambda()*/suff.getSuffProv());
    t2 = clock() - t2;
    cout<<"Influence running time: "<<((float)t2)/CLOCKS_PER_SEC<<" seconds"<<endl;
    Literal x = suff.maxInfluence();
    cout<<"maxInfluence Literal: "<<x.getName()<<" "<<x.getProb()<<endl;
    
    //clock_t t3 = clock();
    //vector<Literal> vcl = suff.changedLiterals(dnf.getLambda()/*suff.getSuffProv()*/, 0.7);
    //t3 = clock() - t3;
    //cout<<"Changed literals running time: "<<((float)t3)/CLOCKS_PER_SEC<<" seconds"<<endl;
    //cout<<"Changed Literals: "<<endl;
    //suff.print(vcl);
    
    return 0;
}

