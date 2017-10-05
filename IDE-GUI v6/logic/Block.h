//
// Created by Jeanpol on 18/9/2017.
//

#ifndef SEMANTICANALYSIS_BLOCK_H
#define SEMANTICANALYSIS_BLOCK_H


#include <vector>
#include <string>
#include<stdio.h>
#include <iostream>
#include "Var.h"

using namespace std;

class Block{
public:
    Block* father;
    //IF
    vector <string> vals1;
    vector <int> vals2;
    void setVal1(string pname){
        vals1.push_back(pname);
    }
    void setVal2(int val){
        vals2.push_back(val);
    }
    //FOR
    int times;
    //DOW
    string var;
    int valor1;
    int valor2;
    void setVarD(string pvar){
        var=pvar;
    }
    void setValor1(int pval){
        valor1=pval;
    }
    void setValor2(int pval){
        valor2=pval;
    }
    //INCREASE-DECREASE
    string vardec;
    string varinc;
    void setVarDec(string pvar){
        vardec=pvar;
    }
    void setVarInc(string pvar){
        varinc=pvar;
    }

    //BLOCK
    std::vector<Block *> sentences;
    string name;
    std::vector< Var * > Variables;
    Block();
    void setName(string pname){
        name=pname;
        cout<<name<<endl;
    }
    string getName(){
        return name;
    }
    void addVars(Var *var);
    bool hasVariable(string pname);
    bool hasBlock();
    int getVar(string pname);
    void addSentence(Block *sentence);
    void setFather(Block *pfather);
    void increase(string pname);
    void decrease(string pname);
    void setVal(string pname, int val);
    virtual ~Block();

    // CodeSentence interface
public:
    virtual void execute();
};


#endif //SEMANTICANALYSIS_BLOCK_H
