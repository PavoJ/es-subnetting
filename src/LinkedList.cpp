#pragma once

/* 
    deve essere incluso anche questo sorgente per il corretto funzionamento della lista, 
    data la natura imprevedibile dei template.
*/

#include<LinkedList.hpp>
#include<FLSM.hpp>

namespace pavoLibs{

    // dato

    template<typename T>
    dato<T>::dato(T val, dato<T>* next): val(val), next(next){  }

    // LinkedList

    template<typename T>
    LinkedList<T>::LinkedList(){
        first = nullptr;
        last = nullptr;
        len = 0;
    }

    template<typename T>
    LinkedList<T>::LinkedList(const LinkedList<T>& ll){
        first = ll.getData();

        last = first;
        len = 0;
        while(last!=nullptr) {
            last = last->next;
            len++;
        }
    }

    template<typename T>
    LinkedList<T>::LinkedList(T val, dato<T>* next){
        first = new dato<T>(val, next);
        
        len=1;
        last = first;
        while(last->next != nullptr) {
            last = last->next;
            len++;
        }
    }
    
    template<typename T>
    LinkedList<T>::~LinkedList(){
        dato<T> *pnt;
        while(first!=nullptr){
            pnt = first;
            first = first->next;
            delete pnt;
        }
    }

    template<typename T>
    void LinkedList<T>::sort(std::function<bool(T v1, T v2)> compare){
        if(first == nullptr) return;

        std::function<void(dato<T>* d)> sorter = [&](dato<T>* d)->void{
            bool sorted = true;// parto con il presupposto che sia ordinato
            if(d->next == nullptr) return;
            else {
                dato<T>* tmpP = d;
                while(tmpP->next!=nullptr)
                {
                    if(compare(tmpP->val, tmpP->next->val)){
                        sorted = false;
                        T placeHolder = tmpP->val;
                        tmpP->val = tmpP->next->val;
                        tmpP->next->val = placeHolder;
                    }

                    tmpP = tmpP->next;
                }
                
            }
            if(!sorted) sorter(d);
        };

        sorter(first);
    }

    template<typename T>
    dato<T>* LinkedList<T>::getData(){ return first; }

    template<typename T>
    dato<T>* LinkedList<T>::getData() const
    {
        if(first==nullptr) return nullptr;

        dato<T>* newDato = new dato<T>(first->val, nullptr);
        dato<T>* tmpF = newDato;
        dato<T>* tmpP = first->next;

        while(tmpP!=nullptr){
            tmpF->next = new dato<T>(tmpP->val, nullptr);

            tmpF = tmpF->next;
            tmpP = tmpP->next;
        }
        
        return newDato;
    }

    template<typename T>
    int LinkedList<T>::length() const{ return len; }

    template<typename T>
    void LinkedList<T>::push(T val){
        len++;
        if(first == nullptr){
            first = new dato<T>(val, nullptr);
            last = first;
        }else{
            last->next = new dato<T>(val, nullptr);
            last = last->next;
        }
    }

    template<typename T>
    void LinkedList<T>::insertAtS(dato<T>* dat, int index, T val){
        if(index>0) LinkedList<T>::insertAtS(dat->next, index-1, val);
        else if(index==0) {
            dato<T>* t = new dato<T>(val, dat->next);
            dat.next = t;
        }
        return;// index<0
    }

    template<typename T>
    void LinkedList<T>::insertAt(int index, T val){ insertAt(first, index, val); index>=0?len++:false; }

    template<typename T>
    T LinkedList<T>::extract(int index){
        if(first==nullptr || index<0) return (T)0;

        dato<T> *pnt=this->first, *secondToLast=this->first;
        for(int i=0; i<index && pnt->next!=nullptr; i++) {
            pnt = pnt->next;
            if(i!=index-1) secondToLast=pnt;
        }

        //estraggo l'elemento richiesto
        dato<T>* retD = pnt;
        T ret = retD->val;

        //aggiorno la lista NB: la terza istruzione è un if, non un else if
        if(pnt->next!=nullptr)  secondToLast->next = pnt->next; 
        else                    this->last = pnt;
        if(pnt==secondToLast)   first = pnt->next;
        
        delete retD;
        this->len--;

        return ret;
    }

    template<typename T>
    T& LinkedList<T>::operator[](int index){
        dato<T>* ret = first;
        for(int i=0; i<index; i++) ret = ret->next;
        return ret->val;
    }

}

/*
template<typename T>
std::ostream& operator<<(std::ostream& stream, pavoLibs::LinkedList<T>& sll){
    stream << "[";
    pavoLibs::LinkedList<T> ls = pavoLibs::LinkedList<T>(sll);
    while(ls.len > 0){
        T toStream = ls.extract(ls.len-1);
        stream << toStream << ls.len!=1?", ":"";
    }
    stream << "]";

    return stream;
}*/