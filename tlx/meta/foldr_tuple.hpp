/*******************************************************************************
 * tlx/meta/foldr_tuple.hpp
 *
 * Part of tlx - http://panthema.net/tlx
 *
 * Copyright (C) 2018 Hung Tran <hung@ae.cs.uni-frankfurt.de>
 *
 * All rights reserved. Published under the Boost Software License, Version 1.0
 ******************************************************************************/

#ifndef TLX_META_FOLDR_TUPLE_HEADER
#define TLX_META_FOLDR_TUPLE_HEADER

#include <tlx/meta/index_sequence.hpp>
#include <tlx/meta/foldr.hpp>
#include <tuple>

namespace tlx {

//! \addtogroup tlx_meta
//! \{

/******************************************************************************/
// Variadic Template Expander: Implements foldr on the components of a tuple.

namespace detail {

//! helper for foldr_tuple: forwards tuple entries
template <typename Reduce, typename Init, typename Tuple, std::size_t... Is>
auto foldr_tuple_impl(Reduce&& r, Init&& init, Tuple&& t, tlx::index_sequence<Is...>)
{
    return foldr(std::forward<Reduce>(r), std::forward<Init>(init), std::get<Is>(std::forward<Tuple>(t)) ...);
}

} // namespace detail

//! Implements foldr with binary Reduce operation and initial value on a tuple.
template <typename Reduce, typename Init, typename Tuple>
auto foldr_tuple(Reduce&& r, Init&& init, Tuple&& t)
{
    using Indices = tlx::make_index_sequence<
        std::tuple_size<typename std::decay<Tuple>::type>::value>;
    return detail::foldr_tuple_impl(
        std::forward<Reduce>(r),
        std::forward<Init>(init),
        std::forward<Tuple>(t), Indices());
}

//! \}

} // namespace tlx

#endif // !TLX_META_FOLDR_TUPLE_HEADER

/******************************************************************************/
