#include <iostream>

#define sizeof_bin(A) sizeof(A) * 8

//             89
// binary  = 0101.1001.00000000.00000000.00000000
//            5    9
// decimal = 1493172224

unsigned int	raw = 1493172224;
int	sessionID_size = 4;
int	champs2_size = 4;

int	MakePacket(int sessionID, int champs2)
{


}

int	ReadPacket(int)
{

}

void	print()
{
  unsigned int	first_octet = raw >> (sizeof_bin(raw)  - 8);
  unsigned int	sessionId   = raw >> (sizeof_bin(raw) * 8 - sessionID_size);
  unsigned int	champs2   = raw << sessionID_size >> (sizeof_bin(raw) - champs2_size);
  std::cout << "first_octet = " << first_octet << std::endl;
  std::cout << "sessionID = " << sessionId << std::endl;
  std::cout << "champs2 = " << champs2 << std::endl;
}

int	main()
{
  print();
  return 0;
}
