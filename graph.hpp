#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <list>
#include <queue>
#include "./statool/srand.hpp"
#include "node.hpp"
#include <cmath>


class Graph {
protected:

  vector<People> people;
  vector<Forum> forum;

public:
  int get_deg_people(int index);
  int get_deg_forum(int index);
  int size_people();//num of ppl
  int size_people_effective();
  int size_forum();//num of forums
  int size_forum_effective();
  int total_forum_degree();
  double people_positive_f();
  double forum_positive_f();
  int opinion_people(int index);
  double opinion_forum(int index);
  int convince_ppl(int index);
  int ppl_leave_forums(int index, double t);
  void set_convince(int index,int d);
  bool connection_check(int ppl,int frm);
  void insert_connection(int ppl,int frm);
  void set_people_opin(int index,int opin);
  void update_people(int index);
  void update_forum(int index);
  void resize_people(int size);
  void build_a_forum(int ppl);// which ppl build this forum
  int num_posi_people_in_forum(int index);
  int num_nega_people_in_forum(int index);
  int num_pos_people_in_forum_c(int index);
  int num_neg_people_in_forum_c(int index);
  double forum_avg_opinion();
  void clear(){people.clear();forum.clear();}  
  Graph(){
  }
};

int Graph::get_deg_people(int index){
  return people[index].degree();
}
//---------------------------------------
int Graph::get_deg_forum(int index){
  return forum[index].degree();
}
//--------------------------------------
int Graph::size_people(){ return people.size();}
int Graph::size_forum(){return forum.size();}
int Graph::size_people_effective(){
  int num=0;
  for(int i=0;i<people.size();++i)
    if(!people[i].degree())
      num++;
  return num;
}
int Graph::size_forum_effective(){
  int num=0;
  for(int i=0;i<forum.size();++i)
    if(forum[i].degree())
      num++;
  return num;
}
//-------------------------------------
int Graph::total_forum_degree(){
int total_num_degree=0;
  for (int i=0;i<forum.size();i++) total_num_degree+=forum[i].degree();
  return total_num_degree;
}
//------------------------------------
double Graph::people_positive_f(){
  double count=0;
  for(int i=0;i<people.size();++i)
    if(people[i].opinion()>0)
      count++;
  return count/double(people.size());
}
//------------------------------------
double Graph::forum_positive_f(){
  double count=0;
  for(int i=0;i<forum.size();++i)
    if(get_deg_forum(i) && forum[i].opinion()>0)
      count++;
  return count/double(size_forum_effective());
}
//------------------------------------
int Graph::opinion_people(int index){
  return people[index].opinion();
}
double Graph::opinion_forum(int index){
  return forum[index].opinion();
}
//-------------------------------------
int Graph::convince_ppl(int index){
  return people[index].convince();
}
//-------------------------------------
//-------------------------------------
int Graph::ppl_leave_forums(int index, double t){
  list<int>::iterator it2=people[index].forum_end();
  vector<int>::iterator pref_it;
  for(list<int>::iterator it=people[index].forum_begin();it!=it2;++it){
    //cout<<"num of forums connected:"<<people[index].degree()<<endl;
    if(opinion_forum(*it)*opinion_people(index)<0 && srand()<(1.-t)*abs(opinion_forum(*it))){
      people[index].rm_a_forum(*it);
      //cout<<"remove2"<<endl;
      forum[*it].rm_a_people(index);
      //cout<<"remove2"<<endl;
      it--;
      it2=people[index].forum_end();      	
    }// if end
  }// check each opp end
}// leave function end
//----------------------------------------
void Graph::set_convince(int index,int d){
  people[index].set_convince(d);
}
//-------------------------------------
//-------------------------------------
bool Graph::connection_check(int ppl, int frm){
  for(list<int>::iterator it=people[ppl].forum_begin();      it!=people[ppl].forum_end();it++)
    if(*it==frm)
      return true;
  return false;
}
//-------------------------------------
void Graph::insert_connection(int ppl, int frm){
  people[ppl].add_a_forum(frm); //cout << " done ins p+f"<<endl;
  forum[frm].add_a_people(ppl); //........cout << " done ins f+p"<<endl;
}
//--------------------------------------
void Graph::set_people_opin(int index,int opin){
  people[index].update(opin);
}
void Graph::update_people(int index){
  double opinion=double(opinion_people(index));
  for(list<int>::iterator it=people[index].forum_begin();it!=people[index].forum_end();++it)
    opinion+=opinion_forum(*it);
  if(opinion>0)
    people[index].update(1);
  else if(opinion<0)
    people[index].update(-1);
}
void Graph::update_forum(int index){
//if (forum[index].degree()!=0) {  
  int opinion=0;
  for(list<int>::iterator it=forum[index].people_begin();it!=forum[index].people_end();++it)
    {//cout<<"op "<<opinion_people(*it) << "  c is " <<people[*it].convince()<<endl;
     opinion = opinion+opinion_people(*it)*people[*it].convince();}//cout<<"op bf nor "<<opinion<<" and deg is "<<forum[index].degree()<<endl;
  double op=double(opinion)/double(forum[index].degree());//cout<<"op aft nor "<<op<<endl;
  forum[index].update(op); 

/*
  if(opinion>0)
    forum[index].update(+1);
  else if(opinion<0)
    forum[index].update(-1);  
*/
}
//-------------------------------------
void Graph::resize_people(int size){
  people.clear();
  people.resize(size);
}
//------------------------------------------------
//Build a forum, connect the forum with its builder.
//set the forum's opinion as the builder's opinion.
//------------------------------------------------
void Graph::build_a_forum(int ppl){
  Forum m;
  m.add_a_people(ppl);
  m.update(double(people[ppl].opinion()));
  forum.push_back(m);
  people[ppl].add_a_forum(forum.size()-1);
}  


int Graph::num_posi_people_in_forum(int index){int counterposipeople=0;
	for(list<int>::iterator it=forum[index].people_begin();it!=forum[index].people_end();++it){if (opinion_people(*it)==1) counterposipeople+=1;}
        return counterposipeople;             }

int Graph::num_nega_people_in_forum(int index){int counternegapeople=0;
	for(list<int>::iterator it=forum[index].people_begin();it!=forum[index].people_end();it++){if (opinion_people(*it)==-1) counternegapeople+=1;}
        return counternegapeople;             }
                                    
int Graph::num_pos_people_in_forum_c(int index){int counterposipeople=0;
	for(list<int>::iterator it=forum[index].people_begin();it!=forum[index].people_end();++it){if (opinion_people(*it)==1 && convince_ppl(*it)==1) counterposipeople+=1;}
        return counterposipeople;             }

int Graph::num_neg_people_in_forum_c(int index){int counternegapeople=0;
	for(list<int>::iterator it=forum[index].people_begin();it!=forum[index].people_end();it++){if (opinion_people(*it)==-1 && convince_ppl(*it)==1)counternegapeople+=1;}
        return counternegapeople;             }   

double Graph::forum_avg_opinion(){double room_op=0.;
	for(int i=0;i<forum.size();i++){room_op=room_op+forum[i].opinion();}
        room_op=room_op/double(forum.size());
        return room_op;
}
#endif
