#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    if (mp <= 0)
    {
        throw exception("ffff");
    }
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.GetMaxPower();
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    TBitField result(BitField);
    return result;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if ((MaxPower == s.MaxPower) && (BitField == s.BitField))
    {
        return 1;
    }
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (*this == s)
    {
        return 0;
    }
    return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet result(max(MaxPower, s.MaxPower));
    result.BitField = BitField|s.BitField;
    return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet result(*this);
    result.BitField.SetBit(Elem);
    return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet result(*this);
    result.BitField.ClrBit(Elem);
    return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet result(max(MaxPower, s.MaxPower));
    result.BitField = BitField&s.BitField;
    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet result(MaxPower);
    result.BitField = ~BitField;
    return result;
    
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i))
        {
            ostr << i << endl;
        }
    }
    return ostr;
}
