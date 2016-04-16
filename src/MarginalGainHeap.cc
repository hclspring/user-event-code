#include "MarginalGainHeap.h"

MarginalGainHeap::MarginalGainHeap():
	_heap(NULL), _maxHeap(true), _size(0), _capacity(0) {
		_uepMatrix.clear();
	}

MarginalGainHeap::MarginalGainHeap(HeapAttr ha) {
	_heap = NULL;
	if (ha == MAXHEAP) {
		_maxHeap = true;
	} else {
		_maxHeap = false;
	}
	_size = 0;
	_capacity = 0;
	_uepMatrix.clear();
}

MarginalGainHeap::MarginalGainHeap(HeapAttr ha, const int &numUsers, const int &numEvents){
	initialize(ha, numUsers, numEvents);
}

MarginalGainHeap::~MarginalGainHeap(){
	clear();
}

void MarginalGainHeap::initialize(HeapAttr ha, const int &numUsers, const int &numEvents)
{
	if (ha == MAXHEAP) {
		_maxHeap = true;
	} else {
		_maxHeap = false;
	}
	_size = 0;
	_capacity = numUsers * numEvents + 1;
	_heap = new MarginalGain[_capacity];
	std::vector<long> temp(numEvents, 0);
	_uepMatrix.resize(numUsers, temp);
}

bool MarginalGainHeap::clear() {
	if (_heap != NULL) {
		delete [] _heap;
		_heap = NULL;
	}
	_size = 0;
	_capacity = 0;
	_uepMatrix.clear();
	return true;
}

long MarginalGainHeap::size() const {
	return _size == 0 ? 0 : _size - 1;
}

bool MarginalGainHeap::empty() const {
	if (_size <= 1){
		return true;
	} else {
		return false;
	}
}

MarginalGain MarginalGainHeap::getTop() const {
	assert(_size > 1);
	return _heap[1];
}

MarginalGain MarginalGainHeap::pop() {
	assert(_size > 1);
	MarginalGain mg = getTop();
	delTop();
	return mg;
}

bool MarginalGainHeap::delTop() {
	if (empty()) {
		return false;
	} else {
		_uepMatrix[_heap[1].get_user()][_heap[1].get_event()] = 0;
		set(1, _heap[_size - 1]);
		--_size;
		sinkTop();
		return true;
	}
}

bool MarginalGainHeap::insert(const MarginalGain &m){
	if (_size >= _capacity) {
		return false;
	}
	if (_size == 0) {
		_size = 1;
	}
	if (contains(m)) {
		return false;
	} else {
		++_size;
		set(_size - 1, m);
		goup(_size - 1);
		return true;
	}
}

bool MarginalGainHeap::update(const int &user, const int &event, const double &gain) {
	long index = getIndex(user, event);
	if (index <= 0 || index >= _size) {
		return false;
	} else {
		double old_gain = _heap[index].get_gain();
		_heap[index].set_gain(gain);
		if (gain > old_gain) {
			if (_maxHeap) {
				goup_MaxHeap(index);
			} else {
				sink_MinHeap(index);
			}
		} else {
			if (_maxHeap) {
				sink_MaxHeap(index);
			} else {
				goup_MinHeap(index);
			}
		}
		return true;
	}
}

bool MarginalGainHeap::contains(const MarginalGain &mg) const {
	return contains(mg.get_user(), mg.get_event());
}

bool MarginalGainHeap::contains(const int &user, const int &event) const {
	long index = getIndex(user, event);
	if (index > 0 && index < _size) {
		return true;
	} else {
		return false;
	}
}

bool MarginalGainHeap::sinkTop() {
	if (empty()){
		return false;
	} else {
		if (_maxHeap) {
			sink_MaxHeap(1);
		} else {
			sink_MinHeap(1);
		}
		return true;
	}
}

void MarginalGainHeap::sink_MaxHeap(const long &index) {
	long leftIndex = 2 * index;
	long rightIndex = leftIndex + 1;
	if (leftIndex < _size) {
		long maxIndex = leftIndex;
		if (rightIndex < _size && _heap[rightIndex] > _heap[maxIndex]) {
			maxIndex = rightIndex;
		}
		if (_heap[maxIndex] > _heap[index]) {
			swapElements(maxIndex, index);
			sink_MaxHeap(maxIndex);
		}
	}
}


void MarginalGainHeap::sink_MinHeap(const long &index) {
	long leftIndex = 2 * index;
	long rightIndex = leftIndex + 1;
	if (leftIndex < _size) {
		long minIndex = leftIndex;
		if (rightIndex < _size && _heap[rightIndex] < _heap[minIndex]) {
			minIndex = rightIndex;
		}
		if (_heap[minIndex] < _heap[index]) {
			swapElements(minIndex, index);
			sink_MinHeap(minIndex);
		}
	}
}

bool MarginalGainHeap::goup(const long &index) {
	if (index <= 1 || index >= _size) {
		return false;
	} else {
		if (_maxHeap) {
			goup_MaxHeap(index);
		} else {
			goup_MinHeap(index);
		}
		return true;
	}
}

void MarginalGainHeap::goup_MaxHeap(const long &index) {
	long pa = index / 2;
	if (pa >= 1 && _heap[pa] < _heap[index]) {
		swapElements(pa, index);
		goup_MaxHeap(pa);
	}
}

void MarginalGainHeap::goup_MinHeap(const long &index) {
	long pa = index / 2;
	if (pa >= 1 && _heap[pa] > _heap[index]) {
		swapElements(pa, index);
		goup_MaxHeap(pa);
	}
}

void MarginalGainHeap::swapElements(const long &index1, const long &index2){
	assert(index1 > 0 && index1 < _size);
	assert(index2 > 0 && index2 < _size);
	MarginalGain temp1 = _heap[index1];
	MarginalGain temp2 = _heap[index2];
	set(index1, temp2);
	set(index2, temp1);
}

void MarginalGainHeap::set(const long &index, const MarginalGain &mg){
	assert(index > 0 && index < _size);
	int user = mg.get_user();
	int event = mg.get_event();
	_uepMatrix[user][event] = index;
	_heap[index] = mg;
}

long MarginalGainHeap::getIndex(const int &user, const int &event) const {
	if (user < _uepMatrix.size() && event < _uepMatrix[user].size()) {
		return _uepMatrix[user][event];
	} else {
		return 0;
	}
}

long MarginalGainHeap::getIndex(const MarginalGain &mg) const {
	return getIndex(mg.get_user(), mg.get_event());
}
