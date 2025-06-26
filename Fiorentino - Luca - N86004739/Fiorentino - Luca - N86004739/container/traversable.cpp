#include "traversable.hpp"

namespace lasd {

/* ************************************************************************** */

// ...

template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc)
  const{
    Traverse(
      [fun, &acc](const Data &dat)
      {
          acc = fun(dat, acc);
      }
    );
  return acc;
}

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data& x)
  const noexcept {
    bool found = false;
    Traverse(
      [&found, x](const Data &dat)
      {
          if (dat == x)
              found = true;
      }
    );
  return found;
}

template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun)
  const {
    PreOrderTraverse(fun);
}

template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc)
  const {
    PreOrderTraverse(
      [fun, &acc](const Data &dat)
      {
          acc = fun(dat, acc);
      }
    );
  return acc;
}

template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun)
  const {
    PostOrderTraverse(fun);
}

template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc)
  const {
    PostOrderTraverse(
      [fun, &acc](const Data &dat)
      {
          acc = fun(dat, acc);
      }
    );
  return acc;
}

/* ************************************************************************** */

}
