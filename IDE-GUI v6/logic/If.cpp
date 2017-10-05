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
            if(getVar(vals1[i])==vals2[i]){
                cout<<sentences[i]->getName()<<endl;
               sentences[i]->execute();
                return;
            }
        }sentences[sentences.size()-1]->execute();
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


