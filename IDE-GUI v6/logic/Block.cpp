//
// Created by Jeanpol on 18/9/2017.
//

#include "Block.h"
Block::Block()
{
    father = this;
}

void Block::setPara(){
    for(int i=0;i!=params.size();i++){
        if(paramtypes[i].compare("var")==0){
        values.push_back(getVar(params[i]));
        }else{
        values.push_back(stoi(params[i]));
        }
      }
}


bool Block::hasBlock(){
    if(sentences.size()==0){
        return false;
    }else{
        return true;
    }
}

void Block::addSentence(Block* sentence)
{
    sentences.push_back(sentence);
    sentences.back()->setFather(this);
    sentences.back()->setjuego(this->juego);
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
bool Block::isInit(string pname){
    for (int i=0; i!=INZ.size();i++){
        if (pname.compare(INZ[i]->getName()) == 0) return true;
        cout<< pname <<"INICIALIZADA"<<endl;
    }
    if (father!= this){ return father->isInit(pname);}else{
    return false;}
}

void Block::setVal(string pname,int pval){
    for (int i=0; i!=Variables.size();i++){

        if (pname.compare(Variables[i]->getName()) == 0){ this->Variables[i]->setValues(pval);
        return;}
    }
    if (father!= this){ return father->setVal(pname,pval);}else{

    QString variab = QString::fromStdString(pname);
    ID->console(variab +": No existe o no esta inicializada");}

    return;
}

void Block::addVars(Var* pvar){
    Variables.push_back(pvar);
}

int Block::getVar(string pname)
{

    for (int i=0;i!=Variables.size();i++){
        if (Variables[i]->getName().compare(pname) == 0){ return Variables[i]->getVal();}
    }
    if (father!= this) {return father->getVar(pname);}else{
    return 0;}

}

void Block::increase(string pname)
{

    for (int i=0;i!=Variables.size(); i++){
        cout<<pname<<endl;
        cout<<"--X--"<<endl;
        cout<<Variables[i]->getName()<<endl;
        if (pname.compare(Variables[i]->getName()) == 0) { cout<<"DIS NIGGA"<<Variables[i]->getVal()<<endl; Variables[i]->value=(Variables[i]->value)+1;}

    }
    if (father!= this){ return father->increase(pname);}
}
void Block::decrease(string pname)
{
    cout << "Decremento: ";
    for (int i=0;i!=Variables.size(); i++){
        cout<<Variables[i]->getName();
        if (pname.compare(Variables[i]->getName()) == 0){
            if(Variables[i]->getVal()!=0){
                cout<<Variables[i]->getVal()<<endl;
                Variables[i]->value=(Variables[i]->value)-1;


                return;
            }else{
                ID->console("ERROR: No se puede hacer un decremento");
                cout<<"ERROR: No se puede hacer un decremento"<<endl;
                return;
            }
        }
    }
    if (father!= this){ return father->decrease(pname);}else{ID->console("ERROR: No se puede hacer un decremento");cout<<"ERROR: No se puede hacer un decremento"<<endl; }
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
