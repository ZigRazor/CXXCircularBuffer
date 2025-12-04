#ifndef CXXCIRCULARBUFFER_CIRCULARBUFFER_HPP
#define CXXCIRCULARBUFFER_CIRCULARBUFFER_HPP

#include <cstddef>
#include <iterator>

namespace CXXCircularBuffer
{

    template <typename T>
    class CircularBufferIterator
    {
    private:
        const CircularBuffer *buffer_;
        std::size_t index_;
        std::size_t position_;

    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;

        CircularBufferIterator() : buffer_(nullptr), index_(0), position_(0) {}

        CircularBufferIterator(const CircularBuffer *buf, std::size_t idx, std::size_t pos)
            : buffer_(buf), index_(idx), position_(pos) {}

        reference operator*() const { return buffer_->buffer_[index_]; }
        pointer operator->() const { return &buffer_->buffer_[index_]; }

        CircularBufferIterator &operator++()
        {
            index_ = (index_ + 1) % Size;
            ++position_;
            return *this;
        }

        CircularBufferIterator operator++(int)
        {
            CircularBufferIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        CircularBufferIterator &operator--()
        {
            index_ = (index_ == 0) ? Size - 1 : index_ - 1;
            --position_;
            return *this;
        }

        CircularBufferIterator operator--(int)
        {
            CircularBufferIterator tmp = *this;
            --(*this);
            return tmp;
        }

        CircularBufferIterator &operator+=(difference_type n)
        {
            position_ += n;
            index_ = (index_ + n) % Size;
            return *this;
        }

        CircularBufferIterator &operator-=(difference_type n)
        {
            return *this += (-n);
        }

        CircularBufferIterator operator+(difference_type n) const
        {
            CircularBufferIterator tmp = *this;
            return tmp += n;
        }

        CircularBufferIterator operator-(difference_type n) const
        {
            CircularBufferIterator tmp = *this;
            return tmp -= n;
        }

        difference_type operator-(const CircularBufferIterator &other) const
        {
            return position_ - other.position_;
        }

        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }

        bool operator==(const CircularBufferIterator &other) const
        {
            return buffer_ == other.buffer_ && position_ == other.position_;
        }

        bool operator!=(const CircularBufferIterator &other) const
        {
            return !(*this == other);
        }

        bool operator<(const CircularBufferIterator &other) const
        {
            return position_ < other.position_;
        }

        bool operator>(const CircularBufferIterator &other) const
        {
            return other < *this;
        }

        bool operator<=(const CircularBufferIterator &other) const
        {
            return !(other < *this);
        }

        bool operator>=(const CircularBufferIterator &other) const
        {
            return !(*this < other);
        }
    };

    template <typename T, size_t Size>
    class CircularBuffer
    {

    private:
        T *buffer_;
        std::size_t head_ = 0;
        std::size_t tail_ = 0;

    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        // Const iterator class
        class const_iterator
        {
        private:
            const CircularBuffer *buffer_;
            std::size_t index_;
            std::size_t position_;

        public:
            typedef std::random_access_iterator_tag iterator_category;
            typedef T value_type;
            typedef ptrdiff_t difference_type;
            typedef const T *pointer;
            typedef const T &reference;

            const_iterator() : buffer_(nullptr), index_(0), position_(0) {}

            const_iterator(const CircularBuffer *buf, std::size_t idx, std::size_t pos)
                : buffer_(buf), index_(idx), position_(pos) {}

            // Conversion from iterator to const_iterator
            const_iterator(const iterator &it)
                : buffer_(it.buffer_), index_(it.index_), position_(it.position_) {}

            reference operator*() const { return buffer_->buffer_[index_]; }
            pointer operator->() const { return &buffer_->buffer_[index_]; }

            const_iterator &operator++()
            {
                index_ = (index_ + 1) % Size;
                ++position_;
                return *this;
            }

            const_iterator operator++(int)
            {
                const_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            const_iterator &operator--()
            {
                index_ = (index_ == 0) ? Size - 1 : index_ - 1;
                --position_;
                return *this;
            }

            const_iterator operator--(int)
            {
                const_iterator tmp = *this;
                --(*this);
                return tmp;
            }

            const_iterator &operator+=(difference_type n)
            {
                position_ += n;
                index_ = (index_ + n) % Size;
                return *this;
            }

            const_iterator &operator-=(difference_type n)
            {
                return *this += (-n);
            }

            const_iterator operator+(difference_type n) const
            {
                const_iterator tmp = *this;
                return tmp += n;
            }

            const_iterator operator-(difference_type n) const
            {
                const_iterator tmp = *this;
                return tmp -= n;
            }

            difference_type operator-(const const_iterator &other) const
            {
                return position_ - other.position_;
            }

            reference operator[](difference_type n) const
            {
                return *(*this + n);
            }

            bool operator==(const const_iterator &other) const
            {
                return buffer_ == other.buffer_ && position_ == other.position_;
            }

            bool operator!=(const const_iterator &other) const
            {
                return !(*this == other);
            }

            bool operator<(const const_iterator &other) const
            {
                return position_ < other.position_;
            }

            bool operator>(const const_iterator &other) const
            {
                return other < *this;
            }

            bool operator<=(const const_iterator &other) const
            {
                return !(other < *this);
            }

            bool operator>=(const const_iterator &other) const
            {
                return !(*this < other);
            }
        };

        // Const reverse iterator class
        class const_reverse_iterator
        {
        private:
            const CircularBuffer *buffer_;
            std::size_t index_;
            std::size_t position_;

        public:
            typedef std::random_access_iterator_tag iterator_category;
            typedef T value_type;
            typedef ptrdiff_t difference_type;
            typedef const T *pointer;
            typedef const T &reference;

            const_reverse_iterator() : buffer_(nullptr), index_(0), position_(0) {}

            const_reverse_iterator(const CircularBuffer *buf, std::size_t idx, std::size_t pos)
                : buffer_(buf), index_(idx), position_(pos) {}

            // Conversion from reverse_iterator to const_reverse_iterator
            const_reverse_iterator(const reverse_iterator &it)
                : buffer_(it.buffer_), index_(it.index_), position_(it.position_) {}

            reference operator*() const { return buffer_->buffer_[index_]; }
            pointer operator->() const { return &buffer_->buffer_[index_]; }

            const_reverse_iterator &operator++()
            {
                index_ = (index_ == 0) ? Size - 1 : index_ - 1;
                ++position_;
                return *this;
            }

            const_reverse_iterator operator++(int)
            {
                const_reverse_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            const_reverse_iterator &operator--()
            {
                index_ = (index_ + 1) % Size;
                --position_;
                return *this;
            }

            const_reverse_iterator operator--(int)
            {
                const_reverse_iterator tmp = *this;
                --(*this);
                return tmp;
            }

            const_reverse_iterator &operator+=(difference_type n)
            {
                position_ += n;
                // Move backwards in the buffer
                index_ = (index_ - n % Size + Size) % Size;
                return *this;
            }

            const_reverse_iterator &operator-=(difference_type n)
            {
                return *this += (-n);
            }

            const_reverse_iterator operator+(difference_type n) const
            {
                const_reverse_iterator tmp = *this;
                return tmp += n;
            }

            const_reverse_iterator operator-(difference_type n) const
            {
                const_reverse_iterator tmp = *this;
                return tmp -= n;
            }

            difference_type operator-(const const_reverse_iterator &other) const
            {
                return position_ - other.position_;
            }

            reference operator[](difference_type n) const
            {
                return *(*this + n);
            }

            bool operator==(const const_reverse_iterator &other) const
            {
                return buffer_ == other.buffer_ && position_ == other.position_;
            }

            bool operator!=(const const_reverse_iterator &other) const
            {
                return !(*this == other);
            }

            bool operator<(const const_reverse_iterator &other) const
            {
                return position_ < other.position_;
            }

            bool operator>(const const_reverse_iterator &other) const
            {
                return other < *this;
            }

            bool operator<=(const const_reverse_iterator &other) const
            {
                return !(other < *this);
            }

            bool operator>=(const const_reverse_iterator &other) const
            {
                return !(*this < other);
            }
        };

        CircularBuffer() : buffer_(new T[Size]) head_(0), tail_(0) {}

        virtual ~CircularBuffer()
        {
            delete[] buffer_;
        };

        size_type size() const
        {
            return (head_ >= tail_) ? (head_ - tail_) : (Size - tail_ + head_);
        }

        size_type capacity() const
        {
            return Size;
        }

        size_type max_size() const
        {
            return Size;
        }

        bool empty() const
        {
            return head_ == tail_;
        }

        reference front()
        {
            return buffer_[head_];
        }

        reference back()
        {
            return buffer_[tail_];
        }

        const_reference front() const
        {
            return buffer_[head_];
        }

        const_reference back() const
        {
            return buffer_[tail_];
        }

        void clear()
        {
            head_ = tail_ = 0;
        }

        void push_back(const T &item)
        {
            buffer_[head_] = item;
            head_ = (head_ + 1) % Size;
            if (head_ == tail_)
            {
                tail_ = (tail_ + 1) % Size; // Overwrite the oldest data
            }
        }

        void pop_front()
        {
            if (!empty())
            {
                tail_ = (tail_ + 1) % Size;
            }
        }

        const_reference operator[](size_type index) const
        {
            return buffer_[index];
        }

        const_iterator begin() const
        {
            return const_iterator(this, tail_, 0);
        }

        const_iterator end() const
        {
            return const_iterator(this, head_, size());
        }

        const_iterator cbegin() const
        {
            return const_iterator(this, tail_, 0);
        }

        const_iterator cend() const
        {
            return const_iterator(this, head_, size());
        }

        const_reverse_iterator rbegin() const
        {
            std::size_t last_index = (head_ == 0) ? Size - 1 : head_ - 1;
            return const_reverse_iterator(this, last_index, 0);
        }

        const_reverse_iterator rend() const
        {
            std::size_t before_tail = (tail_ == 0) ? Size - 1 : tail_ - 1;
            return const_reverse_iterator(this, before_tail, size());
        }

        const_reverse_iterator crbegin() const
        {
            std::size_t last_index = (head_ == 0) ? Size - 1 : head_ - 1;
            return const_reverse_iterator(this, last_index, 0);
        }

        const_reverse_iterator crend() const
        {
            std::size_t before_tail = (tail_ == 0) ? Size - 1 : tail_ - 1;
            return const_reverse_iterator(this, before_tail, size());
        }
    };
} // namespace CXXCircularBuffer

#endif // CXXCIRCULARBUFFER_CIRCULARBUFFER_HPP