#ifndef BASE_UNIT_H_
#define BASE_UNIT_H_

namespace base {

// Unit is an empty struct.
struct Unit {};

inline bool operator==(const Unit&, const Unit&) { return true; }
inline bool operator!=(const Unit&, const Unit&) { return false; }

} // namespace base

#endif
