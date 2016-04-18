#ifndef _PROCESS_H_
#define _PROCESS_H_

#define MAX 999999999

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <cassert>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cfloat>

#include "User.h"
#include "Event.h"
#include "Util.h"
#include "MarginalGainHeap.h"

class Process{
private:
	std::vector<User> users;
	std::vector<Event> events;

	int num_users; // Initiated as -1
	int num_events; // Initiated as -1

	std::vector<std::vector<double> > distance_user_event;
	std::vector<std::vector<double> > similarity_user_event;
	std::vector<std::vector<double> > weight_user_user; // user has weight 0 with himself
	std::vector<std::list<int> > graph_users;

	std::vector<int> users_arrival;

	std::vector<int> user_affinities; // which event each user participate in
	std::vector<std::set<int> > event_users; // which users each event has
	double cut_cost;
	double clique_cost;

	Util util;

public:
	Process();
	~Process();

	// read data
	bool read_attr_file(std::string filename);
	bool read_user_pos_file(std::string filename); // must be used after read_attr_file is used
	bool read_event_pos_file(std::string filename); // must be used after read_attr_file is used
	bool read_event_capacity_file(std::string filename); // must be used after read_attr_file is used

	bool read_preprocessed_data(std::string filename);
	bool read_users_arrival(std::string filename);
	
	bool read_assignment_data(std::string filename);

	// generate random online arrivals
	void gen_rand_arrival();
	// calculate input content (three matrices: distance, similarity, weight)
	void calc_input_content();

	// write data
	bool write_preprocessed_data(std::string filename);
	bool write_assignment_result(std::string filename);
	bool write_assignment_costs(std::string filename);
	bool write_assignment_costs(std::string filename, std::string type);
	bool write_arrival_sequence(std::string filename);


	// assignment algorithm implementation
	void calc_assignments_clique_offline();
	void calc_assignments_cut_offline();
	void calc_assignments_exhaustive_offline(const std::string & kind, const double & alpha, const double & beta, const double & gamma);
	void calc_assignments_clique_online();
	void calc_assignments_cut_online();

	// calculate assignment cost
	double calc_cut_cost(double alpha, double beta, double gamma);
	double calc_clique_cost(double alpha, double beta, double gamma);

private:
	// 初始化空分配
	void initialize_null_assignments();
	// 分配某个用户去某个活动; 该用户必须尚未分配、且活动尚未人满i，否则返回false
	bool assign(int user, int event);
//	bool change_assignment(int user, int event);

	// 读文件并做相应操作
	void read_user_event_count(std::ifstream &ifs);//读人数、活动数
	void read_event_attributes(std::ifstream &ifs);//读活动属性
	void read_user_attributes(std::ifstream &ifs);//读用户属性
	void read_user_positions(std::ifstream &ifs);//读用户位置
	void read_event_positions(std::ifstream &ifs);//读活动位置
	void read_event_capacities(std::ifstream &ifs);//读活动的容量
	void read_event_capacities(std::ifstream &ifs, const std::string &firstline);//读活动的容量
	void read_distance_matrix(std::ifstream &ifs);//读人与活动的距离
	void read_similarity_matrix(std::ifstream &ifs);//读人与活动的距离
	std::string read_weight_matrix(std::ifstream &ifs);//读人与人之间的权重（网络），然后返回下一行

	double calc_marginal_gain_offline_clique(int user_index, int event_index);
	double calc_marginal_gain_offline_cut(int user_index, int event_index);
	double calc_marginal_gain_online_clique(int user_index, int event_index);
	double calc_marginal_gain_online_clique(int user_index, int neighbor_index, int event_index);
	double calc_marginal_gain_online_cut(int user_index, int event_index);
	double calc_marginal_gain_online_cut(int user_index, int neighbor_index, int event_index);
	// about network
	void create_graph_users();

	// calculations of preprocess
	double calc_distance_user_event(User & u, Event & e);
	double calc_similarity_user_event(User & u, Event & e);
	double calc_weight_user_user(User & u1, User & u2);

	void calc_distance_matrix();
	void calc_similarity_matrix();
	void calc_weight_matrix();

	bool initialize_exhaustive_first_feasible_assignments();
	bool find_exhaustive_next_feasible_assignments();
	
	// 检查当前的分配是否符合要求
	bool check_assignments_feasible();

};


#endif
