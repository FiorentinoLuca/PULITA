
namespace lasd {

  template <typename Data>
  inline lasd::BVecT<Data>::BVecT(const Data& dat)
  : Vector<Data>(1), areNodes(1) {
    buffer[0] = dat;
    areNodes[0] = true;
  }

  template <typename Data>
  inline lasd::BVecT<Data>::BVecT(Data&& dat)
  : Vector<Data>(1), areNodes(1) {
    buffer[0] = std::move(dat);
    areNodes[0] = true;
  }

  

} // namespace lasd