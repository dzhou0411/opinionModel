using namespace std;
#include <iomanip>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <list>
#include <string>

#include "node.hpp"
#include "graph.hpp"
#include "net_algo.hpp"
//#include "net_ops.hpp"

int main() {

initsrand(1);


string fileout;

int num_pars=10000;
//double f0=0.6;
double convince=1;

double p_create=0.001;
double p_link=0.3;
//double p_leave=0.7;//
//double tolerance=1.0-p_leave;  // 

int realizations=100;



int sim_step=500;

//double ffinal[sim_step];
//double roomavgop[sim_step];

 
// fout.open("./10result.dat");


// f1out.open("./10forum.dat");

//Graph net;
//net.resize_people(num_pars);
//initiate(net,f0,convince);

//cout << net.people_positive_f()<<endl;
//initiate_dyn(net, p_link,p_create, pref_attachment_list);
//cout << net.people_positive_f()<<endl;
//for (int i=0;i<num_pars;i++){ cout<<"op "<<net.opinion_people(i)<<"conv "<<net.convince_ppl(i)<<endl;}

//net_dynamic_ini(net,p_link, p_create);

for(

for(double p_leave=0.1;p_leave<=0.9;p_leave=p_leave+0.1){cout<<"p_leave is "<<p_leave<<endl;                    //each p_leave start
double ffinal[500]={0.};
int    forumdegree[500]={0};
double roomavgop[500]={0.};
stringstream sspleave;
sspleave<<p_leave;
fileout="./dataoutput/ffinalrevVSsimstepPleave"+sspleave.str()+"r100.dat";
ofstream fout;
fout.open(fileout.c_str());
cout<<"doing "<<fileout<<endl;
for(int r=0;r<realizations;r++){cout<<"realization # "<<r<<endl;							// each realization start
Graph net;
net.resize_people(num_pars);
initiate(net,f0,convince);
for (int step=0;step<sim_step;step++) {//cout << " step is " << step << endl;
	net_dynamic(net,p_link,p_create,1.-p_leave);
	ffinal[step]=ffinal[step]+net.people_positive_f();	                             // +opinion percentige
        //forumdegree[step]=forumdegree[step]+net.total_forum_degree();                      // total forum degree
        //  roomavgop[step]=roomavgop[step]+net.forum_avg_opinion();                         // chatroom's average opinion

 //      roomavgop[step][p_leaveint-1]=roomavgop[step][p_leaveint-1]+net.forum_avg_opinion();		
  //      fout << step << "  " << net.people_positive_f()<<endl;
//cout<<"op of forum#1 is" << net.opinion_forum(1)<<" ; degree is " << net.get_deg_forum(1)<<endl; 
					}


}//each real end
for (int step=0;step<sim_step;step++){
                  ffinal[step]=ffinal[step]/double(realizations);                        // +opinion percentage
                  // forumdegree[step]=forumdegree[step]/realizations;                   // total forum degree
                  //roomavgop[step]=roomavgop[step]/double(realizations);                // chatroom average opinion
                        }

for (int step=0;step<sim_step;step++){ 
	fout<< step<<"  "<<ffinal[step] << endl;                                         // +opinion percentage
        //  fout<< step<<"  "<<forumdegree[step] << endl;                                // total forum degree
        //   fout<<step<<"  "<<roomavgop[step]<<endl;                                    // chatroom average opinion
    }                  
/*
for (int step=0;step<sim_step;step++){ f1out<< step <<"  ";
	for (int j=0;j<10;j++){f1out<< roomavgop[step][j] <<"  ";}
        f1out<<endl;
                        } 		
*/
}//each p_leave end


} //main end
