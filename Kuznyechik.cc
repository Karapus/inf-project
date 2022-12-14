#include <cstddef>
#include <cassert>
#include <array>

namespace Kuznyechik {

static constexpr int BLOCK_SIZE = 16; // длина блока

// таблица прямого нелинейного преобразования
static std::byte Pi[] = {
    (std::byte)0xFC, (std::byte)0xEE, (std::byte)0xDD, (std::byte)0x11,
    (std::byte)0xCF, (std::byte)0x6E, (std::byte)0x31, (std::byte)0x16,
    (std::byte)0xFB, (std::byte)0xC4, (std::byte)0xFA, (std::byte)0xDA,
    (std::byte)0x23, (std::byte)0xC5, (std::byte)0x04, (std::byte)0x4D,
    (std::byte)0xE9, (std::byte)0x77, (std::byte)0xF0, (std::byte)0xDB,
    (std::byte)0x93, (std::byte)0x2E, (std::byte)0x99, (std::byte)0xBA,
    (std::byte)0x17, (std::byte)0x36, (std::byte)0xF1, (std::byte)0xBB,
    (std::byte)0x14, (std::byte)0xCD, (std::byte)0x5F, (std::byte)0xC1,
    (std::byte)0xF9, (std::byte)0x18, (std::byte)0x65, (std::byte)0x5A,
    (std::byte)0xE2, (std::byte)0x5C, (std::byte)0xEF, (std::byte)0x21,
    (std::byte)0x81, (std::byte)0x1C, (std::byte)0x3C, (std::byte)0x42,
    (std::byte)0x8B, (std::byte)0x01, (std::byte)0x8E, (std::byte)0x4F,
    (std::byte)0x05, (std::byte)0x84, (std::byte)0x02, (std::byte)0xAE,
    (std::byte)0xE3, (std::byte)0x6A, (std::byte)0x8F, (std::byte)0xA0,
    (std::byte)0x06, (std::byte)0x0B, (std::byte)0xED, (std::byte)0x98,
    (std::byte)0x7F, (std::byte)0xD4, (std::byte)0xD3, (std::byte)0x1F,
    (std::byte)0xEB, (std::byte)0x34, (std::byte)0x2C, (std::byte)0x51,
    (std::byte)0xEA, (std::byte)0xC8, (std::byte)0x48, (std::byte)0xAB,
    (std::byte)0xF2, (std::byte)0x2A, (std::byte)0x68, (std::byte)0xA2,
    (std::byte)0xFD, (std::byte)0x3A, (std::byte)0xCE, (std::byte)0xCC,
    (std::byte)0xB5, (std::byte)0x70, (std::byte)0x0E, (std::byte)0x56,
    (std::byte)0x08, (std::byte)0x0C, (std::byte)0x76, (std::byte)0x12,
    (std::byte)0xBF, (std::byte)0x72, (std::byte)0x13, (std::byte)0x47,
    (std::byte)0x9C, (std::byte)0xB7, (std::byte)0x5D, (std::byte)0x87,
    (std::byte)0x15, (std::byte)0xA1, (std::byte)0x96, (std::byte)0x29,
    (std::byte)0x10, (std::byte)0x7B, (std::byte)0x9A, (std::byte)0xC7,
    (std::byte)0xF3, (std::byte)0x91, (std::byte)0x78, (std::byte)0x6F,
    (std::byte)0x9D, (std::byte)0x9E, (std::byte)0xB2, (std::byte)0xB1,
    (std::byte)0x32, (std::byte)0x75, (std::byte)0x19, (std::byte)0x3D,
    (std::byte)0xFF, (std::byte)0x35, (std::byte)0x8A, (std::byte)0x7E,
    (std::byte)0x6D, (std::byte)0x54, (std::byte)0xC6, (std::byte)0x80,
    (std::byte)0xC3, (std::byte)0xBD, (std::byte)0x0D, (std::byte)0x57,
    (std::byte)0xDF, (std::byte)0xF5, (std::byte)0x24, (std::byte)0xA9,
    (std::byte)0x3E, (std::byte)0xA8, (std::byte)0x43, (std::byte)0xC9,
    (std::byte)0xD7, (std::byte)0x79, (std::byte)0xD6, (std::byte)0xF6,
    (std::byte)0x7C, (std::byte)0x22, (std::byte)0xB9, (std::byte)0x03,
    (std::byte)0xE0, (std::byte)0x0F, (std::byte)0xEC, (std::byte)0xDE,
    (std::byte)0x7A, (std::byte)0x94, (std::byte)0xB0, (std::byte)0xBC,
    (std::byte)0xDC, (std::byte)0xE8, (std::byte)0x28, (std::byte)0x50,
    (std::byte)0x4E, (std::byte)0x33, (std::byte)0x0A, (std::byte)0x4A,
    (std::byte)0xA7, (std::byte)0x97, (std::byte)0x60, (std::byte)0x73,
    (std::byte)0x1E, (std::byte)0x00, (std::byte)0x62, (std::byte)0x44,
    (std::byte)0x1A, (std::byte)0xB8, (std::byte)0x38, (std::byte)0x82,
    (std::byte)0x64, (std::byte)0x9F, (std::byte)0x26, (std::byte)0x41,
    (std::byte)0xAD, (std::byte)0x45, (std::byte)0x46, (std::byte)0x92,
    (std::byte)0x27, (std::byte)0x5E, (std::byte)0x55, (std::byte)0x2F,
    (std::byte)0x8C, (std::byte)0xA3, (std::byte)0xA5, (std::byte)0x7D,
    (std::byte)0x69, (std::byte)0xD5, (std::byte)0x95, (std::byte)0x3B,
    (std::byte)0x07, (std::byte)0x58, (std::byte)0xB3, (std::byte)0x40,
    (std::byte)0x86, (std::byte)0xAC, (std::byte)0x1D, (std::byte)0xF7,
    (std::byte)0x30, (std::byte)0x37, (std::byte)0x6B, (std::byte)0xE4,
    (std::byte)0x88, (std::byte)0xD9, (std::byte)0xE7, (std::byte)0x89,
    (std::byte)0xE1, (std::byte)0x1B, (std::byte)0x83, (std::byte)0x49,
    (std::byte)0x4C, (std::byte)0x3F, (std::byte)0xF8, (std::byte)0xFE,
    (std::byte)0x8D, (std::byte)0x53, (std::byte)0xAA, (std::byte)0x90,
    (std::byte)0xCA, (std::byte)0xD8, (std::byte)0x85, (std::byte)0x61,
    (std::byte)0x20, (std::byte)0x71, (std::byte)0x67, (std::byte)0xA4,
    (std::byte)0x2D, (std::byte)0x2B, (std::byte)0x09, (std::byte)0x5B,
    (std::byte)0xCB, (std::byte)0x9B, (std::byte)0x25, (std::byte)0xD0,
    (std::byte)0xBE, (std::byte)0xE5, (std::byte)0x6C, (std::byte)0x52,
    (std::byte)0x59, (std::byte)0xA6, (std::byte)0x74, (std::byte)0xD2,
    (std::byte)0xE6, (std::byte)0xF4, (std::byte)0xB4, (std::byte)0xC0,
    (std::byte)0xD1, (std::byte)0x66, (std::byte)0xAF, (std::byte)0xC2,
    (std::byte)0x39, (std::byte)0x4B, (std::byte)0x63, (std::byte)0xB6};

// таблица обратного нелинейного преобразования
static std::byte reverse_Pi[] = {
    (std::byte)0xA5, (std::byte)0x2D, (std::byte)0x32, (std::byte)0x8F,
    (std::byte)0x0E, (std::byte)0x30, (std::byte)0x38, (std::byte)0xC0,
    (std::byte)0x54, (std::byte)0xE6, (std::byte)0x9E, (std::byte)0x39,
    (std::byte)0x55, (std::byte)0x7E, (std::byte)0x52, (std::byte)0x91,
    (std::byte)0x64, (std::byte)0x03, (std::byte)0x57, (std::byte)0x5A,
    (std::byte)0x1C, (std::byte)0x60, (std::byte)0x07, (std::byte)0x18,
    (std::byte)0x21, (std::byte)0x72, (std::byte)0xA8, (std::byte)0xD1,
    (std::byte)0x29, (std::byte)0xC6, (std::byte)0xA4, (std::byte)0x3F,
    (std::byte)0xE0, (std::byte)0x27, (std::byte)0x8D, (std::byte)0x0C,
    (std::byte)0x82, (std::byte)0xEA, (std::byte)0xAE, (std::byte)0xB4,
    (std::byte)0x9A, (std::byte)0x63, (std::byte)0x49, (std::byte)0xE5,
    (std::byte)0x42, (std::byte)0xE4, (std::byte)0x15, (std::byte)0xB7,
    (std::byte)0xC8, (std::byte)0x06, (std::byte)0x70, (std::byte)0x9D,
    (std::byte)0x41, (std::byte)0x75, (std::byte)0x19, (std::byte)0xC9,
    (std::byte)0xAA, (std::byte)0xFC, (std::byte)0x4D, (std::byte)0xBF,
    (std::byte)0x2A, (std::byte)0x73, (std::byte)0x84, (std::byte)0xD5,
    (std::byte)0xC3, (std::byte)0xAF, (std::byte)0x2B, (std::byte)0x86,
    (std::byte)0xA7, (std::byte)0xB1, (std::byte)0xB2, (std::byte)0x5B,
    (std::byte)0x46, (std::byte)0xD3, (std::byte)0x9F, (std::byte)0xFD,
    (std::byte)0xD4, (std::byte)0x0F, (std::byte)0x9C, (std::byte)0x2F,
    (std::byte)0x9B, (std::byte)0x43, (std::byte)0xEF, (std::byte)0xD9,
    (std::byte)0x79, (std::byte)0xB6, (std::byte)0x53, (std::byte)0x7F,
    (std::byte)0xC1, (std::byte)0xF0, (std::byte)0x23, (std::byte)0xE7,
    (std::byte)0x25, (std::byte)0x5E, (std::byte)0xB5, (std::byte)0x1E,
    (std::byte)0xA2, (std::byte)0xDF, (std::byte)0xA6, (std::byte)0xFE,
    (std::byte)0xAC, (std::byte)0x22, (std::byte)0xF9, (std::byte)0xE2,
    (std::byte)0x4A, (std::byte)0xBC, (std::byte)0x35, (std::byte)0xCA,
    (std::byte)0xEE, (std::byte)0x78, (std::byte)0x05, (std::byte)0x6B,
    (std::byte)0x51, (std::byte)0xE1, (std::byte)0x59, (std::byte)0xA3,
    (std::byte)0xF2, (std::byte)0x71, (std::byte)0x56, (std::byte)0x11,
    (std::byte)0x6A, (std::byte)0x89, (std::byte)0x94, (std::byte)0x65,
    (std::byte)0x8C, (std::byte)0xBB, (std::byte)0x77, (std::byte)0x3C,
    (std::byte)0x7B, (std::byte)0x28, (std::byte)0xAB, (std::byte)0xD2,
    (std::byte)0x31, (std::byte)0xDE, (std::byte)0xC4, (std::byte)0x5F,
    (std::byte)0xCC, (std::byte)0xCF, (std::byte)0x76, (std::byte)0x2C,
    (std::byte)0xB8, (std::byte)0xD8, (std::byte)0x2E, (std::byte)0x36,
    (std::byte)0xDB, (std::byte)0x69, (std::byte)0xB3, (std::byte)0x14,
    (std::byte)0x95, (std::byte)0xBE, (std::byte)0x62, (std::byte)0xA1,
    (std::byte)0x3B, (std::byte)0x16, (std::byte)0x66, (std::byte)0xE9,
    (std::byte)0x5C, (std::byte)0x6C, (std::byte)0x6D, (std::byte)0xAD,
    (std::byte)0x37, (std::byte)0x61, (std::byte)0x4B, (std::byte)0xB9,
    (std::byte)0xE3, (std::byte)0xBA, (std::byte)0xF1, (std::byte)0xA0,
    (std::byte)0x85, (std::byte)0x83, (std::byte)0xDA, (std::byte)0x47,
    (std::byte)0xC5, (std::byte)0xB0, (std::byte)0x33, (std::byte)0xFA,
    (std::byte)0x96, (std::byte)0x6F, (std::byte)0x6E, (std::byte)0xC2,
    (std::byte)0xF6, (std::byte)0x50, (std::byte)0xFF, (std::byte)0x5D,
    (std::byte)0xA9, (std::byte)0x8E, (std::byte)0x17, (std::byte)0x1B,
    (std::byte)0x97, (std::byte)0x7D, (std::byte)0xEC, (std::byte)0x58,
    (std::byte)0xF7, (std::byte)0x1F, (std::byte)0xFB, (std::byte)0x7C,
    (std::byte)0x09, (std::byte)0x0D, (std::byte)0x7A, (std::byte)0x67,
    (std::byte)0x45, (std::byte)0x87, (std::byte)0xDC, (std::byte)0xE8,
    (std::byte)0x4F, (std::byte)0x1D, (std::byte)0x4E, (std::byte)0x04,
    (std::byte)0xEB, (std::byte)0xF8, (std::byte)0xF3, (std::byte)0x3E,
    (std::byte)0x3D, (std::byte)0xBD, (std::byte)0x8A, (std::byte)0x88,
    (std::byte)0xDD, (std::byte)0xCD, (std::byte)0x0B, (std::byte)0x13,
    (std::byte)0x98, (std::byte)0x02, (std::byte)0x93, (std::byte)0x80,
    (std::byte)0x90, (std::byte)0xD0, (std::byte)0x24, (std::byte)0x34,
    (std::byte)0xCB, (std::byte)0xED, (std::byte)0xF4, (std::byte)0xCE,
    (std::byte)0x99, (std::byte)0x10, (std::byte)0x44, (std::byte)0x40,
    (std::byte)0x92, (std::byte)0x3A, (std::byte)0x01, (std::byte)0x26,
    (std::byte)0x12, (std::byte)0x1A, (std::byte)0x48, (std::byte)0x68,
    (std::byte)0xF5, (std::byte)0x81, (std::byte)0x8B, (std::byte)0xC7,
    (std::byte)0xD6, (std::byte)0x20, (std::byte)0x0A, (std::byte)0x08,
    (std::byte)0x00, (std::byte)0x4C, (std::byte)0xD7, (std::byte)0x74};

// вектор линейного преобразования
static std::byte l_vec[] = {
    (std::byte)1,   (std::byte)148, (std::byte)32,  (std::byte)133,
    (std::byte)16,  (std::byte)194, (std::byte)192, (std::byte)1,
    (std::byte)251, (std::byte)1,   (std::byte)192, (std::byte)194,
    (std::byte)16,  (std::byte)133, (std::byte)32,  (std::byte)148};

using BlockTy = std::array<std::byte, BLOCK_SIZE>;

// массив для хранения констант
static std::array<BlockTy, 32> IterC;
// массив для хранения ключей
static std::array<BlockTy, 10> IterKey;


// функция X
static auto X(BlockTy A, BlockTy B) {
  BlockTy Res;
  for (int i = 0; i < BLOCK_SIZE; i++)
    Res[i] = (A[i] ^ B[i]);
  return Res;
}


    // Функция S
    static std::byte* GOST_Kuz_S(std::byte* in_data)
    {
        int i;
        std::byte* out_data = new std::byte[in_data.length];
        for (i = 0; i < BLOCK_SIZE; i++)
        {
            int data = in_data[i];
            if (data < 0)
            {
                data = data + 256;
            }
            out_data[i] = Pi[data];
        }
        return out_data;
    }

    // умножение в поле Галуа
    static std::byte GOST_Kuz_GF_mul(std::byte a, std::byte b)
    {
        byte c = 0;
        byte hi_bit;
        int i;
        for (i = 0; i < 8; i++)
        {
            if ((b & 1) == 1)
                c ^= a;
            hi_bit = a & 0x80;
            a <<= 1;
            if (hi_bit < 0)
                a ^= 0xc3; //полином  x^8+x^7+x^6+x+1
            b >>= 1;
        }
        return c;
    }

    // функция R сдвигает данные и реализует уравнение, представленное для расчета L-функции
    static std::byte* GOST_Kuz_R(std::byte* state)
    {
        int i;
        std::byte a_15 = 0;
        std::byte* internal = new byte[16];
        for (i = 15; i >= 0; i--)
        {
            if (i == 0)
                internal[15] = state[i];
            else
                internal[i - 1] = state[i];
            a_15 ^= GOST_Kuz_GF_mul(state[i], l_vec[i]);
        }
        internal[15] = a_15;
        return internal;
    }

    static std::byte* GOST_Kuz_L(std::byte* in_data)
    {
        int i;
        std::byte* out_data = new byte[in_data.length];
        std::byte* internal = in_data;
        for (i = 0; i < 16; i++)
        {
            internal = GOST_Kuz_R(internal);
        }
        out_data = internal;
        return out_data;
    }

    static private std::byte* GOST_Kuz_reverse_S(std::byte* in_data)
    {
        int i;
        std::byte* out_data = new byte[in_data.length];
        for (i = 0; i < BLOCK_SIZE; i++)
        {
            int data = in_data[i];
            if (data < 0)
            {
                data = data + 256;
            }
            out_data[i] = reverse_Pi[data];
        }
        return out_data;
    }

static auto reverse_R(BlockTy State)
{
    std::byte A0 = State[15];
    BlockTy Res;
    for (int i = 1; i < 16; i++)
    {
        Res[i] = State[i - 1];
        A0 ^= GF_mul(Res[i], l_vec[i]);
    }
    Res[0] = A0;
    return Res;
}

static auto reverse_L(BlockTy In)
{
    BlockTy Out = In;
    for (int i = 0; i < 16; i++)
    	Out = reverse_R(Out);
    return Out;
}

// функция расчета констант
static void GetC()
{
  std::array<BlockTy, 32> IterNum;
    for (int i = 0; i < 32; i++)
    {
    	for(int j = 0; j < BLOCK_SIZE; j++)
    		IterNum[i][j] = std::byte{0};
        IterNum[i][0] = (std::byte)(i+1);
    }
    for (int i = 0; i < 32; i++)
    {
    	IterC[i] = L(IterNum[i]);
    }
}
// функция, выполняющая преобразования ячейки Фейстеля
static auto F(BlockTy InKey1, BlockTy InKey2, BlockTy IterConst)
{
  BlockTy Internal;
  auto OutKey2 = InKey1;
  Internal = L(S(X(InKey1, IterConst)));
      auto OutKey1 = X(Internal, InKey2);
      std::array<BlockTy, 2> Key;
      Key[0] = OutKey1;
      Key[1] = OutKey2;
      return Key;
}
// функция расчета раундовых ключей
void Expand_Key(BlockTy Key1, BlockTy Key2)
{
    std::array<BlockTy, 2> Iter12, Iter34;
    GetC();
    IterKey[0] = Key1;
    IterKey[1] = Key2;
    Iter12[0] = Key1;
    Iter12[1] = Key2;
    for (int i = 0; i < 4; i++)
    {
        Iter34 = F(Iter12[0], Iter12[1], IterC[0 + 8 * i]);
        Iter12 = F(Iter34[0], Iter34[1], IterC[1 + 8 * i]);
        Iter34 = F(Iter12[0], Iter12[1], IterC[2 + 8 * i]);
        Iter12 = F(Iter34[0], Iter34[1], IterC[3 + 8 * i]);
        Iter34 = F(Iter12[0], Iter12[1], IterC[4 + 8 * i]);
        Iter12 = F(Iter34[0], Iter34[1], IterC[5 + 8 * i]);
        Iter34 = F(Iter12[0], Iter12[1], IterC[6 + 8 * i]);
        Iter12 = F(Iter34[0], Iter34[1], IterC[7 + 8 * i]);

        IterKey[2 * i + 2] = Iter12[0];
        IterKey[2 * i + 3] = Iter12[1];
    }
}
// функция шифрования блока
auto Encript(BlockTy In)
{
    BlockTy Out = In;
    for(int i = 0; i < 9; i++)
    {
    	Out = L(S(X(IterKey[i], Out)));
    }
    Out = X(Out, IterKey[9]);
    return Out;
}
//функция расшифрования блока
auto Decript(BlockTy In)
{
    BlockTy Out = In;
    Out = X(Out, IterKey[9]);
    for(int i = 8; i >= 0; i--)
    {
    	Out = X(IterKey[i], reverse_S(reverse_L(Out)));
    }
    return Out;
}
} // namespace Kuznyechik


int main() 
{
  Kuznyechik::BlockTy Key1 = {(std::byte)0x77, (std::byte)0x66, (std::byte)0x55, (std::byte)0x44, (std::byte)0x33, (std::byte)0x22, (std::byte)0x11, (std::byte)0x00, (std::byte)0xff,  (std::byte) 0xee, (std::byte) 0xdd, (std::byte) 0xcc, (std::byte) 0xbb, (std::byte) 0xaa, (std::byte) 0x99, (std::byte) 0x88};
  Kuznyechik::BlockTy Key2 = 
  {(std::byte) 0xef, (std::byte) 0xcd, (std::byte) 0xab, (std::byte) 0x89, (std::byte)0x67, (std::byte)0x45, (std::byte)0x23, (std::byte) 0x01,(std::byte)
    0x10, (std::byte)0x32, (std::byte)0x54, (std::byte)0x76, (std::byte) 0x98, (std::byte) 0xba, (std::byte) 0xdc, (std::byte) 0xfe};
  Kuznyechik::BlockTy Blk{(std::byte)0x88 ,(std::byte)0x99 ,(std::byte)0xaa ,(std::byte)0xbb ,(std::byte)0xcc ,(std::byte)0xdd ,(std::byte)0xee ,(std::byte)0xff ,(std::byte)0x00 ,(std::byte)0x77 ,(std::byte)0x66 ,(std::byte)0x55 ,(std::byte)0x44 ,(std::byte)0x33 ,(std::byte)0x22 ,(std::byte)0x11};
  Kuznyechik::Expand_Key(Key1, Key2);
  auto EncriptBlk = Kuznyechik::Encript(Blk);
  auto DecriptBlk = Kuznyechik::Decript(EncriptBlk);
  for (int i = 0; i < Kuznyechik::BLOCK_SIZE; ++i)
    assert(Blk[i] == DecriptBlk[i]);
}
