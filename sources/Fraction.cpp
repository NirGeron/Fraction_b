#include "Fraction.hpp"

#include <iostream>
#include <stdexcept>
#include <limits>
using namespace ariel;
using namespace std;
#define MAX_INT  std::numeric_limits<int>::max()
#define MIN_INT  std::numeric_limits<int>::min()

Fraction::Fraction() : numerator(0), denominator(1) {
}

Fraction::Fraction(float numerator_){
    this->numerator = (numerator_ * 1000);
    this->denominator = 1000;

}

Fraction::Fraction(int numerator_, int denominator_):numerator(numerator_),denominator(denominator_) {
    if (denominator_ < 0 ) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
        this->numerator = numerator_;
        this->denominator = denominator_;
    }
    if (denominator_ == 0) {
        throw std::invalid_argument("you can devide by 0");
    }
}

Fraction Fraction::reduce() {
    
    int reduced = Fraction::reduced(numerator, denominator);
    if(numerator!=0 && reduced!=0){
        numerator /= reduced;}
    denominator /= reduced;
    return *this;
}

int Fraction::reduced(int numerator_temp, int denominator_temp) {
    if(numerator_temp==0){
    return 1;}
    return denominator_temp == 0 ? numerator_temp : reduced(denominator_temp, numerator_temp % denominator_temp);

}

bool Fraction::number_check(std::string input){
    size_t itr=0;
    bool pos=true;
    if(input[0] != '-')
    {
        pos=false;
        itr=1;
    }
 
    for(size_t i = itr ; i < input.length() ; i++)
    {
        if(!std::isdigit(input[i])){
            return false;
        }
    }
    return true;
}

int Fraction::addOverflow(int temp, int temp_2)const{
    if ( (temp > MAX_INT - temp_2 && temp_2 > 0 ) || (temp < MIN_INT - temp_2 && temp_2 < 0)){
        throw std::overflow_error("ERR - Overflow");
        }
    else {
        return temp+temp_2;
    }
}

int Fraction::subOverflow(int temp, int temp_2)const{
    if ( (temp > MAX_INT + temp_2 && temp_2 < 0)||  (temp < MIN_INT + temp_2 && temp_2 > 0) ){
        throw std::overflow_error("ERR - Overflow");
    }
    else {
        return temp-temp_2;
    }
}
int Fraction::mulOverflow(int temp, int temp_2)const{
    long long num = static_cast<long long>(temp) * temp_2;
    if ((num < MIN_INT) || (num > MAX_INT)) {
        throw std::overflow_error("ERR - Overflow");
    }else {
        return temp * temp_2;
    }
}


std::istream& ariel::operator>>(std::istream& input, Fraction& frac) {
    int numerator_temp, denominator_temp;
    if (input >> numerator_temp >> denominator_temp) {
        frac.denominator = denominator_temp;
        frac.numerator = numerator_temp;
    } 
    else {
        input.setstate(std::ios::failbit);
        throw runtime_error("ERR - not a numerator and denominator.");
    }
     if(frac.getDenominator()==0){
        throw runtime_error("ERR - cant devide in 0");
    }
    return input;
}



Fraction ariel::Fraction::operator++(int)
{
    Fraction copy(*this);
    numerator += denominator;
    return copy;
};

Fraction Fraction::operator++(){
    numerator += denominator;
    return *this;
};



Fraction ariel::Fraction::operator--(int){
    Fraction temp(*this);
    numerator -= denominator;
    return temp;
};

Fraction Fraction::operator--(){
    numerator -= denominator;
    return *this;
};


Fraction Fraction::operator+(const Fraction& frac) const {
    
    int numerator_temp =addOverflow(mulOverflow(numerator, frac.denominator) , mulOverflow(denominator, frac.numerator));
    int denominator_temp = mulOverflow(denominator, frac.denominator);
    
    return Fraction(numerator_temp, denominator_temp).reduce();
}
Fraction ariel::operator+( const Fraction& fracconst ,float numerator_temp){
   Fraction frac_(numerator_temp);

    return (fracconst+frac_).reduce();
}
Fraction ariel::operator+(float numerator_temp,const Fraction& fracconst ){
   Fraction frac_(numerator_temp);

    return (fracconst+frac_).reduce();
}


Fraction Fraction::operator*(const Fraction& frac) const {
    int temp_1=reduced(numerator,denominator);
    int temp_2=reduced(frac.getDenominator(),frac.getNumerator());
    int numerator_temp =mulOverflow(numerator/temp_1 ,frac.numerator/temp_2);
    int den = mulOverflow( denominator/temp_1 ,frac.denominator/temp_2);
    return Fraction(numerator_temp, den).reduce();
}
Fraction ariel::operator*(float numerator_temp, const Fraction& franc){
    Fraction frac_(numerator_temp);
    return (franc*frac_).reduce();
}

Fraction ariel::operator*(const Fraction& franc,float numerator_temp){
    Fraction frac_(numerator_temp);
    return (franc*frac_).reduce();
}


Fraction Fraction::operator/(const Fraction& frac) const {
    int first_gcd=reduced(numerator,denominator);
    int second_gcd=reduced(frac.getDenominator(),frac.getNumerator());
    int numerator_temp = mulOverflow( numerator/first_gcd , frac.denominator/second_gcd);
    int denominator_temp =mulOverflow(denominator/first_gcd , frac.numerator/second_gcd);
    if(denominator_temp==0){throw std::runtime_error("ERR - cant devide in 0");}
    return Fraction(numerator_temp, denominator_temp).reduce();
}
Fraction ariel::operator/(const Fraction& frac, float numerator_temp) {
    Fraction num_fraction(numerator_temp);
    return (frac/num_fraction).reduce();
}
Fraction ariel::operator/( float numerator_temp,const Fraction& frac) {
    
    Fraction num_fraction(numerator_temp);
    return (num_fraction/frac).reduce();
}


Fraction Fraction::operator-(const Fraction& frac) const {
    int numerator_temp =subOverflow(mulOverflow(numerator, frac.denominator) , mulOverflow(denominator , frac.numerator));
    int den =mulOverflow(denominator , frac.denominator);
    return Fraction(numerator_temp, den).reduce();
}

Fraction ariel::operator-(const Fraction& frac, float numerator_temp) {
    Fraction frac_(numerator_temp);
    return (frac-frac_).reduce();
}
Fraction ariel::operator-(float numerator_temp,const Fraction& frac)  {
    Fraction frac_(numerator_temp);
    return (frac_-frac).reduce();
}



bool Fraction::operator>( float value)const{
    Fraction frac(value);
    return ((numerator * frac.denominator) > (frac.numerator * denominator));
}
bool Fraction::operator>(const Fraction& frac) const{


    return (numerator*frac.denominator > frac.numerator* denominator);
}
bool ariel::operator>(float numerator_temp, const Fraction& frac){
    Fraction frac_(numerator_temp);
    return (frac_>frac);
}


bool Fraction::operator!=(const Fraction& frac)const {
    return (numerator*frac.denominator != frac.numerator* denominator);
}
bool ariel::operator!=(float numerator_temp,const Fraction& frac){
    return ((frac-numerator_temp)!=0);
    };

bool Fraction::operator!=(float value)const{
    return ((numerator/denominator) != value);
};



bool Fraction::operator<(float value)const  {
    Fraction frac(value);
    return (numerator * frac.denominator < frac.numerator * denominator);
}

bool Fraction::operator<(const Fraction& frac)const {


    return (numerator * frac.denominator < frac.numerator * denominator);
}

bool ariel::operator<(float numerator_temp,const Fraction& frac){
    
    return (frac>numerator_temp);
}




bool Fraction::operator<=(const Fraction& frac)const {

    
    return ((numerator * frac.denominator) <= (frac.numerator * denominator));
}
bool Fraction::operator<=(float value) const {
    Fraction frac(value);
    return ((numerator * frac.denominator) <= (frac.numerator * denominator));
}


bool ariel::operator<=(float numerator_temp,const Fraction& frac){
    
    return (frac>=numerator_temp);
}



bool Fraction::operator==(const Fraction &frac) const{
    return (numerator * frac.denominator) == (frac.numerator * denominator);
};
bool Fraction::operator==(float numerator_temp ) const{
    if(numerator_temp>=1){
        return (((numerator/denominator)-numerator_temp) < 0.0001);
    }
    return (((static_cast<double>(numerator)/denominator)-numerator_temp) < 0.0001);
}


bool Fraction::operator>=(const Fraction& other) const{


    return (numerator*other.denominator >= other.numerator* denominator);
}
bool Fraction::operator>=(float value)  const{
    Fraction other(value);
    return ((numerator * other.denominator) >= (other.numerator * denominator));
    
}


bool ariel::operator>=(float numerator_temp,const Fraction& frac){
    Fraction temp(numerator_temp);
    return ((temp.numerator * frac.denominator) >= (frac.numerator * temp.denominator));
}

