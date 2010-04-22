#include <iostream>

#define sizeof_bin(A) sizeof(A) * 8

//             89
// binary  = 0101.1001.00000000.00000000.00000000
//            5    9
// decimal = 1493172224

// [4bits][3bit][1.bit][9bit][8bit][7bit]          <=> raw
// c1	   c2    c3    c4    c5    c6     32bit   <=> raw

int	c1_size = 4;
int	c2_size = 3;
int	c3_size = 1;
int	c4_size = 9;
int	c5_size = 8;
int	c6_size = 7;

#define C1_SIZE 4
#define C2_SIZE 4
#define C1_SIZE 4
#define C1_SIZE 4
#define C1_SIZE 4
#define C1_SIZE 4


struct bits {
  unsigned int c1 : C1_SIZE;
  unsigned int c2 : c1;
  unsigned int c3 : 1;
  unsigned int c4 : 9;
  unsigned int f5 : 8;
  unsigned int f6 : 7;
} field;


int	MakePacket(int c1, int c2, int c3, int c4, int c5, int c6)
{
  int	raw;
  field.f1 = 15;

  //  std::cout << field << std::endl;

//   unsigned int test = c1 << sizeof_bin(c1) - c1_size;
//   std::cout << test << std::endl;
  //make raw
  return ReadPacket(int)raw;
}

int	ReadPacket(int raw)
{
  unsigned int	c1, c2, c3, c4, c5, c6;

  std::cout << sizeof_bin(raw) << std::endl;
  c1 = raw >> (sizeof_bin(raw) - c1_size);
  c2 = raw >> (sizeof_bin(raw) - c2_size);
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
  //  int raw = MakePacket(1, 2, 3, 4, 5, 6);
  //  ReadPacket(raw);
  ReadPacket(1234567891);
  return 0;
}
