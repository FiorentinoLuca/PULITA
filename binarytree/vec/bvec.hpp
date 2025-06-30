
#ifndef BVEC_HPP
#define BVEC_HPP

/* ************************************************************************** */

#include "../btree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */


template <typename Data>
class BVecT;

template <typename Data>
class BVecTInOrderIt: virtual public Iterator<Data> {

private:

protected:

BVecT<Data> &root;
BTree<Data> *current;

public:

  BVecTInOrderIt(BVecT<Data>&);

  virtual
  ~BVecTInOrderIt();

  bool IsTerminated() const noexcept override;

  Data operator*() override;

  Iterator<Data>& operator++() override;

  Iterator<Data>& operator+(int idx) override;

  int operator-(Iterator<Data>& other) override;

  void Reset() override;

protected:

  BTree<Data>& LeftMostNode();

};

template <typename Data>
class BVecT: virtual public BTree<Data> {

private:

protected:

  ulong idx;
  ulong size;
  BvecTRoot* nodes;

public:

  struct BvecTRoot : virtual protected Vector<Data>
  {

  protected:
    
    BVecTRoot(ulong);

  public:
  
    ~BVectTRoot();
  };
  
  // Default constructor
  BVecT() = default;

  // Specific constructor
  BVecT(const LinearContainer<Data>&);
  BVecT(MutableLinearContainer<Data>&&);
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

  bool HasLeft() const noexcept override;
  bool HasRight() const noexcept override;

  const Data& Element() const& override;
  Data& Element() & override;
  Data&& Element() && override;

  const Data& operator[](ulong) const override; // (non-mutable version; must throw std::out_of_range when out of range)
  Data& operator[](ulong) override; // (mutable version; must throw std::out

  /* ************************************************************************ */

protected:

  // Specific member functions
  using Vector<Data>::buffer;
  using BTree<Data>::InOrderMappingThrough;
  using Container::Empty;

  friend void ::mytest();
  friend class BVecTInOrderIt<Data>;
  
};



} // namespace lasd

#include "bvec.cpp"

#endif // BVEC_HPP