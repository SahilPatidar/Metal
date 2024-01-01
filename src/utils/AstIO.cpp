#include<iostream>
#include"../../include/utils/AstIO.hpp"

namespace astio{

static int& tab() {
    static int t = 0;
    return t;
}

static void tab_apply() {
    for(int i = 0; i < tab(); i++){
        std::cout<<"    ";
    }
}

void tabin() {
    tab()++;
}

void tabbr() {
    tab() = 0;
}

void display(){
    tab_apply();

}




}