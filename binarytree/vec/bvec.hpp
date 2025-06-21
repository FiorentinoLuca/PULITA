
#ifndef BVEC_HPP
#define BVEC_HPP

/* ************************************************************************** */

#include "../btree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BVecT: virtual public BTree<Data>, virtual protected Vector<Data> {

private:

protected:

  ulong rootIdx;
  Vector<bool> areNodes;

public:

  // Default constructor
  BVecT();

  // Specific constructor
  BVecT(const TraversableContainer<Data>&);
  BVecT(MappableContainer<Data>&&);
  BVecT(const BVecT<Data>&);
  BVecT(BVecT<Data>&&);
  BVecT(const Data& dat);
  BVecT(Data&& dat);
  
  // Destructor
  virtual
  ~BVecT() = default;

  /* ************************************************************************ */

  // Copy assignment
  BVecT<Data>& operator=(const BVecT<Data>&);
  // Move assignment
  BVecT<Data>& operator=(BVecT<Data>&&);

  /* ************************************************************************ */
  
  const BTree<Data>& L() const override;
  const BTree<Data>& R() const override;

  BTree<Data>& L() override;
  BTree<Data>& R() override;

  void InsertBefore(const Data&, ulong) override;
  void InsertBefore(Data&&, ulong) override;

  void InsertAfter(const Data&, ulong) override;
  void InsertAfter(Data&&, ulong) override;

  const Data& operator[](ulong) const override; // (non-mutable version; must throw std::out_of_range when out of range)
  Data& operator[](ulong) override; // (mutable version; must throw std::out

  /* ************************************************************************ */

protected:

  // Specific member functions
  ulong calcLeftIdx(ulong);
  ulong calcRightIdx(ulong);
  using Vector<Data>::buffer;
  
};

} // namespace lasd

#include "bvec.cpp"

#endif // BVEC_HPP