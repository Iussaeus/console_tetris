module;

#include <algorithm>
#include <iostream>
#include <ostream>

export module buffer;

export namespace buffer {
	template <typename T>
	class buffer_2d {
	public:
		buffer_2d();
		buffer_2d(int x, int y);
		~buffer_2d();

		T* operator[](size_t i) {
			return data_[i];
		};

		const T& operator[](size_t i) const {
			return data_[i];
		};

		buffer_2d(const buffer_2d& other);
		buffer_2d& operator=(const buffer_2d& other);

		// TODO: implement it with sfinae
		// void print_data();

		int get_width() const;
		int get_height() const;

	private:
		int width_, height_;
		T** data_ = nullptr;

	private:
		void allocate_buffer();
		void deallocate_buffer();
	};

	template <typename T>
	buffer_2d<T>::buffer_2d() : width_(16), height_(48) {
		// manual allocation
		data_ = new T*[height_];
		for (int i = 0; i < height_; i++) {
			data_[i] = new T[width_];
			for (int j = 0; j < width_; j++) {
				data_[i][j] = T();
			}
		}
	}

	template <typename T>
	buffer_2d<T>::buffer_2d(int x, int y) : width_(x), height_(y) {
		allocate_buffer();
	}

	template <typename T>
	buffer_2d<T>::~buffer_2d() {
		deallocate_buffer();
	}

	template <typename T>
	buffer_2d<T>::buffer_2d(const buffer_2d& other) : width_(other.width_), height_(other.height_) {
		allocate_buffer();
		for (int i = 0; i < height_; i++) {
			for (int j = 0; j < width_; j++) {
				data_[i][j] = other.data_[i][j];
			}
		}
	}

	template <typename T>
	buffer_2d<T>& buffer_2d<T>::operator=(const buffer_2d& other) {
		if (this == &other)
			return *this;

		buffer_2d temp(other);
		std::swap(data_, temp.data_);

		return *this;
	}

	template <typename T>
	int buffer_2d<T>::get_width() const {
		return width_;
	}

	template <typename T>
	int buffer_2d<T>::get_height() const {
		return height_;
	}

	template <typename T>
	void buffer_2d<T>::allocate_buffer() {
		data_ = new T*[height_];
		for (int i = 0; i < height_; i++) {
			data_[i] = new T[width_];
		}
	}

	template <typename T>
	void buffer_2d<T>::deallocate_buffer() {
		for (int i = 0; i < height_; i++) {
			delete[] data_[i];
		}
		delete[] data_;
	}
}
