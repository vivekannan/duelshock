//Button Values.
#define AS 128
#define AX 64
#define AO 32
#define AT 16
#define R1 8
#define L1 4
#define R2 2
#define L2 1

#define DLEFT 128
#define DDOWN 64
#define DRIGHT 32
#define DUP 16
#define START 8
#define R3 4
#define L3 2
#define SELECT 1

#define PS buf[4]
#define POINTER_SENSITIVITY 0.90

#define KEY "xdotool key%s %s"
#define MOUSE "xdotool mouse%s %s"

#define UP "up "
#define DOWN "down "

//Button Mappings. Refer xdotool's man page to know more about keystroke names.
#define DLEFTMAP "Left"
#define DDOWNMAP "Down"
#define DRIGHTMAP "Right"
#define DUPMAP "Up"

#define STARTMAP "Return"
#define SELECTMAP "alt"

#define R1MAP "XF86AudioNext"
#define R2MAP "shift"
#define R3MAP "Escape"

#define L1MAP "XF86AudioPrev"
#define L2MAP "ctrl"
#define L3MAP "MClick"		//Middle-Click

#define ASMAP "BackSpace"
#define AXMAP "LClick"		//Left-Click
#define AOMAP "RClick"		//Right-Click
#define ATMAP "XF86AudioPlay"

//Icon paths for notify-send.
#define PLAY_ICON "/usr/share/icons/Humanity/actions/48/player_play.svg"
#define PAUSE_ICON "/usr/share/icons/Humanity/actions/48/player_pause.svg"
#define ERROR_ICON "/usr/share/icons/Humanity/status/48/important.svg"
#define GAMEPAD_ICON "/usr/share/icons/Humanity/categories/48/applications-simulation.svg"

struct Held {
	int sAction;
	int xAction;
	int oAction;
	int tAction;
	int r1;
	int l1;
	int r2;
	int l2;
	int dLeft;
	int dDown;
	int dRight;
	int dUp;
	int start;
	int r3;
	int l3;
	int select;
	int ps;
}held;

struct Stick {
	float horizontal;
	float vertical;
}left, right;

unsigned char buf[128];
char doCommand[200];
char hidraw[15];
int device, nr;

int actionKey;
int dKey;
int standby;
int verticalScrollDelay, horizontalScrollDelay;
