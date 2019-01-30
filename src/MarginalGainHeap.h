#ifndef _MARGINAL_GAIN_HEAP_H_
#define _MARGINAL_GAIN_HEAP_H_

#include <vector>
#include <cassert>
#include <cstdio>

class MarginalGain;

enum HeapAttr {MAXHEAP, MINHEAP};

class MarginalGainHeap {
private:
	MarginalGain* _heap; //堆的数组，第一个元素为空
	bool _maxHeap; //决定是否为大顶堆
	long _size; //堆数组_heap的实际元素数量，计入第一个元素
	long _capacity; //堆数组_heap的大小，计入第一个元素

	std::vector<std::vector<long> > _uepMatrix; // 外层是user，内层是event，元素为堆里相应的元素的下标，为0表示堆里没有该元素

public:
	// 构造函数（默认大顶堆）
	MarginalGainHeap();
	MarginalGainHeap(HeapAttr ha);
	MarginalGainHeap(HeapAttr ha, const int &numUsers, const int &numEvents);

	// 析构函数
	~MarginalGainHeap();

	// 初始化user数量、event数量、大/小顶
	void initialize(HeapAttr ha, const int &numUsers, const int &numEvents);

	// 清空
	bool clear();

	// 堆元素数目
	long size() const;
	bool empty() const;

	// 获取最大/最小元素的拷贝
	MarginalGain getTop() const;

	// 删除最大/最小元素，并返回其一个拷贝，自带排序
	MarginalGain pop();

	// 删除最大/最小元素，自带排序；若为空，则返回false
	bool delTop();

	//　插入/更新元素，自带排序
	bool insert(const MarginalGain &t); // 若原来就存在或者堆已满，则返回false；若成功插入，返回true
	bool update(const int &user, const int&event, const double&gain); // 若不存在该元素，则返回false; 存在该元素，则更新值并返回true
	
	// 检查堆中是否存在相应的元素
	bool contains(const MarginalGain &m) const;
	bool contains(const int &user, const int &event) const;


private:
	bool sinkTop(); //把堆顶沉下去。如果为空，返回false，否则返回true.
	void sink_MaxHeap(const long &index); //把堆数组中index的元素往下沉
	void sink_MinHeap(const long &index);

	bool goup(const long &index); //把index上浮一层。如果元素不存在，返回false.
	void goup_MaxHeap(const long &index);
	void goup_MinHeap(const long &index);
	void swapElements(const long &index1, const long &index2); //交换堆里index1和index2，同时要修改矩阵
	void set(const long &index, const MarginalGain &mg); //设置堆里的index，同时修改矩阵，不考虑被占用位置元素的问题
	long getIndex(const int &user, const int &event) const; //根据user和event获取在堆中的地址;若存在，返回地址，否则返回0
	long getIndex(const MarginalGain &mg) const;
};
#endif //_MARGINAL_GAIN_HEAP_H__
