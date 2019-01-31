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
#include <unordered_set>
#include <set>
#include <utility>
#include <limits>


class User;
class Event;
class UserEventBase;
class Util;
class MarginalGainHeap;
class MarginalGain;

class Process{
private:
	std::vector<User> users;
	std::vector<Event> events;

	int num_users; // Initiated as -1
	int num_events; // Initiated as -1

	std::vector<std::vector<double> > distance_user_event;
	std::vector<std::vector<double> > distance_user_event_normalized;
	std::vector<std::vector<double> > similarity_user_event;
	std::vector<std::vector<double> > similarity_user_event_normalized;
	std::vector<std::vector<double> > weight_user_user; // user has weight 0 with himself
	std::vector<std::vector<double> > utility_user_event; // utility matrix is calculated only when useful, that is to say, when algorithm is implemented
	std::vector<std::list<int> > graph_users;
	std::set<std::pair<int, int> > conflict_events; // only <A, B> exist without <B, A>

	std::vector<int> users_arrival;

	std::vector<int> user_affinities; // which event each user participate in, 1 user -> 1 event
	std::vector<std::set<int> > event_users; // which users each event has/matched, 1 event -> many users
	std::vector<std::set<int> > user_events; // which events each user matched, 1 user -> many events
	double cut_cost;
	double clique_cost;

public:
	Process();
	~Process();

	// read data
	bool read_attr_file(std::string filename);
	bool read_user_pos_file(std::string filename); // must be used after read_attr_file is used
	bool read_event_pos_file(std::string filename); // must be used after read_attr_file is used
	bool read_user_capacity_file(std::string filename); // must be used after read_attr_file is used
	bool read_event_capacity_file(std::string filename); // must be used after read_attr_file is used
	bool read_conflict_events_file(std::string filename);

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
	bool write_match_result(std::string filename);
	bool write_assignment_costs(std::string filename);
	bool write_assignment_costs(std::string filename, std::string type);
	bool write_arrival_sequence(std::string filename);


	// assignment algorithm implementation
	void calc_assignments_clique_offline();
	void calc_assignments_cut_offline();
	void calc_assignments_exhaustive_offline(const std::string & kind, const double & alpha, const double & beta, const double & gamma);
	void calc_assignments_clique_online();
	void calc_assignments_cut_online();

	// matching algorithm implementation
	void calc_matches_online_greedy(double alpha);
	void calc_matches_onlineF_greedy(double alpha);

	// calculate assignment cost
	double calc_cut_cost(double alpha, double beta, double gamma);
	double calc_clique_cost(double alpha, double beta, double gamma);

private:
	// 初始化空分配assignment
	void initialize_null_assignments();
	// 初始化空匹配match
	void initialize_null_matches();

	// 分配某个用户去某个活动; 该用户必须尚未分配、且活动尚未人满i，否则返回false
	bool assign_trial(int user, int event);
//	bool change_assignment(int user, int event);
	// 匹配某个用户和某个活动，已经过函数check_match_condition确认两者匹配的可行性
	void match(int user, int event);

	// 读文件并做相应操作
	int parse_preprocess_version(std::string line);//根据首行内容判断预处理文件的版本
	void read_user_event_count(std::ifstream &ifs);//读人数、活动数
	void read_user_event_count(std::string &line);//读人数、活动数
	void read_event_attributes(std::ifstream &ifs);//读活动属性
	void read_user_attributes(std::ifstream &ifs);//读用户属性
	void read_user_positions(std::ifstream &ifs);//读用户位置
	void read_event_positions(std::ifstream &ifs);//读活动位置
	void read_user_capacities(std::ifstream &ifs);//读用户的容量
	void read_user_capacities(std::ifstream &ifs, const std::string &firstline);//读用户的容量
	void read_event_capacities(std::ifstream &ifs);//读活动的容量
	void read_event_capacities(std::ifstream &ifs, const std::string &firstline);//读活动的容量
	void read_distance_matrix(std::ifstream &ifs);//读人与活动的距离
	void read_normalized_distance_matrix(std::ifstream &ifs);//读人与活动的距离
	void read_similarity_matrix(std::ifstream &ifs);//读人与活动的相似度
	void read_normalized_similarity_matrix(std::ifstream &ifs);//读人与活动的相似度
	std::string read_weight_matrix(std::ifstream &ifs);//读人与人之间的权重（网络），然后返回下一行
	void read_conflict_events(std::ifstream &ifs);//读冲突的活动清单

	double calc_marginal_gain_offline_clique(int user_index, int event_index);
	double calc_marginal_gain_offline_cut(int user_index, int event_index);
	double calc_marginal_gain_online_clique(int user_index, int event_index);
	double calc_marginal_gain_online_clique(int user_index, int neighbor_index, int event_index);
	double calc_marginal_gain_online_cut(int user_index, int event_index);
	double calc_marginal_gain_online_cut(int user_index, int neighbor_index, int event_index);
	double calc_utility(int user_index, int event_index, double alpha);
	// about network
	void create_graph_users();

	// calculations of preprocess
	double calc_distance_user_event(User & u, Event & e);
	double calc_similarity_user_event(User & u, Event & e);
	double calc_weight_user_user(User & u1, User & u2);

	void calc_distance_matrix();
	void calc_normalized_distance_matrix();
	void calc_similarity_matrix();
	void calc_normalized_similarity_matrix();
	void calc_weight_matrix();
	void calc_utility_matrix(double alpha); // this matrix is calculated only when useful

	bool initialize_exhaustive_first_feasible_assignments();
	bool find_exhaustive_next_feasible_assignments();
	
	// 检查当前的分配是否符合要求
	bool check_assignments_feasible();

	// 检查是否可以match用户u和活动v
	// 需要考虑用户和活动的capacity，以及同一用户所参加活动之间的冲突
	bool check_match_condition(int user, int event);

	// 检查两个活动是否有冲突，有则返回true，无冲突则返回false
	bool check_conflict(int event1, int event2);

};


#endif
