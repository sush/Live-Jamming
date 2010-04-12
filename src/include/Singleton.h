#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template <typename T>
class Singleton
{
public:
  static T	*getInstance();
  static void	Delete();

protected:
  Singleton();
  Singleton(T const &);
  T &		operator = (T const &) const;
  virtual ~Singleton();

  static T	*_singleton;
};

template <typename T>
Singleton<T>::Singleton()
{}

template <typename T>
Singleton<T>::~Singleton()
{}

template <typename T>
T		*Singleton<T>::_singleton = 0;

template <typename T>
T		*Singleton<T>::getInstance()
{
  if (Singleton<T>::_singleton == 0)
    Singleton<T>::_singleton = new T;
  return static_cast<T *>(Singleton<T>::_singleton);

}

template <typename T>
void		Singleton<T>::Delete()
{
  if (Singleton<T>::_singleton != 0)
    {
      delete Singleton<T>::_singleton;
      Singleton<T>::_singleton = 0;
    }
}

#endif // ! __SINGLETON_H__
