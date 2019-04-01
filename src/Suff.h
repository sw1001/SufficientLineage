/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Suff.h
 * Author: shaobo
 *
 * Created on October 12, 2018, 5:43 AM
 */

#ifndef SUFF_H
#define SUFF_H

#include <vector>
#include <string>
#include "DNF.h"

using namespace std;

class Suff {
public:
    Suff();
    Suff(const Suff& orig);
    virtual ~Suff();
    //
    vector < vector<Literal> > findSuff(vector < vector<Literal> >, double);
    vector < vector<Literal> > findMatch(vector < vector<Literal> >);
    double probMC(vector < vector<Literal> >);
    double probMatch(vector < vector<Literal> >);
    double probMono(vector<Literal>);
    bool isIn(Literal, vector<Literal>);
    void printProv(vector < vector<Literal> >);
    //void setSuffProv();
    vector < vector<Literal> > getSuffProv();
    void setSuffProv(vector < vector<Literal> >, double);
    map<string, double> getInfluence();
    void setInfluence(vector < vector<Literal> >);
    vector < vector<Literal> > newLambda(vector < vector<Literal> >, Literal, bool);
    //void printInflu(vector <Literal>);
private:
    vector < vector<Literal> > suffProv;
    map <string, double> influence;
};

#endif /* SUFF_H */

