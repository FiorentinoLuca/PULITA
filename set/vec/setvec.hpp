
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>, virtual protected Vector<Data> {
  // Must extend Set<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  static const ulong initialSize;
  using Container::size;
  using Vector<Data>::buffer;
  ulong head = 0;
  ulong numElements = 0;

  // ...

public:

  // Default constructor
  SetVec();

  /* ************************************************************************ */

  // Specific constructors
  SetVec(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
  SetVec(MappableContainer<Data>&&); // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetVec(const SetVec<Data>&);

  // Move constructor
  SetVec(SetVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual
  ~SetVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  SetVec<Data>& operator=(const SetVec<Data>&);

  // Move assignment
  SetVec<Data>& operator=(SetVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetVec<Data>&) const noexcept;
  bool operator!=(const SetVec<Data>&) const noexcept; 

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty) 
  Data MinNRemove() override;  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  
  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  bool Insert(Data&&) noexcept override;  // Override DictionaryContainer member (move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[] (ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

  
  ulong Size() const noexcept override;
  
  void Traverse(typename TraversableContainer<Data>::TraverseFun) const override;

  using Container::Empty;

  using Set<Data>::InsertAll;
  using Set<Data>::RemoveAll;
  using Set<Data>::InsertSome;
  using Set<Data>::RemoveSome;
  using Set<Data>::Front;
  using Set<Data>::Back;

protected:

  // Auxiliary functions, if necessary!

  Data &operator[](ulong idx) override;
  ulong FindPred(const Data&);
  ulong FindSucc(const Data&);
  void EnsureCapacity(ulong) override;
  void Resize(ulong) override;
  void Transfer(SetVec<Data> &receiver, ulong srcStart, int grouping, ulong dstStart);
  bool isLefter(int);
  void Shift(int, int);
  const Data& getData(const int&) const;
  int Reach(int, ulong, int&) const;
  int BSearch(const Data&) const;

  using Vector<Data>::mod;
  using Set<Data>::card;
  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;

  friend class Set<Data>;

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
