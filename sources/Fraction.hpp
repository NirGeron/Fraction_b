#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
namespace ariel{
class Fraction {
private:
    int numerator;
    int denominator;
    
    static int reduced(int numerator, int denominator);
        
public:
    Fraction();

    Fraction(float numerator);

    Fraction(int numerator, int den );
    

    int getNumerator()const{return this->numerator;}
    int getDenominator()const{return this->denominator;}
        
    bool number_check(std::string input);    
     
    int addOverflow(int temp,int temp_2)const;
    int subOverflow(int temp, int temp_2)const;
    int mulOverflow(int temp, int temp_2)const;

    Fraction operator+(const Fraction& frac) const;
    friend Fraction operator+( const Fraction& fracconst ,float numerator);
    friend Fraction operator+( float numerator,const Fraction& fracconst );
    
    friend std::istream &operator>>(std::istream& input, Fraction& fraction);
   
    Fraction operator-(const Fraction& frac) const;
    friend Fraction operator-( const Fraction& fracconst ,float numerator);
    friend Fraction operator-( float numerator,const Fraction& fracconst );

    Fraction operator*(const Fraction& frac) const;
    friend Fraction operator*(float numerator, const Fraction& frac);
    friend Fraction operator*( const Fraction& frac,float numerator );

    Fraction operator/(const Fraction& frac) const;
    friend Fraction operator/(const Fraction& frac, float numerator);
    friend Fraction operator/(float numerator,const Fraction& frac);

    Fraction operator++(int);
    Fraction operator++();


    Fraction operator--(int);
    Fraction operator--();

    bool operator>(float value)const ;
    bool operator>(const Fraction& frac)const ;
    friend bool operator>(float numerator,const Fraction& frac);
    friend bool operator>=(float numerator,const Fraction& frac);
    bool operator>=(float value) const;
    bool operator>=(const Fraction& frac)const ;
    
    bool operator<(float value)const ;
    bool operator<(const Fraction& frac) const;
    friend bool operator<(float numerator,const Fraction& frac);
    friend bool operator<=(float numerator,const Fraction& frac);
    bool operator<=(float value)const;
    bool operator<=(const Fraction& frac)const ;

    bool operator!=(const Fraction& frac)const ;
    friend bool operator!=(float numerator,const Fraction& frac);
    bool operator!=(float value)const;
    bool operator==(const Fraction& frac) const;
    bool operator==(float numerator ) const;
    Fraction reduce();

    friend std::ostream &operator<<(std::ostream& res, const Fraction& other){
    int tgcd=reduced(other.numerator , other.denominator);
    if(other<0){
        res <<'-'<< abs(other.numerator/tgcd)<< "/" << abs(other.denominator/tgcd);
    }
    else{ res << other.numerator/tgcd<< "/" << other.denominator/tgcd; }
    if(other.denominator==0){
        throw std::runtime_error("ERR - cant devide in 0");
        }
    return res;}

};

}
#endif 