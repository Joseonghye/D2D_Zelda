#pragma once
#ifndef __SUBJECT_H__
#define __SUBJECT_H__

class CObserver;
class CSubject
{
public:
	CSubject() {}
	virtual ~CSubject() {}

	virtual void RegisterObserver(CObserver *observer) = 0;
	virtual void RemoveObserver() = 0;
	virtual void NotifyObserver() = 0;

};

#endif // !__SUBJECT_H__