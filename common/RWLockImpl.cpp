//#include "RWLockImpl.h"
//
//using namespace dis::common;
//
//CRWLockImpl::CRWLockImpl()
//{
//	if (pthread_rwlock_init(&m_rwl, NULL))
//		cout<<"cannot create reader/writer lock"<<endl;
//}
//
//CRWLockImpl::~CRWLockImpl()
//{
//	pthread_rwlock_destroy(&m_rwl);
//}
//
//void CRWLockImpl::ReadLockImpl()
//{
//	if (pthread_rwlock_rdlock(&m_rwl)) 
//		cout<<"cannot lock reader/writer lock"<<endl;
//}
//
//bool CRWLockImpl::TryReadLockImpl()
//{
//	int rc = pthread_rwlock_tryrdlock(&m_rwl);
//	if (rc == 0)
//		return true;
//	else if (rc == EBUSY)
//		return false;
//	else
//		cout<<"cannot lock reader/writer lock"<<endl;
//
//	return false;
//}
//
//void CRWLockImpl::WriteLockImpl()
//{
//	if (pthread_rwlock_wrlock(&m_rwl)) 
//		cout<<"cannot lock reader/writer lock"<<endl;
//}
//
//bool CRWLockImpl::TryWriteLockImpl()
//{
//	int rc = pthread_rwlock_trywrlock(&m_rwl);
//	if (rc == 0)
//		return true;
//	else if (rc == EBUSY)
//		return false;
//	else
//		cout<<"cannot lock reader/writer lock"<<endl;
//	return false;
//}
//
//void CRWLockImpl::UnlockImpl()
//{
//	if (pthread_rwlock_unlock(&m_rwl))
//		cout<<"cannot unlock reader/writer lock"<<endl;
//}