#ifndef MODEL_H
#define MODEL_H

#include "Object3D.h"

/*Model - zlozony obiekt 3D ktory agreguje inne obiekty. Jest kompozytem.
--objectsVector_	- vector agregowanych obiektow
--model_			- macierz obrotu w globalnym ukladzie wspolrzednych
--rotationMatrix_	- macierz obrotu w lokalnym ukladzie wspolrzednych*/
class Model : public BasicObject {
protected:
	std::vector<BasicObject*> objectsVector_;
	glm::mat4 model_;
	glm::mat4 rotationMatrix_;
public:

	Model(const glm::vec3&, const glm::vec3&);
	virtual ~Model();

	/*add
	* Zwraca true (udalo sie dodac element), false (w kazdym innym)*/
	bool add(BasicObject*);

	/*remove
	* Zwraca true (podano poprawny indeks), false (proba odwolania sie do miejsca spoza obaszaru wektora)*/
	bool remove(unsigned int);

	/*getChild
	* Zwraca BasicObject* (podano poprawny indeks), nullptr (proba odwolania sie do miejsca spoza obaszaru wektora)*/
	BasicObject* getChild(unsigned int);

	/*bind_buffers
	* Wola metode bind_buffers agregowanych obiektow*/
	virtual void bind_buffers();

	/*free_buffers
	* Wola metode free_buffers agregowanych obiektow*/
	virtual void free_buffers();

	/*draw
	* Metoda rysowania. Jako argument bierze macierz przeksztalcenia obiektu wyzej w hierarchi (obiektu zawierajacego)
	* Ma domyslny argument, macierz jednostkowa.*/
	virtual void draw(glm::mat4& = glm::mat4());

	/*translate
	* przyjmuje wektor 3D przesuniêcia*/
	virtual void translate(const glm::vec3&);

	/*rotate - dwuargumentowa
	* Rotuje obiekt w lokalnym ukladzie odniesienia. Wszystkie rotacje wokol wlasnych osi TYLKO przez nia.
	* arg1: kat obrotu w stopniach, arg2: wektor obrotu*/
	virtual void rotate(float, const glm::vec3&);

	/*rotate - trzyargumentowa
	* Rotuje obiekt w globalnym ukladzie odniesienia. Wszystkie rotacje wokol osi globalnych,
	* lub wokol punktu TYLKO przez nia.
	* arg1: kat obrotu w stopniach, arg2: wektor obrotu, arg3: fixed point*/
	virtual void rotate(float, const glm::vec3&, const glm::vec3&);

	/*scale
	* skalowania wzgledem podanego wektora*/
	virtual void scale(const glm::vec3&);
};

class Cube : public Object3D {
public:

	Cube(const ShaderProgram*);
	~Cube();
};

class Cylinder : public Object3D {
public:
	Cylinder(unsigned int, unsigned int, const glm::vec3&, const ShaderProgram*);

};
#endif
