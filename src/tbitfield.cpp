// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw len;
	BitLen = len;
	MemLen = BitLen/(sizeof(TELEM)*8) + 1;
	pMem = new TELEM [MemLen];
	for ( int i=0; i<MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[bf.MemLen];
    for (int i=0; i<MemLen; i++)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{ delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{if (n<0) throw n;
if (n>BitLen) throw n;
	return (n/(sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n<0) throw n;
	if (n>BitLen) throw n;
	TELEM temp = 1;
int Pos = n%(sizeof(TELEM)*8);
temp = temp << Pos;
return temp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{if (n<0) throw n;
if (n>BitLen) throw n;
	int Index = GetMemIndex(n);
TELEM mask = GetMemMask(n);
pMem[Index] = pMem[Index] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{if (n<0) throw n;
if (n>BitLen) throw n;
int Index = GetMemIndex(n);
TELEM mask = ~GetMemMask(n);
pMem[Index] = pMem[Index] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{if (n<0) throw n;
if (n>BitLen) throw n;
  TELEM tmp = GetMemMask(n);
	if ((pMem[GetMemIndex(n)] & tmp) == 0) return 0; else return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{if (BitLen != bf.BitLen)
		{
			delete[]pMem;
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
		}
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	return(*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{ if ((MemLen != bf.MemLen) || (BitLen != bf.BitLen)) return false;
	else
	{
		bool f = true;
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i]) f = false;
			break;
		}
		return f;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{ return !(bf == (*this));
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen <= bf.BitLen)
	{
		TBitField tmp(bf);
		for (int i = 0; i < MemLen; i++)
			tmp.pMem[i] |= pMem[i];
		return(tmp);
	}
	else
	{
		TBitField tmp(*this);
		for (int i = 0; i < bf.MemLen; i++)
			tmp.pMem[i] |= bf.pMem[i];
		return(tmp);
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{if (BitLen <= bf.BitLen)
	{
		TBitField tmp(bf), tmp2(bf.BitLen);
		tmp2 = tmp2 | (*this);
		for (int i = 0; i < bf.MemLen; i++)
			tmp.pMem[i] &= tmp2.pMem[i];
		return(tmp);
	}
	else
	{
		TBitField tmp(*this), tmp2((*this).BitLen);
		for (int i = 0; i < MemLen; i++)
			tmp.pMem[i] &= tmp2.pMem[i];
		return(tmp);
	}
}

TBitField TBitField::operator~(void) // отрицание
{TBitField tmp(BitLen);
for (int i=0; i<BitLen; i++)
	if (tmp.GetBit(i) == 1)
		tmp.ClrBit(i);
	else tmp.SetBit(i);
return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{int temp;
int Len;
istr >> Len;
TBitField tempbit(Len);
for (int i=0; i<tempbit.BitLen; i++)
	{ istr >> temp;
      if (temp == 1)
	  tempbit.SetBit(i);
	}
bf = tempbit;
return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{for (int i=0; i<bf.BitLen; i++)
if (bf.GetBit(i)) ostr<<i;
else ostr << 0;
return ostr;
}
