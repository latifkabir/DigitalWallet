// Filename: ReadData.cpp
// Description: 
// Author: Latiful Kabir < siplukabir@gmail.com >
// Created: Sat Nov  5 01:07:45 2016 (-0400)
// URL: latifkabir.github.io

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <unordered_map>
#include <queue>
#include <list>

std::unordered_map<int, std::set<int> > Map; // Map (Hash Table) for any sender and all of it's receiver.
std::unordered_map<int, int> Cache; // Cache for the level number.
std::unordered_map<int, bool> Visited; // Cache to check if already visited

void ExtendNetwork(int sender, int receiver); //Extend network for each payment from stream file that has been already checked regardless of warning
void CheckForMatch(int user, int receiver, int generation);
bool matchFound=false;
std:: list <int> V;

int main(int argc, char *argv[])
{

    if(argc != 2)
    {
	std::cout<<" Syntax: ./PayMo FEATURE"<<std::endl;
	return -1;
    }

    int feature = atoi(argv[1]);

    if(feature == 0)
    {
	std::cout<< " Please enter any feature between 1 to 3. Feature number greater than 3 will also work as the generation number."<<std::endl;
	return -1;
    }
    else if(feature>3)
	std::cout<<"------> Note : Feature number greater than 3 will be considered as the generation number. <-------"<<std::endl;
    
    int level;
    level = (feature == 3) ? 4 : feature;     
    
    //================Read the batch payment data file =======================
    std::fstream batchFile("./paymo_input/batch_payment.txt");
    if(!batchFile)
    {
	std::cout << "The input batchFile NOT found" <<std::endl;
	return -1;
    }
    std::string line;
    std::string value;

    int column;
    int sender_b;  // Sender form batch file
    int receiver_b; // Receiver from batch file

    getline(batchFile,line); // Skip the  first line
    
    while(getline(batchFile,line))
    {
	std::stringstream linestream(line);
	column=0;
	while(getline(linestream,value,','))
	{
	    ++column;
	    if(column == 2)
	    	sender_b = std::stoi(value);
	    if(column == 3)
	    	receiver_b=std::stoi(value);
	}
	ExtendNetwork(sender_b,receiver_b);
    }

    batchFile.close();
    
    //================Read the stream payment data file =======================
    std::fstream streamFile("./paymo_input/stream_payment.txt");
    if(!streamFile)
    {
	std::cout << "The input file streamFile NOT found" <<std::endl;
	return -1;
    }

    int sender_s;  // Sender form stream file
    int receiver_s; // Receiver from stream file
 
    getline(streamFile,line); // Skip the first line
    
    while(getline(streamFile,line))
    {
	matchFound=false;
	
	std::stringstream linestream(line);
	column=0;
	while(getline(linestream,value,','))
	{
	    ++column;
	    if(column == 2)
	    	sender_s = std::stoi(value);
	    if(column == 3)
	    	receiver_s = std::stoi(value);
	}
	
	//=================Implementation of the Features =========================

	//----------- All first time user with no friend at all --------------------
	if(Map.count(sender_s) == 0) 
	{
	    std::cout<<"unverified"<<std::endl;
	    ExtendNetwork(sender_s,receiver_s);
	    continue;
	}

	//-----------------------Faster Approach using recursion ---------------------------
	std::list<int>::iterator it;
	for(it=V.begin();it!=V.end();++it)
	{
	    Cache[*it]=1;
	    Visited[*it]=false;
	}
	V.clear();
	
	CheckForMatch(sender_s,receiver_s,level);
	if(matchFound)
	    std::cout<<"trusted"<<std::endl;
	else
	    std::cout<<"unverified"<<std::endl;
	ExtendNetwork(sender_s,receiver_s);		
    }

    streamFile.close();
    
    return 0;
}

//============ Extend user network adding each payment from stream file that has been already checked regardless of warning ===========
void ExtendNetwork(int sender, int receiver)
{
    Map[sender].insert(receiver);
    Map[receiver].insert(sender); //We need to add both sender & receiver for undirected graph
    Cache[sender] = 1;
    Cache[receiver] = 1;
    Visited[sender] = false;
    Visited[receiver] = false;
}


void CheckForMatch(int user, int receiver, int generation)
{
    Visited[user]=true;
    V.push_back(user);
    
    if(Cache[user]>generation)
    {
	return;
    }

    if(Map[user].count(receiver))
    {
	matchFound=true;
	return;
    }
	
    std::set<int>::iterator it;	
    for(it = Map[user].begin(); it != Map[user].end(); ++it)
    {
	if(!Visited[*it])
	{
	    Cache[*it]=Cache[user]+1;	
	    CheckForMatch(*it,receiver,generation);
	}
    }	       
}
