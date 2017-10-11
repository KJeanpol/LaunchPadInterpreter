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
            if(isInit(vals1[i])){
                cout<<"SOOOO"<<endl;
            if(getVar(vals1[i])==vals2[i]){
                cout<<sentences[i]->getName()<<endl;
             for(int j=0;j!=sentences.size();j++){
              if(sentences[j]->If==i+1){
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
            if(sentences[i]->If==i+1){
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


