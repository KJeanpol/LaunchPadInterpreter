//
// Created by Jeanpol on 18/9/2017.
//

#include "Block.h"
Block::Block()
{
    father = this;
}

bool Block::hasBlock(){
    if(sentences.size()==0 || sentences.back()->name.compare("ard")==0){
        return false;
    }else{
        return true;
    }
}

void Block::addSentence(Block* sentence)
{
    sentences.push_back(sentence);
    sentences.back()->setFather(this);
}


void Block::setFather(Block* pfather)
{
    father=pfather;
}

Block::~Block()
{
    while(!sentences.empty()){
        delete sentences.back();
        sentences.pop_back();
    }
    while(!Variables.empty()){
        delete Variables.back();
        Variables.pop_back();
    }
}
bool Block::hasVariable(string pname)
{

    for (int i=0; i!=Variables.size();i++){
        if (pname.compare(Variables[i]->getName()) == 0) return true;
    }
    if (father!=this) return father->hasVariable(pname);
    return false;

}

void Block::setVal(string pname,int pval){
    for (int i=0; i!=Variables.size();i++){
        if (pname.compare(Variables[i]->getName()) == 0) Variables[i]->setVal(pval);
        cout<<"INICIALIZADA"<<endl;
    }
    if (father!= this) return father->setVal(pname,pval);
    return;
}

void Block::addVars(Var* var){
    Variables.push_back(var);
}

int Block::getVar(string pname)
{

    for (int i=0;i!=Variables.size();i++){
        if (pname.compare(Variables[i]->getName()) == 0) return Variables[i]->getVal();
    }
    if (father!= this) return father->getVar(pname);
    return false;

}

void Block::increase(string pname)
{
    cout << "Increasing: ";
    for (int i=0;i!=Variables.size(); i++){
        if (pname.compare(Variables[i]->getName()) == 0) Variables[i]->setVal(Variables[i]->getVal() +1);

    }
    if (father!= this) return father->increase(pname);
}
void Block::decrease(string pname)
{
    cout << "Decremento: ";
    for (int i=0;i!=Variables.size(); i++){
        if (pname.compare(Variables[i]->getName()) == 0){
            if(Variables[i]->getVal()!=0){
                cout<<Variables[i]->getVal()<<endl;
                Variables[i]->setVal(Variables[i]->getVal()-1);

                return;
            }else{
                cout<<"ERROR: No se puede hacer un decremento"<<endl;
                return;
            }
        }
    }
    if (father!= this) return father->decrease(pname);
}
//--------------------------------------------//

void Block::execute()
{
    //cout<<sentences.back()->getName()<<endl;
    cout << "Execute: " << sentences.size()<< getName()<<" orders"<<endl;
    for (int i=0;i!=sentences.size();i++){
        sentences[i]->execute();
    }
}
