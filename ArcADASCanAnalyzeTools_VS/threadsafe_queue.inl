#pragma once

#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>

template <typename T>
class threadsafe_queue
{
public:
	threadsafe_queue();

	threadsafe_queue(const threadsafe_queue&);

	threadsafe_queue& operator=(const threadsafe_queue&) = delete;

	void push(T newValue);

	bool try_pop(T& value);

	std::shared_ptr<T> try_pop();

	bool wait_and_pop(T& value);

	std::shared_ptr<T> wait_and_pop();

	bool empty() const;

	void clear();

	size_t size() const;

	~threadsafe_queue();

private:
	mutable std::mutex m_mutex;
	std::queue<T> m_dataQueue;
	std::condition_variable m_dataCond;
};

template <typename T>
size_t threadsafe_queue<T>::size() const
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return m_dataQueue.size();
}

template <typename T>
threadsafe_queue<T>::threadsafe_queue()
{

}

template <typename T>
threadsafe_queue<T>::threadsafe_queue(const threadsafe_queue& other)
{
	std::lock_guard<std::mutex> lk(other.m_mutex);
	m_dataQueue = other.m_dataQueue;
}

template <typename T>
bool threadsafe_queue<T>::empty() const
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return m_dataQueue.empty();
}

template<typename T>
void threadsafe_queue<T>::clear()
{
	std::lock_guard<std::mutex> lk(m_mutex);
	std::queue<T> empty;
	std::swap(empty, m_dataQueue);
}

template <typename T>
std::shared_ptr<T> threadsafe_queue<T>::try_pop()
{
	std::lock_guard<std::mutex>lk(m_mutex);
	if (m_dataQueue.empty())
	{
		return std::shared_ptr<T>();
	}

	std::shared_ptr<T> res(std::make_shared<T>(m_dataQueue.front()));

	m_dataQueue.pop();

	return res;
}

template <typename T>
bool threadsafe_queue<T>::try_pop(T& value)
{
	std::lock_guard<std::mutex>lk(m_mutex);

	if (m_dataQueue.empty())
	{
		return false;
	}

	value = m_dataQueue.front();
	m_dataQueue.pop();
	return true;
}

template <typename T>
std::shared_ptr<T> threadsafe_queue<T>::wait_and_pop()
{
	std::unique_lock<std::mutex> lk(m_mutex);
	m_dataCond.wait(lk, [&]
	{
		return !m_dataQueue.empty();
	});

	std::shared_ptr<T> res(std::make_shared<T>(m_dataQueue.front()));

	m_dataQueue.pop();

	return res;
}

template <typename T>
bool threadsafe_queue<T>::wait_and_pop(T& value)
{
	std::unique_lock<std::mutex> lk(m_mutex);
    m_dataCond.wait_for(lk,  std::chrono::milliseconds(1), [&]
	{
		return !m_dataQueue.empty();
	});

	if (m_dataQueue.empty())
	{
		return false;
	}

	value = m_dataQueue.front();
	m_dataQueue.pop();

	return true;
}

template <typename T>
void threadsafe_queue<T>::push(T newValue)
{
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        m_dataQueue.push(newValue);
    }
	m_dataCond.notify_one();
}

template <typename T>
threadsafe_queue<T>::~threadsafe_queue()
{

}
