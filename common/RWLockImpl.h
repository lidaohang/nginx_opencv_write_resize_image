//#ifndef DIS_COMMON_CRWLOCKIMPL_H_
//#define DIS_COMMON_CRWLOCKIMPL_H_
//
//#include <iostream>
//#include <pthread.h>
//#include <errno.h>
//#include <assert.h>
//
//using namespace std;
//namespace dis
//{
//	namespace common{ 
//		/*
//			��д������ǰ�Ķ�����û����ʱ�����Դ����ֻ����һ��д���߷��ʱ�����Դ
//		*/
//
//		//-----------------------------------------------------------------
//		class CRWLockImpl
//		{
//		protected:
//			CRWLockImpl();
//			~CRWLockImpl();
//			void ReadLockImpl();
//			bool TryReadLockImpl();
//			void WriteLockImpl();
//			bool TryWriteLockImpl();
//			void UnlockImpl();
//
//		private:
//			pthread_rwlock_t m_rwl;
//		};
//
//		//-----------------------------------------------------------------
//
//		class CMyRWLock: private CRWLockImpl
//		{
//		public:
//
//			//������/д��
//			CMyRWLock(){};
//
//			//���ٶ�/д��
//			~CMyRWLock(){};
//
//			//��ȡ����
//			//�������һ���߳�ռ��д������ǰ�̱߳���ȴ�д�����ͷţ����ܶԱ�����Դ���з���
//			void ReadLock();
//
//			//���Ի�ȡһ������
//			//�����ȡ�ɹ�������������true��������һ���߳�ռ��д�����򷵻�false
//			bool TryReadLock();
//
//			//��ȡд��
//			//���һ��������߳�ռ�ж����������ȴ����������ͷ�
//			//�����ͬ��һ���߳��Ѿ�ռ��һ��������д�����򷵻ؽ����ȷ��
//			void WriteLock();
//
//			//���Ի�ȡһ��д��
//			//�����ȡ�ɹ�������������true������һ������������߳�ռ�ж���������false
//			//�����ͬ��һ���߳��Ѿ�ռ��һ��������д�����򷵻ؽ����ȷ��
//			bool TryWriteLock();
//
//			//�ͷ�һ��������д��
//			void Unlock();
//
//		private:
//			CMyRWLock(const CMyRWLock&);
//			CMyRWLock& operator = (const CMyRWLock&);
//		};
//
//		inline void CMyRWLock::ReadLock()
//		{
//			ReadLockImpl();
//		}
//
//		inline bool CMyRWLock::TryReadLock()
//		{
//			return TryReadLockImpl();
//		}
//
//		inline void CMyRWLock::WriteLock()
//		{
//			WriteLockImpl();
//		}
//
//		inline bool CMyRWLock::TryWriteLock()
//		{
//			return TryWriteLockImpl();
//		}
//
//		inline void CMyRWLock::Unlock()
//		{
//			UnlockImpl();
//		}
//	}
//}
//#endif