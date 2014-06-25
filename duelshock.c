#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "duelshock.h"

void moveMouse(struct Stick stick) {
	
	stick.vertical *= POINTERSENSITIVITY;
	stick.horizontal *= POINTERSENSITIVITY;
	
	if((stick.horizontal || stick.vertical) && (stick.horizontal != 1 && stick.vertical != 1)) {
		sprintf(doCommand, "xdotool mousemove_relative -- %f %f", stick.horizontal, stick.vertical);
		system(doCommand);
	}
}

void scroll(struct Stick stick) {
	if(stick.vertical > 2 || stick.vertical < -2) {
		verticalScrollDelay--;
		
		if(!verticalScrollDelay) {
			sprintf(doCommand, "xdotool click %i", (stick.vertical > 0) ? 5 : 4);
			system(doCommand);
			verticalScrollDelay = 3;
		}
		
		return;
	}
	
	else if(verticalScrollDelay != 3) verticalScrollDelay = 3;
	
	if(stick.horizontal > 2 || stick.horizontal < -2) {
		horizontalScrollDelay--;
		
		if(!horizontalScrollDelay) {
			sprintf(doCommand, "xdotool keydown shift click %i keyup shift", (stick.horizontal > 0) ? 5 : 4);
			system(doCommand);
			horizontalScrollDelay = 2;
		}
	}
	
	else if(horizontalScrollDelay != 2) horizontalScrollDelay = 2;
}

int mouseOrKey(char *map, char *dir) {
	
	if(!strcmp(map, "LClick")) sprintf(doCommand, MOUSE, dir, "1");
	
	else if(!strcmp(map, "MClick")) sprintf(doCommand, MOUSE, dir, "2");
	
	else if(!strcmp(map, "RClick")) sprintf(doCommand, MOUSE, dir, "3");
	
	else sprintf(doCommand, KEY, dir, map);
	
	return system(doCommand);
}

void setNode() {
	
	FILE *f;
	
	f = popen("dmesg | tail | fgrep 'Sony PLAYSTATION(R)3 Controller' | grep -Po 'hidraw[0-9]+' | tail -1", "r");
	fgets(hidraw, 15, f);
	pclose(f);
	
	hidraw[strlen(hidraw) - 1] = '\0'; //To remove '\n' from the path.
}

void simulateKeys() {
	
	if(dKey >= DLEFT) {
		dKey -= DLEFT;
		if(!held.dLeft) held.dLeft = !mouseOrKey(DLEFTMAP, DOWN);
	}
	
	else if(held.dLeft) held.dLeft = mouseOrKey(DLEFTMAP, UP);
	
	if(dKey >= DDOWN) {
		dKey -= DDOWN;
		if(!held.dDown) held.dDown = !mouseOrKey(DDOWNMAP, DOWN);
	}
	
	else if(held.dDown) held.dDown = mouseOrKey(DDOWNMAP, UP);
	
	if(dKey >= DRIGHT) {
		dKey -= DRIGHT;
		if(!held.dRight) held.dRight = !mouseOrKey(DRIGHTMAP, DOWN);
	}
	
	else if(held.dRight) held.dRight = mouseOrKey(DRIGHTMAP, UP);
	
	if(dKey >= DUP) {
		dKey -= DUP;
		if(!held.dUp) held.dUp = !mouseOrKey(DUPMAP, DOWN);
	}
	
	else if(held.dUp) held.dUp = mouseOrKey(DUPMAP, UP);
	
	if(dKey >= START) {
		dKey -= START;
		if(!held.start) held.start = !mouseOrKey(STARTMAP, DOWN);
	}
	
	else if(held.start) held.start = mouseOrKey(STARTMAP, UP);
	
	if(dKey >= R3) {
		dKey -= R3;
		if(!held.r3) held.r3 = !mouseOrKey(R3MAP, DOWN);
	}
	
	else if(held.r3) held.r3 = mouseOrKey(R3MAP, UP);
	
	if(dKey >= L3) {
		dKey -= L3;
		if(!held.l3) held.l3 = !mouseOrKey(L3MAP, DOWN);
	}
	
	else if(held.l3) held.l3 = mouseOrKey(L3MAP, UP);
	
	if(dKey >= SELECT) {
		dKey -= SELECT;
		if(!held.select) held.select = !mouseOrKey(SELECTMAP, DOWN);
	}
	
	else if(held.select) held.select = mouseOrKey(SELECTMAP, UP);
	
	if(actionKey >= AS) {
		actionKey -= AS;
		if(!held.sAction) held.sAction = !mouseOrKey(ASMAP, DOWN);
	}
	
	else if(held.sAction) held.sAction = mouseOrKey(ASMAP, UP);
	
	if(actionKey >= AX) {
		actionKey -= AX;
		if(!held.xAction) held.xAction = !mouseOrKey(AXMAP, DOWN);
	}
	
	else if(held.xAction) held.xAction = mouseOrKey(AXMAP, UP);
	
	if(actionKey >= AO) {
		actionKey -= AO;
		if(!held.oAction) held.oAction = !mouseOrKey(AOMAP, DOWN);
	}
	
	else if(held.oAction) held.oAction = mouseOrKey(AOMAP, UP);
	
	if(actionKey == AT) {
		actionKey -= AT;
		if(!held.tAction) held.tAction = !mouseOrKey(ATMAP, DOWN);
	}
	
	else if(held.tAction) held.tAction = mouseOrKey(ATMAP, UP);
	
	if (actionKey >= R1) {
		actionKey -= R1;
		if(!held.r1) held.r1 = !mouseOrKey(R1MAP, DOWN);
	}
	
	else if(held.r1) held.r1 = mouseOrKey(R1MAP, UP);
	
	if(actionKey >= L1) {
		actionKey -= L1;
		if(!held.l1) held.l1 = !mouseOrKey(L1MAP, DOWN);
	}
	
	else if(held.l1) held.l1 = mouseOrKey(L1MAP, UP);
	
	if(actionKey >= R2) {
		actionKey -= R2;
		if(!held.r2) held.r2 = !mouseOrKey(R2MAP, DOWN);
	}
	
	else if(held.r2) held.r2 = mouseOrKey(R2MAP, UP);
	
	if(actionKey >= L2) {
		actionKey -= L2;
		if(!held.l2) held.l2 = !mouseOrKey(L2MAP, DOWN);
	}
	
	else if(held.l2) held.l2 = mouseOrKey(L2MAP, UP);
	
	moveMouse((LEFTSTICKMOUSE) ? left : right);
	scroll((LEFTSTICKMOUSE) ? right : left);
}

void latchController() {
	
	standby = 1;
	verticalScrollDelay = 3;
	horizontalScrollDelay = 2;
	
	sprintf(doCommand, "/dev/%s", hidraw);
	device = open(doCommand, O_RDONLY);
	
	while ((nr = read(device, buf, sizeof(buf)))) {
		
		if (nr < 0) {
			dKey = 0;
			actionKey = 0;
			left = (struct Stick){0};
			right = (struct Stick){0};
			
			simulateKeys();
			held = (struct Held){0};
			
			close(device);
			
			return;
		}
		
		if(PS && !held.ps) {
			standby = !standby;
			held.ps = 1;
			
			sprintf(doCommand, "notify-send -i %s 'DuelShock' 'Controller %s Stand-by mode.'", (standby) ? PAUSE_ICON : PLAY_ICON, (standby) ? "in" : "out of");
			system(doCommand);
		}
		
		else if(!PS && held.ps) held.ps = 0;
		
		if(!standby) {
			dKey = buf[2];
			actionKey = buf[3];
			left.horizontal = (buf[6] / 10 - 12);
			left.vertical = (buf[7] / 10 - 12);
			right.horizontal = (buf[8] / 10 - 12);
			right.vertical = (buf[9] / 10 - 12);
			
			simulateKeys();
		}
	}
}

int main() {
	while(1) {
		
		if(!system("lsusb | grep -q 'PlayStation 3 Controller'")) {
			setNode();
			
			sprintf(doCommand, "notify-send -i %s 'DuelShock' 'PS3 controller detected! Press PS button.'", GAMEPAD_ICON);
			system(doCommand);
			
			latchController();
			
			sprintf(doCommand, "notify-send -i %s 'DuelShock' 'Lost connection to PS3 controller. Please reconnect the controller.'", ERROR_ICON);
			system(doCommand);
		}
		
		sleep(3);
	}
	
	return 0;
}
