//
//  main.cpp
//  hw02.cpp
//
//  Created by Elias Attias on 2/2/20.
//  Copyright © 2020 Elias Attias. All rights reserved.
// This code models a game of medieval times. Our world is filled with warriors and an amount of strength. They will fight each other to the death.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Warrior{
    string name;
    int strength;
};

void readFile(ifstream& warrior, vector<Warrior>& warriors);
void addWarrior(const string& name, int strength, vector<Warrior>& warriors);
size_t position(const string& name, const vector<Warrior>& warriors);
void battle(const string& warriorOne, const string& warriorTwo, vector<Warrior>& warriors);
void status(const vector<Warrior>& warriors);

int main(){
    ifstream warrior("warriors.txt");
    vector<Warrior> warriors;
    readFile(warrior, warriors);
    warrior.close();
}

//This function displays the warriors with their corresponding name and strength
void status(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior& aWarrior : warriors){
        cout << "Warrior: " << aWarrior.name << ", strength: " << aWarrior.strength << endl;
    }
}

//This function locates a warrior in the vector
size_t position(const string& name, const vector<Warrior>& warriors){
    size_t index = 0;
    for (size_t i = 0; i < warriors.size(); i++){
        if (warriors[i].name == name){
            index = i;
            return index;
        }
    }
    return warriors.size();
}

//This function evaluates the battle between two warriors and acts accordingly
void battle(const string& warriorOne, const string& warriorTwo, vector<Warrior>& warriors){
    cout << warriorOne << " battles " << warriorTwo << endl;
    size_t posOne = position(warriorOne, warriors);
    size_t posTwo = position(warriorTwo, warriors);
    if (warriors[posOne].strength == warriors[posTwo].strength){
        if (warriors[posOne].strength != 0 && warriors[posTwo].strength != 0){
            warriors[posOne].strength = 0;
            warriors[posTwo].strength = 0;
            cout << "Mutual Annihilation: " << warriorOne << " and " << warriorTwo << " die at each other's hands" << endl;
        }
        else{
            cout << "Oh, No, They're both dead! Yuck!" << endl;
        }
    }
    else if (warriors[posOne].strength > warriors[posTwo].strength){
        if (warriors[posTwo].strength == 0){
            cout << "He's dead, " << warriorOne << endl;
        }
        else{
            warriors[posOne].strength -= warriors[posTwo].strength;
            warriors[posTwo].strength = 0;
            cout << warriorOne << " defeats " << warriorTwo << endl;
        }
    }
    else if (warriors[posTwo].strength > warriors[posOne].strength){
        if (warriors[posOne].strength == 0){
            cout << "He's dead, " << warriorTwo << endl;
        }
        else{
            warriors[posTwo].strength -= warriors[posOne].strength;
            warriors[posOne].strength = 0;
            cout << warriorOne << " defeats " << warriorTwo << endl;
        }
    }
}

//This function stores new warriors in a vector that hold name and strength
void addWarrior(const string& name, int strength, vector<Warrior>& warriors){
    Warrior warrior{name,strength};
    warriors.push_back(warrior);
}

//This function reads the first word of every line and acts accordingly
void readFile(ifstream& warrior, vector<Warrior>& warriors){
    if (!warrior){
        cerr << "could not open the file" << endl;
        exit(1);
    }
    string firstWord;
    while (warrior >> firstWord){
        if (firstWord == "Warrior"){
            string name;
            int strength;
            warrior >> name >> strength;
            addWarrior(name, strength, warriors);
        }
        else if (firstWord == "Battle"){
            string warriorOne;
            string warriorTwo;
            warrior >> warriorOne >> warriorTwo;
            battle(warriorOne, warriorTwo, warriors);
        }
        else{
            status(warriors);
        }
    }
}
