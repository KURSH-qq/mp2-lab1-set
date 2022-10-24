#include <tbitfield.h>

using namespace std;


typedef unsigned int TELEM;


TBitField::TBitField(int len)
{
    if (len > 0)
    {
        BitLen = len;
        MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = 0;
        }
    }
    else
    {
        throw exception("negative len");
    }
    
}

TBitField::TBitField(const TBitField& bf)
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const
{
    return n / (8 * sizeof(TELEM));

}

TELEM TBitField::GetMemMask(const int n) const
{
    return 1 << n % (sizeof(TELEM) * 8); //подумать
}

int TBitField::GetLength() const
{
    return BitLen;
}

void TBitField::SetBit(const int n)
{
    if ((n < BitLen) && (n >= 0))
    {
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
    }
    else
    {
        throw exception("wrong index");
    }
    

}

void TBitField::ClrBit(const int n)
{
    if ((n < BitLen) && (n >= 0))
    {
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~(GetMemMask(n));
    }
    else
    {
        throw exception("wrong index");
    }
    

}

int TBitField::GetBit(const int n) const
{
    if ((n < BitLen) && (n >= 0))
    {
        return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> n;
    }
    else
    {
        throw exception("wrong index");
    }
    
}

TBitField& TBitField:: operator=(const TBitField& bf)
{

    if (this == &bf)
    {
        return *this;
    }

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete[]pMem;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }

    return *this;

}

int TBitField:: operator==(const TBitField& bf) const
{
    if (BitLen != bf.BitLen)
    {
        return 0;
    }
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
        {
            return 0;
        }
    }
    return 1;

}

int TBitField:: operator!=(const TBitField& bf) const
{
    if (*this == bf)
    {
        return 0;
    }
    return 1; 
}


TBitField TBitField:: operator&(const TBitField& bf)
{   
    TBitField result(max(BitLen,bf.BitLen));
    for (int i = 0; i < min(MemLen,bf.MemLen); i++)
    {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return result;
}

TBitField TBitField:: operator|(const TBitField& bf)
{
    if (BitLen > bf.BitLen)
    {
        TBitField tmp(*this);
        for (int i = 0; i < bf.MemLen; i++)
        {
            tmp.pMem[i] |= bf.pMem[i];
        }
        return tmp;
    }
    else
    {
        TBitField tmp(bf);
        for (int i = 0; i < MemLen; i++)
        {
            tmp.pMem[i] |= pMem[i];
        }
        return tmp;
    }
}

TBitField TBitField:: operator~()
{
    TBitField result(*this);
    for (int i = 0; i < BitLen; i++) {
        if (GetBit(i))
        {
            result.ClrBit(i);
        }
        else
        {
            result.SetBit(i);
        }
    }
    return result;
}


istream& operator>>(istream& istr, TBitField& bf)
{
    int len;
    int el;
    cout << "enter length of bitfield: " << endl;
    cin >> len;
    TBitField result(len);
    for (int i = 0; i < len; i++)
    {
        cout << "enter the bit: ";
        cin >> el;
        if (el == 0)
        {
            result.ClrBit(i);
        }
        else
        {
            result.SetBit(i);
        }
    }
    bf = result;
    return istr;
}


ostream& operator<<(ostream &ostr, const TBitField &bf)
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        ostr << bf.GetBit(i) << " ";
    }
    ostr << endl;
    return ostr;
}





