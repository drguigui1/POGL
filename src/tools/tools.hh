#ifndef TOOLS_HH_
#define TOOLS_HH_

inline float clamp(float a, float b, float value) {
    return std::max(a, std::min(b, value));
}


#endif /* !SRC/TOOLS/TOOLS_HH_ */
