//Action maps.
#define AS 128
#define AX 64
#define AO 32
#define AT 16
#define R1 8
#define L1 4
#define R2 2
#define L2 1

//D-Pad maps.
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
	int dPadLeft;
	int dPadDown;
	int dPadRight;
	int dPadUp;
	int start;
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
int device, nr;

int actionKey;
int dPadKey;
int standby;
int verticalScrollDelay, horizontalScrollDelay;
