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
#include <cmath>

using namespace std;

/*
 * 
 */
string *all_motifs(int length ){
    int *mas=new int[length];
    int number=1;
    int y=pow(4,length);// кол-во всех наборов из  A C G T  длины length
    string *rez= new string [y];
    for(int i=0;i<length;i++){
        mas[i]=0;
    }
    for(int i=0;i<length;i++) rez[0]+='A';
    int pr=0;
    while(pr==0){
       if (mas[length-1]==3){
           mas[length-1]=0;
           int pr1=0;
           int k=length-2;
           while(pr1==0){
               if(mas[k]==3){
                    mas[k]=0;
                    k--;
                }
                else {
                    mas[k]++;
                    pr1=1;
                }       
           }
       }
       else mas[length-1]++;
    //проверка на совпадение 
    int ch=0;
    for(int i=0;i<length;i++){
        if(mas[i]==3)ch++;    
        switch (mas[i]){
            case 0 : rez[number]+="A";break;
            case 1 : rez[number]+="C";break;
            case 2 : rez[number]+="G";break;
            case 3 : rez[number]+="T";break; 
        }
        //cout<<mas[i];
    } 
    number++;
    if(ch==length) pr=1;
    } 
    return rez;
}


int hamming_distance(string str, string original,int length){
    int rez=0;
    for(int i=0;i<length;i++){
        if(str[i]!=original[i]) rez++;
    }
    return rez;
}


int main(int argc, char** argv) {
    ifstream input_file("Input.txt");
    ifstream input_file2("Input.txt");
    ofstream output_file("Output.txt");
    string *str;
    string a1;
    string result;//результат
    string motifs;//текущий  мотив
    string **all_patterns;//все наборы из строки
    string *original; //наборы составленые из A C G T
    int length_pattern;
    int number_str;
    int length_str;
    int best_hamming=INT_MAX;//наилучшее расстяние хэмминга
    int hamming;// расстояние хэмминга для текущего 
    getline(input_file,a1,' ');
    length_pattern=atoi(a1.c_str());
    
    //считаем кол-во 
    while (!input_file.eof())
    {
        string tmp;
        getline(input_file, tmp, '\n');
        number_str++;
    }
    number_str--;//удаляем певую строчку
    str=new string [number_str];
    
    for(int i=0;i<number_str+1;i++){
        string tmp;
        getline(input_file2,tmp,'\n');
        if(i>0) {str[i-1]=tmp;length_str=tmp.length(); }
    }
    //cout<<number_str;
    all_patterns=new string* [number_str];
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
    //cout<<length_pattern;
    int z=pow(4,length_pattern);
    int sum_hamming;
    int best_sum_hamming=INT_MAX;
    original=new string[z];
    original=all_motifs(length_pattern);
    
    for(int i=0;i<z;i++){//цикл по наборам AAA...TTT
        sum_hamming=0;
        for(int j=0;j<number_str;j++){// цикл по строкам
            best_hamming=INT_MAX;
            for(int h=0;h<length_str-length_pattern+1;h++){
               hamming=hamming_distance(original[i],all_patterns[j][h],length_pattern);
               //cout<<hamming<<" ";
               if(best_hamming>=hamming){
                   best_hamming=hamming;
               }
//               cout<<best_hamming<<" ";
            }
            //cout<<endl;
            sum_hamming+=best_hamming;
            
        }
        
        cout<<endl;
        cout<<sum_hamming<<" ";
        if(best_sum_hamming>=sum_hamming){
            best_sum_hamming=sum_hamming;
            result=original[i];
        }
        cout<<best_sum_hamming;
    }
    cout<<result;
     
    output_file<<result;
    output_file.close();
    input_file.close();
//    for (int i = 0; i < number_str; i++)
//        delete [] all_patterns[i];
//    delete str;
//    delete result;
//    delete motifs;
    return 0;
}

