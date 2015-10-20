// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
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
    delete [] pMem;
    pMem = new TELEM [bf.MemLen];
    for (int i=0; i<MemLen; i++)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{ delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{return n/(sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{int Pos = n%(sizeof(TELEM)*8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{int Index = GetMemIndex(n);
TELEM mask = GetMemMask(n);
pMem[Index] = pMem[Index] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{int Index = GetMemIndex(n);
TELEM mask = ~GetMemMask(n);
pMem[Index] = pMem[Index] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{if (MemLen != bf.MemLen)
{ delete [] pMem;
 pMem = new TELEM [bf.MemLen];
 MemLen = bf.MemLen;
}
for (int i=0; i<MemLen; i++)
	pMem[i] = bf.pMem[i];
return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{ for (int i = 0; i < BitLen; i++)
if ((*this).GetBit(i) != bf.GetBit) 
  return 0;
return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{ for (int i = 0; i < BitLen; i++)
if ((*this).GetBit(i) == bf.GetBit) 
  return 0;
return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{TBitField tmp(BitLen);
for (int i=0; i<MemLen; i++)
	tmp.pMem[i] = pMem[i] | bf.pMem[i];
return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{TBitField tmp(BitLen);
for (int i=0; i<MemLen; i++)
	tmp.pMem[i] = pMem[i] & bf.pMem[i];
return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{TBitField tmp(BitLen);
for (int i=0; i<MemLen; i++)
	tmp.pMem[i] = ~pMem[i];
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
