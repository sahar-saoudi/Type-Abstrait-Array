#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

//Classe Array
template<typename TYPE, size_t dim>
class Array {
	TYPE* tab;		//Pointeur associe a l'array en memoire dynamique
public:
	class iterator;
	class const_iterator;
	Array();													//Constructeur par defaut
	Array(const Array<TYPE, dim>&);								//Constructeur de copie
	Array(Array<TYPE, dim>&&);									//Constructeur de mouvement
	~Array();													//Destructeur

	size_t size() const;										//Methode retournant la dimension de l'array
	bool empty() const ;										//Methode identifiant si la dimension de l'array est nulle

	TYPE& operator[](size_t);									//Methode accedant a un element d'un array
	TYPE const operator [](size_t) const;						//Methode accedant a un element d'un array constant
	TYPE& at(size_t);											//Methode accedant a un element d'un array avec verification de la position
	TYPE const at(size_t) const;								//Methode accedant a un element d'un array avec verification de la position
	TYPE& front();												//Methode accedant au premier element d'un array
	TYPE const front() const;									//Methode accedant au premier element d'un array constant
	TYPE& back();												//Methode accedant au dernier element d'un array
	TYPE const back() const;									//Methode accedant au dernier element d'un array constant
	void fill(TYPE);											//Methode remplissant l'array d'une valeur
	void swap(Array<TYPE, dim>&);								//Methode echangeant les identificateurs de deux arrays de dimension identique
	template<size_t M>
	Array<TYPE, dim + M> const fusion(const Array<TYPE, M>&);	//Methode fusionnant deux arrays de dimension identiques ou differentes en un seul
	template<size_t M>
	Array<TYPE, M> const subset(size_t);						//Methode creant un sous-Array d'un Array principal
	iterator begin();											//Methode creant un iterateur pointant le debut d'un l'array modifiable
	iterator end();												//Methode creant un iterateur pointant la fin d'un l'array modifiable
	const_iterator const cbegin() const;						//Methode creant un iterateur pointant le debut d'un l'array constant
	const_iterator const cend() const;							//Methode creant un iterateur pointant la fin d'un l'array constant
	Array<TYPE, dim>& operator =(Array<TYPE, dim>&&);			//Affectateur de copie
	Array<TYPE, dim>& operator =(const Array<TYPE, dim>&);		//Affectateur de mouvement
};
#endif

/***************************************************************************************************/
//Classe iterator
template<typename TYPE, size_t dim>
class Array<TYPE, dim>::iterator {
	TYPE* P;		//Pointeur utilise pour iterer
public:
	iterator(TYPE* pointeur = nullptr) { P = pointeur; }
	iterator operator++() {
		P++;
		return *this;
	}
	iterator operator++(int) {
		iterator i(*this);	//Copie de l'iterator original avant la modification
		P++;
		return i;
	}
	iterator operator--() {
		P--;
		return *this;
	}
	iterator operator--(int) {
		iterator i(*this);	//Copie de l'iterator original avant la modification
		P--;
		return i;
	}
	bool operator==(const iterator& i) {
		return (P == i.P);
	}
	/*****************************************/
	bool operator!=(const iterator& i) {
		return (P != i.P);
	}
	/*****************************************/
	TYPE& operator*() {
		return *P;
	}
};

/***************************************************************************************************/
//Classe const_iterator
template<typename TYPE, size_t dim>
class Array<TYPE, dim>::const_iterator {
	TYPE* P;		//Pointeur utilise pour iterer
public:
	const_iterator(TYPE* pointeur = nullptr) { P = pointeur; };
	const_iterator operator++() {
		P++;
		return *this;
	}
	const_iterator operator++(int) {
		const_iterator i(*this);	//Copie de l'iterator original avant la modification
		P++;
		return i;
	}
	const_iterator operator--() {
		P--;
		return *this;
	}
	const_iterator operator--(int) {
		const_iterator i(*this);	//Copie de l'iterator original avant la modification
		P--;
		return i;
	}
	bool operator==(const const_iterator& i) {
		return (P == i.P);
	}
	/*****************************************/
	bool operator!=(const const_iterator& i) {
		return (P != i.P);
	}
	/*****************************************/
	const TYPE operator*() {
		return *P;
	}
};

/***************************************************************************************************/
//Methodes
template<typename TYPE, size_t dim>
Array<TYPE, dim>::Array() {
	tab = new TYPE[dim];
}
/*****************************************/
template<typename TYPE, size_t dim>
Array<TYPE, dim>::Array(const Array<TYPE, dim>& arr) {
	tab = new TYPE[dim];
	for (int index = 0; index < dim; index++) {
		*(tab + index) = *(arr.tab + index);
	}
}
/*****************************************/
template<typename TYPE, size_t dim>
Array<TYPE, dim>::Array(Array<TYPE, dim>&& arr) {
	tab = arr.tab;
	arr.tab = nullptr;
}
/*****************************************/
template<typename TYPE, size_t dim>
Array<TYPE, dim>::~Array() {
	delete[]tab;
	tab = nullptr;
}
/*****************************************/
template<typename TYPE, size_t dim>
size_t Array<TYPE, dim>::size() const{
	return dim;
}
/*****************************************/
template<typename TYPE, size_t dim>
bool Array<TYPE, dim>::empty() const{
	return (dim==0);
}
/*****************************************/
template<typename TYPE, size_t dim>
TYPE& Array<TYPE, dim>::operator[](size_t position) {
	return *(tab + position);
}
/*****************************************/
template<typename TYPE, size_t dim>
TYPE const Array<TYPE, dim>::operator[](size_t position) const {
	return *(tab + position);
}
/*****************************************/
template<typename TYPE, size_t dim>
TYPE& Array<TYPE, dim>::at(size_t position) {
	if (position >= dim) {
		throw std::out_of_range("index out of range");
	}
	return *(tab + position);
}
/*****************************************/
template<typename TYPE, size_t dim>
TYPE const Array<TYPE, dim>::at(size_t position) const {
	if (position >= dim) {
		throw std::out_of_range("index out of range");
	}
	return *(tab + position);
}
/*****************************************/
template<typename TYPE, size_t dim>
TYPE& Array<TYPE, dim>::front() {
	return *(tab);
}
/*****************************************/
template<typename TYPE, size_t dim>
TYPE const Array<TYPE, dim>::front() const {
	return *(tab);
}
/*****************************************/
template<typename TYPE, size_t dim>
TYPE& Array<TYPE, dim>::back() {
	return *(tab + dim - 1);
}
/*****************************************/
template<typename TYPE, size_t dim>
TYPE const Array<TYPE, dim>::back() const {
	return *(tab + dim - 1);
}
/*****************************************/
template<typename TYPE, size_t dim>
void Array<TYPE, dim>::fill(TYPE element) {
	for (int index = 0; index < dim; index++) {
		*(tab + index) = element;
	}
}
/*****************************************/
template<typename TYPE, size_t dim>
void Array<TYPE, dim>::swap(Array<TYPE, dim>& arr) {
	TYPE* p;
	p = tab;
	tab = arr.tab;
	arr.tab = p;
}
/*****************************************/
template<typename TYPE, size_t dim>
template<size_t M>
Array<TYPE, dim + M> const Array<TYPE, dim>::fusion(const Array<TYPE, M>& arr) {
	Array < TYPE, dim + M> tableau;
	for (int index = 0; index < dim; index++) {
		tableau[index] = *(tab + index);
	}
	for (int index = 0; index < M; index++) {
		tableau[dim + index] = arr[index];
	}
	return tableau;
}
/*****************************************/
template<typename TYPE, size_t dim>
template<size_t M >
Array<TYPE, M> const Array<TYPE, dim>::subset(size_t position) {
	Array < TYPE, M> tableau;
	for (int index = position; index < (position + M); index++) {
		tableau[index - position] = *(tab + index);
	}
	return tableau;
}
/*****************************************/
template<typename TYPE, size_t dim>
typename Array<TYPE, dim>::iterator
Array<TYPE, dim>::begin() {
	return iterator(tab);
}
/*****************************************/
template<typename TYPE, size_t dim>
typename Array<TYPE, dim>::iterator
Array<TYPE, dim>::end() {
	return iterator(tab + dim);
}
/*****************************************/
template<typename TYPE, size_t dim>
typename Array<TYPE, dim>::const_iterator
const Array<TYPE, dim>::cbegin() const {
	return const_iterator(tab);
}
/*****************************************/
template<typename TYPE, size_t dim>
typename Array<TYPE, dim>::const_iterator
const Array<TYPE, dim>::cend() const {
	return const_iterator(tab + dim);
}
/*****************************************/
template<typename TYPE, size_t dim>
Array<TYPE, dim>& Array<TYPE, dim>::operator =(Array<TYPE, dim>&& arr) {
	this.swap(arr);
	return *this;
}
/*****************************************/
template<typename TYPE, size_t dim>
Array<TYPE, dim>& Array<TYPE, dim>::operator =(const Array<TYPE, dim>& arr) {
	delete[]tab;
	tab = new TYPE[dim];
	for (int index = 0; index < dim; index++) {
		*(tab + index) = *(arr.tab + index);
	}
	return *this;
}