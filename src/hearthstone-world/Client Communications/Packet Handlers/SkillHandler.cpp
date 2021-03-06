/***
 * Demonstrike Core
 */

#include "StdAfx.h"

/************************************************************************/
/* Talent Anti-Cheat                                                    */
/************************************************************************/

/*
    mage - arcane - 81
    mage - fire - 41
    mage - frost - 61

    rogue - assassination - 182
    rogue - combat - 181
    rogue - subelty - 183

    warlock - afflication - 302
    warlock - demonology - 303
    warlock - destruction - 301

    warrior - arms - 161
    warrior - fury - 163
    warrior - protection - 164

    shaman - elemental - 261
    shaman - enchantment - 263
    shaman - restoration - 262

    paladin - holy - 382
    paladin - protection - 383
    paladin - retribution - 381

    priest - dicipline - 201
    priest - holy - 202
    priest - shadow - 203

    hunter - beast - 361
    hunter - marksmanship - 363
    hunter - survival - 362

    druid - balance - 283
    druid - feral combat - 281
    druid - restoration - 282
*/

void WorldSession::HandleLearnTalentOpcode( WorldPacket & recv_data )
{
    CHECK_INWORLD_RETURN();
 
    uint32 talent_id, requested_rank;
    recv_data >> talent_id >> requested_rank;

    _player->LearnTalent(talent_id, requested_rank);

    _player->smsg_TalentsInfo(false);
}

void WorldSession::HandleLearnPreviewTalents( WorldPacket & recv_data )
{
    uint32 count = 0;
    uint32 talent_id, requested_rank;
    recv_data >> count;
    for(uint32 i = 0; i < count && recv_data.rpos() < recv_data.size(); i++)
    {
        recv_data >> talent_id >> requested_rank;
        _player->LearnTalent(talent_id, requested_rank);
    }
    _player->smsg_TalentsInfo(false);
}

void WorldSession::HandleUnlearnTalents( WorldPacket & recv_data )
{
    CHECK_INWORLD_RETURN();
    uint32 playerGold = GetPlayer()->GetUInt32Value( PLAYER_FIELD_COINAGE );
    uint32 price = GetPlayer()->CalcTalentResetCost(GetPlayer()->GetTalentResetTimes());

    if( playerGold < price ) return;

    GetPlayer()->SetTalentResetTimes(GetPlayer()->GetTalentResetTimes() + 1);
    GetPlayer()->SetUInt32Value( PLAYER_FIELD_COINAGE, playerGold - price );
    GetPlayer()->Reset_Talents();

    GetPlayer()->GetAchievementInterface()->HandleAchievementCriteriaTalentResetCostTotal( price );
    GetPlayer()->GetAchievementInterface()->HandleAchievementCriteriaTalentResetCount();
}

void WorldSession::HandleUnlearnSkillOpcode(WorldPacket& recv_data)
{
    CHECK_INWORLD_RETURN();
    uint32 skill_line;
    recv_data >> skill_line;

    // Cheater detection
    // if(!_player->HasSkillLine(skill_line)) return;

    // Remove any spells within that line that the player has
    _player->RemoveSpellsFromLine(skill_line);

    // Remove any quests finished and active for this skill
    _player->RemoveQuestsFromLine(skill_line);

    // Finally, remove the skill line.
    _player->_RemoveSkillLine(skill_line);
}
