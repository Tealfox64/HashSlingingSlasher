/***********************************************************************
* Module:
*    Week 12, Hash
*    Brother Ercanbrack, CS 235
* Author:
*    Matthias Bruveleit
* Summary:
*    This will implement a simple hash
************************************************************************/
#ifndef HASH_H
#define HASH_H

#include <list>

template<class T>
class Hash
{
public:
   Hash() throw (const char *);
   Hash(int numBuckets) throw (const char *);
   Hash(const Hash<T> & rhs) throw (const char *);
   ~Hash();

   Hash<T> & operator = (const Hash<T> & rhs) throw (const char *);

   bool empty()    const { return (numItems == 0); }
   int  size()     const { return numItems; }
   int  capacity() const { return numBuckets; }
   
   void clear();
   
   bool find(T value);
   void insert(T value);
   
   virtual int hash(const T & value) const = 0;

   std::list<T> getList(int index) const;

private:
   std::list<T> * hashArray;
   int numBuckets;
   int numItems;
   int hashKey;

};

#endif //HASH_H

 /**************************************
 * CONSTRUCTORS
 * Initialize the size of the hash array
 **************************************/
template<class T>
Hash<T>::Hash() throw (const char *)
{
   try
   {
      hashArray = new std::list<T>[256];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }

   numBuckets = 256;
   numItems = 0;
}

template<class T>
Hash<T>::Hash(int numBuckets) throw (const char *)
{
   try
   {
      hashArray = new std::list<T>[numBuckets];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }

   this->numBuckets = numBuckets;
   numItems = 0;
}

template<class T>
Hash<T>::Hash(const Hash<T>& rhs) throw (const char *)
{
   try
   {
      hashArray = new std::list<T>[rhs.capacity()];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }

   numBuckets = rhs.capacity();
   numItems = rhs.size();

   for (int i = 0; i < numBuckets; i++)
   {
      hashArray[i] = rhs.hashArray[i];
   }

}

/**************************************
* DESTRUCTOR
* Delete all the elements in the hash
**************************************/
template<class T>
Hash<T>::~Hash()
{
   if (hashArray != NULL)
   {
      delete[] hashArray;
      hashArray = NULL;
      numBuckets = 0;
      numItems = 0;
   }
}

/**************************************
* = OPERATOR
* Copy one Hash into another
**************************************/
template<class T>
Hash<T>& Hash<T>::operator=(const Hash<T>& rhs) throw(const char *)
{
   if (!(rhs.empty()))
   {
      delete[] hashArray;
      // hashArray = NULL
      numBuckets = 0;
      numItems = 0;
   }

   try
   {
      hashArray = new std::list<T>[rhs.capacity()];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }

   numBuckets = rhs.capacity();
   numItems = rhs.size();

   for (int i = 0; i < numBuckets; i++)
   {
      hashArray[i] = rhs.hashArray[i];
   }

   return *this;
}

/**************************************
* CLEAR
* Deletes the items of each linked list
**************************************/
template<class T>
void Hash<T>::clear()
{
   for (int i = 0; i < numBuckets; i++)
   {
      if (!(hashArray[i].empty))
         hashArray[i].clear();
   }
   numItems = 0;
}

/**************************************
* FIND
* Find will call hash to get the key for
* the value. The key will be the index
* of the array, and the list within will
* be searched for the value
**************************************/
template<class T>
bool Hash<T>::find(T value)
{
   hashKey = hash(value);
   for (typename std::list<T>::iterator it = hashArray[hashKey].begin(); it != hashArray[hashKey].end(); ++it)
   {
      if (*it == value)
         return true;
   }
   return false;
}

/**************************************
* INSERT
* Find will call hash to get the key for
* the value. The key will be the index
* of the array, and the value will be
* inserted into the list within the index
**************************************/
template<class T>
void Hash<T>::insert(T value)
{
   hashKey = hash(value);
   hashArray[hashKey].push_back(value);
   numItems++;
}

/**************************************
* GET LIST
* For the = operator, getList creates and
* sends out a copy of the list at a given
* index in the hash
**************************************/
template<class T>
std::list<T> Hash<T>::getList(int index) const
{
   std::list<T> newList;
   if (index < numBuckets)
   {
      newList = hashArray[index];
   }
      return newList;
}
