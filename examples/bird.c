#define MAX_RAINBOW_OFFSET 50 
//#define MAX_RAINBOW_OFFSET (192 - 16 - 2) 

#ifdef __ATARI2600__
#include "vcs.h"
unsigned char X, Y;

#ifdef PAL
const unsigned char RED = 0x64;
const unsigned char BLUE = 0xB2;
const unsigned char LBLUE = 0xBA;
const unsigned char BLACK = 0x00;
const unsigned char WHITE = 0x0e;
const unsigned char YELLOW = 0x2c;
const unsigned char ORANGE = 0x4c;
const unsigned char GREY = 0x04;
const unsigned char GREEN = 0x58;
#else
const unsigned char RED = 0x36;
const unsigned char BLUE = 0x84;
const unsigned char LBLUE = 0x8e;
const unsigned char BLACK = 0x00;
const unsigned char WHITE = 0x0e;
const unsigned char YELLOW = 0x1e;
const unsigned char ORANGE = 0xfa;
const unsigned char GREY = 0x04;
const unsigned char GREEN = 0xC6;
#endif

#define KERNAL 192
#ifdef PAL
#define BLANK 48
#define PALBOTTOM 36
#define OVERSCAN 36
#else
#define BLANK 40
#define OVERSCAN 30
#endif

const unsigned char s0_PF0[24]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0xf0,0xf0,0x70,0x30,0x10};
const unsigned char s0_PF1[24]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0f,0x1f,0x3e,0x7c,0xf8,0xf0,0xe0,0xc0,0x80,0x00,0x00,0x00,0x00};
const unsigned char s0_PF2[24]={0x80,0xc0,0xe0,0xf0,0xf8,0x7c,0x3e,0x1f,0x0f,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char s1_PF0[24]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0x70,0x30,0x10,0x00};
const unsigned char s1_PF1[24]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0e,0x1c,0x38,0x70,0xe0,0xc0,0x80,0x00,0x00,0x00,0x00,0x00};
const unsigned char s1_PF2[24]={0x00,0x80,0xc0,0xe0,0x70,0x38,0x1c,0x0e,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

char first_time;
unsigned char i, j, k, l;
unsigned char scroll_sequence;
unsigned char scroll_counter;
unsigned char lPFx[12];
unsigned char rPFx[12];
unsigned char lPFy[12];
unsigned char rPFy[12];
unsigned char left_window, right_window;
unsigned short ybird;
signed short yspeed;
unsigned char button_pressed;
unsigned char bird_type;
unsigned char bird_animation_counter;
unsigned char score_low;
unsigned char score_high;
unsigned char highscore_low;
unsigned char highscore_high;
unsigned char *background_ptr1;
unsigned char *background_ptr2;
unsigned char rainbow_offset;

#define SPRITE_HEIGHT 16 
#define RAINBOW_SIZE 16

#define BIRD1
#define BEFORE X = i;   
#define WAIT i = Y >> 4; Y--; 
#define BEFORE2 X = i; *COLUBK = j;  
#define WAIT2 i = right_shift4[Y]; Y--; 

#define kernel kernel11
#define START BEFORE; *PF1 = lPFx[X]; *PF2 = lPFy[X]; WAIT; *PF1= rPFx[X]; *PF2 = rPFy[X];
#define START2 BEFORE2; *PF1 = lPFx[X]; *PF2 = lPFy[X]; WAIT2; *PF1= rPFx[X]; *PF2 = rPFy[X];
#include "bird_kernel.c"

#undef kernel
#undef START
#undef START2

#define kernel kernel21
#define START BEFORE; *PF0 = lPFx[X]; *PF1 = lPFy[X]; WAIT; *PF0 = rPFx[X]; *PF1 = rPFy[X];
#define START2 BEFORE2; *PF0 = lPFx[X]; *PF1 = lPFy[X]; WAIT2; *PF0 = rPFx[X]; *PF1 = rPFy[X];
#include "bird_kernel.c"

#undef kernel
#undef START
#undef START2

#define kernel kernel31
#define START BEFORE; *PF0 = lPFx[X]; *PF2 = lPFy[X]; WAIT; *PF0 = rPFx[X]; *PF2 = rPFy[X];
#define START2 BEFORE2; *PF0 = lPFx[X]; *PF2 = lPFy[X]; WAIT2; *PF0 = rPFx[X]; *PF2 = rPFy[X];
#include "bird_kernel.c"

#undef kernel
#undef START
#undef START2

#undef BIRD1
#define bank1 bank2
#define right_shift4 right_shift4_bank2
#define rainbow rainbow_bank2
#undef WAIT2
#define WAIT2 i = right_shift4[Y]; Y--; 

#define kernel kernel12
#define START BEFORE; *PF1 = lPFx[X]; *PF2 = lPFy[X]; WAIT; *PF1= rPFx[X]; *PF2 = rPFy[X];
#define START2 BEFORE2; *PF1 = lPFx[X]; *PF2 = lPFy[X]; WAIT2; *PF1= rPFx[X]; *PF2 = rPFy[X];
#include "bird_kernel.c"

#undef kernel
#undef START
#undef START2

#define kernel kernel22
#define START BEFORE; *PF0 = lPFx[X]; *PF1 = lPFy[X]; WAIT; *PF0 = rPFx[X]; *PF1 = rPFy[X];
#define START2 BEFORE2; *PF0 = lPFx[X]; *PF1 = lPFy[X]; WAIT2; *PF0 = rPFx[X]; *PF1 = rPFy[X];
#include "bird_kernel.c"

#undef kernel
#undef START
#undef START2

#define kernel kernel32
#define START BEFORE; *PF0 = lPFx[X]; *PF2 = lPFy[X]; WAIT; *PF0 = rPFx[X]; *PF2 = rPFy[X];
#define START2 BEFORE2; *PF0 = lPFx[X]; *PF2 = lPFy[X]; WAIT2; *PF0 = rPFx[X]; *PF2 = rPFy[X];
#include "bird_kernel.c"

void init_sprites_pos()
{
    strobe(WSYNC);

    *COLUP0 = RED; 
    *HMP0 = 0;
    *GRP0 = 0;
    *GRP0 = 0;
    *GRP0 = 0;
    *GRP0 = 0;
    strobe(RESP0);
    strobe(WSYNC);

    *COLUP1 = WHITE; 
    *HMP1 = 0;
    *GRP1 = 0;
    *GRP1 = 0;
    *GRP1 = 0;
    *GRP0 = 0;
    strobe(RESP1);
    strobe(WSYNC);

    *COLUBK = BLUE;
    *COLUPF = BLACK;
    *GRP1 = 0;
    *GRP1 = 0;
    *CTRLPF = 0x20;
    *GRP0 = 0;
    strobe(RESBL);
    strobe(WSYNC);
    strobe(HMOVE);

    *HMBL = 0xF0;
    strobe(WSYNC);
    strobe(HMOVE);

    *HMBL = 0x00;
    strobe(WSYNC);
    strobe(HMOVE);
}

void load_scroll_sequence()
{
    if (scroll_sequence < 12) {
        i = 0;
    } else if (scroll_sequence < 20) {
        i = 1;
    } else {
        i = 2;
    }

    Y = scroll_sequence;
    if (i == 0) {
        j = s1_PF1[Y];
        k = s1_PF2[Y]; 
    } else if (i == 1) {
        j = s1_PF0[Y];
        k = s1_PF1[Y]; 
    } else if (i == 2) {
        j = s1_PF0[Y];
        k = s1_PF2[Y]; 
    }

    for (X = 0; X != right_window; X++) {
        rPFx[X] = j;
        rPFy[X] = k;
    }

    if (i == 0) {
        j = s0_PF1[Y];
        k = s0_PF2[Y]; 
    } else if (i == 1) {
        j = s0_PF0[Y];
        k = s0_PF1[Y]; 
    } else if (i == 2) {
        j = s0_PF0[Y];
        k = s0_PF2[Y]; 
    }
    rPFx[X] = j;
    rPFy[X] = k;
    X++;

    for (; X != right_window + 4; X++) {
        rPFx[X] = 0;
        rPFy[X] = 0;
    }

    if (i == 0) {
        j = s0_PF1[Y];
        k = s0_PF2[Y]; 
    } else if (i == 1) {
        j = s0_PF0[Y];
        k = s0_PF1[Y]; 
    } else if (i == 2) {
        j = s0_PF0[Y];
        k = s0_PF2[Y]; 
    }
    rPFx[X] = j;
    rPFy[X] = k;
    X++;

    if (i == 0) {
        j = s1_PF1[Y];
        k = s1_PF2[Y]; 
    } else if (i == 1) {
        j = s1_PF0[Y];
        k = s1_PF1[Y]; 
    } else if (i == 2) {
        j = s1_PF0[Y];
        k = s1_PF2[Y]; 
    }

    for (; X != 12; X++) {
        rPFx[X] = j;
        rPFy[X] = k;
    }
    
    Y = scroll_sequence + 4;
    if (Y >= 24) Y = Y - 24;
    if (i == 0) {
        j = s1_PF1[Y];
        k = s1_PF2[Y]; 
    } else if (i == 1) {
        j = s1_PF0[Y];
        k = s1_PF1[Y]; 
    } else if (i == 2) {
        j = s1_PF0[Y];
        k = s1_PF2[Y]; 
    }

    for (X = 0; X != left_window; X++) {
        lPFx[X] = j;
        lPFy[X] = k;
    }

    if (i == 0) {
        j = s0_PF1[Y];
        k = s0_PF2[Y]; 
    } else if (i == 1) {
        j = s0_PF0[Y];
        k = s0_PF1[Y]; 
    } else if (i == 2) {
        j = s0_PF0[Y];
        k = s0_PF2[Y]; 
    }
    lPFx[X] = j;
    lPFy[X] = k;
    X++;

    for (; X != left_window + 4; X++) {
        lPFx[X] = 0;
        lPFy[X] = 0;
    }

    if (i == 0) {
        j = s0_PF1[Y];
        k = s0_PF2[Y]; 
    } else if (i == 1) {
        j = s0_PF0[Y];
        k = s0_PF1[Y]; 
    } else if (i == 2) {
        j = s0_PF0[Y];
        k = s0_PF2[Y]; 
    }
    lPFx[X] = j;
    lPFy[X] = k;
    X++;

    if (i == 0) {
        j = s1_PF1[Y];
        k = s1_PF2[Y]; 
    } else if (i == 1) {
        j = s1_PF0[Y];
        k = s1_PF1[Y]; 
    } else if (i == 2) {
        j = s1_PF0[Y];
        k = s1_PF2[Y]; 
    }

    for (; X != 12; X++) {
        lPFx[X] = j;
        lPFy[X] = k;
    }
}
    
void init()
{
    init_sprites_pos();
    first_time = 0;
    ybird = 100 * 256;
}

void gameover()
{
    ybird = 100 * 256;
    yspeed = 0;
    score_low = 0;
    score_high = 0;
}

void game_logic()
{
    if (scroll_counter == 10) {
        scroll_counter = 0;
        scroll_sequence++;
        if (scroll_sequence == 20) left_window = right_window;
        if (scroll_sequence == 24) {
            right_window = right_window + 1;
            if (right_window == 8) right_window = 0;
            scroll_sequence = 0;
        }
    }
    yspeed -= 10;
    if (yspeed >> 8 < 0) bird_type = 0;
    if ((*INPT4 & 0x80) != 0) {
        if (button_pressed == 0) {
            button_pressed = 1;
            yspeed = 350;
            if (bird_type == 0) 
                bird_type = 1;
            else {
                bird_type = 0;
                bird_animation_counter = 5;
            }
        }
    } else button_pressed = 0;

    if (bird_animation_counter != 0) {
        bird_animation_counter--;
        if (bird_animation_counter == 0) bird_type = 1;
    }

    ybird = ybird + yspeed;
    if (ybird >> 8 < 20) {
        gameover();
    }
    if (ybird >> 8 > 189) {
        gameover();
    }
    if ((*CXP0FB & 0x80) != 0) gameover();
    if ((*CXP1FB & 0x80) != 0) gameover();
    if ((*CXBLPF & 0x80) != 0) gameover();
    strobe(CXCLR);

    load_scroll_sequence();
    scroll_counter++;

    rainbow_offset++;
    if (rainbow_offset == 50 + 16) rainbow_offset = 0;
}

const bank3 unsigned char score_line1_PF0[100]={
	0x77, 0x47, 0x77, 0x77, 0x57, 0x77, 0x77, 0x77, 
	0x77, 0x77, 0x74, 0x44, 0x74, 0x74, 0x54, 0x74, 
	0x74, 0x74, 0x74, 0x74, 0x77, 0x47, 0x77, 0x77, 
	0x57, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x47, 
	0x77, 0x77, 0x57, 0x77, 0x77, 0x77, 0x77, 0x77, 
	0x75, 0x45, 0x75, 0x75, 0x55, 0x75, 0x75, 0x75, 
	0x75, 0x75, 0x77, 0x47, 0x77, 0x77, 0x57, 0x77, 
	0x77, 0x77, 0x77, 0x77, 0x77, 0x47, 0x77, 0x77, 
	0x57, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x47, 
	0x77, 0x77, 0x57, 0x77, 0x77, 0x77, 0x77, 0x77, 
	0x77, 0x47, 0x77, 0x77, 0x57, 0x77, 0x77, 0x77, 
	0x77, 0x77, 0x77, 0x47, 0x77, 0x77, 0x57, 0x77, 
	0x77, 0x77, 0x77, 0x77};

const bank3 unsigned char score_line2_PF0[100]={
	0x55, 0x45, 0x45, 0x45, 0x55, 0x15, 0x15, 0x45, 
	0x55, 0x55, 0x54, 0x44, 0x44, 0x44, 0x54, 0x14, 
	0x14, 0x44, 0x54, 0x54, 0x54, 0x44, 0x44, 0x44, 
	0x54, 0x14, 0x14, 0x44, 0x54, 0x54, 0x54, 0x44, 
	0x44, 0x44, 0x54, 0x14, 0x14, 0x44, 0x54, 0x54, 
	0x55, 0x45, 0x45, 0x45, 0x55, 0x15, 0x15, 0x45, 
	0x55, 0x55, 0x51, 0x41, 0x41, 0x41, 0x51, 0x11, 
	0x11, 0x41, 0x51, 0x51, 0x51, 0x41, 0x41, 0x41, 
	0x51, 0x11, 0x11, 0x41, 0x51, 0x51, 0x54, 0x44, 
	0x44, 0x44, 0x54, 0x14, 0x14, 0x44, 0x54, 0x54, 
	0x55, 0x45, 0x45, 0x45, 0x55, 0x15, 0x15, 0x45, 
	0x55, 0x55, 0x55, 0x45, 0x45, 0x45, 0x55, 0x15, 
	0x15, 0x45, 0x55, 0x55};

const bank3 unsigned char score_line3_PF0[100]={
	0x55, 0x45, 0x75, 0x75, 0x75, 0x15, 0x75, 0x45, 
	0x75, 0x75, 0x54, 0x44, 0x74, 0x74, 0x74, 0x14, 
	0x74, 0x44, 0x74, 0x74, 0x57, 0x47, 0x77, 0x77, 
	0x77, 0x17, 0x77, 0x47, 0x77, 0x77, 0x57, 0x47, 
	0x77, 0x77, 0x77, 0x17, 0x77, 0x47, 0x77, 0x77, 
	0x57, 0x47, 0x77, 0x77, 0x77, 0x17, 0x77, 0x47, 
	0x77, 0x77, 0x51, 0x41, 0x71, 0x71, 0x71, 0x11, 
	0x71, 0x41, 0x71, 0x71, 0x57, 0x47, 0x77, 0x77, 
	0x77, 0x17, 0x77, 0x47, 0x77, 0x77, 0x54, 0x44, 
	0x74, 0x74, 0x74, 0x14, 0x74, 0x44, 0x74, 0x74, 
	0x57, 0x47, 0x77, 0x77, 0x77, 0x17, 0x77, 0x47, 
	0x77, 0x77, 0x57, 0x47, 0x77, 0x77, 0x77, 0x17, 
	0x77, 0x47, 0x77, 0x77};

const bank3 unsigned char score_line4_PF0[100]={
	0x55, 0x45, 0x15, 0x45, 0x45, 0x45, 0x55, 0x45, 
	0x55, 0x45, 0x54, 0x44, 0x14, 0x44, 0x44, 0x44, 
	0x54, 0x44, 0x54, 0x44, 0x51, 0x41, 0x11, 0x41, 
	0x41, 0x41, 0x51, 0x41, 0x51, 0x41, 0x54, 0x44, 
	0x14, 0x44, 0x44, 0x44, 0x54, 0x44, 0x54, 0x44, 
	0x54, 0x44, 0x14, 0x44, 0x44, 0x44, 0x54, 0x44, 
	0x54, 0x44, 0x54, 0x44, 0x14, 0x44, 0x44, 0x44, 
	0x54, 0x44, 0x54, 0x44, 0x55, 0x45, 0x15, 0x45, 
	0x45, 0x45, 0x55, 0x45, 0x55, 0x45, 0x54, 0x44, 
	0x14, 0x44, 0x44, 0x44, 0x54, 0x44, 0x54, 0x44, 
	0x55, 0x45, 0x15, 0x45, 0x45, 0x45, 0x55, 0x45, 
	0x55, 0x45, 0x54, 0x44, 0x14, 0x44, 0x44, 0x44, 
	0x54, 0x44, 0x54, 0x44};

const bank3 unsigned char score_line5_PF0[100]={
	0x77, 0x47, 0x77, 0x77, 0x47, 0x77, 0x77, 0x47, 
	0x77, 0x77, 0x74, 0x44, 0x74, 0x74, 0x44, 0x74, 
	0x74, 0x44, 0x74, 0x74, 0x77, 0x47, 0x77, 0x77, 
	0x47, 0x77, 0x77, 0x47, 0x77, 0x77, 0x77, 0x47, 
	0x77, 0x77, 0x47, 0x77, 0x77, 0x47, 0x77, 0x77, 
	0x74, 0x44, 0x74, 0x74, 0x44, 0x74, 0x74, 0x44, 
	0x74, 0x74, 0x77, 0x47, 0x77, 0x77, 0x47, 0x77, 
	0x77, 0x47, 0x77, 0x77, 0x77, 0x47, 0x77, 0x77, 
	0x47, 0x77, 0x77, 0x47, 0x77, 0x77, 0x74, 0x44, 
	0x74, 0x74, 0x44, 0x74, 0x74, 0x44, 0x74, 0x74, 
	0x77, 0x47, 0x77, 0x77, 0x47, 0x77, 0x77, 0x47, 
	0x77, 0x77, 0x77, 0x47, 0x77, 0x77, 0x47, 0x77, 
	0x77, 0x47, 0x77, 0x77};

const bank3 unsigned char score_line1_PF1[100]={
	0x0e, 0x02, 0x0e, 0x0e, 0x0a, 0x0e, 0x0e, 0x0e, 
	0x0e, 0x0e, 0x2e, 0x22, 0x2e, 0x2e, 0x2a, 0x2e, 
	0x2e, 0x2e, 0x2e, 0x2e, 0xee, 0xe2, 0xee, 0xee, 
	0xea, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xe2, 
	0xee, 0xee, 0xea, 0xee, 0xee, 0xee, 0xee, 0xee, 
	0xae, 0xa2, 0xae, 0xae, 0xaa, 0xae, 0xae, 0xae, 
	0xae, 0xae, 0xee, 0xe2, 0xee, 0xee, 0xea, 0xee, 
	0xee, 0xee, 0xee, 0xee, 0xee, 0xe2, 0xee, 0xee, 
	0xea, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xe2, 
	0xee, 0xee, 0xea, 0xee, 0xee, 0xee, 0xee, 0xee, 
	0xee, 0xe2, 0xee, 0xee, 0xea, 0xee, 0xee, 0xee, 
	0xee, 0xee, 0xee, 0xe2, 0xee, 0xee, 0xea, 0xee, 
	0xee, 0xee, 0xee, 0xee};

const bank3 unsigned char score_line2_PF1[100]={
	0x0a, 0x02, 0x02, 0x02, 0x0a, 0x08, 0x08, 0x02, 
	0x0a, 0x0a, 0x2a, 0x22, 0x22, 0x22, 0x2a, 0x28, 
	0x28, 0x22, 0x2a, 0x2a, 0x2a, 0x22, 0x22, 0x22, 
	0x2a, 0x28, 0x28, 0x22, 0x2a, 0x2a, 0x2a, 0x22, 
	0x22, 0x22, 0x2a, 0x28, 0x28, 0x22, 0x2a, 0x2a, 
	0xaa, 0xa2, 0xa2, 0xa2, 0xaa, 0xa8, 0xa8, 0xa2, 
	0xaa, 0xaa, 0x8a, 0x82, 0x82, 0x82, 0x8a, 0x88, 
	0x88, 0x82, 0x8a, 0x8a, 0x8a, 0x82, 0x82, 0x82, 
	0x8a, 0x88, 0x88, 0x82, 0x8a, 0x8a, 0x2a, 0x22, 
	0x22, 0x22, 0x2a, 0x28, 0x28, 0x22, 0x2a, 0x2a, 
	0xaa, 0xa2, 0xa2, 0xa2, 0xaa, 0xa8, 0xa8, 0xa2, 
	0xaa, 0xaa, 0xaa, 0xa2, 0xa2, 0xa2, 0xaa, 0xa8, 
	0xa8, 0xa2, 0xaa, 0xaa};

const bank3 unsigned char score_line3_PF1[100]={
	0x0a, 0x02, 0x0e, 0x0e, 0x0e, 0x08, 0x0e, 0x02, 
	0x0e, 0x0e, 0x2a, 0x22, 0x2e, 0x2e, 0x2e, 0x28, 
	0x2e, 0x22, 0x2e, 0x2e, 0xea, 0xe2, 0xee, 0xee, 
	0xee, 0xe8, 0xee, 0xe2, 0xee, 0xee, 0xea, 0xe2, 
	0xee, 0xee, 0xee, 0xe8, 0xee, 0xe2, 0xee, 0xee, 
	0xea, 0xe2, 0xee, 0xee, 0xee, 0xe8, 0xee, 0xe2, 
	0xee, 0xee, 0x8a, 0x82, 0x8e, 0x8e, 0x8e, 0x88, 
	0x8e, 0x82, 0x8e, 0x8e, 0xea, 0xe2, 0xee, 0xee, 
	0xee, 0xe8, 0xee, 0xe2, 0xee, 0xee, 0x2a, 0x22, 
	0x2e, 0x2e, 0x2e, 0x28, 0x2e, 0x22, 0x2e, 0x2e, 
	0xea, 0xe2, 0xee, 0xee, 0xee, 0xe8, 0xee, 0xe2, 
	0xee, 0xee, 0xea, 0xe2, 0xee, 0xee, 0xee, 0xe8, 
	0xee, 0xe2, 0xee, 0xee};

const bank3 unsigned char score_line4_PF1[100]={
	0x0a, 0x02, 0x08, 0x02, 0x02, 0x02, 0x0a, 0x02, 
	0x0a, 0x02, 0x2a, 0x22, 0x28, 0x22, 0x22, 0x22, 
	0x2a, 0x22, 0x2a, 0x22, 0x8a, 0x82, 0x88, 0x82, 
	0x82, 0x82, 0x8a, 0x82, 0x8a, 0x82, 0x2a, 0x22, 
	0x28, 0x22, 0x22, 0x22, 0x2a, 0x22, 0x2a, 0x22, 
	0x2a, 0x22, 0x28, 0x22, 0x22, 0x22, 0x2a, 0x22, 
	0x2a, 0x22, 0x2a, 0x22, 0x28, 0x22, 0x22, 0x22, 
	0x2a, 0x22, 0x2a, 0x22, 0xaa, 0xa2, 0xa8, 0xa2, 
	0xa2, 0xa2, 0xaa, 0xa2, 0xaa, 0xa2, 0x2a, 0x22, 
	0x28, 0x22, 0x22, 0x22, 0x2a, 0x22, 0x2a, 0x22, 
	0xaa, 0xa2, 0xa8, 0xa2, 0xa2, 0xa2, 0xaa, 0xa2, 
	0xaa, 0xa2, 0x2a, 0x22, 0x28, 0x22, 0x22, 0x22, 
	0x2a, 0x22, 0x2a, 0x22};

const bank3 unsigned char score_line5_PF1[100]={
	0x0e, 0x02, 0x0e, 0x0e, 0x02, 0x0e, 0x0e, 0x02, 
	0x0e, 0x0e, 0x2e, 0x22, 0x2e, 0x2e, 0x22, 0x2e, 
	0x2e, 0x22, 0x2e, 0x2e, 0xee, 0xe2, 0xee, 0xee, 
	0xe2, 0xee, 0xee, 0xe2, 0xee, 0xee, 0xee, 0xe2, 
	0xee, 0xee, 0xe2, 0xee, 0xee, 0xe2, 0xee, 0xee, 
	0x2e, 0x22, 0x2e, 0x2e, 0x22, 0x2e, 0x2e, 0x22, 
	0x2e, 0x2e, 0xee, 0xe2, 0xee, 0xee, 0xe2, 0xee, 
	0xee, 0xe2, 0xee, 0xee, 0xee, 0xe2, 0xee, 0xee, 
	0xe2, 0xee, 0xee, 0xe2, 0xee, 0xee, 0x2e, 0x22, 
	0x2e, 0x2e, 0x22, 0x2e, 0x2e, 0x22, 0x2e, 0x2e, 
	0xee, 0xe2, 0xee, 0xee, 0xe2, 0xee, 0xee, 0xe2, 
	0xee, 0xee, 0xee, 0xe2, 0xee, 0xee, 0xe2, 0xee, 
	0xee, 0xe2, 0xee, 0xee};

void bottom()
{
    strobe(WSYNC);
#ifdef PAL
    for (X = PALBOTTOM; X != 0; X--) strobe(WSYNC);
#endif

    *VBLANK = 2; // Enable VBLANK again
                 // Now we have 30 lines of VBLANK
                 //strobe(HMCLR);
    for (X = OVERSCAN; X != 0; X--) strobe(WSYNC);
}

void main()
{
  first_time = 1;

  do {
    *VBLANK = 2; // Enable VBLANK
    *VSYNC = 2; // Set VSYNC
    strobe(WSYNC); // Hold it for 3 scanlines
    strobe(WSYNC);
    strobe(WSYNC);
    *VSYNC = 0; // Turn VSYNC Off

    if (first_time) {
        init();
    } else {
#ifdef PAL
        *TIM64T = 49; 
#else
        *TIM64T = 39;
#endif
        // The game logic
        game_logic();
        while (*INTIM);
    }
    strobe(WSYNC);
   
    if (bird_type == 0) {
        if (scroll_sequence < 12) {
            kernel11();
        } else if (scroll_sequence < 20) {
            kernel21();
        } else kernel31();
    } else {
        if (scroll_sequence < 12) {
            kernel12();
        } else if (scroll_sequence < 20) {
            kernel22();
        } else kernel32();
    }

    bottom();
  } while(1);
}
#else

#include <stdio.h>

unsigned char reverse(unsigned char input)
{
    unsigned char output = 0;
    if (input & 1) output |= 128;
    if (input & 2) output |= 64;
    if (input & 4) output |= 32;
    if (input & 8) output |= 16;
    if (input & 16) output |= 8;
    if (input & 32) output |= 4;
    if (input & 64) output |= 2;
    if (input & 128) output |= 1;
    return output;
}

void main()
{
    int i, j, c, d;
#define WIDTH 24
    unsigned char PF[3][WIDTH];
    for (j = 0; j < 2; j++) {
        unsigned int mask = (j)?0x0e:0x1f;
        for (i = 0; i < WIDTH; i++) {
            unsigned int val = (mask << i) >> 4;
            PF[0][i] = reverse((val >> 16) & 0x0f);
            PF[1][i] = (val >> 8) & 0xff;
            PF[2][i] = reverse(val & 0xff);
        }
        for (d = 0; d < 3; d++) {
            printf("const unsigned char s%d_PF%d[%d]={", j, d, WIDTH);
            for (c = 0; c < WIDTH - 1; c++) {
                printf("0x%02x,", PF[d][c]);
            }
            printf("0x%02x};\n", PF[d][c]);
        }
    }
    printf("const unsigned char right_shift4[256]={\n\t");
    for (i = 0; i < 256; i++) {
        printf("0x%02x", i >> 4);
        if (i != 255) printf(",");
        if (!((i + 1) % 16)) printf("\n\t");
    }
    printf("};\n");
    const int sprite_height = 18;
    const int rainbow_height = 16;
    const int blue_pal = 0xb2;
    const int blue_ntsc = 0x84;
    unsigned char rainbow[rainbow_height];

    for (j = 0; j < 2; j++) {
        switch (j) {
            case 0: // NTSC
                for (i = 0; i < 8; i++) {
                    rainbow[i] = 0x76 + 0x10 * i;
                }
                for (i = 0; i < 8; i++) {
                    rainbow[i + 8] = 0x06 + 0x10 * i;
                }
                break;
            case 1: // PAL
                for (i = 0; i < 6; i++) {
                    rainbow[i] = 0xd6 - 0x20 * i;
                }
                rainbow[i + 6] = 0x38;
                rainbow[i + 7] = 0x3e;
                rainbow[i + 8] = 0x2e;
                rainbow[i + 9] = 0x26;
                for (i = 0; i < 6; i++) {
                    rainbow[i + 10] = 0x26 + 0x20 * i;
                }
                break;
        }
        printf("const unsigned char rainbow_%s[%d]={\n\t", (j)?"PAL":"NTSC", 2 * MAX_RAINBOW_OFFSET + (192 - sprite_height) + 2 * rainbow_height);
        for (i = 0; i < MAX_RAINBOW_OFFSET; i++) {
            printf("0x%02x, ", (j)?blue_pal:blue_ntsc);
            if (!((i + 1) % 16)) printf("\n\t");
        }
        printf("\n\t");
        for (i = 0; i< rainbow_height; i++) {
            printf("0x%02x, ", rainbow[i]);
        }
        printf("\n\t");
        for (i = 0; i < 192 - sprite_height; i++) {
            printf("0x%02x, ", (j)?blue_pal:blue_ntsc);
            if (!((i + 1) % 16)) printf("\n\t");
        }
        printf("\n\t");
        for (i = 0; i < rainbow_height; i++) {
            printf("0x%02x, ", rainbow[rainbow_height - 1 - i]);
        }
        printf("\n\t");
        for (i = 0; i < MAX_RAINBOW_OFFSET - 1; i++) {
            printf("0x%02x, ", (j)?blue_pal:blue_ntsc);
            if (!((i + 1) % 16)) printf("\n\t");
        }
        printf("0x%02x};\n", (j)?blue_pal:blue_ntsc);
    }
}
#endif
