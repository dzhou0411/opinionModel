#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>

class People {
protected:
  list<int> forum;
  int opin;
  double p;//prob to build a new forum
  double p1;//prob to visit a new forum
  double t;//tolerance, prob to stay if ppl's opinion differs from a forum's opinion.
  int c;//1:his opinion matters; 0: doesn't matter

public:
  int opinion();
  void add_a_forum(int index);
  void rm_a_forum(int index);
  void rm_all_forums();
  int degree();//num of forums
  int convince();
  void set_convince(int d);
  void update(int o);//update opinion
  typedef list<int>::iterator forum_iterator;
  forum_iterator forum_begin() { return forum.begin(); }
  forum_iterator forum_end() { return forum.end(); }
  People() {
    p=0;p1=0;t=0;c=0;opin=0;
  }
};

class Forum {
protected:
  list<int> people;
  double opin; 
public:
  double opinion();
  void add_a_people(int index);
  void rm_a_people(int index);
  void rm_all_people();
  int degree();//num of people
  void update(double );//update the forum's opinion
  typedef list<int>::iterator people_iterator;
  people_iterator people_begin() { return people.begin(); }
  people_iterator people_end() { return people.end(); }
  Forum(){
    opin=0;
  }
};
//--------------------------------------
int People::opinion(){
  return opin;
}
//--------------------------------------
void People::add_a_forum(int index) {
  forum.push_back(index);
}
//---------------------------------------
void People::rm_a_forum(int index){
  forum_iterator it;
  for(it=forum_begin();it!=forum_end();++it){
    if(*it==index){
      break;
    }
  }
  if(it!=forum_end()){
    forum.erase (it);
  }
  else{
    cerr<<"don't have such forum!"<<endl;
    exit(1);
  }
}

//---------------------------------------
void People::rm_all_forums(){
  forum.clear();
  return;
}

//---------------------------------------
int People::degree() { return forum.size(); }
//---------------------------------------
void People::update(int a){ opin=a; }
//---------------------------------------
int People::convince(){return c;}
//--------------------------------------
void People::set_convince(int d){c=d;}
//--------------------------------------
double Forum::opinion(){
  return opin;
}
//---------------------------------------
void Forum::add_a_people(int index){
  people.push_back(index);
}
//---------------------------------------
void Forum::rm_a_people(int index){
  list<int>::iterator it;
  for(it=people.begin();it!=people.end();++it){
    if(*it==index)
      break;
  }  
  if(it!=people.end()){
    people.erase(it);
  }
  else{
    cerr<<"don't have such a people!"<<endl;
    exit(1);
  }
}
//--------------------------------------
void Forum::rm_all_people(){
  people.clear();
}
//--------------------------------------
int Forum::degree(){ return people.size();}
//--------------------------------------
void Forum::update(double a){opin=a;}

#endif
