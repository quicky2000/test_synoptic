#include "synoptic.h"
#include "color_zone.h"
#include "my_bmp.h"
#include "text_field_zone.h"
#include "drawing_zone.h"
#include <unistd.h>

int main(void)
{
  
#if 0
  lib_bmp::my_bmp l_input_bmp("test_grid.bmp");
  const uint32_t l_size_min = 153;
  uint32_t l_width = l_input_bmp.get_width();
  uint32_t l_height = l_input_bmp.get_height();
  std::cout << "Width = " << l_width << std::endl ;
  std::cout << "Heigth = " << l_height << std::endl ;
  if(l_width < l_size_min || l_height < l_size_min)
    {
      std::cout << "Error image must be at least 153*153" << std::endl ;
      exit(-1);
    }

  for(uint32_t l_line = 0; l_line < 16 ; ++l_line)
    {
      uint32_t l_y_min = (l_line +1 ) * 9;
      for(uint32_t l_column = 0; l_column < 16 ; ++l_column)
	{
          uint8_t l_char_representation = l_column + 16 * l_line;
          if(l_char_representation >= ' ' && l_char_representation <= '~')
            {
              uint32_t l_x_min = (l_column +1 ) * 9;
              uint64_t l_coded_value = 0;
              for(uint32_t l_y = l_y_min ; l_y < l_y_min + 8 ; ++l_y)
                {
                  for(uint32_t l_x = l_x_min ; l_x < l_x_min + 8 ; ++l_x)
                    {
                      lib_bmp::my_color l_black(0,0,0);
                      lib_bmp::my_color_alpha l_color = l_input_bmp.get_pixel_color(l_x,l_y);
#ifdef DEBUG
                      l_color.display();
                      std::cout << " " << (l_color == l_black ? "false" : "true" ) << std::endl ;
#endif
                      l_coded_value = l_coded_value << 1;
                      if(l_color == l_black)
                        {
                          l_coded_value |= 0x1;
                        }
                    } 
                }
              std::cout << "'" << (uint8_t) (16 * l_line + l_column) << "',0x" << std::hex << l_coded_value << std::dec << std::endl ;
            }
	}
    }
#endif

  synoptic::synoptic l_synoptic(640,480);
  synoptic::color_zone l_zone1(l_synoptic,"zone1",100,100,0xFF,0,0);
  synoptic::color_zone l_zone2(l_synoptic,"zone2",200,200,0,0,0xFF);
  synoptic::text_field_zone l_text(l_synoptic,"text_zone",20);
  synoptic::drawing_zone l_drawing_zone(l_synoptic,"drawing_zone",50,50);
  l_synoptic.add_zone(100,100,l_zone2);
  l_synoptic.add_zone(0,0,l_zone1);
  l_synoptic.add_zone(0,400,l_text);
  l_synoptic.add_zone(150,0,l_drawing_zone);
  l_synoptic.refresh();
  sleep(2);
  l_zone1.paint();
  l_synoptic.refresh();
  sleep(2);
  l_zone2.paint();
  l_synoptic.refresh();
  sleep(2);
  l_text.set_text("Hello world");
  l_text.paint();
  l_synoptic.refresh();
  sleep(2);
  l_text.set_text("Oups");
  l_text.paint();
  l_synoptic.refresh();
  sleep(2);
  for(uint32_t l_x = 0 ; l_x < 50 ; ++l_x)
    {
      for(uint32_t l_y = 0 ; l_y < 50 ; ++l_y)
	{
	  l_drawing_zone.set_pixel(l_x,l_y,255 * (l_x % 2),255 * ( l_y % 2) , 255 * ( (l_x + l_y) % 2));
	  l_drawing_zone.paint();
	  l_synoptic.refresh();	  	  	  
	}
    }

  for(uint32_t l_index = 0 ; l_index < 10000 ; ++l_index)
    {
      l_text.set_text((uint64_t)l_index);
      l_text.paint();
      l_synoptic.refresh();
    }
}
