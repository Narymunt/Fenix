#pragma once

#include <math.h>
#include <vector>

class Tween
{
    
public:
    
    Tween();
    Tween(int iSize);                      // tutaj tworzymy na starcie tablice o wskazanym rozmiarze
    Tween(float fv1, float fv2, int i);    // podajemy dwie wartości i ilość elementów, które chcemy mieć w tablicy
    Tween(float fv1, float fv2, float f);  // automatycznie tworzy tablice o rozmiarze potrzebnym dla danych wartosci
    Tween(float fv1, float fv2);           // podajemy dwie wartości, nie tworzymy tablicy
    ~Tween();
    
    float       back(float t);
    float       back(float f1, float f2, float t);
    
    float       bounce(float t);
    float       bounce(float f1, float f2, float t);
    
    float       circ(float t);
    float       circ(float f1, float f2, float t);
    
    float       cubic(float t);
    float       cubic(float f1, float f2, float t);
    
    float       elastic(float t);
    float       elastic(float f1, float f2, float t);
    
    float       expo(float t);
    float       expo(float f1, float f2, float t);
    
    float       linear(float t);
    float       linear(float f1, float f2, float t);
    
    float       quad(float t);
    float       quad(float f1, float f2, float t);
    
    float       quart(float t);
    float       quart(float f1, float f2, float t);
    
    float       quint(float t);
    float       quint(float f1, float f2, float t);
    
    float       sine(float t);
    float       sine(float f1, float f2, float t);   
    
    float                   _fV1, _fV2;     // nasze dwa punkty, wartości pomiędzy którymi się poruszamy
    std::vector <float>     _pTable;        // tablica z wartościami, nie zawsze używana
    
};
