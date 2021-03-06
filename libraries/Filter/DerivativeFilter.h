// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
//
// This is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.
//

/// @file	Derivative.h
/// @brief	A class to implement a derivative (slope) filter
/// See http://www.holoborodko.com/pavel/numerical-methods/numerical-derivative/smooth-low-noise-differentiators/

#ifndef __DERIVATIVE_FILTER_H__
#define __DERIVATIVE_FILTER_H__

#include "FilterClass.h"
#include "FilterWithBuffer.h"

// 1st parameter <T> is the type of data being filtered.
// 2nd parameter <FILTER_SIZE> is the number of elements in the filter
template <class T, uint8_t FILTER_SIZE>
class DerivativeFilter : public FilterWithBuffer<T,FILTER_SIZE>
{
public:
    // constructor
    DerivativeFilter() : FilterWithBuffer<T,FILTER_SIZE>() {
    };

    // update - Add a new raw value to the filter, but don't recalculate
    void        update(T sample, uint32_t timestamp);

    // return the derivative value
    float        slope(void) const;

    // reset - clear the filter
    virtual void        reset() override;

private:
    mutable bool    _new_data;   // new_data and _last_slope are only used for caching the slope() result.
    mutable float   _last_slope; // Apart from the caching, slope() doesn't change the object and should
                                 // therefore be marked as const what requires these members to be mutable.

    // microsecond timestamps for samples. This is needed
    // to cope with non-uniform time spacing of the data
    uint32_t        _timestamps[FILTER_SIZE];
};

typedef DerivativeFilter<float,5> DerivativeFilterFloat_Size5;
typedef DerivativeFilter<float,7> DerivativeFilterFloat_Size7;
typedef DerivativeFilter<float,9> DerivativeFilterFloat_Size9;


#endif // __DERIVATIVE_FILTER_H__

