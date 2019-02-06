#include "UtilIgraph.h"

#include <igraph.h>

#include "User.h"
#include "Event.h"

using namespace std;

void UtilIgraph::calc_temporary_match_with_maxflow_and_pushrelabel(
			const std::vector<User> & users, 
			const std::vector<Event> & events,
			const std::vector<std::set<int> > & same_area_users,
			const std::vector<std::set<int> > & same_area_events,
			std::vector<std::set<int> > & user_events) {
	// calculate some important values
	int num_users = users.size();
	int num_events = events.size();
	int left_edge_count = get_left_edge_count(num_events);
	int mid_edge_count = get_mid_edge_count(same_area_users, same_area_events);
	int right_edge_count = get_right_edge_count(num_users);
	int num_edges = left_edge_count + mid_edge_count + right_edge_count;
	int num_areas = same_area_users.size();

	// create a graph as source[0] -> events[1..v] -> users[v+1..v+u] -> sink[v+u+1]
	igraph_t g;
	//create_graph(num_events, num_users, num_areas, num_edges, same_area_events, same_area_users, &g);
	create_graph(num_events, num_users, num_areas, num_edges, users, events, same_area_events, same_area_users, &g);
	// initialize igraph maxflow api parameters
	igraph_real_t maxflow_value;
	igraph_vector_t flow, capacity;
	igraph_vector_init(&flow, num_edges);
	// initialize igraph capacity values
	init_edge_capacities(num_events, num_users, num_edges, mid_edge_count, users, events, capacity);
	igraph_maxflow_stats_t stats;
	igraph_integer_t source = 0, target = num_events + num_users + 1;
	// run igraph maxflow api, results are maxflow_value and flow
	int error_code = igraph_maxflow(&g, &maxflow_value, &flow, NULL, NULL, NULL, source, target, &capacity, &stats);
	// add event to user's candidate set if the flow through the edge > 0
	assert(igraph_vector_size(&flow) == num_edges);
	user_events.clear();
	user_events.resize(num_users);
	for (int edge_id = 0; edge_id < num_edges; ++edge_id) {
		if (VECTOR(flow)[edge_id] > 0.0001) {
			igraph_integer_t from, to;
			igraph_edge(&g, edge_id, &from, &to);
			if (from > 0 && from <= num_events && to > num_events && to <= num_events + num_users) {
				int event_id = get_event_id(from, num_events);
				int user_id = get_user_id(to, num_events, num_users);
				user_events[user_id].insert(event_id);
			}
		}
	}
	igraph_vector_destroy(&flow);
	igraph_vector_destroy(&capacity);
	igraph_destroy(&g);
}


int UtilIgraph::get_user_id(int igraph_vertex, int num_events, int num_users) {
	assert(igraph_vertex > num_events && igraph_vertex < num_events + num_users + 1);
	return igraph_vertex - num_events - 1;
}

int UtilIgraph::get_event_id(int igraph_vertex, int num_events) {
	assert(igraph_vertex > 0 && igraph_vertex < num_events + 1);
	return igraph_vertex - 1;
}

int UtilIgraph::get_igraph_vertex_from_user(int user_id, int num_users, int num_events) {
	assert(user_id >= 0 && user_id < num_users);
	return num_events + user_id + 1;
}

int UtilIgraph::get_igraph_vertex_from_event(int event_id, int num_events) {
	assert(event_id >= 0 && event_id < num_events);
	return event_id + 1;
}

int UtilIgraph::get_left_edge_count(int num_events) {
	// source -> events
	return num_events;
}

int UtilIgraph::get_mid_edge_count(const std::vector<std::set<int> > & same_area_users, const std::vector<std::set<int> > & same_area_events) {
	// events -> users
	assert(same_area_users.size() == same_area_events.size());
	int num_areas = same_area_events.size();
	int num_edges = 0;
	for (int area = 0; area < num_areas; ++area) {
		int num_events_this_area = same_area_events[area].size();
		int num_users_this_area = same_area_users[area].size();
		num_edges += num_events_this_area * num_users_this_area;
	}
	return num_edges;
}

int UtilIgraph::get_right_edge_count(int num_users) {
	// users -> target
	return num_users;
}

void UtilIgraph::create_graph(int num_events, int num_users, 
			int num_areas, int num_edges, 
			const std::vector<User> & users, 
			const std::vector<Event> & events,

			const std::vector<std::set<int> > & same_area_events,
			const std::vector<std::set<int> > & same_area_users,
			igraph_t * g) {
	igraph_vector_t edges;
	igraph_vector_init(&edges, 2 * num_edges);
	for (int i = 0; i < num_events; ++i) {
		VECTOR(edges)[2*i] = 0; // 始端source
		VECTOR(edges)[2*i+1] = get_igraph_vertex_from_event(i, num_events); // 末端event
	} // 2*num_events个元素
	int vector_edges_count = 2 * num_events;
	for (int area = 0; area < num_areas; ++area) {
		// will add num_events_this_area * num_users_this_area edges
		for (set<int>::iterator it = same_area_events[area].begin(); it != same_area_events[area].end(); ++it) {
			int event = *it;
			for (set<int>::iterator jt = same_area_users[area].begin(); jt != same_area_users[area].end(); ++jt) {
				int user = *jt;
				VECTOR(edges)[vector_edges_count] = get_igraph_vertex_from_event(event, num_events);
				VECTOR(edges)[vector_edges_count + 1] = get_igraph_vertex_from_user(user, num_users, num_events);
				vector_edges_count += 2;
			}
		}
	}
	for (int i = 0; i < num_users; ++i) {
		VECTOR(edges)[vector_edges_count + 2*i] = get_igraph_vertex_from_user(i, num_users, num_events);
		VECTOR(edges)[vector_edges_count + 2*i + 1] = num_events + num_users + 1;
	} // 2*num_users个元素
	// construct the graph
	igraph_create(g, &edges, num_users + num_events + 2, IGRAPH_DIRECTED);
	igraph_vector_destroy(&edges);
}

void UtilIgraph::init_edge_capacities(int num_events, int num_users, 
			int num_edges, int num_mid_edges, 
			const std::vector<User> & users,
			const std::vector<Event> & events,
			igraph_vector_t & capacity) {
	igraph_vector_init(&capacity, num_edges);
	for (int event = 0; event < num_events; ++event) {
		VECTOR(capacity)[event] = events[event].get_upper_capacity();
	}
	int vector_capacity_count = num_events;
	for (int i = 0; i < num_mid_edges; ++i) {
		VECTOR(capacity)[vector_capacity_count] = 1;
		++vector_capacity_count;
	}
	for (int user = 0; user < num_users; ++user) {
		VECTOR(capacity)[vector_capacity_count + user] = users[user].get_upper_capacity();
	}
}





