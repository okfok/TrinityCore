#include "ScriptMgr.h"
#include "GameObject.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "TemporarySummon.h"

class item_xp_extractor : public ItemScript
{
public:
    item_xp_extractor() : ItemScript("item_xp_extractor") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
    {
        if (player->GetLevel() == 80 && player->GetXP() >= 10000){
            ItemPosCountVec dest;
            uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 360018, 1); // Ripe Disgusting Jar
            if (msg == EQUIP_ERR_OK) {
                player->SetXP(player->GetXP() - 10000);
                player->StoreNewItem(dest, 360018, true, GenerateItemRandomPropertyId(360018));
            }
        }
        return true;
    }
};


void AddSC_custom_misc_scripts()
{
    new item_xp_extractor();
}