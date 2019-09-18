#include "container.h"

template <class T>
Container<T>::nodo::nodo(const T& t, nodo* b) : info(t) , next(b) {}

template <class T>
Container<T>::Container() : item(nullptr) {}

template <class T>
Container<T>::Container(const Container& c) : item(copy(c.item)) {}

template <class T>
Container<T>::nodo::~nodo(){if(next) delete next;}

template <class T>
bool Container<T>::search(const T& t ,nodo* n){
   if(!n) return false;
   return (n->info == t) || search(t,n->next);
}

template <class T>
void Container<T>::append(const T& t, nodo*& n){
    if(!n) n = new nodo(t);
    else append(t,n->next);
}

template <class T>
void Container<T>::remove(const T& t, nodo*& n){
    if(n){
      if(n->info == t) n=n->next;
      else remove(t,n->next);
    }
}

template <class T>
typename Container<T>::nodo* Container<T>::copy(nodo* n){
   if(!n) return 0;
   return new nodo(n->info, copy(n->next));
}

template <class T>
bool Container<T>::iterator::operator==(iterator i) const{
   return punt == i.punt;
}

template <class T>
bool Container<T>::iterator::operator!=(iterator i) const {
   return punt != i.punt;
}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator++(){
   if(punt) punt = punt->next;
   return *this;
}

template <class T>
typename Container<T>::iterator Container<T>::iterator::operator++(int){
   Container<T>::iterator aux = *this;
   if(punt) punt = punt->next;
   return aux;
}

template <class T>
T& Container<T>::iterator::operator*() const{
    return punt->info;
}

template <class T>
Container<T>& Container<T>::operator=(const Container& c){
   if(this!= &c){
      delete item;
      item = copy(c.item);
   }
   return *this;
}

template <class T>
bool Container<T>::is_empty() const{
   return item == nullptr;
}

template <class T>
bool Container<T>::search(const T& t) const {
   return search(t, item);
}

template <class T>
void Container<T>::insert(const T& t){
    append(t,item);
}

template <class T>
void Container<T>::remove(const T& t){
   remove(t,item);
}

template <class T>
Container<T>::~Container() {if(item) delete item;}

template <class T>
typename Container<T>::iterator Container<T>::begin() const{
   iterator aux;
   aux.punt = item;
   return aux;
}

template <class T>
typename Container<T>::iterator Container<T>::end() const{
   iterator aux;
   aux.punt = 0;
   return aux;
}

template <class T>
T& Container<T>::operator[](int i) const{
    Container<T>::iterator it = begin();
    while (it != end() && i) {
        it++;  i--;
      }
    if (it != end()) return *it;
    return *it;
}

template <class T>
int Container<T>::size() const {
    if(!item) return 0;
    int size =0;
    for(Container<T>::iterator it = begin(); it != end() ; it++) size++;
    return size;
}

template <class T>
const T Container<T>::at(int index) const{
    nodo* m = item;
    int conta = 0;
    while(m !=nullptr){
        if(conta ==index) return m->info;
        conta++; m = m->next;
    }
    return m->info;
}

template<class T>
void Container<T>::replace(int index, T t) {
        operator[](index) = t;
}
