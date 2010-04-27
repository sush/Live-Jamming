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
  unsigned char		save_before, save_after;

  if (!bin_len)  // bin_len = 0 nothing to set
    return;

  start_byte = bin_offset / 8;
  end_byte = (bin_offset + bin_len) / 8;
  if ((bin_offset + bin_len) % 8 == 0)
    --end_byte;
  
  // byte1		byte2		byte3
  // xxxx.xxBB	      BBBB.BBBB		BBxx.xxxx
  // putting only data of start byte beginning at offset;

  // zero other data of val
  val = val << (sizeof_bin(val) - bin_len);
  val = val >> (sizeof_bin(val) - bin_len);

  // THIS IS TO HELP IF YOU MODIFY THIS FUNCTION
  //
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
  /////////////////////////////////////////////////////

  // save only data of first byte before val (other bits are zero ed)
  // xxxx.xxBB
  save_before = _buffer[start_byte];
  save_before = save_before >> (8 - bin_offset % 8);
  save_before = save_before << (8 - bin_offset % 8);
  // xxxx.xx00

  // save data of last byte after val (other bits are zero ed)
  // BBBB.Bxxx
  save_after = _buffer[end_byte];
  if ((bin_offset + bin_len) % 8 == 0)
    save_after = 0;
  else
    {
      save_after = save_after << ((bin_offset + bin_len) % 8);
      save_after = save_after >> ((bin_offset + bin_len) % 8);
    }
  // 0000.0xxx

  // first byte = first byte bits of val + save_before
  tmp_val = val << (sizeof_bin(val) - bin_len);
  tmp_val = tmp_val >> (sizeof_bin(val) - (8 - bin_offset % 8));
  _buffer[start_byte] = save_before + tmp_val;

  // intermediate bytes
  for (int i = start_byte + 1; i < end_byte; ++i)
    {
      tmp_val = val << (sizeof_bin(val) - bin_len + (8 - bin_offset % 8) + 8 * (i - start_byte - 1));
      tmp_val = tmp_val >> (sizeof_bin(val) - 8);
      _buffer[i] = tmp_val;
    }

  // last byte = last bits of val + save_after
  //  tmp_val = val
  if ((bin_offset + bin_len) % 8 == 0)
    tmp_val = val << (sizeof_bin(val) - 8);
  else
    tmp_val = val << (sizeof_bin(val) - ((bin_offset + bin_len) % 8));
  tmp_val = tmp_val >> (sizeof_bin(val) - 8);//((bin_offset + bin_len) % 8 - (8 - (bin_offset + bin_len) % 8)));
  if (start_byte == end_byte)
    _buffer[end_byte] = save_before + tmp_val + save_after;
  else
    _buffer[end_byte] = tmp_val + save_after;
  // xxxx.xxBB
  // 00xx.xxxx
  // xxxx.xx00
}

int		main(int argc, char *argv[])
{

  //[0]  1010.0010	162
  //[1]  1010.0011	163
  //[2]  1001.0101	149
  //[3]  0100.1001	73

  int		val = 1234543522;
  
  unsigned char	buffer[4] = {42, 42, 42, 42};
  setField(buffer, 65535, 7, 23);
  std::cout << (int)getField((unsigned char *)&val, 23, 8) << std::endl;  // 0010...1010  42
  std::cout << "[0]" << (int) buffer[0] << " [1]" << (int) buffer[1] << " [2]" << (int)buffer[2] << " [3]" << (int) buffer[3] << std::endl;
  // 1010.0010
  // 1011.1110
  // 1111.1111		1111.1111
  // 1100.0000		0000.
  setField(buffer, 0, 16, 8);
  std::cout << "get = " <<(int)getField(buffer, 7, 23) << std::endl;  // 0010...1010  42  
  std::cout << "[0]" << (int) buffer[0] << " [1]" << (int) buffer[1] << " [2]" << (int)buffer[2] << " [3]" << (int) buffer[3] << std::endl;
  return 0;
}
