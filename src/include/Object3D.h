#ifndef OBJECT3D_H
#define OBJECT3D_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

#include "include/shprogram.h"

/*ToDo
2) Popraw wskazniki na smart_ptr
*/
/*BasicObject - abstrakcyjna klasa bazowa w hierarchii kompozytu. Nie musicie sie nia przejmowac.*/
class BasicObject {
public:
	glm::vec3 centerPoint_;
	glm::vec3 scaleVector_;

	BasicObject(const glm::vec3&, const glm::vec3&);
	virtual ~BasicObject() {}
	virtual void bind_buffers() = 0;
	virtual void free_buffers() = 0;
	virtual void draw(glm::mat4&) = 0;

	virtual void translate(const glm::vec3&) = 0;
	virtual void rotate(float, const glm::vec3&) = 0;
	virtual void rotate(float, const glm::vec3&, const glm::vec3&) = 0;
	virtual void scale(const glm::vec3&) = 0;
};

/*Object3D - podstawowy obiekt 3D, pelni role elementu w hierarchii kompozytu
--model_ - macierz obrotu w globalnym ukladzie wspolrzednych
--rotationMatrix_ - macierz obrotu w lokalnym ukladzie wspolrzednych*/
class Object3D : public BasicObject {
private:
	GLuint VAO, VBO, EBO;
	glm::mat4 model_;
	glm::mat4 rotationMatrix_;
	
public:
	std::vector<GLfloat> vertices_;
	std::vector<GLuint> indices_;

	const ShaderProgram* shader_;
	GLuint texture_;

	Object3D(const glm::vec3&, const glm::vec3&,const ShaderProgram*);
	virtual ~Object3D();

	/*bind_buffers 
	* Tutaj jest zalozenie ze mamy tylko dwa atrybuty:
	* 1.pozycje wierzcholka
	* 2.wspolrzedne tekstury
	* Jak potzrebujecie wiecej musiscie przeciazyc. Ew info do mniej to postaram sie dodac nowe funkcjonalnosci*/
	virtual void bind_buffers();
	virtual void free_buffers();

	/*draw
	* Metoda rysowania. Jako argument bierze macierz przeksztalcenia obiektu wyzej w hierarchi (obiektu zawierajacego)
	* Ma domyslny argument, macierz jednostkowa, dlatego mozna ja uzywac do rysowania obiektow, ktore nie sa przez nic agregowane*/
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

	/*set_geometry
	* Laczy dzialanie metod set_vertices, set_indices. Podajecie jej vetor'y vertices i indices*/
	void set_geometry(const std::vector<GLfloat>&, const std::vector<GLuint>&);
	void set_vertices(const std::vector<GLfloat>&);
	void set_indices(const std::vector<GLuint>&);
	void set_color(const glm::vec3&); // chwilowo bez implementacji

	/*set_shader
	* Przyjmuje wskaznik na shader i ustawia go jako shader dla danego obiektu.
	* Zwraca false (jezeli wskaznik = nullptr), true (w kazdym innym przypadku)
	* Zaleca sie weryfikowanie wartosci zwracanej przez metode*/
	bool set_shader(ShaderProgram*);

	/*set_texture
	* Przyjmuje indeks tekstury i ustawia ja jako teksture obiektu.
	* Indeks tekstury mozna uzyskac wywolujac funkcje LoadMipmapTexture() z pliku utils.h
	* By uproscic uzytkowanie zaleca sie nastepujacy sposob wywolania:
	* Object3D->set_texture(LoadMipmapTexture(GLuint texId, const char* fname));*/
	void set_texture(GLuint);
};
#endif // !OBJECT3D_H

