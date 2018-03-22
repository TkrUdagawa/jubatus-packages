// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2011 Preferred Networks and Nippon Telegraph and Telephone Corporation.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License version 2.1 as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef JUBATUS_CORE_FV_CONVERTER_DATUM_HPP_
#define JUBATUS_CORE_FV_CONVERTER_DATUM_HPP_

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <msgpack.hpp>
#include "jubatus/util/data/serialization.h"

namespace jubatus {
namespace core {
namespace fv_converter {

struct datum {
  typedef std::vector<std::pair<std::string, std::string> > sv_t;
  typedef std::vector<std::pair<std::string, double> > nv_t;

  sv_t string_values_;
  nv_t num_values_;
  sv_t binary_values_;

  MSGPACK_DEFINE(string_values_, num_values_, binary_values_);

  template<class Archiver>
  void serialize(Archiver& ar) {
    std::map<std::string, std::string> sv;
    std::map<std::string, double> nv;
    std::map<std::string, std::string> bv;
    if (ar.is_read) {
      ar
          & JUBA_NAMED_MEMBER("string_values", sv)
          & JUBA_NAMED_MEMBER("num_values", nv)
          & JUBA_NAMED_MEMBER("binary_values", bv);
      string_values_ = sv_t(sv.begin(), sv.end());
      num_values_ = nv_t(nv.begin(), nv.end());
      binary_values_ = sv_t(bv.begin(), bv.end());
    } else {
      sv.insert(string_values_.begin(), string_values_.end());
      nv.insert(num_values_.begin(), num_values_.end());
      bv.insert(binary_values_.begin(), binary_values_.end());
      ar
          & JUBA_NAMED_MEMBER("string_values", sv)
          & JUBA_NAMED_MEMBER("num_values", nv)
          & JUBA_NAMED_MEMBER("binary_values", bv);
    }
  }
};

}  // namespace fv_converter
}  // namespace core
}  // namespace jubatus

#endif  // JUBATUS_CORE_FV_CONVERTER_DATUM_HPP_
