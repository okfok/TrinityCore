#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "ArenaTeamMgr.h"
#include "CellImpl.h"
#include "CharacterCache.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "DisableMgr.h"
#include "GridNotifiers.h"
#include "Group.h"
#include "GroupMgr.h"
#include "InstanceSaveMgr.h"
#include "IpAddress.h"
#include "IPLocation.h"
#include "Item.h"
#include "Language.h"
#include "LFG.h"
#include "Log.h"
#include "MiscPackets.h"
#include "MMapFactory.h"
#include "MotionMaster.h"
#include "MovementDefines.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Pet.h"
#include "Player.h"
#include "Realm.h"
#include "SpellAuras.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "Transport.h"
#include "Weather.h"
#include "WeatherMgr.h"
#include "World.h"
#include "WorldSession.h"

// temporary hack until includes are sorted out (don't want to pull in Windows.h)
#ifdef GetClassName
#undef GetClassName
#endif

#if TRINITY_COMPILER == TRINITY_COMPILER_GNU
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif


using namespace Trinity::ChatCommands;

class custom_commandscript : public CommandScript {
public:
    custom_commandscript() : CommandScript("custom_commandscript") {}

    ChatCommandTable GetCommands() const override {
        static ChatCommandTable commandTable =
                {
                        {"engrave", HandleEngraveCommand, LANG_COMMAND_ENGRAVE_HELP, rbac::RBAC_PERM_COMMAND_ADDITEM, Console::No},
                };
        return commandTable;
    }

    static bool HandleEngraveCommand(ChatHandler *handler, int32 markId, Optional<uint32> markLvl) {
        Player *player = handler->GetSession()->GetPlayer();

        Item *itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, 23);
        if (!itemTarget)
            return false;


        itemTarget->SetItemRandomProperties(markId);

        if (markLvl) {
            itemTarget->SetUInt32Value(ITEM_FIELD_PROPERTY_SEED, uint32(markLvl.value_or(0)));
        } else {
            itemTarget->UpdateItemSuffixFactor();
        }

        return true;
    }
};

void AddSC_custom_commandscript() {
    new custom_commandscript();
}