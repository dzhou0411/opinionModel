#ifndef NET_OPS_HPP
#define NET_OPS_HPP
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include "./statool/srand.hpp"

//--------------------------------------
//1. Initiate
//Set up the graph; Give the ppl original opinion;
//First round of building forums.
//  *p_b probability of building a forum
//  *initially f0 fraction people have + opinion
//  *c percentage of ppl are convincing
//--------------------------------------
void initiate(Graph &net,double f0,double c){
  int num_ppl=net.size_people();
  net.resize_people(num_ppl);  
  for(int i=0;i<num_ppl;++i){
    if(srand()<f0)
      net.set_people_opin(i,1);
    else
      net.set_people_opin(i,-1);    
    if(srand()<c)
      net.set_convince(i,1);
  }
}


/*
void initiate_dyn(Graph &net, double p_a,double p_b, vector<int> & pref_list) {
	int num_ppl=net.size_people();
        
// the first (no. 0) people must build a forum
        net.build_a_forum(0);
        pref_list.push_back(net.size_forum()-1);
//start from the second (no.1) people, do creat-link dynamic. when link, use preferrential attachment
        for(int i=1;i<num_ppl;++i) {//cout<<"now ini no. " << i<<endl;
    //1-------------------------------------------
        if(srand()<p_b) { //cout<<" now build" << endl;
		net.build_a_forum(i);
		pref_list.push_back(net.size_forum()-1);
                                    }
    //2----------------------------------------------        
	if(srand()<p_a) {int b;	//cout<<" now add" << endl;	                
		do {b=srand()*pref_list.size();}
                while (net.connection_check(i,pref_list[b])==true); //cout << "link chosen"<<i<<" "<<b<<endl;
		net.insert_connection(i,pref_list[b]);//cout << " done insert"<<endl;
                pref_list.push_back(pref_list[b]); //cout << " done pref_list add"<<endl;
                                     }    
                                    }// for end
                                                                          }


*/


void net_dynamic(Graph &net,double p_a,double p_b,double t) {

	int num_ppl=net.size_people();int counter=0;
        double mm;
  	int nn;
  	int upper,lower;
  	bool mark;
        

       
	//1---build----------------------------------
	 for(int i=0;i<num_ppl;++i){                if (net.get_deg_people(i)<10){
		if(srand()<p_b) {
			net.build_a_forum(i);
                                            }}                                     }
        //cout<<"finished 1-build"<<endl;
        //2, add a forum, preferential method
    	 int num_forum=net.size_forum();
    	 vector<double> v(num_forum+1,0);
    	 for(int i=0;i<num_forum;++i)
      		v[i+1]=v[i]+net.get_deg_forum(i);
    	 for(int i=0;i<num_ppl;++i)                                      if (net.get_deg_people(i)<10){
      		if(rand()%10000/10000.<p_a){                                      
			mark=true;
			while(mark){
	  			mm=v[num_forum]*(rand()%10000/10000.);
	  			upper=num_forum+1;
	  			lower=0;
	  			while(upper-lower>1){
	    				nn=int((upper+lower)/2);
	    				if(v[nn]>mm)
	      					upper=nn;
	    				else
	      					lower=nn;
	  					    }// while(upper-lower>1 end)
	  			if(!net.connection_check(i,lower)){
	    				mark=false;
	    				net.insert_connection(i,lower);
	  							  }// this if end	
				     }// while marke=true end
													}
     					  }// for each people end                                      
                                                                                                       
        //5---update forum's opinion-------------
        for(int i=0;i<net.size_forum();++i)
      		net.update_forum(i);


        //3---leave a forum-----------------------------------
	 for(int i=0;i<num_ppl;++i){
                net.ppl_leave_forums(i,t);}
        //4---update people's opinion------------
	 for(int i=0;i<num_ppl;++i){
                net.update_people(i);}        
        
                                                                               }



void net_dynamic_ini(Graph &net,double p_a,double p_b, double t) {

	int num_ppl=net.size_people();int counter=0;
        double mm;
  	int nn;
  	int upper,lower;
  	bool mark;

       
	//1---build----------------------------------
	 for(int i=0;i<num_ppl;++i){                
		if(srand()<p_b ) {
			net.build_a_forum(i);
                                            }}                                     
        //cout<<"finished 1-build"<<endl;
        //2, add a forum, preferential method
    	 int num_forum=net.size_forum();
    	 vector<double> v(num_forum+1,0);
    	 for(int i=0;i<num_forum;++i)
      		v[i+1]=v[i]+net.get_deg_forum(i);
    	 for(int i=0;i<num_ppl;++i)                                      
      		if(srand()<p_a){                                      
			mark=true;
			while(mark){
	  			mm=v[num_forum]*(rand()%10000/10000.);
	  			upper=num_forum+1;
	  			lower=0;
	  			while(upper-lower>1){
	    				nn=int((upper+lower)/2);
	    				if(v[nn]>mm)
	      					upper=nn;
	    				else
	      					lower=nn;
	  					    }// while(upper-lower>1 end)
	  			if(!net.connection_check(i,lower)){
	    				mark=false;
	    				net.insert_connection(i,lower);
	  							  }// this if end	
				     }// while marke=true end
													
     					  }// for each people end                                      
                                                                                                       
        // check each room
	for (int i=0;i<net.size_forum();i++){cout<<"in room# "<<i<<" , +people "<<net.num_posi_people_in_forum(i)<<"("<<net.num_pos_people_in_forum_c(i)<<")"<<"  "<<", -people "<<net.num_nega_people_in_forum(i)<<"("<<net.num_neg_people_in_forum_c(i)<<")"<<" , room op is "<<net.opinion_forum(i)<<endl;}

//3---leave a forum-----------------------------------
	 for(int i=0;i<num_ppl;++i){
                net.ppl_leave_forums(i,t);}

        //4---update people's opinion------------
	 for(int i=0;i<num_ppl;++i){
                net.update_people(i);}        
        //5---update forum's opinion-------------
        for(int i=0;i<net.size_forum();++i)
      		net.update_forum(i);
                                                                               }


#endif
