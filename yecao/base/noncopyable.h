#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace yecao {

    class noncopyable {
    public:
        noncopyable(const noncopyable&) = delete;
        void operator=(const noncopyable&) = delete;

    protected:
        noncopyable() = default;
        ~noncopyable() = default;
    };

}   // namespace yecao

#endif  // NONCOPYABLE_H
