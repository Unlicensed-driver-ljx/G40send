#ifndef DATACACHEQUEUE_H
#define DATACACHEQUEUE_H

#include <QQueue>
#include <QMutex>

using namespace std;

/**
* @brief  
* @date 2018/03/06
* @version 1.0
* @author Wangzy
*/
template <class T>
class DataCacheQueue
{
public:
	DataCacheQueue();
	~DataCacheQueue();

	void enqueue(T item);
	T dequeue();
	void clear();
	int count();
	bool isEmpty();
    void setMaxCount(int max_count);
private:
    int m_max_count;
	QMutex m_mutex;
	QQueue<T> m_queue;
};

template <class T>
DataCacheQueue<T>::~DataCacheQueue()
{
    m_queue.clear();
}

template <class T>
DataCacheQueue<T>::DataCacheQueue()
{
    m_max_count = 100000000;
    m_queue.reserve(100);
    m_queue.clear();
}

template <class T>
bool DataCacheQueue<T>::isEmpty()
{
	return m_queue.isEmpty();
}

template <class T>
int DataCacheQueue<T>::count()
{
	return m_queue.count();
}

template <class T>
void DataCacheQueue<T>::clear()
{
	m_mutex.lock();
	m_queue.clear();
	m_mutex.unlock();
}

template <class T>
T DataCacheQueue<T>::dequeue()
{
	m_mutex.lock();
	T item = m_queue.dequeue();
	m_mutex.unlock();
	return item;
}

template <class T>
void DataCacheQueue<T>::enqueue(T item)
{
	m_mutex.lock();
    if(m_queue.count() >= m_max_count)
    {
        m_queue.clear();
    }
	m_queue.enqueue(item);
	m_mutex.unlock();
}

template <class T>
void DataCacheQueue<T>::setMaxCount(int max_count)
{
    if(max_count > 0)
    {
        m_max_count = max_count;
    }
}
#endif //DATACACHEQUEUE_H
