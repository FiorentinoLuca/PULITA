
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual
  ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer& operator=(const DictionaryContainer&) = delete;
  
  // Move assignment
  DictionaryContainer& operator=( DictionaryContainer&&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual
  bool Insert(const Data&) = 0;

  virtual
  bool Insert(Data&&) = 0;
  
  virtual
  bool Remove(const Data&) = 0;
  
  virtual
  bool InsertAll(const TraversableContainer<Data> &); 
  
  virtual
  bool InsertAll(MappableContainer<Data>&&);

  virtual
  bool RemoveAll(const TraversableContainer<Data>&);
  
  virtual
  bool InsertSome(const TraversableContainer<Data>&);
  
  virtual
  bool InsertSome(MappableContainer<Data>&&);
  
  virtual
  bool RemoveSome(const TraversableContainer<Data>&);

};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : virtual public DictionaryContainer<Data> {
  // Must extend DictionaryContainer<Data>

private:

protected:

public:

  // Destructor
  virtual
  ~OrderedDictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer<Data>& operator=(const MappableContainer<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MappableContainer<Data>& operator=(MappableContainer<Data>&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual
  const Data& Min() const = 0; // (concrete function must throw std::length_error when empty)
  virtual
  Data MinNRemove() = 0; // (concrete function must throw std::length_error when empty)
  virtual
  void RemoveMin() = 0; // (concrete function must throw std::length_error when empty)
  
  virtual
  const Data& Max() const = 0; // (concrete function must throw std::length_error when empty)
  virtual
  Data MaxNRemove() = 0; // (concrete function must throw std::length_error when empty)
  virtual
  void RemoveMax() = 0; // (concrete function must throw std::length_error when empty)

  virtual
  const Data& Predecessor(const Data&) const = 0; // (concrete function must throw std::length_error when not found)
  virtual
  Data PredecessorNRemove(const Data&) = 0; // (concrete function must throw std::length_error when not found)
  virtual
  void RemovePredecessor(const Data&) = 0; // (concrete function must throw std::length_error when not found)

  virtual
  const Data& Successor(const Data&) const = 0; // (concrete function must throw std::length_error when not found)
  virtual
  Data SuccessorNRemove(const Data&) = 0; // (concrete function must throw std::length_error when not found)
  virtual
  void RemoveSuccessor(const Data&) = 0; // (concrete function must throw std::length_error when not found)

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
