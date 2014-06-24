#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "duelshock.h"

void setNode() {
	
	FILE *f;
	
	f = popen("dmesg | fgrep 'Sony PLAYSTATION(R)3 Controller' | grep -Po 'hidraw[0-9]+' | tail -1", "r");
	fgets(hidraw, 15, f);
	hidraw[strlen(hidraw) - 1] = '\0'; //To remove '\n' from the path.
	
	pclose(f);
}

void simulateKeys() {
	
	if(dKey >= DLEFT) {
		dKey -= DLEFT;
		if(!held.dLeft) held.dLeft = !system(MOUSEORKEY(DLEFTMAP, DOWN));
	}
	
	else if(held.dLeft) held.dLeft = system(MOUSEORKEY(DLEFTMAP, UP));
	
	if(dKey >= DDOWN) {
		dKey -= DDOWN;
		if(!held.dDown) held.dDown = !system(MOUSEORKEY(DDOWNMAP, DOWN));
	}
	
	else if(held.dDown) held.dDown = system(MOUSEORKEY(DDOWNMAP, UP));
	
	if(dKey >= DRIGHT) {
		dKey -= DRIGHT;
		if(!held.dRight) held.dRight = !system(MOUSEORKEY(DRIGHTMAP, DOWN));
	}
	
	else if(held.dRight) held.dRight = system(MOUSEORKEY(DRIGHTMAP, UP));
	
	if(dKey >= DUP) {
		dKey -= DUP;
		if(!held.dUp) held.dUp = !system(MOUSEORKEY(DUPMAP, DOWN));
	}
	
	else if(held.dUp) held.dUp = system(MOUSEORKEY(DUPMAP, UP));
	
	if(dKey >= START) {
		dKey -= START;
		if(!held.start) held.start = !system(MOUSEORKEY(STARTMAP, DOWN));
	}
	
	else if(held.start) held.start = system(MOUSEORKEY(STARTMAP, UP));
	
	if(dKey >= R3) {
		dKey -= R3;
		if(!held.r3) held.r3 = !system(MOUSEORKEY(R3MAP, DOWN));
	}
	
	else if(held.r3) held.r3 = system(MOUSEORKEY(R3MAP, UP));
	
	if(dKey >= L3) {
		dKey -= L3;
		if(!held.l3) held.l3 = !system(MOUSEORKEY(L3MAP, DOWN));
	}
	
	else if(held.l3) held.l3 = system(MOUSEORKEY(L3MAP, UP));
	
	if(dKey >= SELECT) {
		dKey -= SELECT;
		if(!held.select) held.select = !system(MOUSEORKEY(SELECTMAP, DOWN));
	}
	
	else if(held.select) held.select = system(MOUSEORKEY(SELECTMAP, UP));
	
	if(actionKey >= AS) {
		actionKey -= AS;
		if(!held.sAction) held.sAction = !system(MOUSEORKEY(ASMAP, DOWN));
	}
	
	else if(held.sAction) held.sAction = system(MOUSEORKEY(ASMAP, UP));
	
	if(actionKey >= AX) {
		actionKey -= AX;
		if(!held.xAction) held.xAction = !system(MOUSEORKEY(AXMAP, DOWN));
	}
	
	else if(held.xAction) held.xAction = system(MOUSEORKEY(AXMAP, UP));
	
	if(actionKey >= AO) {
		actionKey -= AO;
		if(!held.oAction) held.oAction = !system(MOUSEORKEY(AOMAP, DOWN));
	}
	
	else if(held.oAction) held.oAction = system(MOUSEORKEY(AOMAP, UP));
	
	if(actionKey == AT) {
		actionKey -= AT;
		if(!held.tAction) held.tAction = !system(MOUSEORKEY(ATMAP, DOWN));
	}
	
	else if(held.tAction) held.tAction = system(MOUSEORKEY(ATMAP, UP));
	
	if (actionKey >= R1) {
		actionKey -= R1;
		if(!held.r1) held.r1 = !system(MOUSEORKEY(R1MAP, DOWN));
	}
	
	else if(held.r1) held.r1 = system(MOUSEORKEY(R1MAP, UP));
	
	if(actionKey >= L1) {
		actionKey -= L1;
		if(!held.l1) held.l1 = !system(MOUSEORKEY(L1MAP, DOWN));
	}
	
	else if(held.l1) held.l1 = system(MOUSEORKEY(L1MAP, UP));
	
	if(actionKey >= R2) {
		actionKey -= R2;
		if(!held.r2) held.r2 = !system(MOUSEORKEY(R2MAP, DOWN));
	}
	
	else if(held.r2) held.r2 = system(MOUSEORKEY(R2MAP, UP));
	
	if(actionKey >= L2) {
		actionKey -= L2;
		if(!held.l2) held.l2 = !system(MOUSEORKEY(L2MAP, DOWN));
	}
	
	else if(held.l2) held.l2 = system(MOUSEORKEY(L2MAP, UP));
	
	if((left.horizontal || left.vertical) && (left.horizontal != 1 && left.vertical != 1)) {
		sprintf(doCommand, "xdotool mousemove_relative -- %f %f", left.horizontal, left.vertical);
		system(doCommand);
	}
	
	if(right.vertical > 2 || right.vertical < -2) {
		verticalScrollDelay--;
		
		if(!verticalScrollDelay) {
			sprintf(doCommand, "xdotool click %i", (right.vertical > 0) ? 5 : 4);
			system(doCommand);
			verticalScrollDelay = 3;
		}
	
		return;
	}
	
	else if(verticalScrollDelay != 3) verticalScrollDelay = 3;
	
	if(right.horizontal > 2 || right.horizontal < -2) {
		horizontalScrollDelay--;
		
		if(!horizontalScrollDelay) {
			sprintf(doCommand, "xdotool keydown shift click %i keyup shift", (right.horizontal > 0) ? 5 : 4);
			system(doCommand);
			horizontalScrollDelay = 2;
		}
	}
	
	else if(horizontalScrollDelay != 2) horizontalScrollDelay = 2;
}

void latchController() {
	
	standby = 1;
	verticalScrollDelay = 3;
	horizontalScrollDelay = 2;
	
	sprintf(doCommand, "/dev/%s", hidraw);
	device = open(doCommand, O_RDONLY);
	
	while (nr = read(device, buf, sizeof(buf))) {
		
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
			left.horizontal = (buf[6] / 10 - 12) * POINTER_SENSITIVITY;
			left.vertical = (buf[7] / 10 - 12) * POINTER_SENSITIVITY;
			right.horizontal = (buf[8] / 10 - 12);
			right.vertical = (buf[9] / 10 - 12);
			
			simulateKeys();
		}
	}
}

int main() {
	while(1) {
		
		if(!system("lsusb | grep -q 'PlayStation 3 Controller'")) {
			sprintf(doCommand, "notify-send -i %s 'DuelShock' 'PS3 controller detected! Press PS button.'", GAMEPAD_ICON);
			system(doCommand);
			
			setNode();
			latchController();
			
			sprintf(doCommand, "notify-send -i %s 'DuelShock' 'Lost connection to PS3 controller. Please reconnect the controller.'", ERROR_ICON);
			system(doCommand);
		}
		
		sleep(3);
	}
	
	return 0;
}
