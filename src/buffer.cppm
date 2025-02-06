module;

#include <algorithm>
#include <iostream>

export module buffer;

export namespace buffer {
    template <typename T, int = 16, int = 16>
    class buffer {
    public:
        buffer();
        buffer(int x, int y);
        ~buffer();

        T* operator[](size_t i) {
            return data_[i];
        };

        const T* operator[](size_t i) const {
            return data_[i];
        };

        buffer(const buffer& other);
        buffer& operator=(const buffer& other);

        // TODO: implement it with sfinae
        // void print_data();

        int width() const;
        int height() const;
        void print_data() const;

    private:
        int width_, height_;
        T** data_ = nullptr;

    private:
        void allocate_buffer();
        void deallocate_buffer();
    };

    template <typename T, int W, int H>
    buffer<T, W, H>::buffer() : width_(W), height_(H) {
        allocate_buffer();
    }

    template <typename T, int W, int H>
    buffer<T, W, H>::buffer(int x, int y) : width_(x), height_(y) {
        allocate_buffer();
    }

    template <typename T, int W, int H>
    buffer<T, W, H>::~buffer() {
        deallocate_buffer();
    }

    template <typename T, int W, int H>
    buffer<T, W, H>::buffer(const buffer& other) : width_(other.width_), height_(other.height_) {
        allocate_buffer();
        for (int i = 0; i < height_; i++) {
            for (int j = 0; j < width_; j++) {
                data_[i][j] = other.data_[i][j];
            }
        }
    }

    template <typename T, int W, int H>
    buffer<T, W, H>& buffer<T, W, H>::operator=(const buffer& other) {
        if (this == &other)
            return *this;

        buffer temp(other);
        std::swap(data_, temp.data_);

        return *this;
    }

    template <typename T, int W, int H>
    int buffer<T, W, H>::width() const {
        return width_;
    }

    template <typename T, int W, int H>
    int buffer<T, W, H>::height() const {
        return height_;
    }

    template <typename T, int W, int H>
    void buffer<T, W, H>::print_data() const {
        for (int i = 0; i < height_; i++) {
            for (int j = 0; j < width_; j++) {
                std::cout << data_[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    template <typename T, int W, int H>
    void buffer<T, W, H>::allocate_buffer() {
        data_ = new T*[height_];
        for (int i = 0; i < height_; i++) {
            data_[i] = new T[width_]();
        }
    }

    template <typename T, int W, int H>
    void buffer<T, W, H>::deallocate_buffer() {
        for (int i = 0; i < height_; i++) {
            delete[] data_[i];
        }
        delete[] data_;
    }
}
