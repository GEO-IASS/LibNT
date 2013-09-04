// Copyright (c) 2013, Adam Harrison*
// http://www.ualberta.ca/~apharris/
// All rights reserved.

// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

// -Redistributions of source code must retain the above copyright notice, the footnote below, this list of conditions and the following disclaimer.
// -Redistributions in binary form must reproduce the above copyright notice, the footnote below, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// -Neither the name of the University of Alberta nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// *This work originated as part of a Ph.D. project under the supervision of Dr. Dileepan Joseph at the Electronic Imaging Lab, University of Alberta.



#ifndef INDEXUTIL_H
#define INDEXUTIL_H

#include<array>

#include <boost/type_traits.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/print.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/begin_end.hpp>

#include "libdivide/libdivide.h"
#include "Index.h"

namespace LibMIA
{
/** \addtogroup util Utilities
 *  @{
*/

/** \addtogroup index_util Index Utilities
 *  @{
 */


namespace internal
{

template<class array_type>
bool check_ascending(const array_type& _from){
    for(size_t i=0;i<_from.size();++i){
        if (_from[i]!=(typename array_type::value_type)i)
            return false;
    }
    return true;
}

template<class array_type1,class array_type2, class array_type3,class array_type4,size_t size1, size_t size2, size_t size3>
void concat_arrays(const std::array<array_type1,size1>& _array1, const std::array<array_type2,size2>& _array2,const std::array<array_type3,size3>& _array3,std::array<array_type4,size1+size2+size3>& to_array)
{


    size_t idx=0;
    for(auto _elem: _array1)
    {

        to_array[idx++]=_elem;
    }
    for(auto _elem: _array2)
    {

        to_array[idx++]=_elem;
    }
    for(auto _elem: _array3)
    {

        to_array[idx++]=_elem;
    }


}

//!
template<class array_type1,class array_type2, class array_type3,size_t size1, size_t size2, size_t size3>
std::array<size_t,size1+size2+size3> concat_index_arrays(const std::array<array_type1,size1>& _array1, const std::array<array_type2,size2>& _array2,const std::array<array_type3,size3>& _array3)
{

    std::array<size_t,size1+size2+size3> to_array;
    size_t idx=0;
    for(auto _elem: _array1)
    {

        to_array[idx++]=_elem;
    }
    for(auto _elem: _array2)
    {

        to_array[idx++]=_elem;
    }
    for(auto _elem: _array3)
    {

        to_array[idx++]=_elem;
    }
    return to_array;

}

//!
template<class array_type1,class array_type2, size_t size1, size_t size2>
std::array<size_t,size1+size2> concat_index_arrays(const std::array<array_type1,size1>& _array1, const std::array<array_type2,size2>& _array2)
{

    std::array<size_t,size1+size2> to_array;
    size_t idx=0;
    for(auto _elem: _array1)
    {

        to_array[idx++]=_elem;
    }
    for(auto _elem: _array2)
    {

        to_array[idx++]=_elem;
    }

    return to_array;

}

//!
template<class array_type1,class array_type2>
array_type1 reorder_to(const array_type1& from_array, const array_type2& to_sequence_order)
{

    array_type1 to_array;
    size_t curIdx=0;
    for(auto _order: to_sequence_order)
    {

        to_array[(size_t)_order]=from_array[curIdx++];

    }
    return to_array;

}


//! same as reorder_to but we start at i=curIdx instead of 0
template<class array_type1,class array_type2, class array_type3>
typename array_type3::value_type reorder_to(const array_type1& from_array, const array_type2& to_sequence_order,array_type3& to_array,size_t& curIdx)
{

    typename array_type3::value_type _dimensionality=1;
    for(auto _order: to_sequence_order)
    {

        to_array[(size_t)_order]=from_array[curIdx];
        _dimensionality*=from_array[curIdx++];
    }
    return _dimensionality;

}
//! collect dimensions of MIA, where order indexes output array _dims, e.g., _dims[order[i]]=_mia.dims[i]
template<class array_type1,class array_type2, class array_type3>
typename array_type3::value_type reorder_to(const array_type1& from_array, const array_type2& to_sequence_order,array_type3& to_array)
{

    size_t curIdx=0;
    return reorder_to(from_array,to_sequence_order,to_array,curIdx);
}
//! same as collect_dimensions_from_order but we start at i=curIdx instead of 0
template<class array_type1,class array_type2, class array_type3>
typename array_type3::value_type reorder_from(const array_type1& from_array, const array_type2& from_sequence_order,array_type3& to_array,size_t& curIdx)
{

    typename array_type3::value_type _dimensionality=1;
    for(auto _order: from_sequence_order)
    {

        to_array[curIdx++]=from_array[(size_t)_order];
        _dimensionality*=from_array[(size_t)_order];
    }
    return _dimensionality;

}
//! same as collect_dimensions_from_order but we start at i=curIdx instead of 0
template<class array_type1,class array_type2, class array_type3>
typename array_type3::value_type reorder_from(const array_type1& from_array, const array_type2& from_sequence_order,array_type3& to_array)
{

    size_t curIdx=0;
    return reorder_from(from_array,from_sequence_order,to_array,curIdx);
}

//! get total dimensionality
template<class array_type1,class array_type2>
typename array_type1::value_type dimensionality_from(const array_type1& from_array, const array_type2& from_sequence_order)
{

    typename array_type1::value_type _dimensionality=1;
    for(auto _order: from_sequence_order)
    {
        _dimensionality*=(unsigned)from_array[(size_t)_order];
    }
    return _dimensionality;

}


//should be undefined
template<typename...Args>
struct check_mia_index_args;


//base case, inherit from true_type
template<>
struct check_mia_index_args<>:public boost::true_type {};

//checks to ensure dimension arguments are all convertable to index_type. Uses recursion to allow
//check to happen regardless of number of arguments. Checking is controlled through inheritance
template<typename arg,typename...Args>
struct check_mia_index_args<arg,Args...> :
        boost::mpl::and_<
            internal::is_ProdInd<arg>,
            check_mia_index_args<Args...>
        >
    {};


//should be undefined
template<class index_type,typename...Args>
struct check_mia_dim_args;


//base case, inherit from true_type
template<class index_type>
struct check_mia_dim_args<index_type>:public boost::true_type {};

//checks to ensure dimension arguments are all convertable to index_type. Uses recursion to allow
//check to happen regardless of number of arguments. Checking is controlled through inheritance
template<class index_type,typename arg,typename...Args>
struct check_mia_dim_args<index_type,arg,Args...> :
        boost::mpl::and_<
        boost::is_same<
        typename boost::numeric::conversion_traits<index_type,arg >::supertype,
        index_type
        >,
        check_mia_dim_args<index_type,Args...>
        >
    {};

//checks to make sure size of variadic arguments is equal to order of MIA
template<class _MIA,typename...Args>
struct check_dims_count : boost::mpl::bool_<sizeof...( Args ) ==internal::order<_MIA>::value>
{ };

//checks to make sure size of variadic arguments is equal to order of MIA
template<class _MIA>
struct check_order : boost::mpl::bool_<(internal::order<_MIA>::value >0)>
{ };

template<typename _MIA, typename...Args>
struct check_mia_constructor;

template<class _MIA, typename...Args>
struct check_mia_constructor
{

    typedef typename
    boost::mpl::and_<
        boost::mpl::and_<
            check_dims_count<_MIA,Args...>,
            check_mia_dim_args<typename internal::index_type<_MIA>::type,Args...>
        >,
        check_order<_MIA>
    >::type type;

};

template<typename _MIA, typename...Args>
struct check_mia_indexing;

template<class _MIA, typename...Args>
struct check_mia_indexing
{

    typedef typename
    boost::mpl::and_<
        check_dims_count<_MIA,Args...>,
        check_mia_index_args<Args...>
    >::type type;

};

template<class index_type1,class index_type2>
struct check_index_compatibility:
    boost::is_same<
        typename boost::numeric::conversion_traits<index_type1,index_type2 >::supertype,
        index_type1
    >
{};



//check, probably std::array second parameter templated by size_t
template<typename indexType,size_t T>
inline void ind2sub(indexType idx, const std::array<indexType,T> & dims,std::array<indexType,T> & full_indices)
{



    for(size_t i=0; i<T; ++i)
    {

        full_indices[i]=idx%dims[i];
        idx/=dims[i];

    }


}

//check, probably std::array second parameter templated by size_t
template<typename indexType,size_t T>
std::array<indexType,T> ind2sub(indexType idx, const std::array<indexType,T> & dims)
{

    std::array<indexType,T> indices;

    for(size_t i=0; i<T; ++i)
    {

        indices[i]=idx%dims[i];
        idx/=dims[i];

    }

    return indices;
}

//check, probably std::array second parameter templated by size_t
template<typename indexType>
std::array<indexType,0> ind2sub(indexType idx, const std::array<indexType,0> & dims)
{

    return std::array<indexType,0>();
}

//!order is given in the order of dims used to calculate linear index idx and also the order that we assign the entries in the index array
template<typename idxType, typename orderType,typename dimType>
dimType ind2sub_reorder(idxType idx, const dimType & dims,const orderType & _order)
{

    dimType indices;

    for(size_t i=0; i<_order.size(); ++i)
    {

        indices[_order[i]]=idx%dims[_order[i]];
        idx/=dims[_order[i]];

    }

    return indices;
}

//!order is given in the order of dims used to calculate linear index idx
template<typename idxType, typename orderType,typename dimType>
dimType ind2sub(idxType idx, const dimType & dims,const orderType & _order)
{

    dimType indices;

    for(size_t i=0; i<_order.size(); ++i)
    {

        indices[i]=idx%dims[_order[i]];
        idx/=dims[_order[i]];

    }

    return indices;
}

template<class indexType1,class indexType2,size_t _size>
inline std::array<libdivide::divider<size_t>,_size> createDimAccumulatorLibDivide(const std::array<indexType1,_size>& dims,const std::array<indexType2,_size>& index_order)
{

    std::array<libdivide::divider<size_t>,_size> dim_accumulator;

    for(size_t i=0;i<_size;++i){
        dim_accumulator[i]=libdivide::divider<size_t>((size_t)std::accumulate(dims.begin(),dims.begin()+i,1,std::multiplies<indexType1>()));
    }

    dim_accumulator=internal::reorder_to(dim_accumulator,index_order); //reorder the denominators based on the reshuffle order
    return dim_accumulator;

}

template<class indexType1,class indexType2,size_t _size>
inline std::array<size_t,_size> createDimAccumulator(const std::array<indexType1,_size>& restrict dims,const std::array<indexType2,_size>& restrict index_order)
{

    std::array<size_t,_size> dim_accumulator;
    size_t current_accumulator=1;
    dim_accumulator[index_order[0]]=1;
    static_for<1, _size>::_do([&](int i)
    {
        current_accumulator*=(size_t)dims[i-1];
        dim_accumulator[index_order[i]]=current_accumulator;
    });


    return dim_accumulator;

}

template<class indexType1,size_t _size>
inline std::array<size_t,_size> createMultiplier(const std::array<indexType1,_size>& dims)
{

    std::array<size_t,_size> multiplier;
    multiplier[0]=1;
    static_for<1, _size>::_do([&](int i)
    {
        multiplier[i]= (size_t)(multiplier[i-1]*dims[i-1]);
    });


    return multiplier;

}

template<class indexType1,class indexType2,size_t _size>
inline indexType1 getShuffleLinearIndex(indexType1 idx,const std::array<indexType1,_size>& restrict dims,const std::array<indexType2,_size>& restrict dim_accumulator)
{

    size_t ioffset_next=0;
    size_t multiplier=1;

    static_for<0, _size>::_do([&](int i){
        //ioffset_next+=(dim_accumulator[i].perform_divide(idx))%((unsigned)dims[i])*multiplier;
        auto &divisor=dim_accumulator[i];
        ioffset_next+=((size_t)idx/divisor)%((size_t)dims[i])*(size_t)multiplier; //use the shuffled denominators to compute shuffle full indices, then convert linIdx on the fly
        multiplier*=(size_t)dims[i];
    });

    return (indexType1)ioffset_next;

}

template<class indexType1,class indexType2,size_t _size>
inline indexType1 getShuffleLinearIndex(const indexType1 &idx,const std::array<indexType1,_size>& restrict dims,const std::array<indexType2,_size>& restrict multiplier,const std::array<indexType2,_size>& restrict dim_accumulator)
{

//    size_t ioffset_next=0;
//    for(size_t i=0;i<_size;++i){
//        //ioffset_next+=(dim_accumulator[i].perform_divide(idx))%((unsigned)dims[i])*multiplier;
//
//        ioffset_next+=((size_t)idx/(size_t)dim_accumulator[i])%((size_t)dims[i])*(size_t)multiplier[i]; //use the shuffled denominators to compute shuffle full indices, then convert linIdx on the fly
//
//    }
//
//    return (indexType1)ioffset_next;


    size_t ioffset_next=0;
    static_for<0, _size>::_do([&](int i)
    {

        //ioffset_next+=(dim_accumulator[i].perform_divide(idx))%((unsigned)dims[i])*multiplier;

        ioffset_next+=((size_t)idx/(size_t)dim_accumulator[i])%((size_t)dims[i])*(size_t)multiplier[i]; //use the shuffled denominators to compute shuffle full indices, then convert linIdx on the fly

    });
    return (indexType1)ioffset_next;

}

template<typename indexType,size_t T>
indexType sub2ind(const std::array<indexType,T> & indices, const std::array<indexType,T> & dims)
{


    indexType idx=0;
    indexType multiplier=1;
    for(size_t i=0; i<T; ++i)
    {
        idx+=indices[i]*multiplier;
        multiplier*=dims[i];
    }
    return idx;

}

template<typename function_type, typename indexType,size_t T>
inline indexType sub2ind_function(const std::array<function_type,T> & indices_function, const indexType original_idx, const std::array<indexType,T> & dims)
{


    indexType idx=0;
    indexType multiplier=1;
    for(size_t i=0; i<T; ++i)
    {
        idx+=indices_function[i](original_idx)*multiplier;
        multiplier*=dims[i];
    }
    return idx;

}

//!order is given in the order we collect dims and indices is given in the default order, that is not suffled around
template<typename itType, typename accessType2,typename dimType>
typename dimType::value_type sub2ind(itType _begin, itType _end,const accessType2 &order, const dimType & dims)
{



    typename dimType::value_type idx=0;
    typename dimType::value_type multiplier;
    size_t i=0;
    for (auto it=_begin; it< _end; ++it,++i)
    {

        multiplier=1;
        for(size_t j=0; j<(size_t)order[i]; ++j)
        {

            multiplier*=dims[j];
        }
        idx+=(*it)*multiplier;



    }

    return idx;

}

//!order is given in the order we collect dims and indices is given in the default order, that is not suffled around
template<typename accessType, typename accessType2,typename dimType>
inline typename dimType::value_type sub2ind(const accessType & indices, const accessType2 &order, const dimType & dims)
{



    typename dimType::value_type idx=0;
    typename dimType::value_type multiplier=1;

    for (size_t i=0; i< indices.size(); ++i)
    {
        multiplier=1;
        for(size_t j=0; j<(size_t)order[i]; ++j)
        {

            multiplier*=dims[j];
        }
        idx+=indices[i]*multiplier;


    }

    return idx;

}

//!order is given in the order we collect dims and indices are also reordered
template<typename accessType, typename accessType2,typename dimType>
typename dimType::value_type sub2ind_reorder(const accessType & indices, const accessType2 &order, const dimType & dims)
{


    typename dimType::value_type idx=0;
    typename dimType::value_type multiplier=1;
    for(size_t i=0; i<indices.size(); ++i)
    {
        idx+=indices[order[i]]*multiplier;
        multiplier*=dims[order[i]];
    }
    return idx;





}



template<typename arrayType1, typename arrayType2,size_t _size>
std::array<arrayType1,_size> reOrderArray(const std::array<arrayType1,_size> & _array, const std::array<arrayType2,_size> & _reorder)
{
    std::array<arrayType1,_size>  new_array;
    for(size_t i=0;i<_array.size();++i)
        new_array[i]=_array[_reorder[i]];
    return new_array;
}


template<class index_param_type,size_t _size>
std::array<index_param_type,_size> reverseOrder(const std::array<index_param_type,_size>& init_order)
{
    std::array<index_param_type,_size> output_order;
    for(size_t i=0;i<_size;++i)
    {
        for(size_t j=0;j<_size;++j)
        {
            if (init_order[j]==(index_param_type)i){
                 output_order[i]=j;
                break;
            }
        }

    }
    return output_order;
}

template<class index_param_type1,class index_param_type2, size_t _size>
void reverseOrder(const std::array<index_param_type1,_size> & init_order,std::array<index_param_type2,_size>& output_order)
{

    for(size_t i=0;i<_size;++i)
    {
        for(size_t j=0;j<_size;++j)
        {
            if (init_order[j]==(index_param_type1)i){
                 output_order[i]=j;
                break;
            }
        }

    }

}

template<size_t _size>
std::array<size_t,_size> createAscendingIndex(size_t _start=0){
    std::array<size_t,_size> ret;
    size_t idx=0;
    for (size_t &x : ret) {
        x=_start+idx++;
    }
    return ret;


}


/*! @} */
/*! @} */
} //namespace internal

}

#endif // INDEXUTIL_H

