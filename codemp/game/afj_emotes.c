#include "g_local.h"
#include "bg_saga.h"
#include "bg_public.h"

#define EMF_NONE						(0x00u)
#define EMF_STATIC						(0x01u) // hold animation on torso + legs, don't allow movement
#define EMF_HOLD						(0x02u) // hold animation on torso
#define EMF_HOLSTER						(0x04u) // forcibly deactivate saber

qboolean BG_InKnockDown(int anim);
void G_Knockdown(gentity_t *victim);
void saberKnockDown(gentity_t *saberent, gentity_t *saberOwner, gentity_t *other);
qboolean saberKnockOutOfHand(gentity_t *saberent, gentity_t *saberOwner, vec3_t velocity);

typedef struct emote_s {
	const char *name;
	animNumber_t animLoop, animLeave;
	uint32_t flags;
} emote_t;

static const emote_t emotes[] = {
	{ "aimgun", BOTH_STAND5TOAIM, MAX_ANIMATIONS, EMF_HOLD | EMF_HOLSTER },
	{ "atease", BOTH_STAND4, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "beg", BOTH_KNEES2, MAX_ANIMATIONS, EMF_HOLD | EMF_HOLSTER },
	{ "breakdance", BOTH_FORCE_GETUP_B4, MAX_ANIMATIONS, EMF_NONE },
	{ "breakdance2", BOTH_FORCE_GETUP_B6, MAX_ANIMATIONS, EMF_NONE },
	{ "cower", BOTH_COWER1_START, BOTH_COWER1, EMF_HOLSTER },
	{ "dance1", BOTH_TURNSTAND1, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD },
	{ "dance2", BOTH_TURNSTAND4, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "dance3", BOTH_TURNSTAND5, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD },
	{ "die", BOTH_HIT1, BOTH_FORCE_GETUP_F2, EMF_STATIC | EMF_HOLD },
	{ "die2", BOTH_DEATH15, BOTH_FORCE_GETUP_F2, EMF_STATIC | EMF_HOLD },
	{ "fabulous", BOTH_K7_S7_TR, MAX_ANIMATIONS, EMF_HOLD },
	{ "finishinghim", BOTH_SABERKILLER1, MAX_ANIMATIONS, EMF_STATIC },
	{ "harlem", BOTH_FORCE_DRAIN_GRABBED, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD },
	{ "heal", BOTH_FORCEHEAL_START, BOTH_FORCEHEAL_STOP, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "hello", BOTH_SILENCEGESTURE1, MAX_ANIMATIONS, EMF_NONE },
	{ "hiltthrow1", BOTH_SABERTHROW1START, BOTH_SABERTHROW1STOP, EMF_NONE },
	{ "hiltthrow2", BOTH_SABERTHROW2START, BOTH_SABERTHROW2STOP, EMF_NONE },
	{ "hips", BOTH_STAND5TOSTAND8, BOTH_STAND8TOSTAND5, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "kneel", BOTH_CROUCH3, BOTH_UNCROUCH3, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "kneel2", BOTH_ROSH_PAIN, BOTH_UNCROUCH3, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "neo", BOTH_FORCE_GETUP_B4, MAX_ANIMATIONS, EMF_NONE },
	{ "nod", BOTH_HEADNOD, MAX_ANIMATIONS, EMF_NONE },
	{ "noisy", BOTH_SONICPAIN_HOLD, BOTH_SONICPAIN_END, EMF_HOLD },
	{ "power", BOTH_FORCE_GETUP_F2, MAX_ANIMATIONS, EMF_NONE },
	{ "radio", BOTH_TALKCOMM1START, BOTH_TALKCOMM1STOP, EMF_HOLD | EMF_HOLSTER },
	{ "shake", BOTH_HEADSHAKE, MAX_ANIMATIONS, EMF_NONE },
	{ "shovel", BOTH_TUSKENATTACK2, MAX_ANIMATIONS, EMF_NONE },
	{ "sit1", BOTH_SIT1, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD },
	{ "sit2", BOTH_SIT2, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "sit3", BOTH_SIT3, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "sit4", BOTH_SIT4, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "sit6", BOTH_SIT6, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "sleep", BOTH_SLEEP1, BOTH_SLEEP1GETUP, EMF_HOLD | EMF_HOLSTER | EMF_STATIC },
	{ "smack1", BOTH_FORCEGRIP3THROW, MAX_ANIMATIONS, EMF_NONE },
	{ "smack2", BOTH_TOSS1, MAX_ANIMATIONS, EMF_NONE },
	{ "stand", BOTH_STAND8, MAX_ANIMATIONS, EMF_STATIC | EMF_HOLD },
	{ "stepback", BOTH_FORCE_2HANDEDLIGHTNING, MAX_ANIMATIONS, EMF_NONE },
	{ "suggest", BOTH_STAND1_TALK3, MAX_ANIMATIONS, EMF_NONE },
	{ "surrender", TORSO_SURRENDER_START, TORSO_SURRENDER_STOP, EMF_HOLD | EMF_HOLSTER },
	{ "victory", BOTH_TAVION_SCEPTERGROUND, MAX_ANIMATIONS, EMF_NONE },
	{ "wait", BOTH_STAND10, BOTH_STAND10TOSTAND1, EMF_STATIC | EMF_HOLD | EMF_HOLSTER },
	{ "won", TORSO_HANDSIGNAL1, MAX_ANIMATIONS, EMF_NONE },
};
static const size_t numEmotes = ARRAY_LEN(emotes);

static int emotecmp(const void *a, const void *b) {
	return strcmp((const char *)a, ((const emote_t *)b)->name);
}

static qboolean SetEmote(gentity_t *ent, const emote_t *emote) {
	forceHandAnims_t handExtend = HANDEXTEND_TAUNT;
	int emoteTime;

	// busy
	if (ent->client->ps.weaponTime > 0 || ent->client->ps.saberMove > LS_READY || ent->client->ps.fd.forcePowersActive
		|| ent->client->ps.groundEntityNum == ENTITYNUM_NONE || ent->client->ps.duelInProgress
		|| BG_InKnockDown(ent->client->ps.legsAnim) || BG_InRoll(&ent->client->ps, ent->client->ps.legsAnim)
		|| ent->client->ps.forceHandExtend != HANDEXTEND_NONE || ent->client->emote.freeze)
	{
		return qfalse;
	}

	if (emote->flags & EMF_STATIC) {
		// emotes that require you to be standing still
		VectorClear(&ent->client->ps.velocity);
		handExtend = HANDEXTEND_DODGE;
	}
	if (emote->flags & EMF_HOLD) {
		// hold animation on torso
		emoteTime = INT32_MAX;
	}
	else {
		// once off actions
		emoteTime = level.time + BG_AnimLength(ent->localAnimIndex, emote->animLoop);
	}

	// holster saber if necessary
	if ((emote->flags & EMF_HOLSTER) && ent->client->ps.weapon == WP_SABER && ent->client->ps.saberHolstered < 2) {
		ent->client->ps.saberCanThrow = qfalse;
		ent->client->ps.forceRestricted = qtrue;
		ent->client->ps.saberMove = LS_NONE;
		ent->client->ps.saberBlocked = 0;
		ent->client->ps.saberBlocking = 0;
		ent->client->ps.saberHolstered = 2;
		if (ent->client->saber[0].soundOff) {
			G_Sound(ent, CHAN_AUTO, ent->client->saber[0].soundOff);
		}
		if (ent->client->saber[1].model[0] && ent->client->saber[1].soundOff) {
			G_Sound(ent, CHAN_AUTO, ent->client->saber[1].soundOff);
		}
	}

	ent->client->ps.forceHandExtend = handExtend;
	ent->client->ps.forceHandExtendTime = emoteTime;
	ent->client->ps.forceDodgeAnim = emote->animLoop;
	ent->client->emote.nextAnim = emote->animLeave;
	ent->client->emote.freeze = qtrue;

	return qtrue;
}

static void RegularEmote(gentity_t *ent, const char *emoteName) {
	const emote_t *emote = (emote_t *)bsearch(emoteName, emotes, numEmotes, sizeof(emote_t), emotecmp);
	if (!emote) {
		assert(!"Emote not found");
		return;
	}
	SetEmote(ent, emote);
}

#define EMOTE(x) void Cmd_Emote_##x( gentity_t *ent ){RegularEmote( ent, XSTRING(x) );}
#include "afj_emotes.h"
#undef EMOTE