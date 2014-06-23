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
	
	if(dPadKey >= DLEFT) {
		dPadKey -= DLEFT;
		if(!held.dPadLeft) held.dPadLeft = !system(KEYDOWN DLEFTMAP);
	}
	
	else if(held.dPadLeft) held.dPadLeft = system(KEYUP DLEFTMAP);
	
	if(dPadKey >= DDOWN) {
		dPadKey -= DDOWN;
		if(!held.dPadDown) held.dPadDown = !system(KEYDOWN DDOWNMAP);
	}
	
	else if(held.dPadDown) held.dPadDown = system(KEYUP DDOWNMAP);
	
	if(dPadKey >= DRIGHT) {
		dPadKey -= DRIGHT;
		if(!held.dPadRight) held.dPadRight = !system(KEYDOWN DRIGHTMAP);
	}
	
	else if(held.dPadRight) held.dPadRight = system(KEYUP DRIGHTMAP);
	
	if(dPadKey >= DUP) {
		dPadKey -= DUP;
		if(!held.dPadUp) held.dPadUp = !system(KEYDOWN DUPMAP);
	}
	
	else if(held.dPadUp) held.dPadUp = system(KEYUP DUPMAP);
	
	if(dPadKey >= START) {
		dPadKey -= START;
		if(!held.start) held.start = !system(KEYDOWN STARTMAP);
	}
	
	else if(held.start) held.start = system(KEYUP STARTMAP);
	
	if(dPadKey >= R3) {
		dPadKey -= R3;
		if(!held.r3) held.r3 = !system(KEYDOWN R3MAP);
	}
	
	else if(held.r3) held.r3 = system(KEYUP R3MAP);
	
	if(dPadKey >= L3) {
		dPadKey -= L3;
		if(!held.l3) held.l3 = !system(MOUSEDOWN L3MAP);
	}
	
	else if(held.l3) held.l3 = system(MOUSEUP L3MAP);
	
	if(dPadKey >= SELECT) {
		dPadKey -= SELECT;
		if(!held.select) held.select = !system(KEYDOWN SELECTMAP);
	}
	
	else if(held.select) held.select = system(KEYUP SELECTMAP);
	
	if(actionKey >= AS) {
		actionKey -= AS;
		if(!held.sAction) held.sAction = !system(KEYDOWN ASMAP);
	}
	
	else if(held.sAction) held.sAction = system(KEYUP ASMAP);
	
	if(actionKey >= AX) {
		actionKey -= AX;
		if(!held.xAction) held.xAction = !system(MOUSEDOWN AXMAP);
	}
	
	else if(held.xAction) held.xAction = system(MOUSEUP AXMAP);
	
	if(actionKey >= AO) {
		actionKey -= AO;
		if(!held.oAction) held.oAction = !system(MOUSEDOWN AOMAP);
	}
	
	else if(held.oAction) held.oAction = system(MOUSEUP AOMAP);
	
	if(actionKey == AT) {
		actionKey -= AT;
		if(!held.tAction) held.tAction = !system(KEYDOWN ATMAP);
	}
	
	else if(held.tAction) held.tAction = system(KEYUP ATMAP);
	
	if (actionKey >= R1) {
		actionKey -= R1;
		if(!held.r1) held.r1 = !system(KEYDOWN R1MAP);
	}
	
	else if(held.r1) held.r1 = system(KEYUP R1MAP);
	
	if(actionKey >= L1) {
		actionKey -= L1;
		if(!held.l1) held.l1 = !system(KEYDOWN L1MAP);
	}
	
	else if(held.l1) held.l1 = system(KEYUP L1MAP);
	
	if(actionKey >= R2) {
		actionKey -= R2;
		if(!held.r2) held.r2 = !system(KEYDOWN R2MAP);
	}
	
	else if(held.r2) held.r2 = system(KEYUP R2MAP);
	
	if(actionKey >= L2) {
		actionKey -= L2;
		if(!held.l2) held.l2 = !system(KEYDOWN L2MAP);
	}
	
	else if(held.l2) held.l2 = system(KEYUP L2MAP);
	
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

int latchController() {
	
	standby = 1;
	verticalScrollDelay = 3;
	horizontalScrollDelay = 2;
	
	sprintf(doCommand, "/dev/%s", hidraw);
	device = open(doCommand, O_RDONLY);
	
	while (nr = read(device, buf, sizeof(buf))) {
		
		if (nr < 0) {
			dPadKey = 0;
			actionKey = 0;
			left = (struct Stick){0};
			right = (struct Stick){0};
			
			simulateKeys();
			held = (struct Held){0};
			
			return close(device);
		}
		
		if(PS && !held.ps) {
			standby = !standby;
			held.ps = 1;
			
			sprintf(doCommand, "notify-send -i %s 'DuelShock' 'Controller %s Stand-by mode.'", (standby) ? PAUSE_ICON : PLAY_ICON, (standby) ? "in" : "out of");
			
			system(doCommand);
		}
		
		else if(!PS && held.ps) held.ps = 0;
		
		if(!standby) {
			dPadKey = buf[2];
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
