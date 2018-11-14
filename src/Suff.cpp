/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Suff.cpp
 * Author: shaobo
 * 
 * Created on October 12, 2018, 5:43 AM
 */

#include <algorithm>
#include "Suff.h"

using namespace std;

Suff::Suff() {
}

Suff::Suff(const Suff& orig) {
}

Suff::~Suff() {
}

vector < vector <Literal> > Suff::findMatch(vector < vector <Literal> > lambda) {
    //greedily find a match
    vector <string> names(0);
    vector < vector <Literal> > match(0);
    match.push_back(lambda[0]);
    for (int i = 0; i < lambda[0].size(); i++) {
        names.push_back(lambda[0][i].getName());
    }
    for (int i = 1; i < lambda.size(); i++) {
        bool independent = true;
        for (int j = 0; j < lambda[i].size(); j++) {
            if (find(names.begin(), names.end(), lambda[i][j].getName()) != names.end()) {
                independent = false;
                break;
            }
        }
        if (independent) {
            match.push_back(lambda[i]);
            for (int j = 0; j < lambda[i].size(); j++) {
                names.push_back(lambda[i][j].getName());
            }
        }
    }
    return match;
}

vector < vector <Literal> > Suff::findSuff(vector < vector <Literal> > lambda, double epsilon) {
    vector < vector <Literal> > match = Suff::findMatch(lambda);
    //cout<<"print match"<<endl;
    //Suff::print(match);
    double pLambda = Suff::probMC(lambda);
    //cout<<"pLambda = "<<pLambda<<endl;
    double pMatch = Suff::probMatch(match);
    //cout<<"pMatch = "<<pMatch<<endl;
    int l = match.size();
    //cout<<"print match size"<<endl;
    //cout<<l<<endl;
    if(pLambda - pMatch <= epsilon) {
        //Sort(match);
        vector < vector < Literal > > m(0);        
        double order[l];
        double order_copy[l];
        int order_index[l];
        for (int i = 0; i < l; i++) {
            order[i] = Suff::probMono(match[i]);
            order_copy[i] = Suff::probMono(match[i]);
            order_index[i] = i;
        }
        /*sort(order_index.begin(), order_index.end(), [&](int x, int y) { \
            return order[x] < order[y]; });*/
        
        sort(order, order + l, greater<double>());
        for (int i = 0; i < l ; i++) {
            order_index[i] = find(order_copy, order_copy + l, order[i]) - order_copy;
        }
                
        for (int i = 0; i < l ; i++) {
            m.push_back(match[order_index[i]]);
            //cout<<"m = ";
            //Suff::print(m);
            if(pLambda - Suff::probMatch(m) <= epsilon){
               break; 
            }            
        }
        //cout<<"m = "<<endl;
        //Suff::print(m);
        return m;
    } else {
        //find a small cover        
        vector <Literal> cover(0);
        for (int i = 0; i < l ; i++) {
            for (int j = 0; j < match[i].size(); j++) {
                cover.push_back(match[i][j]);
            }
        }
        int c = cover.size();
        //cout<<"print cover size"<<endl;
        //cout<<c<<endl;
        //create a set of buckets
        vector <  vector < vector <Literal> > > buckets(c);
        //each mono in lambda
        for (int i = 0; i < lambda.size(); i++) {
            //each literal in mono
            vector <Literal> candidates(0);
            for (int j = 0; j < lambda[i].size(); j++) {
                //find potential covers
                if(Suff::isIn(lambda[i][j], cover)) {
                    candidates.push_back(lambda[i][j]);
                }
            }
            //arbitrarily pick a candidate literal
            Literal candidate = candidates[rand() % candidates.size()];
            //remove candidate from lambda[i] and send it to corresponding bucket
            for (int j = 0; j < lambda[i].size(); j++) {
                if(lambda[i][j].getName() == candidate.getName()){
                    lambda[i].erase(lambda[i].begin() + j);
                    break;
                }
            }
            for (int j = 0; j < c; j++) {
                if(cover[j].getName() == candidate.getName()){
                    buckets[j].push_back(lambda[i]);
                    break;
                }
            }
        }
        //iterate through each bucket
        vector< vector<Literal> >  lambda_s(0);
        for (int i = 0; i < buckets.size(); i++) {
            //cout<<"print buckets["<<i<<"]"<<endl;
            //Suff::print(buckets[i]);
            //cout<<buckets.size()<<endl;
            if (!buckets[i].empty()) {
                vector< vector<Literal> > v = Suff::findSuff(buckets[i], epsilon / c);
                for (int j = 0; j < v.size(); j++) {
                    lambda_s.push_back(v[j]);
                }
            }
                        
        }
        return lambda_s;
    }
    
}

//MC simulation
double Suff::probMC(vector< vector<Literal> > v) {
    double rounds = 10000.0;
    double sum = 0.0;
    //cout<<"print v"<<endl;
    //Suff::print(v);
    //simulation
    for (int i = 0; i < rounds; i++) {
        //generate an assignment
        vector <string> litsDone(0);
        vector < pair<string, double> > assignment(0);        
        int vs = v.size();
        for (int j = 0; j < vs; j++) {
            int vms = v[j].size();
            for (int k = 0; k < vms; k++) {
                //if literal was not processed before
                if (find(litsDone.begin(), litsDone.end(), v[j][k].getName()) == litsDone.end()) {
                    //randomly assign a literal based on its probability
                    double prand = (double) rand() / (RAND_MAX + 1.0);
                    //cout<<"prand = "<<prand<<endl;
                    pair <string, double> assignLiteral;
                    if (v[j][k].getProb() < prand) {
                        assignLiteral = make_pair(v[j][k].getName(), 0.0);
                    } else {
                        assignLiteral = make_pair(v[j][k].getName(), 1.0);
                    }
                    litsDone.push_back(v[j][k].getName());
                    assignment.push_back(assignLiteral);
                }
            }
        }
        //compute
        double value = 0.0;
        //for each monomial
        for (int j = 0; j < vs; j++) {
            int vms = v[j].size();
            //for each literal
            double valueMono = 1.0;
            for (int k = 0; k < vms; k++) {
                for (int a = 0; a < assignment.size(); a++) {
                    if (v[j][k].getName() == assignment[a].first && assignment[a].second == 0.0) {
                        valueMono = 0.0;
                        break;
                    }
                }
                if (valueMono == 0.0) {
                    break;
                }
            }
            if (valueMono == 1.0) {
                value = 1.0;
                break;
            }
        }
        
        //update sum
        sum += value;
        
    }
    //cout<<"print probability"<<endl;
    //cout<<sum/rounds<<endl;
    return sum / rounds;
}

double Suff::probMatch(vector< vector<Literal> > v) {
    double p = 1.0;
    for (int i = 0; i < v.size(); i++) {
        p *= (1.0 - Suff::probMono(v[i]));
    }
    
    return 1.0 - p;
}

double Suff::probMono(vector<Literal> v) {
    double p_m = 1.0;
    for (int i = 0; i < v.size(); i++) {
        p_m *= v[i].getProb();
    }
    
    return p_m;
}

bool Suff::isIn(Literal x, vector<Literal> cover) {
    for(int i = 0; i < cover.size(); i++) {
        if(x.getName() == cover[i].getName()) {            
            return true;
        }
    }
    return false;
}


void Suff::print(vector< vector<Literal> > v) {    
    int n = v.size();
    for(int i = 0; i < n; i++) {
        int m = v[i].size();
        for(int j = 0; j < m; j++){
            cout<<v[i][j].getName()<<", ";
        }
        cout<<endl;
    }
}

/*
void Suff::setSuffProv() {
    suffProv = Suff::findSuff();
}
*/