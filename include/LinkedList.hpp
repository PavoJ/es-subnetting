/*
  Per il funzionamento corretto della lista, bisogna includere anche LinkedList.cpp
*/

#ifndef PILA_H
#define PILA_H

#include<iostream>
#include<functional>

namespace pavoLibs{
  template<typename T>
  struct dato
  {
    dato(T val, dato<T>* next);

    T val;
    dato<T>* next;
  };

  template<typename T>
  class LinkedList
  {
    private:
      dato<T>* first;
      dato<T>* last;
      int len;

      static void insertAtS(dato<T>* dat, int index, T val);
    public:
      LinkedList();
      LinkedList(const LinkedList<T>& ll);
      LinkedList(T val, dato<T>* next);
      ~LinkedList();
      
      void sort(std::function<bool(T v1, T v2)> compare);

      dato<T>* getData();
      dato<T>* getData() const;
      int length() const;

      void push(T val); // inserimento di un valore in coda
      //T& pop(); // lettura e estrazione in coda
      void insertAt(int index, T val); // inserimento in posizione index
      T extract(int index); // eliminazione senza lettura
      T& operator[](int index); // lettura in posizione index
  };
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, pavoLibs::LinkedList<T>& sll){
    stream << "[";
    int len;
    for(int i=0;i<(len=sll.length());i++){
        stream << sll[i] << (i!=len-1?", ":"");
    }
    stream << "]";

    return stream;
}

#endif // PILA_H
