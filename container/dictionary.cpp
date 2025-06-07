
namespace lasd {

/* ************************************************************************** */

// ...

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &box)
{
  bool check = true;
  box.Traverse(
    [this, &check](const Data &dat)
    {
      check = (Insert(dat) && check);
    }
  );
  return check;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&box)
{
  bool check = true;
  box.Map(
    [this, &check](Data &dat)
    {
      check = (Insert(std::move(dat)) && check);
    }
  );
  return check;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &box)
{
  bool check = true;
  box.Traverse(
    [this, &check](const Data &dat)
    {
      check = (Remove(dat) && check);
    }
  );
  return check;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &box)
{
  bool check = false;
  box.Traverse(
    [this, &check](const Data &dat)
    {
        check = (Insert(dat) || check);
    }
  );
  return check;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&box)
{
  bool check = false;
  box.Map(
    [this, &check](Data &dat)
    {
        check = (Insert(std::move(dat)) || check);
    }
  );
  return check;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &box)
{
  bool check = false;
  box.Traverse(
    [this, &check](const Data &dat)
    {
        check = (Remove(dat) || check);
    }
  );
  return check;
}

/* ************************************************************************** */

}
