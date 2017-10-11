//
// Created by Luis on 2/10/2017.
//

#include "If.h"
If::If() {
}

void If::execute(){
        for(int i=0;i!=vals1.size();i++){
            cout<<"If "<<getVar(vals1[i])<< " equals " <<vals2[i]<<endl;
            cout<<i<<endl;
            if(getVar(vals1[i])!=0){
                cout<<"Size "<<vals2.size()<<endl;
                cout<<"Size1 "<<vals1.size()<<endl;
            if(getVar(vals1[i])==vals2[i]){
                cout<<sentences[i]->getName()<<endl;
             for(int j=0;j!=sentences.size();j++){
              if(sentences[j]->If==i+1){
                  cout<<sentences[j]->getName()<<endl;
               sentences[j]->execute();
                }
             }return;
            }
            }else{
                QString ss = QString::fromStdString(vals1[i]);
                ID->console("Error: "+ ss+" No esta inicializada");
                return;
            }
        }for(int i=vals1.size();i!=sentences.size();i++){
            if(sentences[i]->If==0){
             sentences[i]->execute();
              }}
    }

If:: ~If(){
    while(!sentences.empty()){
        delete sentences.back();
        sentences.pop_back();
    }
    while(!vals1.empty()){
        delete Variables.back();
        Variables.pop_back();
    }
    while(!vals2.empty()){
        delete Variables.back();
        Variables.pop_back();
    }
}


