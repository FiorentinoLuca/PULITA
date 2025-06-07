
namespace lasd {

/* ************************************************************************** */

// ...

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun f) 
{
  PreOrderMap(f);
}

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun f) 
{
  PostOrderMap(f);
}

/* ************************************************************************** */

}
