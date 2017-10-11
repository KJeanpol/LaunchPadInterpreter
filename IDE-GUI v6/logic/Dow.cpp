//
// Created by Luis on 29/9/2017.
//

#include "Dow.h"

Dow::Dow(string pvar) {
    var=pvar;

}


void Dow::execute()
{



        cout<<sentences.size()<<endl;
        for(int i=0;i!=sentences.size();i++){
            setVal(var, valor1);
            cout<<i<<endl;
            if(sentences[i]->exit!=true){
                cout<<"AAA";

                sentences[i]->setPara();
                for(int j=0;j!=sentences[i]->params.size();j++){
                    if(var.compare((sentences[i]->params[j]))==0){
                       sentences[i]->values[j] = valor1;
                    }
                }
                sentences[i]->execute();
                valor1 = valor1+valor2;

                if(i==sentences.size()-1){
                    i=0;
                }
            }else{
                sentences[i]->execute();
            }
        }return;
    }

