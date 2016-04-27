#pragma once

template<typename LOCK, typename WORKER>
class CAutoLock
{
public:
	//LOCK of type CLockHolder
	CAutoLock(
		LOCK& lock
		) : m_lock(lock)
	{
		m_lock.Lock();
	}
	//LOCK of type TLOCK in CLockWorker's & CLockHolder's
	CAutoLock(
		LOCK* lock
		) : m_lock(lock)
	{
		m_lock.Lock();
	}

	~CAutoLock()
	{
		m_lock.Unlock();
	}

	CAutoLock(const CAutoLock&);
private:
	void operator=(const CAutoLock&) = delete;

protected:
	WORKER m_lock;
};

template<typename TLOCK>
class CLockWorker
{
protected:
	explicit CLockWorker(
		TLOCK* lock
		) : m_tLock(lock)
	{
	}

private:
	CLockWorker(const CLockWorker&) = delete;
	void operator=(const CLockWorker&) = delete;

protected:
	TLOCK* m_tLock;
};

template<typename TLOCK>
class CLockHolder
{
protected:
	explicit CLockHolder()
	{
	}

public:
	TLOCK* operator&()
	{
		return &m_tInitLock;
	}

private:
	CLockHolder(const CLockHolder&) = delete;
	void operator=(const CLockHolder&) = delete;

protected:
	TLOCK m_tInitLock;
};
