#include "circular_buffer.h"
#include <iostream>

CircularBuffer::iterator::iterator(CircularBuffer& container, size_t index_) : container_(container), index_(index_% container_.capacity()) { first_step = true; }
value_type& CircularBuffer::iterator::operator*() const { return container_[index_]; }
CircularBuffer::iterator& CircularBuffer::iterator::operator+(int N) { index_ = N >= 0 ? (index_ + N) % container_.capacity() : container_.capacity() + (N % container_.capacity()); return *this; }
CircularBuffer::iterator& CircularBuffer::iterator::operator++() { index_ = (index_ + 1) % container_.capacity(); return *this; }
CircularBuffer::iterator CircularBuffer::iterator::operator++(int) { return ++(*this); }
bool CircularBuffer::iterator::operator!=(const CircularBuffer::iterator& right) const { return index_ != right.index_ % container_.capacity(); }
bool CircularBuffer::iterator::operator==(const CircularBuffer::iterator& right) const { return index_ == right.index_ % container_.capacity(); }

//typedef int T;
CircularBuffer::CircularBuffer() {
	buffer = new value_type(sizeof(value_type) * 1);
	start_val = 0;
	end_val = 0;
	actual_length = 0;
	cont_length = 0;
}
CircularBuffer::~CircularBuffer() = default;
CircularBuffer::CircularBuffer(const CircularBuffer& cb) {
	start_val = cb.start_val;
	end_val = cb.end_val;
	buffer = new value_type(sizeof(value_type) * cb.cont_length);
	memcpy(buffer, cb.buffer, sizeof(value_type) * cb.cont_length);
	actual_length = cb.actual_length;
	cont_length = cb.cont_length;
}
CircularBuffer::CircularBuffer(int capacity) {
	int actual_capacity = capacity + 1;
	cont_length = actual_capacity;
	buffer = new value_type(sizeof(value_type) * (actual_capacity));
	start_val = 0;
	end_val = 0;
	actual_length = 0;
}
CircularBuffer::CircularBuffer(int capacity, const value_type& elem) {
	int actual_capacity = capacity + 1;
	buffer = new value_type(sizeof(value_type) * (actual_capacity));
	cont_length = actual_capacity;
	start_val = 0;
	end_val = 0;
	actual_length = 0;
	for (int i = 0; i < capacity; i++)
		buffer[i] = elem;
}
CircularBuffer::iterator CircularBuffer::begin() { return CircularBuffer::iterator(*this, this->start_val); }
CircularBuffer::iterator CircularBuffer::end() { return CircularBuffer::iterator(*this, this->end_val); }
value_type& CircularBuffer::operator[](int i) {
	return buffer[i];
}
const value_type& CircularBuffer::operator[](int i) const {
	return buffer[i];
}
value_type& CircularBuffer::at(int i) {
	if (i > cont_length) {
		throw std::invalid_argument("invalid index");
		return buffer[0];
	}
	else {
		return buffer[i];
	}
}
const value_type& CircularBuffer::at(int i) const {
	if (i > cont_length) {
		throw std::invalid_argument("invalid index");
		return buffer[0];
	}
	else {
		return buffer[i];
	}
}
value_type& CircularBuffer::front() //—сылка на первый элемент.
{
	return buffer[start_val];
}
value_type& CircularBuffer::back()  //—сылка на последний элемент.
{
	return buffer[end_val - 1];
}
const value_type& CircularBuffer::front() const
{
	return buffer[start_val];
}
const value_type& CircularBuffer::back() const
{
	return buffer[end_val - 1];
}
value_type* CircularBuffer::linearize()
{
	rotate(start_val);
	return &buffer[0];
}
bool CircularBuffer::is_linearized() const
{
	return start_val == 0 ? true : false;
}
int CircularBuffer::give_index_in_circle(int index) {
	return index >= 0 ? index % cont_length : (cont_length + (index % cont_length)) % cont_length;
}
void CircularBuffer::rotate(int new_begin)
{
	for (int i = new_begin; i > 0; i--) {
		value_type last_val = buffer[i-1];
		bool first_step = true;
		for (int j = give_index_in_circle(i - 1); give_index_in_circle(j) != give_index_in_circle(i - 1) || first_step; j--) {
			value_type tmp = buffer[give_index_in_circle(j - 1)];
			buffer[give_index_in_circle(j - 1)] = last_val;
			last_val = tmp;
			first_step = false;
		}
		start_val = give_index_in_circle(start_val - 1);
		end_val = give_index_in_circle(end_val - 1);
	}

}
int CircularBuffer::size() const {
	return actual_length;
}
bool CircularBuffer::empty() const {
	return (actual_length == 0);
}
bool CircularBuffer::full() const {
	return (actual_length == cont_length - 1);
}
int CircularBuffer::reserve() const {
	return (cont_length - actual_length - 1);
}
int CircularBuffer::capacity() const {
	return (cont_length);
}
void CircularBuffer::set_capacity(int new_capacity) {
	int actual_capacity = new_capacity + 1;
	value_type* new_buffer = new value_type(sizeof(value_type) * actual_capacity);
	memcpy(new_buffer, buffer, sizeof(value_type) * cont_length);
	buffer = new_buffer;
	start_val = 0;
	end_val = 0;
	actual_length = 0;
	cont_length = actual_capacity;
}
void CircularBuffer::resize(int new_size, const value_type& item) {
	int actual_new_size = new_size + 1;
	if (cont_length > actual_new_size) {
		value_type* new_buffer = new value_type(sizeof(value_type) * actual_new_size);
		memcpy(new_buffer, buffer, sizeof(value_type) * cont_length);
		//if buffer is become smaller we need to change start and end indices
		if (start_val > actual_new_size)
			start_val = 0;
		if (end_val > actual_new_size)
			end_val = 0;
		cont_length = actual_new_size;
		delete buffer;
		buffer = new_buffer;
	}
	else if (cont_length < actual_new_size) {
		value_type* new_buffer = new value_type(sizeof(value_type) * actual_new_size);
		memcpy(new_buffer, buffer, sizeof(value_type) * cont_length);
		for (int i = cont_length; i < actual_new_size; i++)
			new_buffer[i] = item;
		int last_val = start_val > end_val ? start_val : end_val;
		//if buffer is become bigger we need to move start or end of buffer 
		for (int i = last_val; i % capacity() != 0; i++)
			new_buffer[actual_new_size - abs(last_val - i) - 1] = new_buffer[i];
		if (start_val > end_val)
			start_val = actual_new_size - abs(last_val - capacity());
		else
			end_val = actual_new_size - abs(last_val - capacity());
		cont_length = actual_new_size;
		delete buffer;
		buffer = new_buffer;
	}
}
void CircularBuffer::swap(CircularBuffer& cb) {
	for (int i = 0; i < cont_length; i++) {
		value_type tmp = buffer[i];
		buffer[i] = cb[i];
		cb[i] = tmp;
	}
}
void CircularBuffer::push_back(const value_type& item) {
	if (cont_length - 1 == actual_length) {
		buffer[start_val] = item;
		return;
	}
	buffer[end_val] = item;
	actual_length++;
	end_val = give_index_in_circle(end_val + 1);
}
void CircularBuffer::push_front(const value_type& item) {
	if (cont_length - 1 == actual_length) {
		buffer[end_val - 1] = item;
		return;
	}
	start_val = give_index_in_circle(start_val - 1);
	buffer[start_val] = item;
	actual_length++;
}
void CircularBuffer::pop_back() {
	//if actual length of buffer is lesser then zero we do nothing;
	if (actual_length > 0) {
		end_val = give_index_in_circle(end_val - 1);
		actual_length--;
	}
}
void CircularBuffer::pop_front() {
	//if actual length of buffer is lesser then zero we do nothing;
	if (actual_length > 0) {
		start_val = give_index_in_circle(start_val + 1);
		actual_length--;
	}
}
void CircularBuffer::clear() {
	actual_length = 0;
	start_val = 0;
	end_val = 0;
}

bool operator==(const CircularBuffer& a, const CircularBuffer& b) {
	return a == b;
}
bool operator!=(const CircularBuffer& a, const CircularBuffer& b) {
	return a != b;
}



//int main() {
//	CircularBuffer* buf = new CircularBuffer(5);
//
//	std::cout << buf->size() << "\n";
//
//	buf->push_back(23);
//	buf->push_front(123);
//	std::cout << (buf->at(5)) << " " << (buf->at(0)) << std::endl;
//	buf->resize(8);
//	buf->push_front(321);
//	buf->push_front(221);
//	for (auto p : *buf) {
//		std::cout << p << " ";
//	}
//	return 0;
//}