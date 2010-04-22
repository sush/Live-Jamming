#include <iostream>
#include <bitset>
#include <stdio.h>
#include <string.h>
#define sizeof_bin(A) sizeof(A) * 8

//             89
// binary  = 0101.1001.00000000.00000000.00000000
//            5    9
// decimal = 1493172224

// [4bits][3bit][1.bit][9bit][8bit][7bit]          <=> raw
// c1	   c2    c3    c4    c5    c6     32bit   <=> raw

int	c1_size = 16;
int	c2_size = 6;

<<<<<<< .mine
=======
#define C1_SIZE 4
#define C2_SIZE 4
#define C1_SIZE 4
#define C1_SIZE 4
#define C1_SIZE 4
#define C1_SIZE 4

>>>>>>> .r96

struct bits {
<<<<<<< .mine
  unsigned int f1 : 16;
  unsigned int f2 : 6;
  unsigned int f3 : 10;
=======
  unsigned int c1 : C1_SIZE;
  unsigned int c2 : c1;
  unsigned int c3 : 1;
  unsigned int c4 : 9;
  unsigned int f5 : 8;
  unsigned int f6 : 7;
>>>>>>> .r96
} field;


int	MakePacket(int c1, int c2)
{
  int	raw;
  char buffer[4];

  field.f1 = c1;
  field.f2 = c2;
  memcpy(buffer, &field, 2);

  for (unsigned int i = 0; i < 4; ++i)
    std::cout << (int)buffer[i] << std::endl;



//   field.f1 = 15;

  //  std::cout << field << std::endl;

//   unsigned int test = c1 << sizeof_bin(c1) - c1_size;
//   std::cout << test << std::endl;
  //make raw
<<<<<<< .mine

//   std::bitset<10> mybits;

//   mybits[0] = 0001;
//   mybits[1] = 0010;
//   mybits[2] = 0011;
//   mybits[3] = 0100;

//   std::cout << mybits.test(3) << std::endl;
//   std::cout << mybits.to_string() << std::endl;
//   std::cout << mybits.to_ulong() << std::endl;

  



//          309                                           280
//   0000 0001 0011 0101                          0000 0001 0001 1000


//   res[0] = 00000001;
//   res[1] = 00110101;
//   res[2] = 00000001;
//   res[3] = 00011000;



//   if(number <= 1) {
//     cout << number;
//     return;
//   }

// char* buffer;

//   std::bitset<16> sessionId = c1;
//   std::bitset<8> buff1;
//   std::bitset<8> buff2;

//   for (unsigned int i = 0; i < 16; ++i) {
//     if (i < 8)
//       buff1[i] = sessionId[i];
//     else
//       buff2[i] = sessionId[i];
//   }


//   std::cout << "BUFF1 : " << std::endl;
//   std::cout << buff1.to_string() << std::endl;
//   std::cout << buff1.to_ulong() << std::endl;
//   std::cout << "BUFF2 : " << std::endl;
//   std::cout << buff2.to_string() << std::endl;
//   std::cout << buff2.to_ulong() << std::endl;





  return raw;
=======
  return ReadPacket(int)raw;
>>>>>>> .r96
}

int	ReadPacket(unsigned int raw)
{
  unsigned int	c1, c2, c3, c4, c5, c6;

  std::cout << sizeof_bin(raw) << std::endl;
  c1 = raw >> (sizeof_bin(raw) - c1_size);
  c2 = raw << c1_size >> (sizeof_bin(raw) - c2_size);
  std::cout << "C1 = " << c1 << std::endl;
  std::cout << "C2 = " << c2 << std::endl;

  // get and print values from raw
}

// void	print()
// {
//   unsigned int	first_octet = raw >> (sizeof_bin(raw)  - 8);
//   unsigned int	sessionId   = raw >> (sizeof_bin(raw) * 8 - sessionID_size);
//   unsigned int	champs2   = raw << sessionID_size >> (sizeof_bin(raw) - champs2_size);
//   std::cout << "first_octet = " << first_octet << std::endl;
//   std::cout << "sessionID = " << sessionId << std::endl;
//   std::cout << "champs2 = " << champs2 << std::endl;
// }

int	main()
{
  //  ReadPacket(MakePacket(1, 2, 3, 4, 5, 6));
  //  ReadPacket(raw);
  //  ReadPacket(1771438803);
  MakePacket(380, 209);
  //binary(1234567891);

  return 0;
}
