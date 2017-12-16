/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: macbookpro
 *
 * Created on 16 декабря 2017 г., 23:34
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
 ifstream input_file("Input.txt");
    ofstream output_file("Output.txt");
    string *str;
    string a1;
    string *result;//результат
    string *motifs;//текущий набор мотивов
    string **all_patterns;//все наборы 
    int length_pattern;
    int number_str;
    int length_str;
    int best_score=0;//наилучшее score
    int score;//score для текущего 
    getline(input_file,a1,' ');
    length_pattern=atoi(a1.c_str());
    while (!input_file.eof())
    {
        string tmp;
        getline(input_file, tmp, '\n');
        number_str++;
    }
    number_str--;//удаляем певую строчку
    cout<<number_str;
    str=new string [number_str];
    //считывание строк с ДНК 
    for(int i=0;i<number_str+1;i++){
        string tmp;
        getline(input_file,tmp,'\n');
        if(i>0) str[i-1]=tmp;
    }
    motifs=new string [number_str];
    result=new string [number_str];
    all_patterns=new string* [number_str];
    length_str=str[0].length();
    //инициализация массива со всеми возможными наборами
    for(int i=0;i<number_str;i++){
        all_patterns[i]=new string [length_str-length_pattern+1];
    }
    //заполнение всеми возможными наборами шаблонов 
    for(int i=0;i<number_str;i++){
        string tmp_str=str[i];
        for(int j=0;j<length_str-length_pattern+1;j++){
            for(int k=j;k<j+length_pattern;k++){
                all_patterns[i][j]+=tmp_str[k];
            }
        }
    }
   
    
    
     
    output_file<<result;
    output_file.close();
    input_file.close();
    return 0;
}

