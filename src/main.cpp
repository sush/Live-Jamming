#include <iostream>

#define sizeof_bin(A) (sizeof(A) * 8)

unsigned int		getField(unsigned char *_buffer, unsigned int bin_offset, unsigned int bin_len)
{
  unsigned int				value = 0;
  unsigned int				start_byte;
  unsigned int				end_byte;
  unsigned char				byte;
  
  start_byte = bin_offset / 8;
  end_byte = (bin_offset + bin_len) / 8;
  if ((bin_offset + bin_len) % 8 == 0)
    --end_byte;

  // byte1		byte2		byte3
  // xxxx.xxBB	      BBBB.BBBB		BBxx.xxxx
  // putting only data of start byte beginning at offset;
  byte = _buffer[start_byte] << (bin_offset % 8);
  byte = byte >> (bin_offset % 8);
  
  // 0000.00BB -> value;

  value = byte;
  for (unsigned int i = start_byte + 1; i <= end_byte; ++i)
    {
      if (i < end_byte || (bin_offset + bin_len) % 8 == 0)
	value = (value << 8) + _buffer[i];
      else
	{
	  byte = _buffer[i] >> (8 - (bin_offset + bin_len) % 8);
	  value = (value << (bin_offset + bin_len) % 8) + byte;
	}
    }
  return value;
}

void			setField(unsigned char *_buffer, unsigned int val, unsigned int bin_offset, unsigned int bin_len)
{
  unsigned int		start_byte, end_byte, tmp_val;
  unsigned char		byte, tmp;

  start_byte = bin_offset / 8;
  end_byte = (bin_offset + bin_len) / 8;
  if ((bin_offset + bin_len) % 8 == 0)
    --end_byte;
  
  std::cout << "start_byte = " << start_byte << std::endl;
  std::cout << "end_byte = " << end_byte << std::endl;

  // byte1		byte2		byte3
  // xxxx.xxBB	      BBBB.BBBB		BBxx.xxxx
  // putting only data of start byte beginning at offset;

  // zero other data of val
  std::cout << "val = " << val << std::endl;

  val = val << (sizeof_bin(val) - bin_len);
  val = val >> (sizeof_bin(val) - bin_len);

  std::cout << "val = " << val << std::endl;
  // bin_offset % 8 = 6
  // 0000.00BB		BBBB.BBBB	BBxx.xxxx	xxxx.xxxx
  // << bin_offset % 8
  // BBBB.BBBB		BBBB.xxxx	xxxx.xx00	0000.0000
  // >> sizeof(val) - (bin_offset % 8)
  // 0000.0000		0000.0000	0000.0000	00BB.BBBB

  //					     <------ bin_len --->
  // xxxx.xxxx	      xxxx.xxxx		xxxx.BBBB	BBBB.BBBB
  // << sizeof(val) - bin_len
  // BBBB.BBBB	      BBBB.0000		0000.0000	0000.0000
  // >> sizeof(val) - (8 - bin_offset % 8)
  // 0000.0000	      0000.0000		0000.0000	0000.00BB
  tmp_val = val << (sizeof_bin(val) - bin_len);
  tmp_val = tmp_val >> (sizeof_bin(val) - (8 - bin_offset % 8));
  
  // get byte remainder
  // zero data for future val of first byte
  // xxxx.xx00
  _buffer[0] = _buffer[0] >> (8 - bin_offset % 8);
  _buffer[0] = _buffer[0] << (8 - bin_offset % 8);
  // add bits of val contained in first byte
  _buffer[0] += tmp_val;
  
  byte = _buffer[0];
  byte = byte >> (8 - bin_offset % 8);
  byte = byte << (8 - bin_offset % 8);
  std::cout << "byte = " << (int)byte << std::endl;
  // xxxx.xxBB
  // 00xx.xxxx
  // xxxx.xx00
  
  
  tmp = val >> (sizeof(val) - bin_len);
}

// 48
//0011.0000

int		main(int argc, char *argv[])
{

  //[0]  1010.0010	162
  //[1]  1010.0011	163
  //[2]  1001.0101	149
  //[3]  0100.1001	73

  int		val = 1234543522;
  
  unsigned char	buffer[4] = {162, 163, 149, 73};
  std::cout << (int)getField((unsigned char *)&val, 23, 8) << std::endl;  // 0010...1010  42
  std::cout << "[0]" << (int) buffer[0] << " [1]" << (int) buffer[1] << " [2]" << (int)buffer[2] << " [3]" << (int) buffer[3] << std::endl;
  setField(buffer, 255, 0, 6);
  std::cout << "[0]" << (int) buffer[0] << " [1]" << (int) buffer[1] << " [2]" << (int)buffer[2] << " [3]" << (int) buffer[3] << std::endl;
  return 0;
}
