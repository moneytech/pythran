#ifndef PYTHONIC_RANDOM_CHOICE_HPP
#define PYTHONIC_RANDOM_CHOICE_HPP

#include "pythonic/include/random/choice.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/random/random.hpp"
#include "pythonic/types/traits.hpp"

PYTHONIC_NS_BEGIN

namespace random
{

  namespace details
  {

    template <class Seq>
    typename std::enable_if<types::has_size<Seq>::value,
                            typename Seq::value_type>::type
    choice(Seq const &seq)
    {
      auto tmp = seq.begin();
      // std::advance not usable because it requires operator--
      for (long n = random() * seq.size(); n; --n)
        ++tmp;
      return *tmp;
    }

    template <class Seq>
    typename std::enable_if<!types::has_size<Seq>::value,
                            typename Seq::value_type>::type
    choice(Seq const &seq)
    {
      std::vector<typename std::decay<typename Seq::value_type>::type> tmp(
          seq.begin(), seq.end());
      return tmp[long(random() * tmp.size())];
    }
  }

  template <class Seq>
  typename Seq::value_type choice(Seq const &seq)
  {
    return details::choice(seq);
  }
}
PYTHONIC_NS_END

#endif
