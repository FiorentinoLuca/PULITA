
#ifndef SET_HPP
#define SET_HPP

/* ************************************************************************** */

#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Set : virtual public OrderedDictionaryContainer<Data>,
  virtual public LinearContainer<Data>, virtual public ClearableContainer {
  // Must extend OrderedDictionaryContainer<Data>,
  //             LinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual
  ~Set() = default;

  /* ************************************************************************ */

  // Copy assignment
  Set<Data>& operator=(const Set<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Set<Data>& operator=(Set<Data>&&) = delete; // Move assignment of abstract types is not possible.


  bool InsertAll(const TraversableContainer<Data> &box) override
  {

    if (this == &box)
        return false;

    bool check = true;
    box.Traverse(
      [this, &check](const Data &dat)
      {
        check = (this->Insert(dat) && check);
      }
    );
    return check;
  }

  bool RemoveAll(const TraversableContainer<Data> &box) override
  {

    if (this == &box)
    {
      Clear();
      return true;
    }

    bool check = true;
    box.Traverse(
      [this, &check](const Data &dat)
      {
        check = (this->Remove(dat) && check);
      }
    );
    return check;
  }

  bool InsertSome(const TraversableContainer<Data> &box) override
  {

    if (this == &box)
        return false;

    bool check = false;
    box.Traverse(
      [this, &check](const Data &dat)
      {
          check = (this->Insert(dat) || check);
      }
    );
    return check;
  }

  bool RemoveSome(const TraversableContainer<Data> &box) override
  {

    if (this == &box)
    {
      Clear();
      return true;
    }

    bool check = false;
    box.Traverse(
      [this, &check](const Data &dat)
      {
          check = (this->Remove(dat) || check);
      }
    );
    return check;
  }

protected:
  // Specific member functions

  static ulong card(int a, int b)  
  {
    return std::max(0, b-a+1);
  }

  template <typename Derived, typename Out>
  Out Reach(const Out& cur, ulong mov, Out& predCur) 
    const {
      return dynamic_cast<Derived const*>(this)->Reach(cur, mov, predCur);
  }

  template <typename Derived, typename Out>
  const Data& getData(const Out& cur)
    const {
      return dynamic_cast<Derived const*>(this)->getData(cur);
  }

  template <typename Derived, typename Out>
  Out BSearch(const Data& dat, Out predLeft, Out left, ulong delta, Out& pPred2Nxt) 
    const {
    
      Out mid; 
      pPred2Nxt = predLeft;
      while (delta > 0) {

        mid = Reach<Derived, Out>(left, card(1, (delta>>1) - 1), pPred2Nxt);
        if(getData<Derived, Out>(mid) == dat)
                                  return mid;

        if (getData<Derived, Out>(mid)>dat)
        {
          delta = card(1, (delta >> 1) - 1);
          pPred2Nxt = predLeft;
        }

        else 
        {
          delta = delta - card(1, 1 + card(1, (delta >> 1) - 1));
          left = Reach<Derived, Out>(mid,1,pPred2Nxt);
          predLeft = mid;
        }

      }

    return pPred2Nxt;
  }

};

/* ************************************************************************** */

}

#endif
