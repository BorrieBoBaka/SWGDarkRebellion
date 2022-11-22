#ifndef FORCESENSITIVEPROMPTSUICALLBACK_H_
#define FORCESENSITIVEPROMPTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/managers/skill/SkillManager.h"

class ForceSensitivePromptSuiCallback : public SuiCallback {

public:
	ForceSensitivePromptSuiCallback(ZoneServer* server) : SuiCallback(server) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

		if (playerManager == nullptr)
			return;

		if (args->size() < 1)
			return;

        if(cancelPressed) {
            player->sendSystemMessage("Destiny can be a difficult thing to consider. There is truly no wrong answer. You will be asked again the next time you log in until your choice is made.");
            return;
        }
            

		int index = Integer::valueOf(args->get(0).toString());

        //If they said yes, give them FS box 

        if(index == 0) {
            SkillManager* skillManager = SkillManager::instance();
            ManagedReference<PlayerObject*> targetGhost = player->getPlayerObject();
                if(targetGhost != nullptr)
                    targetGhost->setJediState(1);
                else 
                    return;

            bool successful = skillManager->awardSkill("rp_force_prog_novice", player, true, true, true);
            String message = "";
            if(successful) {
                player->setStoredInt("fs_chosen", 1);
                message = "All your life you've had a suspicion that there was more to the galaxy than what you could see with your eyes.";
                message += "You are likely burdened with a great destiny. Tread carefully.";
		        PlayMusicMessage* musicMessage = new PlayMusicMessage("sound/music_short_lightside.snd");
		        player->sendMessage(musicMessage);
            } else {
                if(targetGhost != nullptr)
                    targetGhost->setJediState(0);
                message = "You've delayed a long time making this decision. Now you must pay a price. To embrace force sensitivity, you need to have 20 free skill points.";
            }
            player->sendSystemMessage(message);
        } else {
            //If they said no, give them 5 skiill points
            int currentFreeSkillPoints = player->getStoredInt("starter_skill_points");
            player->setStoredInt("starter_skill_points", currentFreeSkillPoints + 5);
            String message = "Some consider insensitivity to the Force to be a blessing. ";
            message += "Those who are not gifted with the capability of immense power often find other ways to be gifted, and unique. ";
            message += "As you find yourself more reliant on skill and raw talent to get ahead, you are more prepared than most at this point in one's life.";
            PlayMusicMessage* musicMessage = new PlayMusicMessage("sound/mus_quest_theme_docking.snd");
		    player->sendMessage(musicMessage);
            player->sendSystemMessage(message);
            player->setStoredInt("fs_chosen", 1);
        }
	}	

};

#endif /* FORCESENSITIVEPROMPTSUICALLBACK_H_ */