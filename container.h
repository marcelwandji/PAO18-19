#ifndef CONTAINER_H
#define CONTAINER_H

template <class T>
class Container{
private:
   class nodo{
   public:
      T info;
      nodo* next;
      nodo(const T& , nodo* = nullptr) ;
      ~nodo();
   };
   nodo* item;
   static bool search(const T& , nodo* );
   static void append(const T& , nodo*& );
   static void remove(const T& , nodo*& );
   static nodo* copy(nodo* n);

public:
  class iterator{
  public:
     nodo* punt;
     bool operator==(iterator) const;
     bool operator!=(iterator) const;
     iterator& operator++();
     iterator operator++(int);
     T& operator*() const;
  };
  Container();
  Container(const Container& ) ;
  Container& operator=(const Container& );
  ~Container();
  bool is_empty() const;
  bool search(const T& ) const;
  void insert(const T& );
  void remove(const T& );
  void replace(int, T);
  iterator begin() const;
  iterator end() const;
  T& operator[](int) const;
  int size() const;
  const T at(int ) const;
};


#endif // CONTAINER_H
