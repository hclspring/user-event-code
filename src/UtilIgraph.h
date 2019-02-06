#ifndef _UTIL_IGRAPH_H_
#define _UTIL_IGRAPH_H_

#include <vector>
#include <set>
#include <cassert>
#include <iostream>

#include <igraph.h>

class User;
class Event;

class UtilIgraph {
public:
	static void calc_temporary_match_with_maxflow_and_pushrelabel(
			const std::vector<User> & users, 
			const std::vector<Event> & events,
			const std::vector<std::set<int> > & same_area_users,
			const std::vector<std::set<int> > & same_area_events,
			std::vector<std::set<int> > & user_events);

private:
	// 最大流图结构节点id与用户、活动id互相转换
	static int get_user_id(int igraph_vertex, int num_events, int num_users);
	static int get_event_id(int igraph_vertex, int num_events);
	static int get_igraph_vertex_from_user(int user_id, int num_users, int num_events);
	static int get_igraph_vertex_from_event(int event_id, int num_events);

	// 最大流图结构边id与起点终点的相互转换
	static int get_left_edge_count(int num_events); // source -> events
	static int get_mid_edge_count(const std::vector<std::set<int> > & same_area_users, const std::vector<std::set<int> > & same_area_events); // events -> users
	static int get_right_edge_count(int num_users); // users -> target

	// 构造igraph图模型
	static void create_graph(int num_events, int num_users, 
			int num_areas, int num_edges, 
			const std::vector<User> & users, 
			const std::vector<Event> & events,

			const std::vector<std::set<int> > & same_area_events,
			const std::vector<std::set<int> > & same_area_users,
			igraph_t * g);
	static void init_edge_capacities(int num_events, int num_users, 
			int num_edges, int num_mid_edges,
			const std::vector<User> & users,
			const std::vector<Event> & events,
			igraph_vector_t & capacity);
};

#endif
