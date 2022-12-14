namespace Alex {

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

}
