#pragma once
HINSTANCE gModule;

bool IsTeamGame(int k) {
	if (k == GMODE_TEAMDEATHMATCH || k == GMODE_TEAMSURVIVOR || k == GMODE_CTF || k == GMODE_BOTTEAMDEATHMATCH || k == GMODE_TEAMONESHOTONEKILL || k == GMODE_TEAMKEEPTHEFLAG || k == GMODE_TEAMPF || k == GMODE_TEAMLSS || k == GMODE_BOTTEAMSURVIVOR || k == GMODE_BOTTEAMONESHOTONKILL) {
		return true;
	}
	return false;
}