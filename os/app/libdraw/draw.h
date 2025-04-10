
#include "include/vesa.h"
#include "include/types.h"


#define BLUE        0xff0000
#define GREEN       0x00ff00
#define RED         0x0000ff


void draw_char_en(int o_x, int o_y, int index, int color, unsigned long fbbase, struct mode_info *minfo);
void draw_char_zh(int o_x, int o_y, int index, int color, unsigned long fbbase, struct mode_info *minfo);
void draw_rect(int o_x, int o_y, int h, int w, int color, unsigned long fbbase, struct mode_info *minfo);