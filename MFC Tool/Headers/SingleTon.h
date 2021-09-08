#pragma once
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template<class T>
class CSingleTon
{
protected:
	static T* m_pInstance;

protected:
	explicit CSingleTon() {};
	virtual ~CSingleTon() {};

public:
	static T* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new T;

		return m_pInstance;
	}
	static void DestoryInstacne()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
	
};

template<class T> 
T* CSingleTon<T>::m_pInstance = nullptr;
#endif

