/* Ian Calhoun
   Sean Butrica
   Comp 
   11/14/2019 */

#include <stdio.h>

int main()
{ 
  char line[83], filename[10], temp[2], file1[10], file2[10];
  int sectorsRead = 0, i, j, count = 0;
  char buffer[13312], doc[83];

  enableInterrupts();
  syscall(0,"SHELL>: ");
  syscall(1, line);

  if((line[0] == 't')&&(line[1] == 'y')&&(line[2] == 'p')&&(line[3] == 'e'))
    {

      syscall(3, line+5, buffer, &sectorsRead);
      
      if(sectorsRead != 0)
	{
	  syscall(0, buffer);
	}
      else
	{
	  syscall(0, "invalid file");
	}
      for(i = 0; i < 13312; i++)
	{
	  doc[i] = 0x0;
	}
    }
  else if((line[0] == 'e')&&(line[1] == 'x')&&(line[2] == 'e')&&(line[3] == 'c'))
    {

      syscall(4, line+5);
      
    }
  else if((line[0] == 'd')&&(line[1] == 'i')&&(line[2] =='r'))
    {
      for(i = 0; i < 13312; i++)
	{
	  buffer[i] = 0x0;
	}
      
      syscall(2, buffer, 2);

      for(i = 0; i <= 512; i = i + 32)
	{
	  if(buffer[i] != "\0")
	    {
	      for(j = 0; j < 6; j++)
		{
		  filename[j] = buffer[i+j];
		}
	      if(filename[j-1] == 0x0)
		{
		  filename[j-1] = 0xa;
		  filename[j] = 0xd;
		  filename[j+1] = 0x0;
		}
	      else
		{
		  filename[j] = 0xa;
		  filename[j+1] = 0xd;
		  filename[j+2] = 0x0;
		}
	      syscall(0, filename);
	    }
	}
    }
  else if((line[0] == 'd')&&(line[1] == 'e')&&(line[2] == 'l'))
    {
      syscall(7, line+4);

	  temp[0] = 0xa;
	  temp[1] = 0xd;
	  temp[2] = 0x0;
	  syscall(0, temp);
    }
  else if((line[0] =='c')&&(line[1] == 'o')&&(line[2] == 'p')&&(line[3] =='y'))
    {
      j = 0;
      i = 5;
      while(line[i] != ' ')
	{
	  file1[j] = line[i];
	  j = j + 1;
	  i = i + 1;
	}
      i = i + 1;

      syscall(3, file1, buffer, &sectorsRead);
      syscall(8, buffer, line+i, sectorsRead);
    }
  else if((line[0] == 'c')&&(line[1] == 'r')&&(line[2] == 'e')&&(line[3] == 'a')&&(line[4] == 't')&&(line[5] == 'e'))
    {
      int offset = 7;
      count = 0;
      while(1)
	{
	  for(i = 0; i < 83; i++)
	    {
	      doc[i] = 0x0;
	    }
	  syscall(1, doc);
	  for(j = 0; j < 83; j++)
	    {
	      if(doc[j] != 0x0)
		{
		  buffer[count+j] = doc[j];
		}
	      else
		{
		  count = count + j;
		  buffer[count+1] = 0xa;
		  buffer[count + 2] = 0xd;
		  buffer[count +3] = 0x0;
		  break;
		}
	    }
	  
	  if(doc[0] == 0x0)
	    {
	      break;
	    }
	}
      if(count/512 <= 1)
	{
	  sectorsRead = 1;
	}
      else
	{
	  sectorsRead = count/512;
	}
      syscall(8, buffer, line+offset, sectorsRead);
    }
  else if((line[0] == 'k')&&(line[1] == 'i')&&(line[2] == 'l')&&(line[3] == 'l'))
    {
      syscall(9, line+5);
    } 
}
