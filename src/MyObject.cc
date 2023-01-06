#include <numeric>

#include "MyObject.h"

int MyObject::bSum() const { return std::accumulate(b_.begin(), b_.end(), 0); }
