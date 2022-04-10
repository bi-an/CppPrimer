// 来自 GCC 源码

// enable_shared_from_this
template <typename _Tp>
class enable_shared_from_this {
 protected:
  constexpr enable_shared_from_this() noexcept {}

  enable_shared_from_this(const enable_shared_from_this&) noexcept {}

  enable_shared_from_this& operator=(const enable_shared_from_this&) noexcept {
    return *this;
  }

  ~enable_shared_from_this() {}

 public:
  shared_ptr<_Tp> shared_from_this() {
    return shared_ptr<_Tp>(this->_M_weak_this);
  }

  shared_ptr<const _Tp> shared_from_this() const {
    return shared_ptr<const _Tp>(this->_M_weak_this);
  }

  weak_ptr<_Tp> weak_from_this() noexcept { return _M_weak_this; }

  weak_ptr<const _Tp> weak_from_this() const noexcept { return _M_weak_this; }

 private:
  // 注意：这个函数与 weak_ptr 与 shared_ptr 有着千丝万缕的联系
  // 作用应该是在某个合适的时机，将 _M_weak_this 绑定到 this 上
  template <typename _Tp1>
  void _M_weak_assign(_Tp1* __p, const __shared_count<>& __n) const noexcept {
    _M_weak_this._M_assign(__p, __n);
  }

  // Found by ADL when this is an associated class.
  friend const enable_shared_from_this* __expt_enable_shared_from_this_base(
      const enable_shared_from_this* __p) {
    return __p;
  }

  template <typename>
  friend class shared_ptr;

  mutable weak_ptr<_Tp> _M_weak_this;
};
