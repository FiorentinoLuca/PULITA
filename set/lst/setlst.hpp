
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : virtual public Set<Data>, virtual protected List<Data> {
  // Must extend Set<Data>,
  //             List<Data>

private:

  // ...

protected:

  using Container::size;

  // ...

public:

  // Default constructor
  SetLst();

  /* ************************************************************************ */

  // Specific constructors
  SetLst(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
  SetLst(MappableContainer<Data>&&); // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetLst(const SetLst<Data>&);

  // Move constructor
  SetLst(SetLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual
  ~SetLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  SetLst<Data>& operator=(const SetLst<Data>&);

  // Move assignment
  SetLst<Data>& operator=(SetLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetLst<Data>&) const noexcept;
  bool operator!=(const SetLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
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
  bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

  void Traverse(typename TraversableContainer<Data>::TraverseFun) const override;

  using Set<Data>::InsertAll;
  using Set<Data>::RemoveAll;
  using Set<Data>::InsertSome;
  using Set<Data>::RemoveSome;
  using Set<Data>::Front;
  using Set<Data>::Back;

protected:

  // Auxiliary functions, if necessary!

  using List<Data>::head;
  using List<Data>::tail;
  using List<Data>::RemoveFromFront; // #TODO -> using List<Data>::RemoveFromFront;
  using typename List<Data>::Node; // #TODO -> using typename List<Data>::Node;

  using Node = typename List<Data>::Node;
  const Data& getData(typename List<Data>::Node**) const;
  Node** Reach(Node **, ulong, Node**& ) const;
  Node** BSearch(const Data&) const;

  virtual
  Node** FindPred(const Data& dat);
  virtual
  Node** FindSucc(const Data& dat);

  
  using List<Data>::operator[];
  using List<Data>::Clear;
  using Container::Empty;


  friend class Set<Data>;

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif
