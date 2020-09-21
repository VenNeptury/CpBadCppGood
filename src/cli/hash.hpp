#include <string>

constexpr unsigned int hash(const char *s, int off = 0)
{
    return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}
constexpr inline unsigned int operator"" _(const char *p, size_t)
{
    return hash(p);
}