#include <iostream>
#pragma once

typedef int value_type;

class CircularBuffer {
private:
	value_type* buffer;
	int actual_length;
	int cont_length;
	class iterator : public std::iterator<std::output_iterator_tag, value_type> {
	private:
		CircularBuffer& container_;
		size_t index_{ 0 };
		bool first_step;
	public:
		value_type& operator*() const;
		iterator& operator+(int N);
		iterator& operator++();
		iterator operator++(int);
		bool operator!=(const iterator& right) const;
		bool operator==(const iterator& right) const;
		iterator(CircularBuffer& container, size_t index_ = 0);
	};
public:
	int start_val, end_val;
	class iterator;
	CircularBuffer();
	CircularBuffer(const CircularBuffer& cb);
	~CircularBuffer();
	///Конструирует буфер заданной ёмкости.
	///Designs Circular Buffer with given capacity
	CircularBuffer(int capacity);
	//Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.
	///Designs Circular Buffer with given capacity and fills elem into every node
	CircularBuffer(int capacity, const value_type& elem);

	//Доступ по индексу. Не проверяют правильность индекса.
	///Provides access by index without checking correctness of given index
	value_type& operator[](int i);
	const value_type& operator[](int i) const;

	//Доступ по индексу. Методы бросают исключение в случае неверного индекса.
	///Provides access by index safely(with checking correctness of given index)
	value_type& at(int i);
	const value_type& at(int i) const;
	iterator begin();
	iterator end();
	//Pointer to first element
	value_type& front(); //Ссылка на первый элемент.
	//Pointer to last element
	value_type& back();  //Ссылка на последний элемент.
	const value_type& front() const;
	const value_type& back() const;

	int give_index_in_circle(int index);

	//Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
	//переместится в начало аллоцированной памяти. Возвращает указатель 
	//на первый элемент.
	//Linearize circular buffer(buffer will be rotated so that the first element will be literally the first)
	value_type* linearize();
	//Проверяет, является ли буфер линеаризованным.
	//Method for checking buffer linearization
	bool is_linearized() const;
	//Сдвигает буфер так, что по нулевому индексу окажется элемент 
	//с индексом new_begin.
	//Rotates buffer so that the element with index 'new_begin' will be the first
	void rotate(int new_begin);
	//Количество элементов, хранящихся в буфере.
	//Size of buffer(number of elements contained in the buffer)
	int size() const;
	bool empty() const;
	//true, если size() == capacity().
	//Method for checking buffer fullness
	bool full() const;
	//Количество свободных ячеек в буфере.
	//Returns number of free nodes of buffer
	int reserve() const;
	//ёмкость буфера
	//Returns buffer capacity
	int capacity() const;

	void set_capacity(int new_capacity);
	//Изменяет размер буфера.
	//В случае расширения, новые элементы заполняются элементом item.
	//Method for changing buffer size, if buffer will become bigger new nodes will contain 'item'
	void resize(int new_size, const value_type& item = value_type());
	//Оператор присваивания.
	//Assigment operator
	CircularBuffer& operator=(const CircularBuffer& cb);
	//Обменивает содержимое буфера с буфером cb.
	//Method for swapping buffers contents
	void swap(CircularBuffer& cb);

	//Добавляет элемент в конец буфера. 
	//Если текущий размер буфера равен его ёмкости, то переписывается
	//первый элемент буфера (т.е., буфер закольцован). 
	//Push element in the back of buffer(if buffer is full, item will be placed at the beginning of the buffer)
	void push_back(const value_type& item = value_type());
	//Добавляет новый элемент перед первым элементом буфера. 
	//Аналогично push_back, может переписать последний элемент буфера.
	//Works exactly the same as the push_back but item will be placed at the beginning of the buffer(if buffer is full, item will be placed at the end of the buffer)
	void push_front(const value_type& item = value_type());
	//удаляет последний элемент буфера.
	//Removes the last element of buffer
	void pop_back();
	//удаляет первый элемент буфера.
	//Removes the first element of buffer
	void pop_front();

	//Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
	//Insert element item by the index pos. Buffer capacity remains unchanged
	void insert(int pos, const value_type& item = value_type());
	//Удаляет элементы из буфера в интервале [first, last).
	//Removes buffer's elements in interval [first, last)
	void erase(int first, int last);
	//Очищает буфер.
	//Clears the buffer
	void clear();

	friend bool operator==(const CircularBuffer& a, const CircularBuffer& b);
	friend bool operator!=(const CircularBuffer& a, const CircularBuffer& b);
};

