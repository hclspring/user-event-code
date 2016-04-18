#include "Process.h"

using namespace std;

Process::Process(){
	num_users = -1;
	num_events = -1;
	cut_cost = -1;
	clique_cost = -1;
}

Process::~Process(){
}

bool Process::read_attr_file(std::string filename){
	ifstream ifs(filename.c_str());
	if(ifs.fail()){
		cerr << "Read file " << filename << " error." << endl;
		return false;
	}

	read_user_event_count(ifs);
	read_event_attributes(ifs);
	read_user_attributes(ifs);
	
	ifs.close();
	return true;
}

bool Process::read_user_pos_file(std::string filename){
	ifstream ifs(filename.c_str());
	if(ifs.fail()){
		cerr << "Read file " << filename << " error." << endl;
		return false;
	}
	
	assert(num_users > 0);
	read_user_positions(ifs);

	ifs.close();
	return true;
}

bool Process::read_event_pos_file(std::string filename)
{
	ifstream ifs(filename.c_str());
	if(ifs.fail()){
		cerr << "Read file " << filename << " error." << endl;
		return false;
	}

	assert(num_events > 0);
	read_event_positions(ifs);

	ifs.close();
	return true;

}

bool Process::read_event_capacity_file(std::string filename){
	ifstream ifs(filename.c_str());
	if(ifs.fail()){
		cerr << "Read file " << filename << " error." << endl;
		return false;
	}

	assert(num_events > 0);
	read_event_capacities(ifs);

	ifs.close();
	return true;

}

bool Process::read_preprocessed_data(std::string filename){	
	ifstream ifs(filename.c_str());
	if(ifs.fail()){
		cerr << "Read file " << filename << " error." << endl;
		return false;
	}

	// read number of events and users
	read_user_event_count(ifs);
	// read distance matrix
	read_distance_matrix(ifs);
	// read similarity matrix
	read_similarity_matrix(ifs);
	// read weight matrix
	string nextline = read_weight_matrix(ifs);
	// read upper capacity of events
	read_event_capacities(ifs, nextline);
	// 构造网络
	create_graph_users();

	ifs.close();
	return false;
}

bool Process::read_users_arrival(string filename)
{
	ifstream ifs(filename.c_str());
	if (ifs.fail()) {
		cerr << "Read file " << filename << " error." << endl;
		return false;
	}

	users_arrival.clear();
	string line;
	users_arrival.clear();
	while(getline(ifs, line, '\n')) {
		users_arrival.push_back(atoi(line.c_str()) - 1);
	}
	ifs.close();
	return true;
}

bool Process::read_assignment_data(string filename)
{
	ifstream ifs(filename.c_str());
	if(ifs.fail()){
		cerr << "Read file " << filename << " error." << endl;
		return false;
	}

	assert(num_users > 0 && num_events > 0);

	initialize_null_assignments();
	string line;
	vector<int> temp;
	for(int i = 0; i < num_users; i++){
		getline(ifs, line, '\n');
		temp = util.read_line_ints(line);
		assign(temp[0] - 1, temp[1] - 1);
	}

	ifs.close();
	return true;
}

void Process::create_graph_users()
{
	graph_users.clear();
	for (int i = 0; i < weight_user_user.size(); ++i) {
		list<int> temp;
		for (int j = 0; j < weight_user_user.size(); ++j) {
			if (weight_user_user[i][j] > 0.000001) {
				temp.push_back(j);
			}
		}
		graph_users.push_back(temp);
	}
}

void Process::gen_rand_arrival() {
	users_arrival.clear();
	for (int i = 0; i < num_users; ++i) {
		users_arrival.push_back(i);
	}
	random_shuffle(users_arrival.begin(), users_arrival.end());
	return;
}

void Process::calc_input_content() {
	calc_distance_matrix();
	calc_similarity_matrix();
	calc_weight_matrix();
}

double Process::calc_distance_user_event(User & u, Event & e)
{
	return util.calc_euc_distance(u.get_xpos(), u.get_ypos(), e.get_xpos(), e.get_ypos());
}

double Process::calc_similarity_user_event(User & u, Event & e)
{
	return util.calc_cos_similarity(u.get_attr(), e.get_attr());
}

double Process::calc_weight_user_user(User & u1, User & u2){
	return util.calc_cos_similarity(u1.get_attr(), u2.get_attr());
}

void Process::calc_distance_matrix(){
	assert(num_users > 0 && num_events > 0);
	distance_user_event.clear();

	for(int i = 0 ; i < num_users; i++){
		vector<double> row;
		for(int j = 0; j < num_events; j++){
			row.push_back(calc_distance_user_event(users[i], events[j]));
		}
		distance_user_event.push_back(row);
	}
}

void Process::calc_similarity_matrix(){
	assert(num_users > 0 && num_events > 0);
	similarity_user_event.clear();

	for(int i = 0; i < num_users; i++){
		vector<double> row;
		for(int j = 0; j < num_events; j++){
			row.push_back(calc_similarity_user_event(users[i], events[j]));
		}
		similarity_user_event.push_back(row);
	}
}

void Process::calc_weight_matrix(){
	assert(num_users > 0);
	weight_user_user.clear();

	for(int i = 0; i < num_users; i++){
		vector<double> row;
		for(int j = 0; j < num_users; j++){
			if(i != j){
				row.push_back(calc_weight_user_user(users[i], users[j]));
			} else {
				// user has weight 0 with himself
				row.push_back(0);
			}
		}
		weight_user_user.push_back(row);
	}

}

	// write data
bool Process::write_preprocessed_data(std::string filename){
	ofstream ofs(filename.c_str());
	if(ofs.fail()){
		cerr << "Write file " << filename << " error." << endl;
		return false;
	}

	ofs << num_events << " " << num_users << endl;
	// write distances
	for(int i = 0; i < distance_user_event.size(); i++){
		for(int j = 0; j < distance_user_event[i].size(); j++){
			if(j > 0){
				ofs << " ";
			}
			ofs << distance_user_event.at(i).at(j);
		}
		ofs << endl;
	}
	
	// write similarities
	for(int i = 0; i < similarity_user_event.size(); i++){
		for(int j = 0; j < similarity_user_event[i].size(); j++){
			if(j > 0){
				ofs << " ";
			}
			ofs << similarity_user_event.at(i).at(j);
		}
		ofs << endl;
	}

	// write weights
	for(int i = 0; i < weight_user_user.size(); i++){
		for(int j = i+1; j < weight_user_user[i].size(); j++){
			ofs << i << " " << j << " " << weight_user_user.at(i).at(j) << endl;
		}
	}
 
	//write event capacity
	for(int i = 0; i < events.size(); i++){
		ofs << events[i].get_upper_capacity() << endl;
	}


	ofs.close();
	return true;
}

bool Process::write_assignment_result(string filename)
{
	ofstream ofs(filename.c_str());
	if(ofs.fail()){
		cerr << "Write file " << filename << " error." << endl;
		return false;
	}
	for(int i = 0; i < user_affinities.size(); i++){
		ofs << i+1 << " " << user_affinities[i]+1 << endl;
	}
	return true;
}

bool Process::write_assignment_costs(string filename)
{
	ofstream ofs(filename.c_str());
	if(ofs.fail()){
		cerr << "Write file " << filename << " error." << endl;
		return false;
	}

	if (check_assignments_feasible() == false) {
		ofs << "WARNING: This assignment is NOT feasible." << endl;
	}
	ofs << "cut_cost=" << cut_cost << endl;
	ofs << "clique_cost=" << clique_cost << endl;
	return true;
}

bool Process::write_assignment_costs(string filename, string type)
{
	ofstream ofs(filename.c_str());
	if(ofs.fail()){
		cerr << "Write file " << filename << " error." << endl;
		return false;
	}

	if (check_assignments_feasible() == false) {
		ofs << "WARNING: This assignment is NOT feasible." << endl;
	}
	if (type.compare("cut") == 0) {
		ofs << "cut_cost=" << cut_cost << endl;
	} else {
		ofs << "clique_cost=" << clique_cost << endl;
	}
	return true;

}

bool Process::write_arrival_sequence(string filename)
{
	ofstream ofs(filename.c_str());
	if(ofs.fail()) {
		cerr << "Write file " << filename << " error." << endl;
		return false;
	}

	for (int i = 0; i < users_arrival.size(); ++i) {
		ofs << users_arrival[i] + 1  << endl;
	}
	ofs.close();
	return true;
}

void Process::calc_assignments_clique_offline(){
	initialize_null_assignments();

	MarginalGainHeap mgh(MAXHEAP, num_users, num_events);
	for (int i = 0; i < num_users; ++i) {
		for (int j = 0; j < num_events; ++j) {
			double gain = calc_marginal_gain_offline_clique(i, j);
			if (gain > 0) {
				mgh.insert(MarginalGain(i, j, gain));
			}
		}
	}

	while (!mgh.empty()) {
		MarginalGain maxGain = mgh.pop();
		int u = maxGain.get_user();
		int v = maxGain.get_event();
		if (event_users[v].size() < events[v].get_upper_capacity()
				&& user_affinities[u] < 0) {
			assign(u, v);
			for (list<int>::iterator it = graph_users[u].begin(); it != graph_users[u].end(); ++it) {
				int neigh = *it;
				if (user_affinities[neigh] < 0) {
					mgh.update(neigh, v, calc_marginal_gain_offline_clique(neigh, v));
				}
			}
		}
	}
}

void Process::calc_assignments_cut_offline()
{
	initialize_null_assignments();

	MarginalGainHeap heap(MINHEAP, num_users, num_events);
	for (int i = 0; i < num_users; ++i) {
		for (int j = 0; j < num_events; ++j) {
			double gain = calc_marginal_gain_offline_cut(i, j);
			if (gain > 0) {
				heap.insert(MarginalGain(i, j, gain));
			}
		}
	}

	while (!heap.empty()) {
		MarginalGain minGain = heap.pop();
		int u = minGain.get_user();
		int v = minGain.get_event();
		if (event_users[v].size() < events[v].get_upper_capacity()
				&& user_affinities[u] < 0) {
			assign(u, v);
			for (list<int>::iterator it = graph_users[u].begin(); it != graph_users[u].end(); ++it) {
				int neigh = *it;
				if (user_affinities[neigh] < 0) {
					heap.update(neigh, v, calc_marginal_gain_offline_cut(neigh, v));
				}
			}
		}
	}
}

void Process::calc_assignments_exhaustive_offline(const std::string & kind, const double & alpha, const double & beta, const double & gamma)
{
	bool use_cut;
	if (kind.compare("cut") == 0) {
		use_cut = true;
	} else {
		use_cut = false;
	}

	vector<int> optimal_user_affinities;
	double optimal_cost;
	double current_cost;
	if (initialize_exhaustive_first_feasible_assignments()) {
		if (use_cut) {
			current_cost = calc_cut_cost(alpha, beta, gamma);
			optimal_cost = current_cost;
		} else {
			current_cost = calc_clique_cost(alpha, beta, gamma);
			optimal_cost = current_cost;
		}

		while (find_exhaustive_next_feasible_assignments()) {
			if (use_cut) {
				current_cost = calc_cut_cost(alpha, beta, gamma);
				if (current_cost < optimal_cost) {
					optimal_cost = current_cost;
					optimal_user_affinities = user_affinities;
				}
			} else {
				current_cost = calc_clique_cost(alpha, beta, gamma);
				if (current_cost > optimal_cost) {
					optimal_cost = current_cost;
					optimal_user_affinities = user_affinities;
				}
			}
		}
		
		if (use_cut) {
			cut_cost = optimal_cost;
			clique_cost = 0;
		} else {
			cut_cost = 0;
			clique_cost = optimal_cost;
		}
	} else {
		cut_cost = -1;
		clique_cost = -1;
	}
}


void Process::calc_assignments_clique_online()
{
	initialize_null_assignments();
	for (int arrived_user_index = 0; arrived_user_index < num_users; ++arrived_user_index) {
		int arrived_user = users_arrival[arrived_user_index];
		vector<int> satisfied_neighbors;
		for (list<int>::iterator it = graph_users[arrived_user].begin(); it != graph_users[arrived_user].end(); ++it) {
			int neigh = *it;
			int v = user_affinities[neigh];
			if (v >= 0
					&& event_users[v].size() < events[v].get_upper_capacity()) {
				satisfied_neighbors.push_back(neigh);
			}
		}

		double max_gain = 0;
		int max_v = 0;
		if (satisfied_neighbors.size() == 0) {
			for (int j = 0; j < num_events; ++j) {
				if (event_users[j].size() < events[j].get_upper_capacity()) {
					double gain = calc_marginal_gain_online_clique(arrived_user, j);
					if (gain > max_gain) {
						max_gain = gain;
						max_v = j;
					}
				}
			}
		} else {
			for (int i = 0; i < satisfied_neighbors.size(); ++i) {
				int neighbor = satisfied_neighbors[i];
				int v = user_affinities[neighbor];
				double gain = calc_marginal_gain_online_clique(arrived_user, i, v);
				if (gain > max_gain) {
					max_gain = gain;
					max_v = v;
				}
			}
		}
		assign(arrived_user, max_v);
	}
}

void Process::calc_assignments_cut_online(){
	initialize_null_assignments();
	for (int arrived_user_index = 0; arrived_user_index < num_users; ++arrived_user_index) {
		int arrived_user = users_arrival[arrived_user_index];
		vector<int> satisfied_neighbors;
		for (list<int>::iterator it = graph_users[arrived_user].begin(); it != graph_users[arrived_user].end(); ++it) {
			int neigh = *it;
			int v = user_affinities[neigh];
			if (v >= 0) {
				satisfied_neighbors.push_back(neigh);
			}
		}

		double min_gain = DBL_MAX;
		int min_v = -1;
		if (satisfied_neighbors.size() == 0) {
			for (int j = 0; j < num_events; ++j) {
				if (event_users[j].size() < events[j].get_upper_capacity()) {
					double gain = calc_marginal_gain_online_cut(arrived_user, j);
					if (gain < min_gain) {
						min_gain = gain;
						min_v = j;
					}
				}
			}
		} else {
			for (int i = 0; i < satisfied_neighbors.size(); ++i) {
				int neighbor = satisfied_neighbors[i];
				int nei_event = user_affinities[neighbor];
				for (int v = 0; v < num_events; ++v) {
					if (event_users[v].size() < events[v].get_upper_capacity()) {
						double gain;
						if (v != nei_event) {
							gain = calc_marginal_gain_online_cut(arrived_user, neighbor, v);
						} else {
							gain = calc_marginal_gain_online_cut(arrived_user, v);
						}
						if (gain < min_gain) {
							min_gain = gain;
							min_v = v;
						}
					}
				}
			}
		}
		assign(arrived_user, min_v);
	}

}

double Process::calc_cut_cost(double alpha, double beta, double gamma)
{
	double sum_distance = 0.0, sum_similarity = 0.0, sum_weight = 0.0;

	for(int i = 0; i < num_users; i++){
		sum_distance += distance_user_event.at(i).at(user_affinities[i]);
		sum_similarity += similarity_user_event.at(i).at(user_affinities[i]);
	}

	for (int i = 0; i < num_users; ++i) {
		for (list<int>::iterator it = graph_users[i].begin(); it != graph_users[i].end(); ++it) {
			int nei = *it;
			if (user_affinities[i] != user_affinities[nei]) {
				sum_weight += weight_user_user[i][nei];
			}
		}
	}

	if (fabs(sum_similarity) < 0.000001) {
		cut_cost = alpha*sum_distance + beta * MAX + gamma*sum_weight;
	} else {
		cut_cost = alpha*sum_distance + beta/sum_similarity + gamma*sum_weight;
	}
	return cut_cost;
}

double Process::calc_clique_cost(double alpha, double beta, double gamma)
{
	double sum_distance = 0.0, sum_similarity = 0.0, sum_weight = 0.0;

	for(int i = 0; i < num_users; i++){
		sum_distance += distance_user_event.at(i).at(user_affinities[i]);
		sum_similarity += similarity_user_event.at(i).at(user_affinities[i]);
	}

	for(int i = 0; i < num_events; i++){
		vector<int> temp_users;
		for(set<int>::iterator it = event_users[i].begin(); it != event_users[i].end(); it++){
			set<int>::iterator jt = it;
			for (++jt; jt != event_users[i].end(); ++jt) {
				sum_weight += weight_user_user.at(*it).at(*jt); // 只加一遍j--k，不加k--j
			}
		}
	}

	if (fabs(sum_distance) < 0.000001) {
		clique_cost = alpha * MAX + beta * sum_similarity + gamma * sum_weight;
	} else {
		clique_cost = 1.0 * alpha/sum_distance + beta*sum_similarity + gamma*sum_weight;
	}
	return clique_cost;

}

void Process::initialize_null_assignments(){
	user_affinities.clear();
	user_affinities.resize(num_users, -1);
	event_users.clear();
	event_users.resize(num_events, set<int>());
}

bool Process::assign(int user, int event){
	assert(user >= 0 && user < num_users);
	assert(event >= 0 && event < num_events);
	if (user_affinities[user] >= 0) {
		return false;
	} else if (event_users[event].size() >= events[event].get_upper_capacity()) {
		return false;
	} else {
		user_affinities[user] = event;
		event_users[event].insert(user);
		return true;
	}
}

/*
bool Process::change_assignment(int user, int event){
	assert(user >= 0 && user < num_users);
	assert(event >= 0 && event < num_events);
	if (user_affinities[user] < 0 || user_affinities[user] == event) {
		return false;
	} else if (event_users[event].size() >= events[event].get_upper_capacity()) {
		return false;
	} else {
		event_users[user_affinities[user]].erase(user);
		user_affinities[user] = event;
		event_users[event].insert(user);
		return true;
	}
}
*/

void Process::read_user_event_count(ifstream &ifs) {
	string line;
	getline(ifs, line, '\n');
	vector<int> temp = util.read_line_ints(line);
	assert(temp.size() >= 2);
	num_events = temp[0];
	num_users = temp[1];
	events.clear();
	events.resize(num_events);
	users.clear();
	users.resize(num_users);
}

void Process::read_event_attributes(std::ifstream &ifs) {
	string line;
	for(int line_count = 0; line_count < num_events; line_count++){
		getline(ifs, line, '\n');
		events[line_count].set_attr(util.read_line_doubles(line));
	}
}

void Process::read_user_attributes(std::ifstream &ifs) {
	string line;
	assert(users.size() == num_users);
	for(int line_count = 0; line_count < num_users; line_count++){
		getline(ifs, line, '\n');
		users[line_count].set_attr(util.read_line_doubles(line));
	}
}

void Process::read_user_positions(std::ifstream &ifs) {
	string line;
	vector<double> temp;
	assert(users.size() == num_users);
	for(int i = 0; i < num_users; i++){
		getline(ifs, line, '\n');
		vector<double> temp = util.read_line_doubles(line);
		assert(temp.size() >= 2);
		users[i].set_xpos(temp[0]);
		users[i].set_ypos(temp[1]);
	}
}

void Process::read_event_positions(std::ifstream &ifs) {
	string line;
	vector<double> temp;
	assert(events.size() == num_events);
	for(int i = 0; i < num_events; i++){
		getline(ifs, line, '\n');
		vector<double> temp = util.read_line_doubles(line);
		assert(temp.size() >= 2);
		events[i].set_xpos(temp[0]);
		events[i].set_ypos(temp[1]);
	}
}

void Process::read_event_capacities(std::ifstream &ifs) {
	string line;
	assert(events.size() == num_events);
	for(int i = 0; i < num_events; i++){
		getline(ifs, line, '\n');
		events[i].set_upper_capacity(atoi(line.c_str()));
	}
}

void Process::read_event_capacities(std::ifstream &ifs, const std::string &firstline) {
	assert(events.size() == num_events);
	events[0].set_upper_capacity(atoi(firstline.c_str()));
	string line;
	for(int i = 1; i < num_events; i++){
		getline(ifs, line, '\n');
		events[i].set_upper_capacity(atoi(line.c_str()));
	}
}


void Process::read_distance_matrix(std::ifstream &ifs) {
	distance_user_event.clear();
	string line;
	for(int i = 0; i < num_users; i++){
		getline(ifs, line, '\n');
		distance_user_event.push_back(util.read_line_doubles(line));
	}
}

void Process::read_similarity_matrix(std::ifstream &ifs) {
	similarity_user_event.clear();
	string line;
	for(int i = 0; i < num_users; i++){
		getline(ifs, line, '\n');
		similarity_user_event.push_back(util.read_line_doubles(line));
	}
}

std::string Process::read_weight_matrix(std::ifstream &ifs) {
	weight_user_user.clear();
	weight_user_user.resize(num_users);
	for(int i = 0; i < num_users; i++){
		weight_user_user[i].resize(num_users, 0);
	}
	int a, b;
	double c;

	std::string line;
	while(true){
		getline(ifs, line, '\n');
		if(util.get_number_of_spaces(line) > 1){
			stringstream sstr4(line);
			sstr4 >> a >> b >> c;
			assert(a >= 0 && a < num_users);
			assert(b >= 0 && b < num_users);
			weight_user_user.at(a).at(b) = c;
			weight_user_user.at(b).at(a) = c;
		} else {
			break;
		}
	}
	return line;
}


double Process::calc_marginal_gain_offline_clique(int user_index, int event_index)
{
	double result = 0;
	double d = distance_user_event.at(user_index).at(event_index);
	//assert(fabs(d) > 0.000001);
	if(fabs(d) < 0.000001)
		result += MAX;
	else
		result += 1.0 / d;

	result += similarity_user_event.at(user_index).at(event_index);

	bool event_has_other_users = false;
	for(set<int>::iterator it = event_users[event_index].begin(); it != event_users[event_index].end(); it++){
		int u = *it;
		if(u != user_index){
			event_has_other_users = true;
			result += weight_user_user.at(user_index).at(u);
		}
	}
	
	/*
	if (event_has_other_users) {
		result /= 3.0;
	} else {
		result *= 0.5;
	}
	*/
	return result;
}

double Process::calc_marginal_gain_offline_cut(int user_index, int event_index)
{
	double result = 0;

	double d = distance_user_event.at(user_index).at(event_index);
	result += d;

	double s = similarity_user_event.at(user_index).at(event_index);
	if(fabs(s)<0.0000001)
		result += MAX;
	else
		result += 1.0 / s;

	bool event_has_other_users = false;
	if (event_users[event_index].size() > 0) {
		for (list<int>::iterator it = graph_users[user_index].begin(); it != graph_users[user_index].end(); ++it) {
			int nei = *it;
			if (user_affinities[nei] >= 0 && user_affinities[nei] != event_index) {
				event_has_other_users = true;
				result += weight_user_user[user_index][nei];
			}
		}
	}

	/*
	if (event_has_other_users) {
		result /= 3.0;
	} else {
		result *= 0.5;
	}
	*/

	return result;
}

double Process::calc_marginal_gain_online_clique(int user_index, int event_index){
	double result = 0, temp = distance_user_event[user_index][event_index];
	if (fabs(temp) < 0.000001) {
		result += MAX;
	} else {
		result += 1.0 / temp;
	}
	result += similarity_user_event[user_index][event_index];
	return result;
}

double Process::calc_marginal_gain_online_clique(int user_index, int neighbor_index, int event_index){
	double result = calc_marginal_gain_online_clique(user_index, event_index);
	result += weight_user_user[user_index][neighbor_index];
	return result;
}

double Process::calc_marginal_gain_online_cut(int user_index, int event_index){
	double result = distance_user_event[user_index][event_index];
	double sigma = similarity_user_event[user_index][event_index];
	if (fabs(sigma) < 0.000001) {
		result += MAX;
	} else {
		result += 1.0 / sigma;
	}
	return result;
}
	
double Process::calc_marginal_gain_online_cut(int user_index, int neighbor_index, int event_index){
	double result = calc_marginal_gain_online_cut(user_index, event_index);
	result += weight_user_user[user_index][neighbor_index];
	return result;
}

bool Process::initialize_exhaustive_first_feasible_assignments() {
	initialize_null_assignments();

	int event = 0;
	bool assign_success;
	for (int user = 0; user < num_users && event < num_events; ++user) {
		assign_success = assign(user, event);
		if (assign_success == false) {
			do {
				++event;
				assign_success = assign(user, event);
			} while (assign_success == false && event < num_events);
		}
	}
	if (user_affinities[num_users - 1] >= 0) {
		return true;
	} else {
		return false;
	}
}

bool Process::find_exhaustive_next_feasible_assignments() {
	vector<int> user_asn = user_affinities; //把当前解保存下来

	bool feasible = true; //判断找到的解是不是可行解
	do {
		// 重复循环直到找到一个解满足所有活动的参与人数都不超过各自活动的人数限制
		// 此循环的重复过程类似一个有num_users位的数字（num_events进制数）从当前值开始不断递增加1的过程
		int site = user_asn.size() - 1; //site指代末位数
		if (user_asn[site] == num_events - 1) { //末位数达到num_events-1，类似十进制数中的9，需要进位
			// 进位
			while (user_asn[site] == num_events - 1) { //重复向前进位直到一位不是num_events-1的数（类似十进制中的1299，需要找到百位再停止
				user_asn[site] = 0;
				--site;
			}
			if (site < 0) { //最高位也是num_events-1，即所有位都是num_events-1，达到最大数字，说明没能找到下一个可行解
				return false;
			} else {
				++user_asn[site]; //进位
			}
		} else {
			++user_asn[site]; //直接+1
		}

		// 检查此解的可行性
		vector<int> events_size;
		events_size.resize(num_events, 0);
		for (int i = 0; i < num_users; ++i) {
			++events_size[user_asn[i]];
		}
		feasible = true;
		for (int i = 0; i < events_size.size(); ++i) {
			if (events_size[i] > events[i].get_upper_capacity()) {
				feasible = false;
			}
		}
	} while (feasible == false);

	// 根据找到的可行解进行分配活动
	initialize_null_assignments();
	for (int user = 0; user < num_users; ++user) {
		assign(user, user_asn[user]);
	}
	return true;
}

bool Process::check_assignments_feasible() {
	if (user_affinities.size() != num_users || event_users.size() != num_events) {
		return false;
	}
	for (int i = 0; i < user_affinities.size(); ++i) {
		if (user_affinities[i] < 0 || user_affinities[i] >= num_users) {
			return false;
		}
	}
	for (int i = 0; i < event_users.size(); ++i) {
		if (event_users[i].size() > events[i].get_upper_capacity()) {
			return false;
		}
	}
	return true;
}
