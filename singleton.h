#ifndef SINGLETON_H
#define SINGLETON_H
/***********************************************************************
 * Module:  �̰߳�ȫ����ģ��
 * Author:  wwq(Owen)
 * Modified: 2015��7��17��������
 * Purpose: ����models ���ǵ���
 ***********************************************************************/
#include <mutex>

template<typename T>
class Singleton
{
 public:
	template<typename... Args>
	static T& instance(Args&&... args)
	{
		//�̰߳�ȫ�� ִֻ��һ��
		std::call_once(m_flag, [](Args&&... args){
								init(std::forward<Args>(args)...);
							}, std::forward<Args>(args)...);

		return *value_;
	}

 private:
  //���������湹�죬���ƣ���ֵ
  Singleton();
  Singleton(const Singleton& other);
  Singleton &operator=(const Singleton& other);
  ~Singleton();

  template <typename... Args>
  static void init(Args&&... args)
  {
    value_ = new T(std::forward<Args>(args)...);
    ::atexit(destroy);
  }

  //�ڴ棬��Դ�ͷ�
  static void destroy()
  {
    delete value_;
  }

 private:
  //����һ�α�־
  static std::once_flag m_flag;//����һ�α�־
  static T* value_;
};


template<typename T>
T* Singleton<T>::value_ = NULL;

template<typename T>
std::once_flag Singleton<T>::m_flag;

#endif // SINGLETON_H

