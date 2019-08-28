/*
 * Implement your functionality here without changing given test cases
 */

//-Assume Key_T and Mapped_T are copy constructible and destructible
//-Key_T has a less-than operator (<), and an equality operator (==),
// as free-standing functions (not member functions)
//-Mapped_T has an equality comparison (==). If operator< is invoked
// on Map objects, you may also assume that Mapped_T has operator<

//-You may not assume that either class has a default constructor or
// an assignment operator

//-Only assume that a Mapped_T that is used with operator[] may be
// default initialized

#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <cstdlib>
#include <stdexcept>
#include <stdio.h>
#include <utility>
#include <cstring>
#include <random>
#include <initializer_list>

//using namespace std;

namespace cs540
{

template <typename Key_T, typename Mapped_T>
using ValueType = std::pair<const Key_T, Mapped_T>;

template <typename Key_T, typename Mapped_T> class Node{
public:
    int level;
    ValueType<Key_T, Mapped_T> mapPair;

    //Pointers to arrays
    Node** forward;
    Node** backward;

    //Constructor
    Node(ValueType<Key_T, Mapped_T> mpair);
    Node(ValueType<Key_T, Mapped_T> mpair, int lvl);
    ~Node();

};

template <typename Key_T, typename Mapped_T> class Map{
private:
    int mapSize;
    //Determined by the size of the map (MaxLvl = log(mapSize)/log(p/2));
    const int MaxLvl = 32;
    //current level
    int level;
    float P;

    Node<Key_T, Mapped_T>* sentinel;
    Node<Key_T, Mapped_T>* tail;

public:
    //Iterator and its functions
    class ConstIterator;

    class Iterator{
    public:
        Node<Key_T, Mapped_T>* nodePtr;

        //constructor and destructor
        Iterator() = delete;
        Iterator(Node<Key_T, Mapped_T>* nd){
            nodePtr = nd;
        }
        Iterator(const Iterator &) = default;
        ~Iterator(){ };

        //operators
        //Iterator& operator=(const Iterator &);
        Iterator& operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);
        ValueType<Key_T, Mapped_T>& operator*() const;
        ValueType<Key_T, Mapped_T>* operator->() const;

        //comparison functions
        /*
        friend bool operator==(const Iterator &, const Iterator &);
        friend bool operator==(const Iterator &, const ConstIterator &);
        friend bool operator==(const ConstIterator &, const Iterator &);
        friend bool operator!=(const Iterator &, const Iterator &);
        friend bool operator!=(const Iterator &, const ConstIterator &);
        friend bool operator!=(const ConstIterator &, const Iterator &);
        */
        //non-template friend comparison functions
        //automatically created for each template instantiation of some class

        friend bool operator==(const Iterator &it1, const Iterator &it2){
            bool retVal = false;
            if(it1.nodePtr == nullptr && it2.nodePtr == nullptr){
                retVal = true;
            } else{
                retVal = (it1.nodePtr == it2.nodePtr);
            }
            return retVal;
        }
        friend bool operator==(const Iterator &it1, const ConstIterator &cit2){
            bool retVal = false;
            if(it1.nodePtr == nullptr && cit2.nodePtr == nullptr){
                retVal = true;
            } else{
                retVal = (it1.nodePtr == cit2.nodePtr);
            }
            return retVal;
        }
        friend bool operator==(const ConstIterator &cit1, const Iterator &it2){
            bool retVal = false;
            if(cit1.nodePtr == nullptr && it2.nodePtr == nullptr){
                retVal = true;
            } else{
                retVal = (cit1.nodePtr == it2.nodePtr);
            }
            return retVal;
        }
        friend bool operator!=(const Iterator &it1, const Iterator &it2){
            return (!(it1.nodePtr == it2.nodePtr));
        }
        friend bool operator!=(const Iterator &it1, const ConstIterator &cit2){
            return (!(it1.nodePtr == cit2.nodePtr));
        }
        friend bool operator!=(const ConstIterator &cit1, const Iterator &it2){
            return (!(cit1.nodePtr == it2.nodePtr));
        }

    };

    //ConstIterator and its functions
    class ConstIterator{
    public:
        Node<Key_T, Mapped_T>* nodePtr;

        //constructors and destructor
        ConstIterator() = delete;
        ConstIterator(Node<Key_T, Mapped_T>* nd){
            nodePtr = nd;
        };
        ConstIterator(const ConstIterator &) = default;
        ConstIterator(const Iterator &);
        ~ConstIterator(){ };

        //operators
        //ConstIterator& operator=(const ConstIterator &);
        ConstIterator& operator++();
        ConstIterator operator++(int);
        ConstIterator& operator--();
        ConstIterator operator--(int);
        const ValueType<Key_T, Mapped_T>& operator*() const;
        const ValueType<Key_T, Mapped_T>* operator->() const;

        //comparison functions
        friend bool operator==(const ConstIterator &cit1, const ConstIterator &cit2){
            bool retVal = false;
            if(cit1.nodePtr == nullptr && cit2.nodePtr == nullptr){
                retVal = true;
            } else{
                retVal = (cit1.nodePtr == cit2.nodePtr);
            }
            return retVal;
        }
        /*
        friend bool operator==(const Iterator &it1, const ConstIterator &cit2){
            bool retVal = false;
            if(it1.nodePtr == nullptr && cit2.nodePtr == nullptr){
                retVal = true;
            } else{
                retVal = (it1.nodePtr == cit2.nodePtr);
            }
            return retVal;
        }

        friend bool operator==(const ConstIterator &cit1, const Iterator &it2){
            bool retVal = false;
            if(cit1.nodePtr == nullptr && it2.nodePtr == nullptr){
                retVal = true;
            } else{
                retVal = (cit1.nodePtr == it2.nodePtr);
            }
            return retVal;
        }
        */
        friend bool operator!=(const ConstIterator &cit1, const ConstIterator &cit2){
            return (!(cit1.nodePtr == cit2.nodePtr));
        }
        /*
        friend bool operator!=(const Iterator &it1, const ConstIterator &cit2){
            return (!(it1.nodePtr == cit2.nodePtr));
        }

        friend bool operator!=(const ConstIterator &cit1, const Iterator &it2){
            return (!(cit1.nodePtr == it2.nodePtr));
        }
        */
    };

    //ReverseIterator and its functions
    class ReverseIterator{
    public:
        Node<Key_T, Mapped_T>* nodePtr;

        ReverseIterator() = delete;
        ReverseIterator(Node<Key_T, Mapped_T>* nd){
            nodePtr = nd;
        }
        ReverseIterator(const ReverseIterator &) = default;
        ~ReverseIterator(){ };

        //operators
        //ReverseIterator& operator=(const ReverseIterator &);
        ReverseIterator& operator++();
        ReverseIterator operator++(int);
        ReverseIterator &operator--();
        ReverseIterator operator--(int);
        ValueType<Key_T, Mapped_T>& operator*() const;
        ValueType<Key_T, Mapped_T>* operator->() const;

        //comparison
        friend bool operator==(const ReverseIterator &rit1, const ReverseIterator &rit2){
            bool retVal = false;
            if(rit1.nodePtr == nullptr && rit2.nodePtr == nullptr){
                retVal = true;
            } else{
                retVal = (rit1.nodePtr == rit2.nodePtr);
            }
            return retVal;
        }
        friend bool operator!=(const ReverseIterator &rit1, const ReverseIterator &rit2){
            return (!(rit1.nodePtr == rit2.nodePtr));
        }
    };
    //Constructors and Assignment Operator
    Map();
    Map(const Map &);
    Map &operator=(const Map &);
    Map(std::initializer_list<std::pair<const Key_T, Mapped_T> >);
    ~Map();

    //Size
    size_t size() const;
    bool empty() const;
    int randomLvl();

    //Iterators
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    ReverseIterator rbegin();
    ReverseIterator rend();

    //Element Access
    Iterator find(const Key_T &);
    ConstIterator find(const Key_T &) const;
    Mapped_T& at(const Key_T &);
    const Mapped_T& at(const Key_T &) const;
    Mapped_T &operator[](const Key_T &);

    //Modifiers
    std::pair<typename Map<Key_T, Mapped_T>::Iterator, bool> insert(const ValueType<Key_T, Mapped_T> &);
    template <typename IT_T> void insert(IT_T range_beg, IT_T range_end);
    void erase(Iterator pos);
    void erase(const Key_T &);
    void clear();

    //comparison operators for map
    friend bool operator==(const Map &m1, const Map &m2){
        bool retVal = false;
        //if mapSize different then false
        if(m1.mapSize == m2.mapSize){
            ConstIterator cit1 = m1.begin();
            ConstIterator cit2 = m2.begin();
            while(cit1 != m1.end() && cit2 != m2.end()){
                if(*cit1 != *cit2) return retVal;
                cit1++;
                cit2++;
            }
            retVal = true;
        }
        return retVal;
    }
    friend bool operator!=(const Map &m1, const Map &m2){
        bool retVal = (m1 == m2);
        return !retVal;
    }
    friend bool operator<(const Map &m1, const Map &m2){
        bool lessThan = false;
        bool equalMaps = true;
        ConstIterator cit1 = m1.begin();
        ConstIterator cit2 = m2.begin();
        while(cit1 != m1.end() && cit2 != m2.end()){
            if(*cit1 < *cit2) lessThan = true;
            if(*cit2 != *cit1) equalMaps = false;
            cit1++;
            cit2++;
        }
        if(lessThan) return lessThan;
        if(equalMaps && m1.mapSize < m2.mapSize) return true;
        return false;

    }
};

/*----------------------------------------------------------------
                        Node Functions
----------------------------------------------------------------*/

template <typename Key_T, typename Mapped_T>
Node<Key_T, Mapped_T>::Node(ValueType<Key_T, Mapped_T> mpair): mapPair(mpair) {
    mapPair = nullptr;
    level = 32;

    //allocate memory for circular array
    forward = new Node*[level+1];
    backward = new Node*[level+1];

    //fill array with null
    memset(forward, 0, sizeof(Node*)*(level+1));
    memset(backward, 0, sizeof(Node*)*(level+1));
}

template <typename Key_T, typename Mapped_T>
Node<Key_T, Mapped_T>::Node(ValueType<Key_T, Mapped_T> mpair, int lvl) : mapPair(mpair) {
    //mapPair = mpair; gives me error since operator= is a deleted function
    level = lvl;

    //allocate memory for circular array
    forward = new Node*[lvl+1];
    backward = new Node*[level+1];

    //fill array with null
    memset(forward, 0, sizeof(Node*)*(lvl+1));
    memset(backward, 0, sizeof(Node*)*(level+1));
}

template <typename Key_T, typename Mapped_T>
Node<Key_T, Mapped_T>::~Node(){
    //delete forward and backward arrays
    if(forward != nullptr){
        delete [] forward;
        forward = NULL;
    }
    if(backward != nullptr){
        delete [] backward;
        backward = NULL;
    }
}


/*----------------------------------------------------------------
                        Operator Declarations
----------------------------------------------------------------*/

//comparison operators for Map
template <typename Key_T, typename Mapped_T>
bool operator==(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);
template <typename Key_T, typename Mapped_T>
bool operator!=(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);
template <typename Key_T, typename Mapped_T>
bool operator<(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);

//comparison operators for Iterators
template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::Iterator &, const typename Map<Key_T, Mapped_T>::Iterator &);
template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::ConstIterator &, const typename Map<Key_T, Mapped_T>::ConstIterator &);
template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::Iterator &, const typename Map<Key_T, Mapped_T>::ConstIterator &);
template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::ConstIterator &, const typename Map<Key_T, Mapped_T>::Iterator &);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::Iterator &, const typename Map<Key_T, Mapped_T>::Iterator &);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::ConstIterator &, const typename Map<Key_T, Mapped_T>::ConstIterator &);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::Iterator &, const typename Map<Key_T, Mapped_T>::ConstIterator &);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::ConstIterator &, const typename Map<Key_T, Mapped_T>::Iterator &);
//Reverse
template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::ReverseIterator &, const typename Map<Key_T, Mapped_T>::ReverseIterator &);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::ReverseIterator &, const typename Map<Key_T, Mapped_T>::ReverseIterator &);

/*----------------------------------------------------------------
                    Function Definitions for Map
----------------------------------------------------------------*/

//Constructors and Assignment Operators-----
template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Map() {
    P = 0.5;
    //32 allows to have performance O(lg(N)) for a list of up to 2^32 elements
    //Reasonable overestimation of size of input
    mapSize = 0;
    level = 0;

    sentinel = nullptr;
    tail = nullptr;
}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Map(const Map<Key_T, Mapped_T> &mapToCopy){
    P = mapToCopy.P;
    //MaxLvl = (int) ceil(log(mapToCopy.mapSize)/log(2));
    mapSize = 0;
    level = 0;

    sentinel = nullptr;
    tail = nullptr;
    //cannot simply copy map because if other map is deleted I still want access to the contents
    ConstIterator it = mapToCopy.begin();
    while(it != mapToCopy.end()){
        insert(*it);
        it++;
    }
}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>& Map<Key_T, Mapped_T>::operator=(const Map<Key_T, Mapped_T> &mapToCopy){
    //handle self assesment
    if(&mapToCopy == this){
        return *this;
    }
    P = mapToCopy.P;
    //MaxLvl = (int) ceil(log(mapToCopy.mapSize)/log(2));
    if(mapSize > 0) this->clear();
    if(sentinel != nullptr){
        delete sentinel;
    }
    if(tail != nullptr){
        delete tail;
    }
    mapSize = 0;
    level = 0;

    sentinel = nullptr;
    tail = nullptr;
    //cannot simply copy map because if other map is deleted I still want access to the contents
    ConstIterator it = mapToCopy.begin();
    while(it != mapToCopy.end()){
        insert(*it);
        it++;
    }
    //update this map and return it
    return *this;
}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Map(std::initializer_list<std::pair<const Key_T, Mapped_T> > il){
    P = 0.5;
    //MaxLvl = (int) ceil(log(il.size())/log(2));
    mapSize = 0;
    level = 0;

    sentinel = nullptr;
    tail = nullptr;
    //need to insert list elements one by one
    typename std::initializer_list<std::pair<const Key_T, Mapped_T> >::iterator it = il.begin();
    while(it != il.end()){
        insert(*it);
        it++;
    }
}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::~Map(){
    if(mapSize != 0){
        clear();
    }
    if(sentinel != nullptr){
        delete sentinel;
        sentinel = NULL;
    }
    if(tail != nullptr){
        //delete tail;
        tail = NULL;
    }
}

template <typename Key_T, typename Mapped_T>
int Map<Key_T, Mapped_T>::randomLvl(){
    float r;
    int lvl = 0;
    while((r = (float)rand()/RAND_MAX) < P && lvl < MaxLvl){
        lvl++;
    }
    return lvl;
}

//Size--------------------------------------
template <typename Key_T, typename Mapped_T>
size_t Map<Key_T, Mapped_T>::size() const {
    return mapSize;
}

template <typename Key_T, typename Mapped_T>
bool Map<Key_T, Mapped_T>::empty() const {
    //bool retVal = false;
    //if(mapSize == 0) retVal = true;
    return (mapSize == 0);
}

//Iterators---------------------------------
//Iterator

// template <typename Key_T, typename Mapped_T>
// Map<Key_T, Mapped_T>::Iterator::Iterator(Node<Key_T, Mapped_T>* nd){
//     //first element in the map at lowest level
//     //tempIt->nodePtr = head;
//     nodePtr = nd;
// }

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::begin(){
    //first element in the map at lowest level
    //tempIt->nodePtr = head;
    if(mapSize == 0){
        return Iterator(sentinel);
    }
    return (Iterator(sentinel->forward[0]));
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::end(){

        //tail = last element
        //one past the last element
        //tail->forward[0] == sentinel
    return (Iterator(sentinel));
}

//Const
//Iterator

// template <typename Key_T, typename Mapped_T>
// Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(Node<Key_T, Mapped_T>* nd){
//     //first element in the map at lowest level
//     //tempIt->nodePtr = head;
//     nodePtr = nd;
// }

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::begin() const {
    //first element in the map at lowest level
    //tempIt->nodePtr = head->forward[0];
    return ConstIterator(sentinel->forward[0]);
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::end() const {
    //tail = last element
    //one past the last element
    return ConstIterator(sentinel);
}

//Reverse
// template <typename Key_T, typename Mapped_T>
// Map<Key_T, Mapped_T>::ReverseIterator::ReverseIterator(Node<Key_T, Mapped_T>* nd){
//     //first element in the map at lowest level
//     //tempIt->nodePtr = head;
//     nodePtr = nd;
// }

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rbegin(){
    return ReverseIterator(tail);

}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rend(){
    //one before the first element
    return ReverseIterator(sentinel);
}

//Element Access---------------------------------
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::find(const Key_T &k){
    Iterator tempIt = begin();
    Node<Key_T, Mapped_T>* retNode = sentinel;
    Node<Key_T, Mapped_T>* nextNode = sentinel->forward[level];
    bool found = false;

    for(int i = level; i >=0; --i){
        if(retNode != nullptr){
            nextNode = retNode->forward[i];
        }
        while(nextNode != sentinel){
            //if we havent found the key move forward
            if(nextNode->mapPair.first < k || nextNode->mapPair.first == k){
                retNode = nextNode;
            } else{
                break;
            };
            //update nextNode to following node
            nextNode = retNode->forward[i];
        }
        if(retNode != nullptr){
            //if keys match set iterator's nodePtr to found node*
            if(retNode->mapPair.first == k){
                tempIt.nodePtr = retNode;
                found = true;
                break;
            }
        }
    }
    if(found == false){
        //if not found return iterator to one past last element
        tempIt.nodePtr = sentinel;
    }
    return tempIt;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::find(const Key_T &k) const {
    ConstIterator tempIt = begin();
    Node<Key_T, Mapped_T>* retNode = sentinel;
    Node<Key_T, Mapped_T>* nextNode = sentinel->forward[level];
    bool found = false;

    for(int i = level; i >=0; --i){
        if(retNode != nullptr){
            nextNode = retNode->forward[i];
        }
        while(nextNode != sentinel){
            //if we havent found the key move forward
            if(nextNode->mapPair.first < k || nextNode->mapPair.first == k){
                retNode = nextNode;
            } else{
                break;
            };
            //update nextNode to following node
            nextNode = retNode->forward[i];
        }
        if(retNode != nullptr){
            //if keys match set iterator's nodePtr to found node*
            if(retNode->mapPair.first == k){
                tempIt.nodePtr = retNode;
                found = true;
                break;
            }
        }
    }
    if(found == false){
        //if not found return iterator to one past last element
        tempIt.nodePtr = sentinel;
    }
    return tempIt;
}

template <typename Key_T, typename Mapped_T>
Mapped_T& Map<Key_T, Mapped_T>::at(const Key_T &k){
    Node<Key_T, Mapped_T>* retNode = sentinel;
    Node<Key_T, Mapped_T>* nextNode = sentinel;
    bool found = false;

    for(int i = level; i >=0; --i){
        if(retNode != nullptr){
            nextNode = retNode->forward[i];
        }
        while(nextNode != sentinel){
            //if we havent found the key move forward
            if(nextNode->mapPair.first < k || nextNode->mapPair.first == k){
                retNode = nextNode;
            } else{
                break;
            };
            //update nextNode to following node
            nextNode = retNode->forward[i];
        }
        if(retNode != nullptr){
            //if keys match set iterator's nodePtr to found node*
            if(retNode->mapPair.first == k){
                found = true;
                break;
            }
        }
    }
    if(found == false){
        throw std::out_of_range("Key is not in the map.");
    }
    return retNode->mapPair.second;
}

template <typename Key_T, typename Mapped_T>
const Mapped_T& Map<Key_T, Mapped_T>::at(const Key_T &k) const {
    Node<Key_T, Mapped_T>* retNode = sentinel;
    Node<Key_T, Mapped_T>* nextNode = sentinel->forward[level];
    bool found = false;

    for(int i = level; i >=0; --i){
        if(retNode != nullptr){
            nextNode = retNode->forward[i];
        }
        while(nextNode != sentinel){
            //if we havent found the key move forward
            if(nextNode->mapPair.first < k || nextNode->mapPair.first == k){
                retNode = nextNode;
            } else{
                break;
            };
            //update nextNode to following node
            nextNode = retNode->forward[i];
        }
        if(retNode != nullptr){
            //if keys match set iterator's nodePtr to found node*
            if(retNode->mapPair.first == k){
                found = true;
                break;
            }
        }
    }
    if(found == false){
        throw std::out_of_range("Key is not in the map.");
    }
    return retNode->mapPair.second;
}

template <typename Key_T, typename Mapped_T>
Mapped_T& Map<Key_T, Mapped_T>::operator[](const Key_T &k){
    // pair<typename Map<Key_T, Mapped_T>::Iterator, bool> tempPair;
    // Iterator tempIt = find(k);
    // bool found = false;
    // if(tempIt.nodePtr->mapPair.first != sentinel->mapPair.first){
    //     found = true;
    // }
    // if(found == false){
    //     if(mapSize == 0){
    //         tail = nullptr;
    //     }
    //     //create object and insert it then store its node
    //     ValueType<Key_T, Mapped_T> tempVT (k, Mapped_T());
    //     tempPair = insert(tempVT);
    //     tempIt.nodePtr = tempPair.first.nodePtr;
    // }
    // return tempIt.nodePtr->mapPair.second;
    ValueType<Key_T, Mapped_T> tempVT (k, Mapped_T());
    std::pair<typename Map<Key_T, Mapped_T>::Iterator, bool> tempPair = insert(tempVT);
    //if we try to insert an existing element it simply will return a pair
    //containing the existing element and "false" we can just send a reference to that
    //if the element was not in the map then it is inserted and we are still
    //returning what we are supposed to in the next line
    return ((*tempPair.first).second);
}

//Modifiers---------------------------------
template <typename Key_T, typename Mapped_T>
std::pair<typename Map<Key_T, Mapped_T>::Iterator, bool> Map<Key_T, Mapped_T>::insert(const ValueType<Key_T, Mapped_T> &vt){
    if(empty()){
        //if it is empty the memory being pointed to should be deallocated
        /*
        if(head != nullptr){
            delete head;
            head = NULL;
        }
        if(tail != nullptr){
            delete tail;
            tail = NULL;
        }
        if(sentinel != nullptr){
            delete sentinel;
            sentinel = NULL;
        }
        */
        //there is only one element so head and tail both point to it
        if(tail == nullptr){
            sentinel = new Node<Key_T, Mapped_T>(vt, MaxLvl);
            for(int i = MaxLvl; i >= 0; i--){
                sentinel->forward[i] = sentinel;
                sentinel->backward[i] = sentinel;
            }
        }
    }
    Iterator it = begin();
    Node<Key_T, Mapped_T>* retNode;
    Node<Key_T, Mapped_T>* current = sentinel;

    //creates update array and sets allocated memory to 0
    Node<Key_T, Mapped_T>* update[35];
    memset(update, 0, sizeof(Node<Key_T, Mapped_T>*)*(MaxLvl+1));

    for(int i = level; i>=0; i--){
        while((current->forward[i] != sentinel)){
            if(current->forward[i]->mapPair.first < vt.first){
                current = current->forward[i];;
            } else{
                break;
            }
        }
        update[i] = current;
    }

    current = current->forward[0];

    if(current != nullptr && current != sentinel){
        if(current->mapPair.first == vt.first){
            //element already exists
            it.nodePtr = current;
            std::pair<Map<Key_T, Mapped_T>::Iterator, bool> itBoolPair = std::make_pair(std::move(it), false);
            return itBoolPair;
        }
    }
    int rlvl = randomLvl();
    if(rlvl > level){
        //update level for values between old and new level
        for(int i = level+1; i<rlvl+1; i++){
            update[i] = sentinel;
        }
        level = rlvl;
    }
    retNode = new Node<Key_T, Mapped_T>(vt, rlvl);

    for(int i = 0; i<=rlvl; i++){
        retNode->backward[i] = update[i];
        update[i]->forward[i]->backward[i] = retNode;
        retNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = retNode;

    }
    tail = sentinel->backward[0];
    it.nodePtr = retNode;
    mapSize++;
    //move contents, don't just copy them
    std::pair<Map<Key_T, Mapped_T>::Iterator, bool> itBoolPair = std::make_pair(std::move(it), true);
    return itBoolPair;
}

template <typename Key_T, typename Mapped_T>
template <typename IT_T>
void Map<Key_T, Mapped_T>::insert(IT_T range_beg, IT_T range_end){
    while(range_beg != range_end){
        ValueType<Key_T, Mapped_T> tempVt = range_beg.nodePtr->mapPair;
        insert(tempVt);
        range_beg++;
    }
}

template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::erase(Map<Key_T, Mapped_T>::Iterator pos){
    if(mapSize == 0 || pos.nodePtr == nullptr || pos.nodePtr == sentinel) return;
    mapSize--;
    for(int i = 0; i <= pos.nodePtr->level; i++){
        //back node of next should be back node of current
        pos.nodePtr->forward[i]->backward[i] = pos.nodePtr->backward[i];
        //next node of previous should be next node of current
        pos.nodePtr->backward[i]->forward[i] = pos.nodePtr->forward[i];
    }
    delete pos.nodePtr;
}

template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::erase(const Key_T &k){
    erase(find(k));
}

template <typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::clear(){
    Iterator it = begin();
    while(mapSize > 0){
        erase(it++);
    }
}

/*----------------------------------------------------------------
                Function Definitions for Iterator
----------------------------------------------------------------*/
/*
template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Iterator::Iterator(const Map<Key_T, Mapped_T>::Iterator &it){

}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Iterator::~Iterator(){

}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator=(const Map<Key_T, Mapped_T>::Iterator &it){

}
*/
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator++(){
    nodePtr = nodePtr->forward[0];
    //returns a reference to current object
    return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::Iterator::operator++(int){
    Iterator tempIt(*this);
    nodePtr = nodePtr->forward[0];
    return tempIt;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator--(){
    nodePtr = nodePtr->backward[0];
    //returns a reference to current object
    return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::Iterator::operator--(int){
    Iterator tempIt(*this);
    nodePtr = nodePtr->backward[0];
    return tempIt;
}

template <typename Key_T, typename Mapped_T>
ValueType<Key_T, Mapped_T>& Map<Key_T, Mapped_T>::Iterator::operator*() const {
    return (nodePtr->mapPair);
}

template <typename Key_T, typename Mapped_T>
ValueType<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::Iterator::operator->() const {
    return &(nodePtr->mapPair);
}

/*----------------------------------------------------------------
            Function Definitions for ConstIterator
----------------------------------------------------------------*/
/*
template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(const Map<Key_T, Mapped_T>::ConstIterator &it){

}
*/
template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(const Map<Key_T, Mapped_T>::Iterator &it){
    nodePtr = it.nodePtr;
}
/*
template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ConstIterator::~ConstIterator(){

}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ConstIterator& Map<Key_T, Mapped_T>::ConstIterator::operator=(const Map<Key_T, Mapped_T>::ConstIterator &it){

}
*/
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator& Map<Key_T, Mapped_T>::ConstIterator::operator++(){
    nodePtr = nodePtr->forward[0];
    //returns a reference to current object
    return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::ConstIterator::operator++(int){
    ConstIterator tempIt(*this);
    nodePtr = nodePtr->forward[0];
    return tempIt;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator& Map<Key_T, Mapped_T>::ConstIterator::operator--(){
    nodePtr = nodePtr->backward[0];
    //returns a reference to current object
    return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::ConstIterator::operator--(int){
    ConstIterator tempIt(*this);
    nodePtr = nodePtr->backward[0];
    return tempIt;
}

template <typename Key_T, typename Mapped_T>
const ValueType<Key_T, Mapped_T>& Map<Key_T, Mapped_T>::ConstIterator::operator*() const {
    return (nodePtr->mapPair);
}

template <typename Key_T, typename Mapped_T>
const ValueType<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::ConstIterator::operator->() const {
    return &(nodePtr->mapPair);
}

/*----------------------------------------------------------------
            Function Definitions for ReverseIterator
----------------------------------------------------------------*/
/*
template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ReverseIterator::ReverseIterator(const Map<Key_T, Mapped_T>::ReverseIterator &it){

}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ReverseIterator::~ReverseIterator(){

}

template <typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator=(const Map<Key_T, Mapped_T>::ReverseIterator &it){
}
*/
template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator++(){
    nodePtr = nodePtr->backward[0];
    //returns a reference to current object
    return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::ReverseIterator::operator++(int){
    ReverseIterator tempIt(*this);
    nodePtr = nodePtr->backward[0];
    return tempIt;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator--(){
    nodePtr = nodePtr->forward[0];
    //returns a reference to current object
    return *this;
}

template <typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::ReverseIterator::operator--(int){
    ReverseIterator tempIt(*this);
    nodePtr = nodePtr->forward[0];
    return tempIt;
}

template <typename Key_T, typename Mapped_T>
ValueType<Key_T, Mapped_T>& Map<Key_T, Mapped_T>::ReverseIterator::operator*() const {
    return (nodePtr->mapPair);
}

template <typename Key_T, typename Mapped_T>
ValueType<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::ReverseIterator::operator->() const {
    return &(nodePtr->mapPair);
}

/*----------------------------------------------------------------
            Comparison Operators for Iterators
----------------------------------------------------------------*/
/*
template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::Iterator &, const typename Map<Key_T, Mapped_T>::Iterator &){

}

template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::ConstIterator &, const typename Map<Key_T, Mapped_T>::ConstIterator &){

}

template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::Iterator &, const typename Map<Key_T, Mapped_T>::ConstIterator &){

}

template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::ConstIterator &, const typename Map<Key_T, Mapped_T>::Iterator &){

}

template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::Iterator &, const typename Map<Key_T, Mapped_T>::Iterator &){

}

template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::ConstIterator &, const typename Map<Key_T, Mapped_T>::ConstIterator &){

}

template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::Iterator &, const typename Map<Key_T, Mapped_T>::ConstIterator &){

}

template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::ConstIterator &, const typename Map<Key_T, Mapped_T>::Iterator &){

}

//Reverse
template <typename Key_T, typename Mapped_T>
bool operator==(const typename Map<Key_T, Mapped_T>::ReverseIterator &, const typename Map<Key_T, Mapped_T>::ReverseIterator &){

}

template <typename Key_T, typename Mapped_T>
bool operator!=(const typename Map<Key_T, Mapped_T>::ReverseIterator &, const typename Map<Key_T, Mapped_T>::ReverseIterator &){

}
*/

}//end of namespace

#endif
